#ifndef NUM_H
#define NUM_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Structure of Doubly Linked List
typedef struct node {
    // To store a single digit
    char data;
    // Pointers to the previous and next digit
    struct node* next;
    struct node* prev;
} node;

typedef struct input {
        int size;
        // 0 for +ve and 1 for -ve
        char sign;
	// head pointer to big number linked list
        node *head;
	// tail pointer to big number linked list
        node *tail;
} input;


// to indicate error and exit from loop
extern int cont;


// to init head structure of big number
void init_num(input *num);

// to change the sign of number
void neg(input *num);

void rem_lead_zeros(input *num);

// to free corresponding big number linked list
void destroy(input *num);

/*To display the number.*/
void display(input num);

// To insert at the beginning of the list
void insertInFront(input *num, int value);

// To insert in the end
void insertInEnd(input *num, int value);

// Returns the number of digits
int length(input num);


int compare(input a, input b);

/* Uses simple addition method that we
   follow using carry*/
input add(input *a, input *b);

// Normal subtraction is done by borrowing
input sub(input *a, input *b);

// Normal multiplication is used i.e. in one to all way
input mult(input *a, input *b);

input power(input base, input exp);

input division(input *l, input *m);

input modulo(input *l, input *m);

input changeBase(input num, int k);

input toDeci(list *L, int b);


#endif

