/*****************************************************************************\
 **                                                                         **
 **  FILE:     metaservices.x                                               **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  RPC Protocol specification for BBS meta-services.            **
 **  NOTES:    Purposes:                                                    **
 **              Provide a per-host registration service for all BBSs       **
 **              running on the host.
 **                                                                         **
 **              Offer a central service for the sharing of distributed     **
 **              phone lines.                                               **
 **                                                                         **
 **              Allow the operation of networked messages.                 **
 **                                                                         **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 15:00:47  alexios
 * Initial revision
 *
 * Revision 1.1  1999/07/21 21:32:34  bbs
 * Initial revision
 *
 *
 */



struct registration_package_t {

	/* Straight from the BBS */

	char   codename		[9];	/* BBS node name (8 letters + NULL) */
	char   bbstitle		[52];	/* Full title of the BBS */
	char   company		[48];	/* Company owning the system */
	char   address1		[48];	/* 1st address line */
	char   address2		[48];	/* 2nd address line */
	char   city		[48];	/* City */
	char   dataphone	[48];	/* Data phone number(s) */
	char   voicephone	[48];	/* Voice phone number(s) */
	int    users_online;		/* Current number of users on-line */
	int    lines_free;		/* Number of shareable lines FREE */
	int    lines_max;		/* Max number of shareable lines */

	/* For line sharing and Internet services */

	string hostname		<>;	/* Hostname reported to client */
	int    port;			/* The telnet port to use */
	string url              <>;	/* An optional URL of the BBS's page */
	string email		<>;	/* An optional contact email address */
	string access_allow	<>;	/* Telnet access list (allowed) */
	string access_deny	<>;	/* Telnet access list (denied) */
	string bbs_ad		<8192>; /* ASCII art advert of the system */

	/* These are here so the daemon can get more info on the BBS */

	int    bbs_uid;			/* The UID of the bbs user */
	int    bbs_gid;			/* The GID of the bbs user */
	int    bbsd_pid;		/* The PID of the BBS daemon */
	string prefix		<>;	/* The BBS directory prefix; */

	/* These are only used by the server */

	int    regtime;			/* Time of registration */
	int    flags;			/* !=0: don't disconnect after session */
};


typedef struct info_package_t * info_package_p;


struct info_package_t {
	char   codename		[9];	/* BBS node name (8 letters + NULL) */
	char   bbstitle		[52];	/* Full title of the BBS */
	char   company		[48];	/* Company owning the system */
	char   address1		[48];	/* 1st address line */
	char   address2		[48];	/* 2nd address line */
	char   city		[48];	/* City */
	char   dataphone	[48];	/* Data phone number(s) */
	char   voicephone	[48];	/* Voice phone number(s) */
	int    users_online;		/* Current number of users on-line */
	int    lines_free;		/* Number of FREE shareable lines */
	int    lines_max;		/* Max Number of shareable lines */
	string hostname		<>;	/* Hostname reported to client */
	int    port;			/* The telnet port to use */
	string url              <>;	/* An optional URL of the BBS's page */
	string email		<>;	/* An optional contact email address */
	string bbs_ad		<8192>; /* Advert of the system */
	int    disconnect;		/* Disconnect user after session? */

	info_package_p		next;	/* Ptr to next package in the list */
};



typedef struct club_list_item_t * club_list_item_p;


struct club_list_item_t {
	char	club		[16];	/* The club name (only 16 bytes used) */
	char	descr		[64];	/* Description of the club */

	club_list_item_p	next;	/* Ptr to next club in the list */
};


union club_list switch (int errno) {
case 0:
	club_list_item_p        clubs;  /* Linked list of exported clubs */
default:
	void;
};



struct club_header_request_t {
	char	codename	[9];	/* caller's BBS codename */		
	char	club		[16];	/* name of club */
};



struct club_header_t {
	char	club		[16];	/* name of the club   */
	char	descr		[64];	/* club description */
	char	clubop		[24];	/* main club operator */
	int	crdate;			/* club creation date */
	int	crtime;			/* club creation time */

	int	nmsgs;			/* number of messages */
	int	nper;			/* number of periodic messages */
	int	nblts;			/* number of bulletins */
	int	nfiles;			/* number of files */
	int	nfunapp;		/* number of unapproved files */

	int	msglife;		/* message lifetime */

	string	banner		<>;	/* club banner */
};


union club_header switch (int errno) {
case 0:
	club_header_t	club;		/* Returned club header */
default:
	void;
};



typedef struct ihave_entry_t * ihave_list_p;


struct ihave_entry_t {
	string	codename	<>;	/* originating BBS codename */
	string	orgclub		<>;	/* originating club name */
	string	msgid		<>;	/* system-unique message ID */

	ihave_list_p		next;	/* the next one in the list */
};


union ihave_list switch (int errno) {
case 0:
	ihave_list_p	ihave_list;	/* Linked list of IHAVE entries */
default:
	void;
};


struct ihave_request_t {
	char		codename[9];	/* caller's BBS codename */		
	unsigned int 	since_time;	/* list starting time */
};


struct message_request_t {
	char	codename	[9];	/* caller's BBS codename */		
	string	orgclub		<>;	/* originating club name */
	string	msgid		<>;	/* system-unique message ID */
	int     compression;		/* non-zero for gzipped reply */
};


struct club_message_t {
	char	from		[80];	/* sender's name/email address */
	char	to		[80];	/* recipient (as sender) */
	char	subject		[64];	/* message subject */
	char	fatt		[16];	/* name of file attachment */
	long	msgno;			/* original number */
	long	flags;			/* message flags */
	char	origclub	[16];	/* original club name */

	int	compression;		/* !=0 => strings are gzipped */
	char	message		<>;	/* entire message body */
	char	attachment	<>;	/* file attachment, if any */
};


union club_message switch (int errno) {
case 0:
	club_message_t	message;	/* an entire club message */
default:
	void;
};





program METABBS_PROG {

	version METABBS_VERS {


		/**** Basic BBS connectivity and channel distribution *****/


		/* The BBS registration call */

		int
		metabbs_register
		(registration_package_t) = 1;

		/* Register a system not running Megistos */

		int
 		metabbs_register_non_megistos
		(registration_package_t) = 2;

		/* Request information on all registered BBSs */

		info_package_p
		metabbs_request_info
		(string<>) = 3;



	
		/**** Distributed Megistos clubs ****/


		/* Return a list of all exported clubs with descriptions */

		union club_list
		distclub_request_list
		(string<>) = 100;

		/* Get a specific club's header */

		union club_header
		distclub_request_header
		(club_header_request_t) = 101;

		/* Obtain the IHAVE list since the specified date */

		union ihave_list
		distclub_request_ihave
		(ihave_request_t) = 102;

		/* Obtain an entire message */

		union club_message
		distclub_request_message
		(message_request_t) = 103;

	} = 1;

} = 0x204d4447;

/* The last three bytes of the program number spell "MEG". First byte varies
   {20,21,22,...,3F} */
