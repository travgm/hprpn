/* hprpn.h - HP Style RPN Math Interperter
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
#ifndef HPRPN_H_
#define HPRPN_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* These should NOT be changed as the HP calculators only had 4 working registers
 * stack (memory) should be added beyond that when user enters values beyond T
*/
enum {
  reg_x,
  reg_y,
  reg_z,
  reg_t
};

enum {
    round_up,
    round_down,
};

enum {
  no_error,
  general_error
};

/* Holds the state of the entire program */
typedef struct {
    int stack_pointer;
    double stack[4];
    char cmd[25];
    double result;
    double prev_result;
    int is_operator;
    int is_number;
    int is_command;
    int error;
} rpn_state;

void help_menu(void);

void show_title(void);

/* Stack prototypes, these are defined in stack.c */
void stack_init(rpn_state *state);

void reset_stack(rpn_state *state);

void move_stack_up(rpn_state *state);

void move_stack_down(rpn_state *state);

void print_stack(rpn_state *state);

void set_reg_value(rpn_state *state, int reg, double val);

double get_reg_value(rpn_state *stack, int reg);

void swap_reg_values(rpn_state *stack, int reg_1, int reg_2);

void display_register_x(rpn_state *state);

/* This functions sets whatever register the current stack pointer is pointer to */
void set_curr_stack_reg(rpn_state *state, double n);

/* Mostly helper or verification functions that are in hprpn.c */
int verify_operator(char o);

int verify_is_number(char n[]);

int verify_commands(rpn_state *state);

/* Basic arithmetic is handled in main in hprpn.c, these are math functions
 * that are handled in math.c but are called from command parsing in hprpn.c */
double hp_sqroot(double n);

/* Use the enum defined in this file to send round_up/round_down for direction
 * parameter */
double hp_round(double n, int direction);

double hp_pi(void);

double hp_absolute(double n);

/* Color definitions */
void colors_cyan();

void colors_red();

void colors_yellow();

void colors_reset();

#endif
