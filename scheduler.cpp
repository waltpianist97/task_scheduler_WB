#include "scheduler.h"
#include <QSystemTrayIcon>
#include <QMessageBox>

Scheduler::Scheduler(QWidget *parent)
    : QMainWindow(parent)
    /** Costruttore dello scheduler **/

{
    //creazione del layout di base
    mainLayout = new QVBoxLayout;
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //icona
    this->setWindowIcon(QIcon(":/myappico.png"));

    //system tray icon
    my_system_tray_icon = new QSystemTrayIcon(this);
    my_system_tray_icon->setIcon(QIcon(":/myappico.png"));
    my_system_tray_icon->setVisible(true);

    //questi sono i task per stampare il testo in debug e controllare la presenza del file
    //dopo aver inserito i campi nei rispettivi QLineEdit
    TaskWidget *taskWidget_text = new TaskWidget(this,1);
    mainLayout->addWidget(taskWidget_text);
    TaskWidget *taskWidget_file = new TaskWidget(this,2);
    mainLayout->addWidget(taskWidget_file);

    //questo, a scopo puramente dimostrativo, è un bottone che aggiunge
    //un dummy task
    QPushButton *addTaskWidget = new QPushButton("Add new task",this);
    mainLayout->addWidget(addTaskWidget);
    connect(addTaskWidget, SIGNAL(clicked()), this, SLOT(add_task()));

}

Scheduler::~Scheduler()
{
    /** Metodo distruttore, che elimina i tasks dallo scheduler **/

    for (TaskWidget *taskWidget : taskWidgets) {
        delete taskWidget;
    }
    taskWidgets.clear();
}


void Scheduler::add_task(){
    /** Metodo che aggiunge un nuovo task alla GUI **/
    TaskWidget *taskWidget = new TaskWidget(this,0);
    mainLayout->addWidget(taskWidget);
    taskWidgets.append(taskWidget);

    //esempio di notifica da parte del system tray icon
    my_system_tray_icon->showMessage(tr("Attenzione"),tr("E' stato inserito un nuovo task!"));
}


