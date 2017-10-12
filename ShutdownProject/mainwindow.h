#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * Shutdown Interface
 * Nathan Ahrens
 * Sept. 29 2017
 *
 * This program serves as a program to allow the user to graphically select when to shutdown the computer.
 */

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDateTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QFrame>

#include <shutdownthread.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton *shutdownButton;
    QPushButton *cancelButton;
    QPushButton *exitButton;
    ShutdownThread *shutdownThread;
    QDateTimeEdit *dateTimeEdit;
    QLabel *currentTime;
    QLabel *remainingTime;
    QDateTime *timeSet;
    QSpinBox *hoursSpinner;
    QSpinBox *minutesSpinner;
    QSpinBox *secondsSpinner;
    QRadioButton *timeRadioButton;
    QRadioButton *countdownRadioButton;
    QWidget *timeWidget;

    void createWindow();
    void updateTime();
    int calculateHours() const;
    int calculateMinutes() const;
    int calculateSeconds() const;
    void closeWindow();
    bool running;

private slots:
    void shutdownClicked();
    void cancelClicked();
    void exitClicked();
    void radioChanged();

protected:
    virtual void closeEvent(QCloseEvent *);

};

#endif // MAINWINDOW_H
