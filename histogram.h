#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<double> input_numbers(size_t count);

void show_bin(vector<size_t> bins, const double max_bin, const double ratio);

size_t find_max(vector<size_t> bins);

void find_minmax( const vector<double> numbers, double& min, double& max);

double find_ratio(size_t max_bin, const size_t bin_heght, const size_t Height, const size_t Red_line);

size_t Picture_ratio(size_t max_bin, const size_t bin_heght, const size_t Height, const size_t Red_line);

size_t Width_calculate(const size_t Need);

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count, double min, double max);
