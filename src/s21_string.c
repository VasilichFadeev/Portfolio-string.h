#include "s21_string.h"

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_errors.h"

char *s21_strcpy(char *dest, const char *src) {
  if (dest == NULL || src == NULL) {
    return NULL;
  }
  char *ptr = dest;
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return ptr;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n; i++) {
    dest[i] = src[i];
    if (dest[i] == '\0') {
      for (i++; i < n; i++) {
        dest[i] = '\0';
      }
      break;
    }
  }
  return dest;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = str;
  for (s21_size_t i = 0; i < n; i++) {
    if (p[i] == (unsigned char)c) {
      return (void *)(p + i);
    }
  }
  return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *p1 = str1;
  const unsigned char *p2 = str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return p1[i] - p2[i];
    }
  }
  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = dest;
  const unsigned char *s = src;
  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = str;
  for (s21_size_t i = 0; i < n; i++) {
    p[i] = (unsigned char)c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *original_dest = dest;
  while (*dest) dest++;
  for (s21_size_t i = 0; ((i < n) && (*src)); i++) {
    *dest++ = *src++;
  }
  *dest = '\0';
  return original_dest;
}

char *s21_strchr(const char *str, int c) {
  while (*str != (char)c) {
    if (!str) return S21_NULL;
    str++;
  }
  return (char *)str;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
      return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
  }
  return 0;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  for (; *str1 != '\0'; str1++) {
    const char *check = str2;
    while (*check != '\0') {
      if (*str1 == *check) {
        return count;
      }
      check++;
    }
    count++;
  }
  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *res = S21_NULL;
  for (; *str1 && !res; str1++) {
    for (const char *c = str2; *c && !res; c++) {
      if (*str1 == *c) res = str1;
    }
  }
  return (char *)res;
}

char *s21_strrchr(const char *str, int c) {
  const char *last = S21_NULL;
  char target = (char)c;
  do {
    if (*str == target) last = str;
  } while (*str++);
  return (char *)last;
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (!*needle) return (char *)haystack;
  for (; *haystack; haystack++) {
    const char *h = haystack, *n = needle;
    while (*h && *n && *h == *n) {
      h++;
      n++;
    }
    if (!*n) return (char *)haystack;
  }
  return S21_NULL;
}

char *s21_strerror(int errnum) {
  static char result_stroke[120];
  if (errnum >= 0 && errnum < ERRORS_COUNT) {
    return (char *)s21_errors[errnum];
  } else {
    s21_sprintf(result_stroke, "%s %d", UNKNOWN_ERROR, errnum);
    return result_stroke;
  }
}

char *s21_strtok(char *str, const char *delim) {
  static char *save_ptr = S21_NULL;
  char *token_start;
  int found_delim;
  if (str != S21_NULL) {
    save_ptr = str;
  }
  if (save_ptr == S21_NULL || *save_ptr == '\0') {
    return S21_NULL;
  }
  token_start = save_ptr;
  while (*token_start != '\0') {
    found_delim = 0;
    const char *d = delim;
    while (*d != '\0') {
      if (*token_start == *d) {
        found_delim = 1;
        break;
      }
      d++;
    }
    if (!found_delim) {
      break;
    }
    token_start++;
  }
  if (*token_start == '\0') {
    save_ptr = S21_NULL;
    return S21_NULL;
  }
  char *token_end = token_start;
  while (*token_end != '\0') {
    found_delim = 0;
    const char *d = delim;
    while (*d != '\0') {
      if (*token_end == *d) {
        found_delim = 1;
        break;
      }
      d++;
    }
    if (found_delim) {
      break;
    }
    token_end++;
  }
  if (*token_end == '\0') {
    save_ptr = token_end;
  } else {
    *token_end = '\0';
    save_ptr = token_end + 1;
  }
  return token_start;
}

char *s21_strcat(char *dest, const char *src) {
  char *ptr = dest + s21_strlen(dest);
  while (*src) {
    *ptr++ = *src++;
  }
  *ptr = '\0';
  return dest;
}

typedef struct {
  int minus;
  int plus;
  int space;
  int width;
  int precision;
  int is_precision_set;
  char length;
  char specifier;
  int sharp;
} fmt_params;

