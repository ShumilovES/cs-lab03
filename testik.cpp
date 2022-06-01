#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"

using namespace std;


int main()
{
	//Ввод данных
	const size_t maximum_asterisks_in_bin = 80;

	size_t number_count;
	cerr << "enter number_count: ";
	cin >> number_count;

	cerr << "Enter numbers:\n";

	vector<double> numbers = input_numbers(cin, number_count);

	size_t bin_count;

	cerr << "Enter bin_count: \n";
	cin >> bin_count;

	// Расчеты

	double min;
	double max;
	find_minmax(numbers, min, max);

	double bin_size = (max - min) / bin_count;
	const auto bins = make_histogram(numbers, bin_count, min, max);
	//Вывод данных

	show_histogram_svg(bins);

	return 1;
}

