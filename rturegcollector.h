/*
 * rturegcollector.h
 *
 *  Created on: Sep 29, 2023
 *      Author: a.zavyalov
 */

#ifndef INC_RTUREGCOLLECTOR_H_
#define INC_RTUREGCOLLECTOR_H_

#define MODBUS_MULTIREADREG      0x04 //Номер функции на чтения множества регистров
#define MODBUS_READREGCOUNT      0x06 //Общее количество регистров для чтения

#define MODBUS_WRITESINGLEREG    0x06 //Номер функции на запись одного регистра
#define MODBUS_WRITEREGCOUNT     0x06 //Общее количество регистров для записи

#define MODBUS_WRITEMULTIREG     0x10 //Номер функции на запись множества регистров сразу

//ID регистров
#define REG_WORK_MODE            0x00 //Режим испытания (0 - по массе, 1 - по времени)
#define REG_UNLOAD_MASS          0x01 //Масса опрокидования ковша
#define REG_UNLOAD_TIME          0x02 //Время опрокидования ковша
#define REG_MAXLOADDEVICE        0x03 //Максимальная масса ковша
#define REG_LABLEDOWNTIME        0x04 //Время ковша в опрокинутом состоянии
#define REG_RUNSTATUS            0x05 //Запущено ли испытание (0 - не запущено, 1 - запущено)

//Аппаратные ошибки
#define ERROR_NOERROR            0x00 //Нет ошибок
#define ERROR_CODE_1             0x01 //Ошибка связи с АЦП
#define ERROR_CODE_0             0x02 //Ошибка срабатываения ковша
#define ERROR_CODE_2             0x03 //Ошибка инициализации ETHERNET модуля

//A = %2f beta = %ld Ax = %2f Ay = %2f a = %2f b = %2f
struct TRegCollection
{
	unsigned short A;                   //Перегрузка G
	unsigned short beta;                //Угол наклона элипса
	unsigned short Ax;                  //Вибро перемещение по оси X
	unsigned short Ay;                  //Вибро перемещение по оси Y
	unsigned short a;                   //Большой радиус
	unsigned short b;                   //Малый радиус
};

struct TRegXFer
{
	float Aapoln;
	float beta;
	float Axtr;
	float Aytr;
	float a;
	float b;
};

#endif /* INC_RTUREGCOLLECTOR_H_ */
