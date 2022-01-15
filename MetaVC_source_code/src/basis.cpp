#ifndef _BASIS_CPP
#define _BASIS_CPP

#include "basis.h"

Mersenne_rng rng;
int seed;
string inst;
int fix_vertices_size;
bool flag_print_sol;

//long long maxi_steps;
long long step;
int target_optimal_size;
clock_t start;
clock_t stop;

int v_num;
int e_num;

Edge *edge; //
long long *edge_weight; //

long long *dscore; //
long long *time_stamp; //
long long *vertex_weight; //
double* vertex_prob_value; //
int *tmp_vertex_array_with_ties; //
int tmp_vertex_array_with_ties_length; //

int **v_edges; //
int **v_adj; //
int *v_degree; //

int c_size;
bool *v_in_c; //
int *remove_cand; //
int *index_in_remove_cand; //
int remove_cand_size;

int best_c_size;
bool *best_v_in_c; //
double best_run_time;
long long best_step;

int *uncov_stack; //
int uncov_stack_fill_pointer;
int *index_in_uncov_stack; //

long long total_uncov_edge_weight;

int *conf_change; //
int tabu_remove;

long long avg_weight;
long long delta_total_weight;
long long scale_avg;
long long edge_weight_threshold;
double para_edge_weight_threshold_scale;
double para_edge_weight_p_scale;
double para_edge_weight_q_scale;

int* large_weight_edges;
int large_weight_edges_count;
double para_paws_smooth_probability;
long long para_paws_periodical_step_length;

int *large_weight_vertices;
int large_weight_vertices_count;
int *index_in_large_weight_vertices;
bool *vertex_flag_for_vertex_weight;
int *vertex_cache_for_vertex_weight;
int vertex_cache_for_vertex_weight_count;
double para_twmvc_smooth_probability;
long long para_twmvc_delta;
double para_twmvc_beta;
long long para_twmvc_periodical_step_length;

int *bms_cand_set;
int bms_cand_set_size;
int para_bms_k;

long long para_tabu_tenure;
double para_removing_prob_novelty;

double para_adding_prob_novelty;

double para_prob_distri_c1;
int para_prob_distri_c2;
int para_prob_distri_c3;

double para_prob_ruin_and_reconstruct;
int para_num_vertex_ruin_and_reconstruct;
int *removing_vertices_in_ruin_and_reconstruct;
int removing_vertices_in_ruin_and_reconstruct_size;
int *adding_vertices_in_ruin_and_reconstruct;
int adding_vertices_in_ruin_and_reconstruct_size;
vector<tmpNode> vector_vertex_not_in_cover;

double para_removing_prob_random_walk;
double para_adding_prob_random_walk;

bool decision_perform_preprocess;
bool decision_perform_ruin_and_reconstruct;
bool decision_perform_removing_random_walk;
bool decision_perform_adding_random_walk;
bool decision_perform_edge_weight_scheme;
bool decision_perform_vertex_weight_scheme;


const long long maximum_edge_weight_limit = 2147483646ll;

void reassign_istringstream(istringstream &iss, string line)
{
	iss.clear();
	iss.str(line);
	iss.seekg(0, ios::beg);
	return;
}

void allocate_memory(int v_num, int e_num)
{
	int malloc_adding_length = 10;
	int malloc_v_length = v_num + malloc_adding_length;
	int malloc_e_length = e_num + malloc_adding_length;
	
	dscore = new long long [malloc_v_length];
	time_stamp = new long long [malloc_v_length];
	vertex_weight = new long long [malloc_v_length];
	vertex_prob_value = new double [malloc_v_length];
	tmp_vertex_array_with_ties = new int [malloc_v_length];
	v_edges = new int* [malloc_v_length];
	v_adj = new int* [malloc_v_length];
	v_degree = new int [malloc_v_length];
	v_in_c = new bool [malloc_v_length];
	remove_cand = new int [malloc_v_length];
	index_in_remove_cand = new int [malloc_v_length];
	best_v_in_c = new bool [malloc_v_length];
	conf_change = new int [malloc_v_length];
	my_heap = new int [malloc_v_length];
	pos_in_my_heap = new int [malloc_v_length];
	large_weight_vertices = new int [malloc_v_length];
	index_in_large_weight_vertices = new int [malloc_v_length];
	vertex_flag_for_vertex_weight = new bool [malloc_v_length];
	vertex_cache_for_vertex_weight = new int [malloc_v_length];
	bms_cand_set = new int [malloc_v_length];
	removing_vertices_in_ruin_and_reconstruct = new int [malloc_v_length];
	adding_vertices_in_ruin_and_reconstruct = new int [malloc_v_length];
	
	edge = new Edge [malloc_e_length];
	edge_weight = new long long [malloc_e_length];
	uncov_stack = new int [malloc_e_length];
	index_in_uncov_stack = new int [malloc_e_length];
	large_weight_edges = new int [malloc_e_length];
	
	return;
}

