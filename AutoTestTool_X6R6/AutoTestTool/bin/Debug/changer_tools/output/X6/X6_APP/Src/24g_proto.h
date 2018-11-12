#ifndef __24G_PROTO_H__
#define __24G_PROTO_H__

#include "includes.h"
#include "ckb24_um.h"
#include "main_handle.h"

#define RETRY_24G_MAX_CNT                           3
#define RESENT_24G_MSG_CNT                          30//20
#define RETRY_24G_DELAY_TIME                        40//150

#define SERIAL_NUM_DELAY_TIME                        2

#define INNER_VER_CMD_CHECKSUM            3
#define INNER_VER_CMD                     2
#define INNER_CHECK_SUM                   1
#define INNER_EE_LEN                   2

#define BTRF2_4G_GUNID1         1       //ǹͷ��1
#define BTRF2_4G_GUNID2         2       //ǹͷ��2

#define MAC_LEN                 5

#define PIECE_PKT_LEN_24G_SEND_TO_X6                50      //��Ҫ�޸�
#define LEN_OF_BTRF24G_PROTO_DATA                   200


#define RECEIVE_MAX_PKT_24G            1


enum {
    EVENT_OCCUR = 1,
    EVENT_RECOVER,
};

enum {
    SWIPE_CARD = 1,
    SCAN_CODE,
};

enum {
    CHIP_EMU = 0,                       //0.����оƬ
    CHIP_FLASH,                         //1.flash
    CHIP_E2PROM,                        //2.e2prom
    CHIP_BLUE,                          //3.����
};

enum {
    ONE_TIMES = 0,
    MANY_TIMES,
};

enum{
	CMD_CARD_AUTH_24G						= 0x01,	//��Ȩ����
	CMD_CARD_AUTH_RESULT_RETURN_24G			= 0x02,	//��Ȩ�������
	CMD_START_CHARGER_24G					= 0x03,	//�����������
	CMD_STOP_CHARGER_24G					= 0x04,	//����������
	CMD_CHARGER_STARTED_24G 				= 0x05,	//��翪ʼ֪ͨ
	CMD_CHARGER_STOPED_24G 					= 0x06,	//������֪ͨ
	CMD_HEART_BEAT_24G						= 0x07,	//����
	CMD_COST_DOWN_24G						= 0x08,	//�Ʒ�ģ���·�
	CMD_COST_REQ_24G						= 0x09,	//����Ʒ�ģ��
	CMD_FW_UPGRADE_NOTI_24G 				= 0x0A,	//�̼�������ʼ֪ͨ
    CMD_FW_DOWN_LOAD_24G					= 0x0B,	//�̼��·�
	CMD_FW_UPGRADE_REQ_24G					= 0x0C,	//����̼�����
	CMD_REMOTE_CTRL_24G						= 0x0D,	//Զ�̿���
	CMD_SYSTEM_LOG_24G						= 0x0E,	//ϵͳ��־
	CMD_EVENT_NOTICE_24G					= 0x0F,	//�¼�֪ͨ
	CMD_ENUM_BIND_ACK       				= 0x10,         //16 �豸ö�٣���R6����X6׮��
	CMD_SCAN_CODE_START_CHARGE     			= 0x20,         //ɨ�뿪������ʾ���ܵ�X6�Ŀ������Ӧ��
};

//1��ϵͳ��������2������ǹͷ3���ر�ǹͷ4������/�˳� ������״̬5���趨����������
//6���趨����������ֵ7���趨����ʱ����ֵ8���趨��ǹʱ����ֵ9����ǹ�Ƿ�ֹͣ��綩��
//10������ˢ���幤��ģʽ11���������12�����ô�ӡ����

enum {
    SYSTEM_REBOOT = 1,
    START_CHARGING = 2,
    STOP_CHARGING = 3,
    STOP_SERVER = 4,
    MAX_OUT_POWER = 5,
};

#pragma pack(1)


typedef struct {
    uint8_t ee;                                //0.
    uint8_t len;                               //1.
    uint8_t SerialNum;//ver;                               //2.
    uint8_t cmd;                               //3.
}PROTO_HEAD_BTRF24G_TYPE;

