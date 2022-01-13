#include <stdlib.h>
#include <string.h>
#include "vec.h"

vec *new_vec(void)
{
  vec *v = malloc(sizeof v);
  v->elems = malloc(MAX_VEC_ELEMS);
  v->count = 0;
  return v;
}

void vec_push(vec *v, char *elem)
{
  v->elems[v->count++] = elem;
}

int vec_max_len(vec *v)
{
  int max_len = 0;
  for (int i = 0; i < v->count; i++) {
    int len = strlen(v->elems[i]);
    if (len > max_len) {
      max_len = len;
    }
  }
  return max_len;
}
