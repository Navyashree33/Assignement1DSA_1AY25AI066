#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];  /* coef[i] = coefficient of x^(degree-i) */
} polynomial;

polynomial add(polynomial a, polynomial b) {
    polynomial result;
    int i, max_degree;

    max_degree = (a.degree > b.degree) ? a.degree : b.degree;
    result.degree = max_degree;

    for (i = 0; i <= max_degree; i++) {
        result.coef[i] = 0;

        if (i >= max_degree - a.degree)
            result.coef[i] += a.coef[i - (max_degree - a.degree)];

        if (i >= max_degree - b.degree)
            result.coef[i] += b.coef[i - (max_degree - b.degree)];
    }

    /* Remove leading zero coefficients */
    while (result.degree > 0 && result.coef[0] == 0) {
        for (i = 0; i < result.degree; i++)
            result.coef[i] = result.coef[i + 1];

        result.degree--;
    }

    return result;
}

void display(polynomial p) {
    int i, exponent, printed = 0;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        exponent = p.degree - i;

        if (c == 0)
            continue;

        if (printed) {
            if (c > 0)
                printf(" + ");
            else
                printf(" - ");
        } else if (c < 0) {
            printf("-");
        }

        if (c < 0)
            c = -c;

        if (exponent == 0) {
            printf("%g", c);
        } else {
            if (c != 1)
                printf("%g", c);

            printf("x");

            if (exponent > 1)
                printf("^%d", exponent);
        }

        printed = 1;
    }

    if (!printed)
        printf("0");

    printf("\n");
}

int main(void) {
    polynomial a, b, result;
    int i;

    printf("Enter degree of first polynomial: ");
    if (scanf("%d", &a.degree) != 1 ||
        a.degree < 0 || a.degree > 100) {
        printf("Invalid degree.\n");
        return 1;
    }

    printf("Enter coefficients of first polynomial "
           "from highest degree to constant term:\n");

    for (i = 0; i <= a.degree; i++) {
        if (scanf("%f", &a.coef[i]) != 1) {
            printf("Invalid coefficient.\n");
            return 1;
        }
    }

    printf("Enter degree of second polynomial: ");
    if (scanf("%d", &b.degree) != 1 ||
        b.degree < 0 || b.degree > 100) {
        printf("Invalid degree.\n");
        return 1;
    }

    printf("Enter coefficients of second polynomial "
           "from highest degree to constant term:\n");

    for (i = 0; i <= b.degree; i++) {
        if (scanf("%f", &b.coef[i]) != 1) {
            printf("Invalid coefficient.\n");
            return 1;
        }
    }

    result = add(a, b);

    printf("\nFirst polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    printf("Sum: ");
    display(result);

    return 0;
}
