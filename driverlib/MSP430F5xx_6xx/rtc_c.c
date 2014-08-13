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
//*****************************************************************************
//
//rtc_c.c - Driver for the RTC_C Module.
//
//*****************************************************************************
#include "inc/hw_regaccess.h"
#include "rtc_c.h"
#ifdef  __IAR_SYSTEMS_ICC__
#include "deprecated/IAR/msp430xgeneric.h"
#else
#include "deprecated/CCS/msp430xgeneric.h"
#endif
#include "assert.h"

//*****************************************************************************
//
//! Starts the RTC.
//!
//! \param baseAddress is the base address of the RTC_C module.
//!
//! This function clears the RTC main hold bit to allow the RTC to function.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_startClock (uint32_t baseAddress)
{
	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
    HWREG8(baseAddress + OFS_RTCCTL13_L) &= ~(RTCHOLD);
	HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Holds the RTC.
//!
//! \param baseAddress is the base address of the RTC_C module.
//!
//! This function sets the RTC main hold bit to disable RTC functionality.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_holdClock (uint32_t baseAddress)
{
	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
    HWREG8(baseAddress + OFS_RTCCTL13_L) |= RTCHOLD;
	HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Allows and Sets the frequency output to RTCCLK pin for calibration 
//! measurement.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param frequencySelect is the frequency output to RTCCLK.
//!        Valid values are
//!        \b RTC_C_CALIBRATIONFREQ_OFF - turn off calibration output [Default]
//!        \b RTC_C_CALIBRATIONFREQ_512HZ - output signal at 512Hz for calibration
//!        \b RTC_C_CALIBRATIONFREQ_256HZ - output signal at 256Hz for calibration
//!        \b RTC_C_CALIBRATIONFREQ_1HZ - output signal at 1Hz for calibration
//!        Modified bits are \b RTCCALF of \b RTCCTL3 register.
//!
//! This function sets a frequency to measure at the RTCCLK output pin. After
//! testing the set freqeuncy, the calibration could be set accordingly.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_setCalibrationFrequency (uint32_t baseAddress,
    uint16_t frequencySelect)
{
	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
    HWREG16(baseAddress + OFS_RTCCTL13) &= ~(RTCCALF_3);
    HWREG16(baseAddress + OFS_RTCCTL13) |= frequencySelect;
	HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Sets the specified calibration for the RTC.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param offsetDirection is the direction that the calibration offset will go.
//!        Valid values are
//!        \b RTC_C_CALIBRATION_DOWN1PPM - calibrate at steps of -1
//!        \b RTC_C_CALIBRATION_UP1PPM - calibrat at steps of +1
//!        Modified bits are \b RTCOCALS of \b RTCOCAL register.
//! \param offsetValue is the value that the offset will be a factor of; a valid
//!       value is any integer from 1-240.
//!        Modified bits are \b RTC0CALx of \b RTCOCAL register.
//!
//! This function sets the calibration offset to make the RTC as accurate as
//! possible. The offsetDirection can be either +1-ppm or -1-ppm, and the
//! offsetValue should be from 1-240 and is multiplied by the direction setting
//! (i.e. +1-ppm * 8 (offsetValue) = +8-ppm).
//!
//! \return None
//
//*****************************************************************************
void RTC_C_setCalibrationData (uint32_t baseAddress,
    uint8_t offsetDirection,
    uint8_t offsetValue)
{
	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
    HWREG16(baseAddress + OFS_RTCOCAL) = offsetValue + offsetDirection;
	HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Sets the specified temperature compensation for the RTC.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param offsetDirection is the direction that the calibration offset will go.
//!        Valid values are
//!        \b RTC_C_COMPENSATION_DOWN1PPM - calibrate at steps of -1
//!        \b RTC_C_COMPENSATION_UP1PPM - calibrat at steps of +1
//!        Modified bits are \b RTCTCMPS of \b RTCTCMP register.
//! \param offsetValue is the value that the offset will be a factor of; a valid
//!       value is any integer from 1-240.
//!        Modified bits are \b RTCTCMPx of \b RTCTCMP register.
//!
//! This function sets the calibration offset to make the RTC as accurate as
//! possible. The offsetDirection can be either +1-ppm or -1-ppm, and the
//! offsetValue should be from 1-240 and is multiplied by the direction setting
//! (i.e. +1-ppm * 8 (offsetValue) = +8-ppm).
//!
//! \return STATUS_SUCCESS or STATUS_FAILURE of setting the temperature compensation
//
//*****************************************************************************
unsigned short RTC_C_setTemperatureCompensation(uint32_t baseAddress,
	uint8_t offsetDirection,
	uint8_t offsetValue)
{
	
	while(HWREG8(baseAddress + OFS_RTCTCMP_H) & RTCTCRDY_H);
	
	HWREG16(baseAddress + OFS_RTCTCMP) = offsetValue + offsetDirection;
	
	if(HWREG8(baseAddress + OFS_RTCTCMP_H) & RTCTCOK_H) {
		return STATUS_SUCCESS;
	} else {
		return STATUS_FAIL;
	}
}

//*****************************************************************************
//
//! Initializes the settings to operate the RTC in Calendar mode.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param CalendarTime is the structure containing the values for the Calendar
//!       to be intiialized to.
//!        Valid values should be of type Calendar and should contain the
//!        following members and corresponding values:
//!        \b Seconds between 0-59
//!        \b Minutes between 0-59
//!        \b Hours between 0-24
//!        \b DayOfWeek between 0-6
//!        \b DayOfMonth between 0-31
//!        \b Year between 0-4095
//!        NOTE: Values beyond the ones specified may result in eradic behavior.
//! \param formatSelect is the format for the Calendar registers to use.
//!        Valid values are
//!        \b RTC_C_FORMAT_BINARY [Default]
//!        \b RTC_C_FORMAT_BCD
//!        Modified bits are \b RTCBCD of \b RTCCTL1 register.
//!
//! This function initializes the Calendar mode of the RTC_C module.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_calendarInit (uint32_t baseAddress,
    Calendar CalendarTime,
    uint16_t formatSelect)
{

	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;

    HWREG8(baseAddress + OFS_RTCCTL13_L) |= RTCHOLD;

    HWREG16(baseAddress + OFS_RTCCTL13_L) &= ~(RTCBCD);
    HWREG16(baseAddress + OFS_RTCCTL13_L) |= formatSelect;

    HWREG8(baseAddress + OFS_RTCTIM0_L) = CalendarTime.Seconds;
    HWREG8(baseAddress + OFS_RTCTIM0_H) = CalendarTime.Minutes;
    HWREG8(baseAddress + OFS_RTCTIM1_L) = CalendarTime.Hours;
    HWREG8(baseAddress + OFS_RTCTIM1_H) = CalendarTime.DayOfWeek;
    HWREG8(baseAddress + OFS_RTCDATE_L) = CalendarTime.DayOfMonth;
    HWREG8(baseAddress + OFS_RTCDATE_H) = CalendarTime.Month;
    HWREG16(baseAddress + OFS_RTCYEAR) = CalendarTime.Year;

	HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Returns the Calendar Time stored in the Calendar registers of the RTC.
//!
//! \param baseAddress is the base address of the RTC_C module.
//!
//! This function returns the current Calendar time in the form of a Calendar
//! structure.
//!
//! \return A Calendar structure containing the current time.
//
//*****************************************************************************
Calendar RTC_C_getCalendarTime (uint32_t baseAddress)
{
    Calendar tempCal;

    while ( !(HWREG8(baseAddress + OFS_RTCCTL13_L) & RTCRDY) ) ;

    tempCal.Seconds    = HWREG8(baseAddress + OFS_RTCTIM0_L);
    tempCal.Minutes    = HWREG8(baseAddress + OFS_RTCTIM0_H);
    tempCal.Hours      = HWREG8(baseAddress + OFS_RTCTIM1_L);
    tempCal.DayOfWeek  = HWREG8(baseAddress + OFS_RTCTIM1_H);
    tempCal.DayOfMonth = HWREG8(baseAddress + OFS_RTCDATE_L);
    tempCal.Month      = HWREG8(baseAddress + OFS_RTCDATE_H);
    tempCal.Year       = HWREG16(baseAddress + OFS_RTCYEAR);

    return ( tempCal) ;
}

//*****************************************************************************
//
//! Sets and Enables the desired Calendar Alarm settings.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param minutesAlarm is the alarm condition for the minutes.
//!        Valid values are
//!        \b An integer between 0-59, OR
//!        \b RTC_C_ALARMCONDITION_OFF [Default]
//! \param hoursAlarm is the alarm condition for the hours.
//!        Valid values are
//!        \b An integer between 0-24, OR
//!        \b RTC_C_ALARMCONDITION_OFF [Default]
//! \param dayOfWeekAlarm is the alarm condition for the day of week.
//!        Valid values are
//!        \b An integer between 0-6, OR
//!        \b RTC_C_ALARMCONDITION_OFF [Default]
//! \param dayOfMonthAlarm is the alarm condition for the day of the month.
//!        Valid values are
//!        \b An integer between 0-31, OR
//!        \b RTC_C_ALARMCONDITION_OFF [Default]
//!
//! This function sets a Calendar interrupt condition to assert the RTCAIFG
//! interrupt flag. The condition is a logical and of all of the parameters.
//! For example if the minutes and hours alarm is set, then the interrupt will
//! only assert when the minutes AND the hours change to the specified setting.
//! Use the RTC_C_ALARM_OFF for any alarm settings that should not be apart of the
//! alarm condition.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_setCalendarAlarm (uint32_t baseAddress,
    uint8_t minutesAlarm,
    uint8_t hoursAlarm,
    uint8_t dayOfWeekAlarm,
    uint8_t dayOfMonthAlarm)
{
    //Each of these is XORed with 0x80 to turn on if an integer is passed,
    //or turn OFF if RTC_C_ALARM_OFF (0x80) is passed.
    HWREG8(baseAddress + OFS_RTCAMINHR_L) = (minutesAlarm ^ 0x80);
    HWREG8(baseAddress + OFS_RTCAMINHR_H) = (hoursAlarm ^ 0x80);
    HWREG8(baseAddress + OFS_RTCADOWDAY_L) = (dayOfWeekAlarm ^ 0x80);
    HWREG8(baseAddress + OFS_RTCADOWDAY_H) = (dayOfMonthAlarm ^ 0x80);
}

//*****************************************************************************
//
//! Sets a single specified Calendar interrupt condition.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param eventSelect is the condition selected.
//!        Valid values are
//!        \b RTC_C_CALENDAREVENT_MINUTECHANGE - assert interrupt on every minute
//!        \b RTC_C_CALENDAREVENT_HOURCHANGE - assert interrupt on every hour
//!        \b RTC_C_CALENDAREVENT_NOON - assert interrupt when hour is 12
//!        \b RTC_C_CALENDAREVENT_MIDNIGHT - assert interrupt when hour is 0
//!        Modified bits are \b RTCTEV of \b RTCCTL register.
//!
//! This function sets a specified event to assert the RTCTEVIFG interrupt. This
//! interrupt is independent from the Calendar alarm interrupt.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_setCalendarEvent (uint32_t baseAddress,
    uint16_t eventSelect)
{
	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
    HWREG8(baseAddress + OFS_RTCCTL13_L) &= ~(RTCTEV_3); //Reset bits
    HWREG8(baseAddress + OFS_RTCCTL13_L) |= eventSelect;
	HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Sets up an interrupt condition for the selected Prescaler.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param prescaleSelect is the prescaler to define an interrupt for.
//!        Valid values are
//!        \b RTC_C_PRESCALE_0
//!        \b RTC_C_PRESCALE_1
//! \param prescaleEventDivider is a divider to specify when an interrupt can
//!       occur based on the clock source of the selected prescaler.
//!       (Does not affect timer of the selected prescaler).
//!       Valid values are
//!       \b RTC_C_PSEVENTDIVIDER_2 [Default]
//!       \b RTC_C_PSEVENTDIVIDER_4
//!       \b RTC_C_PSEVENTDIVIDER_8
//!       \b RTC_C_PSEVENTDIVIDER_16
//!       \b RTC_C_PSEVENTDIVIDER_32
//!       \b RTC_C_PSEVENTDIVIDER_64
//!       \b RTC_C_PSEVENTDIVIDER_128
//!       \b RTC_C_PSEVENTDIVIDER_256
//!        Modified bits are \b RTxIP of \b RTCPSxCTL register.
//!
//! This function sets the condition for an interrupt to assert based on the
//! individual prescalers.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_definePrescaleEvent (uint32_t baseAddress,
    uint8_t prescaleSelect,
    uint8_t prescaleEventDivider)
{
    HWREG8(baseAddress + OFS_RTCPS0CTL_L + prescaleSelect) &= ~(RT0IP_7);
    HWREG8(baseAddress + OFS_RTCPS0CTL_L +
        prescaleSelect) |= prescaleEventDivider;
}

//*****************************************************************************
//
//! Returns the selected Prescaler value.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param prescaleSelect is the prescaler to obtain the value of.
//!        Valid values are
//!        \b RTC_C_PRESCALE_0
//!        \b RTC_C_PRESCALE_1
//!
//! This function returns the value of the selected prescale counter register.
//! The counter should be held before reading. If in counter mode, the individual
//! prescaler can be held, while in Calendar mode the whole RTC must be held.
//!
//! \return The value of the specified Prescaler count register
//
//*****************************************************************************
uint8_t RTC_C_getPrescaleValue (uint32_t baseAddress,
    uint8_t prescaleSelect)
{
    if (RTC_C_PRESCALE_0 == prescaleSelect){
        return ( HWREG8(baseAddress + OFS_RTCPS_L) );
    } else if (RTC_C_PRESCALE_1 == prescaleSelect){
        return ( HWREG8(baseAddress + OFS_RTCPS_H) );
    } else   {
        return ( 0) ;
    }
}

//*****************************************************************************
//
//! Sets the selected Prescaler value.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param prescaleSelect is the prescaler to set the value for.
//!        Valid values are
//!        \b RTC_C_PRESCALE_0
//!        \b RTC_C_PRESCALE_1
//! \param prescaleCounterValue is the specified value to set the prescaler to;
//!       a valid value is any integer from 0-255.
//!        Modified bits are \b RTxPS of \b RTxPS register.
//!
//! This function sets the prescale counter value. Before setting the prescale
//! counter, it should be held.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_setPrescaleCounterValue (uint32_t baseAddress,
    uint8_t prescaleSelect,
    uint8_t prescaleCounterValue)
{
	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
    if (RTC_C_PRESCALE_0 == prescaleSelect){
        HWREG8(baseAddress + OFS_RTCPS_L) = prescaleCounterValue;
    } else if (RTC_C_PRESCALE_1 == prescaleSelect){
        HWREG8(baseAddress + OFS_RTCPS_H) = prescaleCounterValue;
    }
	HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables selected RTC interrupt sources.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param interruptMask is a bit mask of the interrupts to enable.
//!        Mask Value is the logical OR of any of the following
//!        \b RTC_C_TIME_EVENT_INTERRUPT - asserts when counter overflows in
//!             counter mode or when Calendar event condition defined by 
//!             defineCalendarEvent() is met.
//!        \b RTC_C_CLOCK_ALARM_INTERRUPT - asserts when alarm condition in
//!             Calendar mode is met.
//!        \b RTC_C_CLOCK_READ_READY_INTERRUPT - asserts when Calendar registers
//!             are settled.
//!        \b RTC_C_PRESCALE_TIMER0_INTERRUPT - asserts when Prescaler 0 event
//!             condition is met.
//!        \b RTC_C_PRESCALE_TIMER1_INTERRUPT - asserts when Prescaler 1 event
//!             condition is met.
//!        \b RTC_C_OSCILLATOR_FAULT_INTERRUPT - asserts if there is
//!             a problem with the 32kHz oscillator, while the RTC is running.
//!
//! This function enables the selected RTC interrupt source.  Only the sources
//! that are enabled can be reflected to the processor interrupt; disabled
//! sources have no effect on the processor. <b>Does not clear interrupt 
//! flags.</b>
//!
//! \return None
//
//*****************************************************************************
void RTC_C_enableInterrupt (uint32_t baseAddress,
    uint8_t interruptMask)
{
    if ( interruptMask & (RTCOFIE + RTCTEVIE + RTCAIE + RTCRDYIE) ){
    	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
        HWREG8(baseAddress + OFS_RTCCTL0_L) |=
            (interruptMask & (RTCOFIE + RTCTEVIE + RTCAIE + RTCRDYIE));
    	HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
    }

    if (interruptMask & RTC_C_PRESCALE_TIMER0_INTERRUPT){
        HWREG8(baseAddress + OFS_RTCPS0CTL_L) |= RT0PSIE;
    }

    if (interruptMask & RTC_C_PRESCALE_TIMER1_INTERRUPT){
        HWREG8(baseAddress + OFS_RTCPS1CTL_L) |= RT1PSIE;
    }
}

//*****************************************************************************
//
//! Disables selected RTC interrupt sources.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param interruptMask is a bit mask of the interrupts to disable.
//!        Mask Value is the logical OR of any of the following
//!        \b RTC_C_TIME_EVENT_INTERRUPT - asserts when counter overflows in
//!             counter mode or when Calendar event condition defined by 
//!             defineCalendarEvent() is met.
//!        \b RTC_C_CLOCK_ALARM_INTERRUPT - asserts when alarm condition in
//!             Calendar mode is met.
//!        \b RTC_C_CLOCK_READ_READY_INTERRUPT - asserts when Calendar registers
//!             are settled.
//!        \b RTC_C_PRESCALE_TIMER0_INTERRUPT - asserts when Prescaler 0 event
//!             condition is met.
//!        \b RTC_C_PRESCALE_TIMER1_INTERRUPT - asserts when Prescaler 1 event
//!             condition is met.
//!        \b RTC_C_OSCILLATOR_FAULT_INTERRUPT - asserts if there is a problem
//!				with the 32kHz oscillator, while the RTC is running.
//!
//! This function disables the selected RTC interrupt source.  Only the sources
//! that are enabled can be reflected to the processor interrupt; disabled
//! sources have no effect on the processor.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_disableInterrupt (uint32_t baseAddress,
    uint8_t interruptMask)
{

    if ( interruptMask & (RTCOFIE + RTCTEVIE + RTCAIE + RTCRDYIE) ){
    	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
        HWREG8(baseAddress + OFS_RTCCTL0_L) &=
            ~(interruptMask & (RTCOFIE + RTCTEVIE + RTCAIE + RTCRDYIE));
    	HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
    }

    if (interruptMask & RTC_C_PRESCALE_TIMER0_INTERRUPT){
        HWREG8(baseAddress + OFS_RTCPS0CTL_L) &= ~(RT0PSIE);
    }

    if (interruptMask & RTC_C_PRESCALE_TIMER1_INTERRUPT){
        HWREG8(baseAddress + OFS_RTCPS1CTL_L) &= ~(RT1PSIE);
    }
}

