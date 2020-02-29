
#include <iostream>
#include <vector>

typedef double type;

type epsilon = 0.0000000000001;
type delta;
type a_0 = 0, b_0 = 0;

using namespace std;

type func(type x)
{
   return pow(x - 15, 2) + 5; // Это не точно
}

void method_dih()
{
   type center_of_interval = (b_0 + a_0) / 2;
   vector<type> a, b, x1, x2;
   a[0] = a_0;
   b[0] = b_0;

}

void method_sech()
{

}

int main()
{
    
}
