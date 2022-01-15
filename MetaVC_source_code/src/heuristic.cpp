#ifndef _HEURISTIC_CPP
#define _HEURISTIC_CPP

#include "heuristic.h"

//for empty functions
void empty_function_ret_void() {}


void add_init(int v)
{
	int pos;
	pos = pos_in_my_heap[v];
	my_heap_remove(pos);
	
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
			
			pos = pos_in_my_heap[n];
			my_heap_remove(pos);
			my_heap_insert(n);
			
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

void init_sol_dscore_heuristic()
{
	int v, e, i;
	int best_v;
	
	for(e=0; e<e_num; e++)
	{
		dscore[edge[e].v1] += edge_weight[e];
		dscore[edge[e].v2] += edge_weight[e];
	}
	
	uncov_stack_fill_pointer = 0;
	
	for(e=0; e<e_num; e++)
	{
		uncover(e);
	}
	
	for(v=1; v<=v_num; v++)
	{
		my_heap_insert(v);
	}
	
	
	for(i=0; uncov_stack_fill_pointer>0;)
	{
		best_v = my_heap[0];
		if(dscore[best_v]>0)
		{
			add_init(best_v);
			i++;
		}
	}
	
	
	c_size = i;
	
	for(v=1; v<=v_num; v++)
	{
		if(v_in_c[v] && dscore[v]==0)
		{
			remove(v);
			c_size--;
		}
	}
	
	return;
}


void init_sol_degree_heuristic()
{
	int v, e;
	int v1, v2;
	
	c_size = 0;
	for(e=0; e<e_num; e++)
	{
		v1 = edge[e].v1;
		v2 = edge[e].v2;
		
		if(!v_in_c[v1] && !v_in_c[v2])
		{
			if(v_degree[v1] > v_degree[v2])
			{
				v_in_c[v1] = true;
			}
			else
			{
				v_in_c[v2] = true;
			}
			c_size++;
		}
	}
	
	uncov_stack_fill_pointer = 0;
	
	for(e=0; e<e_num; e++)
	{
		v1 = edge[e].v1;
		v2 = edge[e].v2;
		
		if(v_in_c[v1] && !v_in_c[v2]) dscore[v1] -= edge_weight[e];
		else if(!v_in_c[v1] && v_in_c[v2]) dscore[v2] -= edge_weight[e];
	}
	
	for(v=1; v<=v_num; v++)
	{
		if(v_in_c[v] && dscore[v]==0)
		{
			remove(v);
			c_size--;
		}
	}
	
	return;
}

bool compare_degree(const tmpNode &v1, const tmpNode &v2)
{
	return v1.degree > v2.degree;
}

bool compare_dscore(const tmpNode &v1, const tmpNode &v2)
{
	return v1.dscore > v2.dscore;
}

void get_adding_vertices_in_ruin_and_reconstruct_degree(vector<tmpNode> &vector_vertex_not_in_cover)
{
	sort(vector_vertex_not_in_cover.begin(), vector_vertex_not_in_cover.end(), compare_degree);
}

void get_adding_vertices_in_ruin_and_reconstruct_dscore(vector<tmpNode> &vector_vertex_not_in_cover)
{
	sort(vector_vertex_not_in_cover.begin(), vector_vertex_not_in_cover.end(), compare_dscore);
}

int select_removing_vertex_in_set_greedy_dscore_age(int *the_set, int the_set_length)
{
	int v, i;
	int best_removing_v = -1;
	
	if(the_set_length == 1) return the_set[0];
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		if(v!=tabu_remove)
		{
			best_removing_v = v;
			break;
		}
	}
	
	for(i++; i<the_set_length; i++)
	{
		v = the_set[i];
		if(v==tabu_remove) continue;
		
		if(dscore[v] < dscore[best_removing_v])
			continue;
		else if(dscore[v] > dscore[best_removing_v])
			best_removing_v = v;
		else if(time_stamp[v] < time_stamp[best_removing_v])
			best_removing_v = v;
	}
	
	if(best_removing_v == -1)
		return the_set[rng.next(the_set_length)];
	
	return best_removing_v;
}

