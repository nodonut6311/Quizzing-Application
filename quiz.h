#ifndef QUIZ_H
#define QUIZ_H

struct Question {
    char question[100];
    char opt1[50];
    char opt2[50];
    char opt3[50];
    char opt4[50];
    int key;
};

#endif