typedef struct {
    PROTO_HEAD_BTRF24G_TYPE head;
    uint8_t  data[LEN_OF_BTRF24G_PROTO_DATA];							//msg+checksum
}PROTO_STR_BTRF24G_TYPE;

// card identify request   ˢ����Ȩ
typedef struct {
	uint8_t  gun_id;                            //0.ǹ��
    uint8_t  optType;                           //2�� 0��ˢ����Ȩ����ʼ��磻1������ѯ��2���ֻ��û������Ȩ
	uint8_t  card_id[8];                       //3. �û��˺ţ����߿��ţ�
	uint8_t  card_psw[3];                       //4. �û��˺���֤����
    uint8_t  mode;                              //5.���ģʽ  0�����ܳ��� 1������� 2����ʱ�� 3��������
	uint16_t chargingPara;                      //6.������  ���ܳ�����Ϊ0  �����ֱ���1��  ��ʱ�����ֱ���1����  ���������ֱ���0.01kwh
}CARD_AUTH_REQ_STR_24G;
typedef struct {
    uint8_t  gun_id;                            //0.    ǹ��
	uint8_t  result;                            //1.��Ȩ��� 0:��Ȩ�ɹ��� 1��������� 2�� ������ߴ��������ꣻ 3������ʹ�ã�����ͬʱʹ�ã�4���˻���Ч�� 5������ԭ��
	uint8_t  cardType;                          //2. 1�¿�
	uint32_t user_momey;                        //4.�˻����ֱ��� 1 ��
	uint8_t  order[ORDER_SECTION_LEN];          //5.������  ��̨���ɵĳ�綩����
}CARD_AUTH_ACK_STR_24G;

// remote control power-on/off   Զ���������
typedef struct {
	uint8_t  gun_id;                            //ǹ��
	uint8_t  mode;                              //���ģʽ  0�����ܳ��� 1������� 2����ʱ�� 3��������
	uint16_t chargingPara;                      //������  ���ܳ�����Ϊ0 ; �����ֱ���1��; ��ʱ�����ֱ���1����; ���������ֱ���0.01kwh
	uint8_t  order[ORDER_SECTION_LEN];          // ������
}START_CHARGING_REQ_STR_24G;

typedef struct {
    uint8_t  gunId;         //
	uint8_t  result;        //
}START_CHARGING_ACK_STR_24G_TYPE;

typedef struct {
	uint32_t  ServerTime;                           //������ʱ��
}R6X6_BIND_REQ_STR_24G_TYPE;

typedef struct {
    uint8_t  deviceID[5];         //
	uint8_t  baseGunSn;        //
}R6X6_BIND_ACK_STR_24G_TYPE;

typedef struct {
    uint8_t  gun_id;                            //0
	uint8_t  result;                            //0:�����ɹ�  1: ����ʧ��
    uint8_t  failReason;                        //1���˿ڹ��� 2��û�мƷ�ģ�� 3���Ѿ��ڳ���� 4���豸û��У׼ 5����������
}START_CHARGING_ACK_STR_24G;

typedef struct {
    uint8_t  gun_id;                            //0
	uint8_t  ReqFwVer;                            //����̼��汾��
	uint32_t  AddrOffset;                            //�̼���ַƫ�� , �Ӵ˴���ʼ��������
}UPGRADE_REQ_STR_BTRF2_4G_TYPE;

typedef struct {
	uint8_t  result;                            // 0�� ���������� 1�� ��������
}UPGRADE_ACK_STR_BTRF2_4G_TYPE;

//Զ�̽������
typedef struct {
	uint8_t  gun_id;
	uint8_t stopReason;
}STOP_CHARGING_REQ_STR_24G;

typedef struct {
    uint8_t  gun_id;
	uint8_t  result;            //0: �ɹ��� 1: ʧ��
}STOP_CHARGING_ACK_STR_24G, CARD_AUTH_ACK_RETURN_STR_24G;

typedef struct {
	uint8_t  gun_id;
    uint8_t  result;                            //0�����ճɹ���1������ʧ��
}ACK_X6_RECEIVED_SCAN_CODE_STR;

