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
#ifndef __MSP430WARE_FLASH_H__
#define __MSP430WARE_FLASH_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_FLASH__

#include "inc/hw_regaccess.h"


//*****************************************************************************
//
//The following are values that can be passed to the FLASH_status()
//API as the mask parameter.
//
//*****************************************************************************
#define FLASH_READY_FOR_NEXT_WRITE              WAIT_L
#define FLASH_ACCESS_VIOLATION_INTERRUPT_FLAG   ACCVIFG_L
#define FLASH_PASSWORD_WRITTEN_INCORRECTLY      KEYV_L
#define FLASH_BUSY                              BUSY_L

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************
extern void FLASH_segmentErase (uint32_t baseAddress,
    uint8_t *flash_ptr);

extern void FLASH_bankErase (uint32_t baseAddress, 
                             uint8_t *flash_ptr);

extern unsigned short FLASH_eraseCheck (uint32_t baseAddress,
    uint8_t *flash_ptr,
    uint16_t numberOfBytes
    );
extern void FLASH_write8 (uint32_t baseAddress,
    uint8_t *Data_ptr,
    uint8_t *flash_ptr,
    uint16_t numberOfBytes
    );
extern void FLASH_write16 (uint32_t baseAddress,
    uint16_t *Data_ptr,
    uint16_t *flash_ptr,
    uint16_t numberOfBytes
    );
extern void FLASH_write32 (uint32_t baseAddress,
    uint32_t *Data_ptr,
    uint32_t *flash_ptr,
    uint16_t numberOfBytes
    );
extern void FLASH_memoryFill32 (uint32_t baseAddress,
    uint32_t value,
    uint32_t *flash_ptr,
    uint16_t count
    );
extern uint8_t FLASH_status (uint32_t baseAddress,
    uint8_t mask
    );
#endif
