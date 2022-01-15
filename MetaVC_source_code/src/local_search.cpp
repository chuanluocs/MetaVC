#ifndef _LOCAL_SEARCH_CPP
#define _LOCAL_SEARCH_CPP

#include "local_search.h"

void get_removing_vertices_in_ruin_and_reconstruct(int num_v_ruin_and_reconstruct)
{
	int i, v, pos, last_v, tmp_remove_cand_size;
	
	removing_vertices_in_ruin_and_reconstruct_size = 0;
	tmp_remove_cand_size = remove_cand_size;
	
	for(i=0; i<num_v_ruin_and_reconstruct; i++)
	{
		pos = rng.next(tmp_remove_cand_size);
		
		v = remove_cand[pos];
		last_v = remove_cand[tmp_remove_cand_size-1];
		
		index_in_remove_cand[v] = tmp_remove_cand_size-1;
		index_in_remove_cand[last_v] = pos;
		
		remove_cand[tmp_remove_cand_size-1] = v;
		remove_cand[pos] = last_v;
		
		removing_vertices_in_ruin_and_reconstruct[removing_vertices_in_ruin_and_reconstruct_size++] = v;
		
		tmp_remove_cand_size--;
	}
	
	return;
}

void get_adding_vertices_in_ruin_and_reconstruct(int num_v_ruin_and_reconstruct)
{
	int i, v;
	tmpNode tmp_vertex;
	
	vector_vertex_not_in_cover.clear();
	vector <tmpNode>().swap(vector_vertex_not_in_cover);
	
	for(v=1; v<=v_num; v++)
	{
		if(!v_in_c[v])
		{
			tmp_vertex.vertex = v;
			tmp_vertex.degree = v_degree[v];
			tmp_vertex.dscore = dscore[v];
			vector_vertex_not_in_cover.push_back(tmp_vertex);
		}
	}
	
	get_adding_vertices_in_ruin_and_reconstruct_ptr(vector_vertex_not_in_cover);
	/*
	for(i=0; i<vector_vertex_not_in_cover.size(); i++)
	{
		cout << vector_vertex_not_in_cover[i].vertex << " " << vector_vertex_not_in_cover[i].degree << " " << vector_vertex_not_in_cover[i].dscore << endl;
	}
	*/
	adding_vertices_in_ruin_and_reconstruct_size = 0;
	for(i=0; i<num_v_ruin_and_reconstruct; i++)
	{
		v = vector_vertex_not_in_cover[i].vertex;
		adding_vertices_in_ruin_and_reconstruct[adding_vertices_in_ruin_and_reconstruct_size++] = v;
	}
	
	return;
}

void ruin_and_reconstruct(int num_v_ruin_and_reconstruct, long long step)
{
	int i, v, v1, v2, index;
	
	if(num_v_ruin_and_reconstruct <=0) return;
	
	get_removing_vertices_in_ruin_and_reconstruct(num_v_ruin_and_reconstruct);
	get_adding_vertices_in_ruin_and_reconstruct(num_v_ruin_and_reconstruct);
	
	
	for(i=0; i<removing_vertices_in_ruin_and_reconstruct_size; i++)
	{
		v = removing_vertices_in_ruin_and_reconstruct[i];
		remove(v);
	}
	
	for(i=0; i<adding_vertices_in_ruin_and_reconstruct_size; i++)
	{
		v = adding_vertices_in_ruin_and_reconstruct[i];
		add(v);
	}
	
	for(i=0; i<num_v_ruin_and_reconstruct; i++)
	{
		v1 = removing_vertices_in_ruin_and_reconstruct[i];
		v2 = adding_vertices_in_ruin_and_reconstruct[i];
		
		index = index_in_remove_cand[v1];
		index_in_remove_cand[v1] = 0;
		
		remove_cand[index] = v2;
		index_in_remove_cand[v2] = index;
		
		time_stamp[v1] = step;
		time_stamp[v2] = step;
	}
	
	return;
}

int select_removing_vertex_random_walk()
{
	return remove_cand[rng.next(remove_cand_size)];
}

int select_removing_vertex_not_bms()
{
	int best_removing_v;
	best_removing_v = select_removing_vertex_in_set_ptr(remove_cand, remove_cand_size);
	return best_removing_v;
}

