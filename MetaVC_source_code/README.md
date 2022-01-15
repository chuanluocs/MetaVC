# MetaVC -- A Meta Local Search Framework For Minimum Vertex Cover (MinVC)

- MetaVC is a meta local search framework for minimum vertex cover. MetaVC provides a top level design, where each key function is an abstraction and can be instantiated with a concrete function.

## Reference
- Chuan Luo, Holger H. Hoos, Shaowei Cai, Qingwei Lin, Hongyu Zhang, Dongmei Zhang. Local Search with Efficient Automatic Configuration for Minimum Vertex Cover. In Proceedings of IJCAI 2019, pages 1297-1304, 2019.

## LICENSE
- This project is licensed under the terms of the GPLv3 license.

## Building Command
- `make`

## Usage Command

```
    ./MetaVC   (*Required*)
        -inst <instance_name>   (*Required*)
        -seed <seed>   (*Required*)
        -opt <target_optimal_size>   [Set it to 0 if you do not have any priori knowledge about the input instance]
        -print_sol {0, 1}   (Default: 0)   [Set it to 1 if you want to see the final solution (vertex cover)]
        -perform_preprocess {0, 1}   (Default: 1)
        -init_sol {1, 2}   (Default: 1)
        -perform_ruin_and_reconstruct {0, 1}   (Default: 0)
        -prob_ruin_and_reconstruct [0, 1]   (Default: 0.001)
        -num_vertex_ruin_and_reconstruct {int, from 1 to 100}   (Default: 10)
        -perform_removing_random_walk {0, 1}   (Default: 0)
        -removing_prob_random_walk [0, 1]   (Default: 0.05)
        -perform_bms {0, 1}   (Default: 0)
        -bms_k {int, from 20 to 1000}   (Default: 50)
        -sel_removing_v {1, 2, 3, 4, 5, 6, 7, 8, 9}   (Default: 1)
        -tabu_tenure {int, from 1 to 100}   (Default: 3)
        -removing_prob_novelty [0, 1]   (Default: 0.5)
        -prob_distri_c1 [2, 10]   (Default: 2.15)
        -prob_distri_c2 {int, from 1 to 10}   (Default: 4)
        -prob_distri_c3 {int, from 10000 to 1000000}   (Default: 75000)
        -perform_adding_random_walk {0, 1}   (Default: 0)
        -adding_prob_random_walk [0, 1]   (Default: 0.05)
        -perform_cc_adding {0, 1}   (Default: 1)
        -sel_adding_v {1, 2, 3, 4, 5, 6}   (Default: 1)
        -adding_prob_novelty [0, 1]   (Default: 0.5)
        -sel_uncov_e {1, 2}   (Default: 1)
        -perform_edge_weight_scheme {0, 1}   (Default: 1)
        -sel_edge_weight_scheme {1, 2, 3, 4}   (Default: 1)
        -edge_weight_threshold_scale [0, 1]   (Default: 0.5)
        -edge_weight_p_scale [0, 1]   (Default: 0.3)
        -edge_weight_q_scale [0, 1]   (Default: 0.7)
        -paws_smooth_probability [0, 1]   (Default: 0.8)
        -paws_periodical_step_length {int, from 50 to 10000}   (Default: 200)
        -perform_vertex_weight_scheme {0, 1}   (Default: 0)
        -sel_vertex_weight_scheme {1, 2}   (Default: 1)
        -twmvc_smooth_probability [0, 1]   (Default: 0.01)
        -twmvc_delta {int, from 1000 to 1000000}   (Default: 100000)
        -twmvc_beta [0, 1]   (Default: 0.8)
        -twmvc_periodical_step_length {int, from 50 to 10000}   (Default: 100)
```

## Usage Examples

- **MetaVC** for instance family of `brock` in the benchmark of `DIMACS-HARD`  and `DIMACS-EASY`
  * `./MetaVC -inst <instance_name> -seed <seed> -opt 0 -print_sol 1 -init_sol '2' -num_vertex_ruin_and_reconstruct '100' -paws_smooth_probability '7.289942911392515E-5' -perform_adding_random_walk '0' -perform_bms '0' -perform_cc_adding '0' -perform_edge_weight_scheme '1' -perform_preprocess '1' -perform_removing_random_walk '0' -perform_ruin_and_reconstruct '1' -prob_ruin_and_reconstruct '0.0028421872317207584' -sel_adding_v '1' -sel_edge_weight_scheme '3' -sel_removing_v '5' -sel_uncov_e '2'`

- **MetaVC** for benchmarks `DIMACS-HARD` and `DIMACS-EASY` (Not including instance family of `brock`)
  * `./MetaVC -inst <instance_name> -seed <seed> -opt 0 -print_sol 1 -edge_weight_p_scale '0.9529615386652125' -edge_weight_threshold_scale '0.35095575247195787' -init_sol '1' -perform_adding_random_walk '0' -perform_bms '0' -perform_cc_adding '1' -perform_edge_weight_scheme '1' -perform_preprocess '0' -perform_removing_random_walk '1' -perform_ruin_and_reconstruct '0' -removing_prob_random_walk '1.3933877085709907E-4' -sel_adding_v '1' -sel_edge_weight_scheme '1' -sel_removing_v '1' -sel_uncov_e '2'`

