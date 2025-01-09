// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2023-2024 Thomas Basler and others
 */
#include "HMT_6CH.h"

static const byteAssign_t byteAssignment[] = {
    { TYPE_DC, CH0, FLD_UDC, UNIT_V, 2, 2, 10, false,true, 1 },
    { TYPE_DC, CH0, FLD_IDC, UNIT_A, 4, 2, 100, false,true,2 },
    { TYPE_DC, CH0, FLD_PDC, UNIT_W, 8, 2, 10, false,true, 1 },
    { TYPE_DC, CH0, FLD_YT, UNIT_KWH, 12, 4, 1000, false, 3 },
    { TYPE_DC, CH0, FLD_YD, UNIT_WH, 20, 2, 1, false,true, 0 },
    { TYPE_DC, CH0, FLD_IRR, UNIT_PCT, CALC_CH_IRR, CH0, CMD_CALC, false,true, 3 },

    { TYPE_DC, CH1, FLD_UDC, UNIT_V, 2, 2, 10, false,true, 1 },
    { TYPE_DC, CH1, FLD_IDC, UNIT_A, 6, 2, 100, false,true, 2 },
    { TYPE_DC, CH1, FLD_PDC, UNIT_W, 10, 2, 10, false,true, 1 },
    { TYPE_DC, CH1, FLD_YT, UNIT_KWH, 16, 4, 1000, false, true,3 },
    { TYPE_DC, CH1, FLD_YD, UNIT_WH, 22, 2, 1, false,true, 0 },
    { TYPE_DC, CH1, FLD_IRR, UNIT_PCT, CALC_CH_IRR, CH1, CMD_CALC, false,true, 3 },

    { TYPE_DC, CH2, FLD_UDC, UNIT_V, 24, 2, 10, false,true, 1 },
    { TYPE_DC, CH2, FLD_IDC, UNIT_A, 26, 2, 100, false,true, 2 },
    { TYPE_DC, CH2, FLD_PDC, UNIT_W, 30, 2, 10, false,true, 1 },
    { TYPE_DC, CH2, FLD_YT, UNIT_KWH, 34, 4, 1000, false, true,3 },
    { TYPE_DC, CH2, FLD_YD, UNIT_WH, 42, 2, 1, false,true, 0 },
    { TYPE_DC, CH2, FLD_IRR, UNIT_PCT, CALC_CH_IRR, CH2, CMD_CALC, false,true, 3 },

    { TYPE_DC, CH3, FLD_UDC, UNIT_V, 24, 2, 10, false,true, 1 },
    { TYPE_DC, CH3, FLD_IDC, UNIT_A, 28, 2, 100, false,true, 2 },
    { TYPE_DC, CH3, FLD_PDC, UNIT_W, 32, 2, 10, false,true, 1 },
    { TYPE_DC, CH3, FLD_YT, UNIT_KWH, 38, 4, 1000, false,true, 3 },
    { TYPE_DC, CH3, FLD_YD, UNIT_WH, 44, 2, 1, false, true,0 },
    { TYPE_DC, CH3, FLD_IRR, UNIT_PCT, CALC_CH_IRR, CH3, CMD_CALC, false,true, 3 },

    { TYPE_DC, CH4, FLD_UDC, UNIT_V, 46, 2, 10, false,true, 1 },
    { TYPE_DC, CH4, FLD_IDC, UNIT_A, 48, 2, 100, false,true, 2 },
    { TYPE_DC, CH4, FLD_PDC, UNIT_W, 52, 2, 10, false,true, 1 },
    { TYPE_DC, CH4, FLD_YT, UNIT_KWH, 56, 4, 1000, false,true, 3 },
    { TYPE_DC, CH4, FLD_YD, UNIT_WH, 64, 2, 1, false,true, 0 },
    { TYPE_DC, CH4, FLD_IRR, UNIT_PCT, CALC_CH_IRR, CH4, CMD_CALC, false,true, 3 },

    { TYPE_DC, CH5, FLD_UDC, UNIT_V, 46, 2, 10, false,true, 1 },
    { TYPE_DC, CH5, FLD_IDC, UNIT_A, 50, 2, 100, false,true, 2 },
    { TYPE_DC, CH5, FLD_PDC, UNIT_W, 54, 2, 10, false,true, 1 },
    { TYPE_DC, CH5, FLD_YT, UNIT_KWH, 60, 4, 1000, false, true,3 },
    { TYPE_DC, CH5, FLD_YD, UNIT_WH, 66, 2, 1, false,true, 0 },
    { TYPE_DC, CH5, FLD_IRR, UNIT_PCT, CALC_CH_IRR, CH5, CMD_CALC, false,true, 3 },

    { TYPE_AC, CH0, FLD_UAC, UNIT_V, 74, 2, 10, false,true, 1 }, // dummy
    { TYPE_AC, CH0, FLD_UAC_1N, UNIT_V, 68, 2, 10, false,true, 1 },
    { TYPE_AC, CH0, FLD_UAC_2N, UNIT_V, 70, 2, 10, false,true, 1 },
    { TYPE_AC, CH0, FLD_UAC_3N, UNIT_V, 72, 2, 10, false,true, 1 },
    { TYPE_AC, CH0, FLD_UAC_12, UNIT_V, 74, 2, 10, false,true, 1 },
    { TYPE_AC, CH0, FLD_UAC_23, UNIT_V, 76, 2, 10, false,true, 1 },
    { TYPE_AC, CH0, FLD_UAC_31, UNIT_V, 78, 2, 10, false,true, 1 },
    { TYPE_AC, CH0, FLD_F, UNIT_HZ, 80, 2, 100, false, true,2 },
    { TYPE_AC, CH0, FLD_PAC, UNIT_W, 82, 2, 10, false,true, 1 },
    { TYPE_AC, CH0, FLD_Q, UNIT_VAR, 84, 2, 10, true,true, 1 },
    { TYPE_AC, CH0, FLD_IAC, UNIT_A, CALC_TOTAL_IAC, 0, CMD_CALC, false,true, 2 },
    { TYPE_AC, CH0, FLD_IAC_1, UNIT_A, 86, 2, 100, false,true, 2 },
    { TYPE_AC, CH0, FLD_IAC_2, UNIT_A, 88, 2, 100, false,true, 2 },
    { TYPE_AC, CH0, FLD_IAC_3, UNIT_A, 90, 2, 100, false,true, 2 },
    { TYPE_AC, CH0, FLD_PF, UNIT_NONE, 92, 2, 1000, false,true, 3 },

    { TYPE_INV, CH0, FLD_T, UNIT_C, 94, 2, 10, true,true, 1 },
    { TYPE_INV, CH0, FLD_EVT_LOG, UNIT_NONE, 96, 2, 1, false,true, 0 },

    { TYPE_INV, CH0, FLD_YD, UNIT_WH, CALC_TOTAL_YD, 0, CMD_CALC, false,true, 0 },
    { TYPE_INV, CH0, FLD_YT, UNIT_KWH, CALC_TOTAL_YT, 0, CMD_CALC, false,true, 3 },
    { TYPE_INV, CH0, FLD_PDC, UNIT_W, CALC_TOTAL_PDC, 0, CMD_CALC, false,true, 1 },
    { TYPE_INV, CH0, FLD_EFF, UNIT_PCT, CALC_TOTAL_EFF, 0, CMD_CALC, false,true, 3 }
};

HMT_6CH::HMT_6CH(HoymilesRadio* radio, const uint64_t serial)
    : HMT_Abstract(radio, serial) {};

bool HMT_6CH::isValidSerial(const uint64_t serial)
{
    // serial >= 0x138200000000 && serial <= 0x1382ffffffff
    uint16_t preSerial = (serial >> 32) & 0xffff;
    return preSerial == 0x1382;
}

String HMT_6CH::typeName() const
{
    return "HMT-1800/2250-6T";
}

const byteAssign_t* HMT_6CH::getByteAssignment() const
{
    return byteAssignment;
}

uint8_t HMT_6CH::getByteAssignmentSize() const
{
    return sizeof(byteAssignment) / sizeof(byteAssignment[0]);
}
