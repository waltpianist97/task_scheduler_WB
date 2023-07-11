#include "taskwidget.h"
#include <QDebug>
#include <QLabel>
#include <QDir>
#include <map>
#include <QDirIterator>
#include <unistd.h>
#define TOT_DURATION 20000 // in ms, durata complessiva dell'esecuzione del task


TaskWidget::TaskWidget(QWidget *parent,int type,int duration) : QWidget(parent) {
    /** metodo costruttore del task widget **/

    startButton = new QPushButton("Start", this);
    type_of_task = type;
    task_duration = duration;
    QHBoxLayout *layout = new QHBoxLayout(this);

    //Questo widget rappressenta un "default task", giusto per far vedere come aggiungere/togliere task nuovi
    if(type_of_task==0){
        progressBar = new QProgressBar(this);
        progressBar->setRange(0, 100);
        deleteWidgetButton = new QPushButton("X",this);
        //layout
        layout->addWidget(startButton);
        layout->addWidget(progressBar);
        layout->addWidget(deleteWidgetButton);
        layout->setContentsMargins(0, 0, 0, 0);
        setLayout(layout);
        // Connessione segnali e slots
        connect(deleteWidgetButton, SIGNAL(clicked()), this, SLOT(remove_task()));

    }

    //Task che stampa una stringa su linea di comando
    if(type_of_task==1){
        text_to_print = new QLineEdit(this);
        label = new QLabel("Enter text",this);
        //layout
        layout->addWidget(startButton);
        layout->addWidget(label);
        layout->addWidget(text_to_print);
        layout->setContentsMargins(0, 0, 0, 0);
        setLayout(layout);
        // Connessione segnali e slots
        connect(startButton, SIGNAL(clicked()), this, SLOT(on_button_clicked()));

    }

    //Task che controlla se un certo path esiste. Se non esiste, stampa un messaggio di debug
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
    /** metodo che gestisce il task **/
    if(this->type_of_task==1){
       qInfo()<<this->text_to_print->text();
    }

    if(this->type_of_task==2){
        QString path = this->path_to_check->text();
        QDir dir(path);
        if(!dir.exists()) {
            qInfo() << "Il file path "<<path<<"non esiste.";
        }

    }
}

void TaskWidget::on_button_clicked()
{
    /** Questo metodo viene invocato quando il task viene avviato.
    Fa partire un ciclo while che esegue per una certa durata il task indicato. Se per caso
    un task viene invocato mentre ne viene eseguito un altro, l'applicazione non risponde, in quanto
    il suo main thread è già occupato dall'esecuzione del task corrente. Non appena finisce, parte quello
    successivo. Non sono definiti altri thread al di fuori di quello dell'applicazione. **/

    // Calcolo del numero totale di iterazioni in base alla durata complessiva e a quella del
    // singolo task
    int totalDuration = TOT_DURATION;
    int dt = this->task_duration;   // intervallo in ms basato sul "Clock" del singolo task
    int numIterations = totalDuration / dt;

    int iteration = 0;
    while(iteration<numIterations){
        this->startTask();
        usleep(dt*1000);
        iteration++;
    }

}





void TaskWidget::remove_task(){
    /** Questo metodo rimuove un certo widget/task **/
    deleteLater();

}