int select_removing_vertex_in_set_greedy_dscore_random(int *the_set, int the_set_length)
{
	int v, i;
	long long best_dscore;
	
	if(the_set_length == 1) return the_set[0];
	tmp_vertex_array_with_ties_length = 0;
	
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		if(v!=tabu_remove)
		{
			best_dscore = dscore[v];
			tmp_vertex_array_with_ties[0] = v;
			tmp_vertex_array_with_ties_length = 1;
			break;
		}
	}
	
	for(i++; i<the_set_length; i++)
	{
		v = the_set[i];
		if(v==tabu_remove) continue;
		
		if(dscore[v]<best_dscore)
			continue;
		else if(dscore[v]>best_dscore)
		{
			best_dscore = dscore[v];
			tmp_vertex_array_with_ties[0] = v;
			tmp_vertex_array_with_ties_length = 1;
		}
		else if(dscore[v]==best_dscore)
		{
			tmp_vertex_array_with_ties[tmp_vertex_array_with_ties_length++] = v;
		}
		
	}
	
	if(tmp_vertex_array_with_ties_length<=0)
		return the_set[rng.next(the_set_length)];
	
	return tmp_vertex_array_with_ties[rng.next(tmp_vertex_array_with_ties_length)];
}


int select_removing_vertex_in_set_greedy_dscore_vertex_weight(int *the_set, int the_set_length)
{
	int v, i;
	int best_removing_v = -1;
	
	if(the_set_length == 1) return the_set[0];
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		if(v!=tabu_remove)
		{
			best_removing_v = v;
			break;
		}
	}
	
	for(i++; i<the_set_length; i++)
	{
		v = the_set[i];
		if(v==tabu_remove) continue;
		
		if(dscore[v] < dscore[best_removing_v])
			continue;
		else if(dscore[v] > dscore[best_removing_v])
			best_removing_v = v;
		else if(vertex_weight[v] > vertex_weight[best_removing_v])
			best_removing_v = v;
	}
	
	if(best_removing_v == -1)
		return the_set[rng.next(the_set_length)];
	
	return best_removing_v;
}


int select_removing_vertex_in_set_configuration_checking_age(int *the_set, int the_set_length)
{
	int v, i;
	int best_removing_v = -1;
	
	if(the_set_length == 1) return the_set[0];
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		if(conf_change[v]==1)
		{
			best_removing_v = v;
			break;
		}
	}
	
	for(i++; i<the_set_length; i++)
	{
		v = the_set[i];
		if(conf_change[v]==0) continue;
		
		if(dscore[v] < dscore[best_removing_v])
			continue;
		else if(dscore[v] > dscore[best_removing_v])
			best_removing_v = v;
		else if(time_stamp[v] < time_stamp[best_removing_v])
			best_removing_v = v;
	}
	
	if(best_removing_v == -1)
		return the_set[rng.next(the_set_length)];
	
	return best_removing_v;
}

int select_removing_vertex_in_set_configuration_checking_random(int *the_set, int the_set_length)
{
	int v, i;
	long long best_dscore;
	
	if(the_set_length == 1) return the_set[0];
	tmp_vertex_array_with_ties_length = 0;
	
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		if(conf_change[v]==1)
		{
			best_dscore = dscore[v];
			tmp_vertex_array_with_ties[0] = v;
			tmp_vertex_array_with_ties_length = 1;
			break;
		}
	}
	
	for(i++; i<the_set_length; i++)
	{
		v = the_set[i];
		if(conf_change[v]==0) continue;
		
		if(dscore[v]<best_dscore)
			continue;
		else if(dscore[v]>best_dscore)
		{
			best_dscore = dscore[v];
			tmp_vertex_array_with_ties[0] = v;
			tmp_vertex_array_with_ties_length = 1;
		}
		else if(dscore[v]==best_dscore)
		{
			tmp_vertex_array_with_ties[tmp_vertex_array_with_ties_length++] = v;
		}
		
	}
	
	if(tmp_vertex_array_with_ties_length<=0)
		return the_set[rng.next(the_set_length)];
	
	return tmp_vertex_array_with_ties[rng.next(tmp_vertex_array_with_ties_length)];
}

