/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */
/* ----------------------- Platform includes --------------------------------*/
#include "port.h"



/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "mb_m.h"
#include "stm32f1xx_hal.h"



/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR(void);



/* ----------------------- Variables ----------------------------------------*/
extern TIM_HandleTypeDef* modbusTimer;

uint16_t timerPeriod = 0;
uint16_t timerCounter = 0;



/* ----------------------- Start implementation -----------------------------*/

/*----------------------------------------------------------------------------*/
BOOL xMBMasterPortTimersInit(USHORT usTim1Timerout50us)
{
  timerPeriod = usTim1Timerout50us;
  return TRUE;
}



/* --------------------------------------------------------------------------*/
inline void vMBMasterPortTimersT35Enable()
{
  vMBMasterSetCurTimerMode(MB_TMODE_T35);
  timerCounter = 0;
  HAL_TIM_Base_Start_IT(modbusTimer);
}



/* --------------------------------------------------------------------------*/
void vMBMasterPortTimersConvertDelayEnable()
{
  vMBMasterSetCurTimerMode(MB_TMODE_CONVERT_DELAY);
}



/* --------------------------------------------------------------------------*/
void vMBMasterPortTimersRespondTimeoutEnable()
{
  vMBMasterSetCurTimerMode(MB_TMODE_RESPOND_TIMEOUT);
}



/* --------------------------------------------------------------------------*/
inline void vMBMasterPortTimersDisable()
{
  HAL_TIM_Base_Stop_IT(modbusTimer);
}



/* --------------------------------------------------------------------------*/
static void prvvTIMERExpiredISR(void)
{
    ( void )pxMBMasterPortCBTimerExpired();
}



/* --------------------------------------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == modbusTimer->Instance)
  {
    timerCounter++;

    if (timerCounter == timerPeriod)
    {
      prvvTIMERExpiredISR();
    }
  }
}



/* --------------------------------------------------------------------------*/
