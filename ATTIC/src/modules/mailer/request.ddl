database request {

	define UIDLEN		24
	define AREALEN	        24
	define FNAMELEN		256
	define DOSFNAMELEN	13

	data file [512] "DATA"	contains reqidx;
	key  file [4096] "KEY0"	contains reqidx.orderc;

	key  file [4096] "KEY1"	contains reqidx.userid;
	key  file [4096] "KEY2"	contains reqidx.reqnum;

	record reqidx {
		int     reqnum;
	    	char	userid	 [UIDLEN];
	    	char	reqarea	 [AREALEN];
	    	char	reqfname [FNAMELEN];
		char    dosfname [DOSFNAMELEN];
	    	int	priority;
	    	long	reqflags;
            	int	reqdate;
		int	msgno;

		primary key orderc {userid, reqarea, reqnum, priority};
		alternate key userid;
		alternate unique key reqnum;
	}
}
