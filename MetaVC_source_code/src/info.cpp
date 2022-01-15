#ifndef _INFO_CPP
#define _INFO_CPP

#include "info.h"

string version_str = "1.2.5";

string get_last_level_name(string file_path)
{
	long long file_path_size = file_path.size();
	if(file_path[file_path_size-1] == '/')
		file_path = file_path.substr(0, file_path_size-1);
	long long pos = file_path.find_last_of('/');
	if(pos<0 || pos>=file_path.size())
		return file_path;
	else return file_path.substr(pos+1, file_path.size()-pos-1);	
}

void print_general_information(char *executable_name)
{
	string executable_name_str = executable_name;
	executable_name_str = get_last_level_name(executable_name_str);
	cout << "c" << endl;
	cout << "c MetaVC -- A Meta Local Search Framework for Minimum Vertex Cover (MinVC)" << endl;
	cout << "c Version: " << version_str << endl;
	cout << "c" << endl;
	return;
}

int get_default_print_sol()
{
	if(flag_print_sol) return 1;
	else return 0;
}

int get_default_perform_preprocess()
{
	if(decision_perform_preprocess) return 1;
	else return 0;
}

int get_default_init_sol()
{
	if(init_sol_heuristic_ptr == init_sol_dscore_heuristic)
		return 1;
	else if(init_sol_heuristic_ptr == init_sol_degree_heuristic)
		return 2;
	else return 1;
}

int get_default_perform_ruin_and_reconstruct()
{
	if(decision_perform_ruin_and_reconstruct) return 1;
	else return 0;
}

int get_default_perform_removing_random_walk()
{
	if(decision_perform_removing_random_walk)
		return 1;
	else return 0;
}

int get_default_perform_bms()
{
	if(select_removing_vertex_ptr == select_removing_vertex_not_bms)
		return 0;
	else if(select_removing_vertex_ptr == select_removing_vertex_bms)
		return 1;
	else return 0;
}

int get_default_sel_removing_v()
{
	if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_greedy_dscore_age)
		return 1;
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_greedy_dscore_random)
		return 2;
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_greedy_dscore_vertex_weight)
		return 3;
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_configuration_checking_age)
		return 4;
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_configuration_checking_random)
		return 5;
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_configuration_checking_vertex_weight)
		return 6;
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_tabu)
		return 7;
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_novelty)
		return 8;
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_probability_distribution)
		return 9;
	else return 1;
}

int get_default_perform_adding_random_walk()
{
	if(decision_perform_adding_random_walk)
		return 1;
	else return 0;
}

int get_default_perform_cc_adding()
{
	if(select_adding_vertex_ptr == select_adding_vertex_from_edge_not_using_configuration_checking)
		return 0;
	else if(select_adding_vertex_ptr == select_adding_vertex_from_edge_using_configuration_checking)
		return 1;
	else return 0;
}

int get_default_sel_adding_v()
{
	if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_greedy_dscore_age)
		return 1;
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_greedy_dscore_random)
		return 2;
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_twmvc)
		return 3;
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_tabu)
		return 4;
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_novelty)
		return 5;
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_probability_distribution)
		return 6;
	else return 1;
}

int get_default_sel_uncov_e()
{
	if(select_uncov_edge_heuristic_ptr == select_uncov_edge_random_heuristic)
		return 1;
	else if(select_uncov_edge_heuristic_ptr == select_uncov_edge_weight_distribution_heuristic)
		return 2;
	else return 1;
}

int get_default_perform_edge_weight_scheme()
{
	if(decision_perform_edge_weight_scheme)
		return 1;
	else return 0;
}

int get_default_sel_edge_weight_scheme()
{
	if(edge_weight_scheme_ptr == edge_weight_scheme_multiplicative_scaling_with_forgetting)
		return 1;
	else if(edge_weight_scheme_ptr == edge_weight_scheme_multiplicative_scaling)
		return 2;
	else if(edge_weight_scheme_ptr == edge_weight_scheme_paws)
		return 3;
	else if(edge_weight_scheme_ptr == edge_weight_scheme_paws_periodical)
		return 4;
	else return 1;
}

