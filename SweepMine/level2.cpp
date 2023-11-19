#include "level2.h"

Level2::Level2(QWidget *parent)
    : QMainWindow{parent}
{
    //数据初始化
    rows = 16;
    bombNum = 40;
    unPressNum = rows*rows;
    numCount = bombNum;

    setFixedSize(780,880);
    setWindowIcon(QIcon(":/res/bomb.bmp"));
    setWindowTitle("Sweep Mines Level2");

    menu = menuBar();

    menu->addMenu(game);
    menu->addSeparator();
    menu->addMenu(help);

    game->addAction(restart);
    game->addSeparator();
    game->addMenu(selectLevel);
    game->addSeparator();
    game->addAction(exitGame);

    selectLevel->addAction(Level01);
    selectLevel->addSeparator();
    selectLevel->addAction(Level02);
    selectLevel->addSeparator();
    selectLevel->addAction(Level03);
    selectLevel->addSeparator();

    help->addAction(about);

    timeLabel = new QLabel("时间",this);
    timeLabel->move(74+20,50);

    bombLabel = new QLabel("雷数",this);
    bombLabel->move(74+40*rows-70+20,50);

    connect(about,&QAction::triggered,this,[=](){
        QMessageBox::about(this,"本软件信息","<html><font size='4' color='red'>制作者：XuanYe</font><br><font size='4' color='blue'>美术资源：网络+部分修改</font><br><font size='4' color='blue'>开发工具：Qt Creator 11.0.3</font><br><font size='4' color='black'>版本信息：0.0.1</font></html>");
    });

    connect(exitGame,&QAction::triggered,this,[=](){
        this->close();
    });

    connect(restart,&QAction::triggered,this,[=](){
        forbidFlag = 1;
        unPressNum = rows*rows;
        numCount = bombNum;
        gameStatus = 0;
        gameTime->stop();
        currentTime = 0;
        hd->reData(rows,Data);
        dialogFlag = 0;
        update();
        forbidFlag = 0;
    });

    connect(Level01,&QAction::triggered,this,[=](){
        Level1 *L1 = new Level1;
        L1->setGeometry(this->geometry().x()+140,this->geometry().y()+140,500,600);
        this->hide();
        L1->show();
    });

    connect(Level02,&QAction::triggered,this,[=](){
        Level2 *L2 = new Level2;
        L2->setGeometry(this->geometry());
        this->hide();
        L2->show();
    });

    connect(Level03,&QAction::triggered,this,[=](){
        Level3 *L3 = new Level3;
        L3->setGeometry(this->geometry().x()-140,this->geometry().y()-60,980,1050);
        this->hide();
        L3->show();
    });

    frame = new QFrame(this);
    frame->setFrameShape(QFrame::Panel);
    frame->move(74,150);
    frame->setFixedSize(40*rows,40*rows);

    hd->addBomb(rows,bombNum,Data);

    installEventFilter(this);

    gameTime = new QTimer(this);

    connect(gameTime,&QTimer::timeout,this,[=](){
        currentTime++;
        update();
    });
}

