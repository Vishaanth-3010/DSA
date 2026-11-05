#include <stdbool.h>
#include <string.h>

bool isValid(char* s) {
    int n = strlen(s);
    char stack[n];
    int top = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        // Push matching closing bracket
        if (c == '(') {
            stack[++top] = ')';
        } else if (c == '{') {
            stack[++top] = '}';
        } else if (c == '[') {
            stack[++top] = ']';
        } else {
            // Check if matches or if stack is empty
            if (top == -1 || stack[top] != c) {
                return false;
            }
            top--; // Pop
        }
    }

    // Valid only if stack is empty
    return top == -1;
}