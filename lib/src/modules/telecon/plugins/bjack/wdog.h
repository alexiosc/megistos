/* watchdog library */

void    set_params (int sl_t, pid_t pr_id, int pr_sig);
int     init_wdog (void);
void    done_wdog (void);
int     check_watchdog (void);
int     do_check (void);
void    loop (void);
void    event ();

/* End of File */
