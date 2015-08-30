Compile: Driver.o TinyParser.o LexicalAnalyzer.o P-Machine.o Compiler.h
	gcc -o Compile Driver.o TinyParser.o LexicalAnalyzer.o P-Machine.o

Driver.o: Driver.c Compiler.h
	gcc -c Driver.c

TinyParser.o: TinyParser.c Compiler.h
	gcc -c TinyParser.c

LexicalAnalyzer.o: LexicalAnalyzer.c Compiler.h
	gcc -c LexicalAnalyzer.c

P-Machine.o: P-Machine.c Compiler.h
	gcc -c P-Machine.c 



