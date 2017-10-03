#include "mainwindow.h"
#include <iostream>
#include <QtConcurrent/QtConcurrent>

using namespace  std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // ensure that the time set is null
    this->timeSet = 0;
    this->running = true;
    // create the GUI window
    this->createWindow();

    // instantiate the shutdown thread, but do not create it.
    this->shutdownThread = new ShutdownThread;

}

MainWindow::~MainWindow()
{
    // delete all pointers
    delete timeRadioButton;
    delete countdownRadioButton;
    delete shutdownButton;
    delete cancelButton;
    delete exitButton;
    delete shutdownThread;
    delete dateTimeEdit;
    delete currentTime;
    delete remainingTime;
    delete timeSet;
    delete hoursSpinner;
    delete minutesSpinner;
    delete secondsSpinner;
}

void MainWindow::createWindow()
{
    /* create and format GUI components */

    /* Radio button for whether we are shutting down in x amount of time
     * or at a specified date/time */
    QGroupBox *groupBox = new QGroupBox;
    timeRadioButton = new QRadioButton(tr("Time"));
    countdownRadioButton = new QRadioButton(tr("Countdown"));

    timeRadioButton->setChecked(true);

    QHBoxLayout *radioButtonLayout = new QHBoxLayout;
    radioButtonLayout->addWidget(timeRadioButton);
    radioButtonLayout->addWidget(countdownRadioButton);
    groupBox->setLayout(radioButtonLayout);

    /*
     * QInputDialogs for hours, minutes, and seconds of countdown
     */
    hoursSpinner = new QSpinBox;
    minutesSpinner = new QSpinBox;
    secondsSpinner = new QSpinBox;
    hoursSpinner->setMinimum(0);
    minutesSpinner->setMinimum(0);
    secondsSpinner->setMinimum(0);
    hoursSpinner->setValue(0);
    minutesSpinner->setValue(0);
    secondsSpinner->setValue(0);

    QHBoxLayout *spinnerLayout = new QHBoxLayout;
    spinnerLayout->addWidget(new QLabel("Hours:"));
    spinnerLayout->addWidget(hoursSpinner);
    spinnerLayout->addWidget(new QLabel("Minutes:"));
    spinnerLayout->addWidget(minutesSpinner);
    spinnerLayout->addWidget(new QLabel("Seconds:"));
    spinnerLayout->addWidget(secondsSpinner);

    // Create and format the DateTime selector
    dateTimeEdit = new QDateTimeEdit;
    dateTimeEdit->setDisplayFormat("MM/dd/yyyy hh:mm:ss");
    dateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(3600));

    // Layout for the date/time selector
    QHBoxLayout *dateTimeLayout = new QHBoxLayout;
    dateTimeLayout->addWidget(new QLabel("Date and time:"));
    dateTimeLayout->addWidget(dateTimeEdit);

    // Label for the current time
    currentTime = new QLabel;
    currentTime->setFont(QFont("Arial", 10, -1, false));
    // Layout for the current time
    QHBoxLayout *currentTimeLayout = new QHBoxLayout;
    currentTimeLayout->addWidget(new QLabel("Current time:"));
    currentTimeLayout->addWidget(currentTime);

    // Label for the remaining time
    remainingTime = new QLabel;
    remainingTime->setFont(QFont("Arial", 10, -1, false));

    // Layout for the remaining time
    QHBoxLayout *remainingTimeLayout = new QHBoxLayout;
    remainingTimeLayout->addWidget(new QLabel("Remaining time:"));
    remainingTimeLayout->addWidget(remainingTime);

    // create buttons and add their slots
    shutdownButton = new QPushButton("&Shutdown");
    cancelButton = new QPushButton("&Cancel");
    exitButton = new QPushButton("E&xit");

    // connect the button signals with the slots
    connect(shutdownButton, SIGNAL(clicked()), this, SLOT(shutdownClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitClicked()));

    // Layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(shutdownButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(exitButton);

    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    // Add everything to the main layout
    this->centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(new QLabel("Specific time"));
    mainLayout->addLayout(dateTimeLayout);
    mainLayout->addWidget(line);
    mainLayout->addWidget(new QLabel("Countdown time"));
    mainLayout->addLayout(spinnerLayout);
    mainLayout->addLayout(currentTimeLayout);
    mainLayout->addLayout(remainingTimeLayout);
    mainLayout->addLayout(buttonLayout);

    // setup window and central widget
    this->centralWidget->setLayout(mainLayout);

    this->setCentralWidget(this->centralWidget);

    this->setWindowTitle("Shutdown");
    this->setFixedSize(QSize(300, 250));

    // Start new thread for updating the current and remaing time
    QtConcurrent::run(this, MainWindow::updateTime);
}


