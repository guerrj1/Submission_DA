#include <stdio.h>

int main(void)
{
	int x = 11;
	int y = 0;
	int z = 0;
	
	for(int i = 0; i < 99; i++ )
	{
		if(x % 3 == 0)
		{
			y = x + y;
		}
		else
		{
			z = x + z;
		}
		x++;
	}
	printf("SUM of Numbers Divisible by 3\n");
	printf("Y = 0x%x\n",y);
	printf("SUM of Numbers Not Divisible by 3\n");
	printf("Z = 0x%x",z);
}