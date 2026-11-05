// Helper function to map Roman characters to their integer values
int value(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default:  return 0;
    }
}

int romanToInt(char* s) {
    int total = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        int current = value(s[i]);
        int next = value(s[i + 1]); // Returns 0 at '\0' (end of string)

        if (current < next) {
            total -= current; // Subtractive notation (e.g., IV: -1 + 5 = 4)
        } else {
            total += current; // Standard addition (e.g., VI: +5 + 1 = 6)
        }
    }

    return total;
}
