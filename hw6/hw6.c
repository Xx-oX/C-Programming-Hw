#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct RULE{
	char ippre[20];//premier
	char ipdeu[20];//deuxieme
	char spb[20];
	char spe[20];
	char dpb[20];
	char dpe[20];
	char bit[20];
}RULE;

typedef struct COMPARE{
	char str[100];
	int num;
}COMPARE;

int main(int argc,char *argv[]){
	FILE *inputfp;
	inputfp=fopen(argv[1],"rt");
	printf((inputfp == NULL)?"Fail to open file!\n":"");
	
	RULE *rule = malloc(sizeof(RULE)*9999);//rule[9999]
	char inputstr[80];
	int i=0,totalrules=0;
	while(fgets(inputstr,80,inputfp)!=NULL){//read
		sscanf(inputstr,"@%s %s %s : %s %s : %s %s",rule[i].ippre,rule[i].ipdeu,rule[i].spb,rule[i].spe,rule[i].dpb,rule[i].dpe,rule[i].bit);
		strcat(rule[i].spb,"/");
		strcat(rule[i].dpb,"/");
		strcat(rule[i].spb,rule[i].spe);
		strcat(rule[i].dpb,rule[i].dpe);
		i++;
		totalrules++;
	}
	int F1=1,F2=1,F3=1,F4=1,F5=1;
	COMPARE *dippre = malloc(sizeof(COMPARE)*9999);
	COMPARE *dipdeu = malloc(sizeof(COMPARE)*9999);
	COMPARE *ds = malloc(sizeof(COMPARE)*9999);
	COMPARE *dd = malloc(sizeof(COMPARE)*9999);
	COMPARE *dbit = malloc(sizeof(COMPARE)*9999);
	strcpy(dippre[0].str,rule[0].ippre);
	strcpy(dipdeu[0].str,rule[0].ipdeu);
	strcpy(ds[0].str,rule[0].spb);
	strcpy(dd[0].str,rule[0].dpb);
	strcpy(dbit[0].str,rule[0].bit);
	int j;
	int add;
	for(i=0;i<totalrules;i++){
	    add=0;
		for(j=0;j<F1;j++){
			if(strcmp(rule[i].ippre,dippre[j].str) != 0){
				add++;
			}else{
			    add = 0;
			    break;
            }}if(add != 0)
                strcpy(dippre[F1++].str,rule[i].ippre);
	}
	for(i=0;i<totalrules;i++){
		add=0;
		for(j=0;j<F2;j++){	
			if(strcmp(rule[i].ipdeu,dipdeu[j].str) != 0){
				add++;
			}else{
			    add = 0;
			    break;
            }}if(add != 0)
                strcpy(dipdeu[F2++].str,rule[i].ipdeu);
	}
	for(i=0;i<totalrules;i++){
	    	add=0;
		for(j=0;j<F3;j++){	
			if(strcmp(rule[i].spb,ds[j].str) != 0){
				add++;
			}else{
			    add = 0;
			    break;
            }}if(add != 0)
                strcpy(ds[F3++].str,rule[i].spb);			
	}
	for(i=0;i<totalrules;i++){
	    	add=0;
		for(j=0;j<F4;j++){	
			if(strcmp(rule[i].dpb,dd[j].str) != 0){
				add++;
			}else{
			    add = 0;
			    break;
            }}
            if(add != 0)
                strcpy(dd[F4++].str,rule[i].dpb);			
	}
	for(i=0;i<totalrules;i++){
	    	add=0;
		for(j=0;j<F5;j++){	
			if(strcmp(rule[i].bit,dbit[j].str) != 0){
				add++;
			}else{
			    add = 0;
			    break;
            }}
            if(add != 0)
                strcpy(dbit[F5++].str,rule[i].bit);			
	}

	int d1=0,d2=0,d3=0,d4=0,d5=0;
	int subrules=1;
	COMPARE *ddd = malloc(sizeof(COMPARE)*9999);
	COMPARE *sub = malloc(sizeof(COMPARE)*9999);
	strcpy(sub[0].str,ddd[0].str);
	for(i=0;i<totalrules;i++){
		if(strcmp(rule[i].ippre,"0.0.0.0/0") == 0)
			d1++;	
		if(strcmp(rule[i].ipdeu,"0.0.0.0/0") == 0)
			d2++;
		if(strcmp(rule[i].spb,"0/65535") == 0)
			d3++;
		if(strcmp(rule[i].dpb,"0/65535") == 0)
			d4++;
		if(strcmp(rule[i].bit,"0x00/0x00") == 0)
			d5++;
	}
	for(i=0;i<totalrules;i++){
		strcpy(ddd[i].str,rule[i].spb);
		strcat(ddd[i].str,rule[i].dpb);
		strcat(ddd[i].str,rule[i].bit);
	}
	for(i=0;i<totalrules;i++){
		add=0;
		for(j=0;j<subrules;j++){
                        if(strcmp(ddd[i].str,sub[j].str) != 0){
                                add++;
                        }else{
                            add = 0;
                            break;
            }}
            if(add != 0)
                strcpy(sub[subrules++].str,ddd[i].str);
	}
	subrules-=1;

	printf("F1:%d\n",F1);
	printf("F2:%d\n",F2);
	printf("F3:%d\n",F3);
	printf("F4:%d\n",F4);	
	printf("F5:%d\n",F5);
	printf("\nF1:%d\n",d1);
        printf("F2:%d\n",d2);
        printf("F3:%d\n",d3);
        printf("F4:%d\n",d4);
        printf("F5:%d\n",d5);
	printf("\n%d\n",totalrules);
	printf("\n%d\n",subrules);
	free(dippre);
	free(dipdeu);
	free(ds);
	free(dd);
	free(dbit);
	free(ddd);
	free(sub);
	free(rule);
	fclose(inputfp);
} 
