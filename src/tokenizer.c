#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//for debugging
const char* tokStrings[] = {
    "TOK_L_PAREN",
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
    "TOK_GEQ",
    "TOK_EOF",
    "TOK_PRINT",
    "TOK_COMMA"
};

/*
  Initializes the global parser as declared in tokenizer.h
 */
void initParser(char *source){
    parser.source = source;
    parser.currentChar = source;
    parser.currentTok = 0;
    parser.currentProd = 0;
    parser.currentTokString = (char*)malloc(MAX_VAR_LEN);

}

/*
  Grabs the next token from input and sets it in the parser. Additionally, we 
  update the current string associated with the current token when it is relevant
  (i.e., we have a TOK_IDENT and need to remember its name). Ugly monolithic switch/case.
 */
void getNextToken(void){

    clearCurrentTokString();

    
    // all 1/2 char tokens
    switch(*(parser.currentChar)){

    case '\0':
	parser.currentTok= TOK_EOF;
	break;	
    case ',':
	parser.currentTok = TOK_COMMA;
	break;
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

	//if the next character is another "=", we must have a TOK_EQUALS, so
	//set the current token and increment the character pointer by one.
	if (*(peekAhead()) == '='){
	    getNextChar();
	    parser.currentTok = TOK_EQUALS;
	    break;
	}
	
	//otherwise we just have a plain old assignment
	else{
	    parser.currentTok = TOK_ASSIGN;
	    break;
	}
	
    case '<':
	
	//same as above, but for TOK_LEQ/TOK_LESS_THAN
	if (*(peekAhead()) == '='){
	    getNextChar();
	    parser.currentTok = TOK_LEQ;
	    break;
	}
	
	else{
	    parser.currentTok = TOK_LESS_THAN;
	    break;
	}
    case '>':

       	//likewise if the next one is "=" we have TOK_GEQ, do the same as above
	if(*(peekAhead()) == '='){
	    getNextChar();
	    parser.currentTok = TOK_GEQ;
	    break;
	}
	else{
	    parser.currentTok = TOK_GREATER_THAN;
	    break;
	}

    //we deal with function definition differently;
    //we could have "f" or the beginning of a TOK_IDENT
    case 'f':
	if (isspace(*(peekAhead()))){
	    parser.currentTok = TOK_FUNCTION;
	    break;
	}
	//if it's not a func definition, it must be TOK_IDENT, since
	//no other keyword begins with "f"
	else{
	    getTokIdent();
	    parser.currentTok = TOK_IDENT;
	    break;
        }

	
    default:

	/*all that we could have now is TOK_WHILE, TOK_IF, TOK_IDENT, TOK_NUMBER, 
	  TOK_RETURN, or TOK_PRINT, so we just have to check whether or not our 
	  current char is a letter of number*/
	
	if (isalpha(*(parser.currentChar))){
	    getTokIdent();
	    if (!strcmp((parser.currentTokString),"if\0")){
		parser.currentTok = TOK_IF;
		break;
		
	    }
	    else if(!strcmp((parser.currentTokString),"while\0")){
		parser.currentTok = TOK_WHILE;
		break;
		
	    }
	    else if(!strcmp((parser.currentTokString),"return\0")){
		parser.currentTok = TOK_RETURN;
		break;
		
	    }
	    else if(!strcmp((parser.currentTokString), "print\0")){
		parser.currentTok = TOK_PRINT;
		break;
		
	    }
	    else{
		parser.currentTok = TOK_IDENT;
		break;
		
	    }
	    
	}
	else if(isdigit(*(parser.currentChar))){
	    getNumIdent();
	    parser.currentTok = TOK_NUMBER;
	    break;
	    
	}
	
	
    }

    
    printCurrentToken();
    getNextChar();

}

/*
  Consumes input in the source when we know we're expecting a TOK_NUMBER, sets the parser's 
  currentTokString to a string representing the given number.
 */
void getNumIdent(void){
    int count = 0;
    while (!isspace(*(parser.currentChar)) && isdigit(*(parser.currentChar))){
	*(parser.currentTokString+count) = *(parser.currentChar);
	*(parser.currentChar++);
	count++;
    }
    *(parser.currentChar--);
    *(parser.currentTokString+count) = '\0';
}	
/*
  Consumes input in the source when we know we're expecting a TOK_IDENT or keyword, sets the
  parser's currentTokString to the associated text.
 */
void getTokIdent(void){
    int count = 0;
    while (!isspace(*(parser.currentChar)) && isalpha(*(parser.currentChar))){
	*(parser.currentTokString+count) = *(parser.currentChar);
	*(parser.currentChar++);
	count++;
    }
    *(parser.currentChar--);
    *(parser.currentTokString+count) = '\0';

}

/*
  Clears the parser's currentTokString so we can get a new string.
 */
void clearCurrentTokString(void){    
    memset(parser.currentTokString, 0, MAX_VAR_LEN);
}

/*
  Sets the parser's currentChar to the next non-whitespace character.
 */
void getNextChar(void){
    *(parser.currentChar++);
    consumeWhitespace();

}

/*
  Returns a pointer to the next character in the input without changing the parser's
  currentChar
 */
char* peekAhead(void){
    return (parser.currentChar + 1);
}

/*
  Increments the parser's currentChar until we reach a non-whitespace character.
 */
void consumeWhitespace(void){
    while (isspace(*parser.currentChar)){
	*(parser.currentChar++);
    }
}

/*
  For debugging. Prints string rep. of parser.currentToken.
 */
void printCurrentToken(void){
    printf("current token is: %s\n", tokStrings[parser.currentTok]);
}

/*
  For debugging. Prints current string (parser.currentTokString) associated with parser.currentToken.
 */
void printCurrentTokString(void){
    if (*(parser.currentTokString) != 0){
	printf("current string for above token is: %s\n", (parser.currentTokString));
    }
}

void printEnterProduction(char *name){
    if (DEBUG_ON){
	printf("Entering %s\n", name);
    }

}

void printExitProduction(char *name){
    if (DEBUG_ON){
	printf("Exiting %s\n", name);
    }

}
