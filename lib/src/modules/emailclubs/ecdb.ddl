database ecdb {

	define UID_LEN		80
	define SUBJ_LEN		64

	data file [1024] "DATA"	contains ecidx;
	key  file [1024] "KEY0"	contains ecidx.num;

	key  file [1024] "KEY1"	contains ecidx.fromc;
	key  file [1024] "KEY2"	contains ecidx.toc;
	key  file [1024] "KEY3"	contains ecidx.subjectc;
	key  file [1024] "KEY4"	contains ecidx.from;
	key  file [1024] "KEY5"	contains ecidx.to;
	key  file [1024] "KEY6"	contains ecidx.subject;

	record ecidx {
		long	num;
		char    from	[UID_LEN];
		char    to	[UID_LEN];
		char	subject	[SUBJ_LEN];
		long    flags;

		primary key num;
		alternate unique key fromc {from, num};
		alternate unique key toc {to, num};
		alternate unique key subjectc {subject, num};
		alternate key from;
		alternate key to;
		alternate key subject;
	}
}
