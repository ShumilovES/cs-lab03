#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"

using namespace std;


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



vector<double> input_numbers(size_t count) {
	vector<double> result(count);
	for (size_t i = 0; i < count; i++) {
		cin >> result[i];
	}
	return result;
}

double find_ratio(size_t max_bin, const size_t bin_heght, const size_t Height, const size_t Red_line) {
	double ratio = 1;
	if (max_bin * bin_heght > Height - 2 * Red_line)
	{
		ratio = double(Height - 2 * Red_line) / ((double(bin_heght) * double(max_bin)));
	}
	return ratio;
}

size_t Picture_ratio(size_t max_bin, const size_t bin_heght, const size_t Height, const size_t Red_line) {

	if (max_bin * bin_heght < Height - 2 * Red_line) {

		return Height;
	}
	else {
		return max_bin * bin_heght + 2 * Red_line;
	}
}


vector <size_t> make_histogramm(vector<double> numbers, size_t bin_count) {

	double min;
	double max;
	find_minmax(numbers, min, max);


	double bin_size = (max - min) / bin_count;

	vector<size_t> bins(bin_count, 0);

	for (size_t i = 0; i < numbers.size(); i++)
	{
		bool found = false;
		for (size_t j = 0; j < (bin_count - 1) && !found; j++)
		{
			auto lo = (min + j * bin_size);
			auto hi = (min + (j + 1) * bin_size);
			if ((lo <= numbers[i]) && numbers[i] < hi)
			{
				bins[j]++;
				found = true;
			}
		}
		if (!found)
		{
			bins[bin_count - 1]++;
		}

	}
	return  bins;

}

void make_histogram(size_t& bin_count, size_t& number_count, const vector<double>& numbers, double& min, double& max, vector <size_t>& bins)
{


    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1) && !found; j++)
        {
            double low = min + j * bin_size;
            double high = min + (j + 1) * bin_size;
            if ((low <= numbers[i]) && (numbers[i] < high))
            {
                bins[j]++;
                found = true;
            }

        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }
}

void svg_begin(double width = 400, double height = 300) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) {

    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill) {

    cout << "<rect x='" << x << "' y='" << y << "' " "width='" << width << "' " "height='" << height
        << "' " "stroke='" << stroke << "' " "fill='" << fill << "' />";
}

void make_histogramm_on_svg(double ratio, const vector<size_t>& bins) {
}

void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 30;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double ratio = find_ratio(find_max(bins), BIN_HEIGHT, IMAGE_HEIGHT, TEXT_BASELINE);

    for (size_t i = 0; i < bins.size(); i++) {

        svg_text(TEXT_LEFT + BLOCK_WIDTH * i, TEXT_BASELINE, to_string(bins[i]));
        svg_rect(TEXT_LEFT - 1 + BLOCK_WIDTH * i, TEXT_BASELINE + 2, BLOCK_WIDTH, BIN_HEIGHT * bins[i] * ratio, "black", "grey");
    }


    svg_end();
}


int main()
{
	//Ввод данных
	const size_t maximum_asterisks_in_bin = 80;

	size_t number_count;
	cerr << "enter number_count: ";
	cin >> number_count;

	cerr << "Enter numbers:\n";

	vector<double> numbers = input_numbers(number_count);

	size_t bin_count;

	cerr << "Enter bin_count: \n";
	cin >> bin_count;

	// Расчеты

	double min;
	double max;
	find_minmax(numbers, min, max);

	double bin_size = (max - min) / bin_count;

	auto bins = make_histogramm(numbers, bin_count);
	//Вывод данных

	show_histogram_svg(bins);

	return 1;
}

