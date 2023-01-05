/******************************************************************************

Implementing PID control algorithm for flight controller
Using for source https://www.technik-consulting.eu/en/optimizing/drone_PID-optimizing.html


Passing in pitch, roll and yaw of the drone
Returning values to send to motors for stabilisation or control

P Value - increases the power of the motors proportional to the angle of the drone. For flight and stabilisation on a large scale.
          Needs to increase/decrease the power between all the motors. Too high of p value drone will begin
          to oscillate. 

D Value - for quick reactions to wind etc, rate of change matters more than the actual value. 
          Gauges the rate of change for larger deflections from p. Allows stability on a smaller scale with small amplitude and rapid oscillation.
          Predicts changes required in the future

I Value - Summing of sensor data over time. Compensates for inbalances between P and D value. 
          IF an imbalance occured drone would incline at an angle repeatedly. Need to keep as close to zero. Mainly data from tilt sensor and calculate tilt over time?
          Constant change to performance from past interference based on deviation and elapsed time

Rules from source: 
  Optimization in flight
  A few rules for optimizing the flight:

  Drone reacts slowly and hovers bad or unstable (eg dances, wobbles)
  Increase P-value and decrease D value. Maybe decrease I value. The P value must in no case be higher than the above-determined threshold.

  During hover the drone drifts
  Increase the I term and possibly   P-value.

  Oscillation during fast flights
  I-value too high or too low - depending on the drone.

  Drone oscillates slightly with disturbances (eg nudge or gust of wind)
  D value down

  Drone reacts too slowly to disturbances (eg nudge or gust of wind)
  Increase D-value and possibly P-value.

******************************************************************************/



