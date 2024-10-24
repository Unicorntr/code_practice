#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;

class TurtlrControlNode : public rclcpp::Node
{
public:
    TurtlrControlNode(const std::string& node_name) : Node(node_name)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        // timer_ = this->create_wall_timer(500ms, std::bind(&TurtlrControlNode::timer_callback, this));
        subscriber_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, 
            std::bind(&TurtlrControlNode::pose_callback, this,std::placeholders::_1));
    }  
    void pose_callback(const turtlesim::msg::Pose::SharedPtr pose)
    {
        //1.获取当前位置
        auto current_x = pose->x;
        auto current_y = pose->y;
        RCLCPP_INFO(this->get_logger(), "当前位置: %f, current_y: %f", current_x, current_y);

        //2.计算偏差
        auto distance = sqrt(pow(current_x - target_x_, 2) + pow(current_y - target_y_, 2));
        auto angle = std::atan2((target_y_ - current_y),(target_x_ - current_x)) - pose->theta;

        //3.控制策略
        auto message = geometry_msgs::msg::Twist();
        if(distance > 0.1)
        {
            if(fabs(angle)> 0.1){
                message.angular.z = fabs(angle);
            } else {
                message.linear.x = k_ * distance;
            }
        }
        if(message.linear.x > max_speed_){
            message.linear.x = max_speed_;
        }
        publisher_->publish(message);
    }

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    // rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;
    double target_x_ = {2.0};
    double target_y_ = {2.0};
    double k_{1.0};//比例系数
    double max_speed_ = {3.0};
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtlrControlNode>("turtlr_Control"));
  rclcpp::shutdown();
  return 0;
}