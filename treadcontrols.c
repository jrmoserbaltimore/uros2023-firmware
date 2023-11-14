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
bool isPrecision = false;

void moveTreads(JoystickValues &js, ButtonValues &buttons)
{
  // Dead zone sets axis to 0
  bool xIsDead = (js.RightX == 0);
  bool yIsDead = (js.LeftY == 0);
  bool yRightIsDead = jRightY;
  signed char leftTread;
  signed char rightTread;

  // Set isPrecision to the button value if all axes are dead.
  // Check this before checking if yIsDeead to stop moving, because
  // we may still be moving in precision mode.
  //
  // We can only enter or leave precision mode when all axes are
  // dead.
  if (xIsDead && yIsDead && yRightIsDead)
  {
    isPrecision = buttons.L1;
    // Stop moving when we enter precision mode, to avoid a race
    // condition.
    isMoving = false;
  }

  // We are never turning if the x axis is dead.
  if (xIsDead)
  {
    isTurning = false;
  }

  // Precision mode cannot set isTurning, but can set or clear isMoving
  if (isPrecision)
  {
    // Entering precision mode counts on xIsDead too, so doesn't cover
    // this check.
    if (yIsDead && yRightIsDead)
    {
      isMoving = false;
    }
    // In precision mode, if we're not dead, move the treads as per
    // separate y axes.
    if (!(yIsDead && yRightIsDead))
    {
      leftTread = js.LeftY;
      rightTread = js.RightY;
      isMoving = true;
    }
  }
  else
  {
    if (yIsDead)
    {
      isMoving = false;
    }
    // If not moving and attempting to turn, turn.
    if (!(isMoving || xIsDead))
    {
      // Turning right drives the left tread forward, the right tread backward,
      // and vice versa.
      leftTread = -js.RightX;
      rightTread = js.RightX;
      // Flag that we're turning.
      isTurning = true;
    }
    // If not turning and attempting to move, move
    else if (!(isTurning || yIsDead))
    {
      leftTread = rightTread = js.LeftY;
      isMoving = true;
    }
  }

  // Stop if it's neither moving nor turning
  if (!(isMoving || isTurning))
  {
    leftTread = rightTread = 0;
  }

  // Set the motors
  motor[LeftTread] = leftTread;
  motor[RightTread] = rightTread;
}
