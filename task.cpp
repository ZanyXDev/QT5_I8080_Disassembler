#include "task.h"

Task::Task(QObject *parent) : QObject(parent)
{

}

void Task::run()
{
    // Do processing here
    qDebug() << "Do processing here";
    emit finished();
}
