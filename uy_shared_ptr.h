#include <iostream>
#include <atomic>
using namespace std;

template <class T>
class uy_shared_ptr_base
{
public:
    uy_shared_ptr_base(T* target):point(target),count(1){   }
//    uy_shared_ptr_base(uy_shared_ptr_base<T> target):point(target.point),count(){   }
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
        delete point;
    }


private:
    T* point = NULL;
    atomic<unsigned int> count;




};


template <class T>
class uy_shared_ptr
{
public:
    uy_shared_ptr():base(new uy_shared_ptr_base<T>( new T())){    }
    uy_shared_ptr(const T& target):base(new uy_shared_ptr_base<T>(new T(target)) ){ }
    uy_shared_ptr(uy_shared_ptr<T>& target):base(target.base){  base -> hold(); }

    uy_shared_ptr_base<T> * get(){  return base;}
    
    operator -> (){ return base->operator -> ();}
    
    T& operator * (){   return **base;}

    template <class T2>
    uy_shared_ptr(const uy_shared_ptr<T2> target)
    {
        base -> release();
        base = target.base;
        base -> hold();
    }


    template <class T2>
    uy_shared_ptr<T>& operator = (uy_shared_ptr<T2> target)
    {
        base -> release();
        base = target.get();
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