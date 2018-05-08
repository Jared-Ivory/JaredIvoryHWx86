#include <stdio.h>
#include "cse222macV4.h"
/*
 * declare the prototype of your assembler program or procedures
 */
// example: short asmreturn();  

//int ASMFormula(int y, int z, int t);
int ASMstrlen(char *str1);
int ASMArySum(int *p, int n);
char str1[] = "The red fox jump over the fence";
char str2[] = "The chicken and duck hide under the rose bushes";
int arynum[] = {40,-70,90};
int arylen = 3;
short tnum[] = {89,9,76};


main(int argc, char *argv[] )
{
	/* 
	 * variable declaration here
	 */

//	int result;
	int y = 8;
	int z = 20;
	int t = 68;


   /*
	* First call INITCST
	* replace Your Name Here with your name
	*/

	INITCST("x86 practice","student name here");

	/*
	 * call your asm procedure here
	 * you can use any variable name you want and make sure the return type
	 * is correct.
	 */
	
	printf(" for str1 <%s>\n",str1);
	printf("          from ASMstrLen : %d  C strlen: %d\n", ASMstrlen(str1), strlen(str1));
	printf("\n------------------------------------------------------------\n\n");
	printf(" for str2 <%s>\n",str2);
	printf("          from ASMstrLen : %d  C strlen: %d\n", ASMstrlen(str2), strlen(str2));
	printf("\n------------------------------------------------------------\n\n");

	printf(" find the sum of array  : %d\n",ASMArySum(&arynum[0], arylen) );
	printf("\n------------------------------------------------------------\n");
	
	printf("\n\nhit any key  .......  quit");
	getchar();

}


int ASMstrlen(char *str1)
{
	int asmlen = -99;

	_asm{
		// use ecx as count
		//     esi - base address of string
		mov esi, str1   // get the base address string
		mov ecx, 0      // use ecx as count
		
		strlen_loop:
		mov eax, [esi + ecx]	//moves the char into eax
		cmp al, 0x00			//checks to see a1 == NULL
		je strlen_loop_end		//jumps to end if it is..

		add ecx, 1				//increment counter++
		jmp strlen_loop			// jumps back to beginning

		strlen_loop_end:
		
		mov asmlen,ecx  // return the value of count
	}
	
	return(asmlen);
}

int ASMArySum(int *p, int n)
{
	int sum = -99999;
	int i	= 4 * n;
	_asm {
		mov esi, p		// get the base address
		mov ecx, 0		// counter
		mov eax, 0
		//--------------------
		arySum_loop:
			cmp[esi + ecx], 0		//checks for negatives
			jl isNegative
			
			cmp ecx, i				//ecx holds counter for length of array
			je SumIsDone

			add eax, [esi + ecx]	//adds the integers that are unsigned positives
			
			add ecx, 4				//byte array offset of 4 bits

			
			jmp arySum_loop			//jumps back to beginning of arySum_Loop
				isNegative:
				mov edx, [esi + ecx]	//move array[i] to edx
				add eax, edx			//adds edx to eax
	
				cmp ecx, i				//checks for completion, array has hit the nth number of spots
				je SumIsDone
				add ecx, 4
				jmp arySum_Loop		//jumps back to beginning of arySum_Loop
		//---------------------
SumIsDone:
		mov	sum,eax   // return the sum accumalated in eax
	}

	return(sum);
}

