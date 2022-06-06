#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#define CURL_STATICLIB
#include <windows.h>
#pragma warning(disable : 4996)

using namespace std;


int main(int argc, char* argv[])
{
	Input input;
	if (argc > 1)
	{
		input = download(argv[1], argc, argv);
	}
	else
	{
		input = read_input(cin, true);
	}

	//Ввод данных

	// Расчеты

	double min;
	double max;
	find_minmax(input.numbers, min, max);


	const auto bins = make_histogram(input.numbers, input.bin_count, min, max);
	//Вывод данных

	show_histogram_svg(bins);

}



