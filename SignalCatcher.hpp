/**
 * Zmienna globalna przechowująca informację o tym, czy został wysłany sygnał SIGINT
 */

bool SIGINT_sent = 0;

/**
 * Zmienna globalna przechowująca informację o zapauzowaniu programu
 */

bool SIGTSTP_sent = 0;
/**
 * Funkcja globalna przechwytująca sygnał SIGINT i zmieniająca wartość zmiennej SIGINT_sent na jeden, co pozwala odczytać później jej stan.
 */
void catch_int(int sig_num)
{
 signal(SIGINT, catch_int);
 SIGINT_sent = 1;
}

/**
 * Funkcja globalna przechwytująca sygnał SIGTSTP i zmieniająca wartość zmiennej SIGTSTP na przeciwną
 */
void catch_tstp(int sig_num)
{
 signal(SIGTSTP, catch_tstp);
 SIGTSTP_sent = !SIGTSTP_sent;
}

/**
 * Funkcja globalna przechwytująca sygnał SIGCONT i ustawiająca wartość zmiennej SIGTSTP_sent na 0
 */

void catch_cont(int sig_num)
{
 signal(SIGCONT, catch_cont);
 SIGTSTP_sent = 0;
}
