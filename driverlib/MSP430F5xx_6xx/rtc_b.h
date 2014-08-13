/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#ifndef __MSP430WARE_RTC_B_H__
#define __MSP430WARE_RTC_B_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_RTC_B__

#include "inc/hw_regaccess.h"

//*****************************************************************************
//
//The following is a struct that can be passed to RTC_B_CalendarInit() in the
//CalendarTime parameter, as well as returned by RTC_B_getCalendarTime()
//
//*****************************************************************************
typedef struct {
    uint8_t Seconds;
    uint8_t Minutes;
    uint8_t Hours;
    uint8_t DayOfWeek;
    uint8_t DayOfMonth;
    uint8_t Month;
    uint16_t Year;
} Calendar;

//*****************************************************************************
//
//The following are values that can be passed to RTC_B_setCalibrationData()
//in the offsetDirection parameter.
//
//*****************************************************************************
#define RTC_B_CALIBRATIONFREQ_OFF   (RTCCALF_0)
#define RTC_B_CALIBRATIONFREQ_512HZ (RTCCALF_1)
#define RTC_B_CALIBRATIONFREQ_256HZ (RTCCALF_2)
#define RTC_B_CALIBRATIONFREQ_1HZ   (RTCCALF_3)

//*****************************************************************************
//
//The following are values that can be passed to RTC_B_setCalibrationData()
//in the offsetDirection parameter.
//
//*****************************************************************************
#define RTC_B_CALIBRATION_DOWN2PPM  ( !(RTCCALS) )
#define RTC_B_CALIBRATION_UP4PPM    (RTCCALS)

//*****************************************************************************
//
//The following are values that can be passed to RTC_B_setClockRegistersFormat()
//in the formatSelect parameter.
//
//*****************************************************************************
#define RTC_B_FORMAT_BINARY  ( !(RTCBCD) )
#define RTC_B_FORMAT_BCD     (RTCBCD)

//*****************************************************************************
//
//The following is a value that can be passed to RTC_B_setCalendarAlarm() in the
//minutesAlarm, hoursAlarm, dayOfWeekAlarm, and dayOfMonthAlarm parameters.
//
//*****************************************************************************
#define RTC_B_ALARMCONDITION_OFF  (0x80)

//*****************************************************************************
//
//The following are values that can be passed to RTC_B_setCalendarEvent()
//in the eventSelect parameter.
//
//*****************************************************************************
#define RTC_B_CALENDAREVENT_MINUTECHANGE  (RTCTEV_0)
#define RTC_B_CALENDAREVENT_HOURCHANGE    (RTCTEV_1)
#define RTC_B_CALENDAREVENT_NOON          (RTCTEV_2)
#define RTC_B_CALENDAREVENT_MIDNIGHT      (RTCTEV_3)

//*****************************************************************************
//
//The following are values that can be passed to RTC_B_counterPrescaleInit(),
//RTC_B_definePreScaleEvent(), RTC_B_readPrescaleCounterValue(), and
//RTC_B_setPrescaleCounterValue() in the prescaleSelect parameter.
//
//*****************************************************************************
#define RTC_B_PRESCALE_0  (0x0)
#define RTC_B_PRESCALE_1  (0x2)

//*****************************************************************************
//The following are values that can be passed to RTC_B_definePrescaleEvent()
//in the prescaleEventDivider parameter.
//
//*****************************************************************************
#define RTC_B_PSEVENTDIVIDER_2   (RT0IP_0)
#define RTC_B_PSEVENTDIVIDER_4   (RT0IP_1)
#define RTC_B_PSEVENTDIVIDER_8   (RT0IP_2)
#define RTC_B_PSEVENTDIVIDER_16  (RT0IP_3)
#define RTC_B_PSEVENTDIVIDER_32  (RT0IP_4)
#define RTC_B_PSEVENTDIVIDER_64  (RT0IP_5)
#define RTC_B_PSEVENTDIVIDER_128 (RT0IP_6)
#define RTC_B_PSEVENTDIVIDER_256 (RT0IP_7)

//*****************************************************************************
//
//The following are values that can be passed to RTC_B_getInterruptStatus(),
//RTC_B_clearInterrupt(), RTC_B_enableInterrupt(),  RTC_B_disableInterrupt()
//in the interruptFlagMask parameter.
//
//*****************************************************************************
#define RTC_B_OSCILLATOR_FAULT_INTERRUPT  RTCOFIE   
#define RTC_B_TIME_EVENT_INTERRUPT        RTCTEVIE  
#define RTC_B_CLOCK_ALARM_INTERRUPT       RTCAIE    
#define RTC_B_CLOCK_READ_READY_INTERRUPT  RTCRDYIE  
#define RTC_B_PRESCALE_TIMER0_INTERRUPT   0x02
#define RTC_B_PRESCALE_TIMER1_INTERRUPT   0x01


//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************
extern void RTC_B_startClock (uint32_t baseAddress);

extern void RTC_B_holdClock (uint32_t baseAddress);

extern void RTC_B_setCalibrationFrequency (uint32_t baseAddress,
    uint16_t frequencySelect);

extern void RTC_B_setCalibrationData (uint32_t baseAddress,
    uint8_t offsetDirection,
    uint8_t offsetValue);

extern void RTC_B_calendarInit (uint32_t baseAddress,
    Calendar CalendarTime,
    uint16_t formatSelect);

extern Calendar RTC_B_getCalendarTime (uint32_t baseAddress);

extern void RTC_B_setCalendarAlarm (uint32_t baseAddress,
    uint8_t minutesAlarm,
    uint8_t hoursAlarm,
    uint8_t dayOfWeekAlarm,
    uint8_t dayOfMonthAlarm);

extern void RTC_B_setCalendarEvent (uint32_t baseAddress,
    uint16_t eventSelect);

extern void RTC_B_definePrescaleEvent (uint32_t baseAddress,
    uint8_t prescaleSelect,
    uint8_t prescaleEventDivider);

extern uint8_t RTC_B_getPrescaleValue (uint32_t baseAddress,
    uint8_t prescaleSelect);

extern void RTC_B_setPrescaleValue (uint32_t baseAddress,
    uint8_t prescaleSelect,
    uint8_t prescaleCounterValue);

extern void RTC_B_enableInterrupt (uint32_t baseAddress,
    uint8_t interruptMask);

extern void RTC_B_disableInterrupt (uint32_t baseAddress,
    uint8_t interruptMask);

extern uint8_t RTC_B_getInterruptStatus (uint32_t baseAddress,
    uint8_t interruptFlagMask);

extern void RTC_B_clearInterrupt (uint32_t baseAddress,
    uint8_t interruptFlagMask);

extern uint16_t RTC_B_convertBCDToBinary (uint32_t baseAddressu,
    uint16_t valueToConvert);

extern uint16_t RTC_B_convertBinaryToBCD (uint32_t baseAddress,
    uint16_t valueToConvert);

#endif
