#include "task.h"

Task::Task(QObject *parent) : QObject(parent)
{
    m_data.clear();
    m_codes.insert(0x87,{1,"ADD A","A←(A) + (A)"});
    m_codes.insert(0x80,{1,"ADD B","A←(B) + (A)"});
    m_codes.insert(0x81,{1,"ADD C","A←(C) + (A)"});
    m_codes.insert(0x82,{1,"ADD D","A←(D) + (A)"});
    m_codes.insert(0x83,{1,"ADD E","A←(E) + (A)"});
    m_codes.insert(0x84,{1,"ADD H","A←(H) + (A)"});
    m_codes.insert(0x85,{1,"ADD L","A←(L) + (A)"});
    m_codes.insert(0x86,{1,"ADD M","A←Loc(HL) + (A)"});
    m_codes.insert(0xC6,{2,"ADI ","A←[d8] + (A)"});
    m_codes.insert(0x80,{1,"ADC A","A←(A) + (A) + CY"});
    m_codes.insert(0x88,{1,"ADC B","A←(B) + (A) + CY"});
    m_codes.insert(0x89,{1,"ADC C","A←(C) + (A) + CY"});
    m_codes.insert(0x8A,{1,"ADC D","A←(D) + (A) + CY"});
    m_codes.insert(0x8B,{1,"ADC E","A←(E) + (A) + CY"});
    m_codes.insert(0x8C,{1,"ADC H","A←(H) + (A) + CY"});
    m_codes.insert(0x8D,{1,"ADC L","A←(L) + (A) + CY"});
    m_codes.insert(0x8E,{1,"ADC M","A←Loc(HL) + (A) + CY"});
    m_codes.insert(0xCE,{2,"ACI ","A←[d8] + (A) + CF"});
    m_codes.insert(0xA7,{1,"ANA A","Проверка A"});
    m_codes.insert(0xA0,{1,"ANA B","Логическое И B с A"});
    m_codes.insert(0xA1,{1,"ANA C","Логическое И C с A"});
    m_codes.insert(0xA2,{1,"ANA D","Логическое И D с A"});
    m_codes.insert(0xA3,{1,"ANA E","Логическое И E с A"});
    m_codes.insert(0xA4,{1,"ANA H","Логическое И H с A"});
    m_codes.insert(0xA5,{1,"ANA L","Логическое И L с A"});
    m_codes.insert(0xA6,{1,"ANA M","Логическое И Loc(HL) с A"});
    m_codes.insert(0xE6,{2,"ANI ","Логическое И непосредственные данные [d8] с Av"});
    m_codes.insert(0xCD,{3,"CALL ","Передать управление подпрограмме по адресу [a16]"});
    m_codes.insert(0xCC,{3,"CZ ","Вызвать подпрограмму по адресу [a16], если нуль"});
    m_codes.insert(0xC4,{3,"СNZ","Вызвать подпрограмму по адресу [a16], если не нуль"});
    m_codes.insert(0xF4,{3,"СP ","Вызвать подпрограмму по адресу [a16], если плюс"});
    m_codes.insert(0xFC,{3,"СM ","Вызвать подпрограмму по адресу [a16], если минус"});
    m_codes.insert(0xDC,{3,"CC ","Вызвать подпрограмму по адресу [a16], если перенос"});
    m_codes.insert(0xD4,{3,"CNC ","Вызвать подпрограмму по адресу [a16], если нет переноса"});
    m_codes.insert(0xEC,{3,"CPE ","Вызвать подпрограмму по адресу [a16], если чётно"});
    m_codes.insert(0xE4,{3,"CPO a16","Вызвать подпрограмму по адресу [a16], если нечётно"});
    m_codes.insert(0x2F,{1,"CMA","Инвертировать A"});
    m_codes.insert(0x3F,{1,"CMC","Инвертировать перенос"});
    m_codes.insert(0xBF,{1,"CMP A","Установить флаг FZ"});
    m_codes.insert(0xB8,{1,"CMP B","Сравнить A с B"});
    m_codes.insert(0xB9,{1,"CMP C","Сравнить A с C"});
    m_codes.insert(0xBA,{1,"CMP D","Сравнить A с D"});
    m_codes.insert(0xBB,{1,"CMP E","Сравнить A с E"});
    m_codes.insert(0xBC,{1,"CMP H","Сравнить A с H"});
    m_codes.insert(0xBD,{1,"CMP L","Сравнить A с L"});
    m_codes.insert(0xBE,{1,"CMP M","Сравнить A с Loc(HL)"});
    m_codes.insert(0xFE,{2,"CPI ","Сравнить A с непосредственными данными [d8], заданными в команде"});
    m_codes.insert(0x27,{1,"DAA	","Десятичная коррекция аккумулятора (совершенно бесполезная команда. Я так и ни разу ей и не воспользовался:)"});
    m_codes.insert(0x09,{1,"DAD B","Сложить BC с HL"});
    m_codes.insert(0x19,{1,"DAD D","Сложить DE с HL"});
    m_codes.insert(0x29,{1,"DAD H","Сложить HL с HL (удвоение HL)"});
    m_codes.insert(0x39,{1,"DAD SP","Сложить SP с HL"});
    m_codes.insert(0x3D,{1,"DCR A","A←(A) - 1 (декремент A)"});
    m_codes.insert(0x05,{1,"DCR B","B←(B) - 1"});
    m_codes.insert(0x0D,{1,"DCR C","C←(C) - 1"});
    m_codes.insert(0x15,{1,"DCR D","D←(D) - 1"});
    m_codes.insert(0x1D,{1,"DCR E","E←(E) - 1"});
    m_codes.insert(0x25,{1,"DCR H","H←(H) - 1"});
    m_codes.insert(0x2D,{1,"DCR L","L←(L) - 1"});
    m_codes.insert(0x35,{1,"DCR M","Loc (HL)←(Loc(HL)) -1"});
    m_codes.insert(0x0B,{1,"DCX B","BC←(BC) - 1"});
    m_codes.insert(0x1B,{1,"DCX D","DE←(DE) -1"});
    m_codes.insert(0x2B,{1,"DCX H","HL←(HL) - 1"});
    m_codes.insert(0x3B,{1,"DCX SP","SP←(SP) -1"});
    m_codes.insert(0xF3,{1,"DI","Запретить прерывания"});
    m_codes.insert(0xFB,{1,"EI","Разрешить прерывания"});
    m_codes.insert(0x76,{1,"HLT","Останов процессора"});
    m_codes.insert(0xDB,{2,"IN ","Ввести данные из порта [d8]"});
    m_codes.insert(0x3C,{1,"INR A","3C	A←(A) + 1 (инкрементировать A)"});
    m_codes.insert(0x04,{1,"INR B","Инкрементировать B"});
    m_codes.insert(0x0C,{1,"INR C","Инкрементировать C"});
    m_codes.insert(0x14,{1,"INR D","Инкрементировать D"});
    m_codes.insert(0x1C,{1,"INR E","Инкрементировать E"});
    m_codes.insert(0x24,{1,"INR H","Инкрементировать H"});
    m_codes.insert(0x2C,{1,"INR L","Инкрементировать L"});
    m_codes.insert(0x34,{1,"INR M","Инкрементировать содержимое Loc(HL)"});
    m_codes.insert(0x03,{1,"INX B","Инкрементировать BС"});
    m_codes.insert(0x13,{1,"INX D","Инкрементировать DE"});
    m_codes.insert(0x23,{1,"INX H","Инкрементировать HL"});
    m_codes.insert(0x33,{1,"INX SP","Инкрементировать SP"});
    m_codes.insert(0xC3,{3,"JMP","Перейти по адресу [a16]"});
    m_codes.insert(0xCA,{3,"JZ","Перейти по адресу [a16], если нуль"});
    m_codes.insert(0xC2,{3,"JNZ ","Перейти по адресу [a16], если не нуль"});
    m_codes.insert(0xF2,{3,"JP ","Перейти по адресу [a16], если плюс"});
    m_codes.insert(0xFA,{3,"JM ","Перейти по адресу [a16], если минус"});
    m_codes.insert(0xDA,{3,"JC ","Перейти по адресу [a16], если перенос"});
    m_codes.insert(0xD2,{3,"JNC ","Перейти по адресу [a16], если нет переноса"});
    m_codes.insert(0xEA,{3,"JPE ","Перейти по адресу [a16], если паритет чётный"});
    m_codes.insert(0xE2,{3,"JPO ","Перейти по адресу [a16], если паритет нечётный"});
    m_codes.insert(0x3A,{3,"LDA ","Загрузить A из ячейки с адресом [a16]"});
    m_codes.insert(0x0A,{1,"LDAX B","Загрузить из ячейки с адресом Loc(BC)"});
    m_codes.insert(0x1A,{1,"LDAX D","Загрузить A из ячейки с адресом Loc(DE)"});
    m_codes.insert(0x2A,{3,"LHLD ","Загрузить в HL содержимое ячейки с адресом [a16]"});
    m_codes.insert(0x01,{3,"LXI B,","Загрузить в BC непосредственные данные [d16]"});
    m_codes.insert(0x11,{3,"LXI D,","Загрузить в D непосредственные данные [d16]"});
    m_codes.insert(0x21,{3,"LXI H,","Загрузить в HL непосредственные данные [d16]"});
    m_codes.insert(0x31,{3,"LXI SP,","Загрузить в SP непосредственные данные [d16]"});
    m_codes.insert(0x7F,{1,"MOV A,A","Переслать из A в A"});
    m_codes.insert(0x78,{1,"MOV A,B","Переслать из B в A (B←(A) )"});
    m_codes.insert(0x79,{1,"MOV A,C","Переслать из C в A"});
    m_codes.insert(0x7A,{1,"MOV A,D","Переслать из D в A"});
    m_codes.insert(0x7B,{1,"MOV A,E","Переслать из E в A"});
    m_codes.insert(0x7C,{1,"MOV A,H","Переслать из H в A"});
    m_codes.insert(0x7D,{1,"MOV A,L","Переслать из L в A"});
    m_codes.insert(0x7E,{1,"MOV A,M","Переслать из Loc(HL) в A"});
    m_codes.insert(0x47,{1,"MOV B,A","Переслать из A в B"});
    m_codes.insert(0x40,{1,"MOV B,B","Переслать из B в B (ещё одна странная команда)"});
    m_codes.insert(0x41,{1,"MOV B,C","Переслать из C в B"});
    m_codes.insert(0x42,{1,"MOV B,D","Переслать из D в B"});
    m_codes.insert(0x43,{1,"MOV B,E","Переслать из E в B"});
    m_codes.insert(0x44,{1,"MOV B,H","Переслать из H в B"});
    m_codes.insert(0x45,{1,"MOV B,L","Переслать из L в B"});
    m_codes.insert(0x46,{1,"MOV B,M","Переслать из Loc(HL) в B"});
    m_codes.insert(0x4F,{1,"MOV C,A","Переслать из A в C"});
    m_codes.insert(0x48,{1,"MOV C,B","Переслать из B в C"});
    m_codes.insert(0x49,{1,"MOV C,C","Переслать из C в C"});
    m_codes.insert(0x4A,{1,"MOV C,D","Переслать из D в C"});
    m_codes.insert(0x4B,{1,"MOV C,E","Переслать из E в C"});
    m_codes.insert(0x4C,{1,"MOV C,H","Переслать из H в C"});
    m_codes.insert(0x4D,{1,"MOV C,L","Переслать из L в C"});
    m_codes.insert(0x4E,{1,"MOV C,M","Переслать из Loc(HL) в C"});
    m_codes.insert(0x57,{1,"MOV D,A","Переслать из A в D"});
    m_codes.insert(0x50,{1,"MOV D,B","Переслать из B в D"});
    m_codes.insert(0x51,{1,"MOV D,C","Переслать из C в D"});
    m_codes.insert(0x52,{1,"MOV D,D","Переслать из D в D"});
    m_codes.insert(0x53,{1,"MOV D,E","Переслать из E в D"});
    m_codes.insert(0x54,{1,"MOV D,H","Переслать из H в D"});
    m_codes.insert(0x55,{1,"MOV D,L","Переслать из L в D"});
    m_codes.insert(0x56,{1,"MOV D,M","Переслать из Loc(HL) в D"});
    m_codes.insert(0x5F,{1,"MOV E,A","Переслать из A в E"});
    m_codes.insert(0x58,{1,"MOV E,B","Переслать из B в E"});
    m_codes.insert(0x59,{1,"MOV E,C","Переслать из C в E"});
    m_codes.insert(0x5A,{1,"MOV E,D","Переслать из D в E"});
    m_codes.insert(0x5B,{1,"MOV E,E","Переслать из E в E"});
    m_codes.insert(0x5C,{1,"MOV E,H","Переслать из H в E"});
    m_codes.insert(0x5D,{1,"MOV E,L","Переслать из L в E"});
    m_codes.insert(0x5E,{1,"MOV E,M","Переслать из Loc(HL) в E"});
    m_codes.insert(0x67,{1,"MOV H,A","Переслать из A в H"});
    m_codes.insert(0x60,{1,"MOV H,B","Переслать из B в H"});
    m_codes.insert(0x61,{1,"MOV H,C","Переслать из C в H"});
    m_codes.insert(0x62,{1,"MOV H,D","Переслать из D в H"});
    m_codes.insert(0x63,{1,"MOV H,E","Переслать из E в H"});
    m_codes.insert(0x64,{1,"MOV H,H","Переслать из H в H"});
    m_codes.insert(0x65,{1,"MOV H,L","Переслать из L в H"});
    m_codes.insert(0x66,{1,"MOV H,","Переслать из Loc(HL) в H"});
    m_codes.insert(0x6F,{1,"MOV L,A","Переслать из A в L"});
    m_codes.insert(0x68,{1,"MOV L,B","Переслать из B в L"});
    m_codes.insert(0x69,{1,"MOV L,C","Переслать из C в L"});
    m_codes.insert(0x6A,{1,"MOV L,D","Переслать из D в L"});
    m_codes.insert(0x6B,{1,"MOV L,E","Переслать из E в L"});
    m_codes.insert(0x6C,{1,"MOV L,H","Переслать из H в L"});
    m_codes.insert(0x6D,{1,"MOV L,L","Переслать из L в L"});
    m_codes.insert(0x6E,{1,"MOV L,M","Переслать из Loc(HL) в L"});
    m_codes.insert(0x77,{1,"MOV M,A","Переслать из A в M"});
    m_codes.insert(0x70,{1,"MOV M,B","Переслать из B в M"});
    m_codes.insert(0x71,{1,"MOV M,C","Переслать из C в M"});
    m_codes.insert(0x72,{1,"MOV M,D","Переслать из D в M"});
    m_codes.insert(0x73,{1,"MOV M,E","Переслать из E в M"});
    m_codes.insert(0x74,{1,"MOV M,H","Переслать из H в M"});
    m_codes.insert(0x75,{1,"MOV M,L","Переслать из L в M"});
    m_codes.insert(0x3E,{2,"MVI A,","Переслать [d8] в A"});
    m_codes.insert(0x06,{2,"MVI B,","Переслать [d8] в B"});
    m_codes.insert(0x0E,{2,"MVI C,","Переслать [d8] в C"});
    m_codes.insert(0x16,{2,"MVI D,","Переслать [d8] в D"});
    m_codes.insert(0x1E,{2,"MVI E,","Переслать [d8] в E"});
    m_codes.insert(0x26,{2,"MVI H,","Переслать [d8] в H"});
    m_codes.insert(0x2E,{2,"MVI L,","Переслать [d8] в L"});
    m_codes.insert(0x36,{2,"MVI M,","Переслать [d8] в Loc(HL)"});
    m_codes.insert(0x00,{1,"NOP","Нет операции"});

    m_codes.insert(0x08,{1,"NOP","Undocumented NOP"});
    m_codes.insert(0x10,{1,"NOP","Undocumented NOP"});
    m_codes.insert(0x18,{1,"NOP","Undocumented NOP"});
    m_codes.insert(0x20,{1,"NOP","Undocumented NOP"});
    m_codes.insert(0x28,{1,"NOP","Undocumented NOP"});
    m_codes.insert(0x30,{1,"NOP","Undocumented NOP"});
    m_codes.insert(0x38,{1,"NOP","Undocumented NOP"});

    m_codes.insert(0xB7,{1,"ORA A","Проверить A и сбросить перенос"});
    m_codes.insert(0xB0,{1,"ORA B","Логичеcкая операция A ИЛИ B"});
    m_codes.insert(0xB1,{1,"ORA C","Логичеcкая операция A ИЛИ C"});
    m_codes.insert(0xB2,{1,"ORA D","Логичеcкая операция A ИЛИ D"});
    m_codes.insert(0xB3,{1,"ORA E","Логичеcкая операция A ИЛИ E"});
    m_codes.insert(0xB4,{1,"ORA H","Логичеcкая операция A ИЛИ H"});
    m_codes.insert(0xB5,{1,"ORA L","Логичеcкая операция A ИЛИ L"});
    m_codes.insert(0xB6,{1,"ORA M","Логичеcкая операция A ИЛИ M"});
    m_codes.insert(0xF6,{2,"ORI","Логичеcкая операция A ИЛИ [d8]"});
    m_codes.insert(0xD3,{2,"OUT ","Записать A в порт [d8]"});
    m_codes.insert(0xE9,{1,"PCHL","Передать управление по адресу в HL"});
    m_codes.insert(0xC1,{1,"POP B","Извлечь слово из стека в BC"});
    m_codes.insert(0xD1,{1,"POP D","Извлечь слово из стека в DE"});
    m_codes.insert(0xE1,{1,"POP H","Извлечь слово из стека в HL"});
    m_codes.insert(0xF1,{1,"POP PSW","Извлечь слово из стека в PSW"});
    m_codes.insert(0xC5,{1,"PUSH B","Поместить в стек содержимое BC"});
    m_codes.insert(0xD5,{1,"PUSH D","Поместить в стек содержимое DE"});
    m_codes.insert(0xE5,{1,"PUSH H","Поместить в стек содержимое HL"});
    m_codes.insert(0xF5,{1,"PUSH PSW","Поместить в стек содержимое PSW"});
    m_codes.insert(0x17,{1,"RAL","Циклический сдвиг CY + A влево"});
    m_codes.insert(0x1F,{1,"RAR","Циклический сдвиг CY + A вправо"});
    m_codes.insert(0x07,{1,"RLC","Сдвинуть A влево на один разряд с переносом"});
    m_codes.insert(0x0F,{1,"RRC","Сдвинуть A вправо на один разряд с переносом"});
    m_codes.insert(0x20,{1,"RIM","Считать маску прерывания (только в 8085)"});
    m_codes.insert(0xC9,{1,"RET","Возврат из подпрограммы"});
    m_codes.insert(0xC8,{1,"RZ","Возврат из подпрограммы, если FZ=0"});
    m_codes.insert(0xC0,{1,"RNZ","Возврат из подпрограммы, если FZ=1"});
    m_codes.insert(0xF0,{1,"RP","Возврат из подпрограммы, если FP=1"});
    m_codes.insert(0xF8,{1,"RM","Возврат из подпрограммы, если FP=0"});
    m_codes.insert(0xD8,{1,"RC","Возврат из подпрограммы, если FC=1"});
    m_codes.insert(0xD0,{1,"RNC","Возврат из подпрограммы, если FC=0"});
    m_codes.insert(0xE8,{1,"RPE","Возврат из подпрограммы, если паритет чётный"});
    m_codes.insert(0xE0,{1,"RPO","Возврат из подпрограммы, если паритет нечётный"});
    m_codes.insert(0xC7,{1,"RST 0","Запуск программы с адреса 0"});
    m_codes.insert(0xCF,{1,"RST 1","Запуск программы с адреса 8h"});
    m_codes.insert(0xD7,{1,"RST 2","Запуск программы с адреса 10h"});
    m_codes.insert(0xDF,{1,"RST 3","Запуск программы с адреса 18h"});
    m_codes.insert(0xE7,{1,"RST 4","Запуск программы с адреса 20h"});
    m_codes.insert(0xEF,{1,"RST 5","Запуск программы с адреса 28h"});
    m_codes.insert(0xF7,{1,"RST 6","Запуск программы с адреса 30h"});
    m_codes.insert(0xFF,{1,"RST 7","Запуск программы с адреса 38h"});
    m_codes.insert(0x30,{1,"SIM	","Установить маску прерывания (только в 8085)"});
    m_codes.insert(0xF9,{1,"SPHL","Загрузить SP из HL"});
    m_codes.insert(0x22,{3,"SHLD ","Записать HL по адресу [a16]"});
    m_codes.insert(0x32,{3,"STA ","Записать A по адресу [a16]"});
    m_codes.insert(0x02,{1,"STAX B","Записать A по адресу Loc(BC)"});
    m_codes.insert(0x12,{1,"STAX D","Записать A по адресу Loc(DE)"});
    m_codes.insert(0x37,{1,"STC","Установить флаг переноса (CF=1)"});
    m_codes.insert(0x97,{1,"SUB A","Вычесть А из А (очистить А)"});
    m_codes.insert(0x90,{1,"SUB B","Вычесть B из А"});
    m_codes.insert(0x91,{1,"SUB C","Вычесть C из А"});
    m_codes.insert(0x92,{1,"SUB D","Вычесть D из А"});
    m_codes.insert(0x93,{1,"SUB E","Вычесть E из А"});
    m_codes.insert(0x94,{1,"SUB H","Вычесть H из А"});
    m_codes.insert(0x95,{1,"SUB L","Вычесть L из А"});
    m_codes.insert(0x96,{1,"SUB M","Вычесть M из А"});
    m_codes.insert(0xD6,{2,"SUI ","Вычесть [d8] из А"});
    m_codes.insert(0x9F,{1,"SBB A","Вычесть А из А (очистить А)"});
    m_codes.insert(0x98,{1,"SBB B","Вычесть c заёмом B из А"});
    m_codes.insert(0x99,{1,"SBB C","Вычесть c заёмом C из А"});
    m_codes.insert(0x9A,{1,"SBB D","Вычесть c заёмом D из А"});
    m_codes.insert(0x9B,{1,"SBB E","Вычесть c заёмом E из А"});
    m_codes.insert(0x9C,{1,"SBB H","Вычесть c заёмом H из А"});
    m_codes.insert(0x9D,{1,"SBB L","Вычесть c заёмом L из А"});
    m_codes.insert(0x9E,{1,"SBB M","Вычесть c заёмом M из А"});
    m_codes.insert(0xDE,{2,"SBI ","Вычесть c заемом [d8] из А"});
    m_codes.insert(0xEB,{1,"XCHG","Обмен содержимым DE и HL"});
    m_codes.insert(0xE3,{1,"XTHL","Обмен содержимого вершины стека с содержимым HL"});
    m_codes.insert(0xAF,{1,"XRA A","Исключающее ИЛИ A с A (очистка A)"});
    m_codes.insert(0xA8,{1,"XRA B","Исключающее ИЛИ B с A"});
    m_codes.insert(0xA9,{1,"XRA C","Исключающее ИЛИ C с A"});
    m_codes.insert(0xAA,{1,"XRA D","Исключающее ИЛИ D с A"});
    m_codes.insert(0xAB,{1,"XRA E","Исключающее ИЛИ E с A"});
    m_codes.insert(0xAC,{1,"XRA H","Исключающее ИЛИ H с A"});
    m_codes.insert(0xAD,{1,"XRA L","Исключающее ИЛИ L с A"});
    m_codes.insert(0xAE,{1,"XRA M","Исключающее ИЛИ Loc(HL) с A"});
    m_codes.insert(0xEE,{2,"XRI","Исключающее ИЛИ d8 с A"});
}

