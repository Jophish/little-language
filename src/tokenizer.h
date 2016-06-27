#ifndef TOK_H
#define TOK_H

#define MAX_VAR_LEN 64 //maximum char length for TOK_IDENT

/* Enum for tokens*/
typedef enum {
    TOK_L_PAREN=0,
    TOK_R_PAREN,
    TOK_NUMBER,
    TOK_IDENT,
    TOK_PLUS,
    TOK_MINUS,
    TOK_MULT,
    TOK_DIVIDE,
    TOK_IF,
    TOK_WHILE,
    TOK_SEMICOLON,
    TOK_R_CURLY,
    TOK_L_CURLY,
    TOK_RETURN,
    TOK_FUNCTION,
    TOK_ASSIGN,
    TOK_EQUALS,
    TOK_LESS_THAN,
    TOK_GREATER_THAN,
    TOK_LEQ,
    TOK_GEQ
} Symbol;

typedef enum{
    PROD_PROGRAM=0,
    PROD_BLOCK,
    PROD_STATEMENT,
    PROD_CONDITION,
    PROD_EXPRESSION,
    PROD_TERM,
    PROD_FACTOR
}Production;

typedef struct{

    char *source;
    Production currentProd;
    Symbol currentTok;
    char *currentChar;

}Parser;


Parser parser;

void initParser(char*);
char *peekAhead(void);
void getNextToken(void);
void getNextChar(void);
void consumeWhitespace(void);
void printCurrentToken(void);

#endif // TOK_H
