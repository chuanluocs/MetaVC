#ifndef _MAIN_CPP
#define _MAIN_CPP

#include "basis.h"

long * solution_for_simplified_graph;
Preprocess * preprocess_ptr;

void handle_interrupt(int sig) 
{
    cout << "c" << endl;
    cout << "c caught signal... exiting" << endl;
    
    if(decision_perform_preprocess)
    {
        cout << "c vertex_cover: " << best_c_size + fix_vertices_size << " run_time: " << best_run_time << " best_step: " << best_step << endl;
        
        solution_for_simplified_graph = new long [best_c_size];
        int v, solution_for_simplified_graph_size = 0;
        for(v=1; v<=v_num; v++)
        {
            if(best_v_in_c[v])
            {
                solution_for_simplified_graph[solution_for_simplified_graph_size++] = v;
            }
        }
        
        if(preprocess_ptr->verify(solution_for_simplified_graph, solution_for_simplified_graph + best_c_size))
        {
            if(flag_print_sol)
            {
                cout << "c detailed_vertex_cover: ";
                preprocess_ptr->out_solution(solution_for_simplified_graph, solution_for_simplified_graph + best_c_size);
            }
        }
    }
    else
    {
        cout << "c vertex_cover: " << best_c_size << " run_time: " << best_run_time << " best_step: " << best_step << endl;
        
        if(check_solution())
        {
            if(flag_print_sol)
            {
                cout << "c detailed_vertex_cover: ";
                print_solution_vc();
            }
        }
    }
    
    cout << "c" <<endl;
    free_memory(v_num, e_num);
    exit(-1);
}

void setup_signal_handler() {
    signal(SIGTERM, handle_interrupt);
    signal(SIGINT, handle_interrupt);
    signal(SIGQUIT, handle_interrupt);
    //signal(SIGABRT, handle_interrupt);
    signal(SIGKILL, handle_interrupt);
}


int main_preprocess()
{
    double run_time, preprocess_time;
    
    Preprocess preprocess(inst.c_str());
    preprocess_ptr = &preprocess;
    preprocess.dominate_simplify_v();
    stop = clock();
    preprocess_time = compute_time(start, stop);
    cout << "c preprocess time = " << preprocess_time << endl;
    cout << "c fix vertice size = " << preprocess.get_fix_vertices_size() << endl;
    fix_vertices_size = preprocess.get_fix_vertices_size();
    
    if(!build_instance(preprocess.get_adjacency_matrix()))
    {
        stop = clock();
        run_time = compute_time(start, stop);
        if(preprocess.verify((long*)  0, (long*) 0))
        {
#ifndef NDEBUG
            cout << "c vc: ";
            preprocess.out_solution((long*) 0, (long*) 0);
#endif
            cout << "c initialised solution size = " << preprocess.get_fix_vertices_size() << endl;
            cout << "c initialised solution time = " << 0 << endl;
            
            cout << "c The solution has been verified!" << endl;
            cout << "c Best found vertex cover size = " << preprocess.get_fix_vertices_size() << endl;
            cout << "c Best search steps = " << 0 << endl;
            cout << "c Best run time = " << run_time << endl;
            cout << "c vertex_cover: " << preprocess.get_fix_vertices_size() << " run_time: " << run_time << " best_step: " << 0 << endl;
        }
        else
        {
            cout << "c The solution is wrong!" << endl;
        }
        
        return 0;
    }
    
    default_algorithm_settings_related_to_graph_information();
    
    print_algorithm_settings_information();
    
    rng.seed(seed);
    
    init_sol();
    
    stop = clock();
    double init_sol_time = compute_time(start, stop);
    cout << "c initialised solution size = " << best_c_size << endl;
    cout << "c initialised solution time = " << init_sol_time << endl;
    cout << "c vertex_cover: " << best_c_size + preprocess.get_fix_vertices_size() << " run_time: " << init_sol_time << " best_step: " << 0 << endl;
    
    if(best_c_size + preprocess.get_fix_vertices_size() > target_optimal_size)
    {
        cover_LS(preprocess.get_fix_vertices_size());
    }
    
    //long * solution_for_simplified_graph = new long [best_c_size];
    solution_for_simplified_graph = new long [best_c_size];
    int v, solution_for_simplified_graph_size = 0;
    for(v=1; v<=v_num; v++)
    {
        if(best_v_in_c[v])
        {
            solution_for_simplified_graph[solution_for_simplified_graph_size++] = v;
        }
    }
    
    if(preprocess.verify(solution_for_simplified_graph, solution_for_simplified_graph + best_c_size))
    {
#ifndef NDEBUG
        cout << "c vc: ";
        preprocess.out_solution(solution_for_simplified_graph, solution_for_simplified_graph + best_c_size);
#endif
        cout << "c The solution has been verified!" << endl;
        cout << "c Best found vertex cover size = " << best_c_size + preprocess.get_fix_vertices_size() << endl;
        cout << "c Best search steps = " << best_step << endl;
        cout << "c Best run time = " << best_run_time << endl;
        
        cout << "c vertex_cover: " << best_c_size + preprocess.get_fix_vertices_size() << " run_time: " << best_run_time << " best_step: " << best_step << endl;
        
        if(flag_print_sol)
        {
            cout << "c detailed_vertex_cover: ";
            preprocess.out_solution(solution_for_simplified_graph, solution_for_simplified_graph + best_c_size);
        }
    }
    else
    {
        cout << "c The solution is wrong!" << endl;
    }
    
    delete [] solution_for_simplified_graph;
    
    return 0;
}

int main_non_preprocess()
{
    if(!build_instance(inst))
    {
        cout << "c" << endl;
        cout << "c Instance File Error!" << endl;
        cout << "c" << endl;
        return -1;
    }
    
    default_algorithm_settings_related_to_graph_information();
    
    print_algorithm_settings_information();
    
    rng.seed(seed);
    
    init_sol();
    
    stop = clock();
    double init_sol_time = compute_time(start, stop);
    cout << "c initialised solution size = " << best_c_size << endl;
    cout << "c initialised solution time = " << init_sol_time << endl;
    cout << "c vertex_cover: " << best_c_size << " run_time: " << init_sol_time << " best_step: " << 0 << endl;
    
    if(best_c_size > target_optimal_size)
    {
        cover_LS(0);
    }
    
    if(check_solution())
    {
        cout << "c The solution has been verified!" << endl;
        cout << "c Best found vertex cover size = " << best_c_size << endl;
        cout << "c Best search steps = " << best_step << endl;
        cout << "c Best run time = " << best_run_time << endl;
        
        cout << "c vertex_cover: " << best_c_size << " run_time: " << best_run_time << " best_step: " << best_step << endl;
        
        if(flag_print_sol)
        {
            cout << "c detailed_vertex_cover: ";
            print_solution_vc();
        }
    }
    else
    {
        cout << "c The solution is wrong!" << endl;
    }
    
    return 0;
}


int main(int argc, char **argv)
{
    start = clock();
    
    setup_signal_handler();
    
    print_general_information(argv[0]);
    
    if(!parse_arguments(argc, argv))
    {
        cout << "c" << endl;
        cout << "c Arguments Error!" << endl;
        cout << "c" << endl;
        print_usage_info(argv[0]);
        return -1;
    }
    
    //print_algorithm_settings_information();
    
    int ret;
    if(decision_perform_preprocess)
    {
        ret = main_preprocess();
    }
    else
    {
        ret = main_non_preprocess();
    }
    
    free_memory(v_num, e_num);
    return ret;
}

#endif
