#include "task.h"

Task::Task(QObject *parent) : QObject(parent)
{

}

void Task::loadFile(QString filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QByteArray m_data = file.readAll();
    file.close();
}

void Task::run()
{
    // Do processing here
    qDebug() << "Do processing here";
    if ( m_data.isEmpty() )
    {
        qDebug() << "not found data in file!";
        return;
    }
    // Disassembly loop
    static unsigned pc;

    emit finished();
}
