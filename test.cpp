#include "uy_shared_ptr.h"
using namespace std;


class uy_t 
{
public:
    uy_t()
    {
        cout<<"uy_t()"<<endl;
    }

    void t_func()
    {
        cout<<"test the operator -> , sucess"<<endl;
    }

    ~uy_t()
    {
        cout<<"~uy_t()"<<endl;
    }
};

template <class T>
void func2(uy_shared_ptr<T> t)
{
    cout<<"counts = "<<t.count()<<endl;

    
}

void func1()
{
    

    uy_shared_ptr<uy_t> test;
    test -> t_func();


    cout<<"counts = "<<test.count()<<endl;


    cout<<" func2 begin"<<endl;
    func2(test);
    

    cout<<" func2 end"<<endl;
    cout<<"counts = "<<test.count()<<endl;
    
    
}



int main()
{
    {
        cout<<"func1 begin"<<endl;
        func1();
        cout<<"func1 end"<<endl;
    }
    cout<<"over"<<endl;





    return 0;
}