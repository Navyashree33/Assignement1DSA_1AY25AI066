#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int emp_id;
    enum { FULL_TIME, CONTRACT } type;

    union {
        float salary;
        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;
    } pay;
} Employee;

int main(void) {
    int n, i;
    float total_bill = 0, total_pay;
    Employee *emp;

    printf("Enter number of employees: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    emp = (Employee*) malloc(n * sizeof(Employee));

    if (emp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter details of employee %d\n", i + 1);

        printf("Enter name: ");
        scanf("%19s", emp[i].name);

        printf("Enter employee ID: ");
        if (scanf("%d", &emp[i].emp_id) != 1) {
            printf("Invalid employee ID.\n");
            free(emp);
            return 1;
        }

        printf("Enter employee type (0-Full-time, 1-Contract): ");
        if (scanf("%d", (int *)&emp[i].type) != 1 ||
            (emp[i].type != Employee::FULL_TIME &&
             emp[i].type != Employee::CONTRACT)) {
            printf("Invalid employee type.\n");
            free(emp);
            return 1;
        }

        if (emp[i].type == Employee::FULL_TIME) {
            printf("Enter monthly salary: ");
            if (scanf("%f", &emp[i].pay.salary) != 1) {
                printf("Invalid salary.\n");
                free(emp);
                return 1;
            }
        } else {
            printf("Enter hourly rate: ");
            if (scanf("%f",
                      &emp[i].pay.contract_info.hourly_rate) != 1) {
                printf("Invalid hourly rate.\n");
                free(emp);
                return 1;
            }

            printf("Enter hours worked: ");
            if (scanf("%d",
                      &emp[i].pay.contract_info.hours_worked) != 1) {
                printf("Invalid hours worked.\n");
                free(emp);
                return 1;
            }
        }
    }

    printf("\n========== EMPLOYEE PAYSLIPS ==========\n");

    for (i = 0; i < n; i++) {
        printf("\nEmployee ID: %d\n", emp[i].emp_id);
        printf("Name: %s\n", emp[i].name);

        if (emp[i].type == Employee::FULL_TIME) {
            total_pay = emp[i].pay.salary;
            printf("Type: Full-time\n");
            printf("Monthly Salary: %.2f\n",
                   emp[i].pay.salary);
        } else {
            total_pay =
                emp[i].pay.contract_info.hourly_rate *
                emp[i].pay.contract_info.hours_worked;

            printf("Type: Contract\n");
            printf("Hourly Rate: %.2f\n",
                   emp[i].pay.contract_info.hourly_rate);
            printf("Hours Worked: %d\n",
                   emp[i].pay.contract_info.hours_worked);
        }

        printf("Total Pay: %.2f\n", total_pay);
        total_bill += total_pay;
    }

    printf("\nTotal Salary Bill: %.2f\n", total_bill);

    free(emp);
    return 0;
}
