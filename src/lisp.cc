#include"lisp.h"

void delete_object(LispObject obj) {
  LispCons *pair;
  switch (typeof(obj)) {
    case NIL:
      break;
    case INT:
      delete (int*)entity(obj);
      break;
    case CONS:
      pair = (LispCons*)(entity(obj)); 
      delete_object(pair->car);
      delete_object(pair->cdr);
  }
}

ObjType typeof(LispObject obj) {
  uintptr_t tag = (uintptr_t)obj & 7;
  return (ObjType)tag;
}

LispObject entity(LispObject obj) {
  uintptr_t ent = (uintptr_t)obj & ~7;
  return (LispObject)ent;
}

LispObject make_int(int* num) {
  uintptr_t obj = (uintptr_t)num | INT;
  return (LispObject)obj;
}

LispObject make_cons(LispObject first, LispObject last) {
  LispCons* obj = new LispCons;
  *obj = {first, last};
  return (LispObject)(((uintptr_t)obj) | CONS);
}

LispObject get_car(LispObject obj) {
  LispCons pair = *(LispCons*)(entity(obj));
  return pair.car;
}

LispObject get_cdr(LispObject obj) {
  LispCons pair = *(LispCons*)(entity(obj));
  return pair.cdr;
}
