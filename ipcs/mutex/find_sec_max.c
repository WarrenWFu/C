#include <stdio.h>

int find_sec_max(const int *array, 
		int count, int *value)
{
	int		i;
	int		sec;//第二大
	int		max;//最大
	for(i=1; 
		(array[0]==array[i]) && i<count;
		i++ )
	{
		NULL;
	}
	if( i == count )
	{
		return 1;
	}

	if( array[0] < array[i] )
	{
		sec = array[0];
		max = array[i];
	}
	else
	{
		sec = array[i];
		max = array[0];
	}
	for( i=i+1; i<count; i++ )
	{
		if( array[i]>max )
		{
			sec = max;
			max = array[i];
		}
		else if( array[i]>sec 
			&& array[i]<max )
		{
			sec = array[i];
		}
	}

	*value = sec;
	return 0;
}

int main()
{
	int num[]={9,9,9,9,8,8,8,9,9,9};
	int sec;
	int ret;

	ret = find_sec_max( num, 
		sizeof(num)/sizeof(int), 
		&sec);
	if(ret)
	{
		printf("Can't find second max number\n");
	}
	else
	{
		printf("The second max number is: %d\n", sec);
	}

	return 0;
}
