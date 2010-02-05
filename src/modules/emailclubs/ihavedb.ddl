database ihavedb {

	data file [1024] "DATA"	contains ihaverec;
	key  file [1024] "KEY0"	contains ihaverec.clubqueryc;

	key  file [1024] "KEY1"	contains ihaverec.netqueryc;
	key  file [1024] "KEY2"	contains ihaverec.ihavelistc;

	/*
	   message types: 'M' = message;
			  'D' = control_delete_message;
	*/

	record ihaverec {
		long	time;		/* Time registered */

		/* Network-wide unique message ID: original source */

		char	bbs     [80];	/* hostname/BBS pair */
		char	msgid   [32];	/* message ID */
		char	orgclub [16];	/* original club name */
		
		/* The local message vector */
			
		char	club	[16];	/* local club name */
		int	num;		/* local number */
		char	type;		/* message type */

		primary key clubqueryc {type,num,club};
		alternate key netqueryc {msgid,orgclub,bbs};
		alternate key ihavelistc {club,time};
	}
}
