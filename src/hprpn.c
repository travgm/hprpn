/* hprpn.c - HP Style RPN Math Interperter
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
#include <string.h>
#include <ctype.h>

#include "includes/hprpn.h"

void help_menu(void) {
    printf("hprpn implements the HP Technology using 4 working registers X, Y, Z, T\n");
    printf("to express mathematical equations. RPN is entered with the numbers\n");
    printf("first being added to the registers and then the operation you would like\n");
    printf("to perform. Example:\n\n");
    printf("      2 [ENTER] 3 [ENTER] + [ENTER]\n\n");
    printf("result would show 'X = 5.0000000'\n");
    printf("hprpn also handles negative numbers as well by writing them with a\n");
    printf("subtraction sign first. To enter a negative 5 we would do '-5'\n\n");
    printf("MATH operators:\n");
    printf("+     addition\n");
    printf("-     subtraction\n");
    printf("*     multiplication\n");
    printf("/     division\n");
    printf("^     raise X to the power of Y\n");
    printf("MATH functions:\n");
    printf("pi    puts the number PI in the X register\n");
    printf("rd    round the number in the X register down\n");
    printf("ru    round the number in the X register up\n");
    printf("ab    replaces the X register with it's absolute value\n");
    printf("REPL command:\n");
    printf("st    print the stack registers X, Y, Z, T\n");
    printf("cl    clear stack registers X, Y, Z, T\n");
    printf("hm    show this help menu\n");
    printf("sw    swap X and Y registers\n");
    printf("la    last, puts the previous result back in the X register\n");
    printf("qt    quit\n");
    printf("\nAny bugs or improvements please send an e-mail to travis@travgm.org\n");
}

void show_title(void) {
    printf("hprpn (HP Style RPN Math Interperter) version 1.1.0\n");
    printf("type 'hm' to see the help menu\n");
}

void hpprint(int error, char *err) {
      switch(error) {
          case no_error:
              printf("%s", err);
              break;
          case general_error:
              colors_red();
              printf("%s", err);
              colors_reset();
              break;
          default:
              printf("%s", err);
      }
}

int main(int argc, char *argv[]) {
    if (argc == 2 && ((strncmp(argv[1], "--help", 6) == 0) || (strncmp(argv[1], "-h", 2) == 0))) {
        help_menu();
        return 0;
    }
    rpn_state *state = malloc(sizeof(rpn_state));;
    if (state == NULL) {
        printf("fatal error: unable to initialize program state\n");
        return -1;
    }

    stack_init(state);
    show_title();

    while(1) {
        printf(": ");
        fgets(state->cmd, sizeof(state->cmd), stdin);
        if(strlen(state->cmd) <= 0)
            continue;

        state->cmd[strlen(state->cmd)-1] = '\0';
        state->is_number = verify_is_number(state->cmd);

        /* Commands are exactly 2 characters long */
	if ((state->is_number == 0 && strlen(state->cmd) == 2)) {
            state->is_command = verify_commands(state);
            if (state->is_command == 0) {
                colors_red();
                hpprint(general_error, "invalid command\n");
                colors_reset();
            }
            continue;
        }

        /* Number was entered update stack pointer and add number to the stack
         * We loop back around if user uses up all 4 registers
         */
        if(state->is_number) {
            double n = atof(state->cmd);
            set_curr_stack_reg(state, n);
	    continue;
        }

        if(strlen(state->cmd) == 1 && verify_operator(state->cmd[0])) {
            state->is_operator = 0;
	        switch(state->cmd[0]) {
	            case '+':
	                state->result = (double)(get_reg_value(state, reg_x) + 
                                                 get_reg_value(state, reg_y));
	                move_stack_down(state);
                        if (!state->error) 
	                    set_reg_value(state, reg_x, state->result);
	                break;
	            case '-':
	                state->result = (double)(get_reg_value(state, reg_x) - 
                                                 get_reg_value(state, reg_y));
	                move_stack_down(state);
                        if (!state->error)
	                    set_reg_value(state, reg_x, state->result);
	                break;
	            case '*':
	                state->result = (double)(get_reg_value(state, reg_x) *
                                                 get_reg_value(state, reg_y));
	                move_stack_down(state);
                        if (!state->error)
	                    set_reg_value(state, reg_x, state->result);
	                break;
	            case '/':
                        if (get_reg_value(state, reg_x) == 0 || 
                            get_reg_value(state, reg_y) == 0) {
                            hpprint(general_error, "invalid divident and quotient\n");
                            continue;
                        } else {
	                    state->result = (double)(get_reg_value(state, reg_x) / 
                                                     get_reg_value(state, reg_y));
	                    move_stack_down(state);
                            if (!state->error)
	                        set_reg_value(state, reg_x, state->result);
                        } 
	                break;
                    case '^':
                        state->result = (double)pow(get_reg_value(state, reg_x), 
                                                    get_reg_value(state, reg_y));
                        move_stack_down(state);
                        if (!state->error)
                            set_reg_value(state, reg_x, state->result);
                        break;
	            default:
                        hpprint(general_error, "error\n");
	                break;
	        }
                state->prev_result = state->result;
	        display_register_x(state);
                continue;
        } else {
            hpprint(1, "unknown command\n");
        }
   }
   free(state);
   return 0;
}
