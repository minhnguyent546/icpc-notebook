/**
 * Description: Gray code is a binary numeral system where two successive values
 * differ in only one bit.
 */

int gray_code(int n) {
    return n ^ (n >> 1);
}

int rev_gray_code(int code) {
    int n = 0;
    while (code > 0) {
        n ^= code;
        code >>= 1;
    }
    return n;
}