void free_memory(int v_num, int e_num)
{
	int v;
	
	for(v=1; v<=v_num; v++)
	{
		delete [] v_edges[v];
		delete [] v_adj[v];
	}
	
	delete [] dscore;
	delete [] time_stamp;
	delete [] vertex_weight;
	delete [] vertex_prob_value;
	delete [] tmp_vertex_array_with_ties;
	delete [] v_edges;
	delete [] v_adj;
	delete [] v_degree;
	delete [] v_in_c;
	delete [] remove_cand;
	delete [] index_in_remove_cand;
	delete [] best_v_in_c;
	delete [] conf_change;
	delete [] my_heap;
	delete [] pos_in_my_heap;
	delete [] large_weight_vertices;
	delete [] index_in_large_weight_vertices;
	delete [] vertex_flag_for_vertex_weight;
	delete [] vertex_cache_for_vertex_weight;
	delete [] bms_cand_set;
	delete [] removing_vertices_in_ruin_and_reconstruct;
	delete [] adding_vertices_in_ruin_and_reconstruct;
	
	delete [] edge;
	delete [] edge_weight;
	delete [] uncov_stack;
	delete [] index_in_uncov_stack;
	delete [] large_weight_edges;
	
	return;
}

double compute_time(clock_t start, clock_t stop)
{
	double run_time = (double)(stop - start) / CLOCKS_PER_SEC;
	return run_time;
}

void update_best_sol()
{
	int v;
	for(v=1; v<=v_num; v++)
	{
		best_v_in_c[v] = v_in_c[v];
	}
	
	best_c_size = c_size;
	stop = clock();
	best_run_time = compute_time(start, stop);
	best_step = step;
	
	return;
}

bool build_instance(string inst)
{
	string line;
	istringstream iss;
	string tempstr1, tempstr2;
	int v, e;
	int v1, v2;
	
	ifstream fin;
	fin.open(inst.c_str(), ios::in);
	if(!fin.is_open()) return false;
	
	v_num = 0;
	e_num = 0;
	
	while(getline(fin, line))
	{
		if(line.substr(0, 1) == "p")
		{
			reassign_istringstream(iss, line);
			iss >> tempstr1 >> tempstr2 >> v_num >> e_num;
			break;
		}
	}
	
	best_c_size = v_num;
	
	allocate_memory(v_num, e_num);
	
	my_heap_count = 0;
	
	for(v=1; v<=v_num; v++)
	{
		v_degree[v] = 0;
	}
	
	for(e=0; e<e_num; e++)
	{
		fin >> tempstr1 >> v1 >> v2;
		v_degree[v1]++;
		v_degree[v2]++;
		
		edge[e].v1 = v1;
		edge[e].v2 = v2;
	}
	
	fin.close();
	
	for(v=1; v<=v_num; v++)
	{
		v_adj[v] = new int [v_degree[v]];
		v_edges[v] = new int [v_degree[v]];
	}
	
	int *v_edge_count_tmp = new int [v_num + 10];
	for(v=1; v<=v_num; v++)
	{
		v_edge_count_tmp[v] = 0;
	}
	
	for(e=0; e<e_num; e++)
	{
		v1 = edge[e].v1;
		v2 = edge[e].v2;
		
		v_edges[v1][v_edge_count_tmp[v1]] = e;
		v_edges[v2][v_edge_count_tmp[v2]] = e;
		
		v_adj[v1][v_edge_count_tmp[v1]] = v2;
		v_adj[v2][v_edge_count_tmp[v2]] = v1;
		
		v_edge_count_tmp[v1]++;
		v_edge_count_tmp[v2]++;
	}
	
	delete [] v_edge_count_tmp;
	
	return true;
}

bool build_instance(const vector<vector<long> > &adjacency_matrix)
{
	vector<vector<long> >::size_type v, e;
	int v1, v2;
	
	if(adjacency_matrix.size() == 1)
	{
		cout << "c The simplified graph is empty!" << endl;
		return false;
	}
	
	v_num = adjacency_matrix.size() - 1;
	
	e_num = 0;
	for (v = 1; v < adjacency_matrix.size(); v++)
	{
		e_num += adjacency_matrix[v].size();
	}
	e_num /= 2;
	
	allocate_memory(v_num, e_num);
	
	my_heap_count = 0;
	for(v = 1, e = 0; v < adjacency_matrix.size(); v++)
	{
		v_degree[v] = adjacency_matrix[v].size();
		for(auto u : adjacency_matrix[v])
		{
			if(v < (vector<vector<long> >::size_type)u)
			{
				edge[e].v1 = v;
				edge[e].v2 = u;
				e++;
			}
		}
	}
	
	for(v=1; v<=v_num; v++)
	{
		v_adj[v] = new int [v_degree[v]];
		v_edges[v] = new int [v_degree[v]];
	}
	
	int *v_edge_count_tmp = new int [v_num + 10];
	for(v=1; v<=v_num; v++)
	{
		v_edge_count_tmp[v] = 0;
	}
	
	for(e=0; e<e_num; e++)
	{
		v1 = edge[e].v1;
		v2 = edge[e].v2;
		
		v_edges[v1][v_edge_count_tmp[v1]] = e;
		v_edges[v2][v_edge_count_tmp[v2]] = e;
		
		v_adj[v1][v_edge_count_tmp[v1]] = v2;
		v_adj[v2][v_edge_count_tmp[v2]] = v1;
		
		v_edge_count_tmp[v1]++;
		v_edge_count_tmp[v2]++;
	}
	
	delete [] v_edge_count_tmp;
	
	return true;
}


