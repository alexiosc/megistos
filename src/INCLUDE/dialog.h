/** @name    dialog.h
    @memo    Interactive, modal data entry tools
    @author  Alexios

    @doc

    Dialogue boxes are an interactive, model means of gathering data from a
    user. Dialogue boxes, be they full-screen or the more conventional,
    menu-driven variety, have a few advantages over serialised question-answer
    data entry: they are a more direct data entry experience for the user; they
    offer random access; higher visibility (the user always knows how much data
    there is to fill in); and much higher user friendliness.

    Very few BBS systems offer such a means. This implementation was very
    loosely based on the Major BBS version 6, with more inspiration coming from
    the (then newfangled) forms on the World Wide Web.

    Implementing a Dialogue box involves a set of steps:

    \begin{itemize}

    \item Decide what information needs to be entered. Try to minimise the
    information. Screen estate is precious at an expected 80x25 text
    mode. The more complexity on the dialogue, the less usable it is.

    \item Lay out the visual template. Try to follow the existing
    examples. It'll keep the style consistent.

    \item Lay out the non-visual template and its individual prompts. Make sure
    the prompts can also work as help tips for the visual version, because
    they'll also be used in this way.

    \end{itemize}

    To use a form, these steps must be followed:

    \begin{itemize}

    \item Create the default data file.

    \item Call the data-entry subsystem.

    \item Read back data file. Check the result code embedded in the file, and
    act accordingly. Canceling implies no changes should be kept.

    \end{itemize}

    The following documentation will hopefully give enough information
    to help you get started.

    Original banner, legalese and change history follow.

    {\footnotesize
    \begin{verbatim}

 *****************************************************************************
 **                                                                         **
 **  FILE:     dialog.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Interactive, modal data entry.                               **
 **  NOTES:                                                                 **
 **  LEGALESE:                                                              **
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
 **                                                                         **
 *****************************************************************************


 *
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 *

\end{verbatim}
} */

/*@{*/

#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#ifndef DIALOG_H
#define DIALOG_H





