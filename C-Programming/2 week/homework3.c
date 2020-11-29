#include <stdio.h>

int main(){
 int str[25]={};
 int arr[5][5]; 
 int i=0,j=0;
 int k=0;

 for(k=0;k<25;k++){
	printf("input %d`s number:",k+1);
	scanf("%d", &str[k]);
 }

 for(k=0;k<25;k++){
	if(str[k]%2==0){
		arr[i][j]=str[k];
			if(j<4){
			 j++;
			}
			else{
			 i++;
			 j=0;
			}
	}
 }

 i=4;
 j=4; 
 for(k=0;k<25;k++){
	if(str[k]%2==1){

		arr[i][j]=str[k];
			if(j>0){
			 j--;
			}
			else{
			 i--;
			 j=4;
			}
 	}	
 }

 printf("======result======\n");
 for(i=0;i<5;i++){
  for(j=0;j<5;j++){
	printf("%d ", arr[i][j]);
  }
  printf("\n");
 }

 return 0;
}