#include "SignalCatcher.h"

bool SIGINT_sent = 0;
bool SIGTSTP_sent = 0;

void catch_int(int sig_num)
{
 signal(SIGINT, catch_int);
 SIGINT_sent = 1;
}

void catch_tstp(int sig_num)
{
 signal(SIGTSTP, catch_tstp);
 SIGTSTP_sent = !SIGTSTP_sent;
}

void catch_cont(int sig_num)
{
 signal(SIGCONT, catch_cont);
 SIGTSTP_sent = 0;
}