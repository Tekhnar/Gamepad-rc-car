
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h>

RF24 radio(9, 10);  // For arduino UNO and other
//RF24 radio(9,53); // For arduino mega

const byte MOTOR_ROTATION_PIN = 6;
const byte MOTOR_PWM_PIN = 5; 
const byte SERVO_PIN = 4; 

const byte NUMBER_BYTE_WITH_STEER = 0;
const byte NUMBER_BYTE_WITH_THROTLLE = 1;
const byte NUMBER_BYTE_WITH_BRAKE = 2;


Servo myservo;

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

void dataProcessing (byte *recieved_data);
void steeringDataProcessing (byte data_steering_wheel);
void throtlleDataProcessing (byte data_throtlle);

void setup() {
  Serial.begin(9600); 

  pinMode (MOTOR_ROTATION_PIN, OUTPUT);
  pinMode (MOTOR_PWM_PIN, OUTPUT);
  // as default forward movemet
  digitalWrite (MOTOR_ROTATION_PIN, HIGH);
  
  myservo.attach (SERVO_PIN);

  //--------- Setup and configure rf radio ---------//
  
  radio.begin(); 
  radio.setAutoAck (1);
  radio.setRetries (0, 15);
  radio.enableAckPayload();
  radio.setPayloadSize (32);

  radio.openReadingPipe (1, address[0]);
  radio.setChannel (0x60);

  radio.setPALevel  (RF24_PA_MAX);  //RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //RF24_2MBPS, RF24_1MBPS, RF24_250KBPS

  radio.powerUp();
  radio.startListening();
  //------------------------------------------------//
}

void loop() {
  byte recieved_data[3] = {};
  
  while (radio.available()) {
    radio.read (&recieved_data, sizeof (recieved_data));    
    dataProcessing (recieved_data);
  }
}


void dataProcessing (byte *recieved_data) {
  steeringDataProcessing (recieved_data [NUMBER_BYTE_WITH_STEER]);
  
  throtlleDataProcessing (recieved_data [NUMBER_BYTE_WITH_THROTLLE]);
}

void steeringDataProcessing (byte data_steering_wheel) {
  byte position = map (data_steering_wheel, 0, 255, 70, 110);
  myservo.write (position); 
}

void throtlleDataProcessing (byte data_throtlle) {
  analogWrite (MOTOR_PWM_PIN, data_throtlle);
}
