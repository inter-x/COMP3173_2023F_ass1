/*
-	You need to design and implement a DFA to complete this task.
-	To implement the DFA, you must use a transition table.
-	You must define the transition table in "lexer.h" in a proper way (for example, as a 2-dimensional constant array).
-	It reads and cuts the source program into lexemes.
-	It returns the first token which is found every time when "next_token" is called.
-	It ignores spaces, indentations, line breaks, and comments.
-	If the token is an identifier, insert the token into the symbol table. Each token has an attribute to record its memory location in the symbol table.
-	If the token is an integer literal, the token has two attributes: type, for its data type; and value, for its value.
-	If the token is none of the above, it does not have an attribute.
-	If there is any lexical error, returns an error flag to the main function.
*/
#include <stdlib.h>
#include<stdio.h>
#include "string.h"
#include "symbol_table.h"

/*
状态机
初始->字母
初始->0
初始->非零数字


去空格后存每一个token

id
字母->字母
字母->空

nat
第一个为0，后面只能下一个token

否则
非零数字->任何数字
非零数字->空
0->任何数字
任何数字->空
任何数字->括号
任何数字->等号

（自然数，第一个）

-后面只能>
[]
()
:
;
?
+
<

*/

int isDigit(char ch){
    if(ch<='9'&&ch>='0')    return 1;
    return 0;
}

int isLetter(char ch){
    if(ch>='a'&&ch<='z')    return 1;
    else if(ch>='A'&&ch<='Z')    return 1;
    return 0;
}

//自然数
int isNatural(char *s){
    int len = strlen(s);
    if(s[0]=='0'){
        if(len==1){
            return 1;
        }
        else{
            return 0;
        }
    }
    int i;
    for(i=0;i<len;i++){
        if(isDigit(s[i])==0){
            return 0;
        }
    }
    return 1;
}

//bool型
int isBoolean(char *s){
    if(sizeof(s)==1){
        if(s[0]=='F'||s[0]=='T'){
            return 1;
        }
    }
    return 0;
}


//字符串
int isId(char *s){
    int len = strlen(s);
    int i;
    for(i=0;i<len;i++){
        if(isLetter(s[i])==0){
            return 0;
        }
    }
    return 1;
}

int isBool(char *s){
    if(strcmp(s,"bool")==1){
        return 1;
    }
    return 0;
}

int isNat(char *s){
    if(strcmp(s,"nat")) return 1;
    return 0;
}

int isFun(char *s){
    if(strcmp(s,"fun")) return 1;
    return 0;
}

int isBoundary(char ch){
	if(ch=='('||ch==')'){
		return 1;
	}
	return 0;
}

int isQue(char ch){
	if(ch=='?')
		return 1;
	return 0;
}

int isColon(char ch){
	if(ch==':')
		return 1;
	return 0;
}

int isSemi(char ch){
	if(ch==';')
		return 1;
	return 0;
}

int isAdd(char ch){
	if(ch=='+')
		return 1;
	return 0;
}

int isAnd(char ch){
	if(ch=='&')
		return 1;
	return 0;
}

int isOP(char ch){
	if(ch=='<')	return 1;
	return 0;
}

int isAssign(char *s){
	if(strcmp(s,"->")==1){
		return 1;
	}
	return 0;
}