static void parse_flags(const char **format, fmt_params *params) {
  while (1) {
    switch (**format) {
      case '-':
        params->minus = 1;
        break;
      case '+':
        params->plus = 1;
        break;
      case ' ':
        params->space = 1;
        break;
      case '#':
        params->sharp = 1;
        break;
      default:
        return;
    }
    (*format)++;
  }
}

static void parse_width(const char **format, fmt_params *params) {
  if (isdigit(**format)) {
    params->width = 0;
    while (isdigit(**format)) {
      params->width = params->width * 10 + (**format - '0');
      (*format)++;
    }
  }
}

static void parse_precision(const char **format, fmt_params *params) {
  if (**format == '.') {
    (*format)++;
    params->is_precision_set = 1;
    params->precision = 0;
    while (isdigit(**format)) {
      params->precision = params->precision * 10 + (**format - '0');
      (*format)++;
    }
  }
}

static void parse_length(const char **format, fmt_params *params) {
  if (**format == 'h' || **format == 'l') {
    params->length = **format;
    (*format)++;
  }
}

static void parse_specifier(const char **format, fmt_params *params) {
  params->specifier = **format;
  (*format)++;
}

static void parse_format(const char **format, fmt_params *params) {
  parse_flags(format, params);
  parse_width(format, params);
  parse_precision(format, params);
  parse_length(format, params);
  parse_specifier(format, params);
}

static void s21_lltoa(long long value, char *str) {
  char *ptr = str;
  int is_negative = 0;
  if (value < 0) {
    is_negative = 1;
    value = -value;
  }
  do {
    *ptr++ = '0' + (value % 10);
    value /= 10;
  } while (value > 0);
  if (is_negative) *ptr++ = '-';
  *ptr = '\0';
  for (char *start = str, *end = ptr - 1; start < end; start++, end--) {
    char temp = *start;
    *start = *end;
    *end = temp;
  }
}

static void s21_ulltoa(unsigned long long value, char *str) {
  char *ptr = str;
  do {
    *ptr++ = '0' + (value % 10);
    value /= 10;
  } while (value > 0);
  *ptr = '\0';
  for (char *start = str, *end = ptr - 1; start < end; start++, end--) {
    char temp = *start;
    *start = *end;
    *end = temp;
  }
}

static void s21_ulltoa_hex(unsigned long long value, char *str, int uppercase) {
  const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  char *ptr = str;
  if (value == 0) {
    *ptr++ = '0';
  } else {
    while (value > 0) {
      *ptr++ = digits[value % 16];
      value /= 16;
    }
  }
  *ptr = '\0';
  for (char *start = str, *end = ptr - 1; start < end; start++, end--) {
    char temp = *start;
    *start = *end;
    *end = temp;
  }
}

static void s21_ulltoa_oct(unsigned long long value, char *str) {
  char *ptr = str;
  if (value == 0) {
    *ptr++ = '0';
  } else {
    while (value > 0) {
      *ptr++ = '0' + (value % 8);
      value /= 8;
    }
  }
  *ptr = '\0';
  for (char *start = str, *end = ptr - 1; start < end; start++, end--) {
    char temp = *start;
    *start = *end;
    *end = temp;
  }
}

static void apply_padding(char *str, int *index, int padding, int left_align,
                          char pad_char) {
  if (!left_align && padding > 0) {
    s21_memset(str + *index, pad_char, padding);
    *index += padding;
  }
}

static void convert_integer(fmt_params params, long long num, char *str,
                            int *index) {
  char num_str[32];
  s21_lltoa(num, num_str);

  int num_len = s21_strlen(num_str);
  int leading_zeros = params.is_precision_set ? params.precision - num_len : 0;
  if (leading_zeros < 0) leading_zeros = 0;

  char sign = (num < 0) ? '-' : (params.plus ? '+' : (params.space ? ' ' : 0));
  int sign_len = sign ? 1 : 0;

  int total_len = sign_len + leading_zeros + num_len;
  int padding = params.width - total_len;
  if (padding < 0) padding = 0;

  apply_padding(str, index, padding, params.minus, ' ');
  if (sign) str[(*index)++] = sign;
  apply_padding(str, index, leading_zeros, 1, '0');

  s21_memcpy(str + *index, num_str, num_len);
  *index += num_len;
  apply_padding(str, index, padding, !params.minus, ' ');
}

