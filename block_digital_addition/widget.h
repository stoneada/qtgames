#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:   //添加槽函数进行弹窗
    void buttonIsOnClick();
    int generateRandomNumber(int maxVal);
    QList<int> generateRandomNumber2(int maxVal);
    QList<int> generateUniqueRandomNumber(int parMaxVal);
    int computerMinVal(QList<int> array);
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
