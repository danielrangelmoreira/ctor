#include "ctor.h"

/* Pointers for stack control */

static int * p; 		/* Stack */
static int * bos;		/* Bottom of Stack */
static int * tos;		/* Top of Stack */

void clear_stack(bool warn){
    p = tos;
    memset(p, NIL, BUFFER);
    if(warn)
        printf("The stack is clean!\n");
}

void result_stack(int result){
    
    if(p < bos){
        clear_stack(false);
        push_stack(result);
        showResult();
        
    } else {
        
        ERROR("p<bos fail p=%i bos=%i", *p, *bos);
    }
    
}
void push_stack(int i){
    
    if(p < bos){
        *p++ = i;
        
    } else {
        ERROR("Buffer overflow: p=%i", *p);
    }
}

int get_stack(void){
    
    if(p > tos){
        return *(--p);
        
    } else {
        
        return *p;
    }
}

int getop(char *c){
    
    int control = false;
    int character = 0;
    bool inNumber = false;
    


    while((character=getc(stdin)))
    {
        // printf("$> ");
        
        if(control){
            control=false;
            if(character == 'q'){
                return QUIT;
            }
            if(character == 'c'){
                return CLEAR;
            }
            if(character == 'h'){
                return HELP;
            }
        }
        
        if(character == ':'){
            control = true;
        }
        
        if( character == '+' ||
           character == '-' ||
           character == '*' ||
           character == '/' ||
           character == '='){
            
            if(inNumber){
                ungetc(character, stdin);
                return NUMBER;
                
            } else{
                *c++ = character;
                *c = '\0';
                return OPERATOR;
            }
        }
        
        if( isdigit(character)){
            inNumber = true;
            *c++ = character;
                
            
        }
        
        else if( character == '\n'){
            if (!inNumber) {
                *c++ = '\0';
                return BLANK;
            }
            else return NUMBER;
            
        }

    
    
    }
    return false;
}

bool initStack(void){
    
    p = (int *) malloc( sizeof(int) * BUFFER );
    
    if(!p){
        
        return false;
        
    } else {
        tos = p;
        bos = p + BUFFER - 1;
        return true;
    }
}

void showTop(void)
{
    if(p){
        
        printf("Top of stack: %i\n",  *tos);
        
    } else {
        
        printf("The stack is empty!\n");
        
    }
}
void showResult(void)
{
    if(p){
        
        printf(":= %i\n",  *tos);
        
    } else {
        
        printf("The stack is empty!\n");
        
    }
}

void showHelp(void){
    printf("showHelp!\n");
}

int main() {
    
    int type = 0;
    int op2 = 0;
    char s[BUFFER];
    
    if(!initStack()){
        ERROR("Can't initStack p=%i", *p);
    }
    
    printf("Reverse Notation Calculator.\n");
    printf(":q to quit :c to clear.\n");
    
    while( (type = getop(s)) != QUIT){
        
        switch(type){
                
            case BLANK:
                break;
                
            case CLEAR:
                clear_stack(true);
                break;
                
            case NUMBER:
                push_stack(atoi(s));
                break;
                
            case OPERATOR:
                
                if(s[0] == '='){
                    showTop();
                    break;
                }
                
                if (s[0] == '+'){
                    
                    result_stack(get_stack() + get_stack());
                    
                    break;
                }
                
                if (s[0] == '-'){
                    op2 = get_stack();
                    result_stack(get_stack() - op2);
                    break;
                }
                
                if (s[0] == '/') {
                    
                    op2 = get_stack();
                    
                    if (op2 != 0){
                        
                        result_stack(get_stack() / op2);
                        break;
                        
                    } else { 
                        
                        printf("main: divisor zero");
                        break;
                    }
                }
                
                if( s[0] == '*'){
                    result_stack( get_stack() * get_stack() );
                    break;
                }
                
                ERROR("Unknow operator s=%c", s[0]);
                return -1;
                
            case HELP:
                showHelp(); /* code */
                break;
                
        }
        
        
    }
    
    return 0;
}