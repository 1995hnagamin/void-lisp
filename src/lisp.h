#include<tuple>

#ifndef __LISP_H_INCLUDED__
#define __LISP_H_INCLUDED__

enum ObjType {
  INT, CONS, NIL
};

struct LispObject {
  void* value;
  ObjType type;
  
  LispObject();
  LispObject(const LispObject &obj);
  LispObject(LispObject* value, ObjType type);
};

struct LispCons {
  LispObject* car;
  LispObject* cdr;
  
  LispCons();
  LispCons(const LispCons &obj);
  LispCons(LispObject* car, LispObject* cdr);
};

typedef std::tuple<LispObject, int> Result;

#endif
