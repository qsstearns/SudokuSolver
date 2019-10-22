#include "simpleStack.h"

Stack::Stack() { top = 0; }

Stack::~Stack() { }

bool Stack::isEmpty() { return top == 0; }  // also return !top;
int Stack::size() { return top; }

void Stack::clear() { top = 0; }

void Stack::push(const StackType &d) {

  if (top == STACK_SIZE)
    throw ContainerFullException();

  data[top] = d;					// data[top++] = d;
  top++;
}

StackType Stack::pop() {

  if (top == 0)
    throw ContainerEmptyException();

  top--;

  return data[top];					// can also return data[--top];
}

StackType Stack::peek() {

  if (top == 0)
    throw ContainerEmptyException();

  return data[top-1];
}

