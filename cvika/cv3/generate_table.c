#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {

    FILE *file;
	if ((file = fopen("dataset.csv", "w")) == NULL)
	{
		printf("ERROR!");
		return 0;
	}

    float g;
    float vy;
    float ysur;
    float vy0;
    float ysur0;

    g = -9.80665; // m/s^2

    // defaults
    ysur0 = 100;
    vy0 = 10;

    // printf("\nZAC Y: ");
    // scanf("%d", &ysur0);
    // printf("\nZAC RYCHLOST Y: ");
    // scanf("%d", &vy0);

    fprintf(file, "time;height;velocity\n");

    for (float t=0; t < 10; t+=0.1) {

        vy = vy0 + g*t;
        ysur = ysur0 + 0.5 * vy * t;

        fprintf(file, "%.1f;%f;%f;\n", t, ysur, vy);
    }





    fclose(file);


    return 0;
}











// gcc generate_table.c -std=c99 -pedantic -Wall -Werror -Wextra -o main ;; ./main
