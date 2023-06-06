#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
	setlocale(0,"Russian");
	double k, S, t, x, a=0.1, b=0.6, h, eps=1;
	int n, p;
	scanf("%d", &p);

	while(1+eps>1) {
		eps/=2;
	}
	printf("Машинное эпсилон = %.19f\n\n",eps);

	printf("-----------------------------------------------------------------\n");
	printf("|  x   |          S            |((1+x*x)/2)*atan(x)-(x/2)|  n   |\n");
	printf("-----------------------------------------------------------------\n");

	h=(b-a)/(p-1);
	x = 0.1;
	for(int i = 0; i < p; i++) {
		n=1;
		S=0;
		t=-x;
		while( t>eps || -t>eps ) {
 			t = -t*x*x;
 			k = t/(4*n*n-1);
 			S += k;
 			n++;
		}
		printf("| %.2f | %.19f | %.19f   | %3d  |\n", x, S, ((1+x*x)/2)*atan(x) - (x/2), n);
		x += h;
}
	printf("-----------------------------------------------------------------\n");
	return 0;
}
