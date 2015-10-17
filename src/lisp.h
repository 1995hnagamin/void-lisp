#include<tuple>

#ifndef __LISP_H_INCLUDED__
#define __LISP_H_INCLUDED__

typedef void* LispObject;

enum ObjType {
  NIL = 0, INT, CONS
};

struct LispCons {
  LispObject car;
  LispObject cdr;
};

typedef std::tuple<LispObject, int> Result;

ObjType typeof(LispObject obj);

LispObject entity(LispObject obj);

#endif
