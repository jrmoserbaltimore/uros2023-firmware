
typedef struct {
  signed char LeftX;
  signed char LeftY;
  signed char RightX;
  signed char RightY;
} JoystickValues;

typedef struct {
  // Shoulder buttons
  bool R1, R2, L1, L2;
  // Right face buttons
  bool A, B, X, Y;
} ButtonValues;


void getJoystickValues(JoystickValues &js);
void getButtonValues(ButtonValues &buttons);
