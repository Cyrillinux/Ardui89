/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2025
 */
#include <xtoy.h>
// int_to_string
void int_to_string(int num, char *str) {
  int i = 0;
  int is_negative = 0;

  if (num < 0) {
    is_negative = 1;
    num = -num;
  }

  do {
    str[i++] = (num % 10) + '0';
    num /= 10;
  } while (num > 0);

  if (is_negative) {
    str[i++] = '-';
  }
    str[i] = '\0';
  // Inverser la chaîne
  for (int j = 0; j < i / 2; j++) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}
