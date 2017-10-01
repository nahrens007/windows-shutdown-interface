#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{

}


void MainWindow::countdown(int hours, int minutes, int seconds)
{

    long long int t_seconds = seconds + (minutes * 60) + (hours * 60 * 60);
    long long int t_loop = t_seconds;
    int hrs,mins,secs;

    for(long long int i = t_loop; i > 0; i--)
    {
        // clear screen from current displays


        //calculate the new hrs, mins, and secs
        hrs = t_seconds / (60 * 60);

        long long int tmpHrs = hrs * 60;
        mins = (t_seconds / 60) - tmpHrs;

        secs = t_seconds % 60;

        // display time left
        //printf("Time until shutdown: %d:%02d:%02d\n", hrs, mins, secs);

        // update t_seconds, since we have passed one second.
        t_seconds--;

        // delay 1 second
    }


    return;
}

// Slot for shutdown button clicked
void shutdownClicked() const
{
    // Start the shutdown timer process
}

// Slot for cancel button clicked
void cancelClicked() const
{
    // Kill the shutdown timer process

}

// Slot for exit button clicked
void MainWindow::exitClicked()
{
    this->close();
    return;
}
