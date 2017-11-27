#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

    void push(stack *s, node data);
    int isempty(stack s);
    int isfull(stack s);
    int initStack(stack *s);
    node* pop(stack *s);

#endif // STACK_H_INCLUDED
