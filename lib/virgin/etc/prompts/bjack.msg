LEVEL2 {}


BJV_WDOGEXP {Plugin inactivity watchdog timer limit: 180} N 0 32768

BJV_TICKEXP {Seconds passed before inform user for inactivity: 30} N 0 32768

BJV_PAUSEEXP {Seconds before a new game begins: 50} N 0 32768

BJV_EPAUSEWARN {Inform users that new game will start soon? YES} B

BJV_PAUSEWARN {Inform user for new game every this seconds: 30} N 0 32768

BJV_WARNEXP {Maximum allowable warnings a player can receive before kicked: 2} N 0 10

BJV_SYSOPS_NOCHARGE {Sysops will not be charged for credits? YES} B

BJV_SYSTEM_PERC {Percent of pot that goes to system: 5} N 0 100

BJV_MIN_CRED {Minimum credits a user should have to play blackjack: 10} N 0 32768

BJV_MAX_BET {Maximum bet a user can place: 60} N 0 10000

BJV_LIGHT_CRED {Starting 'light' credits subtracted at each game: 5} N 0 32768

BJV_MIN_PLAYERS {Minimum number of players need to begin next game: 1} N 1 5

BJV_MAX_PLAYERS {Maximum number of players allowed to play (0=unlimited): 0} N 0 32768

BJV_SYSOPS_DEBUG {Should sysops allowed to see debugging information? NO} B


LEVEL3 {}

	string constant to print various hardcoded strings (will be removed)

BJM_STRING {%s} T String template


	print when starting a new game

