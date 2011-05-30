#ifndef SIGHNALCATHER_H
#define SIGHNALCATHER_H
#include<signal.h>

/**
 * Global variable, which stores information about SIGINT signal status
 */

extern bool SIGINT_sent;

/**
 * Global variable, which stores information about SIGTSTP and SIGCONT signals status
 */

extern bool SIGTSTP_sent;

/**
 * Global variable, which stores information about SIGUSR1 signal status
 */

extern bool SIGUSR1_sent;

/**
 * Global function. Catches SIGINT signal and sets SIGINT_sent value to 1.
 */
void catch_int(int sig_num);

/**
 * Global function. Catches SIGTERM signal and sets SIGINT_sent value to 1.
 * Identical to catch_int function.
 */
void catch_term(int sig_num);

/**
 * Global function. Catches SIGTSTP signal and sets SIGTSTP_sent value to opposite.
 */
void catch_tstp(int sig_num);

/**
 * Global function. Catches SIGCONT signal and sets SIGTSTP_sent value to 0.
 */

void catch_cont(int sig_num);

/**
 * Global function. Catches SIGUSR1 signal and sets SIGUSR1_sent value to 1.
 */
void catch_usr1(int sig_num);


#endif //SIGHNALCATHER_H