My_token next_token(char *s,int pos_n,int s_len){
    My_token ans;
    ans.is_L = 0;
	ans.str = pos_n;
    //结束 -1
    if(s_len==pos_n){
    	printf("%d	%d\n",s_len,pos_n);
        ans.is_L = -1;
        ans.end = pos_n;
        ans.len = 0;
        return ans;
    }
    int pos = pos_n;
    int l ,r = pos_n;
    char ch = s[pos];
    //去掉空格 0
    while(ch==' '||ch=='	'||ch=='\n'||ch=='\0'){
        while(ch=='\0'){
        	pos++;
            ans.len = pos-pos_n;
            ans.is_L = -3;
            return ans;
        }
        pos++;
        ch = s[pos];
    }
	l = pos;
	r = pos;
	ans.str = pos_n;
    //返回注释 0
    if(s[l]=='['){
        ch = s[l];
        while(s[r]!=']'){
            if(ch!='\0'){
                r++;
            }
			else{
                ans.is_L=0;
                ans.len = r-l;
                strncpy(ans.id_name,s+l,r-l);
                return ans;
            }
        }
        
        ans.is_L = 0;
        ans.len = r-pos_n;
        ans.str = pos_n;
        ans.end = r;
        
        char s_tmp[100];
        strncpy(s_tmp,s+l,r-l+1);
        //printf("zhushi%s",s_tmp);
        //printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }

    //标识 1
    if(s[r]=='('){
    	printf("#");
        ans.is_L = 1;
        ans.s = "(";
        ans.id_name = "(";
        ans.len = 1;
        ans.str = pos_n;
        ans.end = r;
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }
    if(s[r]==')'){
    	printf("#");
        ans.is_L = 1;
        ans.s = ")";
		ans.id_name = ")";
        ans.len = 1;
        ans.str = pos_n;
        ans.end = r;
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }
    if(s[r]=='+'){
    	printf("#");
        ans.is_L = 1;
        ans.s = "+";
        ans.id_name = "+";
        ans.len = 1;
        ans.str = pos_n;
        ans.end = r;
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }
    if(s[r]=='&'){
    	
        ans.is_L = 1;
        ans.s = "&";
        ans.id_name = "&";
        ans.len = 1;
        ans.str = pos_n;
        ans.end = r;
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }
    if(s[r]=='?'){
        ans.is_L = 1;
        ans.s = "?";
        ans.id_name = "?";
        ans.len = 1;
        ans.str = pos_n;
        ans.end = r;
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }
    if(s[r]==':'){
        ans.is_L = 1;
        ans.s = ":";
        ans.id_name = ":";
        ans.len = 1;
        ans.str = pos_n;
        ans.end = r;
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }
    if(s[r]==';'){
        ans.is_L = 1;
        ans.s = ";";
        ans.id_name = ";";
        ans.len = 1;
        ans.str = pos_n;
        ans.end = r;
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }
    if(s[r]=='<'){
        ans.is_L = 1;
        ans.s = "<";
        ans.id_name = "<";
        ans.len = 1;
        ans.str = pos_n;
        ans.end = r;
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }
    if(s[r]=='='){
        ans.is_L = 1;
        ans.s = "=";
        ans.id_name = "=";
        ans.len = 1;
        ans.str = pos_n;
        ans.end = r;
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }
    if(s[l]=='-'){
    	printf("--");
        if(s[l+1]=='>'){
            ans.is_L = 1;
            ans.s = "->";
            ans.id_name = "->";
            ans.len =2;
            ans.str = pos_n;
    		ans.end = l+1;
    		printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
    		return ans;
        }
        else{
            ans.is_L = -2;
            ans.s = "-";
            ans.id_name = "-";
            ans.len = 1;
            ans.str = l;
			return ans;
        }
    }
    
    //数字2
    if(isDigit(s[l])==1){
    	int i;
        for(i=l;isDigit(s[i])==1;i++){
            r = i;
        }
        char s_tmp[20];
        strncpy(s_tmp,s+l,r-l+1);
        printf("%s",s_tmp);
        ans.is_L = 2;
        ans.len = r-l+1;
        ans.str = pos_n;
        ans.end = r;
        ans.s = s_tmp;
        ans.id_name = "literal(natural)";
        printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
        return ans;
    }

    //字母开头,关键字为3， 标识符为4
    if(isLetter(s[l])==1){
        int i;
        char s_tmp[20];
        for(i=l;isLetter(s[i])==1;i++){
            r = i; 
        }
        int j = r;
        for(i = r+1;isDigit(s[i])==1;i++){
        	j = i;
		}
        
		
        ans.str = pos_n;
        //只有字母
        if(j==r){
        	printf("l%d r%d j%d",l,r,j);  	
    		ans.len = r-l+1;
    		ans.end = j;
    		ans.str = pos_n;
        	strncpy(s_tmp,s+l,j-l+1);
			ans.s = s_tmp;
            if(l==r){
                ans.is_L = 4;    
                ans.len = 1;         
                if(s[l]=='F'||s[l]=='T'){
                    ans.is_L = 4;
                    ans.id_name = "literal(Boolean)";
                }
                else{
                    ans.is_L = 4;
                    char tmp[] = "identifier";
                    ans.id_name = tmp;
                }
                printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
                return ans;
            }
            else{
            	
                if(strcmp(s_tmp,"fun")==0){
                    ans.is_L = 3;
                    ans.id_name = "fun";
                    ans.s = "fun";
                }
                else if(strcmp(s_tmp,"bool")==0){
                    ans.is_L = 3;
                    ans.id_name = "bool";
                    ans.s = "bool";
                }
                else if(strcmp(s_tmp,"nat")==0){
                    ans.is_L = 3;
                    ans.id_name = "nat";
                    ans.s = "nat";
                }
                else{
                    ans.is_L = 4;
                    ans.id_name = "identifier";
                }
                printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
                return ans;
            }

        }

        //前字母后都有
        else{
            for(i=r+1;isLetter(s[i])+isDigit(s[i])>0;i++){
                j = i;
            }
            ans.str = pos_n;
            ans.end = j;
            ans.len = j-l+1;
			char s_tmp[20];
            strncpy(s_tmp,s+l,j-l+1);
            //printf("$i:%d	j:%d$\n",l,j);
            ans.len = j-l+1;
            ans.str = pos_n;
            ans.end = j;
            ans.s = s_tmp;
            ans.id_name = "identifier";
            ans.is_L = 4;
			printf("lexeme:%s	token:%s\n",ans.s,ans.id_name);
            return ans;
        }

    }
    //错误-2
    ans.is_L = -4;
    ans.len = 1;
    return ans;
}