//*****************************************************************************
//
//! Returns the status of the selected interrupts flags.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param interruptFlagMask is a bit mask of the interrupt flags to return the
//!       status of.
//!        Mask Value is the logical OR of any of the following
//!        \b RTC_C_TIME_EVENT_INTERRUPT - asserts when counter overflows in
//!             counter mode or when Calendar event condition defined by 
//!             defineCalendarEvent() is met.
//!        \b RTC_C_CLOCK_ALARM_INTERRUPT - asserts when alarm condition in
//!             Calendar mode is met.
//!        \b RTC_C_CLOCK_READ_READY_INTERRUPT - asserts when Calendar registers
//!             are settled.
//!        \b RTC_C_PRESCALE_TIMER0_INTERRUPT - asserts when Prescaler 0 event
//!             condition is met.
//!        \b RTC_C_PRESCALE_TIMER1_INTERRUPT - asserts when Prescaler 1 event
//!             condition is met.
//!        \b RTC_C_OSCILLATOR_FAULT_INTERRUPT - asserts if there is a problem
//!				with the 32kHz oscillator, while the RTC is running.
//!
//! This function returns the status of the interrupt flag for the selected
//! channel.
//!
//! \return A bit mask of the selected interrupt flag's status.
//
//*****************************************************************************
uint8_t RTC_C_getInterruptStatus (uint32_t baseAddress,
    uint8_t interruptFlagMask)
{
    uint8_t tempInterruptFlagMask = 0x0000;

    tempInterruptFlagMask |= (HWREG8(baseAddress + OFS_RTCCTL0_L)
                              & ((interruptFlagMask >> 4)
                                 & (RTCOFIFG + 
                                    RTCTEVIFG + 
                                    RTCAIFG + 
                                    RTCRDYIFG)));
    
    tempInterruptFlagMask = tempInterruptFlagMask << 4;

    if (interruptFlagMask & RTC_C_PRESCALE_TIMER0_INTERRUPT){
        if ( HWREG8(baseAddress + OFS_RTCPS0CTL_L) & RT0PSIFG){
            tempInterruptFlagMask |= RTC_C_PRESCALE_TIMER0_INTERRUPT;
        }
    }

    if (interruptFlagMask & RTC_C_PRESCALE_TIMER1_INTERRUPT){
        if ( HWREG8(baseAddress + OFS_RTCPS1CTL_L) & RT1PSIFG){
            tempInterruptFlagMask |= RTC_C_PRESCALE_TIMER1_INTERRUPT;
        }
    }

    return ( tempInterruptFlagMask) ;
}

