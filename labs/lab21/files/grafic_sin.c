#include <stdio.h>
#include <math.h>


int main() {
    // График sin(x)
    
    long double x = 0.0;
    
    while (x < 100) {
        if (roundl(sinl(x) * 10) >= 0) {
            printf("          ");
            for (long double i = 0; i < roundl(sinl(x) * 10); i++) {
                printf(" ");
            }
        } else {
            for (long double i = -10; i < roundl(sinl(x) * 10); i++) {
                printf(" ");
            }
            
        }
        printf("@\n");
        x += 0.2;
        
    }
}