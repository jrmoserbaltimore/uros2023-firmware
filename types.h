
typedef struct {
	signed char LeftX;
	signed char LeftY;
	signed char RightX;
	signed char RightY;
} JoystickValues;

typedef struct {
	bool R1;
	bool R2;
	bool L1;
	bool L2;
} ButtonValues;


void getJoystickValues(JoystickValues &js);
void getButtonValues(ButtonValues &buttons);
