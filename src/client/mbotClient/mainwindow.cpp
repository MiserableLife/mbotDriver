#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImageReader>

using boost::asio::ip::tcp;
using boost::asio::ip::address;


static void image_to_label(unsigned char* image, QLabel* label)
{
    /*
    QImage img(image, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_STEP, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img);
    label->setPixmap(pixmap);*/
   /* label->setPixmap(
                QPixmap::fromImage(
                    QImage( image, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_STEP, QImage::Format_RGB888)));*/
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    imageLabel(new QLabel),
    client(nullptr),
    cmd_ep(address::from_string("127.0.0.1"),COMMAND_PORT)
{
    //cvtColor(img, img, CV_BGR2RGB);

/*
    imageLabel->setPixmap(
                QPixmap::fromImage(
                    QImage(img.data, img.cols, img.rows, img.step,
  QImage::Format_RGB888)));*/
    std::function<void(unsigned char*)> handle_image = std::bind(image_to_label, std::placeholders::_1, imageLabel);

    client = new Client(io, tcp::endpoint(address::from_string("127.0.0.1"), SERVER_PORT ),handle_image);
    std::thread t([this]()
    {
        io.run();
    });
    t.detach();
    QString filename("dogzzing.jpg");
    QImageReader reader(filename);
    imageLabel->setPixmap(QPixmap::fromImage(reader.read()));


    ui->setupUi(this);
    setCentralWidget(imageLabel);
}

MainWindow::~MainWindow()
{
    delete imageLabel;
    delete client;
    delete ui;
}
