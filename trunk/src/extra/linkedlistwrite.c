#include<stdio.h>
#include<stdlib.h>
#include "../include/LinkedListh.h"

void main(){
	FILE *fp;
	int exitvalue ,input;
	
	fp=fopen("../DATFILE/data1.dat","wb");
	struct linkedlist *start=NULL,*new=NULL,*store=NULL;
	
	while(exitvalue !=-1)
	{
		printf("enter the data");
		scanf("%d",&input);
			if(start==NULL){
	
				start=(struct linkedlist*)malloc(sizeof(struct linkedlist));
				start->data=input;
				store=start;
				}
			else{
				store=start;
				new=(struct linkedlist*)malloc(sizeof(struct linkedlist));
				while(store->next!=NULL)
				store=store->next;
	
				store->data=input;
				store->next=new;
			    }
	
		fwrite(&store->data,sizeof(store->data),1,fp);

	
		printf("press -1 to exit");
		scanf("%d",&exitvalue);
	}
	fclose(fp);

}
