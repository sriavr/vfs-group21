#include<stdio.h>
struct linkedlist{

int data;
struct linkedlist *next;
};

struct linkedlist* fetch(FILE *fp);
//void delete();
void update(FILE *fp);
void display(struct linkedlist *);


