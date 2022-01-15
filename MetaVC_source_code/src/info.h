#ifndef _INFO_H
#define _INFO_H

#include "basis.h"

extern string version_str;

string get_last_level_name(string file_path);
void print_general_information(char *executable_name);
void print_usage_info(char *executable_name);
void print_algorithm_settings_information();
void print_solution_mis();
void print_solution_vc();

#endif
