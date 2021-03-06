//Sam Wildman
//S2878126
//COP 3402 Spring 2015
//Homework 1 - P-Machine

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Compiler.h"



Instruction code [5000];
int stack[2000] = {0};

Instruction ir;
int pc = 0;
int pcprev = 0;
int bp = 0;
int sp = -1;

int ars = 0;
int arBreak[2000] = {0};	

int halt = 0;






//fetches the next instruction stored at pc and puts it in the ir, updates pc
void Fetch(){

	ir = code[pc];
	pcprev = pc;
	pc++;
}





//find a variable in a different Activation Record some L levels down:
int Base(int l, int base){
	 
	int b1; //find base L levels down
	b1 = base;
	while (l > 0){
		b1 = stack[b1 + 1];
	  	l--; 
	}
	return b1; 
}
	




//executes the current instruction located in the ir	
void Execute(){
	
	//switch to determine instruction based on opcode
	switch(ir.op){
		
		//LIT - Push constant value (literal) M onto the stack.
		case 1:
			sp++;
			stack[sp] = ir.m;
			break;
		
		//OPR - Depending on M, it could have the following meanings:
		case 2:

		//in the case of OPR, we need to look further at the M value to determine instruction
			switch(ir.m){

				//RET - Returns from current procedure
				case 0:
					sp = bp - 1;

					if(sp == -1){
						halt = 1;
					}

					pc = stack[sp + 4];
					bp = stack[sp + 3];

					arBreak[ars--] = 0;
					break;


				//NEG
				case 1:
					stack[sp] = -stack[sp];
					break;

				//ADD	
				case 2:
					sp--;
					stack[sp] = stack[sp] + stack[sp + 1];
					break;

				//SUB	
				case 3:
					sp--;
					stack[sp] = stack[sp] - stack[sp + 1];
					break;

				//MUL	
				case 4:
					sp--;
					stack[sp] = stack[sp] * stack[sp + 1];
					break;

				//DIV	
				case 5:
					sp--;
					stack[sp] = stack[sp] / stack[sp + 1];
					break;

				//ODD
				case 6:
					stack[sp] = stack[sp] % 2;
					break;

				//MOD	
				case 7:
					sp--;
					stack[sp] = stack[sp] % stack[sp + 1];
					break;
				
				//EQL - For 8 ≤ 𝑀 ≤ 13, the value set is 1 if the comparison is true, 0 otherwise.
				case 8:
					sp--;
					stack[sp] = ((stack[sp] == stack[sp + 1]) ? 1 : 0);
					break;

				//NEQ
				case 9:
					sp--;
					stack[sp] = ((stack[sp] != stack[sp + 1]) ? 1 : 0);
					break;

				//LSS
				case 10:
					sp--;
					stack[sp] = ((stack[sp] < stack[sp + 1]) ? 1 : 0);
					break;

				//LEQ
				case 11:
					sp--;
					stack[sp] = ((stack[sp] <= stack[sp + 1]) ? 1 : 0);
					break;	

				//GTR
				case 12:
					sp--;
					stack[sp] = ((stack[sp] > stack[sp + 1]) ? 1 : 0);
					break;

				//GEQ
				case 13:
					sp--;
					stack[sp] = ((stack[sp] >= stack[sp + 1]) ? 1 : 0);
					break;
			}
			break;
		
		//LOD - Load value from the Stack location at offset M from L lexicographical levels up. 
		//      Then push this loaded value to the top of the Stack.
		case 3:
			sp++;

			int l = ir.l, b = bp;
			while(l>0){
				b = stack[b + 1];
				l--;
			}

			stack[sp] = stack[Base(l, b) + ir.m];
			break;

		//STO - Pop of the value at the top of the Stack and store it at the Stack location 
		//		at offset M from L lexicographical levels up.	
		case 4:
			l = ir.l;
			b = bp;
			while(l>0){
				b = stack[b + 1];
				l--;
			}

			stack[Base(l, b) + ir.m] = stack[sp];
			sp--;
			break;

		//CAL - Call procedure at code index M.	
		case 5:
			stack[sp + 2] = Base(ir.l, bp);
			stack[sp + 3] = bp;
			stack[sp + 4] = pc;
			bp = sp + 1;
			pc = ir.m;
			arBreak[ars++] = bp;
			break;

		//INC - Allocate M locals at the top of the Stack. The first
		//		three are the Static Link (SL), Dyanmic Link (DL), and the Return Address (RA).
		case 6:
			sp = sp + ir.m;
			break;
		
		//JMP - Jump to instruction M
			case 7:
			pc = ir.m;
			break;

		//JPC - Pop off the value from the top of the Stack. Jump to instruction M if that value is 0.
		case 8:
			if(stack[sp] == 0){
				pc = ir.m;
			}

			sp--;
			break;

		//OUT - Pop off the value from the top of the Stack. Print out that value.
		case 9:
			printf("%d\n", stack[sp]);
			sp--;
			break;

		//IN - Read in a value and push it to the top of the Stack.
		case 10:
			sp++;
			printf("Please enter a value: ");
			scanf("%d", &stack[sp]);
			break;
		}
}





