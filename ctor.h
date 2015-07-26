#ifndef CTOR_H
#define CTOR_H


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define ERROR( FormatString, ... ) fprintf( stderr, "(%s:%d)" FormatString "\n", __FUNCTION__, __LINE__, __VA_ARGS__ )

#define NIL '\0'
#define BUFFER 20

#define QUIT 		(-1)
#define NUMBER 		0x001
#define OPERATOR 	0x002
#define HELP		0x004
#define SHOWTOP     0x008
#define CLEAR		0x010
#define BLANK       0x020


void push_stack(double);
double get_stack(void);
int getop(char *);
void showHelp(void);
void showTop(void);
void showResult(void);
void clear_stack(bool);
void result_stack(double);

#endif
