#include <stdio.h>
#include <stdlib.h>
#include "quiz.h"
#include "admin.h"
#include "student.h"
int main() {
    int choice;

    while (1) {
        printf("\n--- Quiz Application ---\n");
        printf("1. Admin\n");
        printf("2. Student\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminMode();
                break;
            case 2:
                studentMode();
                break;
            case 3:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}