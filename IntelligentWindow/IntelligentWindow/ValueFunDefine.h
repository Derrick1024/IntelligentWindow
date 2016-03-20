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

// 本来想定义成class的，但是在另一个类中引用这个类出现了无定义问题，类不能用extern来包含
// 没时间研究了，就索性改成了struct，就可以用exrern了
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



