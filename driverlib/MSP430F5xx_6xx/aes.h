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
#ifndef __MSP430WARE_AES_H__
#define __MSP430WARE_AES_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_AES__

#include "inc/hw_regaccess.h"

//*****************************************************************************
//
//The following value can be passed to AES_clearInterruptFlag(), AES_enableInterrupt(),
// AES_disableInterrupt()
//
//*****************************************************************************
#define AES_READY_INTERRUPT AESRDYIE

//*****************************************************************************
//
//The following value can be returned by AES_getErrorFlagStatus
//
//*****************************************************************************
#define AES_ERROR_OCCURRED	AESERRFG
#define AES_NO_ERROR		0x00

//*****************************************************************************
//
//The following value can be passed to AES_enableInterrupt()
//
//*****************************************************************************
#define		AES_getEncryptedData	AES_getDataOut
#define		AES_getDecryptedData	AES_getDataOut


//*****************************************************************************
//
//The following value is returned by the AES_isBusy() API
//
//*****************************************************************************
#define AES_BUSY		AESBUSY
#define AES_NOT_BUSY	0x00

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************
uint8_t AES_setCipherKey (uint32_t baseAddress,
	 const uint8_t * CipherKey
	 );
uint8_t AES_encryptData (uint32_t baseAddress,
	const uint8_t * Data, 
	uint8_t * encryptedData);
uint8_t AES_decryptDataUsingEncryptionKey (uint32_t baseAddress,
	const uint8_t * Data, 
	uint8_t * decryptedData);
uint8_t AES_decryptData (uint32_t baseAddress,
	const uint8_t * Data, 
	uint8_t * decryptedData);
uint8_t AES_generateFirstRoundKey (uint32_t baseAddress,
	const uint8_t * CipherKey);
void AES_clearInterruptFlag (uint32_t baseAddress );
uint32_t AES_getInterruptFlagStatus (uint32_t baseAddress);
void AES_enableInterrupt (uint32_t baseAddress);
void AES_disableInterrupt (uint32_t baseAddress);
void AES_reset (uint32_t baseAddress);
uint8_t AES_startEncryptData (uint32_t baseAddress,
	const uint8_t * Data, 
	uint8_t * encryptedData);
uint8_t AES_startDecryptDataUsingEncryptionKey (
	uint32_t baseAddress, 
	const uint8_t * Data);
uint8_t AES_startDecryptData (uint32_t baseAddress,
	const uint8_t * Data);
uint8_t AES_startGenerateFirstRoundKey (uint32_t baseAddress,
	const uint8_t * CipherKey);
uint8_t  AES_getDataOut(uint32_t baseAddress,
							uint8_t *OutputData
							);
uint8_t AES_isBusy (uint32_t baseAddress);
void AES_clearErrorFlag (uint32_t baseAddress );
uint32_t AES_getErrorFlagStatus (uint32_t baseAddress);
#endif

