#include <ros.h>
#include <robot_controller/MotorCommand.h>
#define L_PA_PIN 3
#define L_PB_PIN 5
#define L_EN_PIN 4
#define R_PA_PIN 6
#define R_PB_PIN 9
#define R_EN_PIN 7


void setRightSpeed(int speed) {
  if(speed < 0) {
    speed = -speed;
    analogWrite(R_PB_PIN, 0);
    analogWrite(R_PA_PIN, speed);
    digitalWrite(R_EN_PIN, HIGH);
  } else {
    analogWrite(R_PA_PIN, 0);
    analogWrite(R_PB_PIN, speed);
    digitalWrite(R_EN_PIN, HIGH);
  }
}

void setLeftSpeed(int speed) {
  if(speed < 0) {
    speed = -speed;
    analogWrite(L_PB_PIN, 0);
    analogWrite(L_PA_PIN, speed);
    digitalWrite(L_EN_PIN, HIGH);
  } else {
    analogWrite(L_PA_PIN, 0);
    analogWrite(L_PB_PIN, speed);
    digitalWrite(L_EN_PIN, HIGH);
  }
}

int mapSpeed(float speed) {
  int intSpeed = (int)(speed * 255.0f);
  if (intSpeed <= -255)
    return -255;
  if (intSpeed >= 255)
    return 255;

  return intSpeed;
}

ros::NodeHandle nh;

void motorCommandCallback(const robot_controller::MotorCommand& motor_command) {
  setRightSpeed(mapSpeed(motor_command.right));
  setLeftSpeed(mapSpeed(motor_command.left));
  Serial.println(mapSpeed(motor_command.right));
}

ros::Subscriber<robot_controller::MotorCommand> sub("motor_command", motorCommandCallback);

void setup() {
  nh.initNode();
  nh.subscribe(sub);
  pinMode(L_PA_PIN, OUTPUT);
  pinMode(L_PB_PIN, OUTPUT);
  pinMode(L_EN_PIN, OUTPUT);
  pinMode(R_PA_PIN, OUTPUT);
  pinMode(R_PB_PIN, OUTPUT);
  pinMode(R_EN_PIN, OUTPUT);
  setRightSpeed(0);
  setLeftSpeed(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(1);
}