int select_removing_vertex_in_set_configuration_checking_vertex_weight(int *the_set, int the_set_length)
{
	int v, i;
	int best_removing_v = -1;
	
	if(the_set_length == 1) return the_set[0];
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		if(conf_change[v]==1)
		{
			best_removing_v = v;
			break;
		}
	}
	
	for(i++; i<the_set_length; i++)
	{
		v = the_set[i];
		if(conf_change[v]==0) continue;
		
		if(dscore[v] < dscore[best_removing_v])
			continue;
		else if(dscore[v] > dscore[best_removing_v])
			best_removing_v = v;
		else if(vertex_weight[v] > vertex_weight[best_removing_v])
			best_removing_v = v;
	}
	
	if(best_removing_v == -1)
		return the_set[rng.next(the_set_length)];
	
	return best_removing_v;
}



int select_removing_vertex_in_set_tabu(int *the_set, int the_set_length)
{
	int v, i;
	int best_removing_v = -1;
	
	if(the_set_length == 1) return the_set[0];
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		if(time_stamp[v]+para_tabu_tenure<step)
		{
			best_removing_v = v;
			break;
		}
	}
	
	for(i++; i<the_set_length; i++)
	{
		v = the_set[i];
		if(time_stamp[v]+para_tabu_tenure>=step) continue;
		
		if(dscore[v] < dscore[best_removing_v])
			continue;
		else if(dscore[v] > dscore[best_removing_v])
			best_removing_v = v;
		else if(time_stamp[v] < time_stamp[best_removing_v])
			best_removing_v = v;
	}
	
	if(best_removing_v == -1)
		return the_set[rng.next(the_set_length)];
	
	return best_removing_v;
}

int select_removing_vertex_in_set_novelty(int *the_set, int the_set_length)
{
	int v, i;
	int best_removing_v, second_best_removing_v;
	long long greatest_time_stamp;
	
	if(the_set_length == 1) return the_set[0];
	
	best_removing_v = the_set[0];
	greatest_time_stamp = time_stamp[the_set[0]];
	for(i=1; i<the_set_length; i++)
	{
		v = the_set[i];
		if(greatest_time_stamp<time_stamp[v])
			greatest_time_stamp = time_stamp[v];
		
		if(dscore[v]>dscore[best_removing_v])
			best_removing_v = v;
		else if(dscore[v]==dscore[best_removing_v] && time_stamp[v]<time_stamp[best_removing_v])
			best_removing_v = v;
	}
	
	if(time_stamp[best_removing_v]!=greatest_time_stamp)
		return best_removing_v;
	
	if(rng.nextClosed()>=para_removing_prob_novelty)
		return best_removing_v;
	
	second_best_removing_v = -1;
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		if(v!=best_removing_v)
		{
			second_best_removing_v = v;
			break;
		}
	}
	for(i++; i<the_set_length; i++)
	{
		v = the_set[i];
		if(v==best_removing_v) continue;
		if(dscore[v] > dscore[second_best_removing_v])
			second_best_removing_v = v;
		else if(dscore[v] == dscore[second_best_removing_v] && time_stamp[v] < time_stamp[second_best_removing_v])
			second_best_removing_v = v;
	}
	
	if(second_best_removing_v == -1)
		return best_removing_v;
	else return second_best_removing_v;
}

int select_removing_vertex_in_set_probability_distribution(int *the_set, int the_set_length)
{
	int v, i;
	double prob_distri_dscore;
	double prob_distri_age;
	double age_v;
	double sum_prob_value = 0.0;
	double random_prob;
	double random_prob_value;
	
	sum_prob_value = 0.0;
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		prob_distri_dscore = pow(para_prob_distri_c1, dscore[v]);
		age_v = step - time_stamp[v];
		prob_distri_age = 1.0 + pow((double)age_v/(double)para_prob_distri_c3, para_prob_distri_c2);
		vertex_prob_value[v] = prob_distri_dscore * prob_distri_age;
		sum_prob_value += vertex_prob_value[v];
	}
	
	random_prob = rng.nextClosed();
	random_prob_value = random_prob * sum_prob_value;
	
	sum_prob_value = 0;
	for(i=0; i<the_set_length; i++)
	{
		v = the_set[i];
		sum_prob_value += vertex_prob_value[v];
		if(sum_prob_value>=random_prob_value)
			return v;
	}
	
	return the_set[rng.next(the_set_length)];
}




