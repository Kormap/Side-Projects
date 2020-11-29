#include <stdio.h>
#include <stdlib.h>

int main()
{
 int n, size;
 char** dice;
 int i=0,j=0;
 int x=0,y=0;

 printf("input dice number:");
 scanf("%d",&n);

 switch((int)(n))
 {
	case 1:
		printf("input odd number:(n>5):");	
		scanf("%d",&size);
		break;
	case 2:
		printf("input odd number:(n>7)");
		scanf("%d",&size);
		break;
	case 3:
		printf("input odd number:(n>7)");
		scanf("%d",&size);
		break;
	case 4:
		printf("input odd number:(n>7)");
		scanf("%d",&size);
		break;
	case 5:
		printf("input odd number:(n>9)");
		scanf("%d",&size);
		break;
	case 6:
		printf("input odd number:(n>9)");
		scanf("%d",&size);
		break;
 }

 dice=(char**)malloc(sizeof(int*)*size);
 for(i=0;i<size;i++)
 {
	dice[i]=(char*)malloc(sizeof(int)*size);
 }

 for(i=0;i<size;i++)     //  x direction //
 {
  dice[i][0]='бс';
 }

 for(j=1;j<size;j++)     // y direction //
 {
  dice[0][j]='бс';
 }

 for(i=1;i<size;i++)
 {
  dice[i][size-1]='бс';
 }

 for(j=1;j<size;j++)
 {
  dice[size-1][j]='бс';
 }

 switch((int)(n))
 {
	case 1:
		if(size<5)
			printf("FAIL\n");
		else
		{
                	dice[(size-1)/2][(size-1)/2]='бс';
		 for(i=0;i<size;i++)
		 {
		        for(j=0;j<size;j++)
	 	        {
		         printf("%c\t",dice[i][j]);
		        }

		        printf("\n");
		 }
		}
		break;		

	case 2:
		if(size<7)
			printf("FAIL\n");
		else
		{	
	                dice[(size-1)/2-1][(size-1)/2-1]='бс';
        	        dice[(size-1)/2+1][(size-1)/2+1]='бс';
		 for(i=0;i<size;i++)
		 {
		        for(j=0;j<size;j++)
		        {
		         printf("%c\t",dice[i][j]);
		        }

		        printf("\n");
		 }
		}
		break;

	case 3:
		if(size<7)
			printf("FAIL\n");
		else
		{
			dice[(size-1)/2-1][(size-1)/2-1]='бс';
        	        dice[(size-1)/2+1][(size-1)/2+1]='бс';
                	dice[(size-1)/2][(size-1)/2]='бс';
		 for(i=0;i<size;i++)
		 {
		        for(j=0;j<size;j++)
		        {
		         printf("%c\t",dice[i][j]);
		        }

		        printf("\n");
		 }
		}
		break;
	case 4:
		if(size<7)
			printf("FAIL\n");
		else
		{
	                dice[(size-1)/2-1][(size-1)/2-1]='бс';
        	        dice[(size-1)/2+1][(size-1)/2+1]='бс';
        	        dice[(size-1)/2-1][(size-1)/2+1]='бс';
                	dice[(size-1)/2+1][(size-1)/2-1]='бс';
		 for(i=0;i<size;i++)
		 {
		        for(j=0;j<size;j++)
		        {
		         printf("%c\t",dice[i][j]);
		        }

		        printf("\n");
		 }
		}
		break;
	case 5:
		if(size<9)
			printf("FAIL\n");
		else
		{
	                dice[(size-1)/2-1][(size-1)/2-1]='бс';
        	        dice[(size-1)/2+1][(size-1)/2+1]='бс';
               		dice[(size-1)/2-1][(size-1)/2+1]='бс';
	                dice[(size-1)/2+1][(size-1)/2-1]='бс';
        	        dice[(size-1)/2][(size-1)/2]='O';
		 for(i=0;i<size;i++)
		 {
		        for(j=0;j<size;j++)
		        {
		         printf("%c\t",dice[i][j]);
		        }

		        printf("\n");
		 }
		}
                break;
	
	case 6:
		if(size<9)
			printf("FAIL\n");
		else
		{
			dice[(size-1)/2-1][(size-1)/2-1]='бс';
        	        dice[(size-1)/2-1][(size-1)/2+1]='бс';
                	dice[(size-1)/2][(size-1)/2-1]='бс';
	                dice[(size-1)/2][(size-1)/2+1]='бс';
        	        dice[(size-1)/2+1][(size-1)/2-1]='бс';
                	dice[(size-1)/2+1][(size-1)/2+1]='бс';
		 for(i=0;i<size;i++)
		 {
		        for(j=0;j<size;j++)
		        {
		         printf("%c\t",dice[i][j]);
		        }

		        printf("\n");
		 }
		}
		break;
 }

 for(i=0;i<size;i++)
 {
	free(dice[i]);
 }
 free(dice);

 return 0;
}