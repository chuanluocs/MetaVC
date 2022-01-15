#ifndef _PREPROCESS_H_NC8VRLR1
#define _PREPROCESS_H_NC8VRLR1

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <iterator>

class Preprocess {
public:
	Preprocess (std::string origin_graph_filename);
	void simplify();
	void dominate_simplify_v();
	void foutput(std::string simplified_graph_filename);
	const std::vector<std::vector<long>> & get_adjacency_matrix() { return adjacency_matrix; }
	long get_fix_vertices_size() { return fix_vertice.size(); };
	void shrink_memory() { adjacency_matrix.clear(); adjacency_matrix.shrink_to_fit(); }

	template<typename ITERATOR> void out_solution(ITERATOR begin, ITERATOR end);
	template<typename ITERATOR> bool verify(ITERATOR begin, ITERATOR end);

#ifndef NDEBUG
	void print();
#endif
	
private:
	void initialize(std::string origin_graph_file);
	void fix(long v, std::vector<long> &pending_vertice);
	void rm_acnodes();
	bool is_adjacent(long v1, long v2);

	std::string origin_graph_filename;
	std::vector<std::vector<long>> adjacency_matrix;
	std::vector<long> fix_vertice;
	std::map<long, long> vertice_map;
};

template<typename ITERATOR>
void Preprocess::out_solution(ITERATOR begin, ITERATOR end) {
	for (ITERATOR iter = begin; iter != end; ++iter) {
		auto map_iter = vertice_map.find(*iter);
		if (map_iter != vertice_map.end()) {
			std::cout << map_iter->second << ' ';
		}
		else {
			std::cout << *iter << ' ';
		}
	}
	for (auto v : fix_vertice) {
		std::cout << v << ' ';
	}
	std::cout << std::endl;
}

template<typename ITERATOR>
bool Preprocess::verify(ITERATOR begin, ITERATOR end) {
	std::ifstream origin_graph_file(origin_graph_filename);
	if (!origin_graph_file.is_open()) {
		std::cout << "cant open file when verfing" << std::endl;
		exit(1);
	}
	std::string line;
	getline(origin_graph_file, line);
	size_t vertex_count;
	std::string tmp;
	std::istringstream is(line);
	is >> tmp >> tmp >> vertex_count;
	int *solution_bit_array = new int[vertex_count + 1];
	for (size_t i = 1; i <= vertex_count; ++i) {
		solution_bit_array[i] = 0;
	}
	for (ITERATOR iter = begin; iter != end; ++iter) {
		auto map_iter = vertice_map.find(*iter);
		if (map_iter != vertice_map.end()) {
			solution_bit_array[map_iter->second] = 1;
		}
		else {
			solution_bit_array[*iter] = 1;
		}
	}
	for (auto v : fix_vertice) {
		solution_bit_array[v] = 1;
	}
	while (getline(origin_graph_file, line)) {
		long v1, v2;
		char e;
		is.clear();
		is.str(line);
		is >> e >> v1 >> v2;
		if (solution_bit_array[v1] != 1 && solution_bit_array[v2] != 1) {
			return false;
		}
	}
	delete []solution_bit_array;
	origin_graph_file.close();
	return true;
}


#endif

