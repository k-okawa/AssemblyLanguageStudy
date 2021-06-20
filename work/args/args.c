#include <stdio.h>

int return0() {
    return 0;
}

int sum1(int a) {
    return a + a;
}

int sum2(int a, int b) {
    return a + b;
}

int sum3(int a, int b, int c) {
    return a + b + c;
}

int many_sum(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o, int p) {
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p;
}

int main() {
    //printf("%d\n", many_sum(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
    printf("%d", sum2(1,2));
    return 0;
}