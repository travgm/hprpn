/* colors.c - HP Style RPN Math Interperter
 * Copyright (C) 2023 Travis Montoya <travis@travgm.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "includes/hprpn.h"

void colors_cyan() {
    printf("\033[1;36m");
}

void colors_red() {
    printf("\033[0;31m");
}

void colors_yellow() {
    printf("\033[1;33m");
}

void colors_reset() {
    printf("\033[0m");
}
