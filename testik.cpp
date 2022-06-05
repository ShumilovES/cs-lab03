﻿#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>

using namespace std;


int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		cerr << "argc = " << argc << endl;
		for (size_t i = 0; i < argc; i++)
		{
			cerr << "argv[" << i << "] = " << argv[i] << '\n';
		}
		return 0;
	}

	curl_global_init(CURL_GLOBAL_ALL);

	//Ввод данных
	
	const auto input = read_input(cin, true);

	// Расчеты

	double min;
	double max;
	find_minmax(input.numbers, min, max);


	const auto bins = make_histogram(input.numbers, input.bin_count, min, max);
	//Вывод данных

	show_histogram_svg(bins);

	return 1;
}

