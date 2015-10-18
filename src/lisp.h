#include<tuple>
#include<string>

#ifndef __LISP_H_INCLUDED__
#define __LISP_H_INCLUDED__

typedef void* LispObject;

enum ObjType {
  NIL = 0, INT, CONS, SYMBOL
};

struct LispCons {
  LispObject car;
  LispObject cdr;
};

struct LispSymbol {
  std::string name;
  LispObject value;
  LispObject function;
};

typedef std::tuple<LispObject, int> Result;
ObjType typeof(LispObject obj);
LispObject entity(LispObject obj);
void delete_object(LispObject obj);

LispObject make_int(int* num);
LispObject make_cons(LispObject left, LispObject right);
LispObject make_symbol(const std::string &name);

LispObject get_car(LispObject obj);
LispObject get_cdr(LispObject obj);
#endif
