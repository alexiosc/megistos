#!/usr/bin/perl
#
# This perl filter will try to convert source to the new v.99 API. This only
# changes function names! Please be aware that quite a few functions have
# changed in more fundamental ways than this. You have been warned! Well, at
# the very least, this should save some find-and-replace time.
#
# You should execute this filter like this:
#
# for a in *.[ch]; do 98to99.pl <$a >$a~ && mv -vf $a~ $a; done
#
# This functionality isn't implemented within the script for versatility's
# sake.
#
# Good luck with porting! - Alexios
# (who am I kidding? This message is probably only for me)

while(<>){

    # channels

    s/\bbaudstg(\s*\()/channel_baudstg$1/g;
    s/\bgetlinestatus(\s*\()/channel_getstatus$1/g;
    s/\bsetlinestatus(\s*\()/channel_setstatus$1/g;

    # bbsmod

    s/\bINIT([A-Z]+)\b/INI_$1/g;
    s/\binitmodule(\s*\()/mod_init$1/g;
    s/\bdonemodule(\s*\()/mod_done$1/g;
    
    # errors

    s/\bfatal(\s*\()/error_fatal$1/g;
    s/\bfatalsys(\s*\()/error_fatalsys$1/g;
    s/\blogerror(\s*\()/error_log$1/g;
    s/\blogerrorsys(\s*\()/error_logsys$1/g;
    s/\binterror(\s*\()/error_int$1/g;
    s/\binterrorsys(\s*\()/error_intsys$1/g;

    #input

    s/\binput\b/inp_buffer/g;
    s/\binplen\b/inp_len/g;
    s/\binitinput(\s*\()/inp_init$1/g;
    s/\bdoneinput(\s*\()/inp_done$1/g;
    s/\bacceptinjoth(\s*\()/inp_acceptinjoth$1/g;
    s/\bgetinput(\s*\()/inp_get$1/g;
    s/\binputstring(\s*\()/inp_readstring$1/g;
    s/\bparsin(\s*\()/inp_parsin$1/g;
    s/\brstrin(\s*\()/inp_raw$1/g;
    s/\bcancelinput(\s*\()/inp_cancel$1/g;
    s/\bsetinputtimeout(\s*\()/inp_timeout$1/g;
    s/\bsetpasswordentry(\s*\()/inp_setpasswd$1/g;
    s/\binptimeout_msecs(\s*\()/inp_timeout_msecs$1/g;
    s/\binptimeout_intr(\s*\()/inp_timeout_intr$1/g;
    s/\bmonitoinput(\s*\()/inp_monitor$1/g;
    s/\nonbblocking(\s*\()/inp_block$1/g;
    s/\bblocking(\s*\()/inp_block$1/g;
    s/\bresetblocking(\s*\()/inp_resetblocking$1/g;

    s/\bnxtcmd\b/cnc_nxtcmd/g;
    s/\bbgncnc\b/cnc_begin/g;
    s/\bendcnc\b/cnc_end/g;
    s/\bcncchr\b/cnc_chr/g;
    s/\bcnclon\b/cnc_long/g;
    s/\bcncyesno \b/cnc_yesno/g;
    s/\bcncword\b/cnc_word/g;
    s/\bcncall \b/cnc_all/g;
    s/\bmorcnc\b/cnc_more/g;
    s/\bcnchex\b/cnc_hex/g;
    s/\bcncnum\b/cnc_num/g;

    s/\bgetnumber(\s*\()/get_number$1/g;
    s/\bgetbool(\s*\()/get_bool$1/g;
    s/\bgetuserid(\s*\()/get_userid$1/g;
    s/\bgetmenu(\s*\()/get_menu$1/g;

    # locks
    
    s/\bplacelock(\s*\()/lock_place$1/g;
    s/\bchecklock(\s*\()/lock_check$1/g;
    s/\brmlock(\s*\()/lock_rm$1/g;
    s/\bwaitlock(\s*\()/lock_wait$1/g;

    # prompts

    s/\bstruct(\s+)linestatus\b/channel_status_t/g;
    s/\bmsgbuf\b/msg_buffer/g;
    s/\bsysblk\b/msg_sys/g;
    s/\bcurblk\b/msg_cur/g;
    s/\blastblk\b/msg_last/g;
    s/\bpromptblk\b/promptblock_t/g;
    s/\bopnmsg(\s*\()/msg_open$1/g;
    s/\bclsmsg(\s*\()/msg_close$1/g;
    s/\bsetmbk(\s*\()/msg_set$1/g;
    s/\bgetmsglang(\s*\()/msg_getl$1/g;
    s/\bgetmsg(\s*\()/msg_get$1/g;
    s/\bgetpfixlang(\s*\()/msg_getunitl$1/g;
    s/\bgetpfix(\s*\()/msg_getunit$1/g;
    s/\blngopt(\s*\()/msg_long$1/g;
    s/\bhexopt(\s*\()/msg_hex$1/g;
    s/\bnumopt(\s*\()/msg_int$1/g;
    s/\bynopt(\s*\()/msg_bool$1/g;
    s/\bchropt(\s*\()/msg_char$1/g;
    s/\bstgopt(\s*\()/msg_string$1/g;
    s/\btokopt(\s*\()/msg_token$1/g;
    s/\bsetlanguage(\s*\()/msg_setlanguage$1/g;

    # security

    s/\bkeyhasflag(\s*\()/key_exists$1/g;
    s/\bhaskey(\s*\()/key_owns$1/g;

    # ttynum
    
    s/\bnumchannels(.+)/chan_count$1/g;
    s/\blastchandef(.+)/chan_last$1/g;
    s/\binitchannels(\s*\()/chan_init$1/g;
    s/\bgetchannelnum(\s*\()/chan_getnum$1/g;
    s/\bgetchannelindex(\s*\()/chan_getindex$1/g;
    s/\bgetchannelname(\s*\()/chan_getname$1/g;
    s/\btelnetlinecount(\s*\()/chan_telnetlinecount$1/g;

    # useracc
    
    s/\buserexists(\s*\()/usr_exists$1/g;
    s/\bfindclass(\s*\()/cls_find$1/g;
    s/\bloaduseraccount(\s*\()/usr_loadaccount$1/g;
    s/\bsaveuseraccount(\s*\()/usr_saveaccount$1/g;
    s/\bloaduseronlrec(\s*\()/usr_loadonlrec$1/g;
    s/\bsaveuseronlrec(\s*\()/usr_saveonlrec$1/g;
    s/\bpostcredits(\s*\()/usr_postcredits$1/g;
    s/\bchargecredits(\s*\()/usr_chargecredits$1/g;
    s/\bchangeclass(\s*\()/usr_setclass$1/g;
    s/\bcanpay(\s*\()/usr_canpay$1/g;
    s/\buinsystem(\s*\()/usr_insystem$1/g;
    s/\buinsys(\s*\()/usr_insys$1/g;
    s/\binjoth(\s*\()/usr_injoth$1/g;
    s/\buidxref(\s*\()/usr_uidxref$1/g;
    s/\bclassrec\b/classrec_t/g;

    print;
}
