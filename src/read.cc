#include<string>
#include<vector>
#include<tuple>
#include<iostream>
#include<cassert>
#include<algorithm>
#include"lisp.h"
#include"lisp.cc"

LispObject make_cons(const LispObject &first, const LispObject &last) {
  LispObject *car = new LispObject, *cdr = new LispObject;
  *car = first, *cdr = last;
  LispCons* cons = new LispCons(car, cdr);
  LispObject obj((LispObject*)cons, CONS);
  return obj;
}

LispObject get_car(LispObject obj) {
  if (obj.type != CONS) throw 1;
  LispCons pair = *(LispCons*)(obj.value);
  return *pair.car;
}

LispObject get_cdr(LispObject obj) {
  if (obj.type != CONS) throw 1;
  LispCons pair = *(LispCons*)(obj.value);
  return *pair.cdr;
}

LispObject lisp_object(Result res) { return std::get<0>(res); }
int reader_pt(Result res) { return std::get<1>(res); }

bool isignorable(const char &c) {
  return c == ' ' || c == '\n' || c == '\t';
}

Result read(std::string prog, int p) {
  while (isignorable(prog[p])) { ++p; }
  if (isdigit(prog[p])) {
    int* num = new int;
    *num = 0;
    while (isdigit(prog[p])) {
      *num = (*num) * 10 + (prog[p] - '0');
      ++p;
    }
    LispObject obj((LispObject*)num, INT);
    return Result(obj, p);
  } else if (prog[p] == '(') {
    ++p;
    std::vector<LispObject> objs;
    while (prog[p] != ')') {
      Result res = read(prog, p);
      objs.push_back(lisp_object(res));
      p = reader_pt(res);
    }
    ++p;
    LispObject val;
    if (objs.empty()) { return Result(val, p); }
    std::reverse(objs.begin(), objs.end());
    for (LispObject obj: objs) { val = make_cons(obj, val); }
    return Result(val, p);
  }
  assert(false);
}

std::string tostring(LispObject obj) {
  int val;
  std::string expr;
  switch (obj.type) {
    case INT:
      val = *(int*)obj.value;
      return std::to_string(val);
    case CONS:
      expr = "(";
      //expr += tostring(get_car(obj));
      std::cout << std::hex << ((LispCons*)obj.value)->car << std::endl;
      expr += " ";
      //expr += tostring(get_cdr(obj));
      std::cout << std::hex << ((LispCons*)obj.value)->cdr << std::endl;
      expr += ")";
      return expr;
    case NIL:
      return "nil";
  }
  assert(false);
}

int main() {
  std::string prog;
  while (std::cout << "> ", std::cin >> prog) {
    Result res = read(prog, 0);
    std::cout << tostring(lisp_object(res)) << std::endl;
    delete_object(lisp_object(res));
  }
  return 0;
}
