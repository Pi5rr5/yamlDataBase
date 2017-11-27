#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/some_funct.h"
#include "../h/struct.h"

#ifndef STACK_C_INCLUDED
#define STACK_C_INCLUDED

int isempty(stack s) {
    return (s.top == -1);
}

int isfull(stack s) {
    return (s.top == s.sizeMax);
}

node* pop(stack *s) {
    node *data;

    if(!isempty(*s)) {
        data = malloc(sizeof(node));
        if(data != NULL) {
            if(s->tree[s->top] != NULL) {
                data = s->tree[s->top];
                free(s->tree[s->top]);
                s->top--;
                return data;
            }
        }
    }
    return NULL;
}

void push(stack *s, node data) {
    if(!isfull(*s)) {
        s->top++;
        s->tree[s->top] = malloc(sizeof(node));
        if(s->tree[s->top] != NULL) {
            strcpy(s->tree[s->top]->content, data.content);
            s->tree[s->top]->line = data.line;
        }
    }
}

int initStack(stack *s) {
    if(s != NULL) {
        s->tree = malloc(sizeof(node)*10);
        if(s->tree != NULL) {
            return 1;
        }
        s->sizeMax = MAX;
        s->top = -1;
    }
    return 0;
}

#endif // STACK_C_INCLUDED
