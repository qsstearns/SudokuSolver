#ifndef _STACK_H
#define _STACK_H

#include "exceptions.h"

const int STACK_SIZE = 64;

typedef int StackType;

class Stack {
 public:
  Stack();
  ~Stack();

  bool isEmpty();
  int size();

  void clear();

  void push(const StackType &);
  StackType pop();
  StackType peek();

 private:
  StackType
    data[STACK_SIZE];
  int
    top;
};

#endif

