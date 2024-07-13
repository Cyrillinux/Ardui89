/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#include <8051.h>
#include <uart_stdio.h>

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
}
// _89_uart_init
void _89_uart_init(unsigned long baudrate, unsigned long fosc) {
    unsigned int reload_value;
    // Calcul de la valeur de reload pour TH1
    reload_value = 256 - (fosc / (12 * 32 * baudrate));
    // Configurer le port série en mode 1 (8-bit UART)
    SCON = 0x50;
    // Configurer le Timer 1 en mode 2 (8-bit auto-reload)
    TMOD = 0x20;
    // Charger TH1 avec la valeur calculée
    TH1 = reload_value;
    // Démarrer le Timer 1
    TR1 = 1;
}
// _89_uart_send_char
void _89_uart_send_char(char c) {
  SBUF = c;        // Envoyer le caractère
  while (!TI);     // Attendre la fin de la transmission
  TI = 0;          // Réinitialiser le flag TI
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
          str = va_arg(args, char *);
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
          str = va_arg(args, char *);
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
    RI=0; // Reset reception flag
    return SBUF;  // Return the received character
}
// _89_uart_read_string
char*  _89_uart_buffer=NULL;
char* _89_uart_read_string(void) {
    unsigned int index=0;
    if (_89_uart_buffer==NULL) _89_uart_buffer = (char*) malloc(BUFFER_SIZE*sizeof(char));
    while (1) {
        char received_char = _89_uart_read_char();  // Read the character
        if ((received_char == '\n') || (index >= BUFFER_SIZE - 1)) {  // End of string or  _89_uart_buffer full
            _89_uart_buffer[index] = '\0';  // Null-terminate the string
            // You can now use the  _89_uart_buffer as needed, e.g., process the received string
            index = 0;  // Reset index for the next string
            break;
        } else {
            _89_uart_buffer[index++] = received_char;  // Store the character in the  _89_uart_buffer
        }
    }
    RI=0;
    return  _89_uart_buffer;
}
