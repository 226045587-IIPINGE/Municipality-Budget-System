#include <stdio.h>
#include <string.h>
#include "BudgetManagement.h"

#define MAX 10
#define NAME_LEN 50

char department[MAX][NAME_LEN];
double allocated_budget[MAX];
double expenditure[MAX];
int count = 0;

void enterBudget(void) {
    if (count >=MAX) {
        printf("Cannot add more departments.\n");
        return;
    }

    printf("\nEnter department name: ");
    fgets(department[count], NAME_LEN, stdin);
    department[count][strcspn(department[count], "\n")]='\0';

    if (strlen(department[count]) ==0){
        printf("Department name cannot be empty.\n");
        return;
    }

    printf("Enter allocated budget: ");
    scanf("%lf", &allocated_budget[count]);
    getchar();

    if (allocated_budget[count] < 0){
        printf("Invalid amount. Please enter a valid amount.\n");
        return;
    }

    expenditure[count] =0;
    count++;
    printf("Budget successfully recorded.\n");
}

void enterExpenditure(void) {
    char name[NAME_LEN];
    double amount;
    int n, found =0;

    if (count ==0){
        printf("No departments registered yet.\n");
        return;
    }

    printf("\nEnter department name: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    for (n = 0; n <count; n++){
        if (strcmp(department[n], name) == 0){
            printf("Enter expenditure amount: ");
            scanf("%lf", &amount);
            getchar();

            if (amount <0){
                printf("Expenditure cannot be negative.\n");
                return;
            }

            expenditure[n] =expenditure[n] +amount;
            found = 1;
            printf("Expenditure stored.\n");
            break;
        }
    }

    if (found == 0){
        printf("Department not found.\n");
    }
}

void displayBudgets(void){
    int n;
    double remaining;

    if (count ==0){
        printf("\nNo budget information available.\n");
        return;
    }

    printf("\n==========BUDGET INFORMATION==========\n");

    for (n = 0; n < count; n++){
        remaining = allocated_budget[n] - expenditure[n];

        printf("\nDepartment: %s\n", department[n]);
        printf("Allocated Budget: N$%.2f\n", allocated_budget[n]);
        printf("Expenditure: N$%.2f\n", expenditure[n]);
        printf("Remaining Budget: N$%.2f\n", remaining);

        if (remaining >= 0){
            printf("Status: Within budget\n");
        } 
        else{
            printf("Status: Exceeded budget\n");
        }
    }
}

void exceededDepartments(void){
    int n, found =0;

    printf("\n=====DEPARTMENTS OVER BUDGET=====\n");

    for (n = 0; n < count; n++){
        if (expenditure[n] > allocated_budget[n]){
            printf("%s exceeded by N$%.2f\n",
                   department[n],
                   expenditure[n] - allocated_budget[n]);
            found = 1;
        }
    }

    if (found == 0){
        printf("No departments have exceeded their budget.\n");
    }
}

void budgetMenu(void){
    int choice;

    do {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Departmental budget\n");
        printf("2. Expenditure\n");
        printf("3. Display budget information\n");
        printf("4. Show departments over budget\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice){
            case 1:
                enterBudget();
                break;
            case 2:
                enterExpenditure();
                break;
            case 3:
                displayBudgets();
                break;
            case 4:
                exceededDepartments();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}