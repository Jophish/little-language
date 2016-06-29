#ifndef PARSER_H
#define PARSER_H


void fileToBuffer(char*, char**);

void enterBlock(void);
void enterFuncDef(void);
void enterStatement(void);
void enterIf(void);
void enterWhile(void);
void enterAssignmentOrFnCall(void);
void enterCondition(void);
void enterExpression(void);
void enterTerm(void);
void enterFactor(void);
void enterVarOrFn(void);
void enterFuncDefArgs(void);
void enterAssignOrCall(void);
void enterAssign(void);
void enterFnCall(void);

void checkTok(Symbol);
void expect(Symbol);

void assertBlock(void);
void assertFuncDef(void);
void assertFuncDefArgs(void);
void assertAssignOrCall(void);
void assertWhile(void);
void assertFnCall(void);
void assertAssign(void);
void assertStatement(void);
void assertExpression(void);
void assertTerm(void);
void assertFactor(void);
void assertCondition(void);
void assertComparator(void);

int isStatement(void);
int isBlock(void);
int isPlusMinus(void);
int isExpression(void);
int isMultDiv(void);

//////////////////////////////////
//Asserts for f'n preconditions//
////////////////////////////////

void assertComparator(void){
    assert(parser.currentTok == TOK_EQUALS ||
	   parser.currentTok == TOK_LESS_THAN ||
	   parser.currentTok == TOK_GREATER_THAN ||
	   parser.currentTok == TOK_GEQ ||
	   parser.currentTok == TOK_LEQ);
}

void assertCondition(void){
    assertExpression();
}

void assertFactor(void){
    assertTerm();
}

void assertTerm(void){
    assert(parser.currentTok == TOK_IDENT ||
	   parser.currentTok == TOK_NUMBER ||
	   parser.currentTok == TOK_L_PAREN);
}
void assertExpression(void){
     assert(parser.currentTok == TOK_PLUS ||
	    parser.currentTok == TOK_MINUS ||
	    parser.currentTok == TOK_NUMBER ||
	    parser.currentTok == TOK_L_PAREN ||
	    parser.currentTok == TOK_IDENT);
}

void assertStatement(void){
    assert(parser.currentTok == TOK_IDENT ||
	   parser.currentTok == TOK_IF ||
	   parser.currentTok == TOK_WHILE);
}

void assertFnCall(void){
    checkTok(TOK_L_PAREN);
}

void assertAssign(void){
    checkTok(TOK_ASSIGN);
}

void assertWhile(void){
    checkTok(TOK_WHILE);
}

void assertIf(void){
    checkTok(TOK_IF);
}

void assertAssignOrCall(void){
    checkTok(TOK_IDENT);
}

void assertFuncDefArgs(void){
    checkTok(TOK_IDENT);
}

void assertFuncDef(void){
    checkTok(TOK_FUNCTION);
}

void assertBlock(void){
    assert(parser.currentTok == TOK_FUNCTION ||
	   parser.currentTok == TOK_IDENT ||
	   parser.currentTok == TOK_IF ||
	   parser.currentTok == TOK_WHILE);
}


////////////////////////////////
//Conditional checks for f'ns//
//////////////////////////////

int isMultDiv(void){
    if(parser.currentTok == TOK_MULT ||
       parser.currentTok == TOK_DIVIDE){
	return 1;
    }
    else{
	return 0;
    }
}

int isExpression(void){
    if(parser.currentTok == TOK_PLUS ||
       parser.currentTok == TOK_MINUS ||
       parser.currentTok == TOK_NUMBER ||
       parser.currentTok == TOK_L_PAREN ||
       parser.currentTok == TOK_IDENT){
	return 1;
    }
    else{
	return 0;
    }
    
}

int isPlusMinus(void){
    if (parser.currentTok == TOK_PLUS ||
	parser.currentTok == TOK_MINUS){
	return 1;
    }
    else{
	return 0;
    }
}


int isStatement(void){
    if (parser.currentTok == TOK_IDENT ||
	parser.currentTok == TOK_IF ||
	parser.currentTok == TOK_WHILE){
	return 1;
    }
    else{
	return 0;
    }
}

int isBlock(void){
    if (parser.currentTok == TOK_FUNCTION ||
	parser.currentTok == TOK_IDENT ||
	parser.currentTok == TOK_IF ||
	parser.currentTok == TOK_WHILE){
	return 1;
    }
    else{
	return 0;
    }
}

#endif // PARSER_H
