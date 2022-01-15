#ifndef _LOCAL_SEARCH_H
#define _LOCAL_SEARCH_H

#include "basis.h"

int select_removing_vertex_random_walk();
int select_removing_vertex_not_bms();
int select_removing_vertex_bms();
int select_adding_vertex_random_walk(int e);
int select_adding_vertex_from_edge_using_configuration_checking(int e);
int select_adding_vertex_from_edge_not_using_configuration_checking(int e);
void exchange_and_update(int best_removing_v, int best_adding_v, long long step);
void cover_LS(int fix_vertices_size);

#endif