// report device result power-on/off  ��翪ʼ֪ͨ
typedef struct {
	uint8_t  gun_id;                            //1.
	uint8_t  user_type;                         //2.
    uint8_t  optType;                           //3. 1���״��������֪ͨ 2����������߻ָ��ط� 3�������ϵͳ����ָ��ط�
	uint8_t  user_account[20];                  //4.�û��˺�
	uint8_t  order[ORDER_SECTION_LEN];          //5. ������
	uint32_t start_time;                        //6.��ʼ���ʱ��
	uint32_t start_power;                       //7.��ʼ������
	uint32_t money;                             //8.Ԥ���ѽ��  ��λ���֣����γ��Ԥ�����ѵĽ����Ϊȫ0xff������
	uint8_t result;
}START_CHARGING_NOTICE_STR_24G;

// report device result power-on/off  ��翪ʼ֪ͨ
typedef struct {
	uint8_t  gun_id;                            //1.
	uint8_t  order[ORDER_SECTION_LEN];          // ������
	uint32_t start_time;                        //��ʼ���ʱ��
	uint8_t result;                             //�������
}START_CHARGING_NOTICE_STR_24G_TYPE;

typedef struct {
    uint8_t  gun_id;
	uint8_t  result;
	uint8_t  order[ORDER_SECTION_LEN];
}START_CHARGING_NOTICE_ACK_STR_24G;


//������֪ͨ
typedef struct {
	uint8_t  gun_id;                            //1.
	uint8_t  user_type;                         //2.
    uint8_t  stop_reason;                       //3.����ԭ��
    uint8_t  stopDetal;                         //4.������ԭ��ϸ��
    uint32_t errStatus;                         //5.���������������ֹ����쳣״̬
    uint8_t  fwVer;                             //6.�̼��汾
	uint8_t  user_account[20];                  //7.�û��˺�
	uint8_t  order[ORDER_SECTION_LEN];          //8.������
	uint32_t startTime;                         //9.��ʼ���ʱ��
	uint32_t stop_time;                         //10.�������ʱ��
	uint32_t startElec;                         //11.��ʼ������
	uint32_t stop_power;                        //12.����������
	uint32_t charger_cost;                      //13.��������  ��
	uint32_t template_id;                       //14.����id
	uint16_t chargingPower;                     //15.�����ʶμƷѵĹ��ʣ���λ��w
}STOP_CHARGING_NOTICE_REQ_STR_24G;

//BTRF2_4G������֪ͨ
typedef struct {
	uint8_t  gun_id;                            //1.
    uint8_t  stop_reason;                       //3.����ԭ��
    uint8_t  stopDetal;                         //4.������ԭ��ϸ��
	uint32_t startTime;                         //9.��ʼ���ʱ��
	uint16_t chargingTime;                      //9.���ʱ��
	uint16_t chargingElec;                         //11.������  0.01kwh
	uint16_t charger_cost;                      //13.��������  ��
	uint16_t chargingPower;                     //15.�����ʶμƷѵĹ��ʣ���λ��w
	uint8_t  order[ORDER_SECTION_LEN];          //������
}STOP_CHARGING_NOTICE_REQ_STR_BTRF2_4G_TYPE;

//BTRF2_4G������¼
typedef struct {
	uint8_t  gun_id;                            //1.
    uint8_t  stop_reason;                       //3.����ԭ��
    uint8_t  stopDetal;                         //4.������ԭ��ϸ��
	uint32_t startTime;                         //9.��ʼ���ʱ��
	uint16_t chargingTime;                      //9.���ʱ��
	uint16_t chargingElec;                         //11.������  0.01kwh
	uint16_t charger_cost;                      //13.��������  ��
	uint16_t chargingPower;                     //15.�����ʶμƷѵĹ��ʣ���λ��w
	uint8_t  order[ORDER_SECTION_LEN];          //������
}ORDER_REPORT_NOTICE_BTRF2_4G_TYPE;

typedef struct {
    uint8_t  isStopChargeFlag;
	uint8_t  isStartChargeFlag;
}START_OR_STOP_CHARGING_BTRF2_4G_TYPE;

