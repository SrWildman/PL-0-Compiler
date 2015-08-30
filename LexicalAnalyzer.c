//Sam Wildman
//S2878126
//COP 3402 Spring 2015
//Homework 2 - Lexical Analyzer

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Compiler.h"



char* input;
char** lexemes;
int* tokentypes;
int error = 0;
int stop = 0;





//Initialize arrays based on size of input file
void Initialize(char in[]){

	int chars = 0;
	int i = 0;

	fp = fopen(in, "r");
	while(!feof(fp)){
		fgetc(fp);
		chars++;
	}

	fclose(fp);

	input = malloc(sizeof(char) * chars+2);
	tokentypes = malloc(sizeof(int) * chars+2);
	lexemes = malloc(sizeof(char*) * chars+2);
	for(i = 0; i < chars+2; i++){
		lexemes[i] = malloc(sizeof(char) * 12);
	}

}





//Append adds a single char c to the end of a string s
//this avoids casting and converting issues using strcat()
void Append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}





//ReadClean reads in an input file with a name specified by in,
//removes all comments, and outputs a clean input file to the name
//specified by out
void ReadClean(char in[], char out[]){

	int cur = 0;
	int i = 0;
	char tmp;
	int star = 0;

	fp = fopen(in, "r");
	
	if(fp == NULL){
		printf("ERROR OPENING FILE %s!!\n", in);
	}

	//while we are not at the end of the file
	while(!feof(fp)){

		//read in the next character regardless of what it is
		input[cur] = fgetc(fp);

		//a comment is specified by /*content*/
		//if the char we just read was a '/' we might be at the start of a comment.
		if(input[cur++] == '/'){
			
			//get the next char and check if it is a '*' which signifies 
			//we have the 2 chars "/*" which is the start of a comment
			input[cur] = fgetc(fp);
			if(input[cur] =='*'){
				
				//we want to ignore these last two chars so we decrement our cur
				//variable and replace the '/' and '*' with spaces for simplicity.
				input[cur--] = ' ';
				input[cur] = ' ';

				//repeat the same process in reverse as "*/" signifies the 
				//end of a comment. We ignore everything until we reach the end of the comment
				while(!feof(fp)){
					
					tmp = fgetc(fp);

					if(tmp == '*'){
						star = 1;
					}
					else if(star == 1 && tmp == '/'){
							break;
					}
					else star = 0;
				}
			}
		}
	}

	fclose(fp);
	fp = fopen(out, "w");

	//print out our clean input 
	tmp = input[i++];
	while(i < cur){
		fprintf(fp, "%c", tmp);
		tmp = input[i++];
	}
	fclose(fp);
}





