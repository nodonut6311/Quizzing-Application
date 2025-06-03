#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "quiz.h"

#define MAX_QUESTIONS 100

void shuffle(struct Question *questions, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Question temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

void studentMode() {
   
    FILE *f = fopen("Questions.bin", "rb");
    if (f == NULL) {
        printf("No quiz available. Please ask admin to add questions.\n");
        return;
    }

    
    struct Question questions[MAX_QUESTIONS];
    int count = 0;
    while (fread(&questions[count], sizeof(struct Question), 1, f) == 1) {
        count++;
    }
    fclose(f);

    if (count == 0) {
        printf("No questions found in the quiz.\n");
        return;
    }

    
    srand(time(NULL));
    shuffle(questions, count);

   
    int score = 0, correct = 0, wrong = 0;
    int userAnswer;
    time_t start;

    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    for (int i = 0; i < count; i++) {
        
        printf("\nQ%d: %s\n", i + 1, questions[i].question);
        printf("1. %s\n2. %s\n3. %s\n4. %s\n", 
               questions[i].opt1, questions[i].opt2, 
               questions[i].opt3, questions[i].opt4);
        printf("You have 10 seconds to answer...\n");

        
        start = time(NULL);
        printf("Enter your answer (1-4): ");

     
        char input[10];
        int timedOut = 0;
        if (fgets(input, sizeof(input), stdin) != NULL) {
            
            input[strcspn(input, "\n")] = '\0';

           
            if (difftime(time(NULL), start) > 10) {
                timedOut = 1;
            } else {
               
                if (sscanf(input, "%d", &userAnswer) != 1 || userAnswer < 1 || userAnswer > 4) {
                    userAnswer = 0; 
                }
            }
        } else {
            timedOut = 1; 
        }

     
        if (timedOut) {
            printf("Time’s up! No marks for this question.\n");
            wrong++;
           
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        
        if (userAnswer == 0) {
            printf("Invalid input! Treated as wrong answer.\n");
            wrong++;
        } else if (userAnswer == questions[i].key) {
            printf("Correct!\n");
            score += 5;
            correct++;
        } else {
            printf("Wrong! Correct answer was: Option %d\n", questions[i].key);
            score -= 1;
            wrong++;
        }

       
        while ((c = getchar()) != '\n' && c != EOF);
    }

   
    printf("\n--- Quiz Summary ---\n");
    printf("Correct Answers: %d\n", correct);
    printf("Wrong Answers: %d\n", wrong);
    printf("Total Score: %d\n", score);
}