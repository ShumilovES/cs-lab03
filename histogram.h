#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>
#define CURL_STATICLIB


using namespace std;

struct Input {
	vector<double> numbers;
	size_t bin_count = 0;
};

void ver(int argc, char** argv, CURL* curl);

Input download(const string& address, int argc, char** argv);

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx);

Input read_input(istream& in, bool prompt);

vector<double> input_numbers(istream& in, size_t count);

void show_bin(vector<size_t> bins, const double max_bin, const double ratio);

size_t find_max(vector<size_t> bins);

void find_minmax(const vector<double> numbers, double& min, double& max);

double find_ratio(size_t max_bin, const size_t bin_heght, const size_t Height, const size_t Red_line);

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count, double min, double max);

