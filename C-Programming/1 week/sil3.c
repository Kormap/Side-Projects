#include <stdio.h>

int main()
{
 int n;
 int i,j,k;

 printf("input number:");
 scanf("%d",&n);

 for(i=0;i<n;i++)	// j+k=n	//
 {
	if(i%2==0)
	{
		if(n%2==0){
			for(j=0;j<n/2;j++)
			{
				printf("* ");
			}
			printf("\n");
		}
		else
		{
			for(j=0;j<n/2+1;j++)
			{
				printf("* ");
			}
			printf("\n");
		}
	}
	
	else
	{
		for(k=0;k<n-j;k++)
		{
			printf(" *");
		}
		printf("\n");
	}
 }

}