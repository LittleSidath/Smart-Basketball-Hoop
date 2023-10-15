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
  return (laser > 1020);
}

void setup(){
  Serial.begin(9600); 
  pinMode(buzzerPin,OUTPUT);
  setupDisplay();
}


//void loop()
//Main portion of the program. Loop runs continuously until the
//Arduino loses power. The Arduino checks to see if a shot has
//been made.
void loop()
{
  if(detectScore1() && millis()-lastShot >= waitTime)
  {
    digitalWrite(buzzerPin, HIGH);
    score++;
    lastShot = millis();
    delay(500);
    digitalWrite(buzzerPin, LOW);
  }
  Serial.println(score);
  String score_string=String(score);
  writeDisplay("Score:", 0, false);
  writeDisplay(score_string.c_str(), 1, false);
}


//boolean detectScore()
//@return      true if shot is detected, false if otherwise
//
//Detects whether or not a shot was made by checking if the
//distance from the ultrasonic distance sensor to the next closest
//object is under the "threshold."


//double distance()
//@return      the distance in centimeters (cm)
//
//Calculates the distance from the sensor to the next closest
//object.



//void incrementScore()
//Increments the socre variable by 1.



//Interrupt Service Routine
//Displays the numbers for the score on the 7-segment display.
//It lights a single segment every 1 ms incrementing the segment
//index every iteration. The "if (bitRead(xxx))" statements
//determine which segment needs to be lit based upon the hexadecimal
//representation of the number we are trying to display and how
//it relates to the segments of the 7-segment display. See
//comments at the beginning of the code. Assumes index variable
//is non-negative.

