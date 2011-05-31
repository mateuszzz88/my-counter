#include "SignalCatcher.h"

bool SIGINTorTERM_sent = 0;
bool SIGTSTP_sent = 0;
bool SIGUSR1_sent = 0;

void catch_int(int sig_num)
{
 signal(SIGINT, catch_int);
 signal(SIGCONT, catch_cont);
 signal(SIGTSTP, catch_tstp);
 signal(SIGTERM, catch_term);
 signal(SIGUSR1, catch_usr1);
 SIGINTorTERM_sent = 1;
}

void catch_tstp(int sig_num)
{
 signal(SIGTSTP, catch_tstp);
 signal(SIGINT, catch_int);
 signal(SIGCONT, catch_cont);
 signal(SIGTERM, catch_term);
 signal(SIGUSR1, catch_usr1);
 SIGTSTP_sent = !SIGTSTP_sent;
}

void catch_cont(int sig_num)
{
 signal(SIGCONT, catch_cont);
 signal(SIGINT, catch_int);
 signal(SIGTSTP, catch_tstp);
 signal(SIGTERM, catch_term);
 signal(SIGUSR1, catch_usr1);
 SIGTSTP_sent = 0;
}

void catch_term(int sig_num)
{
 signal(SIGCONT, catch_cont);
 signal(SIGINT, catch_int);
 signal(SIGTSTP, catch_tstp);
 signal(SIGTERM, catch_term);
 signal(SIGUSR1, catch_usr1);
 SIGINTorTERM_sent = 1;
}

void catch_usr1(int sig_num)
{
 signal(SIGCONT, catch_cont);
 signal(SIGINT, catch_int);
 signal(SIGTSTP, catch_tstp);
 signal(SIGTERM, catch_term);
 signal(SIGUSR1, catch_usr1);
 SIGUSR1_sent = 0;
}
