#include "task.h"

Task::Task(QObject *parent) : QObject(parent)
{
    m_data.clear();

    m_codes.insert(0x00,{1,"NOP"," not opperation "});
    m_codes.insert(0x01,{3,"LXI B ",""});
    m_codes.insert(0x02,{1,"STAX B ",""});
    m_codes.insert(0x03,{1,"INX B ",""});
    m_codes.insert(0x04,{1,"INR B ",""});
    m_codes.insert(0x05,{1,"DCR B ",""});
    m_codes.insert(0x06,{2,"MVI B ",""});
    m_codes.insert(0x07,{1,"RLC ",""});
    m_codes.insert(0x08,{1,"ILLEGAL ",""});
    m_codes.insert(0x09,{1,"DAD B ",""});
    m_codes.insert(0x0A,{1,"LDAX B ",""});
    m_codes.insert(0x0B,{1,"DCX B ",""});
    m_codes.insert(0x0C,{1,"INR C ",""});
    m_codes.insert(0x0D,{1,"DCR C ",""});
    m_codes.insert(0x0E,{2,"MVI C ",""});
    m_codes.insert(0x0F,{1,"RRC ",""});


}

void Task::loadFile(QString filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    m_data = file.readAll();
    file.close();
}

void Task::run()
{
    if ( !m_data.isEmpty() )
    {
#ifdef LOCAL_DEBUG
        pc= 0xF800; // Start address monitor
#else
#endif
        QByteArray::iterator data_iterator = m_data.begin();
        while( data_iterator != m_data.end() )  // Disassembly loop
        {
            QString  txt;
            quint8 data_item = static_cast<quint8>( *data_iterator );
            QHash<quint8, mnemonics>::const_iterator mnemonic_iterator =m_codes.find(data_item);
            if ( mnemonic_iterator != m_codes.end())
            {

                switch (mnemonic_iterator.value().size) {
                case ONE_BYTE:
                    txt =  QString("ADR:%1\t%2;\t%3")
                            .arg(pc,0,16)
                            .arg(mnemonic_iterator.value().txt)
                            .arg(mnemonic_iterator.value().desc);
                    qDebug() << txt;
                    pc++;
                    break;
                case TWO_BYTES:
                    if ( isCanDecode(data_iterator,TWO_BYTES) )
                    {
                        data_iterator++;
                        txt =  QString("ADR:%1\t%2 %3;\t%4")
                                .arg(pc,0,16)
                                .arg(mnemonic_iterator.value().txt)
                                .arg(data_iterator,0,16)
                                .arg(mnemonic_iterator.value().desc);
                        qDebug() << txt;
                        pc+=2;
                    }
                    break;
                case THREE_BYTES:
                    if ( isCanDecode(data_iterator,THREE_BYTES) )
                    {
                        quint8 d8_1,d8_2;

                        d8_1 = static_cast<quint8>( *data_iterator );
                        data_iterator++;
                        d8_2 = static_cast<quint8>( *data_iterator );
                        data_iterator++;
                        quint16 addr16 = static_cast<quint16>( (d8_1 & 0x00FF) << 8 ) | ( d8_2 & 0x00FF) ;

                        txt =  QString("ADR:%1\t%2 %3;\t%4")
                                .arg(pc,0,16)
                                .arg(mnemonic_iterator.value().txt)
                                .arg(addr16,0,16)
                                .arg(mnemonic_iterator.value().desc);
                        qDebug() << txt;
                        pc+=3;
                    }
                    break;
                default:
                    break;
                }
            }else {
                qDebug() << QString("opCode[%1] not found or illegal").arg(data_item,0,16);
            }
            asm_text.append(txt);
            data_iterator++;
        }
    }else {
        qDebug() << "not found data in file!";
    }
    emit finished();
}

bool Task::isCanDecode( QByteArray::iterator current_iterator, quint8 size )
{
    QByteArray::iterator iterrator = current_iterator;
    int i=0;
    while (iterrator != m_data.end()){
        i++;
        iterrator++;
        if (i >= size)
        {
            return  true;
        }
    }
    return false;

}
/*
 * QMap<QString, int> map;
...

        QHash<quint8, mnemonics>::const_iterator i;
        for (i = m_codes.constBegin(); i != m_codes.constEnd(); ++i){
            qDebug() << "key:"<< i.key();
        }

QMap<QString, int>::const_iterator i = map.find("HDR");
while (i != map.end() && i.key() == "HDR") {
    cout << i.value() << endl;
    ++i;
}
*/
