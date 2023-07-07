#include "taskwidget.h"
#include "taskwidget.h"
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QDir>
#include <map>
#include <QDirIterator>

std::map<int, int> widget_to_duration = {
    {0, 50},
    {1, 10*1000},
    {2, 30*1000}
};

TaskWidget::TaskWidget(QWidget *parent,int type) : QWidget(parent) {
    startButton = new QPushButton("Start", this);
    type_of_task = type;
    QHBoxLayout *layout = new QHBoxLayout(this);

    //this widget is a "default task"
    if(type_of_task==0){
        progressBar = new QProgressBar(this);
        progressBar->setRange(0, 100);
        deleteWidgetButton = new QPushButton("X",this);
        //create the layout
        layout->addWidget(startButton);
        layout->addWidget(progressBar);
        layout->addWidget(deleteWidgetButton);
        layout->setContentsMargins(0, 0, 0, 0);
        setLayout(layout);
        // Connect signals to slots
        connect(this, SIGNAL(progressUpdated(int)), this, SLOT(updateProgressBar(int)));
        connect(this, SIGNAL(finished()), this, SLOT(re_enable_button()));
        connect(startButton, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
        connect(deleteWidgetButton, SIGNAL(clicked()), this, SLOT(remove_task())); // Connect to remove_task() slot
    }

    //this task prints the a text line in debug
    if(type_of_task==1){
        text_to_print = new QLineEdit(this);
        label = new QLabel("Enter text",this);
        //create the layout
        layout->addWidget(startButton);
        layout->addWidget(label);
        layout->addWidget(text_to_print);
        layout->setContentsMargins(0, 0, 0, 0);
        setLayout(layout);
        // Connect signals to slots
        connect(startButton, SIGNAL(clicked()), this, SLOT(on_button_clicked()));

    }

    //this task checks if a given path exists
    if(type_of_task==2){
        path_to_check = new QLineEdit(this);
        label = new QLabel("Enter path",this);

        //create the layout
        layout->addWidget(startButton);
        layout->addWidget(label);
        layout->addWidget(path_to_check);
        layout->setContentsMargins(0, 0, 0, 0);
        setLayout(layout);
        // Connect signals to slots
        connect(startButton, SIGNAL(clicked()), this, SLOT(on_button_clicked()));

    }

}

void TaskWidget::startTask() {
    // Handle the start of the task
    // You can update the progress bar, perform operations, etc.
    // Example:
    if(this->type_of_task==0){
        progressBar->setValue(0);
        for (int progress = 0; progress <= 100; ++progress)
        {
            QThread::msleep(20); // Simulate some work
            emit progressUpdated(progress);
        }
        emit finished();
    }
    if(this->type_of_task==1){
       qInfo()<<this->text_to_print->text();
    }

    if(this->type_of_task==2){
        QString path = this->path_to_check->text();
        QDir dir(path);
        if(!dir.exists()) {
            qInfo() << "The path "<<path<<"does not exist.";
        }else{
            qInfo() << "The path "<<path<<"does exist and contains the following folders/files:";
            QDirIterator it(path, QDir::AllEntries | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

               while (it.hasNext()) {
                   qInfo() << it.next();
               }
        }

    }
}

void TaskWidget::on_button_clicked()
{
    // Disable the button
    startButton->setEnabled(false);

    // Calculate the total number of iterations based on the desired total duration
    int totalDuration = 60*1000;  // 1 minute in milliseconds
    int dt = widget_to_duration[this->type_of_task];      // Interval in milliseconds
    int numIterations = totalDuration / dt;

    // Create a QTimer object
    QTimer* timer = new QTimer(this);

    // Connect the timeout signal to a slot or lambda function
    connect(timer, &QTimer::timeout, this, [this, timer, numIterations]() {
        static int iteration = 0;

        // Perform your task here
        this->startTask();

        // Check if the desired number of iterations is reached
        if (++iteration >= numIterations) {
            // Stop the timer
            timer->stop();

            // Enable the button
            startButton->setEnabled(true);
        }
    });

    // Start the timer
    timer->start(dt);
}





void TaskWidget::remove_task(){

    deleteLater(); // Schedule the TaskWidget for deletion

}