/** @name Template directives.
    @filename dialog_directives

    @doc Template directives are special escape sequences resembling terminal
    directives. They are, of course, not handled by any terminal in
    existence. Within the BBS, they are interpreted {\em only} where data entry
    templates are specified, i.e. only the {\tt dialog_run()} function.

    Although the same directives work on both visual dialogue boxes and
    conventional menu-driven data entry, they perform differently in either
    case. The following list will describe each behaviour.

    All directives start with the sequence `{\tt ESC @}', or ASCII codes {\tt
    27 64} (in decimal). Directives need one or more arguments, depending on
    their type. Arguments may be of two types:

    \begin{description}

    \item[{\tt int] Denotes an integer argument.

    \item[{\tt str] Denotes a string argument, enclosed in double
    quotes.

    \end{description}

    All arguments are separated with semicolons. The directive is terminated by
    a single character which identifies the type of directive. The following
    types of directives are currently available, listed here with their
    expected argument types (spaces aren't included for clarity, and are not to
    be used in the directives):

    \begin{description}

    \item[{\tt ESC int ; int ; int s}] Specifies a {\bf s}tring input
    field. The first argument is the maximum allowed length of the string. The
    second argument is the maximum length of the screen that will be {\em
    visible}, that is the physical length of the input field. The third
    argument represents a set of flags (ORred together), as follows:

    \begin{description}

    \item[0] Normal operation.

    \item[1] Characters are converted to upper case.

    \item[2] Password: asterisks are echoed.

    \item[4] Date input: formatted as a DD/MM/YY-style date.

    \end{description}

    In full-screen mode, this directive inserts an input field at the current
    position of the cursor, and the current character attributes (colour et
    cetera). The length is that of the second argument plus 2 (the field is
    space-padded on either side). Once the field is active, it interprets
    editing commands such as the arrow keys, backspace, delete, et
    cetera. Characters are inserted properly, and, if the string is longer than
    its visible part, the field scrolls to accommodate it. If the string
    extends past the left edge of the field, a less-than sign ({\tt <}) is
    displayed at the left padding space. Likewise, the right padding space will
    display a greater-than ({\tt >}) if the string extends past the right
    edge of the field.

    In menu-driven mode, this directive simply prints the string, date, or
    whatever. The string is padded to the length specified by the second
    argument, but is not space-padded (little use for the scrolling arrows
    here). If the string is longer than the length of the field, the beginning
    of the string is displayed. An ellipsis ({\tt ...}) is displayed at the
    rightmost three characters of the field to denote that the entire string
    could not fit on-screen.

    Here are a few examples:

    \begin{itemize}

    \item {\tt ESC@80;40;s} specifies a string field holding up to 80
    characters, of which up to 40 will be visible. The field occupies 42
    characters in visual mode, and 40 in text mode.

    \item {\tt ESC@40;40;1s} A non-scrolling, string field that automatically
    converts characters to upper case.

    \item {\tt ESC@8;8;2s} A non-scrolling, password entry field. Any
    characters typed will echo as asterisks.

    \end{itemize}



    \item[{\tt ESC int ; int ; int ; int n}] Specifies a {\bf n}umber input
    field. The first argument is the maximum allowed {\em length} of the
    number. The second and arguments hold the minimum and maximum values the
    number is allowed to have. Invalid values cause the number to be changed to
    the nearest valid number. The fourth argument is, as usual, a set of flags
    (ORred together), as follows:

    \begin{description}

    \item[0] Normal number.

    \item[1] Right-flush number when displaying. The default is to left-flush
    it.

    \end{description}

    In full-screen mode, this directive works just like a string field (see the
    above documentation for details), but it automatically validates its
    input. Only digits may be typed inside a field (other characters are
    ignored). Leaving the field with a number off-limits will cause the number
    to change to the nearest valid integer.

    In menu-driven mode, this directive behaves exactly like a string
    field. The number limits are imposed when entering the number. The user
    will keep getting the question (along with the valid range of numbers)
    until they respect the limits.




    
    \item[{\tt ESC int ; str l}] Specifies a {\bf l}ist of values, a multiple
    choice selection. The first argument defines the visible length of this
    field. The second argument is a string containing the possible choices. The
    string is enclosed in double quotes and choices are delimited with pipes
    ({\tt |}).

    In full-screen mode, this directive uses the specified space to print as
    much of one of the choices as will fit. The arrow keys, the space bar and
    other keys change the active option.

    In menu-driven mode, the user is presented with a submenu of the choices
    specified in the second argument.

    Here are a few examples:

    \begin{itemize}

    \item {\tt ESC@5;"Yes|No|Maybe"l} denotes a multiple-choice list providing
    three obvious options. All options are padded to 5 characters, except
    `Maybe', which is already 5 characters long.

    \item {\tt ESC@5;"Yessirree|Nope, thank you|Maybe"l} chops off excess
    characters, transforming the visible choices to `Yessi', `Nope,', and
    leaving `Maybe' as it is.

    \end{itemize}

    

    \item[{\tt ESC str t}] Specifies a {\bf t}oggle field, holding a boolean
    value. The first and only argument is a two-character string (any less
    cause undefined behaviour, any more are ignored), denoting the two
    characters used to display the off/on states of the toggle (or yes/no, or
    true/false, or whatever else you use it for). The first character is the
    off/no/false state, the second is on/yes/true.

    In full-screen mode, this directive uses a single character to display the
    state of the toggle field. Space or the arrow keys toggle the value.

    In menu-driven mode, the system prints the corresponding character where
    the field is specified.

    Here's a simple example:

    \begin{itemize}

    \item {\tt [ESC@" X"t]} Specifies a toggle drawn inside a pair of
    brackets. The toggle displays a space for the off state, rendering into
    {\tt [ ]}. The on state is {\tt [X]}. This is the style I personally
    prefer, because it looks a bit like Borland's Turbovision (which I was
    programming on before I got into Megistos --- the are definite influences
    in the default visual design of the dialog boxes).

    \end{itemize}

    
    \item[{\tt ESC int ; str b}] Specifies a {\bf b}utton. Buttons terminate
    the data entry session. All dialog boxes have at least two buttons, whether
    you define them or not: OK and Cancel. These are associated with hot-keys
    in full-screen mode, and with the {\tt OK} and {\tt X} commands in
    menu-driven mode. The first argument of the directive specifies the width
    of the button in characters. The second is the button label.

    In full-screen mode, labels are centred within the available
    space. Focusing or `going into' the button draws greater-than and less-than
    signs as arrows to point to the label. The makeshift arrows are drawn at
    the edges of the button's area, so always specify at least two characters
    more than the width of the label.

    In menu-driven mode, there is {\em no visual component} for this
    control. However, the user may select it by number, exiting the current
    dialogue.

    Here's a simple example:

    \begin{itemize}

    \item {\tt ESC@8;"OK"b} Specifies an `OK' button, centred in an
    8-character space. Focusing will put makeshift arrows in the first and
    eighth position, effectively decreasing the padding.

    \end{itemize}
    
 */

