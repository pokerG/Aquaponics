/*
| 设备码	| 设备类型	| 作用			|
| -----	| -------------	| ---------------------	|
| 0x01	| 步进电机	| 控制LED阵列红灯		|
| 0x02	| 步进电机	| 控制LED阵列蓝灯		|
| 0x03	| 步进电机	| 控制喂鱼器		|
| 0x04	| 继电器		| 控制滴定酸液蠕动泵	|
| 0x05	| 继电器		| 控制滴定碱液蠕动泵	|
| 0x06	| 继电器		| 控制日光灯		|
| 0x07	| 继电器		| 控制补水泵		|
| 0x08	| 继电器		| 控制抽水泵		|
| 0x09	| 继电器		| 控制氧气泵		|
| 0x0A	| 继电器		| 控制造浪泵		|
*/
#define ID_LRED 0x1
#define ID_LBLE 0x2
#define ID_FFSH 0x3
#define ID_PACI 0x4
#define ID_PALK 0x5
#define ID_LFLU 0x6
#define ID_PSUP 0x7
#define ID_PREC 0x8
#define ID_POXY 0x9
#define ID_PFLW 0xA

/*
| 控制码	| 作用	|
| -----	| -----	|
| 0xFF	| 通电	|
| 0x00	| 断电	|
*/
#define ON 0xFF
#define OFF 0x00

/*
对电机设备，八位控制码由方向位(1bit)、转速位(7bit)两部分组成
*/
#define MOTOR_CTR(D,S) \
(D << 7 + S)

/*
控制指令由两字节组成，第一字节代表设备码，第二字节代表控制码
*/
struct CMD
{
	unsigned char id;
	unsigned char ctr;
};

/*
| 设备码	| 设备类型	| 作用			|
| -----	| -------------	| ---------------------	|
| 0x01	| 湿度传感器	| 监测陶粒基质湿度		|
| 0x02	| 温度传感器	| 监测菜盘温度		|
| 0x03	| 水位传感器	| 监测菜盘水位高度		|
| 0x04	| 光敏电阻	| 监测外界对菜盘光照强度	|
| 0x05	| 温度传感器	| 监测鱼缸水温		|
| 0x06	| 水位传感器	| 监测鱼缸水位		|
| 0x07	| pH传感器	| 监测鱼缸水质pH值	|
*/
#define ID_SHU0 0x1
#define ID_STP0 0x2
#define ID_SWL0 0x3
#define ID_SRL0 0x4
#define ID_STP1 0x5
#define ID_SWL1 0x6
#define ID_SPH1 0x7

/*
传感器数据由三字节组成，第一字节代表设备码，第二、三字节代表数据
*/
struct DAT
{
	unsigned char id;
	unsigned int dat;
};