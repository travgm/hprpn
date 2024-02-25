/* hpstack.c - HP Style RPN Math Interperter
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

#define EMPTY_REG 0.00000000

/*
 * ERROR CHECKING NOTE:
 * When calling void functions the state does not change unless there is NO errors.
 * After calling a void function check state->error for the value being 1 and handle
 * accordingly.
*/
void stack_init(rpn_state *state) {
    state->error = 0;
    if (state == NULL) {
        state->error = 1;
    } else {
        state->stack_pointer = 0;
        reset_stack(state);
        state->result = EMPTY_REG;
        state->is_operator = 0;
        state->is_number = 0;
        state->is_command = 0;
        state->error = 0;
        state->prev_result = EMPTY_REG;
    } 
}

void reset_stack(rpn_state *state) {
    state->error = 0;
    if (state == NULL) {
        state->error = 1;
    } else {
        double x = get_reg_value(state, reg_x);
        if (x != EMPTY_REG) {
            state->prev_result = x;
            /* Since we are clearing the stack and setting a value in X if it had a value
             * we need to manually update the stack pointer to point to Y. */
            state->stack_pointer = reg_y;
        } else {
            state->stack_pointer = reg_x;
        }
        for(int i = 0; i <= 4; i++)
            state->stack[i] = EMPTY_REG;
    }
}

void move_stack_up(rpn_state *state) {
    state->error = 0;
    if (state == NULL) {
        state->error = 1;
    } else {
        state->stack[reg_t] = state->stack[reg_z];
        state->stack[reg_z] = state->stack[reg_y];
        state->stack[reg_y] = state->stack[reg_x];
    }
}

void move_stack_down(rpn_state *state) {
    state->error = 0;
    if (state == NULL) {
	state->error = 1;
    } else {
        state->stack[reg_y] = state->stack[reg_z];
        state->stack[reg_z] = state->stack[reg_t];
        state->stack[reg_t] = EMPTY_REG;
        /* We performed some operation on the stack so we need to deincrement
         * the stack pointer since it removed an item from the stack */
        state->stack_pointer -= 1;
    }
}

void set_reg_value(rpn_state *state, int reg, double val) {
    state->error = 0;
    if (state == NULL) {
        state->error = 1;
    } else {
        if (reg <= 3 && reg >= 0) {
            /* Anytime reg_x is updated we save the result to the prev_result variable in state
             * allowing us to undo the change using 'la' command */
            if (reg == reg_x) {
                state->prev_result = get_reg_value(state, reg_x);
            }
            state->stack[reg] = val;
        } else {
            state->error = 1;
        }
    }
}

double get_reg_value(rpn_state *state, int reg) {
    state->error = 0;
    if (state == NULL) {
	state->error = 1;
	return EMPTY_REG;
    }
    if (reg > 3 || reg < 0) {
        state->error = 1;
        return EMPTY_REG;
    }
 
    return state->stack[reg];
}

void swap_reg_values(rpn_state *state, int reg_1, int reg_2) {
    state->error = 0;
    if (state == NULL) {
        state->error = 1;
    } else {
        if ((reg_1 <= 3 && reg_1 >= 0) && (reg_2 <= 3 && reg_2 >= 0)) {
            double t = state->stack[reg_1];
            state->stack[reg_1] = state->stack[reg_2];
            state->stack[reg_2] = t;
        } else {
            state->error = 1;
        }
    }
}

void set_curr_stack_reg(rpn_state *state, double n) {
    state->error = 0;
    if (state == NULL) {
        state->error = 1;
    } else {
        state->stack[state->stack_pointer++] = n;
        if (state->stack_pointer > 3)
            state->stack_pointer = 0;
    }
}

void display_register_x(rpn_state *state) {
    double x = get_reg_value(state, reg_x);
    if (x < 0) {
      colors_yellow();
    } else {
      colors_cyan();
    }
    printf("X = %4.8f\n", get_reg_value(state, reg_x));
    colors_reset();
}

void print_stack(rpn_state *state) {
    double y = get_reg_value(state, reg_y);
    double z = get_reg_value(state, reg_z);
    double t = get_reg_value(state, reg_t);
    display_register_x(state);

    if (y < 0) {
        colors_yellow();
    } 
    printf("Y = %4.8f\n", y);
    colors_reset();

    if (z < 0) {
        colors_yellow();
    } 
    printf("Z = %4.8f\n", z);
    colors_reset();

    if (t < 0) {
        colors_yellow();
    }
    printf("T = %4.8f\n", t);
    colors_reset();
}
