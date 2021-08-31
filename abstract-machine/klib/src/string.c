#include <klib.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len = 0;

  while (*(s++) != '\0') {
    len += 1;
  }

  return len;
}

char *strcpy(char *dst, const char *src) {
  size_t i;

  for (i = 0; src[i] != '\0'; i++)
    dst[i] = src[i];

  dst[i] = '\0';

  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++)
    dst[i] = src[i];
  for (; i < n; i++)
    dst[i] = '\0';

  return dst;
}

char *strcat(char *dst, const char *src) {
  size_t dest_len = strlen(dst);
  size_t i;

  for (i = 0; src[i] != '\0'; i++)
    dst[dest_len + i] = src[i];

  dst[dest_len + i] = '\0';

  return dst;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    ++s1;
    ++s2;
  }
  return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t i;

  for (i = 0; *s1 && (*s1 == *s2) && i < n; i++) {
    ++s1;
    ++s2;
  }

  return *s1 - *s2;
}

void *memset(void *v, int c, size_t n) {
  if (v == NULL || n < 0) {
    return NULL;
  }

  char *tmp = (char *)v;

  while (n-- > 0) {
    *(tmp++) = c;
  }

  return v;
}

void *memmove(void *dst, const void *src, size_t n) {
  if (dst == NULL || src == NULL || n < 0) {
    return NULL;
  }

  char tmp[n];
  char *dst_tmp = (char *)dst;
  const char *src_tmp = (char *)src;

  size_t i;

  for (i = 0; i < n; i++) {
    tmp[i] = src_tmp[i];
  }
  for (i = 0; i < n; i++) {
    dst_tmp[i] = tmp[i];
  }

  return dst;
}

void *memcpy(void *dst, const void *src, size_t n) {
  if (dst == NULL || src == NULL || n < 0) {
    return NULL;
  }

  char *dst_tmp = (char *)dst;
  const char *src_tmp = (char *)src;

  while (n-- > 0) {
    *(dst_tmp++) = *(src_tmp++);
  }

  return dst;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *s1_tmp = (const unsigned char *)s1;
  const unsigned char *s2_tmp = (const unsigned char *)s2;

  size_t i;

  for (i = 0; i < n; i++, s1_tmp++, s2_tmp++) {
    if (*s1_tmp < *s2_tmp) {
      return -1;
    } else if (*s1_tmp > *s2_tmp) {
      return 1;
    }
  }

  return 0;
}

#endif