typedef struct {
    uint8_t  StartChargeFlag[GUN_NUM_MAX];
}START_CHARGING_STR;

typedef struct {
	uint8_t  isNeedToStartChargeFlag;
    uint8_t  gun_id;                            //ǹ��
	uint8_t  mode;                              //���ģʽ  0�����ܳ��� 1������� 2����ʱ�� 3��������
	uint32_t chargingPara;                      //������  ���ܳ�����Ϊ0 ; �����ֱ���1��; ��ʱ�����ֱ���1����; ���������ֱ���0.01kwh
	uint8_t  order[ORDER_SECTION_LEN];          // ������
	uint8_t isStartChargeSN;
}IS_START_CHARGING_BTRF2_4G_TYPE;


//����������󳤶� 22*12+7=271
typedef struct {
    uint8_t  gunIndex;                          //1.
    uint8_t  status;                            //3.����״̬ 0 ���� 1 ռ��δ�򿪻�ر� 2 ռ���Ѵ򿪣������ 3 ����
    uint8_t  faultCode;                         //4.
    uint8_t  voltage;                           //5. ��ѹ 1V /����
    uint16_t current;                           //6.������� �ֱ��ʣ�0.1A/����
    uint16_t power;                             //7.������ʣ���λ����
    uint16_t elec;                              //8.
    uint16_t money;                             //9.
    uint8_t  resvered[4];				        //10.
}GUN_HEART_BEAT_STR_24G;

//  ң�ż�����
typedef struct {
	uint32_t  ServerTime;                           //������ʱ��
    uint32_t cost_modeID;						    //�Ʒ�ģ��ID
    uint8_t  fwVer;                            //�̼��汾
    uint8_t  gwMAC[MAC_LEN];                           //���ص�ַ
    uint8_t  baseGunSn;				            //��ʼǹͷ
}HEART_BEAT_REQ_STR_BTRF2_4G_TYPE;


typedef struct {
    uint8_t gun_id;                        //���ӿ� 1 ���
    uint8_t ChargeStatus;                  //3.����״̬ 0 ���� 1 ռ���Ѵ򿪣������ 2 ����
    uint8_t errStatus;                   // 1 ״̬�쳣 2 ����оƬͨ�Ź���
    uint8_t reserve[2];                 //����
}HEART_BEAT_CHARGE_PORT_BTRF2_4G_TYPE;

typedef struct {
    uint8_t gun_id;                        //���ӿ� 1 ���
    uint8_t ChargeStatus;                  //3.����״̬ 0 ���� 1 ռ���Ѵ򿪣������ 2 ����
    uint8_t errStatus;                   // 1 ״̬�쳣 2 ����оƬͨ�Ź���
    uint8_t voltage;           //����ѡ�� ����״̬ Ϊ ����� ���У� ʵʱ�����ѹ����λ��
	uint8_t current;           //����ѡ������״̬ Ϊ ����� ���У� ʵʱ������� �ֱ��ʣ� 0.1A/����
	uint16_t power;             //����ѡ������״̬ Ϊ ����� ���У� ������ʵʱ������ʣ���λ����
	uint16_t elec;              //����ѡ������״̬ Ϊ ����� ���У� ����ۼƵ��� ��λ�� 0.01 ��/����
	uint16_t ChargeCost;        //����ѡ������״̬ Ϊ ����� ���У� ��λ �֣�
	uint8_t reserve[2];                 //����
}HEART_BEAT_CHARGE_INFO_BTRF2_4G_TYPE;

typedef struct {
	uint8_t temperature;			//�����¶�
	uint8_t includeVer;			//include�ļ�����İ汾��
	uint8_t timestamp;             //���α����������ĳ��ӿ���Ŀ
#if 1
    uint8_t Data[13 * GUN_NUM_MAX];
#else
	union {
        HEART_BEAT_CHARGE_PORT_BTRF2_4G_TYPE ChargePort;
        HEART_BEAT_CHARGE_INFO_BTRF2_4G_TYPE ChargeInfo;
    }Data[GUN_NUM_MAX];
#endif
}HEART_BEAT_ACK_STR_BTRF2_4G_TYPE;

