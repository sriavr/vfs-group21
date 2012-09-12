#include<stdio.h>
struct linkedlist{

int data;
struct linkedlist *next;
};

void fetch(FILE *fp);
void delete(FILE *fp);
void update(FILE *fp);
void display();


