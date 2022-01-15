#ifndef _HEURISTIC_H
#define _HEURISTIC_H

#include "basis.h"

void empty_function_ret_void();

void add_init(int v);
void init_sol_dscore_heuristic();
void init_sol_degree_heuristic();

void get_adding_vertices_in_ruin_and_reconstruct_degree(vector<tmpNode> &vector_vertex_not_in_cover);
void get_adding_vertices_in_ruin_and_reconstruct_dscore(vector<tmpNode> &vector_vertex_not_in_cover);

int select_removing_vertex_in_set_greedy_dscore_age(int *the_set, int the_set_length);
int select_removing_vertex_in_set_greedy_dscore_random(int *the_set, int the_set_length);
int select_removing_vertex_in_set_greedy_dscore_vertex_weight(int *the_set, int the_set_length);
int select_removing_vertex_in_set_configuration_checking_age(int *the_set, int the_set_length);
int select_removing_vertex_in_set_configuration_checking_random(int *the_set, int the_set_length);
int select_removing_vertex_in_set_configuration_checking_vertex_weight(int *the_set, int the_set_length);
int select_removing_vertex_in_set_tabu(int *the_set, int the_set_length);
int select_removing_vertex_in_set_novelty(int *the_set, int the_set_length);
int select_removing_vertex_in_set_probability_distribution(int *the_set, int the_set_length);

int select_adding_vertex_from_edge_greedy_dscore_age(int v1, int v2);
int select_adding_vertex_from_edge_greedy_dscore_random(int v1, int v2);
int select_adding_vertex_from_edge_twmvc(int v1, int v2);
int select_adding_vertex_from_edge_tabu(int v1, int v2);
int select_adding_vertex_from_edge_novelty(int v1, int v2);
int select_adding_vertex_from_edge_probability_distribution(int v1, int v2);

int select_uncov_edge_random_heuristic();
int select_uncov_edge_weight_distribution_heuristic();

void init_edge_weight_scheme_multiplicative_scaling_with_forgetting();
void multiplicative_scaling_edge_weights_with_forgetting();
void edge_weight_scheme_multiplicative_scaling_with_forgetting();

void init_edge_weight_scheme_multiplicative_scaling();
void multiplicative_scaling_edge_weights();
void edge_weight_scheme_multiplicative_scaling();

void init_edge_weight_scheme_paws();
void dec_edge_weight_paws();
void inc_edge_weight_paws();
void edge_weight_scheme_paws();

void init_edge_weight_scheme_paws_periodical();
void dec_edge_weight_paws_periodical();
void inc_edge_weight_paws_periodical();
void edge_weight_scheme_paws_periodical();

void init_vertex_weight_scheme_twmvc();
void dec_vertex_weight_scheme_twmvc();
void inc_vertex_weight_scheme_twmvc();
void vertex_weight_scheme_twmvc();

void init_vertex_weight_scheme_twmvc_periodical();
void dec_vertex_weight_scheme_twmvc_periodical();
void inc_vertex_weight_scheme_twmvc_periodical();
void vertex_weight_scheme_twmvc_periodical();

#endif
