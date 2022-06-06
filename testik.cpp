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
	DWORD mask = 0b00000000'00000000'11111111'11111111;
	DWORD info = GetVersion();
	DWORD version = info & mask;
	printf("Windows (decimal) version is %u.\n", version);
	printf("Windows (16x) version is %x.\n", version);
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

	cerr << "CURL: " << curl_version_info(CURLVERSION_NOW)->version << "\n" << "SSL: " << curl_version_info(CURLVERSION_NOW)->ssl_version;

	return 1;

}

