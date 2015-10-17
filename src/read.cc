#include<string>
#include<vector>
#include<tuple>
#include<iostream>
#include<cassert>
#include<algorithm>
#include"lisp.h"
#include"lisp.cc"

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
    return Result(make_int(num), p);
  } else if (prog[p] == '(') {
    ++p;
    std::vector<LispObject> objs;
    while (prog[p] != ')') {
      Result res = read(prog, p);
      objs.push_back(lisp_object(res));
      p = reader_pt(res);
    }
    ++p;
    LispObject val = NULL;
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
  switch (typeof(obj)) {
    case INT:
      val = *(int*)(entity(obj));
      return std::to_string(val);
    case CONS:
      expr = "(";
      expr += tostring(get_car(obj));
      expr += " ";
      expr += tostring(get_cdr(obj));
      expr += ")";
      return expr;
    case NIL:
      return "nil";
  }
  assert(false);
}

int main() {
  std::string prog;
  while (std::cout << "> " << std::flush, getline(std::cin, prog)) {
    Result res = read(prog, 0);
    std::cout << tostring(lisp_object(res)) << std::endl;
    delete_object(lisp_object(res));
  }
  return 0;
}
