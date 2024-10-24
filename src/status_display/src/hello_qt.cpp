#include <QApplication>
#include <QLabel>

int main(int argc, char **argv) {
    // 创建 QApplication 对象
    QApplication app(argc, argv);

    // 创建 QLabel 对象并设置文本
    QLabel label("Hello Qt!");
    label.show();

    // 执行应用程序，阻塞代码直到应用程序退出
    return app.exec();
}