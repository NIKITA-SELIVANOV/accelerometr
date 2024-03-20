/*
 * modbusrtudrv.h
 *
 *  Created on: Aug 17, 2023
 *      Author: a.zavyalov
 */

#ifndef SRC_MODBUSRTUDRV_H_
#define SRC_MODBUSRTUDRV_H_

#include <string.h>
#include <stdint.h>
#include <utils.h>
#include <rturegcollector.h>

#define MODBUSRTU_MAX_RECV_SIZE     300  //300 байт максимальный размер пакета MODBUS


/*
 * Информация о регистрах
 * 0x00 - Режим работы (0 - по массе, 1 - по времени)
 */

class TModBusRTUDrv {
private:
	uint8_t *RecvBuffer;                      //Кольцевой буффер
	uint8_t *SendBuffer;
	uint16_t BufPos;
	char auchCRCHi[0x100];                             //Таблица старших битов для вычисления контрольнйо суммы
	char auchCRCLo[0x100];                             //Таблица младших битов для вычисления контрольной суммы
	uint8_t portcfg[0x03];                             //[0] - Data bit [1] = parity [2] = stop bits
	unsigned short CRC16(char *puchMsg,unsigned short usDataLen);
	TUtils *utils;
	uint8_t err_state;
	typedef void (*SendDataFunc)(char *data,uint16_t datalen);
	typedef void (*SetUARTParamsFunc)(uint32_t speed, uint8_t databits, uint8_t stopbit, uint8_t parity);
	typedef void (*ApplyParamsFunc)();
	//Функция получения данных на отправку
	typedef TRegCollection *(*GetDataFunc)();
	//Работа с кодом функции 0x04  MODBUSRTU_MULTIREADREG
	void MODBUSRTU_MULTIREADREG_PROC();
	//Работа с кодом функции 0x06  MODBUSRTU_WRITESINGLEREG
	void MODBUSRTU_WRITESINGLEREG_PROC();
	//Работа с кодом функции 0x10  MODBUSRTU_WRITEMULTIREG
	void MODBUSRTU_WRITEMULTIREG_PROC();
	//Обработка неизвестного номера функции
	void MODBUSRTU_UNKNOWN_REGISTER_PROC();
public:
	TModBusRTUDrv(TUtils *u);
	uint8_t *PROTOCOL_BUFFER;
	uint8_t DEVICE_ADDRESS;
	uint32_t MODBUS_DELAY;
	uint32_t BAUDRATE;
	void ClearBuffer();                                      //Очистка кольцевого буффера
	void AddDataToBuffer(uint8_t *data);
	void Protocol_Progress();                                //Обработка пришедшего пакета
	void SetBuffers(uint8_t *recvbuf, uint8_t *sendbuf);
	SendDataFunc SendData;
	SetUARTParamsFunc SetUARTParams;
	ApplyParamsFunc ApplyParams;
	GetDataFunc GetData;
	uint16_t RTUPortConfigToPCArr(char *outval);               //Для передачи на ПО и флеш память
	uint16_t PCArrToRTUPortConfig(char *inval);                //Для загрузки из ПО и флеш память
	void SetErrorState(uint8_t state);                         //Установка статуса ошибок
	virtual ~TModBusRTUDrv();
};

#endif /* SRC_MODBUSRTUDRV_H_ */
