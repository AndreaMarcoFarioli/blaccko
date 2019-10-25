#include "object.h"
#define ENTER 13
#define BACKSPACE 8
#define NO_LIMIT -10
#define LINE_LIMIT 79
#define CONSOLEx 80
#define CONSOLEy 25
#define UPARROW 72
#define DOWNARROW 80
#define LEFTARROW 75
#define RIGHTARROW 77
#define ESC 27
//Preset funzioni di stringa I/O
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define password(lenght) instring(lenght, true, false, NULL) //password con lenght variabile
#define input(lenght) instring(lenght, false, false, NULL)	//Text input con lenght variabile
#define line_input instring(79, false, false, NULL)		//Text con massimo ConsoleX-1 caratteri

//LIMITI

const char UPPER[] = {2,  'A','Z'};
const char LOWER[] = {2,  'a','z'};
const char ALPHA[] = {4,  'A','Z','a','z'};

const char NUMERIC[] = {2,  '0','9'};

const char UPPERNUMERIC[] = {4,  '0','9','A','Z'};
const char LOWERNUMERIC[] = {4,  '0','9','a','z'};
const char ALPHANUMERIC[] = {6,  '0','9','A','Z','a','z'};

const char EMAIL[] = {12,  '0','9','A','Z','a','z','@','@','.','.','-','-'};

const char BINARY[] = {2,  '0', '1'};
const char OCTAL[] = {2,  '0', '8'};
const char HEXADECIMAL[] = {4,  '0', '9', 'A', 'F'};


//FINE LIMITI

#define case_input(lenght, case) instring(lenght, false, true, case)	//Controllo caratteri text
#define case_password(lenght, case) instring(lenght, true, true, case)	//Controllo caratteri password

#define r_out(string) outstring(string, true, false, false)		//Stampato a capo \n%s
#define l_out(string) outstring(string, true, true, false)		//LineaPersonale \n%s\n
#define n_out(string) outstring(string, false, true, false)		//Il prossimo a capo %s\n
#define out(string) outstring(string, false, false, false)		//Output inline %s
#define cl_out(string) outstring(string, false, false, true)

#define $(string) _ins(string)					//Forza il contenuto
#define $_(string, char) _add(char, string)	//Aggiungi carattere in fondo
#define _$(string) _invs(string)	//Inverti stringa
#define $$(string1, string) c_ins(string, string1)	//Concatena	%s%s

const VERTICAL_MENU[] = {DOWNARROW, UPARROW, ENTER, ESC};
const int HORIZONTAL_MENU[] = {RIGHTARROW, LEFTARROW, ENTER, ESC};


/////////////////////////////////////////////////////////////////////////////////////////////////////////

//Useful commands
Int ToInt(String stringa);

//STRING COMMANDS

//Sub programs string
void outstring(String text, bool line, bool line_next,  bool clear);			//preset avaible

//Returned String Struct
String instring(int max, bool pw, bool check, char* toCheck);	//preset avaible
String _ins(string text);
String _add(char toAdd, String actual);
String c_ins(String text, String texted);
String _invs(String text);

/*
***Queste funzioni funzionano esattamente come uno stack
***Una si puo' utilizzare sia per int32 che char8. Ricorda che se lo usi per un char, occuperai lo stesso 32 bit;
***Le stringhe invece occupano 32bit + (string.dim * 8bit) + 8 bit;
*/


//Stack integer, char and delegate COMMANDS
//Ispirato a JavaScript

int pop(Stack *actual);					// Stack pop
Stack push(Stack actual, int toAdd);	// Stack push
Stack _Stack(Stack actual);				// Stack inverter

//Stack String COMMANDS
//Ispirato a JavaScript

String $pop($tack *actual);					//String Stack pop
$tack $push($tack actual, String toAdd);	//String Stack push
$tack _$tack($tack actual);					//String Stack inverter


