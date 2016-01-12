#include <iostream>
#include <vector>
#include "Matrix.hpp"
#include "Complex.h"

using namespace std;


template<class T>
class vec{
public:

    vec(int t):_v(t,T(0)),_a(t)
    {
        for (std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

    }

    vec():vec(2)
    {
        for (std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

    }

    vec(std::vector<T>& inp): _v(inp.begin(),inp.end())
    {
        for (std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it)
        std::cout << ' ' << *it;
        std::cout << '\n';

    }

     T& operator()(unsigned int row)
    {
        return this->_v[row];
    }


private:
    std::vector<T> _v;
    int _a;
};

int main() {
    Complex c(0);
//    cout<<c;

    std::vector<int> first = {1,2,3,4,5,6};
    std::vector<int> second = {2,5,1,-2,2,4};

    Matrix <int> one();


    Matrix <int> tow(2,3);
    tow(1,1)=18;
    tow = tow.trans();

   // Matrix <int> three(tow);


    Matrix <int> four(3,2,first);
    Matrix <int> fourt(2,3,second);
    Matrix<int> five = fourt+four;
   // Matrix<int> six = fourt-four;
  cout<<five;

}