#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "tokenizer.h"
#include "parser.h"


//every enter function expects that it is
//entered with parser.currentTok being a valid
//first token for one of its productions

//every function must exit with parser.currentTok being
//the first token AFTER the production associated with the
//function that was just exited


//this means we need to assert before we enter
//a given function



void expect(Symbol tok){
    getNextToken();
    checkTok(tok);
}

void checkTok(Symbol tok){
    assert(parser.currentTok == tok);
}



void enterStatement(void){

    printEnterProduction("Statement");
    
    switch (parser.currentTok){
	
	
    case TOK_IDENT:{
	assertAssignOrCall();
	enterAssignOrCall();
	break;
    }
    case TOK_IF:{
	assertIf();
	enterIf();
	break;
    }
    case TOK_WHILE:{
	assertWhile();
	enterWhile();
	break;
    }

    default:
	assert(0 && "Should not get here.");
	
    }
    

    printExitProduction("Statement");
}


void enterWhile(void){

    printEnterProduction("While");

    getNextToken();
    assertCondition();
    enterCondition();

    checkTok(TOK_L_CURLY);
    getNextToken();

    assertBlock();
    enterBlock();

    checkTok(TOK_R_CURLY);
    getNextToken();

    printExitProduction("While");
}

void enterAssign(void){
    printEnterProduction("Assign");
    getNextToken();
    
    assertExpression();
    enterExpression();

    checkTok(TOK_SEMICOLON);

    getNextToken();
    printExitProduction("Assign");

}

void enterExpression(void){
    printEnterProduction("Expression");
    
    //if we start with a +/- we must have a 'term' next
    if (isPlusMinus()){
	getNextToken();
    }
    
    assertTerm();
    enterTerm();

    while(isPlusMinus()){
	getNextToken();
	assertTerm();
	enterTerm();
    }
    
    printExitProduction("Expression");
}

void enterTerm(void){
    printEnterProduction("Term");

    assertFactor();
    enterFactor();

    while(isMultDiv()){
	getNextToken();
	assertFactor();
	enterFactor();
    }
	
    printExitProduction("Term");
}

void enterFactor(){
    printEnterProduction("Factor");
    //just a number
    if (parser.currentTok == TOK_NUMBER){
	getNextToken();
    }
    //another expression
    else if( parser.currentTok == TOK_L_PAREN){
	getNextToken();
	assertExpression();
	enterExpression();
	checkTok(TOK_R_PAREN);
	getNextToken();
    }
    //either a var or a function call
    else if( parser.currentTok == TOK_IDENT){
	enterVarOrFn();
        
    }
    else{
	assert(0 && "should not get here");
    }
    
    printExitProduction("Factor");
}

void enterVarOrFn(void){

    printEnterProduction("VarOrFn");

    //this fucks us up, we need to peek or figure something
    //else out
    getNextToken();

    
    //if we have L_PAREN, we know we have a function call
    //if not, just a var, so exit
    if (parser.currentTok == TOK_L_PAREN){
	getNextToken();
	
	while (isExpression()){
	    enterExpression();
	    if (parser.currentTok == TOK_COMMA){
		
		getNextToken();
		assert(isExpression());
		
	    }
	    
	}
	assert(parser.currentTok == TOK_R_PAREN);
	//expect(TOK_SEMICOLON);
	getNextToken();
    }
    
    
    printExitProduction("VarOrFn");

}

void enterFnCall(void){
    printEnterProduction("FnCall");

    getNextToken();
    
    while (isExpression()){
	enterExpression();
	if (parser.currentTok == TOK_COMMA){
	    
	    getNextToken();
	    assert(isExpression());
	    
	}
	
    }

    checkTok(TOK_R_PAREN);
    expect(TOK_SEMICOLON);
    getNextToken();
    
    printExitProduction("FnCall");

}

