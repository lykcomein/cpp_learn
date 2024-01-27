一、数组；(C11)
1、类型别名简化数组指针：
   using int_array = int [4];
   int_array是一个包含四个元素的整形数组类型
   typedef int int_array_same[4];
   与using等价，int_array_same是一个包含四个元素的整形数组类型；
2、begin,end:获取数组第一个元素地址和最后一个元素的下一个位置

二、变量与输出：
1、constexpr：声明为constexpr的变量一定是一个常量；(值不会改变且编译过程中就能得到计算结果)；
  而const是在运行中变量不能被修改；
  (constexpr关键字帮助编译器进行编译时优化，因为它允许编译器在编译期间计算表达式，这样可以减少运行时的计算量，并可能减少程序的大小和运行时间);
  对于指针，const int *q与constexpr int *p 的区别;
  q可以被修改，但是q指向的值*q不能变；
  而p恰好相反，p指向的值*p可以变，但p不能变；
2、using：using newd = double;
   表示newd与double是相同的；
3、decltype(exp):获取exp类型；(decltpye并不对其操作数求值)
