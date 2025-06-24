/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#include <8051.h>
#include <uart_stdio.h>
#include <pins_arduino.h>

struct _89_uart Serial;

//_89_uart_Serial_struct_link
void Serial89Init (void) {
    Serial.available=&_89_uart_available;
    Serial.begin=&_89_uart_begin;
    Serial.printf=&_89_uart_printf;
    Serial.print=&_89_uart_printf;
    Serial.printfln=&_89_uart_printfln;
    Serial.println=&_89_uart_printfln;
    Serial.read=&_89_uart_read_char;
    Serial.readString=&_89_uart_read_string;
}
// _89_uart_init
void _89_uart_init(unsigned long baudrate, unsigned long fosc) {
#ifdef _89C53_
    AUXR=0;
    AUXR1=0;
    CLK_DIV=0;
    unsigned char ACC = P_SW1;
    ACC &= ~(S1_S0 | S1_S1); //S1_S0=0 S1_S1=0
    P_SW1 = ACC; //(P3.0/RxD, P3.1/TxD)
#endif
    unsigned int reload_value;
    // Calcul de la valeur de reload pour TH1
    reload_value = 256 - (fosc / (12 * 32 * baudrate));
    // Configurer le port série en mode 1 (8-bit UART)
    SCON = 0x50;
#ifdef _89C53_
    T2L = (65536 - (fosc/4/baudrate)); //Setting the reload value of buad rate
    T2H = (65536 - (fosc/4/baudrate))>>8;
    AUXR = 0x14; //T2 in 1T mode, and run Timer 2
    AUXR |= 0x01; //Select Timer2 as the baud-rate generator of UART1
    ES = 1;
    EA = 1;
#else
    // Configurer le Timer 1 en mode 2 (8-bit auto-reload)
    TMOD = 0x20;
    // Charger TH1 avec la valeur calculée
    TH1 = reload_value;
    // Démarrer le Timer 1
    TR1 = 1;
#endif
}
// _89_uart_send_char
void _89_uart_send_char(char c) {
  SBUF = c; // Envoyer le caractère
  while (!TI); // Attendre la fin de la transmission
  TI = 0; // Réinitialiser le flag TI
}
// _89_uart_send_string
void _89_uart_send_string(const char *str) {
  while (*str) {
    _89_uart_send_char(*str++);
  }
}
// _89_int_to_string
void _89_int_to_string(int num, char *str) {
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
// _89_uart_printf
void _89_uart_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  char  _89_uart_buffer[16];
  char *str;
  int num;

  while (*format) {
    if (*format == '%') {
      format++;
      switch (*format) {
        case 'c':
          _89_uart_send_char(va_arg(args, int));
          break;
        case 's':
          str = (char *) va_arg(args, char *);
          _89_uart_send_string(str);
          break;
        case 'd':
          num = va_arg(args, int);
          _89_int_to_string(num,  _89_uart_buffer);
          _89_uart_send_string( _89_uart_buffer);
          break;
        default:
          _89_uart_send_char(*format);
          break;
      }
    } else {
      _89_uart_send_char(*format);
    }
    format++;
  }
  va_end(args);
}
// _89_uart_printf
void _89_uart_printfln(const char *format, ...) {
  va_list args;
  va_start(args, format);

  char  _89_uart_buffer[16];
  char *str;
  int num;

  while (*format) {
    if (*format == '%') {
      format++;
      switch (*format) {
        case 'c':
          _89_uart_send_char(va_arg(args, int));
          break;
        case 's':
          str = (char *) va_arg(args, char *);
          _89_uart_send_string(str);
          break;
        case 'd':
          num = va_arg(args, int);
          _89_int_to_string(num,  _89_uart_buffer);
          _89_uart_send_string( _89_uart_buffer);
          break;
        default:
          _89_uart_send_char(*format);
          break;
      }
    } else {
      _89_uart_send_char(*format);
    }
    format++;
  }
  _89_uart_send_char('\n');
  va_end(args);
}
//_89_uart_begin
void _89_uart_begin(int baudrate) {
   _89_uart_init(baudrate, F_CPU);
}
// _89_uart_available
char _89_uart_available(void) {
    if (RI) return 1; else return 0;
}
// _89_uart_read_char
char _89_uart_read_char(void) {
        while (!RI);           // Attendre que le récepteur ait reçu un caractère
        RI = 0;                // Réinitialiser le bit de réception
        return SBUF;           // Retourner le caractère reçu
    }

    // Fonction pour recevoir une chaîne de caractères terminée par un '\0'
void _89_uart_read_string(char* buffer) {
        char ch;
        while (1) {
            ch = _89_uart_read_char();   // Lire un caractère
            *buffer = ch;          // Placer le caractère dans le buffer
            if (ch == '\n') {      // Si fin de chaîne (terminée par '\0')
                break;
            }
            buffer++;              // Passer à l'élément suivant du buffer
        }
    }
