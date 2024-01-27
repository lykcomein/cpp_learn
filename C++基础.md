一、数组；
1、类型别名简化数组指针：
   using int_array = int [4];
   int_array是一个包含四个元素的整形数组类型
   typedef int int_array_same[4];
   与using等价，int_array_same是一个包含四个元素的整形数组类型