/*@{*/
/*@}*/

/** @name Template style guide.
    @filename dialog_style

    @doc Here are a few arbitrary guidelines for full-screen dialogue
    templates. These are the ones I like to use. This being a BBS, though,
    these are only guidelines and not rules!

    \begin{itemize}

    \item Use different colours for different types of fields. I played it safe
    and used the Turbovision scheme: white-on-blue for fields where you key in
    values and black-on-cyan for fields where you just have to press a key to
    make a change (i.e. lists and toggles).

    \item Place brief instructions to the right of each field that doesn't
    behave in any obvious manner. I like to give the valid range of each number
    field, and a string like `Space to change' next to lists and toggles.

    \item My buttons are like Turbovision-on-dope. They're `shaded' buttons,
    with red background for cancel-type buttons and green for everything else.

    \item Lists and toggles don't use any padding. If you use different
    backgrounds for these controls, they'll look strange compared to the
    others. I like to put two spaces on either end of lists. These are in the
    same colour as the list and work as backgrounds. For toggles, I use a space
    on either side {\em and} brackets, all in the same colour attributes as the
    field itself: black on cyan. It makes things look much better.

    \item Don't clutter things! Unless necessary, use every second line of the
    screen for fields. Otherwise, fields touch each other, looking ugly.

    \item If space permits, have a brief legend at the bottom of the dialogue
    box. You can list any of the key bindings for Help (Ctrl-R), field-help
    (Ctrl-O), Redraw (Ctrl-L), OK (Ctrl-S) or Cancel (Ctrl-C). The first two
    should probably always be there.

    \item Don't change the location or ordering of buttons in a dialog! You
    should try to keep the user interface consistent. Of course, if you move
    buttons around, things will break because your dialogue code will be
    looking for the buttons in the wrong places.

    \end{itemize} */

/*@{*/
/*@}*/


