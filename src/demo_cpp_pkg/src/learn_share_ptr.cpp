#include "rclcpp/rclcpp.hpp"
#include <memory>
#include <iostream>
int main(int argc, char const *argv[])
{
    auto p1 = std::make_shared<int>(1);
    auto p2 = p1;

    return 0;
}
