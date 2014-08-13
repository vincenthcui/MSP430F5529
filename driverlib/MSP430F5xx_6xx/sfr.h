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
#ifndef __MSP430WARE_SFR_H__
#define __MSP430WARE_SFR_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_SFR__

#include "inc/hw_regaccess.h"

//*****************************************************************************
//
//The following are values that can be passed to SFR_setResetPinPullResistor()
//in the pullResistorSetup parameter.
//
//*****************************************************************************
#define SFR_RESISTORDISABLE         ( !(SYSRSTRE + SYSRSTUP) )
#define SFR_RESISTORENABLE_PULLUP   ( SYSRSTRE + SYSRSTUP )
#define SFR_RESISTORENABLE_PULLDOWN (SYSRSTRE)

//*****************************************************************************
//
//The following are values that can be passed to SFR_setNMIEdge()
//in the edgeDirection parameter.
//
//*****************************************************************************
#define SFR_NMI_RISINGEDGE  ( !(SYSNMIIES) )
#define SFR_NMI_FALLINGEDGE (SYSNMIIES)

//*****************************************************************************
//
//The following are values that can be passed to SFR_setResetNMIPinFunction()
//in the resetPinFunction parameter.
//
//*****************************************************************************
#define SFR_RESETPINFUNC_RESET ( !(SYSNMI) )
#define SFR_RESETPINFUNC_NMI   (SYSNMI)

//******************************************************************************
//
//The following are values that can be passed to 
//SFR_enableInterrupt(), SFR_disableInterrupt(), SFR_getInterruptStatus(),
//SFR_clearInterrupt() in the outboxSelect parameter.
//
//******************************************************************************
#define SFR_JTAG_OUTBOX_INTERRUPT                         JMBOUTIE
#define SFR_JTAG_INBOX_INTERRUPT                          JMBINIE
#define SFR_FLASH_CONTROLLER_ACCESS_VIOLATION_INTERRUPT   ACCVIE
#define SFR_NMI_PIN_INTERRUPT                             NMIIE
#define SFR_VACANT_MEMORY_ACCESS_INTERRUPT                VMAIE
#define SFR_OSCILLATOR_FAULT_INTERRUPT                    OFIE
#define SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT             WDTIE

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************

extern void SFR_enableInterrupt (uint32_t baseAddress,
    uint8_t interruptMask);

extern void SFR_disableInterrupt (uint32_t baseAddress,
    uint8_t interruptMask);

extern uint8_t SFR_getInterruptStatus (uint32_t baseAddress,
    uint8_t interruptFlagMask);

extern void SFR_clearInterrupt (uint32_t baseAddress,
    uint8_t interruptFlagMask);

extern void SFR_setResetPinPullResistor (uint32_t baseAddress,
    uint16_t pullResistorSetup);

extern void SFR_setNMIEdge (uint32_t baseAddress,
    uint16_t edgeDirection);

extern void SFR_setResetNMIPinFunction (uint32_t baseAddress,
    uint8_t resetPinFunction);

#endif
