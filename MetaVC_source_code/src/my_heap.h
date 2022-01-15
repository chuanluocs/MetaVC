#ifndef _MY_HEAP_H
#define _MY_HEAP_H

#include "basis.h"

extern int *pos_in_my_heap;

extern int *my_heap;
extern int my_heap_count;

void my_heap_swap(int a, int b);
bool my_heap_is_leaf(int pos);
int my_heap_left_child(int pos);
int my_heap_right_child(int pos);
int my_heap_parent(int pos);
void my_heap_shiftdown(int pos);
void my_heap_insert(int v);
int my_heap_remove_first();
int my_heap_remove(int pos);

#endif

