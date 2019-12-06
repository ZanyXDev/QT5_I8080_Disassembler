#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDebug>

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);

signals:
    void finished();

public slots:
    void run();
};

#endif // TASK_H

