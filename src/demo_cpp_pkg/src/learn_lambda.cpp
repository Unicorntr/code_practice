#include<iostream>
#include<algorithm>

int main()
{
    auto f = [](int a, int b) { return a + b; };
    int sum = f(1, 2);
    auto print_sum = [sum]() { std::cout << sum << std::endl; };
    print_sum(); 
    return 0;
}
