#include <stdio.h>
#define MAX_GRADES 100

void insertGrades(int Grades[], int *Size);
void sortGrades(int Grades[], int N);
int calculateAverage(int Grades[], int N);
void findMinMax(int Grades[], int N, int *Min, int *Max);
void gradeDistribution(int Grades[], int N);
int searchGrade(int Grades[], int N, int Target);

int main() {
    int Grades[MAX_GRADES];
    int N = 0;
    int Choice;

    do {
        printf("====================================\n");
        printf("1. Insert Grades\n");
        printf("2. Sort Grades\n");
        printf("3. Average Grade\n");
        printf("4. Minimum and Maximum Grades\n");
        printf("5. Grade Distribution\n");
        printf("6. Search for Grade\n");
        printf("0. Exit\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &Choice);

        switch (Choice) {
            case 1:
                insertGrades(Grades, &N);
                break;
            case 2:
                if (N == 0) {
                    printf("No grades to sort.\n");
                } else {
                    sortGrades(Grades, N);
                }
                break;
            case 3:
                if (N == 0) {
                    printf("No grades to calculate average.\n");
                } else {
                    printf("Average: %d\n", calculateAverage(Grades, N));
                }
                break;
            case 4: {
                if (N == 0) {
                    printf("No grades to find min and max.\n");
                } else {
                    int Min, Max;
                    findMinMax(Grades, N, &Min, &Max);
                    printf("Minimum: %d\nMaximum: %d\n", Min, Max);
                }
                break;
            }
            case 5:
                if (N == 0) {
                    printf("No grades for distribution.\n");
                } else {
                    gradeDistribution(Grades, N);
                }
                break;
            case 6: {
                if (N == 0) {
                    printf("No grades to search.\n");
                } else {
                    int Target;
                    printf("Enter grade to search: ");
                    scanf("%d", &Target);
                    int Position = searchGrade(Grades, N, Target);
                    if (Position != -1) {
                        printf("Found at position %d\n",Position);
                    } else {
                        printf("Grade not found\n");
                    }
                }
                break;
            }
            case 0:
                printf("Exiting the program\n");
                break;
            default:
                printf("Invalid choice. Please try again\n");
        }
    } while (Choice != 0);

    return 0;
}

void insertGrades(int Grades[], int *Size) {
    printf("Enter number of grades: ");
    scanf("%d", Size);
    if (*Size > MAX_GRADES) {
        printf("Number exceeds maximum allowed grades %d\n", MAX_GRADES);
        return;
    }
    printf("Enter grades: ");
    for (int i = 0; i < *Size; i++) {
        scanf("%d", &Grades[i]);
    }
}

void sortGrades(int Grades[], int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (Grades[j] > Grades[j + 1]) {
                int temp = Grades[j];
                Grades[j] = Grades[j + 1];
                Grades[j + 1] = temp;
            }
        }
    }
    printf("Grades After Sorting: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", Grades[i]);
    }
    printf("\n");
}

int calculateAverage(int Grades[], int N) {
    int Sum = 0;
    for (int i = 0; i < N; i++) {
        Sum += Grades[i];
    }
    return Sum / N;
}

void findMinMax(int Grades[], int N, int *Min, int *Max) {
    *Min = *Max = Grades[0];
    for (int i = 1; i < N; i++) {
        if (Grades[i] < *Min) *Min = Grades[i];
        if (Grades[i] > *Max) *Max = Grades[i];
    }
}

void gradeDistribution(int Grades[], int N) {
    int A = 0, B = 0, C = 0, D = 0, F = 0;
    for (int i = 0; i < N; i++) {
        if (Grades[i] >= 90) {
            A++;
        } else if (Grades[i] >= 80) {
            B++;
        } else if (Grades[i] >= 70) {
            C++;
        } else if (Grades[i] >= 60) {
            D++;
        } else {
            F++;
        }
    }
    printf("Grade Distribution:\n");
    printf("A: %d\n", A);
    printf("B: %d\n", B);
    printf("C: %d\n", C);
    printf("D: %d\n", D);
    printf("F: %d\n", F);
}

int searchGrade(int Grades[], int N, int Target) {
    for (int i = 0; i < N; i++) {
        if (Grades[i] == Target) {
            return i;
        }
    }
    return -1;
}
