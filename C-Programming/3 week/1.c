#include <stdio.h>

int func(int x,int y,int n){
 int i=0;
 for(i=x;i<y;i++){

        if(i%n!=0){
                printf("%d\n", i);
        }
 }
}

int main(){
 int a=0,b=0,n=0;

 printf("A :");
 scanf("%d", &a);

 printf("B :");
 scanf("%d", &b);

 printf("N :");
 scanf("%d", &n);

 func(a,b,n);

 return 0;
}