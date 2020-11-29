#include <stdio.h>

int main(){
 char A[10]={'D','E','T','A','G','F','B','C','M'};
 char k;
 int i=0,j=0;;

 printf("before:");
 for(i=0;i<10;i++){
	printf("%c ", A[i]);
 }
 printf("\n");

 for(j=8;j>=0;j--){
  for(i=8;i>=0;i--){
   if(A[i]>A[i+1]){
	k=A[i];
	A[i]=A[i+1];
	A[i+1]=k;
   }
  }
 }

 printf("after:");
 for(i=0;i<10;i++){
	printf("%c ", A[i]);
 }
 printf("\n");

 return 0;
}