/*
 * utils.h
 *
 *  Created on: 28 июл. 2023 г.
 *      Author: a.zavyalov
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define SetBit(reg, bit)          reg |= (1<<bit)          //Запись 1 в определённый бит
#define ClearBit(reg, bit)        reg &= (~(1<<bit))       //Запись 0 в определённый бит
#define InvBit(reg, bit)          reg ^= (1<<bit)          //Инвертирование состояния бита
#define BitIsSet(reg, bit)        ((reg & (1<<bit)) != 0)  //Проверяет установлен ли бит
#define BitIsClear(reg, bit)      ((reg & (1<<bit)) == 0)  //Проверяет не установлен ли бит

union Int8DataType
{
    uint8_t iVal;
    unsigned char buf[1];
};

union IntDataType
{
    int iVal;
    unsigned char buf[4];
};

union UInt32DataType
{
    uint32_t iVal;
    unsigned char buf[4];
};

union UInt16DataType
{
    uint16_t iVal;
    unsigned char buf[2];
};

union BFloatDataType
{
	__bf16 iVal;
    unsigned char buf[2];
};

union FloatDataType
{
    float iVal;
    unsigned char buf[4];
};

union DoubleDataType
{
    double iVal;
    unsigned char buf[8];
};

struct TIPParserStruct
{
 uint8_t ip1;
 uint8_t ip2;
 uint8_t ip3;
 uint8_t ip4;
 bool succ;
};

class TUtils {
public:
	TUtils();
	virtual ~TUtils();

	void IntToBytes(int num, unsigned char retval[4]);                                  //Преобразует int в 4 байтовое значение
	void UInt32ToBytes(uint32_t num, unsigned char retval[4]);                          //Преобразование uint32 в 4 байтовове значение
	int BytesToInt(unsigned char *bp);                                                  //Преобразует 4 байта в int значение
    uint32_t BytesToUInt32(unsigned char *bp);                                          //Преобразует 4 байта в uint32
	void UInt16ToBytes(uint16_t num, unsigned char retval[2]);                          //Преобразует uint16_t в 2 байта
	uint8_t BytesToUInt8(unsigned char *bp);                                             //Преобразование 1 байта в int значение
	uint16_t BytesToUInt16(unsigned char *bp);                                          //Преобразование 2 байт в uint16 значение
	uint16_t BytesToUInt16Rev(unsigned char *bp);                                          //Преобразование 2 байт в uint16 значение
	void FloatToBytes(float num, unsigned char retval[4]);                              //Преобразует float в 4 байтовое значение (соответсвует стандарту  IEEE 754)
	void BFloatToBytes(__bf16 num, unsigned char retval[2]);
	void DoubleToBytes(double num, unsigned char retval[8]);                            //Преобразует double в 8 байтовое значение
	float BytesToFloat(unsigned char *bp);                                              //Преобразует 4 байта во float значение
	double BytesToDouble(unsigned char *bp);                                            //Преобразует 8 байта во float значение
	int Pos(char *source, char *searchsym);                                             //Поиск подстроки в строке с самого начала
	void Copy(char *source, char *outsource, int startpos, int count);                  //Копирование подстроки в строку
	uint8_t StrByteToByte(unsigned char sym1, unsigned char sym2);                      //Преобразование 2-х символов HEX в его байт значение
	void ByteToByteStr(unsigned char inputsym, char retval[2]);                         //Преобразование байта в его HEX значение из 2-х символов
	float BytesToFloatRev(unsigned char *bp);
	void ParseIPTextToIP(char *iptext, TIPParserStruct *IPParserStruct); //Преобразует текст IP адреса в отдельные элементы IP адреса
	uint32_t htonl(uint32_t net);
	uint32_t ntohl(uint32_t net);
};

#endif /* UTILS_H_ */
