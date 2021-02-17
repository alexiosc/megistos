int  result;

sprintf (inp_buffer, "%s\n%s\ns\n%s\nOK\nCancel\n",
	 "First string field",
	 "password",
	 "Yes",
	 "on");

result = dialog_run ("foo", FOOVT, FOOLT, inp_buffer);

if (result != 0) {
	error_log ("Unable to run data entry subsystem");
	return;
}

dialog_parse (inp_buffer);

if (sameas (margv [6], "OK") || sameas (margv [4], margv [6])) {
	print ("String field 1 has value \"%s\"\n", margv [0]);
	print ("String field 2 has value \"%s\"\n", margv [1]);
	print ("Toggle has value         \"%s\"\n", margv [2]);
	print ("List has value           \"%s\"\n", margv [3]);
} else {
	print ("Cancel button pressed.\n");
}
