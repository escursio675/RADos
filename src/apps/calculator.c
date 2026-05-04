#include "../stdint.h"
#include "calculator.h"
#include "../stdlib/stdio.h"
#include "../vga.h"

#define CALC_BUF 64
static char calcInput[CALC_BUF];
static int  calcLen = 0;

static const char* parsePtr;
static int         parseError;

static void skipSpaces(void) {
    while (*parsePtr == ' ') parsePtr++;
}

static int parseExpr(void);

static int parseFactor(void) {
    skipSpaces();
    if (parseError) return 0;
    if (*parsePtr == '-') {
        parsePtr++;
        return -parseFactor();
    }
    if (*parsePtr == '(') {
        parsePtr++;
        int val = parseExpr();
        skipSpaces();
        if (*parsePtr == ')') parsePtr++;
        else parseError = 1;
        return val;
    }
    if (*parsePtr >= '0' && *parsePtr <= '9') {
        int val = 0;
        while (*parsePtr >= '0' && *parsePtr <= '9') {
            val = val * 10 + (*parsePtr - '0');
            parsePtr++;
        }
        return val;
    }
    parseError = 1;
    return 0;
}

static int parseTerm(void) {
    int val = parseFactor();
    skipSpaces();
    while (!parseError && (*parsePtr == '*' || *parsePtr == '/')) {
        char op = *parsePtr++;
        int rhs = parseFactor();
        skipSpaces();
        if (op == '*') {
            val *= rhs;
        } else {
            if (rhs == 0) { parseError = 2; return 0; }
            val /= rhs;
        }
    }
    return val;
}

static int parseExpr(void) {
    int val = parseTerm();
    skipSpaces();
    while (!parseError && (*parsePtr == '+' || *parsePtr == '-')) {
        char op = *parsePtr++;
        int rhs = parseTerm();
        skipSpaces();
        val = (op == '+') ? val + rhs : val - rhs;
    }
    return val;
}

static void calcEvaluate(const char* expr) {
    parsePtr   = expr;
    parseError = 0;
    int result = parseExpr();
    skipSpaces();
    if (parseError == 2) {
        print("\n  Error: Division by zero\n\n  > ");
    } else if (parseError || *parsePtr != '\0') {
        print("\n  Error: Invalid expression\n\n  > ");
    } else {
        printf("\n  = %d\n\n  > ", result);
    }
}

void calcInit(void) {
    Reset();
    print("  CALCULATOR\n");
    print("  ----------\n");
    print("  Supports: + - * / ( )\n");
    print("  ESC to return to menu\n\n");
    print("  > ");
    calcLen = 0;
}

int calcHandleKey(char c) {
    if (c == 27) return 1;
    if (c == '\n') {
        calcInput[calcLen] = 0;
        if (calcLen > 0) {
            calcEvaluate(calcInput);
            calcLen = 0;
        }
    } else if (c == '\b') {
        if (calcLen > 0) {
            calcLen--;
            calcInput[calcLen] = 0;
            printf("\b");
        }
    } else if (calcLen < CALC_BUF - 1) {
        if ((c >= '0' && c <= '9') || c == '+' || c == '-' ||
            c == '*' || c == '/' || c == '(' || c == ')' || c == ' ') {
            calcInput[calcLen++] = c;
            printf("%c", c);
        }
    }
    return 0;
}
