#include <stdio.h>
#define MAX_SIZE 100

void inputSet(int set[], int *size);
int removeDuplicates(int set[], int size);
void printSet(const char *name, int set[], int size);
void findUnion(int A[], int sizeA, int B[], int sizeB);
void findIntersection(int A[], int sizeA, int B[], int sizeB);
void findDifference(int A[], int sizeA, int B[], int sizeB);
int checkSubset(int A[], int sizeA, int B[], int sizeB);

int main() {
    int A[MAX_SIZE], B[MAX_SIZE];
    int sizeA, sizeB;
    int choice;

    printf("=Enter Elements for Set A=\n");
    inputSet(A, &sizeA);
    sizeA = removeDuplicates(A, sizeA);

    printf("\n=Enter Elements for Set B=\n");
    inputSet(B, &sizeB);
    sizeB = removeDuplicates(B, sizeB);

    do {
        printf("\n===== MENU =====\n");
        printf("1. Get the Union of A and B.\n");
        printf("2. Get the Intersection of A and B.\n");
        printf("3. Get the Difference of B to A.\n");
        printf("4. Check if A is Subset of B.\n");
        printf("5. Exit the Program.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                findUnion(A, sizeA, B, sizeB);
                break;
            case 2:
                findIntersection(A, sizeA, B, sizeB);
                break;
            case 3:
                findDifference(B, sizeB, A, sizeA);
                break;
            case 4:
                if (checkSubset(A, sizeA, B, sizeB))
                    printf("A is a subset of B.\n");
                else
                    printf("A is NOT a subset of B.\n");
                break;
            case 5:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}

void inputSet(int set[], int *size) {
    printf("Enter Number of Elements: ");
    scanf("%d", size);

    printf("Enter %d Integers:\n", *size);
    for (int i = 0; i < *size; ++i) {
        scanf("%d", &set[i]);
    }
}

int removeDuplicates(int set[], int size) {
    int temp[MAX_SIZE];
    int newSize = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < newSize; j++) {
            if (set[i] == temp[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[newSize++] = set[i];
        }
    }

    for (int i = 0; i < newSize; i++) {
        set[i] = temp[i];
    }

    return newSize;
}

void printSet(const char *name, int set[], int size) {
    printf("%s = { ", name);
    for (int i = 0; i < size; ++i) {
        printf("%d ", set[i]);
    }
    printf("}\n");
}

void findUnion(int A[], int sizeA, int B[], int sizeB) {
    int result[MAX_SIZE];
    int size = 0;

    for (int i = 0; i < sizeA; i++) {
        result[size++] = A[i];
    }

    for (int i = 0; i < sizeB; i++) {
        int exists = 0;
        for (int j = 0; j < sizeA; j++) {
            if (B[i] == A[j]) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            result[size++] = B[i];
        }
    }

    printSet("Union = ", result, size);
}

void findIntersection(int A[], int sizeA, int B[], int sizeB) {
    int result[MAX_SIZE];
    int size = 0;

    for (int i = 0; i < sizeA; i++) {
        for (int j = 0; j < sizeB; j++) {
            if (A[i] == B[j]) {
                result[size++] = A[i];
                break;
            }
        }
    }

    printSet("Intersection = ", result, size);
}

void findDifference(int A[], int sizeA, int B[], int sizeB) {
    int result[MAX_SIZE];
    int size = 0;

    for (int i = 0; i < sizeA; i++) {
        int found = 0;
        for (int j = 0; j < sizeB; j++) {
            if (A[i] == B[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result[size++] = A[i];
        }
    }

    printSet("B - A = ", result, size);
}

int checkSubset(int A[], int sizeA, int B[], int sizeB) {
    for (int i = 0; i < sizeA; i++) {
        int found = 0;
        for (int j = 0; j < sizeB; j++) {
            if (A[i] == B[j]) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}