//Dynamic UI
void Print_Menu(Items_interact items, bool vert, bool hide_menu);
void Incrementator(int *pression, Items_interact *items, bool vert);


///////////////////////////////////////////////////////////////////////////////////////////////////
//String commands


//Auto sized input string
String instring(int max, bool pw, bool check, char* toCheck)
{
	register bool limit = !(bool)(max == -10);
	register size_t dimension = 1;
	String str;
	str.text = (string)malloc(dimension);
	do
	{	
		register char xc = getch();
		register bool imit = check;
		if(check)
		{
			if(xc == ' ')
				imit = false;
				else
				{
				register int nm = 1;
				for(nm; nm < toCheck[0]; nm++)
				{
					if(xc >= toCheck[nm++] && xc <= toCheck[nm])
					{
						imit = false;
						break;
					}
				}
			}
		}
		if(xc == ENTER && dimension > 1)
			{	
			dimension--;
			break;
			}
		if(xc == BACKSPACE && dimension > 1)
		{
				dimension--;
				str.text[dimension] = 0;
				printf("\b%c\b",0);
		}
			if(!imit && xc != BACKSPACE && xc != ENTER && (!limit || dimension <= max))
			{		
			str.text[dimension - 1] = xc;
			if(!pw)
			putchar(str.text[dimension-1]);
			else
			putchar('*');
			dimension++;
			}
			str.text = (string)realloc(str.text, dimension);
	}while(true);
	
	str.dim = dimension;
	fflush(stdin);
	
	return str;
}

//Input string, string concat	APPENA ESCE UN CASINO LO RIMPIAZZO CON O_STR
String _ins(string text)
{
	String t;
	t = new_String();
	register int lect = 0;
		while(text[lect] != '\0')
		t = _add(text[lect++], t);
	return t;
}

String c_ins(String text, String texted)
{
	String t = texted;
	texted = t;	
	register int lect = 0;
	while(lect < text.dim)
		t = _add(text.text[lect++], t);
	return t;
}

//Auto sizeod output string
void outstring(String text, bool line, bool line_next, bool clear)
{
	if(line)
		putchar('\n');
	register int i = 0, counter = 0;
	//gotoxy(margin.x, margin.y);
	for( i = 0; i < text.dim; i++)
	{
		register char t = (!clear)? text.text[i]:0;
		if(t == '\n')
		{
			counter++;
			//gotoxy(margin.x,margin.y+counter);
			continue;
		}
		putchar(t);	
	}
	if(line_next)
		putchar('\n');
	
}

String _invs(String text)
{
	String stringa = new_String();
	register int i;
	for(i = text.dim - 1; i >= 0; i--)
		stringa = _add(text.text[i], stringa);
	return stringa;
}

String _add(char toAdd, String actual)
{
	register String newString;
	newString = actual;
	register size_t dimension = newString.dim;
	bool chk = (bool)(dimension == 0);
	dimension++;
	if(chk)
		newString.text = (string)malloc(dimension);
	else
		newString.text = (string)realloc(newString.text,dimension);
	newString.dim = dimension;
	newString.text[dimension-1] = toAdd;
	return newString;
}

