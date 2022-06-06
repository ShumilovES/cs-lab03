#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#define CURL_STATICLIB
#include <cstdio>


using namespace std;


int main(int argc, char* argv[])
{
	const char* name = "Commander Shepard";
	int year = 2154;
	printf("%s was born in %d.\n", name, year); // Commander Shepard was born in 2154.
	printf("n = %08x\n", 0x1234567); // 01234567
	return 0;

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

	//char* curl_version();

	cerr << "CURL: " << curl_version_info(CURLVERSION_NOW)->version << "\n" << "SSL: " << curl_version_info(CURLVERSION_NOW)->ssl_version;

	return 1;

}