//�Ʒ�ģ��
typedef struct {
    uint16_t startPower;                        //��ʼ���� ��λw
    uint16_t endPower;                          //�������� ��λw
    uint16_t price;                             //ָ��ʱ�������ã��ֱ��ʷ�
    uint16_t duration;                          //�Ʒ�ʱ��,����  ����=100,ʱ��=120��ʾ1Ԫ��2Сʱ
}segment_str_24g;

typedef struct {
    uint8_t  segmentCnt;                        //���ʶ���Ŀ��1~6
    segment_str_24g segmet[6];
}multiPower_t_24g;

typedef struct {
    uint16_t  price;                            //ָ��ʱ�������ã��ֱ���:��
    uint16_t  duration;                         //�Ʒ�ʱ��,����  ����=100,ʱ��=120��ʾ1Ԫ��2Сʱ
}unify_t_24g;

// cost template   �Ʒ�ģ������
typedef struct {
    uint8_t  gunId;                             //0 ǹ��
	uint32_t template_id;                       //1.�Ʒ�ģ����
    uint8_t  mode;                              //2. 1�������ʶμƷ� 2��ͳһ�շ�
    uint8_t  cost_mode;                         //2. 1���̶��Ʒ� 2 ʵʱ�Ʒ�
	uint16_t chargerStartingGold;				//�𲽽� add
	union {
        multiPower_t_24g powerInfo;
        unify_t_24g unifyInfo;
    }Data;
}COST_TEMPLATE_REQ_STR_24G;
typedef struct {
    uint8_t  gunId;         //ǹͷ���: 0 ���ʾ��׮, 1 ��ʼ��ʾ����ǹͷ
	uint8_t  result;        //0: ���³ɹ��� 1: �ֹ��ʶ������� 2���Ʒ�ʱ��Ϊ 0�� 3��ģʽ����
}COST_TEMPLATE_ACK_STR_24G;


//�����·��Ʒ�ģ��
typedef struct{
    uint8_t  gun_id;                            //1.
}REQ_COST_TEMPLATE_STR_24G;


// �̼���������
typedef struct{
	uint32_t     file_size;                 //�ļ���С     
    uint16_t     package_num;               //�̼���Ƭ����       
	uint32_t     checkSum;                  //У����
    uint8_t      fwverson;                  //�̼��汾��
}FW_UPGRADE_NOTI_REQ_STR_24G;
typedef struct {
	uint8_t UpgeadeState;                             // 0������������ 1����������
}FW_UPGRADE_NOTI_ACK_STR_24G;

//�̼��·�
typedef struct{
    uint16_t package_num;               //�̼���Ƭ���
	uint8_t  checkSum;           //�̼���ƬУ����
	uint8_t  len;               //�̼���Ƭ����
	uint8_t  data[PIECE_PKT_LEN_24G_SEND_TO_X6];         //�̼���Ƭ����
}DOWN_FW_REQ_STR_24G;
typedef struct{
	uint8_t result;             //0�� ���ճɹ��� 1������ʧ�� 2��ֹͣ����
	uint16_t package_num;       //�̼���Ƭ��� X6���͸�R6˵��Ҫ������һ����Ƭ��
	uint8_t gunId;              //ǹͷ��
}DOWN_FW_ACK_STR_24G;

//����̼�����
typedef struct{
	uint8_t gunid;
	uint8_t verson;
}UPGRADE_REQ_STR_24G;
typedef struct{
	uint8_t result;
}UPGRADE_ACK_STR_24G;


//Զ�̿���
typedef struct {
    uint8_t  optCode;                           //1��ϵͳ�������� 2������ǹͷ 3���ر�ǹͷ 4������ά��״̬���رճ����� 5������������ 6���趨����������
    uint32_t para;                              //���Ʋ���  ������趨���ʣ���λ��kw
}REMO_CTRL_REQ_STR_24G;
typedef struct {
    uint8_t  gun_id;        //���ӿڱ�� , ����� 0 ��ʾ��׮,  1~128,�����ӿ�
    uint8_t  result;        //0���ɹ��� 1��ʧ��
}REMO_CTRL_ACK_STR_24G;


