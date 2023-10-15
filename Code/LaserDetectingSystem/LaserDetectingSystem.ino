const int ldrPin1 = A7;
const int ldrPin2 = A1;
const int buzzerPin = 2;
const int ldrThreshold = 600;
unsigned long waitTime = 500;
unsigned long lastShot = 0;
unsigned long lastSensor1Detected = 0;
int score = 0;


bool detectScore1(){
  int laser = analogRead(ldrPin1);
  return (laser > ldrThreshold);
}

bool detectScore2(){
  int laser = analogRead(ldrPin2);
  return (laser > ldrThreshold);
}

void setup(){
  Serial.begin(9600); 
  pinMode(buzzerPin,OUTPUT);
  setupDisplay();
}

void loop() {
  int laser = analogRead(ldrPin1);
  int laser2 = analogRead(ldrPin2);
  Serial.println("First: " + String(laser) + " Second: " + String(laser2));
  if(detectScore2()){ 
    delay(1000);
  }
  
  else if(detectScore1() && millis()-lastShot >= waitTime) {
    lastSensor1Detected = millis();
    while (millis()-lastSensor1Detected <= waitTime){
      if(detectScore2()){
        digitalWrite(buzzerPin, HIGH);
        score++;
        lastShot = millis();
        break;
      }
    }
    delay(500);
    digitalWrite(buzzerPin, LOW);
  }
  
  String score_string=String(score);
  writeDisplay("Score:", 0, false);
  writeDisplay(score_string.c_str(), 1, false);
}

