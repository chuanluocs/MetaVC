#ifndef _PREPROCESS_CC
#define _PREPROCESS_CC

#include "preprocess.h"

using namespace std;
Preprocess::Preprocess(string origin_graph_filename) : origin_graph_filename(origin_graph_filename) {
	initialize(origin_graph_filename);
#ifndef NDEBUG
	print();
#endif
}

void Preprocess::initialize(string origin_graph_filename) {
	ifstream in_file(origin_graph_filename);
	if (! in_file.is_open()) {
		cout << "in_file error" << endl;
		exit(1);
	}

	size_t vertex_count, edge_count;
	
	string line;
	istringstream is;
	string p, tmp;
	do {
		getline(in_file, line);
		is.clear();
		is.str(line);
		is >> p >> tmp >> vertex_count >> edge_count;
	} while (p != "p");
	cout << "c origin graph: " << line << endl;

	adjacency_matrix.resize(vertex_count + 1);

	long v1, v2;

	for (size_t i = 0; i < edge_count; ++i) {
		in_file >> tmp >> v1 >> v2;
		adjacency_matrix[v1].push_back(v2);
		adjacency_matrix[v2].push_back(v1);
	}
	in_file.close();
}

void Preprocess::simplify() {
	std::vector<long> pending_vertice;
	for (vector<vector<long>>::size_type v = 1; v < adjacency_matrix.size(); ++v) {
		if (adjacency_matrix[v].size() == 1 || adjacency_matrix[v].size() == 2) {
			pending_vertice.push_back(v);
		}
	}
	while (pending_vertice.size() != 0) {
		long processing_vertice = pending_vertice[pending_vertice.size() - 1];
		pending_vertice.pop_back();

		long degree = adjacency_matrix[processing_vertice].size();
		if (degree == 1) {
			long u = adjacency_matrix[processing_vertice][0];
			fix_vertice.push_back(u);
			fix(u, pending_vertice);
		}
		else if (degree == 2) {
			long u1 = adjacency_matrix[processing_vertice][0], u2 = adjacency_matrix[processing_vertice][1];
			if (is_adjacent(u1, u2)) {
				fix_vertice.push_back(u1); fix_vertice.push_back(u2);
				fix(u1, pending_vertice); fix(u2, pending_vertice);
			}
		}

	}
}

void Preprocess::fix(long v, vector<long> &pending_vertice) {
	for (auto neighbor : adjacency_matrix[v]) {
		vector<long>::size_type i = 0;
		for (; i < adjacency_matrix[neighbor].size(); ++i) {
			if (adjacency_matrix[neighbor][i] == v) {
				break;
			}
		}
		adjacency_matrix[neighbor][i] = *adjacency_matrix[neighbor].rbegin();
		adjacency_matrix[neighbor].pop_back();

		long degree = adjacency_matrix[neighbor].size();
		if (degree == 1 ||degree == 2) {
			pending_vertice.push_back(neighbor);
		}
	}
	adjacency_matrix[v].clear();
}

void Preprocess::dominate_simplify_v() {
	simplify();
	std::vector<long> working_vertice(adjacency_matrix.size());
	std::vector<bool> addable(adjacency_matrix.size(), false);
	for (std::vector<long>::size_type i = 1; i < working_vertice.size(); ++i) {
		working_vertice[i] = i;
	}
	std::vector<long> next_working_vertice;
	next_working_vertice.reserve(adjacency_matrix.size());

	std::vector<bool> neighbor_indicator (adjacency_matrix.size(), false);
	while (!working_vertice.empty()) {
		while (!working_vertice.empty()) {
			long v = *working_vertice.rbegin();
			working_vertice.pop_back();
			neighbor_indicator[v] = true;
			for (auto u : adjacency_matrix[v]) {
				neighbor_indicator[u] = true;
			}

			bool is_dominated = false;
			for (auto u : adjacency_matrix[v]) {
				if (adjacency_matrix[v].size() < adjacency_matrix[u].size()) continue;
				is_dominated = true;
				for (auto w : adjacency_matrix[u]) {
					if (!neighbor_indicator[w]) {
						is_dominated = false;
						break;
					}
				}
				if (is_dominated) {
					break;
				}
			}
			
			neighbor_indicator[v] = false;
			for (auto u : adjacency_matrix[v]) {
				neighbor_indicator[u] = false;
			}

			if (is_dominated) {
				fix_vertice.push_back(v);
				for (auto u : adjacency_matrix[v]) {
					vector<long>::size_type i = 0;
					for (; i < adjacency_matrix[u].size(); ++i) {
						if (adjacency_matrix[u][i] == v) {
							break;
						}
					}
					swap(adjacency_matrix[u][i], *(adjacency_matrix[u].end() - 1));
					adjacency_matrix[u].pop_back();
					for (auto w : adjacency_matrix[u]) {
						if (addable[w]) {
							next_working_vertice.push_back(w);
							addable[w] = false;
						}
					}
				}
				adjacency_matrix[v].clear();
			}
			addable[v] = true;
		}
		working_vertice.swap(next_working_vertice);
		for (auto v : working_vertice) {
			addable[v] = false;
		}
	}
	rm_acnodes();
#ifndef NDEBUG
	print();
#endif
	size_t edge_count = 0;
	for (vector<vector<long>>::size_type v = 1; v < adjacency_matrix.size(); ++v) {
		edge_count += adjacency_matrix[v].size();
	}
	edge_count /= 2;
	cout << "c simplified graph: p edge " << adjacency_matrix.size() - 1 << ' ' << edge_count << endl;
}