//��־�ϴ�
typedef struct {
    uint8_t  gun_id;
    uint8_t  logType;                           //1��������־ 2��ͳ����Ϣ
    uint8_t  data[128];
}SYS_LOG_STR_24G;


/*
    1������
    2���ػ�
    3������
    4���������ӶϿ�
    5���������ӶϿ�������
    6���������
    7���������
    8������
    9���β�ͷ
    10��������ͨ�Ź���
    11������˿�۶�
    12�����س���
    13����ο������ʧ��
    14����������Ԥ��
    15��оƬ����Ԥ��
    16����������
    17��У׼�쳣
    18: ��������
    */
//�¼�֪ͨ
typedef struct {
    uint8_t  gun_id;                            //0. �����0��ʾ��׮,1~128,�����ӿ�
    uint8_t  code;                              //1. �¼����� 1��������ͨ�Ź��ϣ� 2������˿�۶ϣ� 3�����س��ޣ� 4����������Ԥ���� 5����������
    uint8_t  para1;                             //2.
    uint32_t para2;                             //3.
    uint8_t  status;                            //4.1������  2���ָ�
                                                    //��Щ�¼��в����ͻָ���״̬�����磺
                                                    //����ͨ�Ź��ϣ� 1���й��� 2�����ϻָ�
                                                    //��������Ԥ�� 1���и��� 2���½��ָ�
    uint8_t  level;                             //5.�¼��ȼ� 1��ʾ  2�澯  3���ع���
}EVENT_NOTICE_STR_BTRF2_4G;

typedef struct {
	uint8_t gun_id;
	uint8_t result;
}EVENT_NOTICE_ACK_STR_24G;


#pragma pack()


extern uint8_t gFlashCacheBuff[SPI_FLASH_PAGE_SIZE];