- **MetaVC** for benchmarks `BHOSLIB-HARD` and `BHOSLIB-EASY`
  * `./MetaVC -inst <instance_name> -seed <seed> -opt 0 -print_sol 1 -edge_weight_p_scale '0.5214052710418935' -edge_weight_threshold_scale '0.414990365260387' -init_sol '1' -perform_adding_random_walk '0' -perform_bms '0' -perform_cc_adding '1' -perform_edge_weight_scheme '1' -perform_preprocess '1' -perform_removing_random_walk '0' -perform_ruin_and_reconstruct '0' -sel_adding_v '4' -sel_edge_weight_scheme '1' -sel_removing_v '2' -sel_uncov_e '1' -tabu_tenure '5'`

- **MetaVC** for benchmarks `REAL-WORLD-HARD` and `REAL-WORLD-EASY`
  * `./MetaVC -inst <instance_name> -seed <seed> -opt 0 -print_sol 1 -bms_k '633' -init_sol '2' -num_vertex_ruin_and_reconstruct '84' -perform_adding_random_walk '0' -perform_bms '1' -perform_cc_adding '1' -perform_edge_weight_scheme '0' -perform_preprocess '1' -perform_removing_random_walk '1' -perform_ruin_and_reconstruct '1' -perform_vertex_weight_scheme '0' -prob_ruin_and_reconstruct '3.908659583029911E-5' -removing_prob_random_walk '1.5908263953009627E-5' -sel_adding_v '2' -sel_removing_v '2' -sel_uncov_e '1'`

- **MetaVC2** for instance family of `brock` in the benchmark of `DIMACS-HARD`  and `DIMACS-EASY`
  * `./MetaVC -inst <instance_name> -seed <seed> -opt 0 -print_sol 1 -init_sol '2' -num_vertex_ruin_and_reconstruct '100' -paws_smooth_probability '7.049097866501246E-5' -perform_adding_random_walk '0' -perform_bms '0' -perform_cc_adding '1' -perform_edge_weight_scheme '1' -perform_preprocess '0' -perform_removing_random_walk '1' -perform_ruin_and_reconstruct '1' -prob_ruin_and_reconstruct '0.010648810472426678' -removing_prob_random_walk '3.529191710900074E-4' -sel_adding_v '1' -sel_edge_weight_scheme '3' -sel_removing_v '5' -sel_uncov_e '2'`
  
- **MetaVC2** for benchmarks `DIMACS-HARD` and `DIMACS-EASY` (Not including instance family of `brock`)
  * `./MetaVC -inst <instance_name> -seed <seed> -opt 0 -print_sol 1 -adding_prob_random_walk '0.013341402487321777' -edge_weight_p_scale '0.536404473144252' -edge_weight_threshold_scale '0.6927014274138609' -init_sol '1' -perform_adding_random_walk '1' -perform_bms '0' -perform_cc_adding '1' -perform_edge_weight_scheme '1' -perform_preprocess '1' -perform_removing_random_walk '1' -perform_ruin_and_reconstruct '0' -removing_prob_random_walk '3.491447171985374E-5' -sel_adding_v '1' -sel_edge_weight_scheme '1' -sel_removing_v '1' -sel_uncov_e '2'`
  
- **MetaVC2** for benchmarks `BHOSLIB-HARD` and `BHOSLIB-EASY`
  * `./MetaVC -inst <instance_name> -seed <seed> -opt 0 -print_sol 1 -edge_weight_p_scale '0.9742601406594379' -edge_weight_threshold_scale '0.5678018440397401' -init_sol '1' -perform_adding_random_walk '0' -perform_bms '0' -perform_cc_adding '1' -perform_edge_weight_scheme '1' -perform_preprocess '1' -perform_removing_random_walk '1' -perform_ruin_and_reconstruct '0' -removing_prob_random_walk '2.1401098354324204E-5' -sel_adding_v '1' -sel_edge_weight_scheme '1' -sel_removing_v '2' -sel_uncov_e '1'`

- **MetaVC2** for benchmarks `REAL-WORLD-HARD` and `REAL-WORLD-EASY`
  * `./MetaVC -inst <instance_name> -seed <seed> -opt 0 -print_sol 1 -bms_k '720' -init_sol '2' -num_vertex_ruin_and_reconstruct '76' -perform_adding_random_walk '0' -perform_bms '1' -perform_cc_adding '1' -perform_edge_weight_scheme '0' -perform_preprocess '1' -perform_removing_random_walk '1' -perform_ruin_and_reconstruct '1' -perform_vertex_weight_scheme '0' -prob_ruin_and_reconstruct '3.0886947578801404E-5' -removing_prob_random_walk '3.61981045129405E-4' -sel_adding_v '2' -sel_removing_v '1' -sel_uncov_e '1'`


