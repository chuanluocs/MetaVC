#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "basis.h"

extern void (*init_sol_heuristic_ptr) ();

extern void (*get_adding_vertices_in_ruin_and_reconstruct_ptr) (vector<tmpNode> &);

extern int (*select_removing_vertex_in_set_ptr) (int*, int);
extern int (*select_removing_vertex_ptr) ();

extern int (*select_adding_vertex_from_edge_ptr) (int, int);
extern int (*select_adding_vertex_ptr) (int);

extern int (*select_uncov_edge_heuristic_ptr) ();

extern void (*init_edge_weight_scheme_ptr) ();
extern void (*edge_weight_scheme_ptr) ();

extern void (*init_vertex_weight_scheme_ptr) ();
extern void (*vertex_weight_scheme_ptr) ();

void algorithm_settings_numvc();
void algorithm_settings_numvc_related_to_graph_information();

void default_algorithm_settings();
void default_algorithm_settings_related_to_graph_information();


#endif
