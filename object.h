#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio2.h>
#include <math.h>



typedef char* string;		//define type string
typedef void* (*delegate)();
void CallAddress(delegate d);

//Oggetto stringa
typedef struct str
{
	string text;
	size_t dim;			//NON TOCCARE MAI DIRETTAMENTE
} String;

typedef struct STACK
{
	int* stack;
	int dim;
	int counter;
	bool end;
} Stack;


typedef struct s_STACK
{
	String* stack;
	int dim;
	int counter;
	size_t alloc;
	bool end;	
} $tack;


typedef struct packet_int
{
	bool imit;
	bool of;
	int data;
} Int;

typedef struct combo_selection
{
	
	$tack impressions;			//Da anche la dimensione;
	Stack callbacks;
	int cnt;
} Items_interact;



String new_String()
{
	String string_;
	string_.dim = 0;
	string_.text = (string)malloc(1);
	return string_;	
}

Stack new_Stack()
{
	Stack s;
	s.stack = malloc(sizeof(int));
	s.dim = 0;
	s.counter = 0;
	s.end = false;
	return s;
}

$tack new_$tack()
{
	$tack s;
	s.counter = 0;
	s.dim = 0;
	s.end = false;
	s.alloc = 0;
	s.stack = malloc(0);
	return s;
}

Items_interact new_itemsInteract()
{
	Items_interact t;
	t.callbacks = new_Stack();
	t.impressions = new_$tack();
	t.cnt = 0;
	return t;
}

void CallAddress(delegate d)
{
	d();
}


