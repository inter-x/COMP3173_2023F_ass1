/*
-	It is the main entry of the entire project (all phases). 
-	It opens the source program.
-	The source program is passed to the main function as an argument.
-	It makes calls to the function "next_token" defined in "lexer.h" and "lexer.c".
-	It maintains a symbol table defined in "symbol_table.h" and "symbol_table.c" to store all the identifiers.
-	If the function "next_token" returns a token, print the token and its attribute(s) on the screen for verification purpose.
-	If "next_token" returns an error flag, report the error and its location.
-	After the entire process is finished, print out the symbol table.
*/
#include<stdio.h>
#include "lexer.h"
#include "string.h"

#define MAXLINE 100000
#define BUFLEN  1024

int main(){
	FILE *file;
	char buf[BUFLEN];
	int len=0,i=0;
	char *array[MAXLINE];
	file=fopen("test3.txt","r");
	while(fgets(buf,BUFLEN,file))//¶ÁÈ¡TXTÖÐ×Ö·û
	{
		len=strlen(buf);
		array[i]=(char*)malloc(len+1);
		if(!array[i])break;
		strcpy(array[i++],buf);
	}
	
	
	len = sizeof(array);
	int pos = 0;
	i =0;
	//My_token ans;
	int k = 1;
	printf("len%d\n",len);
	while(i<len){
		printf("__%d__%d\n",k,i);
		My_token tmp = next_token(array[0],i,len);
		
		if(tmp.is_L==-3){
			printf("-3");
			//break;			
		}
		else if(tmp.is_L==-2){
			printf("-2");
			printf("error ' %s ' is not an operator.\n",tmp.s);
			break;
		}
		else if(tmp.is_L==0){
			printf("0\n");
		}
		else{	
			ptinrf("Other");	
			printf("start:%d	end:%d	len:%d\n",tmp.str,tmp.end,tmp.len);
		}
		char tokens[20];
		int l,r;
		l = tmp.end-len+1;
		r = tmp.end;

		i = tmp.end+1;
		
		k++;
	}
	printf("%s",array[i+2]);
	return 0;
}
