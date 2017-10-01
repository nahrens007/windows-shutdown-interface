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
#include <QAction>
#include <QLabel>

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
    void countdown(int hours, int minutes, int seconds);
    void createWindow();

private slots:
    void shutdownClicked() const;
    void cancelClicked() const;
    void exitClicked();
};

#endif // MAINWINDOW_H
