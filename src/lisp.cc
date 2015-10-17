#include"lisp.h"

LispObject::LispObject() : value(NULL), type(NIL) {;}

LispObject::LispObject(LispObject* value, ObjType type) :
  value(value), type(type) {;}

LispObject::LispObject(const LispObject &obj) {
  value = obj.value;
  type = obj.type;
}

LispCons::LispCons() : car(NULL), cdr(NULL) {;}

LispCons::LispCons(const LispCons &obj) :
  car(NULL), cdr(NULL) {
  car = (LispObject*)(new LispCons);
  cdr = (LispObject*)(new LispCons);
}

LispCons::LispCons(LispObject* left, LispObject* right) :
  car(left), cdr(right) {;}

void delete_object(const LispObject &obj) {
  LispCons *pair;
  switch (obj.type) {
    case NIL:
      break;
    case INT:
      delete (int*)obj.value;
      break;
    case CONS:
      pair = (LispCons*)obj.value; 
      delete_object(*pair->car);
      delete_object(*pair->cdr);
  }
}
