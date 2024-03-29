#include <Servo.h>
Servo Pipe_Servo;
Servo Gate_Servo;
Servo Bin_Servo;
int sensorpin = 2; // raindrop sensor
int indValue;
const int trigPin = 7; // ultrasonic T
const int echoPin = 8; // ultrasonic E
int i = 0;
float Pipe_Pos = 0.0; 
float Gate_Pos = 0.0;
float Bin_Pos = 0.0;
int n = 0;
long duration;
int distance;
void setup() {
  pinMode(3, INPUT); // metal detector
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("* WELCOME EVERYONE *");
  Serial.println(" SMART DUSTBIN WITH AUTOMATIC WASTE SEGRATING ");
  Pipe_Pos = Pipe_Servo.read();
  Gate_Pos = Gate_Servo.read();
  Bin_Pos = Bin_Servo.read();
  Serial.println("Motor_PIPE Position");
  Serial.println(Pipe_Pos);
  Serial.println("Motor_GATE Position");
  Serial.println(Gate_Pos);
  delay(5000);
  Pipe_Servo.attach(11); // mg996 servo
  if (Pipe_Pos < 90) {
    for (i = Pipe_Pos; i <= 90; i = i + 1) {
      Pipe_Servo.write(i);
      delay(8);
    }
  } else {
    for (i = Pipe_Pos; i >= 90; i = i - 1) {
      Pipe_Servo.write(i);
      delay(8);
    }
  }
  delay(1000);
  Gate_Servo.attach(10); // internal lid servo
  for (n = 0; n <= 90; n = n + 1) {
    Gate_Servo.write(n);
    delay(5);
  }
  delay(1000);
  for (n = 90; n >= 0; n = n - 1) {
    Gate_Servo.write(n);
    delay(5);
  }
  delay(5000);
}
void solution() {
  indValue = digitalRead(3); // metal detector reading
  Serial.println(indValue);
  delay(10);
  int sensorstate = digitalRead(sensorpin); // readin the raindrop sensor , 1: dry 0: wet
  delay(500);
  delay(50);
  Pipe_Pos = Pipe_Servo.read();
  Gate_Pos = Gate_Servo.read();
  //METAL DETECTED/
  if (indValue == 1) {
    Serial.println("Metal Waste Detected");
    Pipe_Pos = Pipe_Servo.read();
    Gate_Pos = Gate_Servo.read();
    Serial.println("Motor_PIPE Position");
    Serial.println(Pipe_Pos);
    Serial.println("Motor_GATE Position");
    Serial.println(Gate_Pos);
    Serial.println("Waste To Metal bin");
    delay(100);
    if (Pipe_Pos < 90) {
      for (i = Pipe_Pos; i <= 66; i = i + 1) {
        Pipe_Servo.write(i);
        delay(8);
      }
    } else {
      for (i = Pipe_Pos; i >= 66; i = i - 1) {
        Pipe_Servo.write(i);
        delay(8);
      }
    }
    delay(1000);
    for (n = 0; n <= 180; n = n + 1) {
      Gate_Servo.write(n);
      delay(5);
    }
    delay(1000);
    for (n = 180; n >= 0; n = n - 1) {
      Gate_Servo.write(n);
      delay(5);
    }
    //METAL DETECTED//
    //DRY DETECTED//
  } else {
    if (sensorstate == 1) {
      delay(100);
      Serial.println("Dry Waste Detected");
      Pipe_Pos = Pipe_Servo.read();
      Gate_Pos = Gate_Servo.read();
      Serial.println("Motor_PIPE Position");
      Serial.println(Pipe_Pos);
      Serial.println("Motor_GATE Position");
      Serial.println(Gate_Pos);
      Serial.println("Waste To Dry Bin");
      delay(100);
      if (Pipe_Pos < 145) {
        for (i = Pipe_Pos; i <= 145; i = i + 1) {
          Pipe_Servo.write(i);
          delay(8);
        }
      } else {
        for (i = Pipe_Pos; i >= 145; i = i - 1) {
          Pipe_Servo.write(i);
          delay(8);
        }
      }
      delay(1000);
      for (n = 0; n <= 180; n = n + 1) {
        Gate_Servo.write(n);
        delay(5);
      }
      delay(1000);
      for (n = 180; n >= 0; n = n - 1) {
        Gate_Servo.write(n);
        delay(5);
      }
    }
    //DRY DETECTED//
    //WET DETECTED//
    else {
      Serial.println("Wet Waste Detected");
      Pipe_Pos = Pipe_Servo.read();
      Gate_Pos = Gate_Servo.read();
      Serial.println("Motor_PIPE Position");
      Serial.println(Pipe_Pos);
      Serial.println("Motor_GATE Position");
      Serial.println(Gate_Pos);
      Serial.println("Waste To Wet Bin");
      delay(1000);
      if (Pipe_Pos < 25) {
        for (i = Pipe_Pos; i <= 1; i = i + 1) {
          Pipe_Servo.write(i);
          delay(8);
        }
      } else {
        for (i = Pipe_Pos; i >= 1; i = i - 1) {
          Pipe_Servo.write(i);
          delay(8);
        }
      }
      delay(1000);
      for (n = 0; n <= 180; n = n + 1) {
        Gate_Servo.write(n);
        delay(5);
      }
      delay(1000);
      for (n = 180; n >= 0; n = n - 1) {
        Gate_Servo.write(n);
        delay(5);
      }
    }
  }
}
void loop() {
  delay(3000);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);  //
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(30);  //it was 1
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance <= 15) {
    Serial.print("Distance: ");
    Serial.println(distance);
    delay(1000);
    Bin_Servo.attach(5);
    for (n = 0; n <= 120; n = n + 1) {
      Bin_Servo.write(n);
      delay(5);
    }
    delay(2000);
    for (n = 120; n >= 0; n = n - 1) {
      Bin_Servo.write(n);
      delay(5);
    }
    delay(2000);
    solution();
  }
}
