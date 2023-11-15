#include <stdio.h>

int input(int *a, int *b, int n);
void output(int *a, int n);
void merge_sort(int *a, int l, int r);
void merge(int *a, int l, int m, int r);
void quick_sort(int *a, int n);
void swap(int *a, int *b);

int main() {
    int n = 10;
    int res_data1[n], res_data2[n];
    if (!input(res_data1, res_data2, n)) {
        printf("n/a");
    } else {
        merge_sort(res_data1, 0, 10);
        output(res_data1, n);
        printf("\n");
        quick_sort(res_data2, n);
        output(res_data2, n);
    }
    return 0;
}

int input(int *a, int *b, int n) {
    int res_flag = 1;
    for (int *p1 = a, *p2 = b; p1 - a < n; p1++, p2++) {
        if (scanf("%d", p1) != 1) {
            res_flag = 0;
        } else {
            *p2 = *p1;
        }
    }
    return res_flag;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d", *p);
        if (p - a != n - 1) {
            printf(" ");
        }
    }
}

void merge(int *a, int l, int m, int r) {
    int i1 = 0, i2 = 0;
    int temp[r - l];
    while (l + i1 < m && m + i2 < r) {
        if (a[l + i1] < a[m + i2]) {
            temp[i1 + i2] = a[l + i1];
            i1++;
        } else {
            temp[i1 + i2] = a[m + i2];
            i2++;
        }
    }

    while (l + i1 < m) {
        temp[i1 + i2] = a[l + i1];
        i1++;
    }

    while (m + i2 < r) {
        temp[i1 + i2] = a[m + i2];
        i2++;
    }

    for (int i = 0; i < i1 + i2; i++) {
        a[l + i] = temp[i];
    }
}

void merge_sort(int *a, int l, int r) {
    int m = 0;
    if (l + 1 < r) {
        m = (l + r) / 2;
        merge_sort(a, l, m);
        merge_sort(a, m, r);
        merge(a, l, m, r);
    }
}

void quick_sort(int *a, int n) {
    int l = 0;
    int r = n - 1;
    int m = a[n / 2];
    do {
        while (a[l] < m) {
            l++;
        }
        while (a[r] > m) {
            r--;
        }
        if (l <= r) {
            swap((a + l), (a + r));
            l++;
            r--;
        }
    } while (l <= r);
    if (r > 0) {
        quick_sort(a, r + 1);
    }
    if (l < n) {
        quick_sort((a + l), n - l);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}