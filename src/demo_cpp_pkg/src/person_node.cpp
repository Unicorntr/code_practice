#include"rclcpp/rclcpp.hpp"
class PersonNode : public rclcpp::Node
{
private:
    std::string name_;
    int age_;

public:
    PersonNode(const std::string &node_name,const std::string &name,const int & age):Node(node_name)
    {
        this->name_ = name;
        this->age_ = age;
    };

    void eat(const std::string &food_name)
    {
        RCLCPP_INFO(this->get_logger(),"%d 的%s eat %s",this->age_,this->name_.c_str(),food_name.c_str());
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PersonNode>("person_node","zhang",18);
    node->eat("apple");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}