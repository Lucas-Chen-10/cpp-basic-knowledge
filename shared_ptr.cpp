#include <iostream>
#include <mutex>

using namespace std;

template <class T>
class shared_ptr
{
    public:
    //普通类初始化
    shared_ptr(T *ptr = nullptr):_pPtr(ptr),_pRefCount(new unsigned int(1)),_pMutex(new mutex())
    {}

    //智能指针初始化
    explicit shared_ptr(const shared_ptr<T> & sp):
        _pPtr(sp._pPtr),
        _pRefCount(sp._pRefCount),
        _pMutex(sp._pMutex)
        {
            AddRefCount();
        }

    ~shared_ptr()
    {
        Release();
    }

    shared_ptr<T> & operator=(shared_ptr<T> & ptr)
    {
        if(_pPtr != ptr._pPtr)
        {
            //释放旧资源
            Release();
            //共享新资源
            _pPtr = ptr._pPtr;
            _pRefCount = ptr._pRefCount;
            //计数器+1
            AddRefCount();

        }

        return *this;
    }

    T& operator* ()
    {
        return *_pPtr;
    }

    T* operator-> ()
    {
        return _pPtr;
    }

    unsigned int UseCount() {return *_pRefCount;}

    T * Get(){return _pPtr;}

    private:
    void Release()
    {
        bool bFlag = false;
        //如果计数器为0，则释放资源，否则计数器递减
        //多线程访问，加锁限制
        _pMutex->lock();
        if(--(*_pRefCount) == 0)
        {
            delete _pRefCount;
            delete _pPtr;

            bFlag = true;
        }

        _pMutex->unlock();
        if(bFlag) delete _pMutex;
    }

    void AddRefCount()
    {
        _pMutex->lock();
        ++(*_pRefCount);
        _pMutex->unlock();
    }


    private:
    T *_pPtr;
    unsigned int *_pRefCount;
    mutex *_pMutex;
};

int main()
{
    shared_ptr<int> p(new int);
    cout << "user_cout:" << p.UseCount() << endl;

    char *p1 = new char(1);
    shared_ptr<char> p2(p1);
    cout << "user_cout:" << p2.UseCount() << endl;

    shared_ptr<char> p3(p2);
    cout << "user_cout:" << p3.UseCount() << endl;

    //shared_ptr<int> p4(new char);
    //cout << "user_cout:" << p4.UseCount() << endl;

    return 0;
}