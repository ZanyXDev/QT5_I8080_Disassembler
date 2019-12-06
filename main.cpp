#include <QCoreApplication>
#include <QTimer>
#include <QFileInfo>
#include "assert.h"
#include "task.h"


#define CORRECT_NUMBER_OF_ARGS 2
#define ERROR                  0

void usage(char *info)
{
    fprintf(stderr, "usage: %s filename\n", info);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != CORRECT_NUMBER_OF_ARGS) {
        usage( argv[0]);
        exit( EXIT_FAILURE);
    }

    QString filename = QString::fromLatin1( argv[1]);

    // check if path exists and if yes: Is it a file and no directory?
    if ( !(QFileInfo::exists( filename ) && QFileInfo( filename ).isFile()) )
    {
        fprintf(stderr, "Filename %s is not exist\n", argv[1]);
        usage( argv[1]);
        exit( EXIT_FAILURE);
    }

    // Task parented to the application so that it
    // will be deleted by the application.
    Task *task = new Task(&a);

    task->loadFile( filename );

    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(task, &Task::finished, &QCoreApplication::quit);

    // This will run the task from the application event loop.
    QTimer::singleShot(0, task, SLOT(run()));
    return a.exec();
}

