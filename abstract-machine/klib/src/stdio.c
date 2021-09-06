#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

enum flag_itoa {
  FILL_ZERO = 1,
  PUT_PLUS = 2,
  PUT_MINUS = 4,
  BASE_2 = 8,
  BASE_10 = 16,
};

static void sitoa(char **buf, unsigned int num, int width, enum flag_itoa flags) {
  unsigned int base;

  if (flags & BASE_2)
    base = 2;
  else if (flags & BASE_10)
    base = 10;
  else
    base = 16;

  char tmp[32];
  char *p = tmp;

  do {
    int rem = num % base;
    *p++ = (rem <= 9) ? (rem + '0') : (rem + 'a' - 0xA);
  } while ((num /= base));

  width -= p - tmp;

  char fill = (flags & FILL_ZERO) ? '0' : ' ';

  while (0 <= --width) {
    *((*buf)++) = fill;
  }

  if (flags & PUT_MINUS) {
    *((*buf)++) = '-';
  } else if (flags & PUT_PLUS) {
    *((*buf)++) = '+';
  }

  do {
    *((*buf)++) = *(--p);
  } while (tmp < p);
}

int printf(const char *fmt, ...) {
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  int int_temp;
  char ch;
  char *str_temp;
  const char *save = out;

  while ((ch = *(fmt++))) {
    int width = 0;
    enum flag_itoa flags = 0;

    if (ch == '%') {
      switch (ch = *(fmt++)) {
        case 'd':
          int_temp = va_arg(ap, int);

          if (int_temp < 0) {
            int_temp = -int_temp;
            flags |= PUT_MINUS;
          }

          sitoa(&out, int_temp, width, flags | BASE_10);

          break;
        case 's':
          str_temp = va_arg(ap, char *);

          if (str_temp) {
            while (*str_temp != '\0') {
              *(out++) = *(str_temp++);
            }
          }

          break;
      }
    } else {
      *(out++) = ch;
    }
  }

  *out = '\0';

  return out - save;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);

  int ret = vsprintf(out, fmt, ap);

  va_end(ap);

  return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);

  int ret = vsnprintf(out, n, fmt, ap);

  va_end(ap);

  return ret;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  int int_temp;
  char ch;
  char *str_temp;
  const char *save = out;

  while ((ch = *(fmt++)) && ((out - save) < (n - 1))) {
    int width = 0;
    enum flag_itoa flags = 0;

    if (ch == '%') {
      switch (ch = *(fmt++)) {
        case 'd':
          int_temp = va_arg(ap, int);

          if (int_temp < 0) {
            int_temp = -int_temp;
            flags |= PUT_MINUS;
          }

          sitoa(&out, int_temp, width, flags | BASE_10);

          break;
        case 's':
          str_temp = va_arg(ap, char *);

          if (str_temp) {
            while ((*str_temp != '\0') && ((out - save) < (n - 1))) {
              *(out++) = *(str_temp++);
            }
          }

          break;
      }
    } else {
      *(out++) = ch;
    }
  }

  *out = '\0';

  return out - save;
}

#endif
