/*
 * modbustcpdrv.h
 *
 *  Created on: Aug 11, 2023
 *      Author: a.zavyalov
 */

#ifndef SRC_MODBUSTCPDRV_H_
#define SRC_MODBUSTCPDRV_H_

#include <string.h>
#include <stdint.h>
#include <utils.h>
#include <rturegcollector.h>

#define MODBUSTCP_MAX_RECV_SIZE    300 //300 байт максимальный размер пакета MODBUS

#define MODBUSTCP_PROTOCOLNUM      0x00   //ID протокола ModBus
/*
 * Информация о регистрах
 * 0x00 - Режим работы (0 - по массе, 1 - по времени)
 */

class TModBusTCPDrv {
private:
	uint8_t *RecvBuffer;                      //Кольцевой буффер
	uint8_t *SendBuffer;
	uint16_t BufPos;
	TUtils *utils;
	uint8_t err_state;
	typedef void (*SendDataFunc)(char *data,uint16_t datalen);
	//Функция получения данных на отправку
	typedef TRegCollection *(*GetDataFunc)(void);
	//Работа с кодом функции 0x04  MODBUSRTU_MULTIREADREG
	void MODBUSRTU_MULTIREADREG_PROC();
	//Работа с кодом функции 0x06  MODBUSRTU_WRITESINGLEREG
	void MODBUSRTU_WRITESINGLEREG_PROC();
	//Работа с кодом функции 0x10  MODBUSRTU_WRITEMULTIREG
	void MODBUSRTU_WRITEMULTIREG_PROC();
	//Обработка неизвестного номера функции
	void MODBUSRTU_UNKNOWN_REGISTER_PROC();
public:
	TModBusTCPDrv(TUtils *u);
	uint8_t *PROTOCOL_BUFFER;
	uint8_t DEVICE_ADDRESS;
	void ClearBuffer();                                      //Очистка кольцевого буффера
	void AddDataToBuffer(uint8_t *data);
	void Protocol_Progress();                                //Обработка пришедшего пакета
	void SetBuffers(uint8_t *recvbuf, uint8_t *sendbuf);
	SendDataFunc SendData;
	GetDataFunc GetData;
	void SetErrorState(uint8_t state);
	virtual ~TModBusTCPDrv();
};

#endif /* SRC_MODBUSTCPDRV_H_ */
