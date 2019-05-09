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
           std::cout<< ev->text().toUtf8().data()<<" pressed!"<<std::endl;
           client->send_cmd(ev->key(), cmd_ep);

    }


private:
    Ui::MainWindow *ui;
    Client *client;
    udp::endpoint cmd_ep;
    boost::asio::io_service io;
    QLabel *imageLabel;


};

#endif // MAINWINDOW_H
