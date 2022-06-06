#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include <curl/curl.h>
#include <sstream>
#define CURL_STATICLIB



using namespace std;

void ver(int argc, char** argv, CURL* curl) {
	bool verbose = false;

	for (int i = 0; i < argc; i++)
	{
		if (argv[i] == "-verbose") {
			verbose = true;
			break;
		}
	}
	if (verbose) {
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	}
	bool oper = false;
	if (!verbose) {
		for (int i = 0; i < argc; i++)
		{
			if (bool(strstr(argv[i], "-"))) {
				oper = true;
			}
		}
		if (oper) {
			cerr << "I don't now what i need say to help, sorry.\n But uou shoud do it.\n JUST DO IT!!!";
		}
	}
};

Input read_input(istream& in, bool prompt) {
	Input data;

	if (prompt)
	{
		cerr << "Enter number count: ";
	}
	size_t number_count;
	in >> number_count;
	if (prompt)
	{
		cerr << "Enter numbers: ";
	}

	data.numbers = input_numbers(in, number_count);
	if (prompt)
	{
		cerr << "Enter bin_count: \n";
	}

	size_t bin_count;
	in >> data.bin_count;

	return data;
}

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) 
{
	size_t data_size = item_size * item_count;
	stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
	(*buffer).write(reinterpret_cast<const char*>(items), data_size);
	return data_size;
}

Input download(const string& address, int argc, char** argv)
{

	stringstream buffer;
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl = curl_easy_init();

	if (curl)
	{
		ver(argc, argv, curl);
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res)
		{
			cerr << curl_easy_strerror(res) << endl;
			exit(1);
		}
	}
	return read_input(buffer, false);
}

vector<double> input_numbers(istream& in,size_t count) {
	vector<double> result(count);
	for (size_t i = 0; i < count; i++) {
		cin >> result[i];
	}
	return result;
}

void show_bin(vector<size_t> bins, const double max_bin, const double ratio) {

	for (size_t i = 0; i < (max_bin * ratio); i++)
	{
		cout << "\t";
		for (size_t bin : bins)
		{
			if (i < (bin * ratio))
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}

		cout << endl;
	}
}

size_t find_max(vector<size_t> bins) {
	size_t max;
	if (bins.size() > 0) {
		max = bins[0];

		for (size_t bin : bins) {
			if (max < bin) {
				max = bin;
			}
		}
	}
	else {
		exit(0);
	}
	return max;
}

void find_minmax(const vector<double> numbers, double& min, double& max) {
	if (numbers.size() != 0)
	{
		min = numbers[0];
		max = numbers[0];
		for (double number : numbers)
		{
			if (min > number)
			{
				min = number;
			}
			if (max < number)
			{
				max = number;
			}
		}
	}
}

double find_ratio(size_t max_bin, const size_t bin_heght, const size_t Height, const size_t Red_line) {
	double ratio = 1;
	if (max_bin * bin_heght > Height - 2 * Red_line)
	{
		ratio = double(Height - 2 * Red_line) / ((double(bin_heght) * double(max_bin)));
	}
	return ratio;
}

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count, double min, double max) {
	vector<size_t>result(bin_count);

	double bin_size = (max - min) / bin_count;
	for (double number : numbers) {
		size_t bin = (size_t)((number - min) / (max - min) * bin_count);
		if (bin == bin_count) {
			bin--;
		}
		result[bin]++;
	}
	return result;
}

