#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QStringList>


#define OP(x)                  (buf[pc + x])
#define MNEM(x)                (mnemonics[buf[pc + x]])
#define SIZE_OF_OPCODE(x)      (opcode_bytes[buf[x]])
#define ONE_BYTE               1
#define TWO_BYTES              2
#define THREE_BYTES            3

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);
    void loadFile(QString filename);
signals:
    void finished();

public slots:
    void run();

private:
    QByteArray m_data;
    QStringList
};

#endif // TASK_H