uint8_t SendEventNotice_BTRF2_4G(uint8_t gunId,uint8_t event,uint8_t para1,uint32_t para2,uint8_t status,uint8_t  level);
int SendReqCostTemplate_BTRF2_4G(uint8_t gunId);
int SendStopChargingNotice_BTRF2_4G(uint8_t gun_id);
int SendHeartBat_BTRF2_4G(void);
int MakeGunHearBeatInfo(GUN_HEART_BEAT_STR_24G *pInfo, uint8_t gun_id);
int SendCardAuthReq_24G(int flag);
/*****************************************************************************
** Function name:       SendStartChargingNoticeBTRF_24G
** Descriptions:        //RF2_4G�������֪ͨ
** input parameters:    gun_id: ǹ��
                        startTime: ��翪ʼʱ��
                        result: �����
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern int SendStartChargingNoticeBTRF_24G(int gun_id, uint32_t startTime, uint8_t result,uint8_t SerialNum);
/*****************************************************************************
** Function name:       X6ToR6HeartBatACK_BTRF2_4G
** Descriptions:        //������Ӧ
** input parameters:    pMsg: �ڲ�Э������ͷָ��
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern void X6ToR6HeartBatACK_BTRF2_4G(void);
/*****************************************************************************
** Function name:       FWUpgradeREQ_BTRF2_4G
** Descriptions:        //�̼�����������Ӧ
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern void FWUpgradeREQ_BTRF2_4G(uint8_t gun_id);
/*****************************************************************************
** Function name:       SpeechSelectGun
** Descriptions:        �����������û�ѡ��ǹ��
** input parameters:    
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern void SpeechSelectGun(uint8_t  gun_id);
/*****************************************************************************
** Function name:       SaveStopChargingNotice_BTRF2_4G
** Descriptions:        //RF2_4G����ֹͣ���֪ͨ��flash
** input parameters:    None
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern int SaveStopChargingNotice_BTRF2_4G(uint8_t gun_id);

/*****************************************************************************
** Function name:       StartChargingAckProc_24G
** Descriptions:        //�������Ӧ��
** input parameters:    result: 
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern void StartChargingAckProc_24G(uint8_t gun_id, uint8_t result, uint8_t SendFlag);
extern void _24gRecvProc(uint8_t *pbuff, uint16_t len);
/*****************************************************************************
** Function name:       isStartChargingBTRF2_4G
** Descriptions:        //��ѯ�Ƿ���Ҫ���������Ƿ������
** input parameters:    pMsg: �ڲ�����ͷָ��
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern void isStartChargingBTRF2_4G(void);
extern void SendStartChargingNotice(void);

/*****************************************************************************
** Function name:       isSendStartChargingBTRF2_4G
** Descriptions:        //�Ƿ���Ҫ���Ϳ������֪ͨ
** input parameters:    None
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern void isSendStartChargingBTRF2_4G(void);
/*****************************************************************************
** Function name:       SendOrderReportNotice_BTRF2_4G
** Descriptions:        //���Ͷ������򱣴�Ķ���
** input parameters:    None
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern int SendOrderReportNotice_BTRF2_4G(ORDER_REPORT_NOTICE_BTRF2_4G_TYPE * pSaveNoticeMsg, uint32_t SerialNum);

/*****************************************************************************
** Function name:       MuxSempTake
** Descriptions:        
** input parameters:    
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern int MuxSempTake(uint8_t *pSemp);

/*****************************************************************************
** Function name:       MuxSempGive
** Descriptions:        
** input parameters:    
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern void MuxSempGive(uint8_t *pSemp);

/*****************************************************************************
** Function name:       CloseUpgradeReqestFlag
** Descriptions:        //�رշ�����������
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern void CloseUpgradeReqestFlag(void);

/*****************************************************************************
** Function name:       OpenUpgradeReqestFlag
** Descriptions:        //open���Է������������־
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern void OpenUpgradeReqestFlag(void);

/*****************************************************************************
** Function name:       GetUpgradeReqestFlag
** Descriptions:        //��ȡ�������������־
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern int GetUpgradeReqestFlag(void);

/*****************************************************************************
** Function name:       CloseBlueToothUpgradeFlag
** Descriptions:        //�ر�����������־
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern void CloseBlueToothUpgradeFlag(void);

/*****************************************************************************
** Function name:       OpenBlueToothUpgradeFlag
** Descriptions:        //open����������־
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern void OpenBlueToothUpgradeFlag(void);

/*****************************************************************************
** Function name:       GetBlueToothUpgradeFlag
** Descriptions:        //��ȡ����������־
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern int GetBlueToothUpgradeFlag(void);

/*****************************************************************************
** Function name:       CloseUARTUpgradeFlag
** Descriptions:        //�ر�uart������־
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern void CloseUARTUpgradeFlag(void);

/*****************************************************************************
** Function name:       OpenUARTUpgradeFlag
** Descriptions:        //open����������־
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern void OpenUARTUpgradeFlag(void);

/*****************************************************************************
** Function name:       GetUARTUpgradeFlag
** Descriptions:        //��ȡ����������־
** input parameters:    pMsg
** output parameters:   None
** Returned value:		None
** Author:              quqian
*****************************************************************************/
extern int GetUARTUpgradeFlag(void);

/*****************************************************************************
** Function name:       FWDownLoadAckBTRF2_4G
** Descriptions:        //�̼��·�Ӧ��
** input parameters:    pMsg: �ڲ�Э������ͷָ��
                        result:   0�����ճɹ���1������ʧ�ܣ�2��ֹͣ����
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern void FWDownLoadAckBTRF2_4G(PROTO_STR_BTRF24G_TYPE  *pMsg, uint8_t result);

/*****************************************************************************
** Function name:       CheckUpgradeWaitTimer
** Descriptions:        //���������У�����50sû�н��յ�����˵�� R6 �Ѿ��ϵ��������
** input parameters:    None
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern void CheckUpgradeWaitTimer(void);

/*****************************************************************************
** Function name:       ClearUpgradeWaitTimer
** Descriptions:        //���¸�λ�ȴ�ʱ��
** input parameters:    None
** output parameters:   None
** Returned value:	  None
** Author:              quqian
*****************************************************************************/
extern void ClearUpgradeWaitTimer(void);
extern int GetPktSum(uint8_t *pData, uint16_t len);

#endif


