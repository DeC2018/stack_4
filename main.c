#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END 5

typedef struct{
    int capacity;
    char *sp;
    char stack[0];
}Stack;


Stack* createStack(int cap){
    Stack *st = (Stack*) calloc(1, sizeof(Stack) + sizeof(char) * cap);
    st->capacity = cap;
    st->sp = st->stack;
    return st;
}

void printStack(const Stack * st){
    char * bp = (char*) st->stack;
    while(bp < st->sp){
        printf("%c ", bp[0]);
        bp++;
    }
    printf("\n");
}

int isStackFull(Stack *st){
    return (int)(st->sp - st->stack) >= st->capacity;
};

void push(Stack *st, char z){
    if( isStackFull(st))
        return;
    st->sp[0] = z;
    st->sp++;
};
int isStackEmpty(Stack* st){
    return st->sp - st->stack <= 0;
};

char pop(Stack * st){
    st->sp--;
    char z = st->sp[0];
    st->sp[0]='\0';
    return z;
};

void destroyStack(Stack* st)
{
    free(st);
};

char* inOutStack(Stack *st, char znak, char * res);

char * getPolska(char * buf);


char* inOutStack(Stack *st, char znak, char * res)
{
	char getZ;


	if(znak == '(')
	{
		push(st, znak);
		return res;
	}


	if (znak == END){
		while(!isStackEmpty(st))
		{
			getZ = pop(st);
			sprintf(res, "%s%c ",res, getZ);
		}
		return res;
	}


	if (znak == ')'){
			while(!isStackEmpty(st))
			{
				getZ = pop(st);
				if (getZ == '(')
					break;
				sprintf(res, "%s%c ",res, getZ);

			}
			return res;
		}


		if (!isStackEmpty(st)){
			getZ = pop(st);


		if (getZ == '(')
		{

			push(st, getZ);

			push(st, znak);
			return res;
		}


		if (znak - getZ >=	 0){
			sprintf(res, "%s%c ",res, getZ);

			push(st, znak);
			return res;
		}

		push(st, getZ);
	}
	push(st, znak);


	return res;
};



char * getPolska(char * buf){
    Stack *st = 0;
    int len = strlen(buf);


    st = createStack(len);
    char *p = buf;


    char *tmp = calloc(len, sizeof(char));

    char znak;
    while(strlen(p) > 0)
    {
        int num;
        int tokens = 0;
        char tostr[20] = {0};
        znak = END;

        if((tokens = sscanf(p, "%d", &num)) < 1)
        {

            sscanf(p, " %c ", &znak);
        }

        if(tokens)
        {
            sprintf(tostr, "%d ", num);
            strcat(tmp, tostr);

        }else{

            sprintf(tostr, " %c", znak);

            tmp = inOutStack(st, znak, tmp);


            printf("res: %s\n stack: ", tmp);
            printStack(st);

        }


        p += strlen(tostr);


        if(strlen(p) < 1)
            break;
    }


		if (znak == ')')
		{
			tmp = inOutStack(st, znak, tmp);
		}
    tmp = inOutStack(st, END, tmp);
    destroyStack(st);
    return tmp;
};

int main(){

    char buf[100] = {0};

    fgets(buf, 99, stdin);
    int len = strlen(buf);
    buf[len - 1] = '\0';

    char *polska = getPolska(buf);
    printf("%s\n", polska);
    return 0;
}