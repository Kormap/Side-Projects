#include <stdio.h>

int main()
{
 int n;
 int i,j,k;

 printf("input number:");
 scanf("%d",&n);

 for(i=0;i<n;i++)
 {
        for(j=0;j<=i;j++)
        {
                printf("*");
        }
        printf("\n");
 }

 for(i=1;i<n;i++)
 {
	for(j=0;j<i;j++)
	{
	 printf(" ");
	}
	for(k=n-i;k>0;k--)
	{
	 printf("*");
	}
	printf("\n");
 }
}