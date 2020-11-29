#include <stdio.h>

int main(){
 int arr[5][5];
 int swap[5][5];
 int i=0,j=0;

 for(i=0;i<5;i++){
  for(j=0;j<5;j++){
	printf("[%d,%d]:",i,j);
	scanf("%d", &arr[i][j]);
  }
 }

 printf("=======original=======\n");
 for(i=0;i<5;i++){
  for(j=0;j<5;j++){
        printf("%d\t",arr[i][j]);
  }
  printf("\n");
 }

 for(i=0;i<5;i++){
  for(j=0;j<5;j++){
	swap[i][j]=arr[i][j];
  }
 }

 for(i=0;i<5;i++){
  for(j=0;j<5;j++){
	arr[j][i]=swap[i][j];
  }
 }

 printf("=======transpose======\n");
 for(i=0;i<5;i++){
  for(j=0;j<5;j++){
	printf("%d\t",arr[i][j]);
  }
  printf("\n");
 }

 return 0;
}