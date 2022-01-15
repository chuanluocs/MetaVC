#ifndef _SETTINGS_CPP
#define _SETTINGS_CPP

#include "settings.h"

void (*init_sol_heuristic_ptr) ();

void (*get_adding_vertices_in_ruin_and_reconstruct_ptr) (vector<tmpNode> &);

int (*select_removing_vertex_in_set_ptr) (int*, int);
int (*select_removing_vertex_ptr) ();

int (*select_adding_vertex_from_edge_ptr) (int, int);
int (*select_adding_vertex_ptr) (int);

int (*select_uncov_edge_heuristic_ptr) ();

void (*init_edge_weight_scheme_ptr) ();
void (*edge_weight_scheme_ptr) ();

void (*init_vertex_weight_scheme_ptr) ();
void (*vertex_weight_scheme_ptr) ();



void algorithm_settings_test()
{
	init_sol_heuristic_ptr = init_sol_dscore_heuristic;
	
	select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_tabu;
	select_removing_vertex_ptr = select_removing_vertex_not_bms;
	
	select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_probability_distribution;
	select_adding_vertex_ptr = select_adding_vertex_from_edge_using_configuration_checking;
	
	select_uncov_edge_heuristic_ptr = select_uncov_edge_weight_distribution_heuristic;
	
	init_edge_weight_scheme_ptr = init_edge_weight_scheme_multiplicative_scaling_with_forgetting;
	edge_weight_scheme_ptr = edge_weight_scheme_multiplicative_scaling_with_forgetting;
	
	init_vertex_weight_scheme_ptr = empty_function_ret_void;
	vertex_weight_scheme_ptr = empty_function_ret_void;
	
	decision_perform_preprocess = true;
	
	para_edge_weight_p_scale = 0.3;
	para_adding_prob_novelty = 0.5;
	para_removing_prob_novelty = 0.5;
	para_tabu_tenure = 3;
	
	para_prob_distri_c1 = 2.15;
	para_prob_distri_c2 = 4;
	para_prob_distri_c3 = 75000;
}

void algorithm_settings_test_related_to_graph_information()
{
	edge_weight_threshold = (long long)(0.5 * v_num);
}


void algorithm_settings_numvc()
{
	init_sol_heuristic_ptr = init_sol_dscore_heuristic;	
	
	select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_age;
	select_removing_vertex_ptr = select_removing_vertex_not_bms;
	
	select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_greedy_dscore_age;
	select_adding_vertex_ptr = select_adding_vertex_from_edge_using_configuration_checking;
	
	select_uncov_edge_heuristic_ptr = select_uncov_edge_random_heuristic;
	
	init_edge_weight_scheme_ptr = init_edge_weight_scheme_multiplicative_scaling_with_forgetting;
	edge_weight_scheme_ptr = edge_weight_scheme_multiplicative_scaling_with_forgetting;
	
	init_vertex_weight_scheme_ptr = empty_function_ret_void;
	vertex_weight_scheme_ptr = empty_function_ret_void;
	
	para_edge_weight_p_scale = 0.3;
}

void algorithm_settings_numvc_related_to_graph_information()
{
	edge_weight_threshold = (long long)(0.5 * v_num);
}



void algorithm_settings_twmvc()
{
	init_sol_heuristic_ptr = init_sol_dscore_heuristic;
	
	select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_age;
	select_removing_vertex_ptr = select_removing_vertex_not_bms;
	
	select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_twmvc;
	select_adding_vertex_ptr = select_adding_vertex_from_edge_using_configuration_checking;
	
	select_uncov_edge_heuristic_ptr = select_uncov_edge_random_heuristic;
	
	init_edge_weight_scheme_ptr = init_edge_weight_scheme_multiplicative_scaling_with_forgetting;
	edge_weight_scheme_ptr = edge_weight_scheme_multiplicative_scaling_with_forgetting;
	
	init_vertex_weight_scheme_ptr = init_vertex_weight_scheme_twmvc;
	vertex_weight_scheme_ptr = vertex_weight_scheme_twmvc;
	
	para_edge_weight_p_scale = 0.3;
	para_twmvc_beta = 0.8;
	para_twmvc_delta = 100000;
	para_twmvc_smooth_probability = 0.01;
}