int select_adding_vertex_from_edge_greedy_dscore_age(int v1, int v2)
{
	if(dscore[v1]>dscore[v2] || (dscore[v1]==dscore[v2] && time_stamp[v1]<time_stamp[v2]))
		return v1;
	else return v2;
}

int select_adding_vertex_from_edge_greedy_dscore_random(int v1, int v2)
{
	if(dscore[v1]>dscore[v2])
		return v1;
	else if(dscore[v1]<dscore[v2])
		return v2;
	else
	{
		if(rng.next(2) == 0)
			return v1;
		else return v2;
	}
}

int select_adding_vertex_from_edge_twmvc(int v1, int v2)
{
	int best_adding_v, index;
	long long vertex_weight_diff_abs;
	long long ori_vertex_weight_best_adding_v = -1;
	
	if(vertex_weight[v1] > vertex_weight[v2])
		vertex_weight_diff_abs = vertex_weight[v1] - vertex_weight[v2];
	else vertex_weight_diff_abs = vertex_weight[v2] - vertex_weight[v1];
	
	//cout << "c debug " << vertex_weight[v1] << " " << vertex_weight[v2] << endl;
	
	if(vertex_weight_diff_abs > para_twmvc_delta)
	{
		if(vertex_weight[v1]>vertex_weight[v2])
			best_adding_v = v1;
		else best_adding_v = v2;
		
		ori_vertex_weight_best_adding_v = vertex_weight[best_adding_v];
		
		vertex_weight[best_adding_v] = vertex_weight[best_adding_v]*para_twmvc_beta;
	
		if(ori_vertex_weight_best_adding_v>0 && vertex_weight[best_adding_v]==0)
		{
			index = index_in_large_weight_vertices[best_adding_v];
			index_in_large_weight_vertices[best_adding_v] = -1;
			large_weight_vertices[index] = large_weight_vertices[--large_weight_vertices_count];
			index_in_large_weight_vertices[large_weight_vertices[index]] = index;
		}
	}
	else
	{
		if(dscore[v1]>dscore[v2] || (dscore[v1]==dscore[v2] && time_stamp[v1]<time_stamp[v2]))
			best_adding_v = v1;
		else best_adding_v = v2;
	}
	
	return best_adding_v;
}

int select_adding_vertex_from_edge_tabu(int v1, int v2)
{
	bool v1_tabued = false, v2_tabued = false;
	
	if(time_stamp[v1]+para_tabu_tenure<step)
		v1_tabued = false;
	else v1_tabued = true;
	
	if(time_stamp[v2]+para_tabu_tenure<step)
		v2_tabued = false;
	else v2_tabued = true;
	
	if(!v1_tabued && v2_tabued) return v1;
	else if(v1_tabued && !v2_tabued) return v2;
	else return select_adding_vertex_from_edge_greedy_dscore_age(v1, v2);
}

int select_adding_vertex_from_edge_novelty(int v1, int v2)
{
	int best_adding_v;
	int other_adding_v;
	
	if(dscore[v1] > dscore[v2])
	{
		best_adding_v = v1;
		other_adding_v = v2;
	}
	else if(dscore[v1] < dscore[v2])
	{
		best_adding_v = v2;
		other_adding_v = v1;
	}
	else
	{
		if(time_stamp[v1] < time_stamp[v2]) return v1;
		else return v2;
	}
	
	if(time_stamp[best_adding_v] < time_stamp[other_adding_v])
		return best_adding_v;
	else
	{
		if(rng.nextClosed()<para_adding_prob_novelty)
			return other_adding_v;
		else return best_adding_v;
	}
}

