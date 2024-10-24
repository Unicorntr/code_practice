#include <QApplication>
#include <QLabel>
#include<QString>
#include <rclcpp/rclcpp.hpp>
#include <status_interfaces/msg/sys_status.hpp>

using SystemStatus = status_interfaces::msg::SysStatus;

class SystemStatusDisplay : public rclcpp::Node 
{
private:
    rclcpp::Subscription<SystemStatus>::SharedPtr subscription_;
    QLabel *label_;
public:

    SystemStatusDisplay() : Node("system_status_display") {
        label_ = new QLabel();
        // 创建订阅者
        auto subscription = this->create_subscription<SystemStatus>(
            "system_status", 10, [&]()(const SystemStatus::SharedPtr msg) {
                label_->setText(get_qstr_from_msg(msg));
        });
        label_->setText(QString::fromStdString(msg->status));
        label_->show();
    }
    QString get_qstr_from_msg(const SystemStatus::SharedPtr msg )
    {
        std::stringstream ss;
        ss << "系统状态可视化" << msg->status << std::endl;
        return QString::fromStdString("Hello Qt!");
    }
};
int main(int argc, char **argv) {
    // 创建 QApplication 对象
    QApplication app(argc, argv);

    // 创建 QLabel 对象并设置文本
    QLabel label("Hello Qt!");
    label.show();

    // 执行应用程序，阻塞代码直到应用程序退出
    return app.exec();
}