bool Level2::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this) {
        if (event->type() == QEvent::HoverMove)
        {

            QHoverEvent *hoverEvent = static_cast<QHoverEvent*>(event);
            int x = hoverEvent->pos().x();
            int y = hoverEvent->pos().y();

            if(x>74 && x<74+40*rows && y>150 && y<150+40*rows)
            {
                hoverPoint = hd->computePos(x,y);

                // 重绘界面
                update();
            }

        } else if (event->type() == QEvent::HoverLeave) {
            // 清除当前悬浮的格子的坐标
            hoverPoint = QPoint();

            // 重绘界面
            update();
        }else if(event->type() == QEvent::MouseButtonPress){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            int x = mouseEvent->x();
            int y = mouseEvent->y();
            if (mouseEvent->button() == Qt::LeftButton)
            {

                if(x>74 && x<74+40*rows && y>150 && y<150+40*rows){
                    leftPoint = hd->computePos(x,y);

                    update();
                }

            }
            else if (mouseEvent->button() == Qt::RightButton)
            {

                if(x>74 && x<74+40*rows && y>150 && y<150+40*rows){
                    rightPoint = hd->computePos(x,y);

                    update();

                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void Level2::paintEvent(QPaintEvent *)// 16*16 40
{

    if(gameStatus == 1 && dialogFlag == 0){

        gameTime->stop();
        dialogFlag =1;

        QMessageBox msgBox;
        msgBox.setWindowTitle("恭喜！！！");
        msgBox.setText("<font size='6' color='blue'>游戏胜利</font>");
        msgBox.setInformativeText(QString("<font size='6' color='blue'>用时：%1s</font>").arg(currentTime)); // 在这里你可以输出计时器的值
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, "重新开始");
        msgBox.setButtonText(QMessageBox::Cancel, "关闭");
        msgBox.setWindowIcon(QIcon(":/res/bomb.bmp"));

        int ret = msgBox.exec();

        while(1){
            if(ret == QMessageBox::Ok){
                unPressNum = rows*rows;
                numCount = bombNum;
                gameStatus = 0;
                currentTime = 0;
                hd->reData(rows,Data);
                dialogFlag = 0;
                break;
            }else{
                break;
            }
        }
    }
    else if(gameStatus == -1 && dialogFlag == 0){

        gameTime->stop();
        dialogFlag = 1;

        QMessageBox msgBox;
        msgBox.setWindowTitle("游戏结束！！！");
        msgBox.setText("<font size='6' color='red'>游戏失败</font>");
        msgBox.setInformativeText(QString("<font size='6' color='red'>用时：%1s</font>").arg(currentTime)); // 在这里你可以输出计时器的值
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, "重新开始");
        msgBox.setButtonText(QMessageBox::Cancel, "关闭");
        msgBox.setWindowIcon(QIcon(":/res/bomb.bmp"));

        boom->play();

        int ret = msgBox.exec();

        while(1){
            if(ret == QMessageBox::Ok){
                unPressNum = rows*rows;
                numCount = bombNum;
                gameStatus = 0;
                currentTime = 0;
                hd->reData(rows,Data);
                dialogFlag = 0;
                break;
            }else{
                break;
            }
        }

        boom->stop();

    }

    QPainter *painter = new QPainter(this);
    QPixmap pix;

    //border
    pix.load(":/res/border1.bmp");
    painter->drawPixmap(74,80,pix.width(),pix.height(),pix);
    painter->drawPixmap(74+40*rows-pix.width(),80,pix.width(),pix.height(),pix);

    //border1-1
    int f = currentTime/100;
    int s = (currentTime/10)%10;
    int t = currentTime%10;

    QString str =QString(":/res/figure%1.bmp").arg(f);
    pix.load(str);
    painter->drawPixmap(74+5,84,pix.width(),pix.height()+3,pix);

    str =QString(":/res/figure%1.bmp").arg(s);
    pix.load(str);
    painter->drawPixmap(74+5+pix.width(),84,pix.width(),pix.height()+3,pix);

    str =QString(":/res/figure%1.bmp").arg(t);
    pix.load(str);
    painter->drawPixmap(74+5+pix.width()*2,84,pix.width(),pix.height()+3,pix);

    //border1-2
    f = numCount/10;
    s = numCount%10;

    str =QString(":/res/figure%1.bmp").arg(f);
    pix.load(str);
    painter->drawPixmap(74+40*rows-65,84,pix.width()+10,pix.height()+3,pix);

    str =QString(":/res/figure%1.bmp").arg(s);
    pix.load(str);
    painter->drawPixmap(74+40*rows-65+pix.width()+10,84,pix.width()+10,pix.height()+3,pix);

    //border2
    pix.load(":/res/border2.bmp");
    painter->drawPixmap(374,80,pix.width(),pix.height(),pix);

    if(gameStatus == 0){
        pix.load(":/res/ing.bmp");
        painter->drawPixmap(374+5,80+5,pix.width()+6,pix.height()+6,pix);
    }
    else if(gameStatus == -1){
        pix.load(":/res/fail.bmp");
        painter->drawPixmap(374+5,80+5,pix.width()+6,pix.height()+6,pix);
    }
    else{
        pix.load(":/res/win.bmp");
        painter->drawPixmap(374+5,80+5,pix.width()+6,pix.height()+6,pix);
    }

    int x = 74,y = 150;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<rows;j++)
        {
            if((*Data)[i][j].first == 1){ pix.load(":/res/flag.bmp"); }
            else if((*Data)[i][j].first == 2){
                int order = (*Data)[i][j].second;
                QString str =QString(":/res/icon%1.bmp").arg(order);
                pix.load(str);
            }
            else{ pix.load(":/res/blank.bmp"); }
            if(gameStatus == -1){
                if((*Data)[i][j].second == -1 && (*Data)[i][j].first != 2){
                    if((*Data)[i][j].first == 1){
                        pix.load(":/res/flagBomb.bmp");
                    }
                    else{
                        pix.load(":/res/bomb.bmp");
                    }
                }
                else if((*Data)[i][j].second != -1 && (*Data)[i][j].first == 1){
                    pix.load(":/res/flagError.bmp");
                }
            }
            else if(gameStatus == 1){
                if((*Data)[i][j].second == -1 && (*Data)[i][j].first != 2){
                    if((*Data)[i][j].first == 1){
                        pix.load(":/res/flagBomb.bmp");
                    }
                    else{
                        pix.load(":/res/bomb.bmp");
                    }
                }
            }
            painter->drawPixmap(x,y,pix.width()*2,pix.height()*2,pix);
            x += 40;
        }
        x = 74;
        y += 40;
    }

    if(!hoverPoint.isNull()&&(*Data)[hoverPoint.y() - 1][hoverPoint.x() - 1].first != 2 && gameStatus == 0){
        if((*Data)[hoverPoint.y() - 1][hoverPoint.x() - 1].first == 1){
            pix.load(":/res/flagHighLight.bmp");
        }
        else {
            pix.load(":/res/blankHighLight.bmp");
        }
        x = 74 + (hoverPoint.x() - 1) * 40;
        y = 150 + (hoverPoint.y() - 1) * 40;
        painter->drawPixmap(x,y,pix.width()*2,pix.height()*2,pix);
    }

    if(!leftPoint.isNull() && (*Data)[leftPoint.y() - 1][leftPoint.x() - 1].first != 1 && gameStatus == 0 &&forbidFlag == 0){
        if(unPressNum == rows*rows){
            gameTime->start(1000);
        }

        int order = (*Data)[leftPoint.y() - 1][leftPoint.x()-1].second;

        if((*Data)[leftPoint.y() - 1][leftPoint.x() - 1].first == 0){

            if(order == -1){
                gameStatus = -1;
            }

            else if(order == 0){
                hd->recursiveSearch(leftPoint.y() - 1,leftPoint.x()-1,rows,unPressNum,Data);
            }
            else{
                unPressNum--;
            }
            (*Data)[leftPoint.y() - 1][leftPoint.x()-1].first = 2;
        }
        else if((*Data)[leftPoint.y() - 1][leftPoint.x() - 1].first == 2){
            hd->Check(leftPoint.y() - 1,leftPoint.x()-1,rows,unPressNum,gameStatus,Data);
        }

        QString str =QString(":/res/icon%1.bmp").arg(order);
        pix.load(str);

        x = 74 + (leftPoint.x() - 1) * 40;
        y = 150 + (leftPoint.y() - 1) * 40;
        painter->drawPixmap(x,y,pix.width()*2,pix.height()*2,pix);

        leftPoint = QPoint();

        if(unPressNum == bombNum && gameStatus!=-1){
            gameStatus = 1;
        }

        update();
    }

    if(!rightPoint.isNull() && (*Data)[rightPoint.y() - 1][rightPoint.x()-1].first != 2 && gameStatus == 0){
        if((*Data)[rightPoint.y() - 1][rightPoint.x()-1].first == 1 && numCount<bombNum){
            pix.load(":/res/blank.bmp");
            (*Data)[rightPoint.y() - 1][rightPoint.x()-1].first = 0;
            numCount++;
        }
        else if((*Data)[rightPoint.y() - 1][rightPoint.x()-1].first != 1 && numCount>0){
            pix.load(":/res/flag.bmp");
            (*Data)[rightPoint.y() - 1][rightPoint.x()-1].first = 1;
            numCount--;
        }
        x = 74 + (rightPoint.x() - 1) * 40;
        y = 150 + (rightPoint.y() - 1) * 40;
        painter->drawPixmap(x,y,pix.width()*2,pix.height()*2,pix);

        rightPoint = QPoint();
        update();
    }

    delete painter;
}
