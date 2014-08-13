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
//flash.c - Driver for the FLASH Module.
//
//*****************************************************************************
#include "inc/hw_regaccess.h"
#include "assert.h"
#include "flash.h"
#ifdef  __IAR_SYSTEMS_ICC__
#include "deprecated/IAR/msp430xgeneric.h"
#else
#include "deprecated/CCS/msp430xgeneric.h"
#endif

//*****************************************************************************
//
//! Erase a single segment of the flash memory.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param flash_ptr is the pointer into the flash segment to be erased
//!
//! \returns NONE
//
//*****************************************************************************
void FLASH_segmentErase (uint32_t baseAddress, uint8_t *flash_ptr)
{
    //5xx Workaround: Disable global interrupt while erasing.
    //local variable to store GIE status
    uint16_t gieStatus;

    //Store current SR register
    gieStatus = __get_SR_register() & GIE;
    //Disable global interrupt
    __disable_interrupt();

    //Clear Lock bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY;

    //Set Erase bit
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY + ERASE;

    //Dummy write to erase Flash seg
    *flash_ptr = 0;

    //test busy
    while (HWREG8(baseAddress + OFS_FCTL3) & BUSY) ;

    //Clear WRT bit
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY + LOCK;

    //Reinstate SR register
    __bis_SR_register(gieStatus);
}

//*****************************************************************************
//
//! Erase a single bank of the flash memory.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param flash_ptr is a pointer into the bank to be erased
//!
//! \returns NONE
//
//*****************************************************************************
void FLASH_bankErase (uint32_t baseAddress, uint8_t *flash_ptr)
{
    //5xx Workaround: Disable global interrupt while erasing.
    //local variable to store GIE status
    uint16_t gieStatus;

    //Store current SR register
    gieStatus = __get_SR_register() & GIE;
    //Disable global interrupt
    __disable_interrupt();
  
    //Clear Lock bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY;
    
    while (HWREG8(baseAddress + OFS_FCTL3) & BUSY) ;

    //Set MERAS bit
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY + MERAS;

    //Dummy write to erase Flash seg
    *flash_ptr = 0;

    //test busy
    while (HWREG8(baseAddress + OFS_FCTL3) & BUSY) ;

    //Clear WRT bit
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY + LOCK;

    //Reinstate SR register
    __bis_SR_register(gieStatus);
}

//*****************************************************************************
//
//! Erase check of the flash memory
//!
//! \param baseAddress is the base address of the Flash module.
//! \param flash_ptr is the Pointer to the starting location of the erase check
//! \param numberOfBytes is the number of bytes to be checked
//!
//! \returns STATUS_SUCCESS or STATUS_FAIL
//
//*****************************************************************************
unsigned short FLASH_eraseCheck (uint32_t baseAddress,
    uint8_t *flash_ptr,
    uint16_t numberOfBytes
    )
{
    uint16_t i;

    for (i = 0; i < numberOfBytes; i++)
    {
        //was erasing successfull?
        if ((*(flash_ptr + i)) != 0xFF){
            return ( STATUS_FAIL) ;
        }
    }
    return ( STATUS_SUCCESS) ;
}

//*****************************************************************************
//
//! Write data into the flash memory in byte format. 
//! Assumes the flash memory is already erased. FLASH_segmentErase can be used
//! to erase a segment.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Data_ptr is the pointer to the data to be written
//! \param flash_ptr is the pointer into which to write the data
//! \param numberOfBytes is the number of bytes to be written
//!
//! \returns NONE
//
//*****************************************************************************
void FLASH_write8 (uint32_t baseAddress,
    uint8_t *Data_ptr,
    uint8_t *flash_ptr,
    uint16_t numberOfBytes
    )
{
    //Clear Lock bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY;

    //Enable byte/word write mode
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY + WRT;

    while (numberOfBytes > 0)
    {
        //test busy
        while (HWREG8(baseAddress + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = *Data_ptr++;
        numberOfBytes--;
    }

    //Clear write bit
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY + LOCK;
}

//*****************************************************************************
//
//! Write data into the flash memory in word format.
//! Assumes the flash memory is already erased. FLASH_segmentErase can be used
//! to erase a segment.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Data_ptr is the pointer to the data to be written
//! \param flash_ptr is the pointer into which to write the data
//! \param numberOfBytes is the number of bytes to be written
//!
//! \returns NONE
//
//*****************************************************************************
void FLASH_write16 (uint32_t baseAddress,
    uint16_t *Data_ptr,
    uint16_t *flash_ptr,
    uint16_t numberOfBytes
    )
{
    //Clear Lock bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY;

    //Enable byte/word write mode
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY + WRT;

    while (numberOfBytes > 0)
    {
        //test busy
        while (HWREG8(baseAddress + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = *Data_ptr++;
        numberOfBytes--;
    }

    //Clear Erase bit
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY + LOCK;
}

//*****************************************************************************
//
//! Write data into the flash memory in long format, pass by reference
//! Assumes the flash memory is already erased. FLASH_segmentErase can be used
//! to erase a segment.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Data_ptr is the pointer to the data to be written
//! \param flash_ptr is the pointer into which to write the data
//! \param numberOfBytes is the number of bytes to be written
//!
//! \returns NONE
//
//*****************************************************************************
void FLASH_write32 (uint32_t baseAddress,
    uint32_t *Data_ptr,
    uint32_t *flash_ptr,
    uint16_t numberOfBytes
    )
{
    //Clear Lock bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY;

    //Enable long-word write
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY + BLKWRT;

    while (numberOfBytes > 0)
    {
        //test busy
        while (HWREG8(baseAddress + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = *Data_ptr++;
        numberOfBytes--;
    }

    //Clear Erase bit
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY + LOCK;
}

//*****************************************************************************
//
//! Write data into the flash memory in long format, pass by value
//! Assumes the flash memory is already erased. FLASH_segmentErase can be used
//! to erase a segment.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Data_ptr is the pointer to the data to be written
//! \param flash_ptr is the pointer into which to write the data
//! \param numberOfBytes is the number of bytes to be written
//!
//! \returns NONE
//
//*****************************************************************************
void FLASH_memoryFill32 (uint32_t baseAddress,
    uint32_t value,
    uint32_t *flash_ptr,
    uint16_t count
    )
{
    //Clear Lock bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY;

    //Enable long-word write
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY + BLKWRT;

    //test busy
    while (count > 0)
    {
        while ((HWREG8(baseAddress + OFS_FCTL3)) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = value;
        count--;
    }

    //Clear Erase bit
    HWREG16(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(baseAddress + OFS_FCTL3) = FWKEY + LOCK;
}

//*****************************************************************************
//
//! Check if Flash status to see if it is currently busy erasing or programming
//!
//! \param baseAddress is the base address of the Flash module.
//! \param mask is the logical OR of the status mask requested
//!            (FLASH_READY_FOR_NEXT_WRITE)
//!            (FLASH_ACCESS_VIOLATION_INTERRUPT_FLAG)
//!            (FLASH_PASSWORD_WRITTEN_INCORRECTLY)
//!            (FLASH_BUSY)
//! \returns logical OR of FLASH_READY_FOR_NEXT_WRITE/
//!          FLASH_ACCESS_VIOLATION_INTERRUPT_FLAG/
//!          FLASH_PASSWORD_WRITTEN_INCORRECTLY/FLASH_BUSY/0x00
//!
//*****************************************************************************
uint8_t FLASH_status (uint32_t baseAddress,
    uint8_t mask
    )
{
    return ((HWREG8(baseAddress + OFS_FCTL3) & mask ));
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
