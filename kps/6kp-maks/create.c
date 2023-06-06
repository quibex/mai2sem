#include "manga.h"
#include <stdio.h>
#include <string.h>


int main() {
    FILE* input = fopen("manga", "r");
    FILE* output = fopen("manga_bin", "wb");
    Manga m;

    if (input == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }
    if (output == NULL) {
        printf("Error opening output file!\n");
        fclose(input);
        return 1;
    }
    
    while(fscanf(input, "%d %s %s %d %lf", &m.id, m.name, m.author, &m.year, &m.rating) != EOF) {
        fwrite(&m, sizeof(Manga), 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}