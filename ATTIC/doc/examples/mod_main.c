/* Warning: This is not a complete source file. */ 

const char rcsinfo[]="$Id$";

mod_info_t mod_info_news = {
	"news",
	"BBS news bulletins",
	"Alexios Chouchoulas <alexios@bedroomlan.org>",
	"Shows bulletins to users immediately after login.",
	rcsinfo,
	"1.0",
	{10, handler_login},		/* Login handler */
	{0,  handler_run},		/* Interactive handler */
	{0,  NULL},			/* Install logout handler */
	{0,  NULL},			/* Hangup handler */
	{50, handler_cleanup},		/* Cleanup handler */
	{0,  NULL}			/* Delete user handler */
};


int
main (int argc, char **argv)
{
	mod_setinfo (&mod_info_news);
	return mod_main (argc, argv);
}
