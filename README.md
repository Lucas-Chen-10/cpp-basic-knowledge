# cpp-basic-knowledge

## 虚析构函数
虚析构函数是为了解决基类的指针指向派生类对象，并用基类的指针删除派生类对象。先调用子类析构函数，再调用基类析构函数，防止内存泄漏。

- [virtual-func](https://github.com/Lucas-Chen-10/cpp-basic-knowledge/blob/main/virtual-func.cpp)
执行结果如下：
```
Animal()
Dog()
Dog run()
~Dog()
~Animal()
```

## 智能指针
C++11标准中引入了shared_ptr、unique_ptr、weak_ptr三种不同类型的智能指针。智能指针是为了管理针内存，防止发生内存泄漏而存在的。

### shared_ptr
它是一个标准的共享所有权的智能指针, 允许多个指针指向同一个对象， 定义在 memory 文件中。
```cpp
shared_ptr<T> ptr(new T); 
```
#### 原理
1. 它是通过引用计数的方式来实现多个shared_ptr对象之间共享资源
2. 在它内部维护了一份计数，用来记录该资源被几个对象共享
3. 析构函数调用时，计数会减1
4. 如果引用计数为0，则释放该资源

#### 简单使用
基本语法和常见错误使用情况
- [shared_ptr_used](https://github.com/Lucas-Chen-10/cpp-basic-knowledge/blob/main/shared_ptr_used.cpp)

#### 简单实现shared_ptr
实现一个线程安全的shared_ptr智能指针
- [shared_ptr](https://github.com/Lucas-Chen-10/cpp-basic-knowledge/blob/main/shared_ptr.cpp)

### weak_ptr
它指向一个由 shared_ptr 管理的对象而不影响所指对象的生命周期，也就是将一个 weak_ptr 绑定到一个 shared_ptr 不会改变 shared_ptr 的引用计数。
```cpp
weak_ptr<T> ptr(new T); 
```

#### 简单使用
- [shared_ptr_used](https://github.com/Lucas-Chen-10/cpp-basic-knowledge/blob/main/shared_ptr_used.cpp)