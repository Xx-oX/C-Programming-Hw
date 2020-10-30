#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

/*DECLARATION*/
int chk_NP(int,int);
int reNP(int);
int chk(int*,int);
int * answer(int,int*);
int judge(int*,int*,int);
int guess(int*,int);
int N,P,H,X;

int main(int argc,char *argv[]){
	/*initialization*/	
	N = atoi(argv[1]);
	P = atoi(argv[2]);
	int r_NP=chk_NP(N,P);
	while(r_NP != 0) r_NP=reNP(r_NP);
	printf("You set N = %d, P = %d\n",N,P);
	int i,r_ans=0,r_gue;
	int *ans;//pointer to the start of array
	ans = answer(P,&r_ans);
	do{
		switch(r_ans){
			case 1:
				r_ans=0;
				for(i=0;i<P;i++) ans[i] = 0;//init
        			printf("The answer is illegal, please reset the answer:\n");
        			ans = answer(P,&r_ans);
				break;
			case 0:
				break;
			default:
				r_ans=0;
				break;
		}}while(r_ans != 0);
	while(1){//loop
		r_gue = guess(ans,P);
		if(H == P && X == 0)
			break;
		else
			continue;
	}	
	printf("Congratulations!!!\n");
	return 0;
}/*check N and P*/
int chk_NP(int n,int p){
	int re=0;
	if(p<0 || p>99) re=1;
	if(n<1) re=1;
	return re;
}/*reinput of N and P*/
int reNP(int re){
	if(re == 1) printf("N/P is illegal, please enter again:");
	scanf("%d%d",&N,&P);
	re = chk_NP(N,P);
	return re;
}/*check the input*/
int chk(int *a,int size)
{
	int i,j,re;
	re=0;//return
	for(i=0;i<size;i++)
	{
		if(a[i]<1 || a[i]>N)
                        re=1;
                else
                        re+=0;
	}
	return re;
}/*deal with 'the answer'*/
int * answer(int p,int *r_ans){
	int i;
	static int read[100];
	for(i=0;i<p;i++) read[i]=0;//init
	printf("ans:");
	for(i=0;i<p;i++){
		scanf("%d",&read[i]);
	}
	*r_ans=chk(read,p);
	return read;
}/*deal with H and X*/
int judge(int *c_ans,int *gue,int size){
	int i,j;
	int ans[P];//copy ans	
	for(i=0;i<P;i++) ans[i] = c_ans[i];
        H=0;
        X=0;
        for(i=0;i<P;i++){
		if(ans[i] == gue[i]){
            H++;
			ans[i]=0;
			gue[i]=(-1);
		}}
	for(i=0;i<P;i++){
		for(j=0;j<P;j++){
			if(ans[i] == gue[j]){
				X++;
				gue[i]=(-2);
				break;
			}}}			
        printf("%dH%dX\n",H,X);
	return 0;
}/*deal with 'the guess'*/
int guess(int *ans,int size){
	int i,j,r_gue,k;
    int gue[size],c_ans[size];
	for(i=0;i<size;i++) c_ans[i] = ans[i];
    printf("guess:");
	for(i=0;i<P;i++) scanf("%d",&gue[i]);
	r_gue=chk(gue,P);
	if(r_gue==1) printf("The guess is illegal!!\n");
	else  r_gue=judge(c_ans,gue,P);
	return 0;
}