//Tokenize takes in our clean input file specified by in, splits the input into tokens,
//outputs a list of lexemes and their token types as well as list of just the token types
//specified by out1 and out2
void Tokenize(char in[], char out1[], char out2[]){

	int spot = 0;
	int numChars = 0;
	int i = 0;
	fp = fopen(in, "r");

	//initialize our chars
	char prev, next;
	char cur = fgetc(fp);
	next = fgetc(fp);

	//tmp will hold our lexemes before we parse them
	char tmp[13] = "";

	//while we dont want to stop and we dont have an error, keep going
	while(!stop && !error){
		
		//we are reading chars into next so if we are at the end of the file
		//run this itteration then stop
		if(feof(fp)){
			stop = 1;
		}

		//switch statement looks at our current char and decides what to do
		//based on cur, we assign the appropriate values to our variables 
		switch(cur){

			//Null_sym
			case '\0':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 1;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Plus_sym
			case '+':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 4;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Minus_sym
			case '-':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 5;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Mult_sym
			case '*':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 6;
			spot++;
			prev = cur;
			cur = next;	
			next = fgetc(fp);
			break;

			//Slash_sym
			case '/':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 7;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Eql_sym
			case '=':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 9;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Lparent_sym
			case '(':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 15;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Rparent_sym
			case ')':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 16;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Comma_sym
			case ',':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 17;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Semicolon_sym
			case ';':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 18;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Period_sym
			case '.':
			Append(lexemes[spot], cur);
			tokentypes[spot] = 19;
			spot++;
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;


			//these next cases deal with tokens that consist of multiple chars
			//we check the first char and then look at the next one and decide
			//what pattern it matches


			//Neq_sym, Leq_sym, Less_sym
			case '<':
			if(next == '>'){
				strcpy(lexemes[spot], "<>");
				tokentypes[spot] = 10;
				prev = next;
				cur = fgetc(fp);
				spot++;
			}
			else if(next == '='){
				strcpy(lexemes[spot], "<=");
				tokentypes[spot] = 12;
				prev = next;
				cur = fgetc(fp);
				spot++;
			}
			else{
				strcpy(lexemes[spot], "<");
				tokentypes[spot] = 11;
				prev = cur;
				cur = next;
				spot++;
			}
			next = fgetc(fp);
			break;

			//Geq_sym, Gtr_sym
			case '>':
			if(next == '='){
				strcpy(lexemes[spot], ">=");
				tokentypes[spot] = 14;
				prev = next;
				cur = fgetc(fp);
				spot++;
			}
			else{
				strcpy(lexemes[spot], ">");
				tokentypes[spot] = 13;
				prev = cur;
				cur = next;
				spot++;
			}
			next = fgetc(fp);
			break;

			//Becomes_sym
			case ':':
			if(next == '='){
				strcpy(lexemes[spot], ":=");
				tokentypes[spot] = 20;
				prev = next;
				cur = fgetc(fp);
				spot++;
			}

			//':' by itself or followed by anything else is invalid
			else{
				printf("ERROR: Invalid symbol encountered\n");
				error = 1;
				break;
			}
			next = fgetc(fp);
			break;

			//ignore spaces, newlines, carrage returns, horizontal and vertical tabs
			case ' ':
			case '\n':
			case '\r':
			case '\t':
			case '\v':
			prev = cur;
			cur = next;
			next = fgetc(fp);
			break;

			//Ident_sym, Number_sym, reserved keyword, or invalid
			default:
			
			//we are looking at an alphabetic character
			//therefore this is an Ident_sym or a reserved keyword
			if(isalpha(cur)){
				
				//max ident size is 11 chars plus space for the null terminatior
				while(numChars < 12){
				
				//if we have no current chars in out tmp we need to get out next char
				if (numChars != 0)
					next = fgetc(fp);

					//we are done looking at our string of chars
					//decide weather we have a reserved keyword or an Ident_sym
					if(!isalnum(cur)){
						
						//Odd_sym
						if(!strcmp(tmp, "odd")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 8;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Begin_sym
						else if(!strcmp(tmp, "begin")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 21;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//End_sym
						else if(!strcmp(tmp, "end")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 22;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//If_sym
						else if(!strcmp(tmp, "if")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 23;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Then_sym
						else if(!strcmp(tmp, "then")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 24;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//While_sym
						else if(!strcmp(tmp, "while")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 25;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Do_sym
						else if(!strcmp(tmp, "do")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 26;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Call_sym
						else if(!strcmp(tmp, "call")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 27;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Const_sym
						else if(!strcmp(tmp, "const")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 28;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Var_sym
						else if(!strcmp(tmp, "var")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 29;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Procedure_sym
						else if(!strcmp(tmp, "procedure")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 30;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Write_sym
						else if(!strcmp(tmp, "write")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 31;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Read_sym
						else if(!strcmp(tmp, "read")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 32;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Else_sym
						else if(!strcmp(tmp, "else")){
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 33;
						spot++;
						strcpy(tmp, "");
						numChars = 0;
						break;
						}

						//Ident_sym
						else{
						strcpy(lexemes[spot], tmp);
						tokentypes[spot] = 2;
						strcpy(tmp, "");
						spot++;
						numChars = 0;
						break;
						}
					}

					//we still have more to look at, add out
					//current char to the end of our tmp array and keep going
					else{
						
						Append(tmp, cur);

						numChars++;
						prev = cur;
						cur = next;
					}
				}

				//if we have more than 11 chars and the null terminator our variable
				//is too long
				if(numChars >= 12){
					printf("ERROR: Variable too long\n");
					error = 1;
					break;
					}

			}

			//we are looking at a digit
			//we have a Number_sym
			else if(isdigit(cur)){

				//max number size is 5 chars plus space for the null terminatior
				while(numChars < 6){

				//if we have no current chars in out tmp we need to get out next char
					if (numChars != 0)
						next = fgetc(fp);

					//we are done looking at our digits
					if(!isdigit(cur)){

						//if have a number followed by a letter, we have an invalid
						//variable, variables must start with a letter
						if(isalpha(cur)){
							printf("ERROR: Variable does not start with letter\n");
							error = 1;
							break;
						}

						//we have a valid number, tokenize it
						else{
							strcpy(lexemes[spot], tmp);
							tokentypes[spot] = 3;
							strcpy(tmp, "");
							spot++;
							numChars = 0;
							break;
						}
					}

					//we still have more to look at, add out
					//current char to the end of our tmp array and keep going
					else{
						Append(tmp, cur);
						numChars++;
						prev = cur;
						cur = next;
					}

					//if we have more than 5 chars and the null terminator our variable
					//is too long
					if(numChars >= 6){
					printf("ERROR: Number too long\n");
					error = 1;
					break;
					}
				}
			}

			//we have encounteres something that is invalid in this language
			else{
				printf("ERROR: Invalid symbol encountered\n");
				error = 1;
				break;
			}		
		}
	}

	fclose(fp);

	fp = fopen(out1, "w");

	//print our headers as well as the list of lexemes and token types
	fprintf(fp, "%-15s%s\n", "lexeme", "token type");
	while(i < spot){
		fprintf(fp, "%-15s%d\n", lexemes[i], tokentypes[i]);
		i++;
	}

	fclose(fp);

	fp = fopen(out2, "w");

	i = 0;

	//print out our list of token types
	while(i < spot){
		fprintf(fp, "%d ", tokentypes[i]);

		//if we have an Ident_sym or a Number_sym, we need to also print the lexeme itself
		if(tokentypes[i] == 2 || tokentypes[i] == 3){
			fprintf(fp, "%s ", lexemes[i]);
		}
		i++;
	}

	fclose(fp);
}





// int main(void){

// 	Initialize("input.txt");
// 	ReadClean("input.txt", "cleaninput.txt");
// 	Tokenize("cleaninput.txt", "lexemetable.txt", "lexemelist.txt");

// 	return 0;
// }