int select_adding_vertex_from_edge_probability_distribution(int v1, int v2)
{
	double prob_distri_dscore_v1, prob_distri_dscore_v2;
	double prob_distri_age_v1, prob_distri_age_v2;
	double age_v1, age_v2;
	double vertex_prob_value_v1, vertex_prob_value_v2;
	double sum_prob_value = 0.0;
	double random_prob;
	double random_prob_value;
	
	double greater_dscore;
	if(dscore[v1] > dscore[v2]) greater_dscore = dscore[v1];
	else greater_dscore = dscore[v2];
	
	prob_distri_dscore_v1 = pow(para_prob_distri_c1, dscore[v1]-greater_dscore);
	age_v1 = step - time_stamp[v1];
	prob_distri_age_v1 = 1.0 + pow((double)age_v1/(double)para_prob_distri_c3, para_prob_distri_c2);
	vertex_prob_value_v1 = prob_distri_dscore_v1 * prob_distri_age_v1;
	
	prob_distri_dscore_v2 = pow(para_prob_distri_c1, dscore[v2]-greater_dscore);
	age_v2 = step - time_stamp[v2];
	prob_distri_age_v2 = 1.0 + pow((double)age_v2/(double)para_prob_distri_c3, para_prob_distri_c2);
	vertex_prob_value_v2 = prob_distri_dscore_v2 * prob_distri_age_v2;
	
	sum_prob_value = vertex_prob_value_v1 + vertex_prob_value_v2;
	random_prob = rng.nextClosed();
	random_prob_value = random_prob * sum_prob_value;	
	
	if(vertex_prob_value_v1 >= random_prob)
		return v1;
	else return v2;
}


int select_uncov_edge_random_heuristic()
{
	return uncov_stack[rng.next(uncov_stack_fill_pointer)];
}

int select_uncov_edge_weight_distribution_heuristic()
{
	long long random_value;
	double random_prob;
	long long value_sum = 0;
	int i, e;
	
	if(uncov_stack_fill_pointer==1) return uncov_stack[0];
	
	if(total_uncov_edge_weight<maximum_edge_weight_limit)
	{
		random_value = rng.next(total_uncov_edge_weight) + 1;
	}
	else
	{
		random_prob = rng.nextClosed();
		random_value = (total_uncov_edge_weight - 1) * random_prob + 1;
		if(random_value < 1) random_value = 1;
		else if(random_value > total_uncov_edge_weight) random_value = total_uncov_edge_weight;
	}
	
	e = -1;
	value_sum = 0;
	for(i=0; i<uncov_stack_fill_pointer; i++)
	{
		e = uncov_stack[i];
		value_sum += edge_weight[e];
		if(random_value<=value_sum)
			break;
	}
	if(e == -1) e = uncov_stack[rng.next(uncov_stack_fill_pointer)];
	return e;
}




void init_edge_weight_scheme_multiplicative_scaling_with_forgetting()
{
	//do noting here
	return;
}

void multiplicative_scaling_edge_weights_with_forgetting()
{
	int v, e;
	int v1, v2;
	long long new_total_weight = 0;
	
	for(v=1; v<=v_num; v++)
	{
		dscore[v] = 0;
	}
	
	total_uncov_edge_weight = 0;
	
	for(e=0; e<e_num; e++)
	{
		edge_weight[e] = edge_weight[e]*para_edge_weight_p_scale;
		if(edge_weight[e] <= 1) edge_weight[e] = 1;
		
		new_total_weight += edge_weight[e];
		
		v1 = edge[e].v1;
		v2 = edge[e].v2;
		
		if(!v_in_c[v1] && !v_in_c[v2])
		{
			dscore[v1] += edge_weight[e];
			dscore[v2] += edge_weight[e];
			
			total_uncov_edge_weight += edge_weight[e];
		}
		else if(!v_in_c[v1] && v_in_c[v2])
		{
			dscore[v2] -= edge_weight[e];
		}
		else if(v_in_c[v1] && !v_in_c[v2])
		{
			dscore[v1] -= edge_weight[e];
		}
	}
	
	avg_weight = new_total_weight/e_num;
	delta_total_weight = new_total_weight - avg_weight*e_num;
	
	return;
}

void edge_weight_scheme_multiplicative_scaling_with_forgetting()
{
	int i, e;
	
	for(i=0; i<uncov_stack_fill_pointer; i++)
	{
		e = uncov_stack[i];
		
		edge_weight[e] += 1;
		dscore[edge[e].v1] += 1;
		dscore[edge[e].v2] += 1;
	}
	
	total_uncov_edge_weight += uncov_stack_fill_pointer;
	
	delta_total_weight += uncov_stack_fill_pointer;
	if(delta_total_weight>=e_num)
	{
		avg_weight += 1;
		delta_total_weight -= e_num;
	}
	
	if(avg_weight>=edge_weight_threshold)
	{
		multiplicative_scaling_edge_weights_with_forgetting();
	}
	
	return;
}


