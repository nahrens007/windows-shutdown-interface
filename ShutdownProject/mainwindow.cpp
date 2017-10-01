#include "mainwindow.h"
#include <iostream>
using namespace  std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->createWindow();

    this->shutdownThread = new ShutdownThread;
}

MainWindow::~MainWindow()
{

}

void MainWindow::createWindow()
{
    // create buttons and add their slots
    shutdownButton = new QPushButton("&Shutdown");
    cancelButton = new QPushButton("&Cancel");
    exitButton = new QPushButton("E&xit");
    connect(shutdownButton, SIGNAL(clicked()), this, SLOT(shutdownClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitClicked()));

    dateTimeEdit = new QDateTimeEdit;
    dateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(3600));

    QHBoxLayout *dateTimeLayout = new QHBoxLayout;
    dateTimeLayout->addWidget(new QLabel("Date and Time:"));
    dateTimeLayout->addWidget(dateTimeEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(shutdownButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(exitButton);

    this->centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(dateTimeLayout);
    mainLayout->addLayout(buttonLayout);

    this->centralWidget->setLayout(mainLayout);

    this->setCentralWidget(this->centralWidget);
}

// Slot for shutdown button clicked
void MainWindow::shutdownClicked()
{
    // Start the shutdown timer process
    cout << dateTimeEdit->dateTime().toString().toStdString() << endl;
    this->shutdownThread->setDateTime(dateTimeEdit->dateTime());
    this->shutdownThread->start();
    return;
}

// Slot for cancel button clicked
void MainWindow::cancelClicked() const
{
    // Kill the shutdown timer process
    this->shutdownThread->cancelShutdown();
    return;
}

// Slot for exit button clicked
void MainWindow::exitClicked()
{
    this->close();
    return;
}

/*
int ShutdownThread::getHours() const
{
    // Calculate and return hours
    return QDateTime::currentDateTime().secsTo(time) / (60 * 60);
}

int ShutdownThread::getMinutes() const
{
    qint64 t_seconds = QDateTime::currentDateTime().secsTo(time);
    return (t_seconds / 60) - (t_seconds / (60 * 60)) * 60;
}

int ShutdownThread::getSeconds() const
{
    return QDateTime::currentDateTime().secsTo(time) % 60;
}
*/
