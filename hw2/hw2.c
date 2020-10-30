#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

void guess(char *ans,int size);
void cls_spc(char *a,int size);
void chk(char *a,int size,int *re);

int N,P,H,X;

/*clear the space and fill it with next value*/
void cls_spc(char *a,int size)
{
	int i,j,n;
	n = strlen(a);
	for(i=0;i<n;i++)
        {
                if(a[i]==32){
                        for(j=i;j<n;j++){
                                a[j]=a[j+1];
                        }
                }
        }
}

/*check the input*/
void chk(char *a,int size,int *re)
{
	int i,j,n;
	*re=0;//return
	n = strlen(a);
	for(i=0;i<n;i++)
	{
		if(a[i]<49 || a[i]>(N+48))
                        *re=1;
                else
                        *re+=0;
	}
	/*check if the input is too short or long*/
	if(n!=P) *re = 1;	
	else *re+=0;
}

/*deal with 'the guess'*/
void guess(char *ans,int size)
{
	
	int i,j,re,k;
        char gue[P];

	memset(gue, 0,sizeof(gue));
        printf("guess:");
        scanf("%[^\n]",gue);
        getchar();
	cls_spc(gue,P);
	chk(gue,P,&re);

	if(re==1)
		printf("The guess is illegal!!\n");
	else{
		k=0;	
        	H=0;
        	X=0;
        	for(i=0;i<P;i++){
        		for(j=k;j<P;j++){
                		if(ans[i] == gue[j]){
                        		if(i == j){
                                		H++;
						k++;
						break;
					}
                                	else{
						X++;
						break;
					}
                        	}
                	}
       		}
        printf("%dH%dX\n",H,X);
	}
}


int main(int argc,char *argv[])
{
	/*initialization*/	
	N = atoi(argv[1]);
	P = atoi(argv[2]);
	if(N<1 || N>9){	
		printf("N is illeagl,pls set N again:");
		scanf("%d",N);
		printf("\n");
	}
	printf("You set N = %d, P = %d\n",N,P);
	char ans[P];
	int re;//from chk()
        memset(ans, 0, sizeof(ans));//initialize the ans[] 
	printf("ans:");
        scanf("%[^\n]",ans);
        getchar();//use to absorb the 'Enter'
	cls_spc(ans,P);
	chk(ans,P,&re);

	do//check the ans
	{
		switch(re)
		{
			case 1:
				memset(ans, 0, sizeof(ans));
        			printf("The answer is illegal, please reset the answer:\nans:");
        			scanf("%[^\n]",ans);
        			getchar();
				re = 0;
				cls_spc(ans,P);
        			chk(ans,P,&re);
				break;
			case 0:
				break;
			default:
				re=0;
				break;
		}
	}while(re!=0);

	while(1)//loop
	{
		guess(ans,P);

		if(H == P && X == 0)
			break;
		else
			continue;
	}
		
	printf("Congratulations!!!\n");
	
	return 0;
}

