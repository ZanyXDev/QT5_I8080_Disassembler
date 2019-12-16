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

    /*   0          1          2          3          4          5           6          7          8          9          A          b          c          d          e          f       */
    //        /*0*/"nop",     "lxi b",   "stax b",  "inx b",   "inr b",   "dcr b",    "mvi b",   "rlc",     "illegal", "dad b",   "ldax b",  "dcx b",   "inr c",   "dcr c",   "mvi c",   "rrc",
    //       /*1*/"illegal", "lxi d",   "stax d",  "inx d",   "inr d",   "dcr d",    "mvi d",   "ral",     "illegal", "dad d",   "ldax d",  "dcx d",   "inr e",   "dcr e",   "mvi e",   "rar",
    //       /*2*/"illegal", "lxi h",   "shld",    "inx h",   "inr h",   "dcr h",    "mvi h",   "daa",     "illegal", "dad h",   "lhld",    "dcx h",   "inr l",   "dcr l",   "mvi l",   "cma",
    //       /*3*/"illegal", "lxi sp",  "sta",     "illegal", "inr m",   "dcr m",    "mvi m",   "stc",     "illegal", "dad sp",  "lda",     "dcx sp",  "inr a",   "dcr a",   "mvi a",   "cmc",
    //       /*4*/"mov b,b", "mov b,c", "mov b,d", "mov b,e", "mov b,h", "mov b,l",  "mov b,m", "mov b,a", "mov c,b", "mov c,c", "mov c,d", "mov c,e", "mov c,h", "mov c,l", "mov c,m", "mov c,a",
    //       /*5*/"mov d,b", "mov d,c", "mov d,d", "mov d,e", "mov d,h", "mov d,l",  "mov d,m", "mov d,a", "mov e,b", "mov e,c", "mov e,d", "mov e,e", "mov e,h", "mov e,l", "mov e,m", "mov e,a",
    //       /*6*/"mov h,b", "mov h,c", "mov h,d", "mov h,e", "mov h,h", "mov h,l",  "mov h,m", "mov h,a", "mov l,b", "mov l,c", "mov l,d", "mov l,e", "mov l,h", "mov l,l", "mov l,m", "mov l,a",
    //       /*7*/"mov m,b", "mov m,c", "mov m,d", "mov m,e", "mov m,h", "mov m,l",  "hlt",     "mov m,a", "mov a,b", "mov a,c", "mov a,d", "mov a,e", "mov a,h", "mov a,l", "mov a,m", "mov a,a",
    //       /*8*/"add b",   "add c",   "add d",   "add e",   "add h",   "add l",    "add m",   "add a",   "adc b",   "adc c",   "adc d",   "adc e",   "adc h",   "adc l",   "adc m",   "adc a",
    //       /*9*/"sub b",   "sub c",   "sub d",   "sub e",   "sub h",   "sub l",    "sub m",   "sbb a",   "sbb b",   "sbb c",   "sbb d",   "sbb e",   "sbb h",   "sbb l",   "sbb m",   "sbb a",
    //       /*a*/"ana b",   "ana c",   "ana d",   "ana e",   "ana h",   "ana l",    "ana m",   "ana a",   "xra b",   "xra c",   "xra d",   "xra e",   "xra h",   "xra l",   "xra m",   "xra a",
    //        /*b*/"ora b",   "ora c",   "ora d",   "ora e",   "ora h",   "ora l",    "ora m",   "ora a",   "cmp b",   "cmp c",   "cmp d",   "cmp e",   "cmp h",   "cmp l",   "cmp m",   "cmp a",
    //       /*c*/"rnz",     "pop b",   "jnz",     "jmp",     "cnz",     "push b",   "adi",     "rst 0",   "rz",      "ret",     "jz",      "illegal", "cz",      "call",    "aci",     "rst 1",
    //       /*d*/"rnc",     "pop d",   "jnc",     "out",     "cnc",     "push d",   "sui",     "rst 2",   "rc",      "illegal", "jc",      "in",      "cc",      "illegal", "sbi",     "rst 3",
    //       /*e*/"rpo",     "pop h",   "jpo",     "xthl",    "cpo",     "push h",   "ani",     "rst 4",   "rpe",     "pchl",    "jpe",     "xchg",    "cpe",     "illegal", "xri",     "rst 5",
    //        /*f*/"rp",      "poppsw",  "jp",      "di",      "cp",      "push psw", "ori",     "rst 6",   "cm",      "sphl",    "jm",      "ei",      "cm",      "illegal", "cpi",     "rst 7"


    // Size (in bytes) of every 8080 opcode
    static const int opcode_bytes[0x100] =
    {/*   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F*/
     /*0*/1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
     /*1*/1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
     /*2*/1, 3, 3, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 2, 1,
     /*3*/1, 3, 3, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
     /*4*/1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     /*5*/1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     /*6*/1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     /*7*/1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     /*8*/1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     /*9*/1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     /*A*/1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     /*B*/1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     /*C*/1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 3, 1, 3, 3, 2, 1,
     /*D*/1, 1, 3, 2, 3, 1, 1, 1, 1, 1, 3, 2, 3, 1, 2, 1,
     /*E*/1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 3, 1, 3, 3, 2, 1,
     /*F*/1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 3, 1, 3, 3, 2, 1
    };

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
    // Do processing here
    qDebug() << "Do processing here";
    if ( !m_data.isEmpty() )
    {
        // Disassembly loop
        static unsigned pc = 0x0;
        quint8 data_item;
        mnemonics m_men;

        QByteArray::iterator data_iterator = m_data.begin();
        while( data_iterator != m_data.end() )
        {
            data_item = static_cast<quint8>( *data_iterator );
            QHash<quint8, mnemonics>::const_iterator mnemonic_iterator =m_codes.find(data_item);
            if ( mnemonic_iterator != m_codes.end())
            {

                switch (mnemonic_iterator.value().size) {
                case ONE_BYTE:
                    qDebug() << QString("ADR:%1\t%2;\t%3").arg(pc,0,16).arg(mnemonic_iterator.value().txt).arg(mnemonic_iterator.value().desc);
                    asm_text.append(QString("ADR:%1\t%2;\t%3").arg(pc,0,16).arg(mnemonic_iterator.value().txt).arg(mnemonic_iterator.value().desc));
                    break;
                case TWO_BYTES:
                    break;
                case THREE_BYTES:
                    break;
                default:
                    break;
                }
            }else {
                qDebug() << QString("opCode[%1] not found or illegal").arg(data_item,0,16);
            }

            data_iterator++;
        }


    }else {
        qDebug() << "not found data in file!";
    }

    emit finished();
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
