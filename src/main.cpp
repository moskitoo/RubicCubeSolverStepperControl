#include <Arduino.h>
#include <AccelStepper.h>

String message;

uint8_t steppers_pins[6][2] = {
  {25, 26},  //UP 
  {30, 31},  //RIGHT
  {35, 36},  //FRONT
  {40, 41},  //DOWN
  {45, 46},  //LEFT
  {50, 51},  //BACK
  };

uint8_t microstepping_pins[6][3] = {
  {22, 23, 24}, //UP
  {27, 28, 29}, //RIGHT
  {32, 33, 34}, //FRONT
  {37, 38, 39}, //DOWN
  {42, 43, 44}, //LEFT
  {47, 48, 49}  //BACK
  };

#define insert_pins(list) list[0], list[1]

#define U 0
#define R 1
#define F 2
#define D 3
#define L 4
#define B 5

#define motorInterfaceType 1

int microstepping = 16;
int speed = 2000;
int acceleration = 3000;

const byte num_steppers = 6;
AccelStepper **motors;

void set_speed(int speed, int microstepping){
  for (int i = 0; i < 6; i++){
    motors[i]->setMaxSpeed(speed * microstepping);
  }
}

void set_acceleration(int acceleration, int microstepping){
  for (int i = 0; i < 6; i++){
    motors[i]->setAcceleration(acceleration * microstepping);
  }
}

void set_microstepping(int stepping){
  for(int i = 0; i < 6; i++)
    {
      if (stepping == 2){
        digitalWrite(microstepping_pins[i][0], HIGH);
        digitalWrite(microstepping_pins[i][1], LOW);
        digitalWrite(microstepping_pins[i][2], LOW);
      }
      else if (stepping == 4){
        digitalWrite(microstepping_pins[i][0], LOW);
        digitalWrite(microstepping_pins[i][1], HIGH);
        digitalWrite(microstepping_pins[i][2], LOW);
      }
      else if (stepping == 8){
        digitalWrite(microstepping_pins[i][0], HIGH);
        digitalWrite(microstepping_pins[i][1], HIGH);
        digitalWrite(microstepping_pins[i][2], LOW);
      }
      else if (stepping == 16){
        digitalWrite(microstepping_pins[i][0], HIGH);
        digitalWrite(microstepping_pins[i][1], HIGH);
        digitalWrite(microstepping_pins[i][2], HIGH);
      }
      else{
        digitalWrite(microstepping_pins[i][0], LOW);
        digitalWrite(microstepping_pins[i][1], LOW);
        digitalWrite(microstepping_pins[i][2], LOW);
      }
    }
}

void move_stepper(int stepper_id, char move_type, int microstep){
  if (move_type == '1') {
      motors[stepper_id]->move(-50 * microstep);
    }
  else if (move_type == '2') {
      motors[stepper_id]->move(100 * microstep);
    }
  else {
      motors[stepper_id]->move(50 * microstep);
    }
}

void setup() {

  motors = new AccelStepper*[num_steppers];
  for (byte i = 0; i < num_steppers; i++) {
    motors[i] = new AccelStepper(AccelStepper::DRIVER, steppers_pins[i][0], steppers_pins[i][1]);
  }

  set_microstepping(microstepping);
  set_speed(speed, microstepping);
  set_acceleration(acceleration, microstepping);

  Serial.begin(9600);
}

void loop() {

    if (Serial.available() > 0) {
    message = Serial.readString();
    Serial.print("message ");
    Serial.println(message[0]);
    
    if (message[0] == 'U'){
      move_stepper(0, message[1], microstepping);
      Serial.print("move completed");
    }
    else if (message[0] == 'R') {
        move_stepper(1, message[1], microstepping);
        Serial.print("move completed");
      }
    else if (message[0] == 'F') {
        move_stepper(2, message[1], microstepping);
        Serial.print("move completed");
      }
    else if (message[0] =='D') {
      move_stepper(3, message[1], microstepping);
      Serial.print("move completed");
      }
    else if (message[0] == 'L') {
        move_stepper(4, message[1], microstepping);
        Serial.print("move completed");
      }
    else if (message[0] == 'B') {
        move_stepper(5, message[1], microstepping);
        Serial.print("move completed");
      }
    Serial.read();
  }

  for (byte i = 0; i < num_steppers; i++) {
  motors[i]->run();
  }
}

