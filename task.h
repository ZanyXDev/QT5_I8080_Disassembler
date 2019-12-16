#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QStringList>
#include <QHash>
#include "config.h"

#define OP(x)                  (buf[pc + x])
#define MNEM(x)                (mnemonics[buf[pc + x]])
#define SIZE_OF_OPCODE(x)      (opcode_bytes[buf[x]])


struct mnemonics {   
    quint8 size;    
    QString txt;
    QString desc;
};

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
    QHash<quint8, mnemonics> m_codes;
    QStringList asm_text;
};

#endif // TASK_H

