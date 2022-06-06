#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"


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

void svg_rect(double x, double y, double width, double height, string stroke, string fill) {

    cout << "<rect x='" << x << "' y='" << y << "' " "width='" << width << "' " "height='" << height
        << "' " "stroke='" << stroke << "' " "fill='" << fill << "' />";
}


void make_histogramm_on_svg(double ratio, const vector<size_t>&bins) {
    }

void show_histogram_svg(const vector<size_t>&bins) {
        const auto IMAGE_WIDTH = 400;
        const auto IMAGE_HEIGHT = 500;
        const auto TEXT_LEFT = 20;
        const auto TEXT_BASELINE = 20;
        const auto TEXT_WIDTH = 50;
        const auto BIN_HEIGHT = 30;
        const auto BLOCK_WIDTH = 30;
        svg_begin(IMAGE_WIDTH + 100, IMAGE_HEIGHT + 30);
        double ratio = find_ratio(find_max(bins), BIN_HEIGHT, IMAGE_HEIGHT, TEXT_BASELINE);

        for (size_t i = 0; i < bins.size(); i++) {

            svg_text(TEXT_LEFT + BLOCK_WIDTH * i, TEXT_BASELINE, to_string(bins[i]));
            svg_text(TEXT_LEFT, IMAGE_HEIGHT - TEXT_BASELINE + 30, make_info_text());
            svg_rect(TEXT_LEFT - 1 + BLOCK_WIDTH * i, TEXT_BASELINE + 2, BLOCK_WIDTH, BIN_HEIGHT * bins[i] * ratio, "black", "grey");
        }


        svg_end();
    }

string make_info_text() {
    DWORD WINAPI GetVersion(void);
    stringstream buffer;
    const auto R = GetVersion();

    printf("n = %lu\n", R);
    printf("n = %lx\n", R);

    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = R & mask;

    printf("ver = %lu\n", version);
    DWORD platform = R >> 16;
    printf("ver2 = %lu\n", platform);
    DWORD mask2 = 0b00000000'11111111;
    DWORD version_major = version & mask2;
    printf("version_major = %lu\n", version_major);
    DWORD version_minor = version>> 8;
    printf("version_minor = %lu\n", version_minor);
    DWORD build = 0;
    if ((R & 0x80000000) == 0)
    {
        build = platform;
        printf("build = %lu\n", build);

    }
    buffer << "Windows" << " " << "v" << " " << version_major << "." << version_minor << " " << "(build" << " " << build << ")" << endl;
    char storage[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD bufCharCount = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(storage, &bufCharCount);
    buffer << "Computer name:" << " " << storage;
    return buffer.str();
}

