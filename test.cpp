#include "uy_shared_ptr.h"
#include <functional>
#include <string>
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






void test_default_construct()
{
    uy_shared_ptr<uy_t> test;
}

void test_point_construct()
{
    uy_shared_ptr<uy_t> test(new uy_t);
}

void test_copy_construct()
{
    uy_shared_ptr<int> base(new int(100));
    uy_shared_ptr<int> copy(base);
    cout<<*base<<endl;
}

void test_operator_equal()
{
    uy_shared_ptr<double> base(new double(6.66));
    uy_shared_ptr<double> target;
    target = base;
    cout<<*base<<endl;
}

void test_porator_xing()
{
    uy_shared_ptr<float> test(new float(99.99));
    cout<<*test<<endl;
}
struct base
{
    string name;
    double height;
    double weight; 
};

void test_operator_jiantou()
{
    uy_shared_ptr<base> test(new base{"uncleyuan",179,62});
    cout<<test->name<<endl<<test->height<<endl<<test->weight<<endl;
}

void test_swap()
{
    uy_shared_ptr<int> test1(new int(100));
    uy_shared_ptr<int> test2(new int(200));
    cout<<"test1 = "<<*test1<<endl;
    cout<<"test2 = "<<*test2<<endl;
    cout<<"after test1.swap(test2)"<<endl;
    test1.swap(test2);
    cout<<"test1 = "<<*test1<<endl;
    cout<<"test2 = "<<*test2<<endl;
    
}

void test_make_shared()
{
    uy_shared_ptr<base> test = make_shared<base>(base{"uncleyuan",179,62});
    cout<<test->name<<endl<<test->height<<endl<<test->weight<<endl;
}


void test_count()
{
    uy_shared_ptr<uy_t> test(new uy_t);
    cout<<"count = "<<test.count()<<endl;
    uy_shared_ptr<uy_t> other = test;
    cout<<"count = "<<test.count()<<endl;
}

template <class T>
void my_deleter(T * ptr)
{
    cout<<"my_deleter()"<<endl;
    delete ptr;
}


void test_deleter()
{
    uy_shared_ptr<base> test(new base{"uncleyuan",179,62},my_deleter<base>);
    cout<<test->name<<endl<<test->height<<endl<<test->weight<<endl;

}



int main()
{
    test_default_construct();
    test_point_construct();
    test_copy_construct();
    test_make_shared();
    test_porator_xing();
    test_operator_equal();
    test_operator_jiantou();
    test_swap();
    test_count();
    test_deleter();

    return 0;
}