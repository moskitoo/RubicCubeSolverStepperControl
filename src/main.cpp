#include <Arduino.h>
#include <AccelStepper.h>

String message;

// // uint8_t steppers_pins[6][2] = {
// //   {46, 48},  //UP 
// //   {28, 30},  //RIGHT
// //   {24, 26},  //FRONT
// //   {25, 23},  //DOWN
// //   {43, 41},  //LEFT
// //   {45, 47},  //BACK
// //   };

// // uint8_t microstepping_pins[6][3] = {
// //   {50, 44, 42}, //UP
// //   {36, 38, 40}, //RIGHT
// //   {22, 32, 34}, //FRONT
// //   {27, 29, 37}, //DOWN
// //   {33, 35, 31}, //LEFT
// //   {49, 51, 53}  //BACK
// //   };

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

const byte num_steppers = 6;
AccelStepper **motors;

void set_speed(int speed){
  for (int i = 0; i < 6; i++){
    motors[i]->setMaxSpeed(speed);
  }
}

void set_acceleration(int acceleration){
  for (int i = 0; i < 6; i++){
    motors[i]->setAcceleration(acceleration);
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

// // WPAKOWAC SILNIKI DO LISTY I LECAC PO LISCIE USTAIWAC IM USTAIWENIA.
// // PRZETESTWOWAC LIMITY PREDKOSCI I PZEYPSIESZENIA

void move_stepper(int stepper_id, char move_type){
  if (move_type == '1') {
      motors[stepper_id]->move(-50);
    }
  else if (move_type == '2') {
      motors[stepper_id]->move(100);
    }
  else {
      motors[stepper_id]->move(50);
    }
}

void setup() {

  motors = new AccelStepper*[num_steppers];
  for (byte i = 0; i < num_steppers; i++) {
    motors[i] = new AccelStepper(AccelStepper::DRIVER, steppers_pins[i][0], steppers_pins[i][1]);
  }

  set_microstepping(8);
  set_speed(800);
  set_acceleration(800);

  Serial.begin(9600);
}

void loop() {

    if (Serial.available() > 0) {
    message = Serial.readString();
    Serial.print("message ");
    Serial.println(message[0]);
    
    if (message[0] == 'U'){
      move_stepper(0, message[1]);
    }
    else if (message[0] == 'R') {
        move_stepper(1, message[1]);
      }
    else if (message[0] == 'F') {
        move_stepper(2, message[1]);
      }
    else if (message[0] =='D') {
      move_stepper(3, message[1]);
      }
    else if (message[0] == 'L') {
        move_stepper(4, message[1]);
      }
    else if (message[0] == 'B') {
        move_stepper(5, message[1]);
      }
    Serial.read();
  }

  for (byte i = 0; i < num_steppers; i++) {
  motors[i]->run();
  }
}

