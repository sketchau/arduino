const int potPin = A0;
const int ledPin = 10;
const int motorPin = 9;


int potValue = 0;
int pwmValue = 0;

int power = 0;
int oldPower = 0;

void setup() {

    Serial.begin(9600);

    pinMode(potPin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(motorPin, OUTPUT);
}

void loop() {
  potValue = analogRead(potPin);
  pwmValue = map(potValue, 0, 1024, 0, 256);

  analogWrite(motorPin, pwmValue);
  analogWrite(ledPin, 128-pwmValue/2);
  
  power = map(potValue, 0, 1024, 0, 10);
  
  if (power != oldPower)
  {
    oldPower = power;
    Serial.print("Changing power mode to: ");
    Serial.println(power+1);
  }
  
  delay(20);
}
