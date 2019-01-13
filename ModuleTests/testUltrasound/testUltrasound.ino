
// defines pins numbers
#define VCC 8
#define TRIGGER 9
#define ECHO 10
#define BUZZER 5
// defines variables
unsigned long duration;
float distance;

//JRI Jan '19: My module 'locks up' in a mode when it emits very long echo pulses. It seems to do so when
// unsure of the reflection, and does not have the built-in cutoff of 38ms advertised in the specs, but instead
// gives a >100ms pulse. So, use a  long cutoff here and instead detect the problem below and power-cycle the 
// ultrasonic module. This allows it to get one valid sample after every reset, at least. Otherwise, it would
// simply emit a long series of '0' timeout readings.
#define LONGEST_DISTANCE 3000 // 200 cm = 2 meters
float farTime =  LONGEST_DISTANCE*2/0.034;

void setup() {
  pinMode(VCC, OUTPUT);
  pinMode(TRIGGER, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO, INPUT); // Sets the echoPin as an Input
  Serial.begin(57600); // Starts the serial communication
}

long counter=0;
void loop() {
  // Clears the trigPin
  digitalWrite(VCC, HIGH);
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(BUZZER,HIGH);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  digitalWrite(BUZZER,LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO, HIGH, farTime);
  Serial.println(duration);

//detect hung echo and reset by powercycle
  if (duration > 50000) {
    //Serial.println("RESET!");
    digitalWrite(VCC, LOW);
    delay(100);
    digitalWrite(VCC, HIGH);
    delay(100);
    return;
  }
  

  // Calculating the distance
  distance = duration * 0.034 / 2; // 10^-6 * 34000 cm/s

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(200);
}
