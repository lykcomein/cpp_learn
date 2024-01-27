#ifndef __LAMBDA_H__
#define __LAMBDA_H__
extern void use_lambda_old();
extern void use_lambda2();
extern void use_lambda3();
extern void use_function();
extern void use_bind();
extern void use_ref();
#include <string>
using namespace std;
class BindTestClass
{
public:
   BindTestClass(int num_, string name_) : num(num_), name(name_) {}
   static void StaticFun(const string & str, int age);
   void MemberFun(const string & job, int score);

public:
   int num;
   string name;
};
#endif