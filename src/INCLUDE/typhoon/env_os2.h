/*----------------------------------------------------------------------------
 * File    : environ.h
 * OS      : UNIX, OS/2, DOS
 * Author  : Thomas B. Pedersen
 *
 * Copyright (c) 1994 Thomas B. Pedersen.  All rights reserved.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the above
 * copyright notice and the following two  paragraphs appear (1) in all 
 * source copies of this software and (2) in accompanying documentation
 * wherever the programatic interface of this software, or any derivative
 * of it, is described.
 *
 * IN NO EVENT SHALL THOMAS B. PEDERSEN BE LIABLE TO ANY PARTY FOR DIRECT,
 * INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF
 * THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF HE HAS BEEN 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THOMAS B. PEDERSEN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" 
 * BASIS, AND THOMAS B. PEDERSEN HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Description:
 *   Multi Operating System compatibility include file.
 *
 * $Id$
 *
 *--------------------------------------------------------------------------*/

#ifndef _ENVIRON_INCLUDED
#define _ENVIRON_INCLUDED

/*--------------------------------------------------------------------------*/
/*                               OS/2 v2.0                                  */
/*--------------------------------------------------------------------------*/

#ifdef OS2
#ifdef __BORLANDC__
#   define __STDC__ 1
#endif
#define DIR_SWITCH		'\\'
#define CREATMASK		(S_IREAD|S_IWRITE)
#define PROTOTYPES		1
#define LITTLE_ENDIAN	1

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned long   ulong;

#endif


/*--------------------------------------------------------------------------*/
/*                                    DOS                                   */
/*--------------------------------------------------------------------------*/

#ifdef DOS

#define DIR_SWITCH		'\\'
#define CREATMASK		(S_IREAD|S_IWRITE)
#define PROTOTYPES		1
#define LITTLE_ENDIAN	1

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned long   ulong;

#endif


#ifdef PROTOTYPES
#	define PRM(x)		x
#	define _PRM(x)		x
#	define ELLIPSIS		,...
#else
#	define PRM(x)		();
#	define _PRM(x)		()
#	define ELLIPSIS		/**/
#endif

#ifndef offsetof
#	define offsetof(s,m)		((int)&(((s *)0))->m)
#endif

#endif

/* end-of-file */
