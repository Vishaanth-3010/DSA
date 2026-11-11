bool isPalindrome(int x) {
    if (x < 0) {
        return false;
    }

    int original = x;
    long rev = 0;
    int i;
    int c = 0;
    int temp = x;

    while (temp != 0) {
        temp = temp / 10;
        c++;
    }

    for (i = 0; i < c; i++) {
        int digit = x % 10;
        rev = rev * 10 + digit;
        x = x / 10;
    }

    if (original == rev) {
        return true;
    } else {
        return false;
    }
}