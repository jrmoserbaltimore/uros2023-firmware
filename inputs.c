/*
 * Inputs
 *
 * This source file obtains inputs from the controller.
 */

// getJoystickValue
//   Places joystick values into the passed JoystickValues struct.
void getJoystickValues(JoystickValues &js)
{
  // ignore this much of the stick's tilt
  const int deadZone = 15;
  bool leftXIsDead;
  bool leftYIsDead;
  bool rightXIsDead;
  bool rightYIsDead;

  // Sample the joystick values
  js.LeftX = vexRT[Ch4];
  js.LeftY = vexRT[Ch3];
  js.RightX = vexRT[Ch1];
  js.RightY = vexRT[Ch2];

  // When in the dead zone, drop the input.
  leftXIsDead = ((js.LeftX > -deadZone) && (js.LeftX < deadZone));
  leftYIsDead = ((js.LeftY > -deadZone) && (js.LeftY < deadZone));
  rightXIsDead = ((js.RightX > -deadZone) && (js.RightX < deadZone));
  rightYIsDead = ((js.RightY > -deadZone) && (js.RightY < deadZone));
  // Dead out the inputs
  js.LeftX = leftXIsDead ? 0 : js.LeftX;
  js.LeftY = leftYIsDead ? 0 : js.LeftY;
  js.RightX = rightXIsDead ? 0 : js.RightX;
  js.RightY = rightYIsDead ? 0 : js.RightY;
}

void getButtonValues(ButtonValues &buttons)
{
  buttons.R1 = (vexRT[Btn6U] != 0);
  buttons.R2 = (vexRT[Btn6D] != 0);
  buttons.L1 = (vexRT[Btn5U] != 0);
  buttons.L2 = (vexRT[Btn6D] != 0);
  buttons.A  = (vexRT[Btn8R] != 0);
  buttons.B  = (vexRT[Btn8D] != 0);
  buttons.X  = (vexRT[Btn8U] != 0);
  buttons.Y  = (vexRT[Btn8L] != 0);
}
