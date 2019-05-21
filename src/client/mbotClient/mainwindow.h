#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include "Client.h"
#include <iostream>



using boost::asio::ip::udp;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *ev)
    {

           int key = ev->key();
           switch(key)
           {
           case Qt::Key_Left:
           case Qt::Key_Up:
           case Qt::Key_Down:
           case Qt::Key_Right:
               std::cout<<key<<" sent!"<<std::endl;
               break;
           default:
               return;
           }/*
           Qt::Key_Left	0x01000012
           Qt::Key_Up	0x01000013
           Qt::Key_Right	0x01000014
           Qt::Key_Down	0x01000015	 */
           client->send_cmd(key, cmd_ep);

    }


private:
    Ui::MainWindow *ui;
    Client *client;
    udp::endpoint cmd_ep;
    boost::asio::io_service io;
    QLabel *imageLabel;


};

#endif // MAINWINDOW_H
