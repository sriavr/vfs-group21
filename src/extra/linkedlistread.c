#include<stdio.h>
#include<stdlib.h>
#include "../include/LinkedListh.h"

void main(){
	FILE *fp;
	struct linkedlist *start=NULL;
	int operation=0;
	fp=fopen("../DATFILE/data1.dat","rb");
		if(fp==NULL)
			printf("file not found");
		else{
			while(1){
			printf("enter which operation you want to continue\n1.Fetch data from file\n 2. Delete data from file \n3.Update data into file\n 4.Display");

			scanf("%d",&operation);
			switch(operation)
			{
			case 1:
<<<<<<< .mine
			start=(struct linkedlist *)fetch(fp);
=======
			fetch(start,fp);
>>>>>>> .r8
			break;
<<<<<<< .mine
			//case 2:
;
	int notmatch=0,scanvalue=0,updatedvalue=0;			//delete(start,fp);
			//break;
=======
			case 2:
			delete(start,fp);
			break;
>>>>>>> .r8
			case 3:
			update(start,fp);
			break;
			case 4:
			display(start);
			break;

		    	
			}
		    }
	

		     }	

}

//FETCHING DATA FROM FILE IN ORDER TO BE DISPLAYED IN LIST
<<<<<<< .mine
struct linkedlist*  fetch(FILE *fp){
	struct linkedlist *store=NULL,*new=NULL,*start=NULL;
		
=======
void fetch(struct linkedlist *start,FILE *fp){
	struct linkedlist *store=NULL,*new=NULL;	
>>>>>>> .r8
	int choice=0;
	int output=0;
	while(choice!=-1){
		fread(&output,sizeof(int),1,fp);
		new=(struct linkedlist*)malloc(sizeof(struct linkedlist));		
		new->data=output;
		new->next=NULL;
		if(start==NULL)
			start=new;
		else{
			store=start;
			while(store->next!=NULL)
			store=store->next;

			store->next=new;
		    }
		printf("do you want to continue");
		scanf("%d",&choice);
		}
		printf("file has been read");
	return start;
}

//DISPLAYING DATA FETCH FROM FILE
void display(struct linkedlist *start){


	struct linkedlist *display=NULL;
	display=start;
	while(	display!=NULL){
		printf("%d",display->data);
		display=display->next;
	}
}


//UPDATING DATA 
void update(struct linkedlist *start,FILE *fp){
	struct linkedlist *update=NULL;
	int notmatch=0,scanvalue=0,updatedvalue=0;
	update=start;
	printf("enter the value you want to update  n  value");
	scanf("%d %d",&scanvalue,&updatedvalue);
	
	while(update!=NULL){
		if(scanvalue==update->data){
		update->data=updatedvalue;
		fseek(fp,notmatch+1,SEEK_SET);
		printf("m in update");//write updated data to file at notmatcth th location
		fwrite(&updatedvalue,sizeof(int),1,fp);
		}

		update=update->next;
		notmatch++;
	}
}	



//REMOVING ANY DATA FROM FILE
void delete(struct linkedlist *start,FILE *fp){
	struct linkedlist *delete=NULL;
	int del=0,notmatch;
	delete=start;
	printf("enter a value you want to delete");
	scanf("%d",&del);
	while(delete!=NULL){
		if(del==delete->next->data){
		delete->next=delete->next->next;
		fseek(fp,notmatch+1,SEEK_SET);//notmatch+1 th location mein data has to del
		//CREATE FREE LIST TO INSERT THIS BLOCK IN FREE LIST
		}
		delete=delete->next;
		notmatch++;
	}
}
		
			

	

		

