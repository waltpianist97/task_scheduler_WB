#include "scheduler.h"
#include <QSystemTrayIcon>
#include <QMessageBox>

Scheduler::Scheduler(QWidget *parent)
    : QMainWindow(parent)
{
    mainLayout = new QVBoxLayout;

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    this->setWindowIcon(QIcon(":/myappico.png"));

    TaskWidget *taskWidget_text = new TaskWidget(this,1);
    mainLayout->addWidget(taskWidget_text);
    TaskWidget *taskWidget_file = new TaskWidget(this,2);
    mainLayout->addWidget(taskWidget_file);

    QPushButton *addTaskWidget = new QPushButton("Add new task",this);
    mainLayout->addWidget(addTaskWidget);
    connect(addTaskWidget, SIGNAL(clicked()), this, SLOT(add_task()));

    my_system_tray_icon = new QSystemTrayIcon(this);
    my_system_tray_icon->setIcon(QIcon(":/myappico.png"));
    my_system_tray_icon->setVisible(true);
}

Scheduler::~Scheduler()
{
    // Clean up the taskWidgets vector
    for (TaskWidget *taskWidget : taskWidgets) {
        delete taskWidget;
    }
    taskWidgets.clear();
}


void Scheduler::add_task(){

    TaskWidget *taskWidget = new TaskWidget(this);
    mainLayout->addWidget(taskWidget);
    taskWidgets.append(taskWidget);
    my_system_tray_icon->showMessage(tr("Message"),tr("New task added!"));
}


