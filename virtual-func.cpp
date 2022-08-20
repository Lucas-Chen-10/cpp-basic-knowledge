#include <iostream>

class Animal
{
    public:
        Animal()   //析构函数不能为虚函数
        {
            std::cout<<"Animal()"<<std::endl;
        }
        virtual ~Animal() //虚析构函数
        {
            std::cout<<"~Animal()"<<std::endl;
        }
        virtual void run()
        {
            std::cout<<"Animal run()"<<std::endl;
        }
};

class Dog : public Animal
{
    public:
    Dog()   //析构函数不能为虚函数
    {
        std::cout<<"Dog()"<<std::endl;
    }
    virtual ~Dog() //虚析构函数
    {
        std::cout<<"~Dog()"<<std::endl;
    }
    virtual void run()
    {
        std::cout<<"Dog run()"<<std::endl;
    }
};


int main()
{
    Animal *pDog = new Dog();
    pDog->run();


    delete pDog;
    pDog = NULL;

    return 0;

}