/** @name Preparing to use a dialogue.
    @filename dialog_preparation

    @doc Using dialogue boxes is, unfortunately, the most complicated part of
    writing a module. It's annoying in the beginning, but, after your first
    dialogue is done, you'll be able to scavenge code and re-use it at
    will. I've been doing the same!
    
    So, let's dive straight into it with some code to prepare and issue a
    dialogue box. We'll be issuing a dialogue with the following controls:

    \begin{enumerate}

    \item An 80 character string field.

    \item A 30 character password field.

    \item A list selection field allowing `Yes', `No' and `Maybe' (5 characters
    maximum).

    \item A toggle control (3 characters, because these controls report `on' or
    `off' depending on their state.

    \item A button labeled `OK'.

    \item Another button, `Cancel'. 

    \end{enumerate}

    Here's the code:

    \begin{verbatim}
    int  result;

    sprintf (inp_buffer,"%s\n%s\ns\n%s\nOK\nCancel\n",
                        "First string field",
			"password",
			"Yes",
			"on");

    result = dialog_run ("foo", FOOVT, FOOLT, inp_buffer, MAXINPLEN);

    if (result!=0) {
            error_log("Unable to run data entry subsystem");
	    return;
    }

    \end{verbatim}

    
    This code demonstrates quite a few things:

    \begin{itemize}

    \item Allocating space for the data. Here, we need space for: one
    80-character field, one 30-character field, a list whose longest value is 5
    characters long, and a toggle with 3 characters (`off' is the longest
    value). Add space needed for line feeds and we have {\tt 81+31+6+4}
    bytes. Add the "OK" button (3 bytes, including line feed) and the "Cancel"
    button (7 bytes, including line feed). Add enough space for the name of the
    longest button (7 bytes), which will be added by the data entry subsystem
    to tell you what button ended the session, and don't forget one byte for
    null termination. The grand total is {\tt 81+31+6+4+3+7+7+1=140}. Brilliant
    stuff.

    {\em Alternatively}, you could say the hell with it, figure out the system
    already has buffers much larger than this, and use them. I whole-heartedly
    recommend using {\tt inp_buffer} from the input subsystem because you can
    re-use existing BBS functionality to parse the results. It's all right to
    clobber {\tt inp_buffer}, assuming you've already parsed all of the user's
    input, which is highly likely. In fact, you shouldn't allow concatenated
    commands past a data entry session anyway.

    \item Specifying the default values. The {\tt sprintf()} command takes care
    of that for us (if you're paranoid about overflows, you're welcome to use
    {\tt snprintf()} instead). We put the value of each control on a line of
    its own, terminating lines with {\tt '\n'}. Here's how to do it for all
    available types of controls:

    \begin{description}

    \item[String and numerical fields] Just write the default value you
    need. Make sure the value is within the specifications (e.g. length,
    min-max ranges for numbers) of the fields! There's no need to enclose
    strings in double quotes.

    \item[Lists] Write the string of one of the settings. In our yes/no/maybe
    example, we write {\tt "Yes"}. Note that we observe case. The string should
    be a perfect match with {\tt strcmp()}.

    \item[Toggles] Specify {\tt on} or {\tt off} to denote the obvious
    things. User lower case.

    \item[Buttons] Anything you write will be ignored, but do write something
    as a placeholder. The data entry subsystem will replace these placeholders
    with the actual labels of the respective buttons on exit.

    \end{description}

    \item Executing the data entry subsystem.

    The call to the data entry subsystem is nothing too complicated (and it's
    all explained in this part of the documentation). You need to give it the
    name of a message block, two prompts containing the dialogue templates for
    visual and menu-based (`linear') data entry, and the newly constructed
    string of default values. Don't forget to check the return value in case an
    error precluded the dialogue from running. In such a case, abort the
    current process and go back to the module's previous (or main) menu. No
    need to register a fatal error for this.

    \end{itemize}

    */

/*@{*/
/*@}*/



