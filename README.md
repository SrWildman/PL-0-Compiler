# PL-0-Compiler
Created for COP 3402 (Systems Software) - Spring 2015

Takes in code in the PL/0 language in a file titled "input.txt" and produces output files representing each step in the compilation process including a list and table of the lexemes, the cleaned input, and the final stacktrace of execution. The result of execution is printed to the console. To compile, follow the instructions below.

Using Makefile

1) Navigate to the directory containing the files (all files must be in the same directory) in the terminal
2) Enter the command "make" (no quotes are necessary)
3) Enter the command “./Compile” (again, no quotes). 
	note: the following flags are able to be appended after “./Compile” in any order 	as long as there is whitespace on either side of the flag

	-l: Print the lexeme list to the console
	-a: Print the generated assembly code to the console
	-v: Print the virtual machine execution trace to the console
