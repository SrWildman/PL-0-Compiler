//Sam Wildman
//S2878126
//COP 3402 Spring 2015
//Homework 3 - Compiler Header

/* This header includes all definitions needed for the
entire compiler and all of its components. It is imported
into each file as it contains necissary definitions for each*/


#ifndef COMPILER_H_  
#define FOO_H_

FILE* fp;



//P-Machine
typedef struct Instruction{
	int op;
	int l;
	int m;
}Instruction;

void Fetch();
int Base(int l, int base);
void Execute();
char *GetOp(Instruction x);
void RWInput(char in[], char out[]);
void WriteToOutput(int status);
void Run();





//Lexical Analyzer
void Initialize(char in[]);
void Append(char* s, char c);
void ReadClean(char in[], char out[]);
void Tokenize(char in[], char out1[], char out2[]);





//Parser
typedef struct mcode{
	int op;
	int l;
	int m;
}mcode;

typedef struct symbol {
    char* id;
    int type; //0 - const, 1 - variable, 2 - procedure
    int value;
    int position;

    struct symbol *next;
} symbol;


typedef struct symbolTable{
    int size;      
    symbol **symbols;
} symbolTable;


symbolTable* CreateTable(int size);
unsigned int Hash(symbolTable* hashtable, char* str);
symbol* Lookup(symbolTable* hashtable, char* str);
int Add(symbolTable* hashtable, char* id, int type, int value, int position);
void Initialize2(char in[], char out[]);
void Gen(int op, int l, int m);
void printOut();
void Get();
void Error(int code);
void Expression();
void Factor();
void Term();
void Condition();
void Statement();
int PBlock();
void PList();
char* Block();




#endif // COMPILER_H_