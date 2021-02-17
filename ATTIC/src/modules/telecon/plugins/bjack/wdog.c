/* Watchdog library */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <unistd.h>


#define PCHAR		'W'
#define	REQUEST		1
#define ANSWER		2

#define MAXTRIES	3
#define SLEEP		10


int     WDOGQID;		/* the watchdog communication channel           */
int     sleep_time;		/* seconds interval between check signals       */
pid_t   proc_id;		/* process id to send message                   */
int     proc_sig;		/* signal to send to proc_id                    */


void
set_params (int sl_t, pid_t pr_id, int pr_sig)
{
	sleep_time = sl_t;
	proc_id = pr_id;
	proc_sig = pr_sig;
}

void
event (void)
{
	kill (proc_id, proc_sig);
}


int
init_wdog (void)
{
	key_t   key;
	FILE   *fp;

	fp = fopen ("/tmp/bjack.qid", "w+");
	fprintf (fp, "%i", getpid ());
	fclose (fp);

	key = ftok ("/tmp/bjack.qid", 'W');
	WDOGQID = msgget (key, 0666 | IPC_CREAT);

	fp = fopen ("/tmp/bjack.qid", "a+");
	fprintf (fp, " %i", WDOGQID);
	fclose (fp);


	return 1;
}

void
done_wdog (void)
{
	msgctl (WDOGQID, IPC_RMID, 0);
	unlink ("/tmp/bjack.qid");

	exit (0);
}


int
check_watchdog (void)
{
	struct msgbuf m;

	if (msgrcv (WDOGQID, &m, 1, 1, IPC_NOWAIT))
		if (m.mtext[0] == (char) REQUEST) {
			m.mtype = 2;
			m.mtext[0] = (char) ANSWER;
			msgsnd (WDOGQID, &m, 1, 0);
			return 1;
		}
	return 0;
}

int
do_check (void)
{
	struct msgbuf m;
	int     i;

	m.mtype = 1;
	m.mtext[0] = (char) REQUEST;
	msgsnd (WDOGQID, &m, 1, 0);

	for (i = 0; i < MAXTRIES; i++) {
		sleep (SLEEP);
		if (msgrcv (WDOGQID, &m, 1, 2, IPC_NOWAIT))
			if (m.mtext[0] == (char) ANSWER)
				return 1;
	}
	return 0;
}

void
loop (void)
{
	for (;;) {
		if (!do_check ()) {
			event ();
			done_wdog ();
		}
		sleep (sleep_time);
	}
}



/* End of File */