//*****************************************************************************
//
//! Clears selected RTC interrupt flags.
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param interruptFlagMask is a bit mask of the interrupt flags to be cleared.
//!        Mask Value is the logical OR of any of the following
//!        \b RTC_C_TIME_EVENT_INTERRUPT - asserts when counter overflows in
//!             counter mode or when Calendar event condition defined by 
//!             defineCalendarEvent() is met.
//!        \b RTC_C_CLOCK_ALARM_INTERRUPT - asserts when alarm condition in
//!             Calendar mode is met.
//!        \b RTC_C_CLOCK_READ_READY_INTERRUPT - asserts when Calendar registers
//!             are settled.
//!        \b RTC_C_PRESCALE_TIMER0_INTERRUPT - asserts when Prescaler 0 event
//!             condition is met.
//!        \b RTC_C_PRESCALE_TIMER1_INTERRUPT - asserts when Prescaler 1 event
//!             condition is met.
//!        \b RTC_C_OSCILLATOR_FAULT_INTERRUPT - asserts if there is
//!             a problem with the 32kHz oscillator, while the RTC is running.
//!
//! This function clears the RTC interrupt flag is cleared, so that it no longer
//! asserts.
//!
//! \return None
//
//*****************************************************************************
void RTC_C_clearInterrupt (uint32_t baseAddress,
    uint8_t interruptFlagMask)
{

    if ( interruptFlagMask & (RTC_C_TIME_EVENT_INTERRUPT +
                              RTC_C_CLOCK_ALARM_INTERRUPT +
                              RTC_C_CLOCK_READ_READY_INTERRUPT +
                              RTC_C_OSCILLATOR_FAULT_INTERRUPT) ){
    	HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
        HWREG8(baseAddress + OFS_RTCCTL0_L) &=
            ~((interruptFlagMask>>4) & (RTCOFIFG + 
                                        RTCTEVIFG + 
                                        RTCAIFG + 
                                        RTCRDYIFG));
        HWREG8(baseAddress + OFS_RTCCTL0_H) = 0x00;
    }

    if (interruptFlagMask & RTC_C_PRESCALE_TIMER0_INTERRUPT){
        HWREG8(baseAddress + OFS_RTCPS0CTL_L) &= ~(RT0PSIFG);
    }

    if (interruptFlagMask & RTC_C_PRESCALE_TIMER1_INTERRUPT){
        HWREG8(baseAddress + OFS_RTCPS1CTL_L) &= ~(RT1PSIFG);
    }
}

