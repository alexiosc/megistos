struct substvar table []={
	{"BBS",      sv_bbstitle, NULL},
	{"COMPANY",  sv_company,  NULL},
	{"ADDRESS1", sv_address1, NULL},
	{"",         NULL,        NULL}
};

/* . . . */

int i=0;

while (table [i].varname [0]) {
	out_addsubstvar (table [i].varname, table [i].varcalc);
	i++;
}
