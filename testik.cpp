#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"

using namespace std;



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
int main()
{
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

