#include "s21_sscanf.h"

int s21_empty_str(char *str) {
  int found_not_space = 1;
  int i = 0;
  while (str[i]) {
    if (!s21_isspace(str[i])) found_not_space = 0;
    i++;
  }
  return found_not_space;
}

int s21_isupper(char c) { return (c >= 'A' && c <= 'Z'); }

int s21_isalpha(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? 1 : 0);
}

int s21_isspace(char c) {
  return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}

int s21_isdigit(char c) {
  return ((c >= '0' && c <= '9') || c == '-' || c == '+');
}

int s21_ishex(char c) {
  return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
          (c >= 'A' && c <= 'F') || c == 'x' || c == 'X' || c == '-' ||
          c == '+');
}

int s21_isoctal(char c) {
  return ((c >= '0' && c <= '7') || c == '-' || c == '+');
}

long s21_strtol(const char *nptr, char **endptr, register int base) {
  register const char *s = nptr;
  register unsigned long acc;
  register int c;
  register unsigned long cutoff;
  register int neg = 0, any, cutlim;
  do {
    c = *s++;
  } while (s21_isspace(c));
  if (c == '-') {
    neg = 1;
    c = *s++;
  } else if (c == '+')
    c = *s++;
  if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
    c = s[1];
    s += 2;
    base = 16;
  }
  if (base == 0) base = c == '0' ? 8 : 10;
  cutoff = neg ? -(unsigned long)S21_LONG_MIN : S21_LONG_MAX;
  cutlim = cutoff % (unsigned long)base;
  cutoff /= (unsigned long)base;
  for (acc = 0, any = 0;; c = *s++) {
    if (s21_isdigit(c))
      c -= '0';
    else if (s21_isalpha(c))
      c -= s21_isupper(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base) break;
    if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
      any = -1;
    else {
      any = 1;
      acc *= base;
      acc += c;
    }
  }
  if (any < 0) {
    acc = neg ? S21_LONG_MIN : S21_LONG_MAX;
    errno = ERANGE;
  } else if (neg)
    acc = -acc;
  if (endptr != 0) *endptr = (char *)(any ? s - 1 : nptr);
  return (acc);
}
llong_type s21_strtoll(const char *nptr, char **endptr, register int base) {
  register const char *s = nptr;
  register ullong_type acc;
  register int c;
  register ullong_type cutoff;
  register int neg = 0, any, cutlim;
  do {
    c = *s++;
  } while (s21_isspace(c));
  if (c == '-') {
    neg = 1;
    c = *s++;
  } else if (c == '+')
    c = *s++;
  if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
    c = s[1];
    s += 2;
    base = 16;
  }
  if (base == 0) base = c == '0' ? 8 : 10;

  cutoff = neg ? -(ullong_type) S21_LLONG_MIN : S21_LLONG_MAX;
  cutlim = cutoff % (ullong_type)base;
  cutoff /= (ullong_type)base;
  for (acc = 0, any = 0;; c = *s++) {
    if (s21_isdigit(c))
      c -= '0';
    else if (s21_isalpha(c))
      c -= s21_isupper(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base) break;
    if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
      any = -1;
    else {
      any = 1;
      acc *= base;
      acc += c;
    }
  }
  if (any < 0) {
    acc = neg ? S21_LLONG_MIN : S21_LLONG_MAX;
    errno = ERANGE;
  } else if (neg)
    acc = -acc;
  if (endptr != 0) *endptr = (char *)(any ? s - 1 : nptr);
  return (acc);
}

unsigned long s21_strtoul(const char *nptr, char **endptr, register int base) {
  register const char *s = nptr;
  register unsigned long acc;
  register int c;
  register unsigned long cutoff;
  register int neg = 0, any, cutlim;

  do {
    c = *s++;
  } while (s21_isspace(c));
  if (c == '-') {
    neg = 1;
    c = *s++;
  } else if (c == '+')
    c = *s++;
  if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
    c = s[1];
    s += 2;
    base = 16;
  }
  if (base == 0) base = c == '0' ? 8 : 10;
  cutoff = (unsigned long)S21_ULONG_MAX / (unsigned long)base;
  cutlim = (unsigned long)S21_ULONG_MAX % (unsigned long)base;
  for (acc = 0, any = 0;; c = *s++) {
    if (s21_isdigit(c))
      c -= '0';
    else if (s21_isalpha(c))
      c -= s21_isupper(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base) break;
    if (any < 0 || acc > cutoff ||(acc == cutoff && c > cutlim))
      any = -1;
    else {
      any = 1;
      acc *= base;
      acc += c;
    }
  }
  if (any < 0) {
    acc = S21_ULONG_MAX;
    errno = ERANGE;
  } else if (neg)
    acc = -acc;
  if (endptr != 0) *endptr = (char *)(any ? s - 1 : nptr);
  return (acc);
}

ullong_type s21_strtoull(const char *nptr, char **endptr, register int base) {
  register const char *s = nptr;
  register ullong_type acc;
  register int c;
  register ullong_type cutoff;
  register int neg = 0, any, cutlim;
  do {
    c = *s++;
  } while (s21_isspace(c));
  if (c == '-') {
    neg = 1;
    c = *s++;
  } else if (c == '+')
    c = *s++;
  if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
    c = s[1];
    s += 2;
    base = 16;
  }
  if (base == 0) base = c == '0' ? 8 : 10;
  cutoff = (ullong_type)S21_ULLONG_MAX / (ullong_type)base;
  cutlim = (ullong_type)S21_ULLONG_MAX % (ullong_type)base;
  for (acc = 0, any = 0;; c = *s++) {
    if (s21_isdigit(c))
      c -= '0';
    else if (s21_isalpha(c))
      c -= s21_isupper(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base) break;
    if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
      any = -1;
    else {
      any = 1;
      acc *= base;
      acc += c;
    }
  }
  if (any < 0) {
    acc = S21_ULLONG_MAX;
    errno = ERANGE;
  } else if (neg)
    acc = -acc;
  if (endptr != 0) *endptr = (char *)(any ? s - 1 : nptr);
  return (acc);
}

long double s21_atold(char *str) {
  int sign = 1, i = 0;
  long double inc = 0.1L, res = 0.L;
  if (str[i] == '-') {
    sign = -1;
    i++;
  } else if (str[i] == '+') {
    i++;
  }
  while (str[i] != '.') {
    if (!(str[i] >= '0' && str[i] <= '9')) {
      break;
    } else {
      res = res * 10.L + str[i] - '0';
      i++;
    }
  }
  if (str[i] == '.') i++;
  while (str[i]) {
    if (!(str[i] >= '0' && str[i] <= '9')) {
      break;
    } else {
      res = res + (str[i] - '0') * inc;
      inc /= 10.L;
      i++;
    }
  }
  inc = 10.L;
  if (str[i] == 'e' || str[i] == 'E') {
    i++;
    if (str[i] == '-') {
      inc = 0.1L;
      i++;
    } else if (str[i] == '+') {
      inc = 10.L;
      i++;
    }
    int count = 0;
    while (str[i] >= '0' && str[i] <= '9') {
      count = count * 10.L + str[i] - '0';
      i++;
    }

    while (count) {
      res *= inc;
      count--;
    }
  }
  return res * sign;
}

long long s21_atoll(const char *str) {
  return s21_strtoll(str, (char **)NULL, 10);
}

long s21_atol(const char *str) { return (s21_strtol(str, (char **)NULL, 10)); }
