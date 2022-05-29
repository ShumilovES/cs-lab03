#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"


void svg_begin(double width = 400, double height = 300);

void svg_end();

void svg_text(double left, double baseline, string text);

void svg_rect(double x, double y, double width, double height, string stroke, string fill);

void make_histogramm_on_svg(double ratio, const vector<size_t>& bins);

void show_histogram_svg(const vector<size_t>& bins);

