/*****************************************************************************\
 **                                                                         **
 **  FILE:     control.c                                                    **
 **  AUTHORS:  Mark Howell (howell_ma@movies.enet.dec.com)                  **
 **            Alexios (porting to Megistos, adding some bells & whistles)  **
 **  PURPOSE:  Run Infocom games in a nice BBS environment.                 **
 **  NOTES:                                                                 **
 **  LEGALESE:                                                              **
 **                                                                         **
 **  ORIGINAL CONDITION OF USE:                                             **
 **                                                                         **
 **  You are expressly forbidden to use this program if in so doing you     **
 **  violate the copyright notice supplied with the original Infocom game.  **
 **                                                                         **
 **  LICENSE AGREEMENT:                                                     **
 **                                                                         **
 **  This program is free software; you  can redistribute it and/or modify  **
 **  it under the terms of the GNU  General Public License as published by  **
 **  the Free Software Foundation; either version 2 of the License, or (at  **
 **  your option) any later version.                                        **
 **                                                                         **
 **  This program is distributed  in the hope  that it will be useful, but  **
 **  WITHOUT    ANY WARRANTY;   without  even  the    implied warranty  of  **
 **  MERCHANTABILITY or  FITNESS FOR  A PARTICULAR  PURPOSE.   See the GNU  **
 **  General Public License for more details.                               **
 **                                                                         **
 **  You  should have received a copy   of the GNU  General Public License  **
 **  along with    this program;  if   not, write  to  the   Free Software  **
 **  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              **
\*****************************************************************************/

/*
 * $Id: control.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: control.c,v $
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/24 20:30:30  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/24 20:12:16  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/08/13 16:59:43  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id: control.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";

/*
 * control.c
 *
 * Functions that alter the flow of control.
 *
 */

#include <bbs.h>
#include "ztypes.h"

static const char *v1_lookup_table[3] = {
	"abcdefghijklmnopqrstuvwxyz",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
	" 0123456789.,!?_#'\"/\\<-:()"
};

static const char *v3_lookup_table[3] = {
	"abcdefghijklmnopqrstuvwxyz",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
	" \n0123456789.,!?_#'\"/\\-:()"
};

/*
 * check_argument
 *
 * Jump if argument is present.
 *
 */

void
check_argument (zword_t argc)
{
	conditional_jump (argc <= (zword_t) (stack[fp + 1] & ARGS_MASK));
}



/*
 * call
 *
 * Call a subroutine. Save PC and FP then load new PC and initialise stack based
 * local arguments.
 *
 */

int
call (int argc, zword_t * argv, int type)
{
	zword_t arg;
	int     i = 1, args, status = 0;

	/* Convert calls to 0 as returning FALSE */

	if (argv[0] == 0) {
		if (type == FUNCTION)
			store_operand (FALSE);
		return (0);
	}

	/* Save current PC, FP and argument count on stack */

	stack[--sp] = (zword_t) (pc / PAGE_SIZE);
	stack[--sp] = (zword_t) (pc % PAGE_SIZE);
	stack[--sp] = fp;
	stack[--sp] = (argc - 1) | type;

	/* Create FP for new subroutine and load new PC */

	fp = sp - 1;
	pc = (unsigned long) argv[0] * story_scaler;

	/* Read argument count and initialise local variables */

	args = (unsigned int) read_code_byte ();
	while (--args >= 0) {
		arg = (h_type > V4) ? 0 : read_code_word ();
		stack[--sp] = (--argc > 0) ? argv[i++] : arg;
	}

	/* If the call is asynchronous then call the interpreter directly.
	   We will return back here when the corresponding return frame is
	   encountered in the ret call. */

	if (type == ASYNC) {
		status = interpret ();
		interpreter_state = RUN;
		interpreter_status = 1;
	}

	return (status);

}



/*
 * ret
 *
 * Return from subroutine. Restore FP and PC from stack.
 *
 */

