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
#ifndef __MSP430WARE_USCI_A_SPI_H__
#define __MSP430WARE_USCI_A_SPI_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_USCI_Ax__

#include "inc/hw_regaccess.h"

//*****************************************************************************
//
//The following are values that can be passed to the USCI_A_SPI_masterInit() API
//as the selectClockSource parameter.
//
//*****************************************************************************
#define USCI_A_SPI_CLOCKSOURCE_ACLK    UCSSEL__ACLK
#define USCI_A_SPI_CLOCKSOURCE_SMCLK   UCSSEL__SMCLK

//*****************************************************************************
//
//The following are values that can be passed to the USCI_A_SPI_masterInit() ,
//USCI_A_SPI_slaveInit() API as the msbFirst parameter.
//
//*****************************************************************************
#define USCI_A_SPI_MSB_FIRST    UCMSB
#define USCI_A_SPI_LSB_FIRST    0x00

//*****************************************************************************
//
//The following are values that can be returned by the USCI_A_SPI_isBusy() API
//
//*****************************************************************************
#define USCI_A_SPI_BUSY        UCBUSY
#define USCI_A_SPI_NOT_BUSY    0x00

//*****************************************************************************
//
//The following are values that can be passed to the USCI_A_SPI_masterInit() ,
//USCI_A_SPI_slaveInit() API as the clockPhase parameter.
//
//*****************************************************************************
#define USCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT    0x00
#define USCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT    UCCKPH

//*****************************************************************************
//
//The following are values that can be passed to the USCI_A_SPI_masterInit() ,
//USCI_A_SPI_slaveInit() API as the clockPolarity parameter.
//
//*****************************************************************************
#define USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH    UCCKPL
#define USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW     0x00

//*****************************************************************************
//
//The following are values that can be passed to the USCI_A_SPI_enableInterrupt() ,
//USCI_A_SPI_disableInterrupt(), USCI_A_SPI_getInterruptStatus(),  API as the mask parameter.
//
//*****************************************************************************
#define USCI_A_SPI_TRANSMIT_INTERRUPT    UCTXIE
#define USCI_A_SPI_RECEIVE_INTERRUPT     UCRXIE

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************
extern unsigned short USCI_A_SPI_masterInit (uint32_t baseAddress,
    uint8_t selectClockSource,
    uint32_t clockSourceFrequency,
    uint32_t desiredSpiClock,
    uint8_t msbFirst,
    uint8_t clockPhase,
    uint8_t clockPolarity
    );
extern void USCI_A_SPI_masterChangeClock (uint32_t baseAddress,
    uint32_t clockSourceFrequency,
    uint32_t desiredSpiClock
    );

extern unsigned short USCI_A_SPI_slaveInit (uint32_t baseAddress,
    uint8_t msbFirst,
    uint8_t clockPhase,
    uint8_t clockPolarity
    );
extern void USCI_A_SPI_changeClockPhasePolarity (uint32_t baseAddress,
    uint8_t clockPhase,
    uint8_t clockPolarity
    );
extern void USCI_A_SPI_transmitData ( uint32_t baseAddress,
    uint8_t transmitData
    );

extern uint8_t USCI_A_SPI_receiveData (uint32_t baseAddress);
extern void USCI_A_SPI_enableInterrupt (uint32_t baseAddress,
    uint8_t mask
    );
extern void USCI_A_SPI_disableInterrupt (uint32_t baseAddress,
    uint8_t mask
    );
extern uint8_t USCI_A_SPI_getInterruptStatus (uint32_t baseAddress,
    uint8_t mask
    );
extern void USCI_A_SPI_enable (uint32_t baseAddress);
extern void USCI_A_SPI_disable (uint32_t baseAddress);
extern uint32_t USCI_A_SPI_getReceiveBufferAddressForDMA
    (uint32_t baseAddress);
extern uint32_t USCI_A_SPI_getTransmitBufferAddressForDMA
    (uint32_t baseAddress);
extern uint8_t USCI_A_SPI_isBusy (uint32_t baseAddress);
extern void USCI_A_SPI_clearInterruptFlag (uint32_t baseAddress,
    uint8_t mask
    );
#endif