int get_default_perform_vertex_weight_scheme()
{
	if(decision_perform_vertex_weight_scheme)
		return 1;
	else return 0;
}

int get_default_sel_vertex_weight_scheme()
{
	if(vertex_weight_scheme_ptr == vertex_weight_scheme_twmvc)
		return 1;
	else if(vertex_weight_scheme_ptr == vertex_weight_scheme_twmvc_periodical)
		return 2;
	else return 1;
}

void print_usage_info(char *executable_name)
{
	default_algorithm_settings();
	cout << "c " << endl;
	cout << "c Usage: " << executable_name << "   (*Required*)" << endl
		 << "c -inst <instance_name>   (*Required*)" << endl
		 << "c -seed <seed>   (*Required*)" << endl
		 << "c -opt <target_optimal_size>   [Set it to 0 if you do not have any priori knowledge about the input instance]" << endl
		 << "c -print_sol {0, 1}   (Default: " << get_default_print_sol() << ") [Set it to 1 if you want to see the final solution (vertex cover)]" << endl
		 << "c -perform_preprocess {0, 1}   (Default: " << get_default_perform_preprocess() << ")" << endl
		 << "c -init_sol {1, 2}   (Default: " << get_default_init_sol() << ")" << endl
		 << "c -perform_ruin_and_reconstruct {0, 1}   (Default: " << get_default_perform_ruin_and_reconstruct() << ")" << endl
		 << "c -prob_ruin_and_reconstruct [0, 1]   (Default: " << para_prob_ruin_and_reconstruct << ")" << endl
		 << "c -num_vertex_ruin_and_reconstruct {int, from 1 to 100}   (Default: " << para_num_vertex_ruin_and_reconstruct << ")" << endl
		 << "c -perform_removing_random_walk {0, 1}   (Default: " << get_default_perform_removing_random_walk() << ")" << endl
		 << "c -removing_prob_random_walk [0, 1]   (Default: " << para_removing_prob_random_walk << ")" << endl
		 << "c -perform_bms {0, 1}   (Default: " << get_default_perform_bms() << ")" << endl
		 << "c -bms_k {int, from 20 to 1000}   (Default: " << para_bms_k << ")" << endl
		 << "c -sel_removing_v {1, 2, 3, 4, 5, 6, 7, 8, 9}   (Default: " << get_default_sel_removing_v() << ")" << endl
		 << "c -tabu_tenure {int, from 1 to 100}   (Default: " << para_tabu_tenure << ")" << endl
		 << "c -removing_prob_novelty [0, 1]   (Default: " << para_removing_prob_novelty << ")" << endl
		 << "c -prob_distri_c1 [2, 10]   (Default: " << para_prob_distri_c1 << ")" << endl
		 << "c -prob_distri_c2 {int, from 1 to 10}   (Default: " << para_prob_distri_c2 << ")" << endl
		 << "c -prob_distri_c3 {int, from 10000 to 1000000}   (Default: " << para_prob_distri_c3 << ")" << endl
		 << "c -perform_adding_random_walk {0, 1}   (Default: " << get_default_perform_adding_random_walk() << ")" << endl
		 << "c -adding_prob_random_walk [0, 1]   (Default: " << para_adding_prob_random_walk << ")" << endl
		 << "c -perform_cc_adding {0, 1}   (Default: " << get_default_perform_cc_adding() << ")" << endl
		 << "c -sel_adding_v {1, 2, 3, 4, 5, 6}   (Default: " << get_default_sel_adding_v() << ")" << endl
		 << "c -adding_prob_novelty [0, 1]   (Default: " << para_adding_prob_novelty << ")" << endl
		 << "c -sel_uncov_e {1, 2}   (Default: " << get_default_sel_uncov_e() << ")" << endl
		 << "c -perform_edge_weight_scheme {0, 1}   (Default: " << get_default_perform_edge_weight_scheme() << ")" << endl
		 << "c -sel_edge_weight_scheme {1, 2, 3, 4}   (Default: " << get_default_sel_edge_weight_scheme() << ")" << endl
		 << "c -edge_weight_threshold_scale [0, 1]   (Default: " << para_edge_weight_threshold_scale << ")" << endl
		 << "c -edge_weight_p_scale [0, 1]   (Default: " << para_edge_weight_p_scale << ")" << endl
		 << "c -edge_weight_q_scale [0, 1]   (Default: " << para_edge_weight_q_scale << ")" << endl
		 << "c -paws_smooth_probability [0, 1]   (Default: " << para_paws_smooth_probability << ")" << endl
		 << "c -paws_periodical_step_length {int, from 50 to 10000}   (Default: " << para_paws_periodical_step_length << ")" << endl
		 << "c -perform_vertex_weight_scheme {0, 1}   (Default: " << get_default_perform_vertex_weight_scheme() << ")" << endl
		 << "c -sel_vertex_weight_scheme {1, 2}   (Default: " << get_default_sel_vertex_weight_scheme() << ")" << endl
		 << "c -twmvc_smooth_probability [0, 1]   (Default: " << para_twmvc_smooth_probability << ")" << endl
		 << "c -twmvc_delta {int, from 1000 to 1000000}   (Default: " << para_twmvc_delta << ")" << endl
		 << "c -twmvc_beta [0, 1]   (Default: " << para_twmvc_beta << ")" << endl
		 << "c -twmvc_periodical_step_length {int, from 50 to 10000}   (Default: " << para_twmvc_periodical_step_length << ")" << endl;
	cout << "c" << endl;
	return;
}