//function to return the string that represents our passed instruction for printing purposes
char *GetOp(Instruction x){
	
	
	switch(x.op){
		
		case 1:
		return "LIT";
		
		//OPR	
		case 2:
		switch(x.m){

			case 0:
			return "OPR";
			case 1:
			return "NEG";		
			case 2:
			return "ADD";	
			case 3:
			return "SUB";
			case 4:
			return "MUL";
			case 5:
			return "DIV";
			case 6:
			return "ODD";
			case 7:
			return "MOD";
			case 8:
			return "EQL";
			case 9:
			return "NEQ";
			case 10:
			return "LSS";
			case 11:
			return "LEQ";	
			case 12:
			return "GTR";
			case 13:
			return "GEQ";
		}
		
		case 3:
		return "LOD";
		case 4:
		return "STO";
		case 5:
		return "CAL";
		case 6:
		return "INC";
		case 7:
		return "JMP";
		case 8:
		return "JPC";
		case 9:
		return "OUT";
		case 10:
		return "IN";
		default: return "";
	}
}





//passed as parameters are our input and output files,
//read data from the input file and write our instructions to the output file
void RWInput(char in[], char out[]){
	
	int i = 0, x = 0;
	
	fp = fopen(in, "r");
	
	if(fp == NULL){
		printf("ERROR OPENING FILE %s!!\n", in);
	}
	
	//read in our initial instruction
	fscanf(fp, "%d%d%d", &code[i].op, &code[i].l, &code[i].m);

	//read in all additional instructions
	while(!feof(fp)){
		i++;
		fscanf(fp, "%d%d%d", &code[i].op, &code[i].l, &code[i].m);
	}
	
	fclose(fp);
	
	
	fp = fopen(out, "w");
	
	if(fp == NULL){
		printf("ERROR OPENING FILE %s!!\n", out);
	}
	
	//format and output line headers
	fprintf(fp, "%-5s  %-5s%-5s%-5s\n", "Line", "OP", "L", "M");
	
	//print out our correctly formatted instructions
	for(x = 0; x < i; x++){
		char op[4];
		strcpy(op, GetOp(code[x]));
		fprintf(fp, "%4d  %-5s %-5d%-5d\n", x, op, code[x].l, code[x].m);
	}
	fprintf(fp, "\n\n");
	fprintf(fp,"                    %-5s%-5s%-5s%s\n", "pc", "bp", "sp", "stack");
}





//write results to output
//status indicates if we are writing out the pointers, stack, or the instruction
void WriteToOutput(int status){
	
	int i=0, numAr = 0;
	char op[4];
	strcpy(op, GetOp(ir));
	
	//determine what we need to write
	switch(status){
		
		//write the instruction
		case 1: fprintf(fp,"%2d   %-5s%-5d%-5d", pcprev, op, ir.l, ir.m);
		break;

		//write the pointers
		case 2: fprintf(fp,"%-5d%-5d%-5d", pc, bp, sp);
		break;
		
		//write our formatted stack
		case 3: for(i = 0; i <= sp; i++){

			//dertermine if we need to print an activation record bar
			if(numAr < ars && i == arBreak[numAr] && i != 0){
				numAr++;
				fprintf(fp, "| ");
			}

			//print our stack content
			fprintf(fp, "%d ", stack[i]);
		}
		fprintf(fp,"\n");
		break;
	}
}





//run our program
void Run(){	
	if(fp == NULL){
		printf("ERROR OPENING FILE %s!!\n", "stacktrace.txt");
	}
	
	//print our initial values
	fprintf(fp,"Initial Values      %-5d%-5d%-5d\n", 0,0,-1);
	
	//run each instruction until we get to the halt condition
	while(!halt){
		
		//get instruction
		Fetch();

		//write the instruction
		WriteToOutput(1);

		//ecevute the instruction
		Execute();

		//write the pointers
		WriteToOutput(2);

		//write the stack
		WriteToOutput(3);
	}
	
	fclose(fp);
}






// int main(void){
	
// 	RWInput("mcode.txt", "stacktrace.txt");
// 	printf("Output:\n");
// 	Run();
	
	
// 	return 0;
// }