void Task::loadFile(QString filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    asm_text.append(QString("Filename %1 size %2 bytes, decoding usage i8080_dasm in %3\n")
                    .arg( filename )
                    .arg( file.size() )
                    .arg( QDateTime::currentDateTime().toString() )
                    );

    QFileInfo fi(filename);

    outFileName = QString("%1/%2.asm")
            .arg( fi.absolutePath() )
            .arg( fi.baseName() );
    qDebug() << fi.absolutePath() << " fn=" << fi.fileName();
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
        /**
         * @note Format output
         * Address\t    Code\t   Label\t  Mnemonic\t   Operand\t   Comment
         */
        asm_text.append(QString("Output format\n") );
        asm_text.append(QString("Address\tCode\tLabel\tMnemonic\tOperand\tComment\n") );

        QByteArray::iterator data_iterator = m_data.begin();

        while( data_iterator != m_data.end() )  // Disassembly loop
        {
            QString txt;
            QString pc_adr;
            QString code;
            QString mnem;
            QString desc;

            quint8 data_item = static_cast<quint8>( *data_iterator );
            QHash<quint8, mnemonics>::const_iterator mnemonic_iterator = m_codes.find(data_item);
            if ( mnemonic_iterator != m_codes.end() )
            {
                QString d8_d16_txt;
                quint8 d8_1;
                quint8 d8_2;
                quint16 addr16;
                switch (mnemonic_iterator.value().size) {
                case ONE_BYTE:
                    mnem = mnemonic_iterator.value().txt;
                    desc = mnemonic_iterator.value().desc;
                    code = QString("%1").arg(data_item,0,16);
                    d8_d16_txt = QString(" ");
                    pc_adr = QString("%1").arg(pc,0,16);
                    pc++;
                    break;
                case TWO_BYTES:
                    //i + n Итератор, указывающий на позицию n элементов вперед.
                    if ( (data_iterator + 1) !=  m_data.end() )
                    {
                        mnem = mnemonic_iterator.value().txt;
                        desc = mnemonic_iterator.value().desc;
                        data_iterator++;
                        d8_1 = static_cast<quint8>( *data_iterator );
                        code = QString("%1 %2  ")
                                .arg(data_item,0,16)
                                .arg(d8_1,0,16);
                        d8_d16_txt = QString("%1   ").arg(d8_1,0,16);
                        pc_adr = QString("%1").arg(pc,0,16);
                        pc+=2;
                    }else
                    {
                        d8_d16_txt = QString("Not found operand! data end or invalid opCode counter!");
                    }
                    break;
                case THREE_BYTES:
                    if ( (data_iterator + 2 ) !=  m_data.end() )
                    {
                        mnem = mnemonic_iterator.value().txt;
                        desc = mnemonic_iterator.value().desc;
                        data_iterator++;
                        d8_1 = static_cast<quint8>( *data_iterator );
                        data_iterator++;
                        d8_2 = static_cast<quint8>( *data_iterator );
                        addr16 = static_cast<quint16>( (d8_1 & 0x00FF) << 8 ) | ( d8_2 & 0x00FF) ;
                        code = QString("%1 %2 %3")
                                .arg(data_item,0,16)
                                .arg(d8_1,0,16)
                                .arg(d8_2,0,16);
                        d8_d16_txt = QString("%1").arg(addr16,0,16);
                        pc_adr = QString("%1").arg(pc,0,16);
                        pc+=3;
                    }else
                    {
                        d8_d16_txt = QString("Not found operand! data end or invalid opCode counter!");
                    }
                    break;
                default:
                    break;
                }
                txt =  QString("0x%1:\t%2\t%3\t%4\t0x%5\t;%6")
                        .arg(pc_adr)       // Address
                        .arg(code)     // opCode
                        .arg(" ")           // Label
                        .arg(mnem)          // Mnemonics
                        .arg(d8_d16_txt)    // Operand or address
                        .arg(desc);         // Description
            }else {
                pc_adr = QString("%1").arg(pc,0,16);
                pc++;
                txt =  QString("0x%1:opCode[0x%2]\tNot found or illegal")
                        .arg(pc_adr)
                        .arg(data_item,0,16);
            }
            qDebug() << txt;
            asm_text.append(txt);
            data_iterator++;
        }
    }else {
        qDebug() << "not found data in file!";
    }
    if (! asm_text.isEmpty())
    {
        saveDecodeText();
    }
    emit finished();
}



void Task::saveDecodeText()
{
    QFile fileOut(outFileName);

    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&fileOut);
        for ( QStringList::Iterator it = asm_text.begin(); it != asm_text.end(); ++it ){
            writeStream << *it << "\n";
        }
        fileOut.close();
    }

}
