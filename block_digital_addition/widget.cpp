#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTime>
#include <ctime>
int sum;
int select=0;
int selectVal=0;
QPushButton *selButton;
QPushButton *sumButton;
int startVal=7;
int uMatrix=16;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString texts[] = {"1", "2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"};
    QList<int> list = generateUniqueRandomNumber(startVal);
    for(int a=0;a<list.size();a++){
        int number = list.at(a);
        if(number>5){
            while(number>5){
                number = generateRandomNumber(5);
            }
            list[a]=number;
        }
    }
    for(int i=0;i<list.size();i++){
        texts[i]=QString::number(list.at(i));
    }
    qDebug()<<"first:"+QString::number(list.size());
    this->setWindowTitle("QGridLayout");
    this->resize(600, 600);
    QHBoxLayout *topLayout = new QHBoxLayout;
    sumButton = new QPushButton(this);
    sumButton->setStyleSheet("text-align: center;background-color: rgb(255, 255, 255);font-size:55px;");
    sum = generateRandomNumber(startVal);
    sumButton->setText(QString::number(sum));
    sumButton->setFixedHeight(80);
    sumButton->setFixedWidth(80);
    QLabel *lbl = new QLabel(QWidget::tr("请选择两个按钮进行计算，计算的结果之和为:"), this);
    topLayout->addWidget(lbl);
    lbl->setBuddy(sumButton);
    topLayout->addWidget(lbl);
    topLayout->addWidget(sumButton);

    QList<int> alllist;
    list=generateRandomNumber2(startVal);
    alllist.append(list);
    list=generateRandomNumber2(startVal);
    alllist.append(list);
    qDebug()<<"second:"+QString::number(alllist.size());
    int k=0;
    for(int i=startVal+1;i<uMatrix;i++){
        texts[i]=QString::number(alllist.at(k));
        k++;
    }

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(2);
    gridLayout->setMargin(2);
    for(int i=0, k = 0; i < 4;i++,k+=4)
    {
        for(int j = 0; j < 4;j++)
        {
            QPushButton *button = new QPushButton(texts[k+j]);
            button->setObjectName("numbutton"+texts[k+j]);
            button->setFixedHeight(80);
            button->setStyleSheet("text-align: center;background-color: rgb(255, 128, 64);font-size:45px;");
            connect(button, SIGNAL(clicked()), this, SLOT(buttonIsOnClick()));
            gridLayout->addWidget(button,i,j);
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(gridLayout);
    this->setLayout(mainLayout);

    //三个按钮的信号都关联到 FoodIsComing 槽函数
    //connect(ui->pushButtonAnderson, SIGNAL(clicked()), this, SLOT(FoodIsComing()));
    //connect(ui->pushButtonBruce, SIGNAL(clicked()), this, SLOT(FoodIsComing()));
    //connect(ui->pushButtonCastiel, SIGNAL(clicked()), this, SLOT(FoodIsComing()));
}
int  Widget::generateRandomNumber(int maxVal)
{
    int r=0;
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    r=qrand()%maxVal;
    return r;
}
QList<int>  Widget::generateRandomNumber2(int maxVal)
{
    QList<int> numbersList;
    maxVal=maxVal/2;
    numbersList=generateUniqueRandomNumber(maxVal);
    return numbersList;
}
QList<int> Widget::generateUniqueRandomNumber(int parMaxVal)
{
    int i,j;
    parMaxVal++;
    QList<int> numbersList;
    srand((unsigned)time(0));
    for(i=0;i<parMaxVal;i++)
    {
        numbersList.append(qrand()%parMaxVal);
        bool flag=true;
        while(flag)
        {
           for(j=0;j<i;j++)
           {
               if(numbersList[i]==numbersList[j])
               {
                   break;
               }
           }
           if(j<i)
           {
               numbersList[i]=rand()%parMaxVal;
           }
           if(j==i)
           {
               flag=!flag;
           }
       }
    }

    for(i=0;i<parMaxVal;i++)
    {
        qDebug()<<"last:"+QString::number(numbersList[i]);
    }
    return numbersList;
}
int disappear_num=0;
void Widget::buttonIsOnClick()
{
    //获取信号源头对象的名称
    QString strObjectSrc = this->sender()->objectName();

    qDebug()<<strObjectSrc; //打印源头对象名称
    //将要显示的消息
    QString strMsg;
    //判断是哪个按钮发的信号
    QPushButton *btn=qobject_cast<QPushButton*>(sender());
    qDebug()<<btn->text();
    QString val=btn->text();
    bool ok;
    int dVal = val.toInt(&ok,10);
    select++;
    if(select==1){
        selectVal=dVal;
        selButton=btn;
    }else if(select == 2){
        selectVal+=dVal;
        if(selectVal==sum){
            btn->setVisible(false);
            btn->setEnabled(false);
            selButton->setVisible(false);
            selButton->setEnabled(false);
            disappear_num++;
            qDebug()<<"disappear_num:"+QString::number(disappear_num);
            if(disappear_num==8){
                QMessageBox::information(this, tr("通关"), "恭喜你通过测试");
                return;
            }
            sum = generateRandomNumber(startVal);
            while(disappear_num<4 && sum<2){
                sum = generateRandomNumber(startVal);
            }
            sumButton->setText(QString::number(sum));

            select=0;
            selectVal=0;


            QObjectList list = children();
            QList<int> iteList;

            if(disappear_num>3){
                foreach (QObject *obj, list) {
                    if (obj->metaObject()->className() == QStringLiteral("QPushButton")){
                        QPushButton *b = qobject_cast<QPushButton*>(obj);
                        QString str = b->objectName();
                        if(str.startsWith("numbutton") && b->isEnabled()){
                            QString tval=b->text();
                            int tmpVal = tval.toInt();
                            iteList.append(tmpVal);
                        }
                    }
                }

                for(int a=0;a<iteList.size();a++)
                {
                    qDebug()<<"computer:"+QString::number(iteList[a]);
                }
                sum = computerMinVal(iteList);
                sumButton->setText(QString::number(sum));
            }
        }else{
            QMessageBox::information(this, tr("计算错误"), QString::number(sum)+";请重新选择;"+QString::number(selectVal));
            select=0;
            selectVal=0;
            return;
        }
    }

    /****
    if( "pushButtonAnderson" == strObjectSrc )
    {
        strMsg = tr("Hello Anderson! Your food is coming!");
    }
    else if( "pushButtonBruce" == strObjectSrc )
    {
        strMsg = tr("Hello Bruce! Your food is coming!");
    }
    else if( "pushButtonCastiel" == strObjectSrc )
    {
        strMsg = tr("Hello Castiel! Your food is coming!");
    }
    else
    {
        //do nothing
        return;
    }***********/
    //显示送餐消息
    //QMessageBox::information(this, tr("Food"), strMsg);
}

int  Widget::computerMinVal(QList<int> array)
{
    QList<int> iteList,minList;
    int len = array.size();
    for(int i=0;i<len;i++){
        for(int k=i+1;k<len;k++){
            int total = array[i]+array[k];
            iteList.append(total);
            if(startVal>total){
                minList.append(total);
            }
        }
    }
    if(minList.size()>0){
        return minList[minList.size()-1];
    }else{
        qSort(iteList.begin(), iteList.end());
        return iteList[0];
    }
    return 0;
}
Widget::~Widget()
{
    delete ui;
}