/** @name Dialogue aftermath.
    @filename dialog_aftermath

    @doc This is what happens after you call the {\tt dialog_run()}. Here's the
    entire code, including the parts mentioned before:

    \begin{verbatim}
    int  result;

    sprint f(inp_buffer,"%s\n%s\ns\n%s\nOK\nCancel\n",
                        "First string field",
			"password",
			"Yes",
			"on");

    result = dialog_run ("foo", FOOVT, FOOLT, inp_buffer);

    if (result!=0) {
            error_log("Unable to run data entry subsystem");
	    return;
    }

    dialog_parse(inp_buffer);

    if (sameas(margv[6],"OK") || sameas (margv[4],margv[6])) {
            print ("String field 1 has value \"%s\"\n",margv[0]);
            print ("String field 2 has value \"%s\"\n",margv[1]);
	    print ("Toggle has value         \"%s\"\n",margv[2]);
	    print ("List has value           \"%s\"\n",margv[3]);
    } else print ("Cancel button pressed.\n");

    \end{verbatim}
    
    This is where using {\tt inp_buffer} shows its advantages: you can parse
    the entire result string with a single call to {\tt dialog_parse()}, which
    is virtually the same function we use to parse a user's input. I like
    re-using code!

    The rest should be pretty obvious. The last datum returned by {\tt
    dialog_run()} is the {\em label} of one of three things: 

    \begin{itemize}

    \item The label of button that ended the dialogue. This may change,
    depending on sysop customisation and internationalisation.

    \item The string {\tt "OK"}, if the user pressed the `save' shortcut, which
    is synonymous to `pressing' the OK button. You should always have an OK
    button, but even if you don't, this shortcut will still work in this way.

    \item The string {\tt "Cancel"}, if the user pressed the `cancel' shortcut.

    \end{itemize}

    Since our dialogue only has two buttons, OK and Cancel, we check for the
    `OK' shortcut and an actual button `press'. The latter is done by comparing
    the label of the OK button (whatever it is) against the label of the button
    that ended the dialogue.

    */

/*@{*/
/*@}*/


/** Issue a dialogue box.

    This function issues and handles an interactive, full-screen dialogue box
    for data-entry purposes. The user is presented with either a full-screen
    (visual) interface, or the traditional menu-driven environment. This
    depends on the user's personal settings.

    @param msg The name of a message block file to open. This is used to obtain
    the dialogue templates, custom help strings, and other prompts. It should
    be supplied as a basename (no directories), and without the {\tt .mbk}
    extension. In other words, just like the string you pass to {\tt
    msg_open()}.

    @param visual The prompt number of the full-screen template for this
    dialogue. This is almost exactly the same as any old ANSI prompt, with one
    addition: it allows certain escape directives to specify the position and
    format of entry fields, buttons, and other controls. For the nature of
    those controls, please refer to the {\em Template directives} section
    below.

    @param linear The base prompt number of the linear, traditional data entry
    template. This allows the same template directives as above, but the
    controls are rendered in a different way.

    @param data A string containing the default values of the fields specified
    in the template, in the order specified in the template. Upon exit, the
    same string will hold the contents of the same fields, as modified by the
    user (or the default, if the fields were not modified). A dialogue exit
    code or the name of the button that terminated the dialogue is also
    returned. The format of the string and how to parse it are described
    elsewhere in this section of documentation. Look at it for fuller
    instructions on how to do it.

    @param len The size of {\tt data}. No results exceeding this size will be
    read from the dialogue. Make sure there's enough space!

    @return A result compatible with that of the {\tt runmodule()} command, or
    -1 if an error occurred in preparing for data entry. */

int dialog_run(char *msg, int visual, int linear, char *data, size_t len);


/** Parse dialog result strings

    Breaks up the supplied string into {\tt margc} data entry components stored
    in {\tt margv}.

    @param s The {\tt data} string as returned from {\tt dialog_run()}. */

void dialog_parse(char *s);


#endif /* DIALOG_H */

/*@}*/

/*
LocalWords: Alexios doc BBS newfangled legalese otnotesize ifndef VER em
LocalWords: endif tt ESC int str bf tring ORred DD ist submenu Yessirree
LocalWords: Yessi oggle Borland's Turbovision Megistos utton centred cyan
LocalWords: button's colours Ctrl inp ns nOK nCancel dataentry foo FOOVT
LocalWords: FOOLT sprintf snprintf min strcmp placeholder placeholders msg
LocalWords: sameas margv sameas margv margv sysop param basename
LocalWords: mbk len runmodule
*/
