//Code:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESIGNATION 70
#define MAX_NAME 70

struct Employee {
    int empID;
    char empFullName[MAX_NAME];
    int empYears;
    int empWage;
    char empRole[MAX_DESIGNATION];
    struct Employee* next;
};

// insert employee
struct Employee* addEmployee(struct Employee* head, int id, int years, int wage, char fullName[], char role[]) {
    struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    if (newEmployee == NULL) {
        printf("\n Allocation failed \n");
        exit(0);
    }
    newEmployee->empID = id;
    newEmployee->empYears = years;
    newEmployee->empWage = wage;
    strncpy(newEmployee->empFullName, fullName, MAX_NAME - 1);
    strncpy(newEmployee->empRole, role, MAX_DESIGNATION - 1);
    newEmployee->empFullName[MAX_NAME - 1] = '\0';
    newEmployee->empRole[MAX_DESIGNATION - 1] = '\0';
    newEmployee->next = head;
    return newEmployee;
}

// delete employee by ID
struct Employee* removeEmployee(struct Employee* head, int id) {
    struct Employee* current = head;
    struct Employee* previous = NULL;

    while (current != NULL) {
        if (current->empID == id) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            free(current);
            printf("\n Removed\n");
            return head;
        }
        previous = current;
        current = current->next;
    }

    printf("\n Employee ID %d not found\n", id);
    return head;
}

// search an employee by ID
void findEmployee(struct Employee* head, int ID) {
    struct Employee* current = head;
    while (current != NULL) {
        if (current->empID == ID) {
            printf("\n ID found:\n");
            printf("\n Employee ID: %d", current->empID);
            printf("\n Name: %s", current->empFullName);
            printf("\n Years: %d", current->empYears);
            printf("\n Role: %s", current->empRole);
            printf("\n Wage: %d\n", current->empWage);
            return;
        }
        current = current->next;
    }
    printf("\n Employee ID %d not found\n", ID);
}

// display all employees
void displayEmployees(struct Employee* head) {
    struct Employee* current = head;
    while (current != NULL) {
        printf("\n Employee ID: %d", current->empID);
        printf(" \n Name: %s", current->empFullName);
        printf(" \n Years: %d", current->empYears);
        printf("\n Role: %s", current->empRole);
        printf("\n Wage: %d\n", current->empWage);
        current = current->next;
    }
}

// Sort employees by ID
struct Employee* sortEmployees(struct Employee* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct Employee* current;
    struct Employee* index;
    struct Employee temp;

    for (current = head; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->empID > index->empID) {
                temp = *current;
                *current = *index;
                *index = temp;

                struct Employee* tempNext = current->next;
                current->next = index->next;
                index->next = tempNext;
            }
        }
    }
    return head;
}

int main() {
    struct Employee* employeesList = NULL;
    int choice;
    int id;
    int years;
    int wage;
    char fullName[MAX_NAME];
    char role[MAX_DESIGNATION];

    printf("\t\t\t------------------WELCOME TO EMPLOYEE MANAGEMENT SYSTEM-----------------\n\n");

    printf("\t\t\t\t* Press 1 to Add an Employee \n");
    printf("\t\t\t\t* Press 2 to Find an Employee \n");
    printf("\t\t\t\t* Press 3 to Display Employee Data \n");
    printf("\t\t\t\t* Press 4 to Remove an Employeea \n");
    printf("\t\t\t\t* Press 5 to EXIT \n");

    while (1) {
        printf("Enter option: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n Enter the Employee ID: ");
                scanf("%d", &id);
                printf(" Enter the Employee full name: ");
                scanf(" %[^\n]", fullName);  // Allows full names with spaces
                printf(" Enter the Employee years of service: ");
                scanf("%d", &years);
                printf(" Enter the Employee role: ");
                scanf(" %[^\n]", role);  // Allows roles with spaces
                printf(" Enter the Employee wage: ");
                scanf("%d", &wage);
                employeesList = addEmployee(employeesList, id, years, wage, fullName, role);
                break;
            case 2:
                printf("\n Enter the employee ID to be found: ");
                scanf("%d", &id);
                findEmployee(employeesList, id);
                break;
            case 3:

                if (employeesList == NULL) {
                    printf("\n List is empty.");
                } else {
                    employeesList = sortEmployees(employeesList);  // Sort the list before displaying
                    displayEmployees(employeesList);
                }
                break;
            case 4:

                printf("\n Enter the employee ID to be removed: ");
                scanf("%d", &id);
                employeesList = removeEmployee(employeesList, id);
                break;
            case 5:
                printf("Exited successfully.\n");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
}