static void convert_string(fmt_params params, char *s, char *str, int *index) {
  if (!s) s = "(null)";
  size_t max_chars = params.is_precision_set
                         ? (s21_strlen(s) < (size_t)params.precision
                                ? s21_strlen(s)
                                : (size_t)params.precision)
                         : s21_strlen(s);

  int padding = params.width - (int)max_chars;
  if (padding < 0) padding = 0;

  apply_padding(str, index, padding, params.minus, ' ');
  s21_memcpy(str + *index, s, max_chars);
  *index += max_chars;
  apply_padding(str, index, padding, !params.minus, ' ');
}

static void convert_unsigned(fmt_params params, unsigned long long num,
                             char *str, int *index, int base, int uppercase) {
  char num_str[32];
  if (base == 16)
    s21_ulltoa_hex(num, num_str, uppercase);
  else if (base == 8)
    s21_ulltoa_oct(num, num_str);
  else
    s21_ulltoa(num, num_str);

  char prefix[3] = {0};
  int prefix_len = 0;
  if (params.sharp) {
    if (base == 8 && num != 0) {
      s21_strcpy(prefix, "0");
      prefix_len = 1;
    } else if (base == 16 && num != 0) {
      prefix[0] = '0';
      prefix[1] = uppercase ? 'X' : 'x';
      prefix_len = 2;
    }
  }

  char combined[64];
  s21_strcpy(combined, prefix);
  s21_strcat(combined, num_str);

  int num_len = s21_strlen(combined);
  int leading_zeros =
      params.is_precision_set ? params.precision - (num_len - prefix_len) : 0;
  if (leading_zeros < 0) leading_zeros = 0;

  int total_len = num_len + leading_zeros;
  int padding = params.width - total_len;
  if (padding < 0) padding = 0;

  apply_padding(str, index, padding, params.minus, ' ');
  apply_padding(str, index, leading_zeros, 1, '0');

  s21_memcpy(str + *index, combined, num_len);
  *index += num_len;
  apply_padding(str, index, padding, !params.minus, ' ');
}

static void convert_float(fmt_params params, double num, char *str, int *index,
                          char specifier) {
  int precision = params.is_precision_set ? params.precision : 6;
  char buffer[64];
  const char *fmt;

  if (specifier == 'e' || specifier == 'E') {
    fmt = (specifier == 'E') ? (params.sharp ? "%#.*E" : "%.*E")
                             : (params.sharp ? "%#.*e" : "%.*e");
  } else if (specifier == 'g' || specifier == 'G') {
    fmt = (specifier == 'G') ? (params.sharp ? "%#.*G" : "%.*G")
                             : (params.sharp ? "%#.*g" : "%.*g");
  } else {
    fmt = "%.*f";
  }

  snprintf(buffer, sizeof(buffer), fmt, precision, num);

  int len = s21_strlen(buffer);
  int padding = params.width - len;
  if (padding < 0) padding = 0;

  apply_padding(str, index, padding, params.minus, ' ');
  s21_memcpy(str + *index, buffer, len);
  *index += len;
  apply_padding(str, index, padding, !params.minus, ' ');
}

static void convert_char(fmt_params params, char c, char *str, int *index) {
  int padding = params.width - 1;
  if (padding < 0) padding = 0;

  apply_padding(str, index, padding, params.minus, ' ');
  str[(*index)++] = c;
  apply_padding(str, index, padding, !params.minus, ' ');
}

