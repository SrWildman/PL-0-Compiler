//Sam Wildman
//S2878126
//COP 3402 Spring 2015
//Homework 3 - Driver

/* Driver is the main function for the compiler. It 
gets called and its main method calls all functions that
are declared and defined in the other files. The driver also
prints to the console information based on given flags*/


#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Compiler.h"
 

int main(int argc, char **argv){
	
	char* tmp;	
	int i;

	//functions for the Lexical Alalyzer
	Initialize("input.txt");
	ReadClean("input.txt", "cleaninput.txt");
	Tokenize("cleaninput.txt", "lexemetable.txt", "lexemelist.txt");



	//check for -l flag and if it exists, print the lexeme list
	for(i=1; i<argc; i++){
		if(!strcmp(argv[i],"-l")){
			fp = fopen("lexemelist.txt", "r");
			   if ( fp != NULL ){
			   		
			   	  printf("\n");

			      char line[1000];
			      while ( fgets ( line, sizeof line, fp ) != NULL ){
			         fputs ( line, stdout );
			      }
			      printf("\n\n");
			      fclose ( fp );
			   }
		}
	}



	//functions for the Parser
	Initialize2("lexemelist.txt", "mcode.txt");
	Get();
	tmp = Block(0);
	if(!strcmp(tmp, ".")){
		Gen(2,0,0);
		printOut();
		fclose(fp);
	}
	else {
		printf("%s\n", tmp);
		Error(9);
	}



	//successful parsing
	printf("No errors, program is syntactically correct.\n");



	//check for -a flag and if it exists, print the generated assembly code
	for(i=1; i<argc; i++){
		if(!strcmp(argv[i],"-a")){
			fp = fopen("mcode.txt", "r");
			   if ( fp != NULL ){
			      
			      printf("\n");

			      char line[1000];
			      while ( fgets ( line, sizeof line, fp ) != NULL ){
			         fputs ( line, stdout );
			      }
			      printf("\n");
			      fclose ( fp );
			   }
		}
	}



	//functions for the P-Machine
	RWInput("mcode.txt", "stacktrace.txt");
	printf("Output:\n");
	Run();



	//check for -v flag and if it exists, print the stack trace
	for(i=1; i<argc; i++){
		if(!strcmp(argv[i],"-v")){
			fp = fopen("stacktrace.txt", "r");
			   if ( fp != NULL ){
			      
			      printf("\n");

			      char line[1000];
			      while ( fgets ( line, sizeof line, fp ) != NULL ){
			         fputs ( line, stdout );
			      }
			      printf("\n");
			      fclose ( fp );
			   }
		}
	}

	return 0;
}