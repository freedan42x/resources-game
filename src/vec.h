#define MAX_VEC_ELEMS 1024

typedef struct
{
  char **elems;
  int count;
} vec;

vec *new_vec(void);
void vec_push(vec *v, char *elem);
int vec_max_len(vec *v);
