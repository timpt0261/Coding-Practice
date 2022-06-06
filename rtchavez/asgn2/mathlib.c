#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14
//The Absolute Value Function
//
static inline double Abs(double x) {
    return x < 0.0 ? -x : x;
}

double Exp(double x) {
    double trm = 1.0, sum = trm;
    for (double k = 1.0; trm > EPSILON; k++) {
        trm *= Abs(x) / k;
        sum += trm;
    }
    return x < 0.0 ? 1 / sum : sum;
}

double Sin(double x) {
    double s = 1.0, v = x, t = x;
    for (double k = 3.0; Abs(t) > EPSILON; k += 2.0) {
        t *= (x * x) / ((k - 1) * k);
        s = -s;
        v += s * t;
    }
    return v;
}

double Cos(double x) {
    double s = 1.0, v = 1.0, t = 1.0, k = 2.0;
    for (double k = 2.0; Abs(t) > EPSILON; k += 2.0) {
        t *= (x * x) / ((k - 1) * k);
        s = -s;
        v += s * t;
    }
    return v;
}
/* Resources I used to implement Sqrt:
- https://git.ucsc.edu/cse13s/code-comments/-/blob/master/biSqrt.c
-Assigment 2 Psudie code 






 */
double Sqrt(double x) {
    double f = 1.0;
    while (x > 1) {
        x /= 4.0;
        f *= 2.0;
    }

    double z = 0.0, y = 1.0;
    while (Abs(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
    }
    return f * y;
}

double Log(double x) {
    double f = 0.0, y = 1.0;

    if (x > 29) {
        const double e = Exp(1);
        while (x > e) {
            x /= e;
            f += 1.0;
        }
    }
    for (double p = Exp(y); Abs(p - x) > EPSILON; y += x / p - 1) {
        p = Exp(y);
    }

    return f + y;
}

double integrate(double (*f)(double x), double a, double b, uint32_t n) {
    double h = (b - a) / n;
    double sum;
    sum = f(a) + f(b);
    for (int j = 1; j < n; j++) {
        long double k = a + j * h;
        if ((j % 2) == 0) {
            sum += 2 * f(k);
        } else {
            sum += 4 * f(k);
        }
    }
    sum *= h / 3;
    sum = (double) sum;
    return sum;
}
