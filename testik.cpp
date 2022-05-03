#include <iostream>
#include <vector>
#include <string>
using namespace std;


vector<double> input_numbers(size_t count)
{
    vector <double> result(count);
    cerr << "Vvedite chisla: ";
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max, size_t& number_count)
{
    min = numbers[0];
    max = numbers[0];
    for (size_t i = 0; i < number_count; i++)
    {
        if (min > numbers[i])
            min = numbers[i];
        if (max < numbers[i])
            max = numbers[i];
    }
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

void svg_begin(double width, double height) {
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
void svg_rect(double x, double y, double width, double height, string stroke = "#990000", string fill = "#66FFFF") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}
void show_histogram_svg(const vector<size_t>& bins) {
    {
        const auto IMAGE_WIDTH = 400;
        const auto IMAGE_HEIGHT = 300;
        const auto TEXT_LEFT = 20;
        const auto TEXT_BASELINE = 20;
        const auto TEXT_WIDTH = 50;
        const auto BIN_HEIGHT = 30;
        const auto BLOCK_WIDTH = 10;
        svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
        double top = 0;
        for (size_t bin : bins) {
            const double bin_width = BLOCK_WIDTH * bin;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            top += BIN_HEIGHT;
        }
        svg_end();
    }
} 


int main()
{
    // Ввод данных
    size_t number_count;
    cerr << "Vvedite kolvo chisel: ";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Vvedite kolvo intervalov: ";
    cin >> bin_count;

    double min, max;

    find_minmax(numbers, min, max, number_count);

    // Расчет гистограммы

    vector <size_t> bins(bin_count, 0);

    make_histogram(bin_count, number_count, numbers, min, max, bins);

    // Вывод данных
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_bin = bins[0];

    show_histogram_svg(bins);

    return 0;
}

