/*****************************************************************************\
 **                                                                         **
 **  FILE:     property.c                                                   **
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
 * $Id$
 *
 * $Log$
 * Revision 1.4  2003/12/24 20:12:15  alexios
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
    "$Id$";

/*
 * property.c
 *
 * Property manipulation routines
 *
 */

#include <bbs.h>
#include <megistos/ztypes.h>



/*
 * get_property_addr
 *
 * Calculate the address of the start of the property list associated with an
 * object.
 *
 */

static  zword_t
get_property_addr (zword_t obj)
{
	zword_t offset, prop;

	/* Calculate the address of the property pointer in the object */

	offset = get_object_address (obj);
	offset += (h_type < V4) ? O3_PROPERTY_OFFSET : O4_PROPERTY_OFFSET;

	/* Read the property pointer */

	prop = get_word (offset);

	/* Skip past object description which is an ASCIC of encoded words */

	prop += (get_byte (prop) * 2) + 1;

	return (prop);
}



/*
 * get_next_property
 *
 * Calculate the address of the next property in a property list.
 *
 */

static  zword_t
get_next_property (zword_t propp)
{
	zbyte_t value;

	/* Load the current property id */

	value = get_byte (propp++);

	/* Calculate the length of this property */

	if (h_type < V4)
		value = (zbyte_t) ((value & property_size_mask) >> 5);
	else if (value & 0x80)
		value = get_byte (propp) & (zbyte_t) property_size_mask;
	else if (value & 0x40)
		value = 1;
	else
		value = 0;

	/* Address property length + 1 to current property pointer */

	return ((zword_t) (propp + value + 1));
}



/*
 * load_property
 *
 * Load a property from a property list. Properties are held in list sorted by
 * property id, with highest ids first. There is also a concept of a default
 * property for loading only. The default properties are held in a table pointed
 * to be the object pointer, and occupy the space before the first object.
 *
 */

void
load_property (zword_t obj, zword_t prop)
{
	zword_t propp;

	/* Load address of first property */

	propp = get_property_addr (obj);

	/* Scan down the property list while the target property id is less than the
	   property id in the list */

	while ((zbyte_t) (get_byte (propp) & property_mask) > (zbyte_t) prop)
		propp = get_next_property (propp);

	/* If the property ids match then load the first property */

	if ((zbyte_t) (get_byte (propp) & property_mask) == (zbyte_t) prop) {

		/* Only load first property if it is a byte sized property */

		if ((get_byte (propp++) & property_size_mask) == 0) {
			store_operand (get_byte (propp));
			return;
		}
	} else
		/* Calculate the address of the default property */

		propp = h_objects_offset + ((prop - 1) * 2);

	/* Load the first property word */

	store_operand (get_word (propp));
}



/*
 * store_property
 *
 * Store a property value in a property list. The property must exist in the
 * property list to be replaced.
 *
 */

void
store_property (zword_t obj, zword_t prop, zword_t value)
{
	zword_t propp;

	/* Load address of first property */

	propp = get_property_addr (obj);

	/* Scan down the property list while the target property id is less than the
	   property id in the list */

	while ((zbyte_t) (get_byte (propp) & property_mask) > (zbyte_t) prop)
		propp = get_next_property (propp);

	/* If the property id was found then store a new value, otherwise complain */

	if ((zbyte_t) (get_byte (propp) & property_mask) == (zbyte_t) prop) {

		/* Determine if this is a byte or word sized property */

		if ((get_byte (propp++) & property_size_mask) == 0)
			set_byte (propp, value);
		else
			set_word (propp, value);
	} else
		error_fatal ("No such property");
}



/*
 * load_next_property
 *
 * Load the property after the current property. If the current property is zero
 * then load the first property.
 *
 */

void
load_next_property (zword_t obj, zword_t prop)
{
	zword_t propp;

	/* Load address of first property */

	propp = get_property_addr (obj);

	/* If the property id is non zero then find the next property */

	if (prop) {

		/* Scan down the property list while the target property id is less than the
		   property id in the list */

		while ((zbyte_t) (get_byte (propp) & property_mask) >
		       (zbyte_t) prop)
			propp = get_next_property (propp);

		/* If the property id was found then get the next property, otherwise complain */

		if ((zbyte_t) (get_byte (propp) & property_mask) ==
		    (zbyte_t) prop)
			propp = get_next_property (propp);
		else
			error_fatal ("No such property");
	}

	/* Return the next property id */

	store_operand (get_byte (propp) & property_mask);
}



/*
 * load_property_address
 *
 * Load the address address of the data associated with a property.
 *
 */

