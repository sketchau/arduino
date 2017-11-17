#include <Servo.h>
#include <IRremote.h>

const int IR_RECV_PIN = 8;

const int MOTOR_PIN = 9;
const int STEERING_PIN = 10;
const int TIPPER_PIN = 11;
const int LIGHTS_PIN = 13;

bool lightsOn = false;
unsigned long lightsLastOn = 0;

int speedValue = 0; // positive is forward
int steeringValue = 0; // positive is left
int tipperValue = 0; // 0 = max closed, 100 = max open


IRrecv irrecv(IR_RECV_PIN);
decode_results results;
unsigned long CurrentValue = 0;
unsigned long PreviousValue = 0;


//Controls

struct TruckControls {
  unsigned long SpeedUp;
  unsigned long SpeedDown;
  unsigned long Stop;
  unsigned long TurnLeft;
  unsigned long TurnRight;
  unsigned long TipperUp;
  unsigned long TipperDown;
  unsigned long Lights;
};

TruckControls controls = {
  3772778233, // speed up
  3772810873, // speed down
  3772782313, // stop
  3772794553, // turn left
  3772819033, // turn right
  3772795063, // tipper up
  3772778743, // tipper down
  3772816993  // switch lights
};

//Servo motorServo;
Servo steeringServo;
Servo tipperServo;

void setup() {

  //motorServo.attach(MOTOR_PIN);
  steeringServo.attach(STEERING_PIN);
  tipperServo.attach(TIPPER_PIN);

  pinMode(LIGHTS_PIN, OUTPUT);
  irrecv.enableIRIn();
}

void loop() {

  if (irrecv.decode(&results)) {
    CurrentValue = (results.value);

    if (CurrentValue == controls.SpeedUp && speedValue < 100)
      speedValue += 20;

    if (CurrentValue == controls.SpeedDown && speedValue > -100)
      speedValue -= 20;

    if (CurrentValue == controls.Stop) 
      speedValue = 0;

    if (CurrentValue == controls.TurnLeft && steeringValue < 100)
      steeringValue += 20;
      
    if (CurrentValue == controls.TurnRight && steeringValue > -100)
      steeringValue -= 20;

    if (CurrentValue == controls.TipperUp)
      tipperValue = 100;

    if (CurrentValue == controls.TipperDown)
      tipperValue = 0;

    if (CurrentValue == controls.Lights && lightsLastOn < millis() - 250)
    {
      lightsOn = !lightsOn;    
      lightsLastOn = millis();
    }
    
    PreviousValue = CurrentValue;
    irrecv.resume();
  }
  else //if no signal is detected, then the current value is 0
  {
    CurrentValue = 0;
  }

  //motorServo.write(speedValue);
  steeringServo.write(map(steeringValue, -100, 100, 40, 150));
  tipperServo.write(map(tipperValue, 0, 100, 160, 60));
  digitalWrite(LIGHTS_PIN, lightsOn ? HIGH : LOW);
  delay(15);
  
  
}




