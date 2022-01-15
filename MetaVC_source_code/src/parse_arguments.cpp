#ifndef _PARSE_ARGUMENTS_CPP
#define _PARSE_ARGUMENTS_CPP

#include "parse_arguments.h"

bool parse_arguments(int argc, char **argv)
{
	int i;
	bool flag_inst = false;
	bool flag_seed = false;
	bool flag_opt = false;
	bool flag_vertex_weight_scheme = false;
	
	default_algorithm_settings();
	
	for(i=1; i<argc; i++)
	{
		if(strcmp(argv[i], "-inst") == 0)
		{
			i++;
			if(i>=argc) return false;
			inst = argv[i];
			flag_inst = true;
			continue;
		}
		else if(strcmp(argv[i], "-seed") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%d", &seed);
			flag_seed = true;
			continue;
		}
		else if(strcmp(argv[i], "-opt") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%d", &target_optimal_size);
			flag_opt = true;
			continue;
		}
		else if(strcmp(argv[i], "-print_sol") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "0") == 0)
			{
				flag_print_sol = false;
				continue;
			}
			else if(strcmp(argv[i], "1") == 0)
			{
				flag_print_sol = true;
				continue;
			}
		}
		else if(strcmp(argv[i], "-perform_preprocess") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "0") == 0)
			{
				decision_perform_preprocess = false;
				continue;
			}
			else if(strcmp(argv[i], "1") == 0)
			{
				decision_perform_preprocess = true;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-init_sol") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "1") == 0)
			{
				init_sol_heuristic_ptr = init_sol_dscore_heuristic;
				continue;
			}
			else if(strcmp(argv[i], "2") == 0)
			{
				init_sol_heuristic_ptr = init_sol_degree_heuristic;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-perform_ruin_and_reconstruct") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "0") == 0)
			{
				decision_perform_ruin_and_reconstruct = false;
				continue;
			}
			else if(strcmp(argv[i], "1") == 0)
			{
				decision_perform_ruin_and_reconstruct = true;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-prob_ruin_and_reconstruct") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_prob_ruin_and_reconstruct);
			continue;
		}
		else if(strcmp(argv[i], "-num_vertex_ruin_and_reconstruct") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%d", &para_num_vertex_ruin_and_reconstruct);
			continue;
		}
		else if(strcmp(argv[i], "-perform_removing_random_walk") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "0") == 0)
			{
				decision_perform_removing_random_walk = false;
				continue;
			}
			else if(strcmp(argv[i], "1") == 0)
			{
				decision_perform_removing_random_walk = true;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-removing_prob_random_walk") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_removing_prob_random_walk);
			continue;
		}
		else if(strcmp(argv[i], "-perform_bms") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "0") == 0)
			{
				select_removing_vertex_ptr = select_removing_vertex_not_bms;
				continue;
			}
			else if(strcmp(argv[i], "1") == 0)
			{
				select_removing_vertex_ptr = select_removing_vertex_bms;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-bms_k") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%d", &para_bms_k);
			continue;
		}
		else if(strcmp(argv[i], "-sel_removing_v") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "1") == 0)
			{
				select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_age;
				continue;
			}
			else if(strcmp(argv[i], "2") == 0)
			{
				select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_random;
				continue;
			}
			else if(strcmp(argv[i], "3") == 0)
			{
				select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_vertex_weight;
				flag_vertex_weight_scheme = true;
				continue;
			}
			else if(strcmp(argv[i], "4") == 0)
			{
				select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_configuration_checking_age;
				continue;
			}
			else if(strcmp(argv[i], "5") == 0)
			{
				select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_configuration_checking_random;
				continue;
			}
			else if(strcmp(argv[i], "6") == 0)
			{
				select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_configuration_checking_vertex_weight;
				flag_vertex_weight_scheme = true;
				continue;
			}
			else if(strcmp(argv[i], "7") == 0)
			{
				select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_tabu;
				continue;
			}
			else if(strcmp(argv[i], "8") == 0)
			{
				select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_novelty;
				continue;
			}
			else if(strcmp(argv[i], "9") == 0)
			{
				select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_probability_distribution;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-tabu_tenure") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lld", &para_tabu_tenure);
			continue;
		}
		else if(strcmp(argv[i], "-removing_prob_novelty") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_removing_prob_novelty);
			continue;
		}
		else if(strcmp(argv[i], "-prob_distri_c1") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_prob_distri_c1);
			continue;
		}
		else if(strcmp(argv[i], "-prob_distri_c2") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%d", &para_prob_distri_c2);
			continue;
		}
		else if(strcmp(argv[i], "-prob_distri_c3") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%d", &para_prob_distri_c3);
			continue;
		}
		else if(strcmp(argv[i], "-perform_adding_random_walk") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "0") == 0)
			{
				decision_perform_adding_random_walk = false;
				continue;
			}
			else if(strcmp(argv[i], "1") == 0)
			{
				decision_perform_adding_random_walk = true;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-adding_prob_random_walk") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_adding_prob_random_walk);
			continue;
		}
		else if(strcmp(argv[i], "-perform_cc_adding") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "0") == 0)
			{
				select_adding_vertex_ptr = select_adding_vertex_from_edge_not_using_configuration_checking;
				continue;
			}
			else if(strcmp(argv[i], "1") == 0)
			{
				select_adding_vertex_ptr = select_adding_vertex_from_edge_using_configuration_checking;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-sel_adding_v") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "1") == 0)
			{
				select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_greedy_dscore_age;
				continue;
			}
			else if(strcmp(argv[i], "2") == 0)
			{
				select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_greedy_dscore_random;
				continue;
			}
			else if(strcmp(argv[i], "3") == 0)
			{
				select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_twmvc;
				flag_vertex_weight_scheme = true;
				continue;
			}
			else if(strcmp(argv[i], "4") == 0)
			{
				select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_tabu;
				continue;
			}
			else if(strcmp(argv[i], "5") == 0)
			{
				select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_novelty;
				continue;
			}
			else if(strcmp(argv[i], "6") == 0)
			{
				select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_probability_distribution;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-adding_prob_novelty") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_adding_prob_novelty);
			continue;
		}
		else if(strcmp(argv[i], "-sel_uncov_e") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "1") == 0)
			{
				select_uncov_edge_heuristic_ptr = select_uncov_edge_random_heuristic;
				continue;
			}
			else if(strcmp(argv[i], "2") == 0)
			{
				select_uncov_edge_heuristic_ptr = select_uncov_edge_weight_distribution_heuristic;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-perform_edge_weight_scheme") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "0") == 0)
			{
				decision_perform_edge_weight_scheme = false;
				init_edge_weight_scheme_ptr = empty_function_ret_void;
				edge_weight_scheme_ptr = empty_function_ret_void;
				continue;
			}
			else if(strcmp(argv[i], "1") == 0)
			{
				decision_perform_edge_weight_scheme = true;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-sel_edge_weight_scheme") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "1") == 0)
			{
				init_edge_weight_scheme_ptr = init_edge_weight_scheme_multiplicative_scaling_with_forgetting;
				edge_weight_scheme_ptr = edge_weight_scheme_multiplicative_scaling_with_forgetting;
				continue;
			}
			else if(strcmp(argv[i], "2") == 0)
			{
				init_edge_weight_scheme_ptr = init_edge_weight_scheme_multiplicative_scaling;
				edge_weight_scheme_ptr = edge_weight_scheme_multiplicative_scaling;
				continue;
			}
			else if(strcmp(argv[i], "3") == 0)
			{
				init_edge_weight_scheme_ptr = init_edge_weight_scheme_paws;
				edge_weight_scheme_ptr = edge_weight_scheme_paws;
				continue;
			}
			else if(strcmp(argv[i], "4") == 0)
			{
				init_edge_weight_scheme_ptr = init_edge_weight_scheme_paws_periodical;
				edge_weight_scheme_ptr = edge_weight_scheme_paws_periodical;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-edge_weight_threshold_scale") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_edge_weight_threshold_scale);
			continue;
		}
		else if(strcmp(argv[i], "-edge_weight_p_scale") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_edge_weight_p_scale);
			continue;
		}
		else if(strcmp(argv[i], "-edge_weight_q_scale") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_edge_weight_q_scale);
			continue;
		}
		else if(strcmp(argv[i], "-paws_smooth_probability") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_paws_smooth_probability);
			continue;
		}
		else if(strcmp(argv[i], "-paws_periodical_step_length") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lld", &para_paws_periodical_step_length);
			continue;
		}
		else if(strcmp(argv[i], "-perform_vertex_weight_scheme") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "0") == 0)
			{
				decision_perform_vertex_weight_scheme = false;
				init_vertex_weight_scheme_ptr = empty_function_ret_void;
				vertex_weight_scheme_ptr = empty_function_ret_void;
				continue;
			}
			else if(strcmp(argv[i], "1") == 0)
			{
				decision_perform_vertex_weight_scheme = true;
				continue;
			}
			else return false;
		}
		else if(strcmp(argv[i], "-sel_vertex_weight_scheme") == 0)
		{
			i++;
			if(i>=argc) return false;
			if(strcmp(argv[i], "1") == 0)
			{
				init_vertex_weight_scheme_ptr = init_vertex_weight_scheme_twmvc;
				vertex_weight_scheme_ptr = vertex_weight_scheme_twmvc;
				continue;
			}
			else if(strcmp(argv[i], "2") == 0)
			{
				init_vertex_weight_scheme_ptr = init_vertex_weight_scheme_twmvc_periodical;
				vertex_weight_scheme_ptr = vertex_weight_scheme_twmvc_periodical;
				continue;
			}
		}
		else if(strcmp(argv[i], "-twmvc_smooth_probability") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_twmvc_smooth_probability);
			continue;
		}
		else if(strcmp(argv[i], "-twmvc_delta") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lld", &para_twmvc_delta);
			continue;
		}
		else if(strcmp(argv[i], "-twmvc_beta") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lf", &para_twmvc_beta);
			continue;
		}
		else if(strcmp(argv[i], "-twmvc_periodical_step_length") == 0)
		{
			i++;
			if(i>=argc) return false;
			sscanf(argv[i], "%lld", &para_twmvc_periodical_step_length);
			continue;
		}
		else return false;
	}
	
	if(!flag_opt)
	{
		target_optimal_size = 0;
	}
	
	if(decision_perform_vertex_weight_scheme && !flag_vertex_weight_scheme)
	{
		decision_perform_vertex_weight_scheme = false;
		init_vertex_weight_scheme_ptr = empty_function_ret_void;
		vertex_weight_scheme_ptr = empty_function_ret_void;
	}
	else if(!decision_perform_vertex_weight_scheme && flag_vertex_weight_scheme)
	{
		decision_perform_vertex_weight_scheme = true;
		init_vertex_weight_scheme_ptr = init_vertex_weight_scheme_twmvc;
		vertex_weight_scheme_ptr = vertex_weight_scheme_twmvc;
	}
	else if(!decision_perform_vertex_weight_scheme && !flag_vertex_weight_scheme)
	{
		decision_perform_vertex_weight_scheme = false;
		init_vertex_weight_scheme_ptr = empty_function_ret_void;
		vertex_weight_scheme_ptr = empty_function_ret_void;
	}
	else
	{
		decision_perform_vertex_weight_scheme = true;
	}
	
	if(flag_inst && flag_seed) return true;
	else return false;
}

#endif
