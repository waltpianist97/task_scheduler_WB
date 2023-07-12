# task_scheduler_WB

Il progetto consiste in un task scheduler sequenziale definito in Qt e C++. 
E' controllabile tramite QSystemTrayIcon e può performare dei task in sequenza, di cui in particolare:
1) Stampare su linea di comando un testo inserito all'interno di un apposito QLineEdit.
2) Contollare che un certo file path, anch'esso in apposito QLineEdit, sia presente nel file system e, qualora non lo fosse, stampare un messaggio di debug.
3) Aggiungere a piacere nuovi task (nel mio caso ho definito un dummy task)

# Come compilare ed eseguire l'app

Ho utilizzato l'IDE QtCreator, il quale ha generato la struttura del progetto. Dopo aver aperto QtCreator, selezionare il file .pro. In seguito:
1) Selezionare sul menu: Build -> Run qmake
2) Run nella sidebar verticale sinistra

A questo punto l'app viene compilata, eseguita ed è possibile eseguire i task. Nella console "Application Output" è possibile visualizzare il debug output. Essendo l'intera applicazione single-threaded, come indicato dalla traccia, non appena viene avviato un task, il main thread dell'applicazione sarà dedicato al completamento del task, tuttavia cliccando sull'altro task, esso verrà eseguito in coda a quello corrente.