void print_algorithm_settings_information()
{
	cout << "c" << endl;
	cout << "c instance = " << inst << endl;
	cout << "c seed = " << seed << endl;
	cout << "c target_optimal_size = " << target_optimal_size << endl;
	
	if(flag_print_sol)
	{
		cout << "c flag_print_sol = true" << endl;
	}
	else
	{
		cout << "c flag_print_sol = false" << endl;
	}
	
	if(decision_perform_preprocess)
	{
		cout << "c decision_perform_preprocess = true" << endl;
	}
	else
	{
		cout << "c decision_perform_preprocess = false" << endl;
	}
	
	if(init_sol_heuristic_ptr == init_sol_dscore_heuristic)
	{
		cout << "c init_sol_heuristic_ptr = init_sol_dscore_heuristic" << endl;
	}
	else if(init_sol_heuristic_ptr == init_sol_degree_heuristic)
	{
		cout << "c init_sol_heuristic_ptr = init_sol_degree_heuristic" << endl;
	}
	
	if(decision_perform_ruin_and_reconstruct)
	{
		cout << "c decision_perform_ruin_and_reconstruct = true" << endl;
		cout << "c para_prob_ruin_and_reconstruct = " << para_prob_ruin_and_reconstruct << endl;
		cout << "c para_num_vertex_ruin_and_reconstruct = " << para_num_vertex_ruin_and_reconstruct << endl;
	}
	else
	{
		cout << "c decision_perform_ruin_and_reconstruct = false" << endl;
	}
	
	if(decision_perform_removing_random_walk)
	{
		cout << "c decision_perform_removing_random_walk = true" << endl;
		cout << "c removing_prob_random_walk = " << para_removing_prob_random_walk << endl;
	}
	else
	{
		cout << "c decision_perform_removing_random_walk = false" << endl;
	}
	
	
	if(select_removing_vertex_ptr == select_removing_vertex_not_bms)
	{
		cout << "c select_removing_vertex_ptr = select_removing_vertex_not_bms" << endl;
	}
	else if(select_removing_vertex_ptr == select_removing_vertex_bms)
	{
		cout << "c select_removing_vertex_ptr = select_removing_vertex_bms" << endl;
		cout << "c bms_k = " << para_bms_k << endl;
	}
	
	if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_greedy_dscore_age)
	{
		cout << "c select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_age" << endl;
	}
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_greedy_dscore_random)
	{
		cout << "c select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_random" << endl;
	}
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_greedy_dscore_vertex_weight)
	{
		cout << "c select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_greedy_dscore_vertex_weight" << endl;
	}
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_configuration_checking_age)
	{
		cout << "c select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_configuration_checking_age" << endl;
	}
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_configuration_checking_random)
	{
		cout << "c select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_configuration_checking_random" << endl;
	}
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_configuration_checking_vertex_weight)
	{
		cout << "c select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_configuration_checking_vertex_weight" << endl;
	}
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_tabu)
	{
		cout << "c select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_tabu" << endl;
		cout << "c tabu_tenure = " << para_tabu_tenure << endl;
	}
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_novelty)
	{
		cout << "c select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_novelty" << endl;
		cout << "c removing_prob_novelty = " << para_removing_prob_novelty << endl;
	}
	else if(select_removing_vertex_in_set_ptr == select_removing_vertex_in_set_probability_distribution)
	{
		cout << "c select_removing_vertex_in_set_ptr = select_removing_vertex_in_set_probability_distribution" << endl;
		cout << "c prob_distri_c1 = " << para_prob_distri_c1 << endl;
		cout << "c prob_distri_c2 = " << para_prob_distri_c2 << endl;
		cout << "c prob_distri_c3 = " << para_prob_distri_c3 << endl;
	}
	
	if(decision_perform_adding_random_walk)
	{
		cout << "c decision_perform_adding_random_walk = true" << endl;
		cout << "c adding_prob_random_walk = " << para_adding_prob_random_walk << endl;
	}
	else
	{
		cout << "c decision_perform_adding_random_walk = false" << endl;
	}
	
	if(select_adding_vertex_ptr == select_adding_vertex_from_edge_not_using_configuration_checking)
	{
		cout << "c select_adding_vertex_ptr = select_adding_vertex_from_edge_not_using_configuration_checking" << endl;
	}
	else if(select_adding_vertex_ptr == select_adding_vertex_from_edge_using_configuration_checking)
	{
		cout << "c select_adding_vertex_ptr = select_adding_vertex_from_edge_using_configuration_checking" << endl;
	}
	
	if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_greedy_dscore_age)
	{
		cout << "c select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_greedy_dscore_age" << endl;
	}
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_greedy_dscore_random)
	{
		cout << "c select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_greedy_dscore_random" << endl;
	}
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_twmvc)
	{
		cout << "c select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_twmvc" << endl;
		cout << "c twmvc_delta = " << para_twmvc_delta << endl;
		cout << "c twmvc_beta = " << para_twmvc_beta << endl;
	}
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_tabu)
	{
		cout << "c select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_tabu" << endl;
		cout << "c tabu_tenure = " << para_tabu_tenure << endl;
	}
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_novelty)
	{
		cout << "c select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_novelty" << endl;
		cout << "c adding_prob_novelty = " << para_adding_prob_novelty << endl;
	}
	else if(select_adding_vertex_from_edge_ptr == select_adding_vertex_from_edge_probability_distribution)
	{
		cout << "c select_adding_vertex_from_edge_ptr = select_adding_vertex_from_edge_probability_distribution" << endl;
		cout << "c prob_distri_c1 = " << para_prob_distri_c1 << endl;
		cout << "c prob_distri_c2 = " << para_prob_distri_c2 << endl;
		cout << "c prob_distri_c3 = " << para_prob_distri_c3 << endl;
	}
	
	if(select_uncov_edge_heuristic_ptr == select_uncov_edge_random_heuristic)
	{
		cout << "c select_uncov_edge_heuristic_ptr = select_uncov_edge_random_heuristic" << endl;
	}
	else if(select_uncov_edge_heuristic_ptr == select_uncov_edge_weight_distribution_heuristic)
	{
		cout << "c select_uncov_edge_heuristic_ptr = select_uncov_edge_weight_distribution_heuristic" << endl;
	}
	
	if(decision_perform_edge_weight_scheme)
	{
		cout << "c decision_perform_edge_weight_scheme = true" << endl;
		if(edge_weight_scheme_ptr == edge_weight_scheme_multiplicative_scaling_with_forgetting)
		{
			cout << "c edge_weight_scheme_ptr = edge_weight_scheme_multiplicative_scaling_with_forgetting" << endl;
			cout << "c edge_weight_threshold_scale = " << para_edge_weight_threshold_scale << endl;
			cout << "c edge_weight_threshold = " << edge_weight_threshold << endl;
			cout << "c edge_weight_p_scale = " << para_edge_weight_p_scale << endl;
		}
		else if(edge_weight_scheme_ptr == edge_weight_scheme_multiplicative_scaling)
		{
			cout << "c edge_weight_scheme_ptr = edge_weight_scheme_multiplicative_scaling" << endl;
			cout << "c edge_weight_threshold_scale = " << para_edge_weight_threshold_scale << endl;
			cout << "c edge_weight_threshold = " << edge_weight_threshold << endl;
			cout << "c edge_weight_p_scale = " << para_edge_weight_p_scale << endl;
			cout << "c edge_weight_q_scale = " << para_edge_weight_q_scale << endl;
		}
		else if(edge_weight_scheme_ptr == edge_weight_scheme_paws)
		{
			cout << "c edge_weight_scheme_ptr = edge_weight_scheme_paws" << endl;
			cout << "c paws_smooth_probability = " << para_paws_smooth_probability << endl;
		}
		else if(edge_weight_scheme_ptr == edge_weight_scheme_paws_periodical)
		{
			cout << "c edge_weight_scheme_ptr = edge_weight_scheme_paws_periodical" << endl;
			cout << "c paws_periodical_step_length = " << para_paws_periodical_step_length << endl;
		}
	}
	else
	{
		cout << "c decision_perform_edge_weight_scheme = false" << endl;
		cout << "c edge_weight_scheme_ptr = empty_function_ret_void" << endl;
	}
	
	if(decision_perform_vertex_weight_scheme)
	{
		cout << "c decision_perform_vertex_weight_scheme = true" << endl;
		if(vertex_weight_scheme_ptr == vertex_weight_scheme_twmvc)
		{
			cout << "c vertex_weight_scheme_ptr = vertex_weight_scheme_twmvc" << endl;
			cout << "c twmvc_smooth_probability = " << para_twmvc_smooth_probability << endl;
		}
		else if(vertex_weight_scheme_ptr == vertex_weight_scheme_twmvc_periodical)
		{
			cout << "c vertex_weight_scheme_ptr = vertex_weight_scheme_twmvc_periodical" << endl;
			cout << "c twmvc_periodical_step_length = " << para_twmvc_periodical_step_length << endl;
		}
	}
	else
	{
		cout << "c decision_perform_vertex_weight_scheme = false" << endl;
		cout << "c vertex_weight_scheme_ptr = empty_function_ret_void" << endl;
	}
	
	return;
}

void print_solution_mis()
{
	int v;
	int mis_vertex_count = 0;
	
	for(v=1; v<=v_num; v++)
	{
		if(!best_v_in_c[v])
		{
			mis_vertex_count++;
		}
	}
	
	if(mis_vertex_count + best_c_size != v_num)
	{
		cout << "c The size of independent set + the size of vertex cover is not equal to |V(G)|!" << endl;
	}
	
	//cout << "c Best found independent set size = " << mis_vertex_count << endl;
	//cout << "c The following output is the found independent set." << endl;
	
	for(v=1; v<=v_num; v++)
	{
		if(!best_v_in_c[v])
		{
			cout << v << " ";
		}
	}
	cout << endl;
	return;
}

void print_solution_vc()
{
	int v;
	for(v=1; v<=v_num; v++)
	{
		if(best_v_in_c[v])
		{
			cout << v << " ";
		}
	}
	cout << endl;
	return;
}

#endif