int select_removing_vertex_bms()
{
	int i, v, best_removing_v;
	
	if(remove_cand_size > para_bms_k)
	{
		bms_cand_set_size = 0;
		for(i=0; i<para_bms_k; i++)
		{
			v = remove_cand[rng.next(remove_cand_size)];
			bms_cand_set[bms_cand_set_size++] = v;
		}
		best_removing_v = select_removing_vertex_in_set_ptr(bms_cand_set, bms_cand_set_size);
	}
	else
	{
		best_removing_v = select_removing_vertex_in_set_ptr(remove_cand, remove_cand_size);
	}
	
	return best_removing_v;
}


int select_adding_vertex_random_walk(int e)
{
	int v1, v2;
	
	v1 = edge[e].v1;
	v2 = edge[e].v2;
	
	if(rng.next(2) == 0)
		return v1;
	else return v2;
}

int select_adding_vertex_from_edge_using_configuration_checking(int e)
{
	int best_adding_v;
	int v1, v2;
	
	v1 = edge[e].v1;
	v2 = edge[e].v2;
	
	if(conf_change[v1] == 0) best_adding_v = v2;
	else if(conf_change[v2] == 0) best_adding_v = v1;
	else
	{
		best_adding_v = select_adding_vertex_from_edge_ptr(v1, v2);
	}
	
	return best_adding_v;
}

int select_adding_vertex_from_edge_not_using_configuration_checking(int e)
{
	int best_adding_v;
	int v1, v2;
	
	v1 = edge[e].v1;
	v2 = edge[e].v2;
	
	best_adding_v = select_adding_vertex_from_edge_ptr(v1, v2);
	
	return best_adding_v;
}


void exchange_and_update(int best_removing_v, int best_adding_v, long long step)
{
	int index;
	
	index = index_in_remove_cand[best_removing_v];
	index_in_remove_cand[best_removing_v] = 0;
	
	remove_cand[index] = best_adding_v;
	index_in_remove_cand[best_adding_v] = index;
	
	time_stamp[best_removing_v] = step;
	time_stamp[best_adding_v] = step;
	
	tabu_remove = best_adding_v;
	
	return;
}

void cover_LS(int fix_vertices_size)
{
	int best_removing_v, best_adding_v;
	int e, v1, v2;
	int num_v_ruin_and_reconstruct;
	int num_v_not_in_cover;
	
	step = 1;
	
	while(true)
	{
		if(uncov_stack_fill_pointer == 0)
		{
			update_best_sol();
			
			cout << "c vertex_cover: " << best_c_size + fix_vertices_size << " run_time: " << best_run_time << " best_step: " << best_step << endl;
			
			if(best_c_size + fix_vertices_size == target_optimal_size)
				return;
			
			update_target_size();
			
			continue;
		}
		
		if(decision_perform_ruin_and_reconstruct)
		{
			if(rng.nextClosed() < para_prob_ruin_and_reconstruct)
			{
				num_v_not_in_cover = v_num - remove_cand_size;
				
				num_v_ruin_and_reconstruct = para_num_vertex_ruin_and_reconstruct;
				if(num_v_ruin_and_reconstruct > remove_cand_size)
					num_v_ruin_and_reconstruct = remove_cand_size;
				if(num_v_ruin_and_reconstruct > num_v_not_in_cover)
					num_v_ruin_and_reconstruct = num_v_not_in_cover;
				
				ruin_and_reconstruct(num_v_ruin_and_reconstruct, step);
				continue;
			}
		}
		
		if(decision_perform_removing_random_walk)
		{
			if(rng.nextClosed() < para_removing_prob_random_walk)
			{
				best_removing_v = select_removing_vertex_random_walk();
			}
			else
			{
				best_removing_v = select_removing_vertex_ptr();
			}
		}
		else
		{
			best_removing_v = select_removing_vertex_ptr();
		}
		
		remove(best_removing_v);
		
		e = select_uncov_edge_heuristic_ptr();
		
		if(decision_perform_adding_random_walk)
		{
			if(rng.nextClosed() < para_adding_prob_random_walk)
			{
				best_adding_v = select_adding_vertex_random_walk(e);
			}
			else
			{
				best_adding_v = select_adding_vertex_ptr(e);
			}
		}
		else
		{
			best_adding_v = select_adding_vertex_ptr(e);
		}
		
		add(best_adding_v);
		
		exchange_and_update(best_removing_v, best_adding_v, step);
		
		if(decision_perform_edge_weight_scheme)
		{
			edge_weight_scheme_ptr();
		}
		
		if(decision_perform_vertex_weight_scheme)
		{
			vertex_weight_scheme_ptr();
		}
		
		step++;
	}
	
	return;
}

#endif