void MainWindow::updateTime()
{
    /* Update the current and remaining time */

    QDateTime dateTime;

    // Update times as long as the thread is active
    while (this->running)
    {
        dateTime = QDateTime::currentDateTime();
        QDate date = dateTime.date();
        QTime time = dateTime.time();

        // Set and format the current time.
        this->currentTime->setText(QString("%1").arg(date.month(), 2, 10, QChar('0')) + "/" + QString("%1").arg(date.day(), 2, 10, QChar('0')) + "/" + QString::number(date.year()) + " " +
                                   QString("%1").arg(time.hour(), 2, 10, QChar('0')) + ":" + QString("%1").arg(time.minute(), 2, 10, QChar('0')) + ":" + QString("%1").arg(time.second(), 2, 10, QChar('0')));

        // If the time has not been set for shutdown yet, do not calculate remaining time.
        if (this->timeSet != 0 && QDateTime::currentDateTime().secsTo(*this->timeSet) > 0)
            this->remainingTime->setText(QString("%1").arg(calculateHours(), 2, 10, QChar('0')) + ":" + QString("%1").arg(calculateMinutes(), 2, 10, QChar('0')) + ":" + QString("%1").arg(calculateSeconds(), 2, 10, QChar('0')));
        else
            this->remainingTime->setText("");

        // Sleep for 100 MS to prevent constant use of resources
        QThread::msleep(100);
    }
    return;
}

// Slot for shutdown button clicked
void MainWindow::shutdownClicked()
{
    // Start the shutdown timer process
    delete timeSet;

    if (timeRadioButton->isChecked())
    {
        this->timeSet = new QDateTime;
        this->timeSet->setDate(dateTimeEdit->date());
        this->timeSet->setTime(dateTimeEdit->time());
    } else
    {
        this->timeSet = new QDateTime(QDateTime::currentDateTime());
        this->timeSet = new QDateTime(this->timeSet->addSecs((hoursSpinner->value() * 60 * 60) + minutesSpinner->value() * 60 + secondsSpinner->value()));
    }
    this->shutdownThread->setDateTime(*this->timeSet);
    this->shutdownThread->start();
    return;
}

// Slot for cancel button clicked
void MainWindow::cancelClicked()
{
    // Kill the shutdown timer process
    this->shutdownThread->cancelShutdown();
    delete timeSet;
    timeSet = 0;
    return;
}

// Slot for exit button clicked
void MainWindow::exitClicked()
{
    this->closeWindow();
}

// Overrite the close event to ensure the child threads are closed.
void MainWindow::closeEvent(QCloseEvent *)
{
    this->closeWindow();
    return;
}

void MainWindow::closeWindow()
{
    // quit the process for updating the remaining and current time labels
    this->running = false;

    // Kill the shutdown timer process and wait for it to terminate
    this->shutdownThread->cancelShutdown();
    shutdownThread->wait();

    // Close the MainWindow
    this->close();
    return;
}

int MainWindow::calculateHours() const
{
    // Calculate and return hours
    return QDateTime::currentDateTime().secsTo(*this->timeSet) / (60 * 60);
}

int MainWindow::calculateMinutes() const
{
    qint64 t_seconds = QDateTime::currentDateTime().secsTo(*this->timeSet);
    return (t_seconds / 60) - (t_seconds / (60 * 60)) * 60;
}

int MainWindow::calculateSeconds() const
{
    return QDateTime::currentDateTime().secsTo(*this->timeSet) % 60;
}


