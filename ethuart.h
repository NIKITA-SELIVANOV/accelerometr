/*
 * ethuart.h
 *
 *  Created on: Aug 3, 2023
 *      Author: a.zavyalov
 */

#ifndef SRC_ETHUART_H_
#define SRC_ETHUART_H_

#include <main.h>
#include <utils.h>
#include <stdio.h>

#define USR_TCP232_DEVICE_NONE  0x00
#define USR_TCP232_DEVICE_V1    0x01
#define USR_TCP232_DEVICE_V2    0x02
#define USR_TCP232_DEVICE_V3    0x03

/*
 * Данный драйвер является независимой оболочкой для настройки и только для настройки модуля ETHERNET
 * Для простого обмена данными нужно реализовывать собственный метод
 * Для работы с модулями ETH<->UART от компании waveshare
 * Старый модуль https://www.waveshare.com/product/iot-communication/wired-comm-converter/ethernet-to-uart-rs232-rs485/uart-to-eth.htm
 * Распиновка
 *
 *
 * Новый модуль https://www.waveshare.com/product/iot-communication/wired-comm-converter/ethernet-to-uart-rs232-rs485/2-ch-uart-to-eth.htm
 * Распиновка
 * 5V / 3V3	power positive, use any pin of 5V/3.3V pins for power supply
 * GND ground
 * RST1 external reset input, low active
 * RESET restore to factory setting, detected when chip poweron, low active
 * TXD1 asynchronous UART 1 data output (enabled by default)
 * TXD2 asynchronous UART 2 data output (disabled by default)
 * RXD1 asynchronous UART 1 data input (enabled by default)
 * RXD2 asynchronous UART 2 data input (disabled by default)
 * CFG0 UART config mode, low level to enter configuration, high level to exit configuration
 * RUN Operating status indicating pin
 * DIR1 UART 1 RS485 RX/TX switch (connects to external RS485 controller)
 * DIR2 UART 2 RS485 RX/TX switch (connects to external RS485 controller)
 */
/*
 * Модуль работает в режими Сервера ожидая входящие соединения
 * Работа ведёться по двум портам, 1 порт рабочий, для передачи информации по протоколу MODBUS TCP
 * А второй сервисный, для получения данных и настроек
 * ===================================================
 * 1. DHCP
 * 2. IP
 * 3. Mask
 * 4. GateWay
 * 5. Port1->Mode
 * 6. Port1->Local Port->Port
 * 7. Port1->Baudrate
 * 8. Port1->Clear buff
 * 9. Port2->On/Off
 * 10. Port2->Mode
 * 11. Port2->Local Port->Port
 * 12. Port2->Baudrate
 *
 */

struct TEthCfgStruct
{
	bool DHCP;
	uint8_t LOCAL_IP[0x04];          //Локальный IP адресс порта 1
	uint8_t LOCAL_MASK[0x04];
	uint8_t LOCAL_GATEWAY[0x04];
	uint8_t MODE_PORT1;              //Режим работы порта 1
	uint16_t LOCAL_PORT1;            //Локальный порт порта 1
	uint32_t BAUDRATE_PORT1;         //Скорость порта 1
	bool CLEAR_BUFF_PORT1;           //Очистка буффера порта 1
	uint8_t MODE_PORT2;              //Режим работы порта 2
	uint16_t LOCAL_PORT2;            //Локальный порт порта 2
	uint32_t BAUDRATE_PORT2;         //Скорость порта 2
};

#define MAX_TX_BUF                    0x7F   //Максимальная длина посылаемых данных для настройки

//1. DHCP
#define ETH_SET_DHCP                  0x33    //Режим DHCP 1-включён 0-выключен          1 байт
#define ETH_GET_DHCP                  0x83    //Получает режим DHCP
//2. IP
#define ETH_SET_LOCAL_IP              0x11    //Устанавливает локальный IP адрес модуля  4 байта
#define ETH_GET_LOCAL_IP              0x61    //Получает локальный IP адрес модуля
//3. Mask
#define ETH_SET_SUBNET_MASK           0x12    //Устанавливает Маску подсети              4 байта
#define ETH_GET_SUBNETMASK            0x62    //Получаем маску подсети
//4. GateWay
#define ETH_SET_GATEWAY               0x13    //Шлюз                                     4 байта
#define ETH_GET_GATEWAY               0x63    //Получаем шлюз
//5. Port1->Mode
#define ETH_SET_MODE1                 0x10    //Режим порта 1:                           1 байт
                                              //0x00:TCP Сервер
                                              //0x01:TCP Клиент
                                              //0x02:UDP Сервер
                                              //0x03:UDP Клиент
