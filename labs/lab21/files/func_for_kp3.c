#include <math.h>
#include <stdio.h>

double get_mch_eps(){
    double eps1=1, eps;
    while(1.0+eps1!=1.0){
        eps=eps1;
        eps1/=2;
    }
    return eps;
}

double elmnt_tylr8(int n, double x){
    return -((pow(2, n-1) * pow(x, n-1))/pow(5, n));
}

double elmnt_tylr9(int n, double x){
    return -(1+2/(pow(3, n+1)))*pow(x, n);
}

void print_begin(int n){
    printf("----------------------------------%d-variant----------------------------------\n", n);
	printf("|   x   |     taylor value     |     formula value     |  difference  |  n  |\n");
	printf("|-------|----------------------|-----------------------|--------------|-----|\n");
}

void var8(double delta){
    double a=0.0, b=2.0, step, sum_tylr, forml_value, x, elmnt_tylr;
    int nmbr_of_step, n = 1;

    printf("Enter the number of partitions for variant 8: ");
    scanf("%d", &nmbr_of_step);
    step=(b-a)/(nmbr_of_step-1);
    x=a;

    print_begin(8);
    for(int i = 0; i < nmbr_of_step; i++) {
		sum_tylr = 0;
        forml_value = 1/(2*x - 5);
        elmnt_tylr = elmnt_tylr8(n, x);
		while(fabs(elmnt_tylr)>delta){
            sum_tylr += elmnt_tylr;
			n++;
            elmnt_tylr = elmnt_tylr8(n, x);
		}
		printf("| %.3f | %.17f | %.18f | %e | %.3d |\n", x, sum_tylr, forml_value, fabs(sum_tylr - forml_value), n);
        printf("|-------|----------------------|-----------------------|--------------|-----|\n");
		x += step;
    }
}

void var9(double delta){
    double a=0.0, b=0.5, step, sum_tylr, forml_value, x, elmnt_tylr;
    int nmbr_of_step, n = 0;

    printf("Enter the number of partitions for variant 9: ");
    scanf("%d", &nmbr_of_step);
    step = (b - a)/(nmbr_of_step - 1);
    x = a;

    print_begin(9);
    for(int i = 0; i < nmbr_of_step; i++) {
		sum_tylr = 0;
        forml_value = (3*x - 5)/(x*x - 4*x + 3);
        elmnt_tylr = elmnt_tylr9(n, x);
		while(fabs(elmnt_tylr)>delta){
            sum_tylr += elmnt_tylr;
			n++;
            elmnt_tylr = elmnt_tylr9(n, x);
		}
		printf("| %.3f | %.17f | %.18f | %e | %.3d |\n", x, sum_tylr, forml_value, fabs(sum_tylr - forml_value), n);
        printf("|-------|----------------------|-----------------------|--------------|-----|\n");
		x += step;
    }
}

