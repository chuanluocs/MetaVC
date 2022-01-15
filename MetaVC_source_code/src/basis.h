#ifndef _BASIS_H
#define _BASIS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define pop(stack) stack[--stack ## _fill_pointer]
#define push(item, stack) stack[stack ## _fill_pointer++] = item

struct Edge
{
	int v1;
	int v2;
};

struct tmpNode
{
	int vertex;
	int degree;
	long long dscore;
};

#include "heuristic.h"
#include "info.h"
#include "local_search.h"
#include "mersenne_rng.h"
#include "my_heap.h"
#include "parse_arguments.h"
#include "preprocess.h"
#include "settings.h"


extern Mersenne_rng rng;
extern int seed;
extern string inst;
extern int fix_vertices_size;
extern bool flag_print_sol;

extern long long maxi_steps;
extern long long step;
extern int target_optimal_size;
extern clock_t start;
extern clock_t stop;

extern int v_num;
extern int e_num;

extern Edge *edge;
extern long long *edge_weight;

extern long long *dscore;
extern long long *time_stamp;
extern long long *vertex_weight;
extern double* vertex_prob_value;
extern int *tmp_vertex_array_with_ties;
extern int tmp_vertex_array_with_ties_length;

extern int **v_edges;
extern int **v_adj;
extern int *v_degree;

extern int c_size;
extern bool *v_in_c;
extern int *remove_cand;
extern int *index_in_remove_cand;
extern int remove_cand_size;

extern int best_c_size;
extern bool *best_v_in_c;
extern double best_run_time;
extern long long best_step;

extern int *uncov_stack;
extern int uncov_stack_fill_pointer;
extern int *index_in_uncov_stack;

extern long long total_uncov_edge_weight;

extern int *conf_change;
extern int tabu_remove;

extern long long avg_weight;
extern long long delta_total_weight;
extern long long scale_avg;
extern long long edge_weight_threshold; //
extern double para_edge_weight_threshold_scale;
extern double para_edge_weight_p_scale; //
extern double para_edge_weight_q_scale; //

extern int* large_weight_edges;
extern int large_weight_edges_count;
extern double para_paws_smooth_probability;
extern long long para_paws_periodical_step_length;

extern int *large_weight_vertices;
extern int large_weight_vertices_count;
extern int *index_in_large_weight_vertices;
extern bool *vertex_flag_for_vertex_weight;
extern int *vertex_cache_for_vertex_weight;
extern int vertex_cache_for_vertex_weight_count;
extern double para_twmvc_smooth_probability; //
extern long long para_twmvc_delta; //
extern double para_twmvc_beta; //
extern long long para_twmvc_periodical_step_length; //

extern int *bms_cand_set;
extern int bms_cand_set_size;
extern int para_bms_k; //

extern long long para_tabu_tenure; //
extern double para_removing_prob_novelty; //

extern double para_adding_prob_novelty; //

extern double para_prob_distri_c1; //
extern int para_prob_distri_c2; //
extern int para_prob_distri_c3; //

extern double para_prob_ruin_and_reconstruct; //
extern int para_num_vertex_ruin_and_reconstruct;
extern int *removing_vertices_in_ruin_and_reconstruct;
extern int removing_vertices_in_ruin_and_reconstruct_size;
extern int *adding_vertices_in_ruin_and_reconstruct;
extern int adding_vertices_in_ruin_and_reconstruct_size;
extern vector<tmpNode> vector_vertex_not_in_cover;

extern double para_removing_prob_random_walk; //
extern double para_adding_prob_random_walk; //

extern bool decision_perform_preprocess; //
extern bool decision_perform_ruin_and_reconstruct; //
extern bool decision_perform_removing_random_walk; //
extern bool decision_perform_adding_random_walk; //
extern bool decision_perform_edge_weight_scheme; //
extern bool decision_perform_vertex_weight_scheme; //

extern const long long maximum_edge_weight_limit;



void reassign_istringstream(istringstream &iss, string line);
void allocate_memory(int v_num, int e_num);
void free_memory(int v_num, int e_num);
double compute_time(clock_t start, clock_t stop);
void update_best_sol();
bool build_instance(string inst);
bool build_instance(const vector<vector<long> > &adjacency_matrix);
void reset_remove_cand();
void update_target_size();
void uncover(int e);
void cover(int e);
void init_sol();
void add(int v);
void remove(int v);
bool check_solution();

#endif
