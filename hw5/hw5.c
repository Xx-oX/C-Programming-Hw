#include<stdio.h>
#include<stdlib.h>
#include<string.h>//for qsort()

/*declare a type called bucket*/
typedef struct bucket{
	int num[100];//number
	int qn;//quantity of numbers
}bucket;
/*DECLARATION*/
int cmp(const void *a,const void *b);
void fprint_result(int n,int new_n,bucket old[],bucket new[]);
bucket mk_bucket(int m,int d,int s,int time);
int bucket_union(bucket old,bucket *new_buc,int new_n,int m);
int new_mapping(bucket old,bucket *new_buc,int index,int new_n,int m);

int main(int argc,char *argv[]){
	int n=atoi(argv[1]);//number of buckets
        int m=atoi(argv[2]);//maximum numbers in a bucket
        int d=atoi(argv[3]);//range of numbers(0~d)
        int s=atoi(argv[4]);//seed for srand()
	int i,j;//for()
	srand(s);//use s as seed to initialize

	bucket old_buc[100];//make a original mapping(includes buckets*n)
	for(i=0;i<n;i++) old_buc[i] = mk_bucket(m,d,s,i);//initialize&randomize buckets
	for(i=0;i<n;i++)//do quick sort for each bucket
		qsort(old_buc[i].num,old_buc[i].qn,sizeof(old_buc[0].num[0]),cmp);
	bucket new_buc[100];//use to store compressed old_buc
	new_buc[0] = old_buc[0];//put first bucket into new_buc
	int new_n=1;//number of buckets in new mapping
	int index[100]={0};//where old bucket should be in new bucket
	/*compress*/
	for(i=1;i<n;i++){
	index[i] = bucket_union(old_buc[i],new_buc,new_n,m);//use bucket_union to find index		
	new_n = new_mapping(old_buc[i],new_buc,index[i],new_n,m);//do new mapping and return new_n
	}fprint_result(n,new_n,old_buc,new_buc);//output
	return 0;
}/*conpare function (for qsort usage)*/
int cmp(const void *a,const void *b){
	return *(int*)a-*(int*)b;//ascend 
}/*output the result to a file*/
void fprint_result(int n,int new_n,bucket old[],bucket new[]){
	FILE *fptr;//pointer to file
	fptr = fopen("hw5.out","w");//make a file called 'hw5.out'
	if(fptr == NULL) printf("Can't create file.\n");//unnecessary
    fprintf(fptr,"%d\n\n",new_n);//print number of buckets
	int i,j;//for()
	for(i=0;i<n;i++){
		fprintf(fptr,"%d/",i);//current number of buckets
		for(j=0;j<old[i].qn;j++) fprintf(fptr,"%d ",old[i].num[j]);
		//print number j of bucket i
		fprintf(fptr,"\n");//change line
	}//print original bucket
	fprintf(fptr,"\n\n");//print space
	for(i=0;i<new_n;i++){
		fprintf(fptr,"%d/",i);//current number of buckets
		for(j=0;j<new[i].qn;j++) fprintf(fptr,"%d ",new[i].num[j]);
		//print number j of bucket i
		fprintf(fptr,"\n");//change line
	}//print new mapping bucket
	printf((fclose(fptr)==0)?"success\n":"failed\n");//close file
}/*make a random numbered bucket*/
bucket mk_bucket(int m,int d,int s,int time){
	bucket buc;//declare a bucket
	int i,j,r,used;//i,j:for() r:random m used:use to generate nonrepeat number 
	r = ((rand()%m)+1);//random quantity of numbers(use 'time' to make 'r' different every time)
	buc.qn = r;//quantity of numbers equals 'r'
	for(i=0;i<r;i++) 
		buc.num[i] = (rand()%d);//generate random number
	return buc;//return a bucket
}/*make index:find the correspond new buckets for old buckets*/
int bucket_union(bucket old,bucket *new_buc,int new_n,int m){
	int i,j,k;//for()
	int same[100]={0};//same[]:quantity of same numbers
	/*find the quantity of same numbers*/
	bucket copy_new[100];
    	for(i=0;i<new_n;i++) copy_new[i]=new_buc[i];//make a copy
	for(i=0;i<new_n;i++){
		for(j=0;j<old.qn;j++){
			for(k=0;k<new_buc[i].qn;k++){
				if(old.num[j] == new_buc[i].num[k]){
					same[i]++;//record in same[]
					new_buc[i].num[k] = -2;//prevent repeat
					break;	
			}}}new_buc[i] = copy_new[i];//recover
	}/*find the biggest same[i] that new_buc[i] has enough space*/
		int a = -1;//use to record i
		int a_max;//record max same[]
	/*-1 means there's no same number nor enough space in exsist buckets */
		for(i=0;i<new_n;i++){
			if((m-new_buc[i].qn) >= (old.qn-same[i])){//if there's enough space in bucket
				if(same[i]>a){//record biggest same[i]
					a_max = same[i];
					a=i;
				}if(a == -1) a=i;//no same number but have space
			}}return a;
}/*put old bucket into new bucket*/
int new_mapping(bucket old,bucket *new_buc,int index,int new_n,int m){
	int i,j,h;//for()	
	int k=old.qn,add[100]={0};//k:position in add[],add[]:buffer for 'wants to add numbers'
	int new_qn = new_buc[index].qn;//new_buc[index].qn = exsisted quantity of numbers in bucket
	bucket copy_new[100];
    	for(i=0;i<new_n;i++) copy_new[i]=new_buc[i];//make a copy
	for(i=0;i<old.qn;i++) add[i] = old.num[i];//add = old
	if(index == -1){//index=-1 means there's no same number in exsist buckets and no space left
		new_buc[new_n] = old;//add a new bucket 
		new_n += 1;//plus 1
	}else{
		for(i=0;i<old.qn;i++){
			for(j=0;j<new_qn;j++){
				if(old.num[i] == new_buc[index].num[j]){
					k--;//k-1
					new_buc[i].num[k] = -2;//prevent repeat
					for(h=i;h<k;h++){//move all number foward to fill the blank
						add[h] = add[h+1];//kick the same number
					}break;
			}}new_buc[i] = copy_new[i];//recover
		}if((k+new_buc[index].qn) > m){//prevent k>m
			new_buc[new_n] = old;//add a new bucket 
			new_n += 1;//plus 1
		}for(i=0;i<k;i++){//k-1 = last position in add[]
			new_buc[index].num[new_qn+i] = add[i];//put number in buffer into new bucket
			new_buc[index].qn += 1;//plus 1
		}}return new_n;//return number of new buckets
}
