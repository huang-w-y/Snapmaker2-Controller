/*
 * Snapmaker2-Controller Firmware
 * Copyright (C) 2019-2020 Snapmaker [https://github.com/Snapmaker]
 *
 * This file is part of Snapmaker2-Controller
 * (see https://github.com/Snapmaker/Snapmaker2-Controller)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "snapmaker.h"
#include "service/system.h"
#include "src/gcode/gcode.h"
#include "../module/toolhead_3dp.h"
#include "../module/toolhead_dualextruder.h"

void GcodeSuite::M4000() {
    const bool seen_t = parser.seenval('F');
    uint8_t val = 0;
    
    if (seen_t) {
        uint8_t stage = (uint8_t)parser.byteval('F', (uint8_t)0);
        switch (stage) {
            case 0: 
                val = parser.byteval('P', (uint8_t)0);
                if (ModuleBase::toolhead() == MODULE_TOOLHEAD_3DP) {
                    printer_single.ModuleCtrlProximitySwitchPower(!!val);
                }
                else if (ModuleBase::toolhead() == MODULE_TOOLHEAD_DUALEXTRUDER) {
                    printer_dualextruder.ModuleCtrlProximitySwitchPower(!!val);
                }
                break;
            
            case 1:
                if (ModuleBase::toolhead() == MODULE_TOOLHEAD_DUALEXTRUDER) {
                    printer_dualextruder.ModuleCtrlRightExtruderMove(GO_HOME);
                }
                break;
            
            default:
                break;
        }

    }
}