void algorithm_settings_twmvc_related_to_graph_information()
{
	edge_weight_threshold = (long long)(0.5 * v_num);
}

void algorithm_settings_fastvc()
{
	init_sol_heuristic_ptr = init_sol_degree_heuristic;
	
	select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_age;
	select_removing_vertex_ptr = select_removing_vertex_bms;
	
	select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_greedy_dscore_age;
	select_adding_vertex_ptr = select_adding_vertex_from_edge_not_using_configuration_checking;
	
	select_uncov_edge_heuristic_ptr = select_uncov_edge_random_heuristic;
	
	init_edge_weight_scheme_ptr = empty_function_ret_void;
	edge_weight_scheme_ptr = empty_function_ret_void;
	
	init_vertex_weight_scheme_ptr = empty_function_ret_void;
	vertex_weight_scheme_ptr = empty_function_ret_void;
	
	para_bms_k = 50; //1000 for frb
}

void algorithm_settings_fastvc_related_to_graph_information()
{
	//do nothing here
	return;
}


void default_algorithm_settings()
{
	//algorithm_settings_test();
	//algorithm_settings_numvc();
	//algorithm_settings_twmvc();
	//algorithm_settings_fastvc();
	
	seed = 1;
	target_optimal_size = 0;
	flag_print_sol = false;
	
	decision_perform_preprocess = true;
	decision_perform_ruin_and_reconstruct = false;
	decision_perform_removing_random_walk = false;
	decision_perform_adding_random_walk = false;
	decision_perform_edge_weight_scheme = true;
	decision_perform_vertex_weight_scheme = false;
	
	init_sol_heuristic_ptr = init_sol_dscore_heuristic;
	
	get_adding_vertices_in_ruin_and_reconstruct_ptr = get_adding_vertices_in_ruin_and_reconstruct_degree;
	
	select_removing_vertex_ptr = select_removing_vertex_not_bms;
	select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_age;
	
	select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_greedy_dscore_age;
	select_adding_vertex_ptr = select_adding_vertex_from_edge_using_configuration_checking;
	
	select_uncov_edge_heuristic_ptr = select_uncov_edge_random_heuristic;
	
	init_edge_weight_scheme_ptr = init_edge_weight_scheme_multiplicative_scaling_with_forgetting;
	edge_weight_scheme_ptr = edge_weight_scheme_multiplicative_scaling_with_forgetting;
	
	init_vertex_weight_scheme_ptr = empty_function_ret_void;
	vertex_weight_scheme_ptr = empty_function_ret_void;
	
	para_bms_k = 50;
	
	para_tabu_tenure = 3;
	
	para_removing_prob_novelty = 0.5;
	
	para_prob_distri_c1 = 2.15;
	para_prob_distri_c2 = 4;
	para_prob_distri_c3 = 75000;
	
	para_twmvc_smooth_probability = 0.01;
	para_twmvc_delta = 100000;
	para_twmvc_beta = 0.8;
	
	para_twmvc_periodical_step_length = 100;
	
	para_adding_prob_novelty = 0.5;
	
	para_edge_weight_threshold_scale = 0.5;
	para_edge_weight_p_scale = 0.3;
	para_edge_weight_q_scale = 0.7;
	
	para_paws_smooth_probability = 0.8;
	para_paws_periodical_step_length = 200;
	
	para_prob_ruin_and_reconstruct = 0.001;
	para_num_vertex_ruin_and_reconstruct = 10;
	
	para_removing_prob_random_walk = 0.05;
	para_adding_prob_random_walk = 0.05;
	
	return;
}

void default_algorithm_settings_related_to_graph_information()
{
	//algorithm_settings_test_related_to_graph_information();
	//algorithm_settings_numvc_related_to_graph_information();
	//algorithm_settings_twmvc_related_to_graph_information();
	//algorithm_settings_fastvc_related_to_graph_information();
	
	edge_weight_threshold = (long long)(para_edge_weight_threshold_scale * v_num);
}


#endif