void Preprocess::rm_acnodes() {
	for (vector<vector<long>>::size_type v = 1; v < adjacency_matrix.size();) {
		if (adjacency_matrix[v].empty()) {
			adjacency_matrix[v].swap(adjacency_matrix[adjacency_matrix.size() - 1]);
			vertice_map[v] = adjacency_matrix.size() - 1;
			adjacency_matrix.pop_back();
		}
		else {
			if (vertice_map.find(v) != vertice_map.end()) {
				long origin_vertex = vertice_map[v];
				for (auto neighbor : adjacency_matrix[v]) {
					vector<long>::size_type i = 0;
					for (; i < adjacency_matrix[neighbor].size(); ++i) {
						if (adjacency_matrix[neighbor][i] == origin_vertex) {
							break;
						}
					}
					adjacency_matrix[neighbor][i] = v;
				}
			}
			++v;
		}
	}
	if (vertice_map.find(adjacency_matrix.size()) != vertice_map.end()) { 
		vertice_map.erase(adjacency_matrix.size());
	}
}

bool Preprocess::is_adjacent(long v1, long v2) {
	if (adjacency_matrix[v1].size() > adjacency_matrix[v2].size()) {
		swap(v1, v2);
	}
	for (auto neighbor : adjacency_matrix[v1]) {
		if (v2 == neighbor) {
			return true;
		}
	}
	return false;
}

void Preprocess::foutput(string simplified_graph_filename) {
	cout << "c fix_vertice size = " << fix_vertice.size() << endl;
	if (adjacency_matrix.size() > 1) {
		ofstream out_file(simplified_graph_filename);
		if (!out_file.is_open()) {
			cout << "cant open output files" << endl;
			exit(1);
		}
		size_t edge_count = 0;
		for (vector<vector<long>>::size_type v = 1; v < adjacency_matrix.size(); ++v) {
			edge_count += adjacency_matrix[v].size();
		}
		edge_count /= 2;
		out_file << "p edge " << adjacency_matrix.size() - 1 << ' ' << edge_count << endl;

		for (vector<vector<long>>::size_type v = 1; v < adjacency_matrix.size(); ++v) {
			for (auto neighbor : adjacency_matrix[v]) {
				if (v < (vector<vector<long>>::size_type)neighbor) {
					out_file << "e " << v << ' ' << neighbor << endl;
				}
			}
		}
		out_file.close();
	}
	else {
		cout << "c the simplified_graph is empty" << endl;
	}
}

#ifndef NDEBUG
void Preprocess::print() {
	if (adjacency_matrix.size() == 1) {
		cout << "empty graph" << endl;
	}
	else {
		cout << "adjacency_matrix: " << endl;
	}
	for (vector<vector<long>>::size_type v = 1; v < adjacency_matrix.size(); ++v) {
		cout << v << ": ";
		for (auto neighbor : adjacency_matrix[v]) {
			cout << neighbor << ' ';
		}
		cout << endl;
	}

	if (vertice_map.empty()) {
		cout << "empty mapping" << endl;
	}
	else {
		cout << "vertice_map: ";
	}
	for (auto v_v : vertice_map) {
		cout << v_v.second << "->" << v_v.first << '\t';
	}
	cout << endl;
	
	if (fix_vertice.empty()) {
		cout << "empty fix fix_vertice" << endl;
	}
	else {
		cout << "fix_vertice: ";
	}
	for (auto v : fix_vertice) {
		cout << v << ' ';
	}
	cout << endl;
}
#endif

#endif