//*****************************************************************************
//
//! Returns the given BCD value in Binary Format
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param valueToConvert is the raw value in BCD format to convert to Binary.
//!        Modified bits are \b BCD2BIN of \b BCD2BIN register.
//!
//! This function converts BCD values to Binary format.
//!
//! \return The Binary version of the valueToConvert parameter.
//
//*****************************************************************************
uint16_t RTC_C_convertBCDToBinary (uint32_t baseAddress,
    uint16_t valueToConvert)
{
    HWREG16(baseAddress + OFS_BCD2BIN) = valueToConvert;
    return ( HWREG16(baseAddress + OFS_BCD2BIN) );
}

//*****************************************************************************
//
//! Returns the given Binary value in BCD Format
//!
//! \param baseAddress is the base address of the RTC_C module.
//! \param valueToConvert is the raw value in Binary format to convert to BCD.
//!        Modified bits are \b BIN2BCD of \b BIN2BCD register.
//!
//! This function converts Binary values to BCD format.
//!
//! \return The BCD version of the valueToConvert parameter.
//
//*****************************************************************************
uint16_t RTC_C_convertBinaryToBCD (uint32_t baseAddress,
    uint16_t valueToConvert)
{
    HWREG16(baseAddress + OFS_BIN2BCD) = valueToConvert;
    return ( HWREG16(baseAddress + OFS_BIN2BCD) );
}
//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************