void
ret (zword_t value)
{
	zword_t argc;

	/* Clean stack */

	sp = fp + 1;

	/* Restore argument count, FP and PC */

	argc = stack[sp++];
	fp = stack[sp++];
	pc = stack[sp++];
	pc += (unsigned long) stack[sp++] * PAGE_SIZE;

	/* If this was an async call then stop the interpreter and return
	   the value from the async routine. This is slightly hacky using
	   a global state variable, but ret can be called with conditional_jump
	   which in turn can be called from all over the place, sigh. A
	   better design would have all opcodes returning the status RUN, but
	   this is too much work and makes the interpreter loop look ugly */

	if ((argc & TYPE_MASK) == ASYNC) {

		interpreter_state = STOP;
		interpreter_status = (int) value;

	} else {

		/* Return subroutine value for function call only */

		if ((argc & TYPE_MASK) == FUNCTION)
			store_operand (value);

	}

}



/*
 * jump
 *
 * Unconditional jump. Jump is PC relative.
 *
 */

void
jump (zword_t offset)
{
	pc = (unsigned long) (pc + (short) offset - 2);
}



/*
 * restart
 *
 * Restart game by initialising environment and reloading start PC.
 *
 */

void
restart (void)
{
	unsigned int i, j, restart_size, scripting_flag;

	/* Reset output buffer */

	flush_buffer (TRUE);

	/* Reset text control flags */

	formatting = ON;
	outputting = ON;
	redirecting = OFF;
	scripting_disable = OFF;

	/* Randomise */

	srand ((unsigned int) time (NULL));

	/* Remember scripting state */

	scripting_flag = get_word (H_FLAGS) & SCRIPTING_FLAG;

	/* Load restart size and reload writeable data area */

	restart_size = (h_restart_size / PAGE_SIZE) + 1;
	for (i = 0; i < restart_size; i++)
		read_page (i, &datap[i * PAGE_SIZE]);

	/* Restart the screen */

	set_status_size (0);
	set_attribute (NORMAL);
	erase_window (SCREEN);

	restart_screen ();

	/* Reset the interpreter state */

	if (scripting_flag)
		set_word (H_FLAGS, (get_word (H_FLAGS) | SCRIPTING_FLAG));

	set_byte (H_INTERPRETER, h_interpreter);
	set_byte (H_INTERPRETER_VERSION, h_interpreter_version);
	set_byte (H_SCREEN_ROWS, screen_rows);	/* Screen dimension in characters */
	set_byte (H_SCREEN_COLUMNS, screen_cols);

	set_byte (H_SCREEN_LEFT, 0);	/* Screen dimension in smallest addressable units, ie. pixels */
	set_byte (H_SCREEN_RIGHT, screen_cols);
	set_byte (H_SCREEN_TOP, 0);
	set_byte (H_SCREEN_BOTTOM, screen_rows);

	set_byte (H_MAX_CHAR_WIDTH, 1);	/* Size of a character in screen units */
	set_byte (H_MAX_CHAR_HEIGHT, 1);

	/* Initialise status region */

	if (h_type < V4) {
		set_status_size (0);
		blank_status_line ();
	}

	/* Initialise the character translation lookup tables */

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 26; j++) {
			if (h_alternate_alphabet_offset) {
				lookup_table[i][j] =
				    get_byte (h_alternate_alphabet_offset +
					      (i * 26) + j);
			} else {
				if (h_type == V1)
					lookup_table[i][j] =
					    v1_lookup_table[i][j];
				else
					lookup_table[i][j] =
					    v3_lookup_table[i][j];
			}
		}
	}

	/* Load start PC, SP and FP */

	pc = h_start_pc;
	sp = STACK_SIZE;
	fp = STACK_SIZE - 1;

}



/*
 * get_fp
 *
 * Return the value of the frame pointer (FP) for later use with unwind.
 * Before V5 games this was a simple pop.
 *
 */

void
get_fp (void)
{
	if (h_type > V4)
		store_operand (fp);
	else
		sp++;
}



/*
 * unwind
 *
 * Remove one or more stack frames and return. Works like longjmp, see get_fp.
 *
 */

void
unwind (zword_t value, zword_t new_fp)
{
	if (new_fp > fp)
		error_fatal ("Bad frame for unwind");

	fp = new_fp;
	ret (value);
}


/* End of File */
