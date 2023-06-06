#include "func_kp4.h"

double F5(double x){
    return (sqrt(1-x) - tan(x));
}

double f5(double x){
    return 1 - tan(x) * sqrt(1-x);
}

double F6(double x){
    return (x + cos(pow(x, 0.52) + 2));
}

double f6(double x){
    return -cos(pow(x, 0.52) + 2);
}


double df( double (*f)(double), double x){
    double dx = pow(2, -21);
    return (f(x + dx) - f(x - dx))/(2 * dx);
}

double ddf( double (*f)(double), double x){
    double dx = pow(2, -12);
    return (f(x + dx) - 2 * f(x) + f(x - dx)) / (dx * dx); 
}


result diho(double (*f)(double), double a, double b, double delta){
    result res;
    res.steps = 0;
    res.success = true;
    if(f(a)*f(b)>0){
        res.success = false;
        return res;
    }
    while(b - a > delta){
        double c = (a+b)/2;
        if (f(a) * f(c) < 0) {b = c;} 
        else {a = c;}
        res.steps++;
    }
    res.root = (a + b)/2;
    return res;
}

result itera(double (*f)(double), double a, double b, double delta){
    result res;
    res.steps = 0;
    res.success = true;
    double x0 = (a+b)/2, x1 = x0;
    do {
        if (fabs(df(f, x0)) >= 1){
            res.success = false;
            return res;
        }
        x0 = x1;
        x1 = f(x0);
        res.steps++;
    } while (fabs(x1 - x0) > delta );
    res.root = x1;
    return res;
}

result Newton(double (*f)(double), double a, double b, double delta){
    result res;
    res.steps = 0;
    res.success = true;
    double x0 = (a+b)/2, x1 = x0;
    do{
        if (fabs(f(x0) * ddf(f, x0)) >= pow(df(f, x0), 2)){
            res.success = 0;
            return res;
        }
        x0 = x1;
        x1 = x0 - f(x0)/df(f, x0);
        res.steps++;
    } while (fabs(x1 - x0) > delta);
    res.root = x1;
    return res;
}

void print_result(int variant, double (*F)(double), double (*f)(double), double a, double b, double delta){
    printf("For %d variant:\n", variant);

    result dih = diho(F, a, b, delta);
    if (dih.success){
        printf("Dihotomia:  root = %.4lf, steps = %d\n", dih.root, dih.steps);
    } else { printf("The Dihotomia method isn't applicable\n");}
    

    result iter = itera(f, a, b, delta);
    if (iter.success){
        printf("Iteration:  root = %.4lf, steps = %d\n", iter.root, iter.steps);
    } else { printf("The iteration method isn't applicable\n");}
    

    result newtn = Newton(F, a, b, delta);
    if (newtn.success){
        printf("Newton:  root = %.4lf, steps = %d\n\n", newtn.root, newtn.steps);
    } else { printf("Newton's method isn't applicable\n\n");}
}