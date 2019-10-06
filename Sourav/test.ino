#include <VarSpeedServo.h>

int s_speed = 60;
//
//VarSpeedServo knee;
//VarSpeedServo joint;


struct leg
{
  VarSpeedServo knee;
  VarSpeedServo joint;
  int stand_k;
  int stand_j;
  int front_k;
  int front_j;
} front_right_leg, front_left_leg, back_right_leg, back_left_leg;

void init(int knee_pin, int joint_pin, int angle_stand_k, int angle_stand_j/*,int angle_knee_up_j*/, int angle_front_k, int angle_front_j, leg &Leg)
{
  Leg.knee.attach(knee_pin);
  Leg.joint.attach(joint_pin);
  Leg.stand_k = angle_stand_k;
  Leg.stand_j = angle_stand_j;
  // Leg.knee_up_j = angle_knee_up_j;
  Leg.front_k = angle_front_k;
  Leg.front_j = angle_front_j;
  Leg.joint.write(Leg.stand_j, (s_speed), false);
  Leg.knee.write(Leg.stand_k, (s_speed), false);
}

void take_step(leg &Leg)
{
  //knee.write(Leg.knee_up_j, s_speed, true);
  Leg.joint.write(Leg.front_j, s_speed, false);
  Leg.knee.write(Leg.front_k, s_speed, true);
  Leg.joint.write(Leg.stand_j, (s_speed / 2), false);
  Leg.knee.write(Leg.stand_k, (s_speed / 2), false);
}

void forward()
{ 
  take_step(back_left_leg);
  take_step(front_left_leg);
  take_step(back_right_leg);
  take_step(front_right_leg);
  Serial.print("joint");
  Serial.print('\t');
  Serial.print("knee");
  Serial.print('\t');
  Serial.println();
  Serial.print(back_right_leg.front_j);
  Serial.print('\t');
  Serial.print(back_right_leg.stand_j);
  Serial.print('\t');
  Serial.println();
}

void setup() {
  // initialize serial:
  Serial.begin(9600);
  //int knee_pin, int joint_pin, int angle_stand_k, int angle_stand_j, int angle_front_k, int angle_front_j, leg Leg
  init(3, 2, 180, 30, 140, 90, back_left_leg);
  init(5, 4, 180, 30, 140, 90, back_right_leg);
  init(7, 6, 180, 30, 140, 90, front_left_leg);
  init(9, 8, 180, 30, 140, 90, front_right_leg);
  delay(2000);
}

void loop() {

 forward();
 //take_step(back_left_leg);
}
