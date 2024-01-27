1、noexcept：表明函数不会发生异常；
2、引用折叠；
  折叠规则
  X&  & ,X&  && 都会被折叠为X&
  X&&  && 会被折叠为X&&
3、完美转换；(forward)
4、可变参数模板
   template<class... T>
   省略号的作用有两个：
  1.声明一个参数包T... args，这个参数包中可以包含0到任意个模板参数；
  2.在模板定义的右边，可以将参数包展开成一个一个独立的参数。
5、shared_ptr:接受参数为指针，由于接受单一指针作为唯一实参的构造函数是explicit，即拒绝隐式转换，所以不可以使用赋值符；
   即：shared_ptr<string> pNico = new string("nico"); //错误
   只可以shared<string> pNico(new string("nico"))；
   或：shared<string> pNico = make_shared<string>("nico");
   对于shared_ptr，我的理解：
   对指针进行了一次包装，它提供了operator*与operator->，可以使用get()获得被shared_ptr包裹的指针；
6、移动构造函数：如为string类定义一个构造函数：
  string(string&& string) noexpect {}
  它从给定对象“窃取”资源而不是拷贝资源；
  注意：一个类默认给声明了一个移动构造函数；
7、decltype(exp):获取exp类型；
8、万能引用：存在于模板中；
   template<typename T>
   void test(T&& t){
   }
   T&&就是万能引用；
9、尾随返回类型：
   一个函数声明:
   auto test(type1 a, type2 b)->int;
   说明test的返回值是int
