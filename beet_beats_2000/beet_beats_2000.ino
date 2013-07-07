#include <Stepper.h>
#include <NewSoftSerial.h>

//  number of steps on motors
#define STEPS 48

// stepper mottor is attached to two digital pins
Stepper motor1(STEPS, 7, 8);
Stepper motor2(STEPS, 2, 3);

// LCD
NewSoftSerial LCD(4,5); 

// LED's
const int ledBpm = 12;

// Potentiometers

const int pM1 = 0; // control motor 1 pattern
const int pM2 = 1; // control motor 2 pattern
const int pTs1 = 4; // control time signature
const int pTs2 = 3; // control time signature
const int pBpm = 5; // control tempo

int pattern1 = 6;
int pattern2 = 32;
int lastPattern1 = 0;
int lastPattern2 = 0;

// beats are arrays of 16 booleans, 1=hit
boolean b0[] = {0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0};

boolean b1[] = {1,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b2[] = {0,1,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b3[] = {0,0,1,0,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b4[] = {0,0,0,1,  0,0,0,0,  0,0,0,0,  0,0,0,0};

boolean b5[] = {1,0,0,1,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b6[] = {1,0,1,0,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b7[] = {1,0,0,1,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b8[] = {1,1,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0};  
boolean b9[] = {0,1,1,0,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b10[] = {0,0,1,1,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b11[] = {0,1,0,1,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b12[] = {0,1,1,0,  0,0,0,0,  0,0,0,0,  0,0,0,0};  
boolean b13[] = {0,0,1,1,  0,0,0,0,  0,0,0,0,  0,0,0,0};

boolean b14[] = {1,0,1,1,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b15[] = {1,1,0,1,  0,0,0,0,  0,0,0,0,  0,0,0,0};
boolean b16[] = {1,1,1,0,  0,0,0,0,  0,0,0,0,  0,0,0,0};  
boolean b17[] = {0,1,1,1,  0,0,0,0,  0,0,0,0,  0,0,0,0};

boolean b18[] = {0,0,0,0,  1,0,0,0,  0,0,0,0,  1,0,0,0};
boolean b19[] = {0,0,0,0,  0,0,0,0,  1,0,0,0,  0,0,0,0};
boolean b20[] = {0,1,0,0,  1,0,0,0,  0,0,0,0,  1,0,0,0};  
boolean b21[] = {0,0,0,0,  1,0,0,0,  1,0,0,0,  1,0,1,0};
boolean b22[] = {1,0,1,0,  0,1,1,1,  1,0,1,0,  0,1,1,1};
boolean b23[] = {0,1,0,0,  0,0,0,0,  1,0,0,0,  0,0,0,0};
boolean b24[] = {0,0,1,1,  0,1,0,1,  1,0,0,0,  0,0,1,1};  
boolean b25[] = {0,0,0,0,  1,0,0,0,  1,0,0,0,  1,0,0,0};
boolean b26[] = {1,0,1,0,  1,0,1,0,  1,0,1,0,  1,1,1,1};
boolean b27[] = {0,1,1,1,  1,1,1,0,  0,1,1,1,  1,0,1,0};
boolean b28[] = {0,0,1,1,  1,0,1,1,  0,0,1,0,  0,1,0,1};  
boolean b29[] = {1,1,1,1,  1,1,1,0,  1,1,1,1,  1,0,0,0};
boolean b30[] = {0,1,1,0,  1,1,1,1,  0,0,1,0,  0,1,0,1};
boolean b31[] = {1,1,1,0,  0,1,1,1,  1,1,0,1,  0,1,1,0};
boolean b32[] = {0,0,1,0,  1,1,1,1,  1,1,1,0,  1,0,0,1};  
boolean b33[] = {1,0,0,1,  1,0,0,1,  0,1,1,0,  1,0,1,1};
boolean b34[] = {1,1,0,0,  1,1,0,0,  1,1,0,0,  1,1,1,0};
boolean b35[] = {0,1,1,0,  0,1,1,0,  1,0,0,1,  0,1,1,1};
boolean b36[] = {1,0,1,1,  0,1,0,1,  0,0,1,0,  0,0,1,0};  
boolean b37[] = {1,1,0,1,  0,0,0,0,  1,0,1,1,  0,1,1,0};
boolean b38[] = {1,0,1,0,  0,1,0,1,  1,1,1,0,  0,1,0,1};
boolean b39[] = {1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1};

boolean* beats[] = {b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16,b17,b18,b19,b20,b21,b22,b23,b24,b25,b26,b27,b28,b29,b30,b31,b32,b33,b34,b35,b36,b37,b38,b39};


// index of place in the bar
int index1 = 0;
int index2 = 0;

// user variables
int timeSignature1 = 16;
int timeSignature2 = 16;
int bpm = 60;
int lastBpm = 0;
boolean displayBpm = false;

long previousMillis = 0;
long ledPreviousMillis = 0;
long bpmPreviousMillis = 0;






void setup()
{ 
  // set the speed of the motorss to 100 RPMs
  motor1.setSpeed(100);
  motor2.setSpeed(100);  

  // led's setup
  pinMode(ledBpm, OUTPUT);      

  // lcd setup
  lcdSetup();
  lcdPassiveNoteChar();
  lcdActiveNoteChar();
  lcdBlankChar();

  // start serial for debugging
  Serial.begin(9600);
}


void loop()
{
  // read tempo from potentiometer
  bpm = map(analogRead(pBpm), 0,1024, 30,180); 
  
  // read motor patterns potentiometer
   pattern1 = map(analogRead(pM1), 0,1024, 0,39);
  if (analogRead(pM1) < 5) { pattern1 = 0; }  
  if (analogRead(pM1) > 1018) { pattern1 = 39; }
  if (pattern1 != lastPattern1) { index1 = index2; lastPattern1 = pattern1; }
  
  
   pattern2 = map(analogRead(pM2), 0,1024, 0,39);  
  if (analogRead(pM2) < 5) { pattern2 = 0; }  
  if (analogRead(pM2) > 1018) { pattern2 = 39; }
  if (pattern2 != lastPattern2) { index2 = index1; lastPattern2 = pattern2; }  

  // read time signature potentiometer
  timeSignature1 = map(analogRead(pTs1), 0,1018, 1,15);  
  if (analogRead(pTs1) < 5) { timeSignature1 = 0; }  
  if (analogRead(pTs1) > 1018) { timeSignature1 = 16; }

  timeSignature2 = map(analogRead(pTs2), 0,1022, 1,16); 
  if (analogRead(pTs2) < 5) { timeSignature2 = 0; }    
  if (analogRead(pTs2) > 1018) { timeSignature2 = 16; }

  // interval between 1/16 notes is calculated according to the bpm
  long noteIntervalMs = 60000 / bpm / 16;

  // store current time
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > noteIntervalMs) 
  {
    // light LED on quarter notes
    if (index1 % 4 == 0) { digitalWrite(ledBpm, HIGH); } else { digitalWrite(ledBpm, LOW); }

    Serial.println(index1);
    Serial.println(index1 % 4);
    Serial.println("");    

    // save millis for next interval
    previousMillis = currentMillis;

    // move the index of the bar according to the time signature
    if (index1 < timeSignature1-1) { 
      index1++; 
    } 
    else { 
      index1 = 0; 
    }
    
    if (index2 < timeSignature2-1) { 
      index2++; 
    } 
    else { 
      index2 = 0; 
    }
    

    // check whether there are hits in this note
    hitTest();

    // debug
    // Serial.println(previousMillis);
  }
  digitalWrite(ledBpm, LOW);  
  
  
  /*
  // when bpm is changed, display it on the lcd
  if (bpm != lastBpm) {
    lastBpm = bpm;
    unsigned long currentBpmMillis = millis();

    if( currentBpmMillis - bpmPreviousMillis > 3000) { 
      bpmPreviousMillis = currentBpmMillis;            
      displayBpm = false;     
    } else {
      displayBpm = true;
    }
  }
  
  if (displayBpm) { lcdDisplayBpm(); } else { lcdLoop(); }
  */
  
  lcdLoop();


}


// test if the motors should play a beat in this 1/16th of the bar
void hitTest()
{
  if(beats[pattern1][index1] == 1) { 
    //Serial.println("motor1 hit");    
    hit(motor1); 
  }
  if(beats[pattern2][index2] == 1) { 
    //Serial.println("motor2 hit");
    hit(motor2); 
  }
}

// perform a single hit by a motor
void hit(Stepper motor)
{
  motor.step(1);
  delay(50);
  motor.step(-1);
}

// LCD greeting
void lcdSetup()
{
  // set the data rate for the NewSoftSerial port
  LCD.begin(9600);
  delay(100);

  LCD.print(0xFE,BYTE);    // enter command mode
  LCD.print(0x51,BYTE);    // clear screen, move cursor home

  LCD.print(0xFE,BYTE);    // enter command mode
  LCD.print(0x52,BYTE);    // select set contrast 
  LCD.print(32,BYTE);      // choose contast 32

  LCD.print(0xFE,BYTE);    // enter command mode
  LCD.print(0x53,BYTE);    // select set brightness
  LCD.print(6,BYTE);       // choose brightness 6
  
  LCD.print(0xFE,BYTE);    // enter command mode
  LCD.print(0x47,BYTE);    // turn on underline cursor

  LCD.print("beet beats 2000");// say hello for two seconds
  delay(2000);

  LCD.print(0xFE,BYTE);
  LCD.print(0x51,BYTE);    // clear screen, move cursor home
}

// LCD displays bpm & time signature
void lcdLoop()
{
  lcdDisplayPatterns();


}

// lcd bpm
void lcdDisplayBpm()
{
  LCD.print(0xFE,BYTE);    // enter command mode
  LCD.print(0x51,BYTE);    // clear screen, move cursor home
  
  LCD.print("BPM: ");
  LCD.print(bpm);
}

// lcd patterns
void lcdDisplayPatterns()
{ 
  LCD.print(0xFE,BYTE);    // enter command mode
  LCD.print(0x45,BYTE);    // select cursor position command
  LCD.print(0x00,BYTE);    // position cursor
  
  lcdDisplayPattern(timeSignature1, pattern1, index1);
  
  LCD.print(0xFE,BYTE);    // enter command mode
  LCD.print(0x45,BYTE);    // select cursor position command
  LCD.print(0x40,BYTE);    // position cursor
  
  lcdDisplayPattern(timeSignature2, pattern2, index2);
}


void lcdDisplayPattern(int timeSignature, int pattern, int index)
{
  for (int i=0; i<timeSignature; i++) {
    boolean note = beats[pattern][i];
    if (note == true) { 
      if (index == i) {
        LCD.print(0,BYTE); 
      } else {
        LCD.print(1,BYTE);
      }
    } else { 
      LCD.print(" "); 
    } 
  }
  for (int i=timeSignature; i<16; i++) {
    LCD.print(2,BYTE); 
  }
}

// custom note characted for the lcd pattern display
void lcdPassiveNoteChar() 
{
  LCD.print(0xFE,BYTE);   // cmd mode
  LCD.print(0x54,BYTE);   // custom character
  LCD.print(0,BYTE);      // address

  LCD.print(0xe,BYTE);   // row0
  LCD.print(0x1f,BYTE);   // row1
  LCD.print(0x17,BYTE);   // row2
  LCD.print(0x1f,BYTE);   // row3
  LCD.print(0x1f,BYTE);   // row4
  LCD.print(0x1f,BYTE);   // row5
  LCD.print(0x1f,BYTE);   // row6
  LCD.print(0x0e,BYTE);   // row7
}

// custom note characted for the lcd pattern display
void lcdActiveNoteChar() 
{
  LCD.print(0xFE,BYTE);   // cmd mode
  LCD.print(0x54,BYTE);   // custom character
  LCD.print(1,BYTE);      // address

  LCD.print(0xe,BYTE);   // row0
  LCD.print(0x1f,BYTE);   // row1
  LCD.print(0x11,BYTE);   // row2
  LCD.print(0x11,BYTE);   // row3
  LCD.print(0x11,BYTE);   // row4
  LCD.print(0x11,BYTE);   // row5
  LCD.print(0x1f,BYTE);   // row6
  LCD.print(0xe,BYTE);   // row7
}

// custom note characted for the lcd pattern display
void lcdBlankChar() 
{
  LCD.print(0xFE,BYTE);   // cmd mode
  LCD.print(0x54,BYTE);   // custom character
  LCD.print(2,BYTE);      // address

  LCD.print(0x1f,BYTE);   // row0
  LCD.print(0x1f,BYTE);   // row1
  LCD.print(0x1f,BYTE);   // row2
  LCD.print(0x1f,BYTE);   // row3
  LCD.print(0x1f,BYTE);   // row4
  LCD.print(0x1f,BYTE);   // row5
  LCD.print(0x1f,BYTE);   // row6
  LCD.print(0x1f,BYTE);   // row7
}

void debugPots()
{
 
  Serial.println("motor 1 pattern");
  Serial.println(analogRead(pM1));
  Serial.println("");  
  
  Serial.println("motor 2 pattern");  
  Serial.println(analogRead(pM2)); 
  Serial.println("");   
 
  Serial.println("ts 1"); 
  Serial.println(analogRead(pTs1)); 
  Serial.println("");   
 
  Serial.println("ts 2"); 
  Serial.println(analogRead(pTs2));   
  Serial.println("");   
  
  Serial.println("bpm");  
  Serial.println(analogRead(pBpm));  
  Serial.println("");   
  
  delay(500);
}
