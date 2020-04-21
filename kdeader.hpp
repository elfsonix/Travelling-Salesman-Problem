#ifndef KHEADER_HPP_
#define KHEADER_HPP_

#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory> //smart pointers
#include <algorithm> //std::min_element, std::max_element
#include <limits>   //infinity


using ivec = std::vector<int>;
using matvec = std::vector<std::vector<double>>;
ivec tsp(std::vector<std::vector<double>> cost_matrix);
double find_min_value(std::vector<std::vector<double>> cost_matrix, int i, int j);
ivec write_path(std::map<int,ivec> pairs, int start);
double infinity = std::numeric_limits<double>::infinity();

#endif // KHEADER_HPP_
