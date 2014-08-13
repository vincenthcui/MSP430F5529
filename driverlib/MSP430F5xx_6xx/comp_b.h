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
#ifndef __MSP430WARE_COMP_B_H__
#define __MSP430WARE_COMP_B_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_COMPB__

#include "inc/hw_regaccess.h"

//*****************************************************************************
//
//The following are values that can be passed to Comp_init(),
//Comp_disableInputBuffer(), and Comp_enableInputBuffer() in the
//positiveTerminalInput, negativeTerminalInput, and inputPort parameters.
//
//*****************************************************************************
#define COMP_B_INPUT0  (CBIPSEL_0)
#define COMP_B_INPUT1  (CBIPSEL_1)
#define COMP_B_INPUT2  (CBIPSEL_2)
#define COMP_B_INPUT3  (CBIPSEL_3)
#define COMP_B_INPUT4  (CBIPSEL_4)
#define COMP_B_INPUT5  (CBIPSEL_5)
#define COMP_B_INPUT6  (CBIPSEL_6)
#define COMP_B_INPUT7  (CBIPSEL_7)
#define COMP_B_INPUT8  (CBIPSEL_8)
#define COMP_B_INPUT9  (CBIPSEL_9)
#define COMP_B_INPUT10 (CBIPSEL_10)
#define COMP_B_INPUT11 (CBIPSEL_11)
#define COMP_B_INPUT12 (CBIPSEL_12)
#define COMP_B_INPUT13 (CBIPSEL_13)
#define COMP_B_INPUT14 (CBIPSEL_14)
#define COMP_B_INPUT15 (CBIPSEL_15)
#define COMP_B_VREF    (0x10)

//*****************************************************************************
//
//The following are values that can be passed to Comp_init() in the
//powerModeSelect parameter.
//
//*****************************************************************************
#define COMP_B_POWERMODE_HIGHSPEED     (CBPWRMD_0)
#define COMP_B_POWERMODE_NORMALMODE    (CBPWRMD_1)
#define COMP_B_POWERMODE_ULTRALOWPOWER (CBPWRMD_2)

//*****************************************************************************
//
//The following are values that can be passed to Comp_init() in the
//outputFilterEnableAndDelayLevel parameter.
//
//*****************************************************************************
#define COMP_B_FILTEROUTPUT_OFF     0x00
#define COMP_B_FILTEROUTPUT_DLYLVL1 (CBF + CBFDLY_0)
#define COMP_B_FILTEROUTPUT_DLYLVL2 (CBF + CBFDLY_1)
#define COMP_B_FILTEROUTPUT_DLYLVL3 (CBF + CBFDLY_2)
#define COMP_B_FILTEROUTPUT_DLYLVL4 (CBF + CBFDLY_3)

//*****************************************************************************
//
//The following are values that can be passed to Comp_init() in the
//invertedOutputPolarity parameter.
//
//*****************************************************************************
#define COMP_B_NORMALOUTPUTPOLARITY   ( !(CBOUTPOL) )
#define COMP_B_INVERTEDOUTPUTPOLARITY (CBOUTPOL)

//*****************************************************************************
//
//The following are values that can be passed to Comp_setReferenceVoltage() in
//the supplyVoltageBase parameter.
//
//*****************************************************************************
#define COMP_B_VREFBASE_VCC (CBREFL_0)
#define COMP_B_VREFBASE1_5V (CBREFL_1)
#define COMP_B_VREFBASE2_0V (CBREFL_2)
#define COMP_B_VREFBASE2_5V (CBREFL_3)

//*****************************************************************************
//
//The following are values that can be passed to Comp_setReferenceVoltage() in
//the refrenceAccuracy parameter.
//
//*****************************************************************************
#define COMP_B_ACCURACY_STATIC	(!CBREFACC)
#define COMP_B_ACCURACY_CLOCKED	(CBREFACC)

//*****************************************************************************
//
//The following are values that can be passed to Comp_setEdgeDirection() in
//the edgeDirection parameter.
//
//*****************************************************************************
#define COMP_B_FALLINGEDGE ( !(CBIES) )
#define COMP_B_RISINGEDGE  (CBIES)

//*****************************************************************************
//
//The following are values that returned by COMP_B_outputValue().
//
//*****************************************************************************
#define COMP_B_LOW  (0x0)
#define COMP_B_HIGH (0x1)


//*****************************************************************************
//API
//*****************************************************************************

extern unsigned short COMP_B_init (uint32_t baseAddress,
    uint8_t positiveTerminalInput,
    uint8_t negativeTerminalInput,
    uint16_t powerModeSelect,
    uint8_t outputFilterEnableAndDelayLevel,
    unsigned short invertedOutputPolarity);

void COMP_B_setReferenceVoltage (uint32_t baseAddress,
    	uint16_t supplyVoltageReferenceBase,
    	uint16_t lowerLimitSupplyVoltageFractionOf32,
    	uint16_t upperLimitSupplyVoltageFractionOf32,
    	uint16_t refrenceAccuracy);

extern void COMP_B_enableInterrupt (uint32_t baseAddress, uint16_t mask);

extern void COMP_B_disableInterrupt (uint32_t baseAddress,
    uint16_t mask);

extern void COMP_B_clearInterrupt (uint32_t baseAddress, uint16_t mask);

extern uint8_t COMP_B_getInterruptStatus (uint32_t baseAddress,
    uint16_t mask);

extern void COMP_B_interruptSetEdgeDirection (uint32_t baseAddress,
    unsigned short edgeDirection);

extern void COMP_B_interruptToggleEdgeDirection (uint32_t baseAddress);

extern void COMP_B_enable (uint32_t baseAddress);

extern void COMP_B_disable (uint32_t baseAddress);

extern void COMP_B_shortInputs (uint32_t baseAddress);

extern void COMP_B_unshortInputs (uint32_t baseAddress);

extern void COMP_B_enableShortOfInputs (uint32_t baseAddress);

extern void COMP_B_disableShortOfInputs (uint32_t baseAddress);

extern void COMP_B_disableInputBuffer (uint32_t baseAddress,
    uint8_t inputPort);

extern void COMP_B_enableInputBuffer (uint32_t baseAddress,
    uint8_t inputPort);

extern void COMP_B_IOSwap (uint32_t baseAddress);

extern unsigned short COMP_B_outputValue (uint32_t baseAddress);

#endif
