union foo_res switch (int errno) {
	case 0:
		string ret_string<>;
	default:
		void;
};

program TESTPROG {
	version TESTVERS {
		foo_res foo(void) = 1;
	} = 1;
} = 0x204d4447; /* The last three bytes spell "MEG". First byte varies {20,21,22,...,3F} */
