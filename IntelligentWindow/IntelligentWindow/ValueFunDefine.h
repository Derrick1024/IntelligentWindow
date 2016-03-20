#define DHT11Pin 45
#define DHTTYPE DHT11
#define MotorPin0 3
#define MotorPin1 4
#define MotorPwm 5
#define RelayPin0 6
#define RelayPin1 7
#define LimitSwitchPin0 8
#define LimitSwitchPin1 9
#define LimitSwitchPin2 10
#define ServoPin0 11
#define ServoPin1 12
#define RainInPin0 A0

// �����붨���class�ģ���������һ���������������������޶������⣬�಻����extern������
// ûʱ���о��ˣ������Ըĳ���struct���Ϳ�����exrern��
struct SensorData
{
	float PM2_5;
	float TempOut;
	float TempIn;
	float HumiOut;
	float HumiIn;
	int RainOut;

};
struct CtrlData
{
	int WinState;

};



