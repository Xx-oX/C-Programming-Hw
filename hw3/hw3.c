#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>
#include <sys/types.h>

/*binary to float*/
void setbit(u_int32_t* f, int i){
    u_int32_t mask = ((u_int32_t)1) << i;
    *f |= mask;
}
float rd_float(char* bits,int size){
    float f = 0;
    for(int i=0;i<size;i++){
        int bit = bits[size-i-1]- '0';
        if(bit){
            setbit((u_int32_t*)&f, i);
        }
    }
    return f;
}

/*binary to double*/
void setbit_64(u_int64_t* f, int i){
    u_int64_t mask = ((u_int64_t)1) << i;
    *f |= mask;
}
double rd_double(char* bits,int size) {
    double f = 0;
    for(int i = 0; i < size; i++){
	int bit = bits[size-i-1] - '0';
	if(bit){
	    setbit_64((u_int64_t*)&f, i);
	}
    }
    return f;
}


/*binary to decimal*/
int b2d(int a[],int size){
	int i,j,t;
	t=0;
	for(i=size-1,j=0;i>=0;i--,j++){	
		t+=a[i] * pow(2,j);
		if(j>size) break;
	}
	return t;
}

/*decimal to binary*/
void d2b(int64_t dec,int size){
	int64_t i;
	u_int64_t m;
	int j;
	for(i=(size-1);i >= 0;i--){
		m = dec >> i;
		putchar((m&1)?'1':'0');//if...->1,else...->0
	}
	putchar('\n');
}

int main(int argc,char *argv[])
{
	int M = atoi(argv[1]);
	int i,j;
	char a_c[32],e_c[64];
	char* cha;
	char* che;	
	int a[32],a_s[31];
	int e[64],e_s[64];
	float b_f,f;
	int *b;
	long long c,*d;
	double d_d,e_d;
	long long int t,T;
	switch(M){
		case 1:
			for(i=0;i<32;i++){
				a_c[i] = argv[2][i];
				a[i]=a_c[i]-48;
			}
			printf("integer:");
			if(a[0] == 1){ //~a
			printf("-");
			for(i=0;i<32;i++) a[i]=(a[i]>0)?0:1;
			}
			a[31]+=1;//a[31]+1
			for(i=31;i>=0;i--){
				if(a[i]>1){
				a[i-1]+=1;
				a[i]=0;	
				}	
			}
			for(i=0,j=1;i<31;i++,j++) a_s[i]=a[j];
			t=b2d(a_s,31);
			printf("%lld\nfloat:",t);
			cha = argv[2];	
			f=rd_float(cha,32);
			printf("%.6f\n",f);
			break;
		case 2:
			printf("32-bit:");
			d2b(atoi(argv[2]),32);
			break;
		case 3:
			printf("32-bit:");
			b_f=atof(argv[2]);
			b= &b_f;
			d2b(*b,32);
			break;
		case 4:
			for(i=0;i<64;i++){
           		e_c[i] = argv[2][i];
                e[i]=e_c[i]-48;
            }
            printf("integer:");
            if(a[0] == 1){ //~a
           		printf("-");
           		for(i=0;i<64;i++) a[i]=(a[i]>0)?0:1;
            	}
            	a[63]+=1;//a[63]+1
            	for(i=63;i>=0;i--){
                	if(a[i]>1){
                	a[i-1]+=1;
                	a[i]=0;
                	}
            	}
			for(i=0,j=1;i<63;i++,j++) e_s[i]=e[j];
			T=0;
        	for(i=63,j=0;i>=0;i--,j++){
            	T+=e[i] * pow(2,j);
                if(j>64) break;
        	}
			printf("%lld\ndouble:",T);
			che = argv[2];	
			e_d=rd_double(che,64);
			printf("%.6f\n",e_d);
            break;
		case 5:
			printf("64-bit:");
			c=atoi(argv[2]);
			d2b(c,64);
			break;
		case 6:
			printf("64-bit:");
			d_d=atof(argv[2]);
			d=&d_d;
			d2b(*d,64);
			break;
		default : break;
	}
	return 0;
}
