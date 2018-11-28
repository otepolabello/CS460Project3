#include "Object.h"

Object listop_ex1()
{
return cons(listop("car", "x y z"), listop("cdr", "a b c 1 2 3"));
}

Object listop_ex2()
{
return cons(listop("cadr", "x y z"), listop("cdddr", "a b c 1 2 3"));
}

int main()
{
cout << listop_ex1(); cout << endl;
cout << listop_ex2(); cout << endl;
return 0;
}
