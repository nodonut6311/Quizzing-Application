#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quiz.h"

void adminMode() {
    int n;
    int choice;
    char ans = 'y';
    while (ans == 'y') {
        printf("\nWhat operation would you like to perform?\n");
        printf("1: Add questions\n");
        printf("2: View Questions\n");
        printf("3: Edit Questions\n");
        printf("4: Delete Questions\n");
        printf("5: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting program.\n");
            break;
        }

        FILE *f;
        switch (choice) {
        case 1:
            f = fopen("Questions.bin", "ab");
            if (f == NULL) {
                printf("Error opening file for writing.\n");
                break;
            }
            printf("How many questions do you want to add?\n");
            scanf("%d", &n);
            struct Question *questions = malloc(n * sizeof(struct Question));

            for (int i = 0; i < n; i++) {
                printf("Enter the question:\n");
                getchar(); 
                fgets(questions[i].question, sizeof(questions[i].question), stdin);
                questions[i].question[strcspn(questions[i].question, "\n")] = '\0';

                printf("Enter Option 1:\n");
                fgets(questions[i].opt1, sizeof(questions[i].opt1), stdin);
                questions[i].opt1[strcspn(questions[i].opt1, "\n")] = '\0';

                printf("Enter Option 2:\n");
                fgets(questions[i].opt2, sizeof(questions[i].opt2), stdin);
                questions[i].opt2[strcspn(questions[i].opt2, "\n")] = '\0';

                printf("Enter Option 3:\n");
                fgets(questions[i].opt3, sizeof(questions[i].opt3), stdin);
                questions[i].opt3[strcspn(questions[i].opt3, "\n")] = '\0';

                printf("Enter Option 4:\n");
                fgets(questions[i].opt4, sizeof(questions[i].opt4), stdin);
                questions[i].opt4[strcspn(questions[i].opt4, "\n")] = '\0';

                printf("Enter the key option number:\n");
                scanf("%d", &(questions[i].key));

                fwrite(&(questions[i]), sizeof(struct Question), 1, f);
                printf("Question added successfully!\n");
            }

            free(questions);
            fclose(f);
            printf("Questions saved successfully.\n");
            printf("Do you want to continue? (y/n): ");
            getchar(); 
            scanf("%c",&ans);
            getchar();
            break;

        case 2:
            f = fopen("Questions.bin", "rb");
            if (f == NULL) {
                printf("Error opening file! Make sure questions exist.\n");
                break;
            }

            struct Question fetchedQuestions;
            printf("\n--- List of Questions ---\n");
            int index = 1;
            while (fread(&fetchedQuestions, sizeof(struct Question), 1, f) == 1) {
                printf("%d) %s\n", index, fetchedQuestions.question);
                printf("1. %s\n", fetchedQuestions.opt1);
                printf("2. %s\n", fetchedQuestions.opt2);
                printf("3. %s\n", fetchedQuestions.opt3);
                printf("4. %s\n", fetchedQuestions.opt4);
                printf("Correct Option: %d\n\n", fetchedQuestions.key);
                index++;
            }

            fclose(f);
            printf("Do you want to continue? (y/n): ");
            getchar(); 
            scanf("%c",&ans);
            break;

        case 3:  
            f = fopen("Questions.bin", "rb");
            if (f == NULL) {
                printf("Error opening file! Make sure questions exist.\n");
                break;
            }

            fseek(f, 0, SEEK_END);
            int total = ftell(f) / sizeof(struct Question);
            rewind(f);

            struct Question *allQuestions = malloc(total * sizeof(struct Question));
            fread(allQuestions, sizeof(struct Question), total, f);
            fclose(f);

            if (total == 0) {
                printf("No questions to edit.\n");
                free(allQuestions);
                break;
            }

            printf("\n--- List of Questions ---\n");
            for (int i = 0; i < total; i++) {
                printf("%d) %s\n", i + 1, allQuestions[i].question);
            }

            int qno;
            printf("Enter the question number to edit (1 to %d): ", total);
            scanf("%d", &qno);
            qno--;  

            if (qno < 0 || qno >= total) {
                printf("Invalid question number!\n");
                free(allQuestions);
                break;
            }

            getchar(); 
            printf("Enter new question text:\n");
            fgets(allQuestions[qno].question, sizeof(allQuestions[qno].question), stdin);
            allQuestions[qno].question[strcspn(allQuestions[qno].question, "\n")] = '\0';

            printf("Enter new Option 1:\n");
            fgets(allQuestions[qno].opt1, sizeof(allQuestions[qno].opt1), stdin);
            allQuestions[qno].opt1[strcspn(allQuestions[qno].opt1, "\n")] = '\0';

            printf("Enter new Option 2:\n");
            fgets(allQuestions[qno].opt2, sizeof(allQuestions[qno].opt2), stdin);
            allQuestions[qno].opt2[strcspn(allQuestions[qno].opt2, "\n")] = '\0';

            printf("Enter new Option 3:\n");
            fgets(allQuestions[qno].opt3, sizeof(allQuestions[qno].opt3), stdin);
            allQuestions[qno].opt3[strcspn(allQuestions[qno].opt3, "\n")] = '\0';

            printf("Enter new Option 4:\n");
            fgets(allQuestions[qno].opt4, sizeof(allQuestions[qno].opt4), stdin);
            allQuestions[qno].opt4[strcspn(allQuestions[qno].opt4, "\n")] = '\0';

            printf("Enter new correct option number: ");
            scanf("%d", &allQuestions[qno].key);

            f = fopen("Questions.bin", "wb");
            if (f == NULL) {
                printf("Error saving updates!\n");
            } else {
                fwrite(allQuestions, sizeof(struct Question), total, f);
                fclose(f);
                printf("Question updated successfully!\n");
            }

            free(allQuestions);
            printf("Do you want to continue? (y/n): ");
            getchar();
            scanf("%c", &ans);
            break;

        case 4: 
            f = fopen("Questions.bin", "rb");
            if (f == NULL) {
                printf("Error opening file! Make sure questions exist.\n");
                break;
            }

            fseek(f, 0, SEEK_END);
            total = ftell(f) / sizeof(struct Question);
            rewind(f);

            allQuestions = malloc(total * sizeof(struct Question));
            fread(allQuestions, sizeof(struct Question), total, f);
            fclose(f);

            if (total == 0) {
                printf("No questions to delete.\n");
                free(allQuestions);
                break;
            }

            printf("\n--- List of Questions ---\n");
            for (int i = 0; i < total; i++) {
                printf("%d) %s\n", i + 1, allQuestions[i].question);
            }

            printf("Enter the question number to delete (1 to %d): ", total);
            scanf("%d", &qno);
            qno--;  

            if (qno < 0 || qno >= total) {
                printf("Invalid question number!\n");
                free(allQuestions);
                break;
            }

            for (int i = qno; i < total - 1; i++) {
                allQuestions[i] = allQuestions[i + 1];
            }
            total--;

            f = fopen("Questions.bin", "wb");
            if (f == NULL) {
                printf("Error saving changes!\n");
            } else {
                fwrite(allQuestions, sizeof(struct Question), total, f);
                fclose(f);
                printf("Question deleted successfully!\n");
            }

            free(allQuestions);
            printf("Do you want to continue? (y/n): ");
            getchar();
            scanf("%c", &ans);
            break;

        default:
            printf("Invalid choice! Please enter 1, 2, 3, 4, or 5.\n");
            printf("Do you want to continue? (y/n): ");
            getchar();
            scanf("%c", &ans);
            break;
        }
    }
}
