#include <LiquidCrystal.h>
#include <Servo.h>

// BUTTON
#define BUTTON_TOGGLE_PIN 2
// LED
#define LED_TOGGLE_PIN 3
// ULTRASONIC SENSOR
#define ULTRA_ECHO_PIN 8
#define ULTRA_TRIG_PIN 9
// DISPLAY
#define DISPLAY_DATA7_PIN 4
#define DISPLAY_DATA6_PIN 5
#define DISPLAY_DATA5_PIN 6
#define DISPLAY_DATA4_PIN 7
#define DISPLAY_EN_PIN 11
#define DISPLAY_RS_PIN 12
// SERVO
#define SERVO_PIN 13
// POTENTIOMETER
#define POT_PIN A5

// DELAYS
#define SERVO_DELAY 10
#define LOOP_DELAY 100

// SERVO
#define SERVO_INCREMENT 5
Servo servo;
int angle = 0;
int swingCounter = 0;
int swingCounterMax = 3;
// BUTTON
int lastButtonToggleState;
int currentButtonToggleState;
int enableServo = false;

// DISPLAY
LiquidCrystal lcd(DISPLAY_RS_PIN, DISPLAY_EN_PIN, DISPLAY_DATA4_PIN, DISPLAY_DATA5_PIN, DISPLAY_DATA6_PIN, DISPLAY_DATA7_PIN);

// ULTRASONIC
long duration;
int distance;
bool withinRange = false;

// POTENTIOMETER
int potData = 0;
int userDistance = 0;

void setup() {
  //Serial.begin(9600);
  
  // SERVO
  servo.attach(SERVO_PIN);
  servo.write(angle);

  // BUTTON/LED
  // toggle button
  pinMode(BUTTON_TOGGLE_PIN, INPUT_PULLUP);
  currentButtonToggleState = digitalRead(BUTTON_TOGGLE_PIN);
  // toggle LED
  pinMode(LED_TOGGLE_PIN, OUTPUT);
  digitalWrite(LED_TOGGLE_PIN, LOW);

  // ULTRASONIC
  pinMode(ULTRA_TRIG_PIN, OUTPUT);
  pinMode(ULTRA_ECHO_PIN, INPUT);

  // display startup message
  writeMessage("     Arduino", " Pinball Hazard", 3000);
}

void servoLeftRight() {
  // scan from 0 to 180 degrees
  for(angle = 10; angle < 180; angle+=SERVO_INCREMENT) {
    servo.write(angle);
    delay(SERVO_DELAY);
  }
  // scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle-=SERVO_INCREMENT) {
    servo.write(angle);
    delay(SERVO_DELAY);
  }
}

void servoRightLeft() {
  // scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle-=SERVO_INCREMENT) {
    servo.write(angle);
    delay(SERVO_DELAY);
  }
  // scan from 0 to 180 degrees
  for(angle = 10; angle < 180; angle+=SERVO_INCREMENT) {
    servo.write(angle);
    delay(SERVO_DELAY);
  }
}

bool getUltraDistance() {
  // clear TRIG
  digitalWrite(ULTRA_TRIG_PIN, LOW);
  delayMicroseconds(2);
  // set TRIG HIGH for 10μs
  digitalWrite(ULTRA_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_TRIG_PIN, LOW);
  // read ECHO
  duration = pulseIn(ULTRA_ECHO_PIN, HIGH);
  // calculate distance (speed of sound / 2)
  distance = duration * 0.03435 * 0.5;
  //distance = (duration / 2) / 29.1;

  // get user data from potentiometer
  potData = analogRead(POT_PIN);
  userDistance = map(potData, 0, 1023, 1, 200);

  // print to display
  writeMessage("Distance: " + String(distance)+ " cm", "Activate: " + String(userDistance) + " cm", 0);

  if(distance <= userDistance) {
    return true;
  }else {
    return false;
  }
}

void writeMessage(String line1, String line2, int wait) {
  lcd.begin(16, 2);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
  if(wait > 0) {
    delay(wait);
  }
}

void loop() {
  // enable servo
  lastButtonToggleState = currentButtonToggleState;
  currentButtonToggleState = digitalRead(BUTTON_TOGGLE_PIN);
  // if button is pressed
  if(lastButtonToggleState == HIGH && currentButtonToggleState == LOW) {
    enableServo = !enableServo;
    if(enableServo) {
      digitalWrite(LED_TOGGLE_PIN, HIGH);
      writeMessage("Servo ENABLED", "", 3000);
    }else {
      digitalWrite(LED_TOGGLE_PIN, LOW);
      writeMessage("Servo DISABLED", "", 3000);
    }
  }

  // check distance
  withinRange = getUltraDistance();

  // if servo enabled and within activation range
  if(enableServo && withinRange) {
    // swing servo swingCounterMax-times
    while(swingCounter < swingCounterMax) {
      servoLeftRight();
      //servoRightLeft();
      delay(LOOP_DELAY);
      swingCounter++;
    }
    // reset swingCounter
    swingCounter = 0;
  }

  delay(LOOP_DELAY);
}
