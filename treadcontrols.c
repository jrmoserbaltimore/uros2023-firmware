/*
 * Robot controls
 *
 * This source file implements controls for the robot's treads.
 *
 * The controls are tank controls:
 *
 *   - Left stick Y:  forward/backwards
 *   - Right stick X:  Turn left/right
 *   - Must come to a complete stop to turn; turning is disabled
 *     when moving
 *
 * The robot won't accept conflicting controls:  once moving or turning, the
 * stick attached to that action must return to 0 before the other stick will
 * be examined.  This allows a driver to buffer inputs, but that can do
 * unexpected things.
 */

// Flags to track if the robot is already moving or turning.
bool isTurning = false;
bool isMoving = false;

void moveTreads(JoystickValues &js)
{
	// Dead zone sets axis to 0
	bool xIsDead = (js.RightX == 0);
	bool yIsDead = (js.LeftY == 0);
	signed char leftTread;
	signed char rightTread;
	// If stationary on one axis, stop acting on that axis
	if (xIsDead)
	{
		isTurning = false;
	}
	if (yIsDead)
	{
		isMoving = false;
	}
	// Stop if it's neither moving nor turning
	if (!(isMoving || isTurning))
	{
		leftTread = rightTread = 0;
//		motor[LeftTread] = motor[RightTread] = 0;
	}

	// If not moving and attempting to turn, turn.
	if (!(isMoving || xIsDead))
	{
		// Turning right drives the left tread forward, the right tread backward,
		// and vice versa.
	  leftTread = -js.RightX;
	  rightTread = js.RightX;
//		motor[LeftTread] = js.RightX;
//		motor[RightTread] = -js.RightX;
		// Flag that we're turning.
		isTurning = true;
	}
	// If not turning and attempting to move, move
	else if (!(isTurning || yIsDead))
	{
		leftTread = rightTread = js.LeftY;
//		motor[LeftTread] = motor[RightTread] = js.LeftY;
		isMoving = true;
	}

	// Set the motors
	motor[LeftTread] = leftTread;
	motor[RightTread] = rightTread;
}