BJM_NEWGAME {@BELL@***
!W[0;1;36m‹ ˜ ¤â˜ §˜¨«å›˜ Black Jack ¥œ¡ ¤©œ.!)
[0;1m} T New game just began


	print when a user entered a BJ command, but he is not
	participating to the game (eg. has not given BJ ON)
	
BJM_NOPART {@BELL@***
!W[0;1;31mƒœ ©¬££œ«â®œ«œ ©«¦ §˜ ®¤å› .!)
[0;1m} T No participation

BJM_BELLACT {œ¤œ¨š¦§¦ ãŸ¡œ} T activated
BJM_BELLDEACT {˜§œ¤œ¨š¦§¦ ãŸ¡œ} T deactivated

BJM_BELL {@BELL@***
!W[0;1;32m† ®« ¡ã œ ›¦§¦å© [37m%s[32m.!)
[0;1m} T Bell notice

BJM_CREDIT {£¦¤á›˜} T credit, singular
BJM_CREDITS {£¦¤á›œª} T credits, plural


	print when starting game, credits have been taken, and two cards are dealed

BJM_LIGHT {***
!W[0;1m%i[32m £¦¤á›œª ˜­˜ ¨âŸ¡˜¤ ˜§æ «¦ ¢¦š˜¨ ˜©£æ ©˜ª.
‘˜ª £¦ ¨á©«¡˜¤ ›ç¦ ­ç¢¢˜.!)
[0;1m} T Starting game

	fatal error message, when we cannot deallocate user memory

BJM_CNTDEALLOC {@BELL@***


FATAL ERROR: Could not deallocate user memory

} T Fatal error


	print when no winner found

BJM_NOWINNER {@BELL@***
!W[0;1;33m‰˜¤â¤˜ª ¤ ¡«ãª!!)
[0;1m} T No winner


	print when all players folded

BJM_ALLQUIT {@BELL@***
!W[0;1;33m¢¦  ¦  §˜å¡«œª œš¡˜«â¢œ ¯˜¤. ‰˜¤â¤˜ª ¤ ¡«ãª!!)
[0;1m} T All folded


	print when betting is over, and players start hitting cards
	
BJM_BEGHIT {@BELL@***
!W[0;1;32m’¦ §¦¤«á¨ ©£˜ ¦¢¦¡¢¨éŸ¡œ.!)
[0;1m} T Hitting is over


	print when an unknown command is given

BJM_ERCMD {@BELL@***
!W[0;1;31m† œ¤«¦¢ã §¦¬ ›é©˜«œ œå¤˜  áš¤à©«.!)
[0;1m} T Error command


	print when a player enters a bet command but its is not his turn
BJM_WAITBET {@BELL@***
!W[0;1;31mƒœ¤ £§¦¨œå«œ ¤˜ §¦¤«á¨œ«œ «é¨˜. œ¨ £â¤œ«œ « [37m©œ ¨á ©˜ª[31m.!)
[0;1m} T Wait turn to bet


	print when player enters a bet command, but the current game 
	state is not betting
	
BJM_CNTBET {@BELL@***
!W[0;1;31mƒœ¤ £§¦¨œå«œ ¤˜ §¦¤«á¨œ«œ «é¨˜. ’˜ §¦¤«˜¨å©£˜«˜ ¦¢¦¡¢¨éŸ¡˜¤.!)
[0;1m} T Cannot bet betting is over


	print when it is the players turn to bet
	
BJM_YTURNBET {***
!W[0;1;32m„å¤˜   ©œ ¨á ©˜ª ¤˜ §¦¤«á¨œ«œ.!)
[0;1m} T Your turn to bet


	print when it is the players turn to hit a card
	
BJM_YTURNHIT {***[0;1;32m
!W„å¤˜   ©œ ¨á ©˜ª ¤˜ «¨˜™ã¥œ«œ â¤˜ ­ç¢¢¦.!)
[0;1m} T Your turn to hit


	what player sees when he has betted an amount of credits
	
BJM_YBETCRED {@BELL@***
!W[0;1;32m¦¤«á¨œ«œ [37m%i[32m £¦¤á›œª.!)
[0;1m} T 


BJM_MPLAYER {} T player male form capital
BJM_FPLAYER {†} T player female form capital


	what other players see when a player has betted an amount of credits
	
BJM_OBETCRED {@BELL@***
!W[0;1;37m%s %s[32m §æ¤«˜¨œ [37m%i[32m £¦¤á›œª.!)
[0;1m} T User has placed their bet


	print when player tries to bet less credits than the
	current bet
	
BJM_MINBET {@BELL@***
!W[0;1;31mƒœ¤ £§¦¨œå«œ ¤˜ §¦¤«á¨œ«œ ¢ šæ«œ¨¦ ˜§æ [37m%i[32m £¦¤á›œª.!)
[0;1m} T Cannot bet so little


	print when player has not enough credits to bet
	
BJM_NOCRED {@BELL@***
!W[0;1;31mƒœ¤ â®œ«œ ˜¨¡œ«âª £¦¤á›œª š ˜ ¤˜ §¦¤«á¨œ«œ.!)
[0;1m} T Not enough credits


	print when a player tries to bet more than the allowed limit
	
BJM_TOOHIGH {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ §¦¤«á¨œ«œ §˜¨˜§á¤à ˜§æ [37m%i[31m £¦¤á›œª.!)
[0;1;m} T Bet is too high


	print when a player tries to bet a negative amount
	
BJM_TOOLOW {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ §¦¤«á¨œ«œ ¢ šæ«œ¨¦ ˜§æ [37m1[37m £¦¤á›˜.!)
[0;1;m} T Bet is too low



	print when a player tries to raise the bet, but it is not his turn
	
BJM_WAITRAISE {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ ˜¤œ™á©œ«œ «¦ §¦¤«á¨ ©£˜ «é¨˜. œ¨ £â¤œ«œ « ©œ ¨á ©˜ª.!)
[0;1m} T Cannot raise wait turn


	print when a player tries to raise the bet but current game state
	is not betting
	
BJM_CNTRAISE {@BELL@***[0;1;31m
!Wƒœ¤ §¦¨œå«œ ¤˜ ˜¤œ™á©œ«œ «¦ §¦¤«á¨ ©£˜ «é¨˜. ’˜ §¦¤«˜¨å©£˜«˜ ¦¢¦¡¢¨éŸ¡˜¤.!)
[0;1m} T Cannot raise betting over


	what player sees when he raises a bet
	
BJM_YRAISE {@BELL@***[0;1;32m
!W„¤«á¥œ  '™¢â§œ«œ' «¦ §¦¤«á¨ ©£˜ ¡˜  «¦ ˜¤œ™áœ«œ ¡˜«á [37m%i[32m £¦¤á›œª.!)
[0;1m} T You raise


	what other players see when a player raises the bet
	
BJM_ORAISE {@BELL@***[0;1;37m
!W%s %s[32m '™¢â§œ ' «¦ §¦¤«á¨ ©£˜ ¡˜  «¦ ˜¤œ™áœ  ¡˜«á [37m%i[32m £¦¤á›œª.!)
[0;1m} T User raises 


	print when a user tries to call a bet but it is not his turn
		
BJM_WAITCALL {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ ›œå«œ «¦ §¦¤«á¨ ©£˜ «é¨˜. œ¨ £â¤œ«œ « ©œ ¨á ©˜ª.!)
[0;1m} T Cannot call wait turn


	print when a user tries to call a bet, but current game state
	is not betting
	
BJM_CNTCALL {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ '›œå«œ' «¦ §¦¤«á¨ ©£˜ «é¨˜. ’˜ §¦¤«˜¨å©£˜«˜ ¦¢¦¡¢¨éŸ¡˜¤.!)
[0;1m} T Cannot call bet is over


	what player sees when calls a bet
	
BJM_YCALL {@BELL@***[0;1;32m
!W„¤«á¥œ , '™¢â§œ«œ' «¦ §¦¤«á¨ ©£˜.!)
[0;1m} T You call


	what other players see when a player calls a bet
	
BJM_OCALL {@BELL@***[0;1;37m
!W%s %s[32m '™¢â§œ ' «¦ §¦¤«á¨ ©£˜.!)
[0;1m} T User calls


	what player sees when folds
	
BJM_YFOLD {@BELL@***[0;1;32m
!Wá«œ '§á©¦'.!)
[0;1m} T You fold


	what other players see when a player folds

BJM_OFOLD {@BELL@***[0;1;37m
!W%s %s[32m §áœ  '§á©¦'.!)
[0;1m} T User folds


	print when player enters BJ POT
	
BJM_SEEPOT {[0;1;32m
!W’¦ ©¬¤¦¢ ¡æ §¦©æ §¦¬ ™¨å©¡œ«˜  ©«¦ «¨˜§â  œå¤˜  [37m%i[32m £¦¤á›œª.!)
[0;1m} T Total bets 


	print when current player enteres BJ TURN
	
BJM_YTURN {***[0;1;32m
!W„å¤˜   [37m©œ ¨á ©˜ª[32m ¤˜ §˜å¥œ«œ.!)
[0;1m} T Your turn to play


	print when not current user enters BJ TURN
	
BJM_OTURN {***[0;1;32m
!W„å¤˜   ©œ ¨á «¦¬ §˜å¡« [37m%s[32m ¤˜ §˜å¥œ  «é¨˜.!)
[0;1m} T Users turn to play


	BJ SCAN line separator string
	
BJM_SCANLINE {[0;1;36m!F-
[0;1m} T Scan line separator


	BJ SCAN header string

BJM_SCANHEADER {[0;1;36m˜å¡«ª   	£¦¤á›œª	œ¤œ¨šæª	â£œ ¤œ
[0;1m} T Scan header


	BJ SCAN player record string (note parameters)
	
BJM_SCANREC 	{[0;1;32m%-10s[37m	%s	%c	%c
} T Scan player record template


	print when a player tries to fold, but it is not his turn
	
BJM_WAITFOLD {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ §á«œ '§á©©¦' «é¨˜. œ¨ £â¤œ « ©œ ¨á ©˜ª.!)
[0;1m} T Cannot fold wait turn


	print when a player tries to fold, but status is hitting
	
BJM_CNTFOLD {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ §á«œ '§á©©¦' «é¨˜. €¤ Ÿâ¢œ«œ £œå¤œ«œ £œ «˜ ­ç¢˜ §¦¬ œ®œ«œ.!)
[0;1m} T Cannot fold stay only


	print when a player tries to hit a card, but it is not his turn
	
BJM_WAITHIT {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ §á¨œ«œ ¤â˜ ¡á¨«˜ «é¨˜. œ¨ £â¤œ«œ « ©œ ¨á ©˜ª.!)
[0;1m} T Cannot hit wait turn


	print when a player tries to hit a card, but status is betting
	
BJM_CNTHIT {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ §á¨œ«œ ­ç¢¢¦ «é¨˜. œ¨ £â¤œ«œ £â®¨  ¤˜ ¦¢¦¡¢¨àŸ¦ç¤ «˜
§¦¤«˜¨å©£˜«˜.!)
[0;1m} T Cannot hit wait until betting is over


	what player sees when he hits a new card
	
BJM_YHIT {@BELL@***[0;1;32m
!W˜å¨¤œ«œ â¤˜ ­ç¢¢¦.!)
%s
[0;1m} T Take card


	what other players see when a player hits a new card
	
BJM_OHIT {@BELL@***[0;1;37m
!W%s %s[32m §˜å¨¤œ  â¤˜ ­ç¢¢¦.!)
[0;1m} T User takes card


	what player sees when he exceeds 21
	
BJM_YBURN {@BELL@***[0;1;33m
!Wœ§œ¨á©˜«œ «¦ 21. ‰˜ã¡˜«œ...!)
[0;1m} T You burn


	what other players see when a player exceeds 21
	
BJM_OBURN {@BELL@***[0;1;37m
!W%s %s[33m ¥œ§â¨˜©œ «¦ 21 ¡˜  ¡á¡œ.!)
[0;1m} T User burned


	print when player tries to hand and has no cards
	
BJM_NOCARDS {@BELL@***[0;1;31m
!Wƒœ¤ â®œ«œ ­ç¢¢˜ ©«˜ ®â¨ ˜ ©˜ª.!)
[0;1m} T No cards in hand


	player's cards sum
	
BJM_CARDSUM {
‘ç¤¦¢¦: %i
} T Sum


	print when a player tries to stay but it is not his turn
	
BJM_WAITSTAY {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ £œå¤œ«œ £œ «˜ ®˜¨« á ©˜ª «é¨˜. œ¨ £â¤œ«œ « ©œ ¨á ©˜ª.!)
[0;1m} T Cannot stay wait turn


	print when a player tries to stay, but current game
	status if betting
	
BJM_CNTSTAY {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ £œå¤œ«œ £œ «˜ ®˜¨« á ©˜ª «é¨˜.
œ¨ £â¤œ«œ £â®¨  ¤˜ ¦¢¦¡¢¨àŸ¦ç¤ «˜ §¦¤«˜¨å©£˜«˜.!)
[0;1m} T Cannot stay wait until betting is over


	what player sees when he stays
	
BJM_YSTAY {@BELL@***[0;1;32m
!W„¤«á¥œ , ›œ¤ §˜å¨¤œ«œ á¢¢¦ ­ç¢¢¦.!)
[0;1m} T You stay


BJM_MOF {«¦¬} T of male form lower case

BJM_FOF {«ª} T of female form lower case


	what other players see when a player stays
	
BJM_OSTAY {@BELL@***[0;1;37m
!W%s %s[32m ›œ¤ §˜å¨¤œ  á¢¢¦ ­ç¢¢¦.!)
[0;1m} T User stays


	what player sees when he wins
	
BJM_YWIN {@BELL@***[0;1;33m
[5mÛÛ[0;1;33m  ‘¬š®˜¨«ã¨ ˜, ¤ ¡ã©˜«œ!
[0;1m} T You win


	what other players see when a player wins
	
BJM_OWIN {@BELL@***[0;1;37m
!W%s %s[33m ¡â¨› ©œ «¤ §˜¨«å›˜!!)
} T User wins


	print when maximum number of players is reached

BJM_NOMOREPL {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ ©¬££œ«á©®œ«œ «é¨˜ ©«¦ §˜ ®¤å› . „®œ  ©¬£§¢¨àŸœå ¦
£âš ©«¦ª ˜¨ Ÿ£æª §˜ ¡«é¤ §¦¬ £§¦¨¦ç¤ ¤˜ §˜å¥¦¬¤.!)
[0;1m} T No more players


	what user sees when he joins game
	
BJM_YJOIN {@BELL@***[0;1;33m
!Wƒ¢é©˜«œ ©¬££œ«¦®ã š ˜ «¤ œ§æ£œ¤ §˜¨«å›˜ Black Jack!!)
[0;1m} T You join


	what other players see when a user joins the game
	
BJM_OJOIN {@BELL@***[0;1;37m
!W%s %s[32m ›ã¢à©œ ©¬££œ«¦®ã š ˜ «¤ œ§æ£œ¤ §˜¨«å›˜ Black Jack!!)
[0;1m} T User joins


	what player sees when enters a game command, but no game is 
	currently active
	
BJM_NOGAME {@BELL@***[0;1;31m
!W¨¦ª «¦ §˜¨æ¤ ›œ¤ §˜åœ«˜  ¡˜£ á §˜¨«å›˜.
˜¨˜¡˜¢é §œ¨ £â¤œ«œ £â®¨  ¤˜ ¥œ¡ ¤ã©œ   œ§æ£œ¤.!)
[0;1m} T No game playing


	what player sees when he receives credits
	
BJM_YGETCRED {@BELL@***[0;1;33m
!WŠ˜£™á¤œ«œ [37m%i[33m £¦¤á›œª.!)
[0;1m} T You get credits


	what other players see when a player receive credits
	
BJM_OGETCRED {@BELL@***[0;1m
!W%s %s[33m ¢˜£™á¤œ  [37m%i[33m £¦¤á›œª.!)
[0;1m} T User gets credits


	print when a player tries to join more than once
	
BJM_MULTJOIN {@BELL@***[0;1;31m
!W„®œ«œ ã› ›¢é©œ  ©¬££œ«¦®ã š ˜ «¤ œ§æ£œ¤ §˜¨«å›˜ Black Jack!!)
[0;1m} T Already joined


	what player sees when he leaves game
	
BJM_YOFF {@BELL@***[0;1;33m
!W„¤«á¥œ , œš¡˜«˜¢œå§œ«œ «¦ §˜ ®¤å› .!)
[0;1m} T You leave


	what other players see when a player leaves game
	
BJM_OOFF {@BELL@***[0;1m
!W%s %s[33m œš¡˜«â¢œ ¯œ «¦ §˜ ®¤å› .!)
[0;1m} T User left


	broadcast this message when plugin watchdog timer has expried
	

BJM_INACTIVITY {} T Plugin inactive


	print when a user is wasting time
	
BJM_TICK {@BELL@***[0;1;33m
!W˜¨˜¡˜¢é ™ ˜©«œå«œ.   á¢¢¦  §˜å¡«œª §œ¨ £â¤¦¬¤.!)
[0;1m} T Please hurry


	print to inform that more players need to start game
	
BJM_WAITMORE {@BELL@***[0;1;33m
!W† œ§æ£œ¤ §˜¨«å›˜ Black Jack Ÿ˜ ¥œ¡ ¤ã©œ  £æ¢ ª ›¢é©¦¬¤ ©¬££œ«¦®ã
[37m%i[33m á«¦£˜.!)
[0;1m} T Wait for more players


	print to inform that a new game will start in some time
	
BJM_START {@BELL@***[0;1;33m
!W† œ§æ£œ¤ §˜¨«å›˜ Black Jack Ÿ˜ ¥œ¡ ¤ã©œ  ©œ [37m%i[33m ›œ¬«œ¨æ¢œ§«˜.!)
[0;1m} T New game soon


	print to inform that a new game will start right now
	
BJM_STARTNOW {@BELL@***[0;1;33m
!W† œ§æ£œ¤ §˜¨«å›˜ Black Jack ¥œ¡ ¤áœ  «é¨˜.!)
[0;1m} T New game now


BJM_MINACTIVE {˜¤œ¤œ¨šæª} T Inactive, male form
BJM_FINACTIVE {˜¤œ¤œ¨šã} T Inactive, female form


	warning message if a user wastes time
	
BJM_WARNEXP {@BELL@***[0;1;31m
!W˜¨˜£œå¤˜«œ %s š ˜ §¦¢ç é¨˜.!)
[0;1m} T Inactive for long time


	what player sees when warning message counter exceeds limit, 
	player is forced to fold
	
BJM_YFORCEFOLD {@BELL@***
!W[0;1;31m“§¦®¨œé¤œ©«œ ¤˜ §á«œ '§á©¦' š ˜ ¤˜ ©¬¤œ® ©«œå «¦ §˜ ®¤å› .!)
[0;1m} T You forced to fold


	what other players see when players warning message counter exceeds limit,
	player is forced to fold

BJM_OFORCEFOLD {@BELL@***[0;1m
!W%s %s[33m §˜¨â£œ ¤œ %s š ˜ §¦¢ç é¨˜.
“§¦®¨œé¤œ«˜  ¤˜ §áœ  '§á©¦' š ˜ ¤˜ ©¬¤œ® ©«œå «¦ §˜ ®¤å› .!)
} T User forced to fold


	what player sees when warning message counter exceeds limit, 
	player is forced to stay

BJM_YFORCESTAY {@BELL@***
!W[0;1;31m“§¦®¨œé¤œ©«œ ¤˜ £œå¤œ«œ £œ «˜ ®˜¨« á ©˜ª.!)
[0;1m} T You forced to stay


	what other players see when players warning message counter exceeds limit,
	player is forced to stay

BJM_OFORCESTAY {@BELL@***[0;1m
!W%s %s[33m §˜¨â£œ ¤œ %s š ˜ §¦¢ç é¨˜.
“§¦®¨œé¤œ«˜  ¤˜ £œå¤œ  £œ «˜ ®˜¨« á §¦¬ â®œ  š ˜ ¤˜ ©¬¤œ® ©«œå «¦ §˜ ®¤å› .!)
} T User forced to stay


BJM_SMTHE {o} T article, male form singular
BJM_SFTHE {} T article, female form singular

BJM_SWON {Œå¡©œ} T Won, singular form
BJM_PWON {Œå¡©˜¤} T Won, plural form

BJM_AND {¡˜ } T and


	winners template (do not change)

BJM_WINNERS {@BELL@***[0;1;33m
%s%s!

To áŸ¨¦ ©£˜ ã«˜¤ [37m%i[0;1;33m.
[0;1m} T Winners template

BJM_WINSUM {[0;1;32m
!W’¦ áŸ¨¦ ©£˜ ã«˜¤ [37m%i1[[32m.!)
[0;1m} T Winning sum


BJM_PLNOINTELE {@BELL@***
!WPlayer %s not in teleconference.!)
} T Player not in teleconf/channel



	print when force a player to quit

BJM_OFORCEOFF {@BELL@***[0;1;33m
!W%s %s[37m ˜§¦™á¢¢œ«˜ , ¢æšà ˜›¨á¤œ ˜ª, ˜§æ «¦ §˜ ®¤å› .!)
[0;1m} T Player forced to quit


	help message

BJM_HELP {[0;1;31m
!Jœ¨¤é¤«˜ª «¦ ­ç¢˜¡˜ «ª §æ¨«˜ª ©«¦ ™áŸ¦ª ¡˜  ˜¤¦åš¦¤«áª «¤ £§˜å¤œ«œ ©«¦
£¬©« ¡æ ›à£˜« á¡  §¦¬ œå¤˜  šœ£á«¦ ¡æ©£¦, ¡˜§¤¦çª ¡˜  §¨á© ¤˜ «¨˜§â ˜...
"†¨Ÿœ  é¨˜ š ˜ ¤˜ ¡œ¨›å©¦¬£œ ¢åš˜ ¢œ­«á" ©¡â­«œ©«œ, ¡˜  §¢© áœ«œ â¤˜
˜§æ ˜¬«á. à«é¤«˜ª «  §˜ ®¤å›  â®œ  ©«¨àŸœå ©«¦ «¨˜§â ,  ˜§á¤«© œå¤˜ :
!)
!C[0;1mBlackjack[0;1;31m
                             
!L  œ¤«¦¢âª §¦¬ £§¦¨œå«œ ¤˜ ›é©œ«œ œå¤˜  ¦  §˜¨˜¡á«à:!)

[33mbj on[37m . . .  ƒã¢à© ©¬££œ«¦®ãª
[33mbj off[37m . . . š˜å¤œ«œ ˜§æ «¦ §˜ ®¤å› 

[33mbj hand[37m . .  „£­á¤ © «à¤ ®˜¨« é¤     [33mbj pot[37m  . . . „£­á¤ © §¦¤«˜¨ ©£á«à¤
[33mbj bet #[37m . . ¦¤«á¨œ«œ                [33mbj raise #[37m .  €¤œ™áœ«œ «¦ §¦¤«á¨ ©£˜
[33mbj fold[37m . .  á«œ §á©©¦               [33mbj call[37m . . . "¢â§œ«œ" «¦ §¦¤«á¨ ©£˜
[33mbj stay[37m  . . ‹â¤œ«œ £œ «˜ ®˜¨« á ©˜ª  [33mbj hit[37m . . .  ˜å¨¤œ«œ ¡ 'á¢¢¦ ®˜¨«å
[33mbj turn[37m . .  ¦ ˜¤¦ç œå¤˜   ©œ ¨á    [33mbj scan[37m . . . „£­á¤ © «à¤ §˜ ¡«é¤  

[33mbj help[37m . .  „£­á¤ © ™¦Ÿœå˜ª
[33mbj rules[37m . . €¤˜¢¬« ¡¦å ¡˜¤æ¤œª š ˜ «¦ §˜ ®¤å› 
[33mbj info[37m . .  „£­á¤ © §¢¨¦­ ¨ é¤ š ˜ «¦ §¨æš¨˜££˜
[33mbj bell[37m  . . „¤œ¨š¦§¦å©/€§œ¤œ¨š¦§¦å© «¦¬ ®« ¡¦ç ©ã£˜«¦ª

[0;1m} T Help message


BJM_RULES {
!C[0;1;32m‰˜¤æ¤œª!)

!J[37m‚ ˜ ¤˜ ¥œ¡ ¤ã©œ  £ ˜ §˜¨«å›˜ BlackJack ˜§˜ «¦ç¤«˜  «¦¬¢á® ©«¦¤
[32m%i[37m §˜å¡«œª. ‰áŸœ ¤â˜ §˜¨«å›˜ ¥œ¡ ¤áœ  [32m%i[37m ›œ¬«œ¨æ¢œ§«˜
˜­æ«¦¬ ©¬£§¢¨àŸœå ¦ §˜¨˜§á¤à ˜¨ Ÿ£æª.!)

!J€¤ ›œ¤ §˜å¥œ«œ £â©˜ ©œ [32m%i[37m ›œ¬«œ¨æ¢œ§«˜ ¢˜£™á¤œ«œ £ ˜
§¨¦œ ›¦§¦å©. €¤ ›œ®«œå«œ [32m%i[37m §¨¦œ ›¦§¦ ã©œ ª «æ«œ ®á¤œ«œ « ©œ ¨á
©˜ª. [33m’ ›œç«œ¨ ­¦¨á §¦¬ Ÿ˜ ®á©œ«œ « ©œ ¨á ©˜ª, ˜§¦™á¢¢œ©«œ ˜§æ «¦
§˜ ®¤å› ![37!)

!J’¦ BlackJack œå¤˜  «¦ š¤à©«æ 21, ©«¦ ¦§¦å¦ ¦  §˜å¡«œª ©¬¤˜šà¤å¦¤«˜ 
£œ«˜¥ç «¦¬ª š ˜ ¤˜ ¡œ¨›å©¦¬¤ «˜ ¢œ­«á §¦¬ â®¦¬¤ §¦¤«˜¨ ©«œå ˜§æ æ©¦¬ª
©¬££œ«â®¦¬¤. ‘«¤ ˜¨®ã «¦¬ §˜ ®¤ › ¦ç æ¢¦  ¦  §˜å¡«œª ¢˜£™á¤¦¬¤ ›ç¦ ­ç¢¢˜,
¡˜  «¦¬ª ˜­˜ ¨œå«˜  š ˜ « ©¬££œ«¦®ã «¦¬ª ©«¦ §˜ ®¤å›  ¡á§¦ ¦ §¦©æ. ‘«
©¬¤â®œ ˜ ¥œ¡ ¤áœ   ­á© «à¤ §¦¤«˜¨ ©£á«à¤, æ§¦¬ ¦ ¡áŸœ §˜å¡«ª §¦¤«á¨œ  «¦
˜¤á¢¦š¦ §¦©æ ã §áœ  '§á©¦'. €­¦ç ¦¢¦¡¢¨àŸ¦ç¤ «˜ §¦¤«˜¨å©£˜«˜, ¦ ¡áŸœ
§˜å¡«ª £œ « ©œ ¨á â®œ  «¦ › ¡˜åà£˜ ¤˜ «¨˜™ã¥œ  ­ç¢¢˜, £œ ©¡¦§æ ¤˜
§¢© á©œ  æ©¦ £§¦¨œå «¦ 21, ®à¨åª æ£àª ¤˜ «¦ ¥œ§œ¨á©œ . §¦ ¦ª ¥œ§œ¨á©œ  «¦
21 '¡˜åšœ«˜ ' ¡˜  ®á¤œ . Œ ¡ã«ª œå¤˜  ˜¬«æª §¦¬ â®œ  «¦ £œš˜¢ç«œ¨¦ áŸ¨¦ ©£˜
­ç¢¢à¤, ¡˜  ˜¬«æª §˜å¨¤œ  æ¢¦ «¦ §¦©æ §¦¬ â®œ  §¦¤«˜¨ ©«œå. €¤ ¬§á¨¥¦¬¤
§œ¨ ©©æ«œ¨¦  ˜§æ â¤˜ª ¤ ¡«âª, «¦ §¦©æ ˜¬«æ £¦ ¨áœ«˜ . ‘«¦¤ ¬§¦¢¦š ©£æ «¦¬
˜Ÿ¨¦å©£˜«¦ª ¦ á©©¦ª £œ«¨áœ  š ˜ 11, œ¤é ˜¤ ¦ §˜å¡«ª â®œ  §á¨œ 
§œ¨ ©©æ«œ¨¦¬ª ˜§æ â¤˜¤ á©©¦¬ª, ˜¬«¦å £œ«¨á¤œ š ˜ 1.!)

[0;1m} T Rules message

BJM_INFO {
[0;1;32m%s[37m

!J‰é› ¡˜ª ˜§æ «¦¤ ˜ššâ¢ æ¡˜ š ˜ «¦ ›å¡«¬¦ [0;32mAcroBase[37m ¡˜ 
[32mG.A.T.E.[37m ’¦ §˜¨é¤ module ©¬¤œ¨šáœ«˜  £œ «¦ §¨æš¨˜££˜
[32m‹œš ©«¦ª[37m ¡˜  › ˜¤â£œ«˜  ¬§æ «¦¬ª æ¨¦¬ª «ª [32mGNU General Public
License[37m. ƒé©«œ [33m/gpl[37m š ˜ §œ¨ ©©æ«œ¨œª ¢œ§«¦£â¨œ œª.!)

!J‚ ˜ ¦§¦ ˜›ã§¦«œ §¢¨¦­¦¨å˜, œ§ ¡¦ ¤à¤ã©«œ £œ «¦ £â¢¦ª [32mValis[37m.!)

[0;1m} T Info text


BJM_CARD_TOP_BLACK {[0;30;47mÚÄÄÄÄÄÄÄ¿[0m } T All black cards, top line (1/7)
BJM_CARD_BOTTOM_BLACK {[0;30;47mÀÄÄÄÄÄÄÄÙ[0m } T All black cards, bottom line (7/7)

BJM_CARD_L2B2 {[0;30;47m³2      ³[0m } T 2 black, line 2/5
BJM_CARD_L3B2 {[0;30;47m³   !   ³[0m } T 2 black, line 3/5
BJM_CARD_L4B2 {[0;30;47m³       ³[0m } T 2 black, line 4/5
BJM_CARD_L5B2 {[0;30;47m³   !   ³[0m } T 2 black, line 5/5
BJM_CARD_L6B2 {[0;30;47m³      2³[0m } T 2 black, line 6/5

BJM_CARD_L2B3 {[0;30;47m³3      ³[0m } T 3 black, line 2/5
BJM_CARD_L3B3 {[0;30;47m³   !   ³[0m } T 3 black, line 3/5
BJM_CARD_L4B3 {[0;30;47m³   !   ³[0m } T 3 black, line 4/5
BJM_CARD_L5B3 {[0;30;47m³   !   ³[0m } T 3 black, line 5/5
BJM_CARD_L6B3 {[0;30;47m³      3³[0m } T 3 black, line 6/5

BJM_CARD_L2B4 {[0;30;47m³4      ³[0m } T 4 black, line 2/5
BJM_CARD_L3B4 {[0;30;47m³  ! !  ³[0m } T 4 black, line 3/5
BJM_CARD_L4B4 {[0;30;47m³       ³[0m } T 4 black, line 4/5
BJM_CARD_L5B4 {[0;30;47m³  ! !  ³[0m } T 4 black, line 5/5
BJM_CARD_L6B4 {[0;30;47m³      4³[0m } T 4 black, line 6/5

BJM_CARD_L2B5 {[0;30;47m³5      ³[0m } T 5 black, line 2/5
BJM_CARD_L3B5 {[0;30;47m³  ! !  ³[0m } T 5 black, line 3/5
BJM_CARD_L4B5 {[0;30;47m³   !   ³[0m } T 5 black, line 4/5
BJM_CARD_L5B5 {[0;30;47m³  ! !  ³[0m } T 5 black, line 5/5
BJM_CARD_L6B5 {[0;30;47m³      5³[0m } T 5 black, line 6/5

BJM_CARD_L2B6 {[0;30;47m³6      ³[0m } T 6 black, line 2/5
BJM_CARD_L3B6 {[0;30;47m³  ! !  ³[0m } T 6 black, line 3/5
BJM_CARD_L4B6 {[0;30;47m³  ! !  ³[0m } T 6 black, line 4/5
BJM_CARD_L5B6 {[0;30;47m³  ! !  ³[0m } T 6 black, line 5/5
BJM_CARD_L6B6 {[0;30;47m³      6³[0m } T 6 black, line 6/5

BJM_CARD_L2B7 {[0;30;47m³7      ³[0m } T 7 black, line 2/5
BJM_CARD_L3B7 {[0;30;47m³ !   ! ³[0m } T 7 black, line 3/5
BJM_CARD_L4B7 {[0;30;47m³ ! ! ! ³[0m } T 7 black, line 4/5
BJM_CARD_L5B7 {[0;30;47m³ !   ! ³[0m } T 7 black, line 5/5
BJM_CARD_L6B7 {[0;30;47m³      7³[0m } T 7 black, line 6/5

BJM_CARD_L2B8 {[0;30;47m³8      ³[0m } T 8 black, line 2/5
BJM_CARD_L3B8 {[0;30;47m³ ! ! ! ³[0m } T 8 black, line 3/5
BJM_CARD_L4B8 {[0;30;47m³ !   ! ³[0m } T 8 black, line 4/5
BJM_CARD_L5B8 {[0;30;47m³ ! ! ! ³[0m } T 8 black, line 5/5
BJM_CARD_L6B8 {[0;30;47m³      8³[0m } T 8 black, line 6/5

BJM_CARD_L2B9 {[0;30;47m³9      ³[0m } T 9 black, line 2/5
BJM_CARD_L3B9 {[0;30;47m³ ! ! ! ³[0m } T 9 black, line 3/5
BJM_CARD_L4B9 {[0;30;47m³ ! ! ! ³[0m } T 9 black, line 4/5
BJM_CARD_L5B9 {[0;30;47m³ ! ! ! ³[0m } T 9 black, line 5/5
BJM_CARD_L6B9 {[0;30;47m³      9³[0m } T 9 black, line 6/5

BJM_CARD_L2B10 {[0;30;47m³10 !   ³[0m } T 10 black, line 2/5
BJM_CARD_L3B10 {[0;30;47m³ ! ! ! ³[0m } T 10 black, line 3/5
BJM_CARD_L4B10 {[0;30;47m³ !   ! ³[0m } T 10 black, line 4/5
BJM_CARD_L5B10 {[0;30;47m³ ! ! ! ³[0m } T 10 black, line 5/5
BJM_CARD_L6B10 {[0;30;47m³   ! 10³[0m } T 10 black, line 6/5

BJM_CARD_L2BA {[0;30;47m³A      ³[0m } T A black, line 2/5
BJM_CARD_L3BA {[0;30;47m³       ³[0m } T A black, line 3/5
BJM_CARD_L4BA {[0;30;47m³   !   ³[0m } T A black, line 4/5
BJM_CARD_L5BA {[0;30;47m³       ³[0m } T A black, line 5/5
BJM_CARD_L6BA {[0;30;47m³      A³[0m } T A black, line 6/5

BJM_CARD_L2BJ {[0;30;47m³J  !   ³[0m } T J black, line 2/5
BJM_CARD_L3BJ {[0;30;47m³ ! ! ! ³[0m } T J black, line 3/5
BJM_CARD_L4BJ {[0;30;47m³ !   ! ³[0m } T J black, line 4/5
BJM_CARD_L5BJ {[0;30;47m³ ! ! ! ³[0m } T J black, line 5/5
BJM_CARD_L6BJ {[0;30;47m³   !  J³[0m } T J black, line 6/5

BJM_CARD_L2BQ {[0;30;47m³Q  !   ³[0m } T Q black, line 2/5
BJM_CARD_L3BQ {[0;30;47m³ ! ! ! ³[0m } T Q black, line 3/5
BJM_CARD_L4BQ {[0;30;47m³ !   ! ³[0m } T Q black, line 4/5
BJM_CARD_L5BQ {[0;30;47m³ ! ! ! ³[0m } T Q black, line 5/5
BJM_CARD_L6BQ {[0;30;47m³   !  Q³[0m } T Q black, line 6/5

BJM_CARD_L2BK {[0;30;47m³K  !   ³[0m } T K black, line 2/5
BJM_CARD_L3BK {[0;30;47m³ ! ! ! ³[0m } T K black, line 3/5
BJM_CARD_L4BK {[0;30;47m³ !   ! ³[0m } T K black, line 4/5
BJM_CARD_L5BK {[0;30;47m³ ! ! ! ³[0m } T K black, line 5/5
BJM_CARD_L6BK {[0;30;47m³   !  K³[0m } T K black, line 6/5



BJM_CARD_TOP_RED {[0;31;47mÚÄÄÄÄÄÄÄ¿[0m } T All red cards, top line (1/7)
BJM_CARD_BOTTOM_RED {[0;31;47mÀÄÄÄÄÄÄÄÙ[0m } T All red cards, bottom line (7/7)

BJM_CARD_L2R2 {[0;31;47m³2      ³[0m } T 2 red, line 2/5
BJM_CARD_L3R2 {[0;31;47m³   !   ³[0m } T 2 red, line 3/5
BJM_CARD_L4R2 {[0;31;47m³       ³[0m } T 2 red, line 4/5
BJM_CARD_L5R2 {[0;31;47m³   !   ³[0m } T 2 red, line 5/5
BJM_CARD_L6R2 {[0;31;47m³      2³[0m } T 2 red, line 6/5

BJM_CARD_L2R3 {[0;31;47m³3      ³[0m } T 3 red, line 2/5
BJM_CARD_L3R3 {[0;31;47m³   !   ³[0m } T 3 red, line 3/5
BJM_CARD_L4R3 {[0;31;47m³   !   ³[0m } T 3 red, line 4/5
BJM_CARD_L5R3 {[0;31;47m³   !   ³[0m } T 3 red, line 5/5
BJM_CARD_L6R3 {[0;31;47m³      3³[0m } T 3 red, line 6/5

BJM_CARD_L2R4 {[0;31;47m³4      ³[0m } T 4 red, line 2/5
BJM_CARD_L3R4 {[0;31;47m³  ! !  ³[0m } T 4 red, line 3/5
BJM_CARD_L4R4 {[0;31;47m³       ³[0m } T 4 red, line 4/5
BJM_CARD_L5R4 {[0;31;47m³  ! !  ³[0m } T 4 red, line 5/5
BJM_CARD_L6R4 {[0;31;47m³      4³[0m } T 4 red, line 6/5

BJM_CARD_L2R5 {[0;31;47m³5      ³[0m } T 5 red, line 2/5
BJM_CARD_L3R5 {[0;31;47m³  ! !  ³[0m } T 5 red, line 3/5
BJM_CARD_L4R5 {[0;31;47m³   !   ³[0m } T 5 red, line 4/5
BJM_CARD_L5R5 {[0;31;47m³  ! !  ³[0m } T 5 red, line 5/5
BJM_CARD_L6R5 {[0;31;47m³      5³[0m } T 5 red, line 6/5

BJM_CARD_L2R6 {[0;31;47m³6      ³[0m } T 6 red, line 2/5
BJM_CARD_L3R6 {[0;31;47m³  ! !  ³[0m } T 6 red, line 3/5
BJM_CARD_L4R6 {[0;31;47m³  ! !  ³[0m } T 6 red, line 4/5
BJM_CARD_L5R6 {[0;31;47m³  ! !  ³[0m } T 6 red, line 5/5
BJM_CARD_L6R6 {[0;31;47m³      6³[0m } T 6 red, line 6/5

BJM_CARD_L2R7 {[0;31;47m³7      ³[0m } T 7 red, line 2/5
BJM_CARD_L3R7 {[0;31;47m³ !   ! ³[0m } T 7 red, line 3/5
BJM_CARD_L4R7 {[0;31;47m³ ! ! ! ³[0m } T 7 red, line 4/5
BJM_CARD_L5R7 {[0;31;47m³ !   ! ³[0m } T 7 red, line 5/5
BJM_CARD_L6R7 {[0;31;47m³      7³[0m } T 7 red, line 6/5

BJM_CARD_L2R8 {[0;31;47m³8      ³[0m } T 8 red, line 2/5
BJM_CARD_L3R8 {[0;31;47m³ ! ! ! ³[0m } T 8 red, line 3/5
BJM_CARD_L4R8 {[0;31;47m³ !   ! ³[0m } T 8 red, line 4/5
BJM_CARD_L5R8 {[0;31;47m³ ! ! ! ³[0m } T 8 red, line 5/5
BJM_CARD_L6R8 {[0;31;47m³      8³[0m } T 8 red, line 6/5

BJM_CARD_L2R9 {[0;31;47m³9      ³[0m } T 9 red, line 2/5
BJM_CARD_L3R9 {[0;31;47m³ ! ! ! ³[0m } T 9 red, line 3/5
BJM_CARD_L4R9 {[0;31;47m³ ! ! ! ³[0m } T 9 red, line 4/5
BJM_CARD_L5R9 {[0;31;47m³ ! ! ! ³[0m } T 9 red, line 5/5
BJM_CARD_L6R9 {[0;31;47m³      9³[0m } T 9 red, line 6/5

BJM_CARD_L2R10 {[0;31;47m³10 !   ³[0m } T 10 red, line 2/5
BJM_CARD_L3R10 {[0;31;47m³ ! ! ! ³[0m } T 10 red, line 3/5
BJM_CARD_L4R10 {[0;31;47m³ !   ! ³[0m } T 10 red, line 4/5
BJM_CARD_L5R10 {[0;31;47m³ ! ! ! ³[0m } T 10 red, line 5/5
BJM_CARD_L6R10 {[0;31;47m³   ! 10³[0m } T 10 red, line 6/5

BJM_CARD_L2RA {[0;31;47m³A      ³[0m } T A red, line 2/5
BJM_CARD_L3RA {[0;31;47m³       ³[0m } T A red, line 3/5
BJM_CARD_L4RA {[0;31;47m³   !   ³[0m } T A red, line 4/5
BJM_CARD_L5RA {[0;31;47m³       ³[0m } T A red, line 5/5
BJM_CARD_L6RA {[0;31;47m³      A³[0m } T A red, line 6/5

BJM_CARD_L2RJ {[0;31;47m³J  !   ³[0m } T J red, line 2/5
BJM_CARD_L3RJ {[0;31;47m³ ! ! ! ³[0m } T J red, line 3/5
BJM_CARD_L4RJ {[0;31;47m³ !   ! ³[0m } T J red, line 4/5
BJM_CARD_L5RJ {[0;31;47m³ ! ! ! ³[0m } T J red, line 5/5
BJM_CARD_L6RJ {[0;31;47m³   !  J³[0m } T J red, line 6/5

BJM_CARD_L2RQ {[0;31;47m³Q  !   ³[0m } T Q red, line 2/5
BJM_CARD_L3RQ {[0;31;47m³ ! ! ! ³[0m } T Q red, line 3/5
BJM_CARD_L4RQ {[0;31;47m³ !   ! ³[0m } T Q red, line 4/5
BJM_CARD_L5RQ {[0;31;47m³ ! ! ! ³[0m } T Q red, line 5/5
BJM_CARD_L6RQ {[0;31;47m³   !  Q³[0m } T Q red, line 6/5

BJM_CARD_L2RK {[0;31;47m³K  !   ³[0m } T K red, line 2/5
BJM_CARD_L3RK {[0;31;47m³ ! ! ! ³[0m } T K red, line 3/5
BJM_CARD_L4RK {[0;31;47m³ !   ! ³[0m } T K red, line 4/5
BJM_CARD_L5RK {[0;31;47m³ ! ! ! ³[0m } T K red, line 5/5
BJM_CARD_L6RK {[0;31;47m³   !  K³[0m } T K red, line 6/5


LANG {}

	string constant to print various hardcoded strings (will be removed)

BJM_STRING {%s} T String template


	print when starting a new game

BJM_NEWGAME {@BELL@***
!W[0;1;36mA new game of Blackjack just started.!)
[0;1m} T New game just began


	print when a user entered a BJ command, but he is not
	participating to the game (eg. has not given BJ ON)
	
BJM_NOPART {@BELL@***
!W[0;1;31mYou're not in this game.!)
[0;1m} T No participation

BJM_BELLACT {activated} T activated
BJM_BELLDEACT {deactivated} T deactivated

BJM_BELL {@BELL@***
!W[0;1;32mBell notification [37m%s[32m.!)
[0;1m} T Bell notice

BJM_CREDIT {credit} T credit, singular
BJM_CREDITS {credits} T credits, plural


	print when starting game, credits have been taken, and two cards are dealed

BJM_LIGHT {***
!W[0;1m%i[32m credits were charged to your account.
You're handed two cards.!)
[0;1m} T Starting game

	fatal error message, when we cannot deallocate user memory

BJM_CNTDEALLOC {@BELL@***


FATAL ERROR: Could not deallocate user memory

} T Fatal error


	print when no winner found

BJM_NOWINNER {@BELL@***
!W[0;1;33mNo winner!!)
[0;1m} T No winner


	print when all players folded

BJM_ALLQUIT {@BELL@***
!W[0;1;33mAll players have abandoned the game. No winner!!)
[0;1m} T All folded


	print when betting is over, and players start hitting cards
	
BJM_BEGHIT {@BELL@***
!W[0;1;32mBetting is over.!)
[0;1m} T Hitting is over


	print when an unknown command is given

BJM_ERCMD {@BELL@***
!W[0;1;31mSorry, your command was not recognised.!)
[0;1m} T Error command


	print when a player enters a bet command but its is not his turn
BJM_WAITBET {@BELL@***
!W[0;1;31mYou can't bet now. Please wait your turn.!)
[0;1m} T Wait turn to bet


	print when player enters a bet command, but the current game 
	state is not betting
	
BJM_CNTBET {@BELL@***
!W[0;1;31mYou can't bet now. Betting is over.!)
[0;1m} T Cannot bet betting is over


	print when it is the players turn to bet
	
BJM_YTURNBET {***
!W[0;1;32mIt's your turn to bet.!)
[0;1m} T Your turn to bet


	print when it is the players turn to hit a card
	
BJM_YTURNHIT {***[0;1;32m
!WIt's your turn to play.!)
[0;1m} T Your turn to hit


	what player sees when he has betted an amount of credits
	
BJM_YBETCRED {@BELL@***
!W[0;1;32mYou bet [37m%i[32m credits.!)
[0;1m} T 


BJM_MPLAYER {} T player male form capital
BJM_FPLAYER {} T player female form capital


	what other players see when a player has betted an amount of credits
	
BJM_OBETCRED {@BELL@***
!W[0;1;37m%s%s[32m just bet [37m%i[32m credits.!)
[0;1m} T User has placed their bet


	print when player tries to bet less credits than the
	current bet
	
BJM_MINBET {@BELL@***
!W[0;1;31mYou can't bet less than [37m%i[32m credits.!)
[0;1m} T Cannot bet so little


	print when player has not enough credits to bet
	
BJM_NOCRED {@BELL@***
!W[0;1;31mYou don't have enough credits to bet.!)
[0;1m} T Not enough credits


	print when a player tries to bet more than the allowed limit
	
BJM_TOOHIGH {@BELL@***[0;1;31m
!WYou can't bet any more than [37m%i[31m credits.!)
[0;1;m} T Bet is too high


	print when a player tries to bet a negative amount
	
BJM_TOOLOW {@BELL@***[0;1;31m
!WYou must bet at least [37mone[37m credit!!)
[0;1;m} T Bet is too low



	print when a player tries to raise the bet, but it is not his turn
	
BJM_WAITRAISE {@BELL@***[0;1;31m
!Wƒœ¤ £§¦¨œå«œ ¤˜ ˜¤œ™á©œ«œ «¦ §¦¤«á¨ ©£˜ «é¨˜. œ¨ £â¤œ«œ « ©œ ¨á ©˜ª.!)
[0;1m} T Cannot raise wait turn


	print when a player tries to raise the bet but current game state
	is not betting
	
BJM_CNTRAISE {@BELL@***[0;1;31m
!WYou can't raise the bet now. Betting's over.!)
[0;1m} T Cannot raise betting over


	what player sees when he raises a bet
	
BJM_YRAISE {@BELL@***[0;1;32m
!WOkay, you see the bet and raise [37m%i[32m credits.!)
[0;1m} T You raise


	what other players see when a player raises the bet
	
BJM_ORAISE {@BELL@***[0;1;37m
!W%s%s[32m sees the bet and raises [37m%i[32m credits.!)
[0;1m} T User raises 


	print when a user tries to call a bet but it is not his turn
		
BJM_WAITCALL {@BELL@***[0;1;31m
!WYou can't see the bet right now. Please wait your turn.!)
[0;1m} T Cannot call wait turn


	print when a user tries to call a bet, but current game state
	is not betting
	
BJM_CNTCALL {@BELL@***[0;1;31m
!WYou can't see the bet right now. Betting's over.!)
[0;1m} T Cannot call bet is over


	what player sees when calls a bet
	
BJM_YCALL {@BELL@***[0;1;32m
!WOkay, you see the bet.!)
[0;1m} T You call


	what other players see when a player calls a bet
	
BJM_OCALL {@BELL@***[0;1;37m
!W%s%s[32m sees the bet.!)
[0;1m} T User calls


	what player sees when folds
	
BJM_YFOLD {@BELL@***[0;1;32m
!WYou fold.!)
[0;1m} T You fold


	what other players see when a player folds

BJM_OFOLD {@BELL@***[0;1;37m
!W%s%s[32m folds.!)
[0;1m} T User folds


	print when player enters BJ POT
	
BJM_SEEPOT {[0;1;32m
!WThere are [37m%i[32m credits heaped on the table.!)
[0;1m} T Total bets 


	print when current player enteres BJ TURN
	
BJM_YTURN {***[0;1;32m
!WIt's [37myour turn[32m to play.!)
[0;1m} T Your turn to play


	print when not current user enters BJ TURN
	
BJM_OTURN {***[0;1;32m
!W[37m%s[32m is currently playing.!)
[0;1m} T Users turn to play


	BJ SCAN line separator string
	
BJM_SCANLINE {[0;1;36m!F-
[0;1m} T Scan line separator


	BJ SCAN header string

BJM_SCANHEADER {[0;1;36mPlayer    	credits	active 	stay
[0;1m} T Scan header


	BJ SCAN player record string (note parameters)
	
BJM_SCANREC 	{[0;1;32m%-10s[37m	%s	%c	%c
} T Scan player record template


	print when a player tries to fold, but it is not his turn
	
BJM_WAITFOLD {@BELL@***[0;1;31m
!WYou can't fold now. Please wait for your turn.!)
[0;1m} T Cannot fold wait turn


	print when a player tries to fold, but status is hitting
	
BJM_CNTFOLD {@BELL@***[0;1;31m
!WYou can't fold now. You can only stay with your current hand.!)
[0;1m} T Cannot fold stay only


	print when a player tries to hit a card, but it is not his turn
	
BJM_WAITHIT {@BELL@***[0;1;31m
!WYou can't have a fresh card now. Please wait for your turn.!)
[0;1m} T Cannot hit wait turn


	print when a player tries to hit a card, but status is betting
	
BJM_CNTHIT {@BELL@***[0;1;31m
!WYou can't have a fresh card now. Please wait until betting is over.!)
[0;1m} T Cannot hit wait until betting is over


	what player sees when he hits a new card
	
BJM_YHIT {@BELL@***[0;1;32m
!WYou get a card.!)
%s
[0;1m} T Take card


	what other players see when a player hits a new card
	
BJM_OHIT {@BELL@***[0;1;37m
!W%s%s[32m gets a new card.!)
[0;1m} T User takes card


	what player sees when he exceeds 21
	
BJM_YBURN {@BELL@***[0;1;33m
!WYou've passed 21. You lose...!)
[0;1m} T You burn


	what other players see when a player exceeds 21
	
BJM_OBURN {@BELL@***[0;1;37m
!W%s%s[33m passed 21 and has lost.!)
[0;1m} T User burned


	print when player tries to hand and has no cards
	
BJM_NOCARDS {@BELL@***[0;1;31m
!WYou have no cards.!)
[0;1m} T No cards in hand


	player's cards sum
	
BJM_CARDSUM {
Total: %i
} T Sum


	print when a player tries to stay but it is not his turn
	
BJM_WAITSTAY {@BELL@***[0;1;31m
!WYou can't stay now. Please wait for your turn.!)
[0;1m} T Cannot stay wait turn


	print when a player tries to stay, but current game
	status if betting
	
BJM_CNTSTAY {@BELL@***[0;1;31m
!WYou can't stay now. Please wait till betting is over.!)
[0;1m} T Cannot stay wait until betting is over


	what player sees when he stays
	
BJM_YSTAY {@BELL@***[0;1;32m
!WOkay, you stay.!)
[0;1m} T You stay


BJM_MOF {} T of male form lower case

BJM_FOF {} T of female form lower case


	what other players see when a player stays
	
BJM_OSTAY {@BELL@***[0;1;37m
!W%s%s[32m stays.!)
[0;1m} T User stays


	what player sees when he wins
	
BJM_YWIN {@BELL@***[0;1;33m
[5mÛÛ[0;1;33m  Congratulations, you win!
[0;1m} T You win


	what other players see when a player wins
	
BJM_OWIN {@BELL@***[0;1;37m
!W%s%s[33m won the game!!)
} T User wins


	print when maximum number of players is reached

BJM_NOMOREPL {@BELL@***[0;1;31m
!WYou can't join the game now. Too many players have already
joined.[0;1m} T No more players


	what user sees when he joins game
	
BJM_YJOIN {@BELL@***[0;1;33m
!WYou'll be joining the next Blackjack game!!)
[0;1m} T You join


	what other players see when a user joins the game
	
BJM_OJOIN {@BELL@***[0;1;37m
!W%s%s[32m will be joining the next Blackjack game!!)
[0;1m} T User joins


	what player sees when enters a game command, but no game is 
	currently active
	
BJM_NOGAME {@BELL@***[0;1;31m
!WThere's no game in progress right now. Please wait till one
starts.!)[0;1m} T No game playing


	what player sees when he receives credits
	
BJM_YGETCRED {@BELL@***[0;1;33m
!WYou get [37m%i[33m credits.!)
[0;1m} T You get credits


	what other players see when a player receive credits
	
BJM_OGETCRED {@BELL@***[0;1m
!W%s%s[33m gets [37m%i[33m credits.!)
[0;1m} T User gets credits


	print when a player tries to join more than once
	
BJM_MULTJOIN {@BELL@***[0;1;31m
!WYou've already joined the next game of Blackjack!!)
[0;1m} T Already joined


	what player sees when he leaves game
	
BJM_YOFF {@BELL@***[0;1;33m
!WOkay, you leave the game.!)
[0;1m} T You leave


	what other players see when a player leaves game
	
BJM_OOFF {@BELL@***[0;1m
!W%s%s[33m has left the game.!)
[0;1m} T User left


	broadcast this message when plugin watchdog timer has expried
	

BJM_INACTIVITY {} T Plugin inactive


	print when a user is wasting time
	
BJM_TICK {@BELL@***[0;1;33m
!WPlease hurry. Other players are waiting.!)
[0;1m} T Please hurry


	print to inform that more players need to start game
	
BJM_WAITMORE {@BELL@***[0;1;33m
!WThe next Blackjack game will start as soon as [37m%i[33m people
join.!)
[0;1m} T Wait for more players


	print to inform that a new game will start in some time
	
BJM_START {@BELL@***[0;1;33m
!WThe next Blackjack game will start in [37m%i[33m seconds.!)
[0;1m} T New game soon


	print to inform that a new game will start right now
	
BJM_STARTNOW {@BELL@***[0;1;33m
!WA Blackjack game starts.!)
[0;1m} T New game now


BJM_MINACTIVE {inactive} T Inactive, male form
BJM_FINACTIVE {inactive} T Inactive, female form


	warning message if a user wastes time
	
BJM_WARNEXP {@BELL@***[0;1;31m
!WYou've been %s for too long.!)
[0;1m} T Inactive for long time


	what player sees when warning message counter exceeds limit, 
	player is forced to fold
	
BJM_YFORCEFOLD {@BELL@***
!W[0;1;31mYou are forced to fold so the game can go on.!)
[0;1m} T You forced to fold


	what other players see when players warning message counter exceeds limit,
	player is forced to fold

BJM_OFORCEFOLD {@BELL@***[0;1m
!W%s%s[33m was inactive for too long.
They fold so the game can continue.!)
} T User forced to fold


	what player sees when warning message counter exceeds limit, 
	player is forced to stay

BJM_YFORCESTAY {@BELL@***
!W[0;1;31mYou are forced to stay.!)
[0;1m} T You forced to stay


	what other players see when players warning message counter exceeds limit,
	player is forced to stay

BJM_OFORCESTAY {@BELL@***[0;1m
!W%s%s[33m has been inactive for too long.
They are forced to stay so the game can continue.!)
} T User forced to stay


BJM_SMTHE {} T article, male form singular
BJM_SFTHE {} T article, female form singular

BJM_SWON {Won} T Won, singular form
BJM_PWON {Won} T Won, plural form

BJM_AND {and} T and


	winners template (do not change)

BJM_WINNERS {@BELL@***[0;1;33m
%s%s!

The pot was [37m%i[0;1;33m.
[0;1m} T Winners template

BJM_WINSUM {[0;1;32m
!WThe pot was [37m%i1[[32m.!)
[0;1m} T Winning sum


BJM_PLNOINTELE {@BELL@***
!WPlayer %s not in teleconference.!)
} T Player not in teleconf/channel



	print when force a player to quit

BJM_OFORCEOFF {@BELL@***[0;1;33m
!W%s%s[37m has been idle for too long and is forced to quit the game.!)
[0;1m} T Player forced to quit


	help message

BJM_HELP {[0;1;31m
!JWalking past the bouncer and through the padded door, you enter a secret
room full of people, smoke, and green-topped tables. Seeing the chance to
win some money, you approach one of the tables. You ask what game is being
played and the answer is:
!)
!C[0;1mBlackjack[0;1;31m
                             
!LThese commands are possible:!)

[33mbj on[37m . . .  Join the next game
[33mbj off[37m . . . Opt out of the next game

[33mbj hand[37m . .  Show your current hand   [33mbj pot[37m  . . . Show bets
[33mbj bet #[37m . . Bet # credits            [33mbj raise #[37m .  Raise the bet
[33mbj fold[37m . .  You fold                 [33mbj call[37m . . . Call the bet
[33mbj stay[37m  . . You stay with your hand  [33mbj hit[37m . . .  Get a new card
[33mbj turn[37m . .  Shows whose turn it is   [33mbj scan[37m . . . List the players  

[33mbj help[37m . .  This help page
[33mbj rules[37m . . Detailed instructions
[33mbj info[37m . .  Display informaton about this programme
[33mbj bell[37m  . . Activate/deactivate the bell

[0;1m} T Help message


BJM_RULES {
!C[0;1;32mInstructions and rules!)

!J[37mWe'll need at least [32m%i[37m players to start a game of
Blackjack. A new game starts [32m%i[37m seconds after enough players have
joined.!)

!JIf it's your turn to play and you remain idle for mroe than [32m%i[37m
seconds, you'll receive a warning. After [32m%i[37m warnings you lose your
turn. [33mIf this happens twice, you'll be kicked out of the game![37!)

!JIn Blackjack, players compete to win the pot of credits other players
have bet. At the beginning of the game, players get two cards and are
'taxed' for their participation. Betting starts immediately. Players can
either raise the pot or call it. When all players have placed their bets,
the game proper starts. The aim is to make the sum of your hand approach 21
as much as possible without exceeding it. A hand that sums up to more than
21 loses the game. The player with the highest sum less than or equal to 21
wins and gets the pot. If more than one players reach the same sum, they
share the pot. In counting the sum, the first ace of a hand counts for 11.
Subsequent aces are worth 1, as per usual.!)

[0;1m} T Rules message

BJM_INFO {
[0;1;32m%s[37m

!JCoding by Vangelis Rokas for the [0;32mAcroBase[37m and
[32mG.A.T.E.[37m network. This module works with [32mMegistos[37m
and is made available under the [32mGNU General Public License[37m.
Enter [33m/gpl[37m to see the license.!)

[0;1m} T Info text


LANGEND {}
