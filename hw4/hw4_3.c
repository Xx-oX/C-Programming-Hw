#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*DECLARATION*/
int b2i(char*);
long long b2i_64(char*);
int b2f(int,float**);
int b2d(long long,double**);
char d2c(long long,int);
int d2b(long long);
int d2b_64(long long);

int main(int argc,char *argv[])
{
	int M = atoi(argv[1]);
	int i,j;
	int nul;//get the return
	float *float_1;
	double *double_4;
	float float_3 = 0;
	double double_6 = 0;
	int *ptr_3;//direct to float_3
	long long *ptr_6;//direct to double_6

	switch(M){
		case 1:
			nul = b2f(b2i(argv[2]),&float_1);
			printf("integer:%d\nfloat:%f\n",b2i(argv[2]),*float_1);
			break;
		case 2:
			nul = d2b(atol(argv[2]));
			break;
		case 3:
			float_3=atof(argv[2]);
			ptr_3 = &float_3;
			nul = d2b(*ptr_3);
			break;
		case 4:
			nul = b2d(b2i_64(argv[2]),&double_4);
			printf("integer:%lld\ndouble:%f\n",b2i_64(argv[2]),*double_4);
                        break;
		case 5:
			nul = d2b_64(atol(argv[2]));
			break;
		case 6:
			double_6=atof(argv[2]);
			ptr_6 = &double_6;
			nul = d2b_64(*ptr_6);
			break;
		default : break;
	}
	return 0;
}

/*binary(32) to integer*/
int b2i(char bin[32]){
	int i,num=0;
	for(i=0;i<32;i++){
		if(bin[i] == '1')
			num |= (int)1 <<31-i;		
	}
	return num;
}
/*binary(64) to integer*/
long long b2i_64(char bin[64]){
	long long i,num=0;
	for(i=0;i<64;i++){
		if(bin[i] == '1')
			num |= (long long)1 <<63-i;		
	}
	return num;
}
/*binary to float (pass by integer)*/
/*void functions are not include in the required 12 functions,
 * so using int function that change value by pointers and return 0*/
int b2f(int num,float **f){
	*f = (float *) &num;
	return 0;
}
/*binary to double (pass by long long)*/
int b2d(long long num,double **d){
	*d = (double *) &num;
	return 0;
}
/*decimal to binary by char*/
char d2c(long long dec,int i){
	unsigned long long m;
	char ch;
	m = dec >> i;
	ch = (m&1)?'1':'0';
	return ch;
}
/*case 2,3(should use void function,but that is not allowed in hw)*/
int d2b(long long x){
	int i;
	printf("32-bit:");
	for(i=31;i>=0;i--)
		printf("%c",d2c(x,i));
	putchar('\n');
	return 0;
}
/*case 5,6*/
int d2b_64(long long x){
	int i;
	printf("64-bit:");
	for(i=63;i>=0;i--)
		printf("%c",d2c(x,i));
	putchar('\n');
	return 0;
}
