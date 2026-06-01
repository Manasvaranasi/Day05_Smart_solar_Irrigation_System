// Smart Solar Powered Rainwater Harvesting
// and Automated Drip Irrigation System

const int soilPin = A0;

const int trigPin = 9;
const int echoPin = 10;

const int greenLED = 5;
const int redLED = 6;

long duration;
float distance;
int soilValue;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  Serial.begin(9600);

  Serial.println("SMART IRRIGATION SYSTEM STARTED");
  Serial.println("--------------------------------");
}

void loop() {

  // Read Soil Moisture
  soilValue = analogRead(soilPin);

  // Read Water Level
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println("--------------------------------");
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilValue);

  Serial.print("Water Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Conditions
  if (soilValue < 600 && distance < 70) {

    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);

    Serial.println("STATUS: PUMP ON");
    Serial.println("Reason: Soil is dry and water is available");
    Serial.println("Action: Irrigation started");

  }
  else {

    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);

    Serial.println("STATUS: PUMP OFF");

    if (soilValue >= 600) {
      Serial.println("Reason: Soil already has enough moisture");
    }

    if (distance >= 70) {
      Serial.println("Reason: Water tank level is low");
    }

    Serial.println("Action: Irrigation stopped");
  }

  delay(1000);
}