#ifndef SIGHNALCATHER_H
#define SIGHNALCATHER_H
#include<signal.h>

/**
 * Zmienna globalna przechowująca informację o tym, czy został wysłany sygnał SIGINT
 */

extern bool SIGINT_sent;

/**
 * Zmienna globalna przechowująca informację o zapauzowaniu programu
 */

extern bool SIGTSTP_sent;
/**
 * Funkcja globalna przechwytująca sygnał SIGINT i zmieniająca wartość zmiennej SIGINT_sent na jeden, co pozwala odczytać później jej stan.
 */
void catch_int(int sig_num);

/**
 * Funkcja globalna przechwytująca sygnał SIGTSTP i zmieniająca wartość zmiennej SIGTSTP na przeciwną
 */
void catch_tstp(int sig_num);

/**
 * Funkcja globalna przechwytująca sygnał SIGCONT i ustawiająca wartość zmiennej SIGTSTP_sent na 0
 */

void catch_cont(int sig_num);

#endif //SIGHNALCATHER_H