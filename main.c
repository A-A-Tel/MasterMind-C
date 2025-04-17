#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef enum { false, true } bool;

const int tries = 10;
const unsigned long codeLength = 4;
const char colors[] = "RGBYPC";

void toUppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

char *generateCode() {

    char *code = malloc((codeLength+1) * sizeof(char));
    if (code == NULL) {
        printf("Malloc Failure\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < codeLength; i++) {
        const int rnd = rand() % (sizeof(colors) - 1);
        code[i] = colors[rnd];
    }
    code[codeLength] = '\0';
    return code;
}

bool validateInput(const char *input) {
    if (strlen(input) != codeLength) {
        printf("Invalid input, try again...\n");
        return false;
    }

    for (int i = 0; i < codeLength; i++) {
        bool isValidChar = false;
        for (int j = 0; j < strlen(colors); j++) {
            if (input[i] == colors[j]) {
                isValidChar = true;
                break;
            }
        }
        if (!isValidChar) {
            printf("Invalid input, try again...\n");
            return false;
        }
    }

    return true;
}

char *inputCode() {

    char *input = malloc(5 * sizeof(char));
    if (input == NULL) {
        printf("Malloc failure\n");
        exit(1);
    }
    do {
        scanf("%4s", input);
        toUppercase(input);

    } while (!validateInput(input));

    return input;
}

void evaluateInput(const char *input,const char *code) {
    unsigned long score = 0;
    char *eval = malloc((codeLength + 1) * sizeof(char));
    for (int i = 0; input[i]; i++) {
        eval[i] = '-';
        if (input[i] == code[i]) {
            eval[i] = 'B';
            score++;
        } else {
            for (int j = 0; j < codeLength; j++) {
                if (i != j && input[i] == code[j]) {
                    eval[i] = 'W';
                }
            }
        }
    }
    eval[codeLength] = '\0';
    printf("%s\n", eval);
    free(eval);

    if (score == codeLength) {
        printf("Congrats! You have cracked the code!\n");
        exit(0);
    }
}

int main() {

    char *code = generateCode();

    for (int i = 1; i <= tries; i++) {
        printf("Try: %d\nChoose from the colors '%s'\nEnter code with length %lu...\n", i, colors, codeLength);
        char *input = inputCode();
        evaluateInput(input, code);
        free(input);
    }

    free(code);
    return 0;
}