void
load_property_address (zword_t obj, zword_t prop)
{
	zword_t propp;

	/* Load address of first property */

	propp = get_property_addr (obj);

	/* Scan down the property list while the target property id is less than the
	   property id in the list */

	while ((zbyte_t) (get_byte (propp) & property_mask) > (zbyte_t) prop)
		propp = get_next_property (propp);

	/* If the property id was found then calculate the property address, otherwise return zero */

	if ((zbyte_t) (get_byte (propp) & property_mask) == (zbyte_t) prop) {

		/* Skip past property id, can be a byte or a word */

		if (h_type > V3 && (get_byte (propp) & 0x80))
			propp++;
		propp++;
		store_operand (propp);
	} else
		/* No property found, just return 0 */

		store_operand (0);

}



/*
 * load_property_length
 *
 * Load the length of a property.
 *
 */

void
load_property_length (zword_t propp)
{
	/* Back up the property pointer to the property id */

	propp--;

	if (h_type < V4)

		/* Property length is in high bits of property id */

		store_operand (((get_byte (propp) & property_size_mask) >> 5) +
			       1);
	else if (get_byte (propp) & 0x80)

		/* Property length is in property id */

		store_operand (get_byte (propp) & property_size_mask);
	else
		/* Word sized property if bit 6 set, else byte sized property */

		store_operand ((get_byte (propp) & 0x40) ? 2 : 1);

}



/*
 * scan_data
 *
 * Scan an array of bytes or words looking for a target byte or word. The
 * optional 4th parameter can set the address step and also whether to scan a
 * byte array.
 *
 */

void
scan_data (int argc, zword_t * argv)
{
	unsigned long address;
	unsigned int i, step;

	/* Supply default parameters */

	if (argc < 4)
		argv[3] = 0x82;

	address = argv[1];
	step = argv[3];

	/* Check size bit (bit 7 of step, 1 = word, 0 = byte) */

	if (step & 0x80) {

		step &= 0x7f;

		/* Scan down an array for count words looking for a match */

		for (i = 0; i < argv[2]; i++) {

			/* If the word was found store its address and jump */

			if (read_data_word (&address) == argv[0]) {
				store_operand ((zword_t) (address - 2));
				conditional_jump (TRUE);
				return;
			}

			/* Back up address then step by increment */

			address = (address - 2) + step;

		}

	} else {

		step &= 0x7f;

		/* Scan down an array for count bytes looking for a match */

		for (i = 0; i < argv[2]; i++) {

			/* If the byte was found store its address and jump */

			if ((zword_t) read_data_byte (&address) ==
			    (zword_t) argv[0]) {
				store_operand ((zword_t) (address - 1));
				conditional_jump (TRUE);
				return;
			}

			/* Back up address then step by increment */

			address = (address - 1) + step;

		}

	}

	/* If the data was not found store zero and jump */

	store_operand (0);
	conditional_jump (FALSE);
}



/*
 * move_data
 *
 */

void
move_data (zword_t src, zword_t dst, zword_t count)
{
	unsigned long address;
	unsigned int i;

	/* Catch no-op move case */

	if (src == dst || count == 0)
		return;

	/* If destination address is zero then fill source with zeros */

	if (dst == 0) {
		for (i = 0; i < count; i++)
			store_byte (src++, 0, 0);
		return;
	}

	address = src;

	if ((short) count < 0) {
		while (count++)
			store_byte (dst++, 0, read_data_byte (&address));
	} else {
		address += (unsigned long) count;
		dst += count;
		while (count--) {
			address--;
			store_byte (--dst, 0, read_data_byte (&address));
			address--;
		}
	}
}



/*
 * load_word
 *
 * Load a word from an array of words
 *
 */

void
load_word (zword_t addr, zword_t offset)
{
	unsigned long address;

	/* Calculate word array index address */

	address = addr + (offset * 2);

	/* Store the byte */

	store_operand (read_data_word (&address));
}



/*
 * load_byte
 *
 * Load a byte from an array of bytes
 *
 */

void
load_byte (zword_t addr, zword_t offset)
{
	unsigned long address;

	/* Calculate byte array index address */

	address = addr + offset;

	/* Load the byte */

	store_operand (read_data_byte (&address));
}



/*
 * store_word
 *
 * Store a word in an array of words
 *
 */

void
store_word (zword_t addr, zword_t offset, zword_t value)
{

	/* Calculate word array index address */

	addr += offset * 2;

	/* Check we are not writing outside of the writeable data area */

	if (addr > data_size)
		error_fatal ("Attempted write out of data area");

	/* Store the word */

	set_word (addr, value);

}



/*
 * store_byte
 *
 * Store a byte in an array of bytes
 *
 */

void
store_byte (zword_t addr, zword_t offset, zword_t value)
{
	/* Calculate byte array index address */

	addr += offset;

	/* Check we are not writing outside of the writeable data area */

	if (addr > data_size)
		error_fatal ("Attempted write out of data area");

	/* Store the byte */

	set_byte (addr, value);

}


/* End of File */


/* End of File */
