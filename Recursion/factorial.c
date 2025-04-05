#include <stdio.h>
#include <errno.h>
#include <string.h>

unsigned long factorial(int n) {
    if (n < 0) {
        errno = EDOM;  // Domain error (standard error code for math functions)
        return 0;
    }

    if (n == 0) return 1;
    return (unsigned long)n * factorial(n - 1);
}

int main() {
    int n;
    printf("Enter a non-negative number: ");
    scanf("%d", &n);

    errno = 0;  // Clear errno before calling the function

    unsigned long result = factorial(n);

    if (errno == EDOM) {
        printf("Error: factorial not defined for negative numbers.\n");
    } else {
        printf("Factorial of %d is %lu\n", n, result);
    }

    return 0;
}
