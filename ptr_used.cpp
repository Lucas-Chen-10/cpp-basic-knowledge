#include <iostream>
#include <memory>

class Test;
class Test2;

class Test
{
    public:
    Test()
    {
        std::cout << "Test()..." << std::endl;
    }

    ~Test()
    {
        std::cout << "~Test()..." << std::endl;
    }

    public:
    std::shared_ptr<Test2> ptr; //模拟循环引用
};

class Test2
{
    public:
    Test2()
    {
        std::cout << "Test2()..." << std::endl;
    }

    ~Test2()
    {
        std::cout << "~Test2()..." << std::endl;
    }

    public:
    std::shared_ptr<Test> ptr; //模拟循环引用
};

int main()
{
    std::shared_ptr<Test> ptr(new Test());
    std::cout << "ptr引用计数：" << ptr.use_count() << std::endl;
    std::shared_ptr<Test> ptr1 = ptr;
    std::cout << "ptr1引用计数：" << ptr1.use_count() << std::endl;

    //同时引用同一个对象
    Test *p = new Test();
    std::shared_ptr<Test> ptr2(p);
    std::cout << "ptr2引用计数：" << ptr2.use_count() << std::endl;
    /*1.shared_ptr多次引用同一数据，会导致两次释放同一内存，引起core dump
    std::shared_ptr<Test> ptr3(p);    
    std::cout << "ptr3引用计数：" << ptr3.use_count() << std::endl;*/
    std::shared_ptr<Test> ptr4(ptr2);
    std::cout << "ptr4引用计数：" << ptr4.use_count() << std::endl;

    
    /*2.禁止给智能指针赋值或者拷贝构造函数
    std::shared_ptr<Test> ptr5 = p; //error: conversion from ‘Test*’ to non-scalar type ‘std::shared_ptr<Test>’ requested
    std::shared_ptr<Test> ptr5; //mismatched types ‘std::unique_ptr<_Tp, _Dp>’ and ‘Test*’
    ptr5 = p;*/

    /*3.循环引用
    两个对象互相使用一个 shared_ptr 成员变量指向对方。这样会引发一个问题，其中任何一个对象的引用计数都为2。
    析构时两个资源引⽤计数会减⼀，于是两者引⽤计数还是大于0，导致跳出函数时资源没有被释放（离开作用域时两个对象的析构函数没有被调⽤）*/
    {
        std::shared_ptr<Test> ptr6(new Test);
        std::shared_ptr<Test2> ptr7(new Test2);
        std::cout << "ptr6引用计数：" << ptr6.use_count() << std::endl;  //1
        std::cout << "ptr7引用计数：" << ptr7.use_count() << std::endl;  //1
        ptr6->ptr = ptr7;
        ptr7->ptr = ptr6;
        std::cout << "ptr6引用计数：" << ptr6.use_count() << std::endl;  //2
        std::cout << "ptr7引用计数：" << ptr7.use_count() << std::endl;  //2
    }

    /*=======================weak_ptr使用======================*/
    std::cout << "=======================weak_ptr使用======================" << std::endl;
    /*weak_ptr使用*/
    std::shared_ptr<Test> ptr8(new Test);
    std::weak_ptr<Test> ptr9(ptr8);
    std::cout << "ptr8引用计数：" << ptr8.use_count() << std::endl;  //1
    std::cout << "ptr9引用计数：" << ptr9.use_count() << std::endl;  //1
    ptr8.reset(); //销毁ptr8
    std::cout << "ptr9是否被销毁：" << (ptr9.expired() ? "是" : "否") << std::endl; //ptr9已经被销毁
    /*循环引用的案例里面，可以使用weak_ptr解决，这样就不会再次计数
    将类中的std::shared_ptr<Test2> ptr;替换为std::weak_ptr<Test2> ptr;
    std::shared_ptr<Test> ptr;替换为std::weak_ptr<Test> ptr;*/

    /*=======================unique_ptr======================*/
    std::cout << "=======================unique_ptr======================" << std::endl;
    /*unique_ptr使用*/
    {
        std::unique_ptr<int> t1(new int(1));//ok
        //std::unique_ptr<int> up2 = new int(1);//error: conversion from ‘int*’ to non-scalar type ‘std::unique_ptr<int>’ requested
        int* pw = new int;
        std::unique_ptr<int> t2(pw);//ok
        /*不可以对unique_ptr执行copy或者assign操作，只能move*/
        //std::unique_ptr<int> t3(pw);//free(): double free detected in tcache 2,这个是运行期错误，程序员必须避免这样的失误
	    //std::unique_ptr<int> t4(t2);// error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
	    std::unique_ptr<int> t5(move(t2));//ok  
    }

    return 0;
}