void enterAssignOrCall(void){

    printEnterProduction("AssignOrCall");
    
    getNextToken();

    if (parser.currentTok == TOK_ASSIGN){
	assertAssign();
	enterAssign();
    }
    else if(parser.currentTok == TOK_L_PAREN){
	assertFnCall();
	enterFnCall();
    }
    else{
	assert(0 && "should not get here");
    }

    printExitProduction("AssignOrCall");

}


void enterIf(void){
    printEnterProduction("If");
    
    getNextToken();
    assertCondition();
    enterCondition();

    checkTok(TOK_L_CURLY);
    getNextToken();
    assertBlock();
    enterBlock();
    checkTok(TOK_R_CURLY);
    getNextToken();
    
    printExitProduction("If");
}

void enterCondition(void){
    printEnterProduction("Condition");
    
    assertExpression();
    enterExpression();
    
    assertComparator();

    getNextToken();
    assertExpression();
    enterExpression();
    
    printExitProduction("Condition");
}

void enterFuncDef(void){
    printEnterProduction("Function");

    expect(TOK_IDENT);
    expect(TOK_L_PAREN);

    getNextToken();

    if (parser.currentTok != TOK_R_PAREN){
	assertFuncDefArgs();
	enterFuncDefArgs();
    }
    
    checkTok(TOK_R_PAREN);
    
    
    expect(TOK_L_CURLY);

    getNextToken();

    //can have arbitrarily many blocks inside a f'n
    while (isBlock()){
	enterBlock();
    }

    
    checkTok(TOK_RETURN);
    getNextToken();
    assertExpression();
    enterExpression();
    checkTok(TOK_SEMICOLON);
    expect(TOK_R_CURLY);
    getNextToken();

    
    printExitProduction("Function");
}

//parser.currentTok should be
//TOK_IDENT -ONLY- when entering this function,
//and should be TOK_R_PAREN upon exit
void enterFuncDefArgs(void){
    printEnterProduction("FunctionDefArgs");
    
    while (parser.currentTok == TOK_IDENT){
	
	getNextToken();
	if (parser.currentTok == TOK_COMMA){
	    
	    getNextToken();
	    assert(parser.currentTok == TOK_IDENT);
	    	    	    
	}
	
    }
    assert(parser.currentTok == TOK_R_PAREN);

    printExitProduction("FunctionDefArgs");
}


void enterBlock(void){

    printEnterProduction("Block");

    switch(parser.currentTok){

    case TOK_FUNCTION:{
	assertFuncDef();
	enterFuncDef();
	break;
    }
    case TOK_IDENT:
    case TOK_IF:
    case TOK_WHILE:{
	assertStatement();
	enterStatement();
	break;
    }
    default:{
	assert(0 && "expected either function definition or statement");
    }

    }
    
    
    printExitProduction("Block");

}




int main(int argc, char *argv[])
{
    char *buffer;
    fileToBuffer(argv[1], &buffer);
    initParser(buffer);
    
    getNextToken();
    
    assertBlock();
    while (isBlock()){
	assertBlock();
	enterBlock();
    }



    
    while (parser.currentTok != TOK_EOF){	
	getNextToken();	
	printCurrentToken();
	printCurrentTokString();
	
    }

    return 0;
    

}



/*
  Reads in a file and allocates storage for its char array at *buffer.
*/
void fileToBuffer(char* fileName, char **buffer){
    FILE *fp;
    long lSize;
    
    fp = fopen ( fileName , "r" );
    if( !fp ) perror(fileName);
    
    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );
    
    /* allocate memory for entire content */
    char* bufferSpace = (char*)calloc( 1, lSize+1 );
    
    
    if( !bufferSpace ) fclose(fp),fputs("memory alloc fails",stderr);

    /* copy the file into the buffer */
    if( 1!=fread( bufferSpace , lSize, 1 , fp) )
	fclose(fp),free(bufferSpace),fputs("entire read fails",stderr);

    *buffer = bufferSpace;
    fclose(fp);
}
