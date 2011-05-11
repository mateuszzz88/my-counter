/**
 * Zmienna globalna przechowująca informację o tym, czy został wysłany sygnał SIGINT
 */

bool SIGINT_sent = 0;

/**
 * Funkcja globalna przechwytująca sygnał SIGINT i zmieniająca wartość zmiennej SIGINT_sent na jeden, co pozwala odczytać później jej stan.
 */
void catch_int(int sig_num)
{
 signal(SIGINT, catch_int);
 SIGINT_sent = 1;
}
