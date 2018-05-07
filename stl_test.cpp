#include <iostream>
#include <memory>
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



int main()
{
    shared_ptr< uy_t > test = new uy_t[10];





    return 0;
}