void init_edge_weight_scheme_multiplicative_scaling()
{
	scale_avg = (edge_weight_threshold+1) * para_edge_weight_q_scale;
	return;
}

void multiplicative_scaling_edge_weights()
{
	int v, e;
	int v1, v2;
	long long new_total_weight = 0;
	
	for(v=1; v<=v_num; v++)
	{
		dscore[v] = 0;
	}
	
	total_uncov_edge_weight = 0;
	
	for(e=0; e<e_num; e++)
	{
		edge_weight[e] = edge_weight[e]*para_edge_weight_p_scale + scale_avg;
		if(edge_weight[e] <= 1) edge_weight[e] = 1;
		
		new_total_weight += edge_weight[e];
		
		v1 = edge[e].v1;
		v2 = edge[e].v2;
		
		if(!v_in_c[v1] && !v_in_c[v2])
		{
			dscore[v1] += edge_weight[e];
			dscore[v2] += edge_weight[e];
			
			total_uncov_edge_weight += edge_weight[e];
		}
		else if(!v_in_c[v1] && v_in_c[v2])
		{
			dscore[v2] -= edge_weight[e];
		}
		else if(v_in_c[v1] && !v_in_c[v2])
		{
			dscore[v1] -= edge_weight[e];
		}
	}
	
	avg_weight = new_total_weight/e_num;
	delta_total_weight = new_total_weight - avg_weight*e_num;
	
	return;
}

void edge_weight_scheme_multiplicative_scaling()
{
	int i, e;
	
	for(i=0; i<uncov_stack_fill_pointer; i++)
	{
		e = uncov_stack[i];
		
		edge_weight[e] += 1;
		dscore[edge[e].v1] += 1;
		dscore[edge[e].v2] += 1;
	}
	
	total_uncov_edge_weight += uncov_stack_fill_pointer;
	
	delta_total_weight += uncov_stack_fill_pointer;
	if(delta_total_weight>=e_num)
	{
		avg_weight += 1;
		delta_total_weight -= e_num;
	}
	
	if(avg_weight>=edge_weight_threshold)
	{
		multiplicative_scaling_edge_weights();
	}
	
	return;
}



void init_edge_weight_scheme_paws()
{
	large_weight_edges_count = 0;
}

void dec_edge_weight_paws()
{
	int i, e, v1, v2;
	for(i=0; i<large_weight_edges_count; i++)
	{
		e = large_weight_edges[i];
		v1 = edge[e].v1;
		v2 = edge[e].v2;
		
		if(v_in_c[v1] || v_in_c[v2])
		{
			delta_total_weight -= edge_weight[e];
			edge_weight[e]--;
			
			if(edge_weight[e]<1) edge_weight[e] = 1;
			
			delta_total_weight += edge_weight[e];
			if(delta_total_weight<0)
			{
				avg_weight--;
				delta_total_weight += e_num;
			}
			
			if(edge_weight[e] == 1)
			{
				large_weight_edges[i] = large_weight_edges[--large_weight_edges_count];
				i--;
			}
			
			if(v_in_c[v1] && !v_in_c[v2])
			{
				dscore[v1]++;
			}
			else if(!v_in_c[v1] && v_in_c[v2])
			{
				dscore[v2]++;
			}
		}
	}
	
	return;
}

void inc_edge_weight_paws()
{
	int i, e, v1, v2;
	
	for(i=0; i<uncov_stack_fill_pointer; i++)
	{
		e = uncov_stack[i];
		v1 = edge[e].v1;
		v2 = edge[e].v2;
		
		edge_weight[e]++;
		if(edge_weight[e] == 2)
		{
			large_weight_edges[large_weight_edges_count++] = e;
		}
		
		dscore[v1]++;
		dscore[v2]++;
	}
	
	total_uncov_edge_weight += uncov_stack_fill_pointer;
	
	delta_total_weight += uncov_stack_fill_pointer;
	if(delta_total_weight > e_num)
	{
		avg_weight++;
		delta_total_weight -= e_num;
	}
	
	return;
}

void edge_weight_scheme_paws()
{
	if(rng.nextClosed()<para_paws_smooth_probability)
		dec_edge_weight_paws();
	else inc_edge_weight_paws();
	
	return;
}



void init_edge_weight_scheme_paws_periodical()
{
	init_edge_weight_scheme_paws();
	if(para_paws_periodical_step_length <= 0)
		para_paws_periodical_step_length = 200;
	return;
}

