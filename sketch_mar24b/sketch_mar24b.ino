#define Ago 23
#define Ain1 39
#define Ain2 39

volatile bool isAvail;
void askAvail()
{
  Serial.println("1");
  digitalWrite(Ago, LOW);
  isAvail = false;
}

void stopAskAvail()
{
  if(isAvail == true) {
    digitalWrite(Ago, LOW);
  }
  else {
    digitalWrite(Ago, HIGH);
  }
  isAvail = !isAvail;
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(Ago, OUTPUT);
  pinMode(Ain1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Ain1), stopAskAvail, FALLING);
  //attachInterrupt(digitalPinToInterrupt(Ain2), askAvail, RISING);
  Serial.begin(9600);
  digitalWrite(Ago, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Status : ");
  Serial.println(digitalRead(Ain1));
  delay(100);
}
