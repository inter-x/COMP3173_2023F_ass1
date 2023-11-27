/*
-	It should be implemented as a data structure (AVL tree is recommended to search and insert symbols efficiently or you can use any data structure you want. Efficiency is not required here.);
-	Each identifier has its variable name and its type. (This language has two three types of identifiers, integers natural numbers, Boolean, and functions.)
-	Currently, the type of identifiers cannot be decided (it is done by semantic analysis). So, the corresponding type in the symbol table is just NULL.
-	The symbol table also needs a function to print out its content.
*/

/*
Keywords: 0.bool	1.nat	2.func 

Control flow: ?		:

Delimiter: ()	[]	; 

Spacing

Identifiers

Literals

Operators

Precedence

*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ctype.h"
//标识符

//存储的结构体
typedef struct
{
	int is_L;
	int keywords;
	//key 1
	int type_name;
	char *s;
	char *id_name;
	int str;
	int end;
	int len;
}My_token;

