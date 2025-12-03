// Copyright 2025 Viktoria Buzlaeva

#include "../lib_functions/functions.h"

#define EPSILON 0.000001

double Functions::my_abs(double x) {
    return x < 0 ? -x : x;
}

double Functions::sin(double x) {
    double  res = x;
    double term = x;
    int n = 0;

    while (my_abs(term) > EPSILON) {
        n++;
        term = -term * x * x / ((2 * n + 1) * (2 * n));
        res += term;
    }

    return res;
}

double Functions::cos(double x) {
    double  res = 1.0;
    double term = 1.0;
    int n = 0;

    while (my_abs(term) > EPSILON) {
        n++;
        term = -term * x * x / ((2 * n) * (2 * n - 1));
        res += term;
    }

    return res;
}

double Functions::tg(double x) {
    double cos_val = cos(x);

    if (std::abs(cos_val) < EPSILON) {
        throw std::logic_error("Тангенс не определен");
    }

    return sin(x) / cos_val;
}
