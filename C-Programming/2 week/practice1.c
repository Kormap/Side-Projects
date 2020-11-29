#include <stdio.h>

int main(){
 char letter[20];
 char ch;
 int j=0,i=0;

 printf("enter letter:");

 while(ch!='\n'){
	ch=getchar();

	if(ch>64 && ch<91){
		letter[j]=ch;
	}
	else{
		letter[j]=ch-32;
	}

	j++;
 }

 for(i=0;i<j-1;i++){
	putchar(letter[i]);
 }

 printf("\n");

 return 0;
}