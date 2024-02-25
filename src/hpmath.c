/* hpmath.c - HP Style RPN Math Interperter
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

#define PI 3.14159265

double hp_pi(void) {
    return PI;
}

double hp_sqroot(double n) {
    return sqrt(n);
}

double hp_absolute(double n) {
	return fabs(n);
}

double hp_round(double n, int direction) {
    double r;
    if (direction == 0) 
        r = ceil(n);
    else if (direction == 1) 
        r = floor(n);

    return r;
}
