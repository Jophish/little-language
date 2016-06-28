#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "tokenizer.h"


void fileToBuffer(char*, char**);

int main(int argc, char *argv[])
{
    char *buffer;
    fileToBuffer(argv[1], &buffer);

    
    initParser(buffer);
    
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