static void convert_pointer(fmt_params params, void *ptr, char *str,
                            int *index) {
  char buffer[32];
  s21_ulltoa_hex((uintptr_t)ptr, buffer, 0);

  int len = s21_strlen(buffer);
  int total_len = len + 2;
  int padding = params.width - total_len;
  if (padding < 0) padding = 0;

  apply_padding(str, index, padding, params.minus, ' ');
  str[(*index)++] = '0';
  str[(*index)++] = 'x';
  s21_memcpy(str + *index, buffer, len);
  *index += len;
  apply_padding(str, index, padding, !params.minus, ' ');
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int str_index = 0;

  while (*format) {
    if (*format != '%') {
      str[str_index++] = *format++;
      continue;
    }
    fmt_params params = {0};
    format++;
    parse_format(&format, &params);

    switch (params.specifier) {
      case 'd':
      case 'i':
        convert_integer(params, va_arg(args, int), str, &str_index);
        break;
      case 'u':
        convert_unsigned(params, va_arg(args, unsigned int), str, &str_index,
                         10, 0);
        break;
      case 'o':
        convert_unsigned(params, va_arg(args, unsigned int), str, &str_index, 8,
                         0);
        break;
      case 'x':
      case 'X':
        convert_unsigned(params, va_arg(args, unsigned int), str, &str_index,
                         16, (params.specifier == 'X'));
        break;
      case 'f':
      case 'e':
      case 'E':
        convert_float(params, va_arg(args, double), str, &str_index,
                      params.specifier);
        break;
      case 'c':
        convert_char(params, va_arg(args, int), str, &str_index);
        break;
      case 's':
        convert_string(params, va_arg(args, char *), str, &str_index);
        break;
      case 'p':
        convert_pointer(params, va_arg(args, void *), str, &str_index);
        break;
      case 'g':
      case 'G':
        convert_float(params, va_arg(args, double), str, &str_index,
                      params.specifier);
        break;
      case '%':
        str[str_index++] = '%';
        break;
    }
  }

  str[str_index] = '\0';
  va_end(args);
  return str_index;
}

typedef enum {
  LENGTH_NONE,
  LENGTH_H,
  LENGTH_HH,
  LENGTH_L,
  LENGTH_LL,
  LENGTH_LD
} length_modifier;

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int count = 0;
  const char *f = format, *s = str;

  while (*f) {
    if (isspace(*f)) {
      while (isspace(*s)) s++;
      f++;
    } else if (*f == '%') {
      f++;
      int assign = 1;
      int width = 0;
      length_modifier mod = LENGTH_NONE;
      if (*f == '*') {
        assign = 0;
        f++;
      }
      while (isdigit(*f)) {
        width = width * 10 + (*f - '0');
        f++;
      }
      if (*f == 'h') {
        f++;
        if (*f == 'h') {
          mod = LENGTH_HH;
          f++;
        } else {
          mod = LENGTH_H;
        }
      } else if (*f == 'l') {
        f++;
        if (*f == 'l') {
          mod = LENGTH_LL;
          f++;
        } else {
          mod = LENGTH_L;
        }
      } else if (*f == 'L') {
        mod = LENGTH_LD;
        f++;
      }
      char spec = *f++;
      switch (spec) {
        case 'd':
        case 'i':
        case 'o':
        case 'u':
        case 'x':
        case 'X': {
          while (isspace(*s)) s++;
          int base = 10;
          if (spec == 'i')
            base = 0;
          else if (spec == 'o')
            base = 8;
          else if (spec == 'x' || spec == 'X')
            base = 16;

          char *end;
          unsigned long num;
          if (mod == LENGTH_LD) break;
          num = strtoul(s, &end, base);
          if (end > s) {
            if (assign) {
              switch (mod) {
                case LENGTH_HH: {
                  signed char *p = va_arg(args, signed char *);
                  *p = (signed char)num;
                  break;
                }
                case LENGTH_H: {
                  short *p = va_arg(args, short *);
                  *p = (short)num;
                  break;
                }
                case LENGTH_L: {
                  long *p = va_arg(args, long *);
                  *p = num;
                  break;
                }
                case LENGTH_LL: {
                  long long *p = va_arg(args, long long *);
                  *p = num;
                  break;
                }
                default: {
                  int *p = va_arg(args, int *);
                  *p = (int)num;
                  break;
                }
              }
              count++;
            }
            s = end;
          }
          break;
        }
        case 'G':
        case 'e':
        case 'E':
        case 'f': {
          while (isspace(*s)) s++;
          char *end;
          long double num;
          if (mod == LENGTH_LD) {
            num = strtold(s, &end);
          } else {
            num = strtod(s, &end);
          }
          if (end > s) {
            if (assign) {
              if (mod == LENGTH_LD) {
                long double *p = va_arg(args, long double *);
                *p = num;
              } else if (mod == LENGTH_L) {
                double *p = va_arg(args, double *);
                *p = (double)num;
              } else {
                float *p = va_arg(args, float *);
                *p = (float)num;
              }
              count++;
            }
            s = end;
          }
          break;
        }
        case 's': {
          while (isspace(*s)) s++;
          if (assign) {
            char *p = va_arg(args, char *);
            int i = 0;
            while (*s && !isspace(*s) && (width == 0 || i < width)) {
              p[i++] = *s++;
            }
            p[i] = '\0';
            count++;
          } else {
            while (*s && !isspace(*s) && (width == 0 || width--)) s++;
          }
          break;
        }
        case 'c': {
          if (assign) {
            char *p = va_arg(args, char *);
            int i = 0;
            while (width ? i < width : 1) {
              if (!*s) break;
              p[i++] = *s++;
            }
            count++;
          } else {
            s += width ? width : 1;
          }
          break;
        }
        case 'n': {
          if (assign) {
            int *p = va_arg(args, int *);
            *p = s - str;
          }
          break;
        }
        case 'p': {
          while (isspace(*s)) s++;
          char *end;
          uintptr_t addr = strtoull(s, &end, 16);
          if (end > s && assign) {
            void **p = va_arg(args, void **);
            *p = (void *)addr;
            count++;
          }
          s = end;
          break;
        }
        case '%': {
          if (*s != '%') break;
          s++;
          break;
        }
      }
    } else {
      if (*s != *f) break;
      s++;
      f++;
    }
  }

  va_end(args);
  return count;
}

