#include <cstdio>
#include <cmath>

int main()
{
    std::puts("please enter a, b and c fot `ax^2 + bx + c = 0`:");
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);
    float discr = sqrt(b * b - 4 * a * c);
    float x1 = (-b + discr) / 2 / a;
    float x2 = (-b - discr) / 2 / a;
    std::printf("x1: %f\n", x1);
    std::printf("x2: %f\n", x2);
}