#define ETH_GET_MODE1                 0x60    //Режим работы порта1
//6. Port1->Local Port->Port
#define ETH_SET_LOCAL_PORT1           0X14    //Номер локального порта 1                 2 байта
#define ETH_GET_LOCAL_PORT1           0x64    //Локальный порт порта1
//7. Port1->Baudrate
#define ETH_SET_BAUDRATEPORT1         0x21    //Baud rate серийного порта 1              4 байта
#define ETH_GET_BAUDRATEPORT1         0x71    //Скорость порта 1
//8. Port1->Clear buff
#define ETH_SET_CLEARBUFFPORT1        0x26    //Очищать ли буффер если соединение установлено 1 байт
#define ETH_GET_CLEARBUFFPORT1        0x76    //Получаем очищать ли буффер если соединение установлено
//9. Port2->On/Off
#define ETH_SET_ON_OFF_UART2          0x39    //Включение/выключение порта 2             1 байт
//10. Port2->Mode
#define ETH_SET_MODE2                 0x40    //Режим порта 2:                           1 байт
                                              //0x00:TCP Сервер
                                              //0x01:TCP Клиент
                                              //0x02:UDP Сервер
                                              //0x03:UDP Клиент
#define ETH_GET_MODE2                 0x90    //Режим работы порта 2
//11. Port2->Local Port->Port
#define ETH_SET_LOCAL_PORT2           0X41    //Номер локального порта 2                 2 байта
#define ETH_GET_LOCAL_PORT2           0x91    //Локальный порт порта 2

//12. Port2->Baudrate
#define ETH_SET_BAUDRATEPORT2         0x44    //Baud rate серийного порта 2              4 байта
#define ETH_GET_BAUDRATEPORT2         0x94    //Скорость порта 2


class TEthUartDrv {
private:
	bool inCFGmode;
	bool timerneed;
	int16_t timer;
	uint16_t BufPos;
	uint8_t *RecvBuffer;
	GPIO_TypeDef* ETH_RESET_PORT;
	uint16_t ETH_RESET_PIN;
	GPIO_TypeDef* ETH_CFG_PORT;
	uint16_t ETH_CFG_PIN;
	TEthCfgStruct base;       //Содержит устанавливаемы настройки модуля
	TEthCfgStruct modulecfg;  //Содержит текущие настройки модуля
	char TX[MAX_TX_BUF];
	uint8_t RX[MAX_TX_BUF];
	uint8_t cfgstep;
	uint8_t rxcounter;
	bool err_state;
	uint16_t setcounter;
	bool changes[0x0F];
	uint8_t usedmodulever;
	TUtils *utils;
	void ETH_Run();           //Запуск модуля
	void ETH_CfgStart();      //Запуск конфигурации модуля
	void ETH_Progress_V2();
	void ETH_PCprotocolwork_V2(uint8_t *data, uint16_t size);
	void ETH_Progress_V3();
	void ETH_PCprotocolwork_V3(uint8_t *data, uint16_t size);
	typedef void (*SendDataFunc)(char *data,uint16_t datalen);
	typedef void (*Set9600UARTSpeedFunc)();
	typedef void (*Set115200UARTSpeedFunc)();
public:
	TEthUartDrv(TUtils *u);
	void SetCFG_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
	void SetRST_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
	SendDataFunc SendData;
	Set9600UARTSpeedFunc Set9600UARTSpeed;
	Set115200UARTSpeedFunc Set115200UARTSpeed;
	void ETH_Reset();         //Сброс модуля
	void ETH_Stop();          //Остановка модуля
	void ETH_CfgStop();       //Остановка конфигурации модуля
	void ETH_ApplyConfigs();  //Применение настроек и перезапуск модуля
	bool SRVMode();           //Возвращает находится ли сейчас модуль в режиме установки конфигурации
	void ETH_ProgressTimer(); //Внутренний таймер
    void ETH_Progress();      //Внутренний проргесс
    void ETH_PCprotocolwork();
    void ETH_ModuleRun();     //Просто запуск модуля
    uint16_t ETH_CfgToPCArr(char *outval);
    uint16_t ETH_PCArrToCfg(char *inval);
    void SetModuleVersion(uint8_t ver);
    bool GetErrorState();
    void ResetError();
    void AddDataToBuffer(uint8_t *data);
    void SetBuffer(uint8_t *buf);
	virtual ~TEthUartDrv();
};

#endif /* SRC_ETHUART_H_ */
