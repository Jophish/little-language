#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//for debugging
const char* tokStrings[] = {"TOK_L_PAREN",
    "TOK_R_PAREN",
    "TOK_NUMBER",
    "TOK_IDENT",
    "TOK_PLUS",
    "TOK_MINUS",
    "TOK_MULT",
    "TOK_DIVIDE",
    "TOK_IF",
    "TOK_WHILE",
    "TOK_SEMICOLON",
    "TOK_R_CURLY",
    "TOK_L_CURLY",
    "TOK_RETURN",
    "TOK_FUNCTION",
    "TOK_ASSIGN",
    "TOK_EQUALS",
    "TOK_LESS_THAN",
    "TOK_GREATER_THAN",
    "TOK_LEQ",
    "TOK_GEQ"
};

void initParser(char *source){
    parser.source = source;
    parser.currentChar = source;
    parser.currentTok = 0;
    parser.currentProd = 0;

}

void getNextToken(void){
    


    // all 1 char tokens
    switch(*(parser.currentChar)){
	
    case '(':
	parser.currentTok = TOK_L_PAREN;
	break;

    case ')':
	parser.currentTok = TOK_R_PAREN;
	break;

    case '+':
	parser.currentTok = TOK_PLUS;
	break;
    case '-':
	parser.currentTok = TOK_MINUS;
	break;

    case '*':
	parser.currentTok = TOK_MULT;
	break;

    case '/':
	parser.currentTok = TOK_DIVIDE;
	break;

    case ';':
	parser.currentTok = TOK_SEMICOLON;
	break;

    case '{':
	parser.currentTok = TOK_L_CURLY;
	break;

    case '}':
	parser.currentTok = TOK_R_CURLY;
	break;

    case '=':
	parser.currentTok = TOK_ASSIGN;
	break;

    case '<':
	parser.currentTok = TOK_LESS_THAN;
	break;

    case '>':
	parser.currentTok = TOK_GREATER_THAN;
	break;
    }
    
	
	/*case 'f':
	if (isspace(*(peekAhead()))){
	    parser.currentTok = TOK_FUNCTION;
	    break;
	}
	else{
	    
	while */
    
    
    getNextChar();

}

void getNextChar(void){
    *(parser.currentChar++);
    consumeWhitespace();

}

char* peekAhead(void){
    return (parser.currentChar + 1);
}

void consumeWhitespace(void){
    while (isspace(*parser.currentChar)){
	*(parser.currentChar++);
    }
}

void printCurrentToken(void){
    printf("current token is: %s\n", tokStrings[parser.currentTok]);
}
