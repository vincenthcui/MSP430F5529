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
#ifndef __MSP430WARE_BAK_BATT_H__
#define __MSP430WARE_BAK_BATT_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_BATTERY_CHARGER__
#define __MSP430_HAS_BACKUP_RAM__

#include "inc/hw_regaccess.h"

//*****************************************************************************
//
//The following are values that can be returned by BAK_BATT_unlockBackupSubSystem().
//
//*****************************************************************************
#define BAK_BATT_UNLOCKFAILURE (0x0)
#define BAK_BATT_UNLOCKSUCCESS (0x1)

//*****************************************************************************
//
//The following are values that can be passed to BAK_BATT_chargerInitAndEnable()
//in the chargerEndVoltage parameter.
//
//*****************************************************************************
#define BAK_BATT_CHARGERENDVOLTAGE_VCC (BAKCHV0)
#define BAK_BATT_CHARGERENDVOLTAGE2_7V (BAKCHV1)

//*****************************************************************************
//
//The following are values that can be passed to BAK_BATT_chargerInitAndEnable()
//in the chargeCurrent parameter.
//
//*****************************************************************************
#define BAK_BATT_CHARGECURRENT_5KOHM  (BAKCHC0)
#define BAK_BATT_CHARGECURRENT_10KOHM (BAKCHC1)
#define BAK_BATT_CHARGECURRENT_20KOHM (BAKCHC0 + BAKCHC1)

//*****************************************************************************
//
//The following are values that can be passed to BAK_BATT_setBackupRAMData() and
//BAK_BATT_getBackupRAMData() in the backupRAMSelect parameter.
//
//*****************************************************************************
#define BAK_BATT_RAMSELECT_0 (0x0000)
#define BAK_BATT_RAMSELECT_1 (0x0002)
#define BAK_BATT_RAMSELECT_2 (0x0004)
#define BAK_BATT_RAMSELECT_3 (0x0006)

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************

extern unsigned short BAK_BATT_unlockBackupSubSystem (uint32_t baseAddress);

extern void BAK_BATT_enableBackupSupplyToADC (uint32_t baseAddress);

extern void BAK_BATT_disableBackupSupplyToADC (uint32_t baseAddress);

extern void BAK_BATT_manuallySwitchToBackupSupply (uint32_t baseAddress);

extern void BAK_BATT_disable (uint32_t baseAddress);

extern void BAK_BATT_chargerInitAndEnable (uint32_t baseAddress,
    uint8_t chargerEndVoltage,
    uint8_t chargeCurrent);

extern void BAK_BATT_disableCharger (uint32_t baseAddress);

extern void BAK_BATT_setBackupRAMData (uint32_t baseAddress,
    uint8_t backupRAMSelect,
    uint16_t data);

extern uint16_t BAK_BATT_getBackupRAMData (uint32_t baseAddress,
    uint8_t backupRAMSelect);


#endif
