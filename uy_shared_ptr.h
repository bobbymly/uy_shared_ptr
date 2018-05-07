#include <iostream>
#include <atomic>
#include <functional>
using namespace std;


// class DefaultDeleter
// {
// public:
//     template <class T>
//     void operator ()(T* ptr)
//     {
//         delete ptr;
//     }
// };


// 默认删除器 ，在使用动态数组时应自定义一个删除器，数组期待的是 delete[]
template<class T>
void DefaultDeleter(T* ptr)
{
    delete ptr;
}


//直接管理对象指针的核心类
template <class T>
class uy_shared_ptr_base
{
public:

    explicit uy_shared_ptr_base(T* target,function<void(T*)> deleter_ = DefaultDeleter<T>):point(target),count(1),deleter(deleter_){   }

    T* get(){  return point;}

    void hold(){  count++;}

    bool release()
    {
        count--;
        if(!count) destroy();
        return 0 == count;
    }

    T* operator -> (){  return point;}

    T& operator * (){  return *point;}

    unsigned int counts(){   return count.load();}

    void destroy()
    {
        //point -> ~T();
        deleter(point);
    }


private:
    T* point = NULL;

    //使用 atomic 保证对引用计数操作的原子性，为多线程环境下的线程安全做准备
    atomic<unsigned int> count;
    function<void (T*)>deleter;



};



template <class T>
class uy_shared_ptr
{
public:
    explicit uy_shared_ptr():base(new uy_shared_ptr_base<T>( new T())){    }


    uy_shared_ptr(T* target,function<void(T*)> deleter_ = DefaultDeleter<T>):base(new uy_shared_ptr_base<T>(target,deleter_) ){    }

    uy_shared_ptr(const uy_shared_ptr<T>& target):base(target.base){  base -> hold(); }

    uy_shared_ptr_base<T> * get(){  return base->get();}
    
    T* operator -> (){ return base -> operator -> ();}
    
    T& operator * (){   return **base;}

    template <class T2>
    explicit uy_shared_ptr(const uy_shared_ptr<T2> &target)
    {
        base -> release();
        base = target.base;
        base -> hold();
    }


    template <class T2>
    uy_shared_ptr<T>& operator = (uy_shared_ptr<T2> &target)
    {
        base -> release();
        base = target.base;
        base -> hold();
        return *this;
    }

    bool reset()
    {
        return base -> release();
    }

    bool reset(const T& target)
    {   
        base ->relese();
        base = target.base;
        base -> hold();

    }

    unsigned int count(){   return base->counts();}

    ~uy_shared_ptr()
    {
        base -> release();
    }


    
private:
    uy_shared_ptr_base<T> *base; 
};


template <class T,class ... Args>
static uy_shared_ptr<T> make_shared(Args&&... args)
{
    T *ptr = new T(std::forward<T>(args)...);
    return uy_shared_ptr<T>(ptr);
}