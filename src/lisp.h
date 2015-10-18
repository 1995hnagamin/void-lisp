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
void delete_object(LispObject obj);

LispObject make_int(int* num);
LispObject make_cons(LispObject left, LispObject right);

LispObject get_car(LispObject obj);
LispObject get_cdr(LispObject obj);
#endif
