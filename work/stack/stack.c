#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}

int sum2(int a, int b, int c) {
    return sum(a, b);
}

int many_sum(int a, int b, int c, int d, int e, int f, int g, int h) {
    return a + b + c + d + e + f + g + h;
}

int func() {
    return many_sum(1,2,3,4,5,6,7,8);
}

int func2() {
    return func();
}

int func3() {
    return func2() + 1;
}

int main() {
    printf("%d", func3());
}