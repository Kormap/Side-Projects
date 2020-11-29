#include <stdio.h>

int stone_compare(int n){
 int x=0, y=0;
 int gap=0;
 int black=1, white=2;

 if(n%2==1){
        x=(n+1)/2;      // x is white`s number
        white=x*x;
        y=x-1;  // y is black`s number
        black=y*y+y;
        gap=white-black;
        printf("there are  %d more white stones than black.\n", gap);
 }

 else{
        x=n/2;
        white=x*x;
        y=x;
        black=y*y+y;
        gap=black-white;
        printf("there are %d more black stones than white\n", gap);
 }
}

int main(){
 int n=0;

 printf("N : ");
 scanf("%d", &n);

 stone_compare(n);

 return 0;
}