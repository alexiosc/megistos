database ecdb {

	define FNAME_LEN	13
	define AREA_LEN		16
	define UID_LEN		24
	define DESCR_LEN	64

	data file [4096] "DATA"	contains bltidx;
	key  file [1024] "KEY0"	contains bltidx.date;

	key  file [1024] "KEY1"	contains bltidx.num;
	key  file [4096] "KEY2"	contains bltidx.fname;
	key  file [4096] "KEY3"	contains bltidx.numc;
	key  file [4096] "KEY4"	contains bltidx.fnamec;

	record bltidx {
		int	num;
		int	date;
		int 	flags;
		int	timesread;
		char	fname[FNAME_LEN];
		char	area[AREA_LEN];
		char	author[UID_LEN];
		char	descr[DESCR_LEN];

		primary key num;
		alternate key date;
		alternate key fname;
		alternate unique key numc {area, num};
		alternate unique key fnamec {fname, area};
	}
}
