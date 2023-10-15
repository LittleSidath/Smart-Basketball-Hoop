
//distance sensor pins
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;

volatile int index = 0;

const double scoreThreshold = 14; //8 cm
int score = 00;
unsigned long lastShot = 0;
unsigned long lastSensor1Detected = 0;
unsigned long waitTime = 2000; //1 seconds
unsigned long BadCaseTime = 3000; //1 seconds

void setup ()
{
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  setupDisplay();
  
  //set timer1 interrupt at 1Hz

}


//void loop()
//Main portion of the program. Loop runs continuously until the
//Arduino loses power. The Arduino checks to see if a shot has
//been made.
void loop()
{
  if(detectScore2()){ 
    Serial.print("bad case");
    delay(3000);
    Serial.print("back to work");
  }
  if(detectScore1() && millis()-lastShot >= waitTime)
  {
    Serial.println("sensor1 okay");
    lastSensor1Detected = millis();
    while (millis()-lastSensor1Detected <= waitTime){
      if(detectScore2()){
        incrementScore();
        lastShot = millis();
        break;
      }
    }
  }
  Serial.println(score);
  String score_string=String(score);
  writeDisplay(score_string.c_str(), 0, false);
}


//boolean detectScore()
//@return      true if shot is detected, false if otherwise
//
//Detects whether or not a shot was made by checking if the
//distance from the ultrasonic distance sensor to the next closest
//object is under the "threshold."
boolean detectScore1()
{
  return (distance1() <= scoreThreshold);
}

boolean detectScore2()
{
  return (distance2() <= scoreThreshold);
}

//double distance()
//@return      the distance in centimeters (cm)
//
//Calculates the distance from the sensor to the next closest
//object.
double distance1()
{
  double duration = 0;

  digitalWrite(trigPin1, HIGH); //send out pulse
  delayMicroseconds(50); //give the pulse time
  digitalWrite(trigPin1, LOW); //turn off pulse
  duration = pulseIn(echoPin1, HIGH); //read echo pin
  
  return (duration/2) / 29.1; //in cm
}

double distance2()
{
  double duration = 0;

  digitalWrite(trigPin2, HIGH); //send out pulse
  delayMicroseconds(50); //give the pulse time
  digitalWrite(trigPin2, LOW); //turn off pulse
  duration = pulseIn(echoPin2, HIGH); //read echo pin
  
  return (duration/2) / 29.1; //in cm
}


//void incrementScore()
//Increments the socre variable by 1.
void incrementScore()
{
  score += 1;
}


//Interrupt Service Routine
//Displays the numbers for the score on the 7-segment display.
//It lights a single segment every 1 ms incrementing the segment
//index every iteration. The "if (bitRead(xxx))" statements
//determine which segment needs to be lit based upon the hexadecimal
//representation of the number we are trying to display and how
//it relates to the segments of the 7-segment display. See
//comments at the beginning of the code. Assumes index variable
//is non-negative.

