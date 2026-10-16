#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

int main(void) {
    int n, i;
    char choice;
    float sum = 0, average;
    struct Student *ptr, *temp, *topper;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    ptr = (struct Student *)malloc(n * sizeof(struct Student));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");

        if (scanf("%d %19s %f",
                  &ptr[i].roll_no,
                  ptr[i].name,
                  &ptr[i].marks) != 3) {
            printf("Invalid student data.\n");
            free(ptr);
            return 1;
        }
    }

    topper = &ptr[0];

    for (i = 0; i < n; i++) {
        sum += ptr[i].marks;

        if (ptr[i].marks > topper->marks) {
            topper = &ptr[i];
        }
    }

    average = sum / n;

    printf("\nAverage marks: %.2f\n", average);
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           topper->name, topper->roll_no, topper->marks);

    printf("\nAdd 2 more students? (y/n): ");

    if (scanf(" %c", &choice) != 1) {
        free(ptr);
        return 1;
    }

    if (choice == 'y' || choice == 'Y') {
        temp = (struct Student *)realloc(
            ptr, (n + 2) * sizeof(struct Student));

        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            free(ptr);
            return 1;
        }

        ptr = temp;

        for (i = n; i < n + 2; i++) {
            printf("Enter roll, name, marks: ");

            if (scanf("%d %19s %f",
                      &ptr[i].roll_no,
                      ptr[i].name,
                      &ptr[i].marks) != 3) {
                printf("Invalid student data.\n");
                free(ptr);
                return 1;
            }
        }

        n += 2;
        sum = 0;
        topper = &ptr[0];

        for (i = 0; i < n; i++) {
            sum += ptr[i].marks;

            if (ptr[i].marks > topper->marks) {
                topper = &ptr[i];
            }
        }

        average = sum / n;

        printf("\nUpdated average marks: %.2f\n", average);
        printf("Updated topper: %s (Roll %d, Marks %.2f)\n",
               topper->name, topper->roll_no, topper->marks);
    }

    free(ptr);
    return 0;
}
