/* hpcommands.c - HP Style RPN Math Interperter
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
#include <string.h>
#include <ctype.h>

int verify_commands(rpn_state *state) {
    if (state == NULL) {
        return 0;
    }
    int valid_cmd = 0;

    /* Add stack commands to this section. Until a better solution is organized
     * organize the section by command type */
    if(strncmp(state->cmd, "st", 2) == 0) {
        valid_cmd = 1;
        print_stack(state);
    }
    if(strncmp(state->cmd, "cl", 2) == 0) {
        valid_cmd = 1;
        reset_stack(state);
    }
    if(strncmp(state->cmd, "sw", 2) == 0) {
        valid_cmd = 1;
        swap_reg_values(state, reg_x, reg_y);
    }
    if(strncmp(state->cmd, "la", 2) == 0) {
        valid_cmd = 1;
        set_reg_value(state, reg_x, state->prev_result);
        display_register_x(state);
    }

    /* Math related commands that operate on the stack registers */
    if(strncmp(state->cmd, "pi", 2) == 0) {
        valid_cmd = 1;
	move_stack_up(state);
        set_reg_value(state, reg_x, hp_pi());
        display_register_x(state);
    }
    if(strncmp(state->cmd, "rd", 2) == 0) {
        valid_cmd = 1;
        set_reg_value(state, reg_x, hp_round(get_reg_value(state, reg_x), round_down));
        display_register_x(state);
    }
    if(strncmp(state->cmd, "ru", 2) == 0) {
        valid_cmd = 1;
        set_reg_value(state, reg_x, hp_round(get_reg_value(state, reg_x), round_up));
        display_register_x(state);
    }
    if(strncmp(state->cmd, "ab", 2) == 0) {
        valid_cmd = 1;
        set_reg_value(state, reg_x, hp_absolute(get_reg_value(state, reg_x)));
        display_register_x(state);
    }

    /* Editor commands, help menu, quitting, etc... */
    if(strncmp(state->cmd, "hm", 2) == 0) {
        valid_cmd = 1;
        help_menu();
    }
    if(strncmp(state->cmd, "qt", 2) == 0) {
        free(state);
        exit(0);
    }
    return valid_cmd;
}

/*
 * Verifications for the REPL in main. These need to be refactored
 */
int verify_operator(char o) {
    if ((int)o == 0)
        return 0;
    return (o == '+' || o == '-' ||
            o == '*' || o == '/' ||
            o == '^');
}

int verify_is_number(char n[]) {
    if (strlen(n) == 0)
        return 0;
    for (int i = 0; i < (int)strlen(n); i++) {
        /* Handle negative numbers and it must be first index */
        if (n[i] == '-' && i == 0 && strlen(n) > 1)
                continue;
        if (!isdigit(n[i]) && n[i] != '.') {
            return 0;
        }
    }
    return 1;
}

