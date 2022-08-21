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

    /*3.循环引用*/
    {
        std::shared_ptr<Test> ptr6(new Test);
        std::shared_ptr<Test2> ptr7(new Test2);
        std::cout << "ptr6引用计数：" << ptr6.use_count() << std::endl;
        std::cout << "ptr7引用计数：" << ptr7.use_count() << std::endl;
        ptr6->ptr = ptr7;
        ptr7->ptr = ptr6;
        std::cout << "ptr6引用计数：" << ptr6.use_count() << std::endl;
        std::cout << "ptr7引用计数：" << ptr7.use_count() << std::endl;
    }

    return 0;
}