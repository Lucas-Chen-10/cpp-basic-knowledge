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