void *to_upper(const char *str) {
  if (str == NULL) return NULL;
  s21_size_t len = s21_strlen(str);
  char *result = (char *)malloc(len + 1);
  if (result == NULL) return NULL;
  for (s21_size_t i = 0; i < len; i++) {
    unsigned char c = str[i];
    if (c >= 'a' && c <= 'z') {
      result[i] = c - 32;
    } else {
      result[i] = c;
    }
  }
  result[len] = '\0';
  return result;
}

void *to_lower(const char *str) {
  if (str == NULL) return NULL;
  s21_size_t len = s21_strlen(str);
  char *result = (char *)malloc(len + 1);
  if (result == NULL) return NULL;
  for (s21_size_t i = 0; i < len; i++) {
    unsigned char c = str[i];
    if (c >= 'A' && c <= 'Z') {
      result[i] = c + 32;
    } else {
      result[i] = c;
    }
  }
  result[len] = '\0';
  return result;
}

void *insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == NULL || str == NULL) return NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  if (start_index > src_len) return NULL;
  char *result = (char *)malloc(src_len + str_len + 1);
  if (result == NULL) return NULL;
  s21_strncpy(result, src, start_index);
  result[start_index] = '\0';
  s21_strcat(result, str);
  s21_strcat(result, src + start_index);
  return result;
}

void *trim(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) return NULL;
  s21_size_t len = 0;
  while (src[len] != '\0') len++;
  s21_size_t start = 0;
  s21_size_t end = (len > 0) ? len - 1 : 0;
  while (start <= end) {
    int found = 0;
    for (s21_size_t i = 0; trim_chars[i] != '\0'; i++) {
      if (src[start] == trim_chars[i]) {
        found = 1;
        break;
      }
    }
    if (!found) break;
    start++;
  }
  while (end >= start) {
    int found = 0;
    for (s21_size_t i = 0; trim_chars[i] != '\0'; i++) {
      if (src[end] == trim_chars[i]) {
        found = 1;
        break;
      }
    }
    if (!found) break;
    end--;
  }
  s21_size_t new_len = (start > end) ? 0 : end - start + 1;
  char *result = (char *)malloc(new_len + 1);
  if (result == NULL) return NULL;
  if (new_len > 0) {
    for (s21_size_t i = 0; i < new_len; i++) {
      result[i] = src[start + i];
    }
  }
  result[new_len] = '\0';
  return result;
}