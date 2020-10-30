/*
	Compute the sum of two fractions
	and reduce it with Euclidean Algorithm
*/
#include<stdio.h>
#include<stdlib.h> 

int reduce(int a,int b)
{
	if(b>a)
		reduce(b,a);
	else{
		if(a%b == 0)
			return b;
		else
			return reduce(b,a%b);
	}

}

int main(int argc, char *argv[])
{
	int num1 = atoi(argv[1]);
	int denom1 = atoi(argv[2]);
	int num2 = atoi(argv[3]);
	int denom2 = atoi(argv[4]);
	int result_num = num1*denom2 + num2*denom1;
	int result_denom = denom1*denom2;
	int gcd = reduce(result_num,result_denom);	
	
	result_denom /= gcd;
	result_num /= gcd;
	printf("%d/%d\n",result_num,result_denom);

	return 0;
}
