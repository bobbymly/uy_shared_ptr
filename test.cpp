#include "uy_shared_ptr.h"
using namespace std;


class uy_t 
{
public:
    uy_t()
    {
        cout<<"uy_t()"<<endl;
    }


    uy_t(const uy_t & target)
    {
        cout<<"copy uy_t"<<endl;
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
    

    uy_shared_ptr<uy_t> test(new uy_t());
    test -> t_func();


    cout<<"counts = "<<test.count()<<endl;


    cout<<" func2 begin"<<endl;
    func2(test);
    cout<<"counts = "<<test.count()<<endl;
    uy_shared_ptr<uy_t> test3 = test;
    

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

    uy_shared_ptr<uy_t> test = make_shared<uy_t>();

    uy_shared_ptr<int> test_int = make_shared<int>(60);

    cout<<"test operator * "<<endl<<*test_int<<endl;


    return 0;
}