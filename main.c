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
    srand(time(NULL));

    for (int i = 0; i < codeLength; i++) {
        const int rnd = rand() % (sizeof(colors) - 1);
        code[i] = colors[rnd];
    }
    code[codeLength] = '\0';
    return code;
}

bool validateInput(const char *input) {
    if (strlen(input) != codeLength) return false;

    for (int i = 0; i < codeLength; i++) {
        bool isValidChar = false;
        for (int j = 0; j < strlen(colors); j++) {
            if (input[i] == colors[j]) {
                isValidChar = true;
                break;
            }
        }
        if (!isValidChar) return false;
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

int main() {

    char *code = generateCode();
    printf("%s\n", code);

    char *input =  inputCode();
    printf("%s\n", input);



    free(code);
    free(input);
    return 0;
}
