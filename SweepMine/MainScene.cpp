#include "MainScene.h"
#include"level1.h"
#include"level2.h"
#include"level3.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(400,400);
    setWindowIcon(QIcon(":/res/bomb.bmp"));
    setWindowTitle("Sweep Mines");

    menu = menuBar();

    menu->addMenu(game);
    menu->addSeparator();
    menu->addMenu(help);

    game->addMenu(selectLevel);
    game->addSeparator();

    selectLevel->addAction(Level01);
    selectLevel->addSeparator();
    selectLevel->addAction(Level02);
    selectLevel->addSeparator();
    selectLevel->addAction(Level03);
    selectLevel->addSeparator();

    help->addAction(about);

    Level1 *L1 = new Level1;

    connect(about,&QAction::triggered,this,[=](){
        QMessageBox::about(this,"本软件信息","<html><font size='4' color='red'>制作者：XuanYe</font><br><font size='4' color='blue'>美术资源：网络+部分修改</font><br><font size='4' color='blue'>开发工具：Qt Creator 11.0.3</font><br><font size='4' color='black'>版本信息：0.0.1</font></html>");
    });

    connect(Level01,&QAction::triggered,this,[=](){
        L1->setGeometry(this->geometry().x()-100,this->geometry().y()-200,500,600);
        this->hide();
        L1->show();
    });

    connect(Level02,&QAction::triggered,this,[=](){
        Level2 *L2 = new Level2;
        L2->setGeometry(this->geometry().x()-200,this->geometry().y()-240,780,880);
        this->hide();
        L2->show();
    });

    connect(Level03,&QAction::triggered,this,[=](){
        Level3 *L3 = new Level3;
        L3->setGeometry(this->geometry().x()-300,this->geometry().y()-300,980,1050);
        this->hide();
        L3->show();
    });

    QPushButton *startBtn = new QPushButton("开始游戏");
    startBtn->setParent(this);
    startBtn->setFixedSize(100,50);
    startBtn->move(this->width()/2 - startBtn->width()/2,this->height()/4 - startBtn->height()/4);
    connect(startBtn,&QPushButton::clicked,this,[=](){
        this->hide();
        L1->show();
    });

    QPushButton *exitBtn = new QPushButton("退出游戏");
    exitBtn->setParent(this);
    exitBtn->setFixedSize(100,50);
    exitBtn->move(this->width()/2 - exitBtn->width()/2,(this->height()/4)*3 - exitBtn->height());

    connect(exitBtn,&QPushButton::clicked,this,[=](){
        this->close();
    });

}