void dec_edge_weight_paws_periodical()
{
	dec_edge_weight_paws();
	return;
}

void inc_edge_weight_paws_periodical()
{
	inc_edge_weight_paws();
	return;
}

void edge_weight_scheme_paws_periodical()
{
	if(step%para_paws_periodical_step_length == 0)
		dec_edge_weight_paws_periodical();
	else inc_edge_weight_paws_periodical();
	
	return;
}



void init_vertex_weight_scheme_twmvc()
{
	int v;
	for(v=1; v<=v_num; v++)
	{
		vertex_weight[v] = 0;
		index_in_large_weight_vertices[v] = -1;
		vertex_flag_for_vertex_weight[v] = false;
	}
	vertex_weight[0] = 0;
	large_weight_vertices_count = 0;
	vertex_cache_for_vertex_weight_count = 0;
	return;
}

void dec_vertex_weight_scheme_twmvc()
{
	int v, i;
	
	for(i=0; i<large_weight_vertices_count; i++)
	{
		v = large_weight_vertices[i];
		if(v_in_c[v] && vertex_weight[v]>0)
		{
			vertex_weight[v]--;
			
			if(vertex_weight[v] == 0)
			{
				large_weight_vertices[i] = large_weight_vertices[--large_weight_vertices_count];
				index_in_large_weight_vertices[v] = -1;
				index_in_large_weight_vertices[large_weight_vertices[i]] = i;
				
				i--;
			}
		}
	}
	return;
}

/*
Original TwMVC increases weights for those vertices which are not in C, but the TwMVC's implementation is time-consuming.
Here, our implementation only increases weights for those vertices which appear in at least one uncovered edge.
*/
void inc_vertex_weight_scheme_twmvc()
{
	int v, e, i;
	
	vertex_cache_for_vertex_weight_count = 0;
	
	for(i=0; i<uncov_stack_fill_pointer; i++)
	{
		e = uncov_stack[i];
		
		v = edge[e].v1;
		if(!vertex_flag_for_vertex_weight[v])
		{
			vertex_flag_for_vertex_weight[v] = true;
			vertex_weight[v]++;
			vertex_cache_for_vertex_weight[vertex_cache_for_vertex_weight_count++] = v;
			
			if(vertex_weight[v] == 1)
			{
				large_weight_vertices[large_weight_vertices_count++] = v;
				index_in_large_weight_vertices[v] = large_weight_vertices_count-1;
			}
		}
		
		v = edge[e].v2;
		if(!vertex_flag_for_vertex_weight[v])
		{
			vertex_flag_for_vertex_weight[v] = true;
			vertex_weight[v]++;
			vertex_cache_for_vertex_weight[vertex_cache_for_vertex_weight_count++] = v;
			
			if(vertex_weight[v] == 1)
			{
				large_weight_vertices[large_weight_vertices_count++] = v;
				index_in_large_weight_vertices[v] = large_weight_vertices_count-1;
			}
		}
	}
	
	for(i=0; i<vertex_cache_for_vertex_weight_count; i++)
	{
		v = vertex_cache_for_vertex_weight[i];
		vertex_flag_for_vertex_weight[v] = false;
	}

	return;
}

void vertex_weight_scheme_twmvc()
{
	if(rng.nextClosed()<para_twmvc_smooth_probability)
		dec_vertex_weight_scheme_twmvc();
	else inc_vertex_weight_scheme_twmvc();
	return;
}



void init_vertex_weight_scheme_twmvc_periodical()
{
	init_vertex_weight_scheme_twmvc();
	if(para_twmvc_periodical_step_length<=0)
		para_twmvc_periodical_step_length = 100;
	return;
}

void dec_vertex_weight_scheme_twmvc_periodical()
{
	dec_vertex_weight_scheme_twmvc();
}

void inc_vertex_weight_scheme_twmvc_periodical()
{
	inc_vertex_weight_scheme_twmvc();
}

void vertex_weight_scheme_twmvc_periodical()
{
	if(step%para_twmvc_periodical_step_length == 0)
		dec_vertex_weight_scheme_twmvc();
	else inc_vertex_weight_scheme_twmvc();
	return;
}


#endif