void reset_remove_cand()
{
	int v, i;
	i = 0;
	for(v=1; v<=v_num; v++)
	{
		if(v_in_c[v])
		{
			remove_cand[i] = v;
			index_in_remove_cand[v] = i;
			i++;
		}
		else
		{
			index_in_remove_cand[v] = 0;
		}
	}
	
	remove_cand_size = i;
	return;
}


void update_target_size()
{
	int v, i;
	int best_removing_v;
	
	c_size--;
	
	best_removing_v = remove_cand[0];
	
	if(dscore[best_removing_v]!=0)
	{
		for(i=1; i<remove_cand_size; i++)
		{
			v = remove_cand[i];
			
			if(dscore[v]==0) break;
			
			if(dscore[v] > dscore[best_removing_v])
				best_removing_v = v;
		}
	}
	
	remove(best_removing_v);
	
	int last_remove_cand_v = remove_cand[--remove_cand_size];
	int index = index_in_remove_cand[best_removing_v];
	remove_cand[index] = last_remove_cand_v;
	index_in_remove_cand[last_remove_cand_v] = index;
	
	return;
}


/*
void update_target_size()
{
	bool init_flag;
	int maxi_improvement;
	int maxi_vertex;
	int v;
	
	c_size--;
	init_flag = false;
	
	for(v=1; v<=v_num; v++)
	{
		if(!v_in_c[v]) continue;
		else if(!init_flag || dscore[v] > maxi_improvement)
		{
			init_flag = true;
			maxi_improvement = dscore[v];
			maxi_vertex = v;
		}
	}
	
	remove(maxi_vertex);
	reset_remove_cand();
}
*/


void uncover(int e)
{
	index_in_uncov_stack[e] = uncov_stack_fill_pointer;
	push(e,uncov_stack);
	
	total_uncov_edge_weight += edge_weight[e];
}

void cover(int e)
{
	int index, last_uncov_edge;
	
	last_uncov_edge = pop(uncov_stack);
	index = index_in_uncov_stack[e];
	uncov_stack[index] = last_uncov_edge;
	index_in_uncov_stack[last_uncov_edge] = index;
	
	total_uncov_edge_weight -= edge_weight[e];
}



void init_sol()
{
	int v, e;
	
	for(v=1; v<=v_num; v++)
	{
		v_in_c[v] = false;
		dscore[v] = 0;
		
		conf_change[v] = 1;
		time_stamp[v] = 0;
	}
	
	for(e=0; e<e_num; e++)
	{
		edge_weight[e] = 1;
	}
	
	tmp_vertex_array_with_ties_length = 0;
	
	total_uncov_edge_weight = 0;
	
	init_sol_heuristic_ptr();
	
	update_best_sol();
	
	reset_remove_cand();
	
	init_edge_weight_scheme_ptr();
	init_vertex_weight_scheme_ptr();
	
	return;
}





void add(int v)
{
	v_in_c[v] = true;
	dscore[v] = -dscore[v];
	conf_change[v] = 0;
	
	int i, e, n;
	int edge_count = v_degree[v];
	
	for(i=0; i<edge_count; i++)
	{
		e = v_edges[v][i];
		n = v_adj[v][i];
		
		if(!v_in_c[n])
		{
			dscore[n] -= edge_weight[e];
			conf_change[n] = 1;
			
			cover(e);
		}
		else
		{
			dscore[n] += edge_weight[e];
			conf_change[n] = 1;
		}
	}
	return;
}

void remove(int v)
{
	v_in_c[v] = false;
	dscore[v] = -dscore[v];
	conf_change[v] = 0;
	
	int i, e, n;
	int edge_count = v_degree[v];
	
	for(i=0; i<edge_count; i++)
	{
		e = v_edges[v][i];
		n = v_adj[v][i];
		
		if(!v_in_c[n])
		{
			dscore[n] += edge_weight[e];
			conf_change[n] = 1;
			
			uncover(e);
		}
		else
		{
			dscore[n] -= edge_weight[e];
			conf_change[n] = 1;
		}
	}
	return;
}

bool check_solution()
{
	int e;
	
	for(e=0; e<e_num; e++)
	{
		if(!best_v_in_c[edge[e].v1] && !best_v_in_c[edge[e].v2])
		{
			cout<<"c Uncovered edge: " << e << endl;
			return false;
		}
	}
	
	return true;
}

#endif
