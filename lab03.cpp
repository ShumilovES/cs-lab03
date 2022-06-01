#include <iostream>
#include <vector>

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

void show_histogram_text(vector <size_t>& bins, size_t& max_bin, const size_t& MAX_ASTERISK)
{
    for (size_t bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }

    for (size_t bin : bins)
    {
        size_t height = bin;
        if (max_bin > MAX_ASTERISK)   //Если масштабировать необходимо
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
        }

        if (bin < 100)
        {
            cout << " ";
        }
        if (bin < 10)
        {
            cout << "  ";
        }
        cout << bin << "|";
        for (size_t i = 0; i < height; i++)
        {
            cout << "*";
        }
        cout << endl;
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

    show_histogram_text(bins, max_bin, MAX_ASTERISK);
 
    return 0;
}