bool Equals(String a, String b)
{
	if(a.dim == b.dim)
	{
		register int i = 0;
		for(i; i<a.dim;i++)
			if(a.text[i] != b.text[i])
				return false;
	}	
	else
		return false;
	return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// STACK COMMANDS

Stack push(Stack actual, int toAdd)
{
	Stack s = actual;
	s.stack = (int)realloc(s.stack, (++s.dim)*sizeof(int));
	s.stack[s.counter++] = (int)toAdd;
	s.end = true;
	return s;
}

int pop(Stack *actual)
{
	if((*actual).end)
	{
		(*actual).end = (bool)!(--(*actual).dim == 0);
		return (*actual).stack[(*actual).counter-- - 1];
	}
	return 0;
}

Stack _Stack(Stack actual)
{
	Stack returned = new_Stack();
	while(actual.end)
		returned = push(returned, pop(&actual));
	return returned;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//STRING STACK COMMANDS

$tack $push($tack actual, String toAdd)
{
	$tack s = actual;
	s.alloc += sizeof(int) + (toAdd.dim * sizeof(char)) + 1;
	s.stack = realloc(s.stack, s.alloc);
	s.dim++;
	s.stack[s.counter++] = toAdd;
	s.end = true;
	return s;
}

String $pop($tack *actual)
{
	String a = new_String();
	if((*actual).end)
	{
		a = (*actual).stack[--(*actual).counter];
		(*actual).alloc -= sizeof(int) + (a.dim * sizeof(char)) + 1;
		(*actual).stack = realloc((*actual).stack, (*actual).alloc);
		(*actual).end = (bool)!(--(*actual).dim == 0);
	}
	return a; 	
}

$tack _$tack($tack actual)
{
	$tack returned = new_$tack();
	while(actual.end)
		returned = $push(returned, $pop(&actual));
	return returned;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//useful commands

Int ToInt(String stringa)
{
	register int i, numTmp;
	Int returnedValue;
	returnedValue.data = 0;
	returnedValue.imit = false;
	returnedValue.of = false;
	for(i = stringa.dim-1; i >= 0; i--)
	{
		if(i > 0)
			numTmp = returnedValue.data;
		
		if(stringa.text[i] < '0' || stringa.text[i] > '9' )
		{
			returnedValue.imit = true;
			break;
		}
		returnedValue.data += (stringa.text[i]-'0') * (int)pow(10,stringa.dim-i-1);
		if(returnedValue.data < numTmp)
		{
			returnedValue.of = true;
			break;
		}
	}
	return returnedValue;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//GRAPHICS MENU            ////////////////////////////////////////////////////////////////////

void Print_Menu(Items_interact items, bool vert, bool hide_menu)
{
	int i = 0;
	static int prev = 0;
	gotoxy(1, prev + 1);
	cl_out($$($$($("["), (items).impressions.stack[prev]), $("]")));
	for(i; i < (items).impressions.dim; i++)
	{
		if(vert)
		gotoxy(1, i + 1);
		if(hide_menu)
		{
			cl_out((items).impressions.stack[i]);
			continue;
		}
		
		String toOut = (items).impressions.stack[i];
		bool a = (i == (items).cnt);
		if(a)
		{
			prev = i;
			out($("["));
			textbackground(RED);
			textcolor(WHITE);
		}
		out(toOut);
		textbackground(BLACK);
		textcolor(WHITE); 
		if(a)
			out($("]"));
		out($(" "));
	}
}

void Incrementator(int *pression, Items_interact *items, bool vert)
{

	Items_interact itemsa = *items;
	int size = itemsa.impressions.dim;
	bool press_1, press_2, confirm, exit;
	do
	{		
		Print_Menu(itemsa, vert, false);	
		int a = getch();
		press_1 = (bool)(a == pression[0]);
		press_2 = (bool)(a == pression[1]);
		confirm = (bool)(a == pression[2]);
		exit = (bool)(a == pression[3]);
		if(press_1)
		{
			if(++(*items).cnt >= size )
				(*items).cnt = 0;
		}
		else if(press_2)
		{
			if(--(*items).cnt < 0)
				(*items).cnt = (size)-1;
		}
		else if(confirm)
		{
			Print_Menu(itemsa, true, true);
			gotoxy(1,1);
			CallAddress((itemsa).callbacks.stack[(*items).cnt]);
		}
		else if(exit)
			break;
				itemsa = *items;
	}while(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// GRAFICA /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void c_out(String text, int y)
{
	register int x = 40 - (text.dim/2);
	gotoxy(x, y);
	out(text);
}

/*
***	Autore: Andrea Marco Farioli
*** Blaccko_1.0
*/
