/*
KOMPILOVAT A PUSTAT PRIKAZOM:

rm main ; clear ; gcc pr1.c -lm -lglut -lGL -lGLEW -lGLU -o main ; ./main 50 15

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// working only if v0 = 0
int analytic(float g, float S, float C, float ro, float m, float dt, float z0, float v0, float K, float Vterm)
{
    FILE *f;
    f = fopen("analytic.dat", "w");
    fprintf(f, " <t>  <v>  <z>\n");
    float v, z;
    float t = 0;
    do {
        v = -Vterm*tanh(g*t/Vterm);
        z = z0 - (Vterm*Vterm/g)*log(cosh(g*t/Vterm));
        t += dt;

        fprintf(f, "%.2f %.2f %.2f\n", t, v, z);

    } while (z >= 0);
    return 0;
}

int numeric(float g, float S, float C, float ro, float m, float dt, float z0, float v0, float K, float Vterm)
{
    FILE *f;
    f = fopen("numeric.dat", "w");
    fprintf(f, " <t>  <v>  <z>\n");

    float t = 0;
    float z = z0;
    float v = v0;
    float func;
    float gunc;
    do {
        t += dt;
        func = -g-K*abs(z)*z;
        float gunc = v;

        v += func * dt;
        z += gunc * dt;

        fprintf(f, "%.2f %.2f %.2f\n", t, v, z);

    } while (z >= 0);
    return 0;
}


// working only if v0 = 0
int land_analytic(float g, float S, float C, float ro, float m, float dt, float z0, float v0, float K, float Vterm)
{
    float t, v;
    float e=2.718281828459045235360287471352;
    t = Vterm / g * acosh(pow(e,(z0*g/(Vterm*Vterm))));
    v = -Vterm*tanh(g*t/Vterm);
    printf("ANA time of landing: %f\n", t);
    printf("ANA speed of landing: %f\n", v);
    return 0;
}

int land_numeric(float g, float S, float C, float ro, float m, float dt, float z0, float v0, float K, float Vterm)
{
    float t = 0;
    float z = z0;
    float v = v0;
    float func;
    float gunc;

    // get one dt bellow zero
    do {
        t += dt;
        func = -g-K*abs(z)*z;
        gunc = v;

        v += func * dt;
        z += gunc * dt;

    } while (z >= 0);

    // go one dt up
    t -= dt;
    func = -g-K*abs(z)*z;
    gunc = v;
    v -= func * dt;
    z -= gunc * dt;

    // iterate with smaller dt
    dt /= 10000;
    do {
        t += dt;
        func = -g-K*abs(z)*z;
        gunc = v;

        v += func * dt;
        z += gunc * dt;

    } while (z >= 0);

    printf("NUM time of landing: %f\n", t);
    printf("NUM speed of landing: %f\n", v);

    return 0;
}

int main(int argc, char **argv)
{
    printf("~start~\n");
    // constants
    float g = 9.80665; // m/s^2
    float S = 0.03;    // m^2
    float C = 0.6;
    float ro = 1.3;  // kg/m^3
    float m = 10;    // kg
    float dt = 0.01; // s

    // input
    if (argc != 3)
    {
        printf("wrong input - use <z0> <v0>!\n");
        exit(0);
    }
    float z0 = atof(argv[1]);
    float v0 = atof(argv[2]);

    float K = 0.5 * C * S * ro / m;
    float Vterm = sqrt((2 * m * g) / (C * S * ro));

    printf("K: %f Vterm: %f\n", K, Vterm);

    analytic(g, S, C, ro, m, dt, z0, v0, K, Vterm);
    numeric(g, S, C, ro, m, dt, z0, v0, K, Vterm);

    land_analytic(g, S, C, ro, m, dt, z0, v0, K, Vterm);
    land_numeric(g, S, C, ro, m, dt, z0, v0, K, Vterm);

    printf("~end~\n");
    return 0;
}