#include"../inc/lambda_.h"
#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <thread>

using namespace std;
typedef void(*P_NameFunc)(string name);
vector<function<void(string)>> vec_Funcs;
void use_lambda_old()
{
  //1匿名调用
  [](string name)
  {
    cout << "this is anonymous" << endl;
    cout << "hello " << name << endl;
  }("zack");

  //2通过auto赋值
  auto fname = [](string name)->string
  {
    cout << "this is auto " << endl;
    cout << "hello " << name << endl;
    return "hello world!"; 
  };
  fname("Vivo");

  //函数指针
  P_NameFunc fname2 = [](string name)
  {
    cout << "this is P_NameFunc" << endl;
    cout << "hello " << name << endl;
  };
  fname2("Vivo2");

  //function
  function<void(string)> funcName;
  funcName = [](string name)
  {
    cout << "this is function " << endl;
    cout << "hello " << name << endl;
  };
  funcName("Uncle Wang");

}

void use_lambda2()
{
  int age = 33;
  string name = "Zack";
  int score = 100;
  string job = "softengineer";

  //值捕获
  [age, name](string name_)
  {
    cout << "age is " << age << "name is " << name << " self-name is " << name_ << endl;
  }("Novia");
  // 上述lambda表达式捕获了age和name，是以值的方式来捕获的。所以无法在lambda表达式内部修改age和name的值，如果修改age和name，编译器会报错.
  
  //引用捕获
  [&age, &name](string name_)
  {
    cout << "age is " << age << " name is " << name << " self-name is" << name_ << endl;
    name = "Xiao Li";
    age = 18;
  }("Novia");
  cout << "name is " << name << " age is " << age << endl;
  
  vec_Funcs.push_back([age, name](string name_)
                    {   cout << "this is value catch " << endl;
                        cout << "age is " << age << " name is " << name << " self-name is " << name_ << endl; });
  //危险，不要捕获局部变量的引用
  // vec_Funcs.push_back([&age, &name](string name_)
  //                     {   cout << "this is referenc catch" << endl;
  //                         cout << "age is " << age << " name is " << name << " self-name is " << name_ << endl; });

  //全部用值捕获， name 用引用捕获
  [=, &name]()
  {
      cout << "age is " << age << " name is " << name << " score is " << score << " job is " << job << endl;
      name = "Cui Hua";
  }();

  //全部用引用捕获，只有name用值捕获
  [&, name]()
  {
      cout << "age is " << age << " name is " << name << " score is " << score << " job is " << job << endl;
  }();
}

void use_lambda3()
{
  for(auto f : vec_Funcs)
  {
    f("zack");
  }
}

class FuncObj
{
public:
  void operator()(string str)
  {
    cout << "this is func obj " << str << endl;
  }
};

void globalFun(string str)
{
  cout << "this is global " << str << endl;
}

void globalFunc2(string name, int age, int score, string job)
{
  cout << "name is " << name << " age is " << age << " score is " << score << " job is " << job << endl;
}

void use_function()
{
  list<function<void(string)>> list_Funcs;
  //存储函数对象
  list_Funcs.push_back(FuncObj());
  //存储lambda表达式
  list_Funcs.push_back([](string str)
                { cout << "this is lambda call " << str << endl; });
  //存储全局函数
  list_Funcs.push_back(globalFun);

  for (const auto &f : list_Funcs)
  {
      f("hello zack");
  }

}

//Bind
void BindTestClass::StaticFun(const string &str, int age)
{
  cout << "this is static function" << endl;
  cout << "name is " << str << endl;
  cout << "age is " << age << endl;
}
void BindTestClass::MemberFun(const string &job, int score)
{
  cout << "this is member function" << endl;
  cout << "name is " << name << endl;
  cout << "age is " << num << endl;
  cout << "job is " << job << endl;
  cout << "score is " << score << endl;
}

void use_bind()
{
  //绑定全局函数
  auto newfun1 = bind(globalFunc2, placeholders::_1, placeholders::_2, 98, "worker");
  //相当于调用globalFun2("Lily",22, 98,"worker");
  newfun1("Lily", 22);
  //多传参数没有用，相当于调用globalFun2("Lucy",28, 98,"worker");
  newfun1("Lucy", 28, 100, "doctor");
  auto newfun2 = bind(globalFunc2, "zack", placeholders::_1, 100, placeholders::_2);
  //相当于调用globalFun2("zack",33,100,"engineer");
  newfun2(33, "engineer");
  auto newfun3 = bind(globalFunc2, "zack", placeholders::_2, 100, placeholders::_1);
  //相当于globalFunc2("zack", 33, 100, "coder");
  newfun3("coder", 33);

  //绑定类的静态成员函数,加不加&都可以
  // auto staticbind = bind(BindTestClass::StaticFun, placeholders::_1, 33);
  auto staticbind = bind(&BindTestClass::StaticFun, placeholders::_1, 33);
  staticbind("zack");
  BindTestClass bindTestClass(33, "zack");
  // 绑定类的成员函数,一定要传递对象给bind的第二个参数，可以是类对象，也可以是类对象的指针
  // 如果要修改类成员，必须传递类对象的指针
  auto memberbind = bind(BindTestClass::MemberFun, &bindTestClass, placeholders::_1, placeholders::_2);
  memberbind("coder", 100);

  auto memberbind2 = bind(BindTestClass::MemberFun, placeholders::_3, placeholders::_1, placeholders::_2);
  memberbind2("coder", 100, &bindTestClass);

  //对象必须取地址
  auto numbind = bind(&BindTestClass::num, placeholders::_1);
  std::cout << numbind(bindTestClass) << endl;

  // function接受bind返回的函数
  function<void(int, string)> funcbind = bind(globalFunc2, "zack", placeholders::_1, 100, placeholders::_2);
  funcbind(33, "engineer");

  // function接受bind 成员函数
  function<void(string, int)> funcbind2 = bind(BindTestClass::MemberFun, &bindTestClass, placeholders::_1, placeholders::_2);
  funcbind2("docker", 100);

  function<void(string, int, BindTestClass *)> funcbind3 = bind(BindTestClass::MemberFun, placeholders::_3, placeholders::_1, placeholders::_2);
  funcbind3("driver", 100, &bindTestClass);

  // function 直接接受成员函数,function的模板列表里第一个参数是类对象引用
  function<void(BindTestClass &, const string &, int)> functomem = BindTestClass::MemberFun;
  functomem(bindTestClass, "functomem", 88);

  // function 绑定类的静态成员函数
  function<void(const string &)> funbindstatic = bind(&BindTestClass::StaticFun, placeholders::_1, 33);
  funbindstatic("Rolis");
}
void modify_name(std::string &name, int age)
{
  name = "zack";
  age = 34;
}

void thread_ref(int &a)
{
  a = 1024;
}

void use_ref()
{
  std::string name = "rolin";
  int age = 25;
  auto bind_value = bind(modify_name, name, age);
  bind_value();
  cout << "name is " << name << " age is "
        << age << endl;
  function<void(void)> bind_ref = bind(modify_name, ref(name), ref(age));
  bind_ref();
  cout << "name is " << name << " age is "
        << age << endl;

  //必须用ref传递，否则编译失败
  // thread trf(thread_ref, age);
  // trf.join();
  // cout << "age is " << age << endl;

  thread trf2(thread_ref, ref(age));
  trf2.join();
  cout << "age is " << age << endl;
}

