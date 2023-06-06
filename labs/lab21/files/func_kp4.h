#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    double root;
    int steps;
    bool success;
} result;

double F5(double x);
double f5(double x);

double F6(double x);
double f6(double x);

double df( double (*f)(double), double x);
double ddf( double (*f)(double), double x);

result diho(double (*f)(double), double a, double b, double delta);
result itera(double (*f)(double), double a, double b, double delta);
result Newton(double (*f)(double), double a, double b, double delta);

void print_result(int variant, double (*F)(double), double (*f)(double), double a, double b, double delta);

