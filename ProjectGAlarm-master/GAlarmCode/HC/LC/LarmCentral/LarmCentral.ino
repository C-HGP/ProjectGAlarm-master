#include <Keypad.h>

//Declaring keypad
const byte ROWS = 4;
const byte COLS = 4;
//Define the keymap
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};


//Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins
byte rowPins[ROWS] = {6, 7, 8, 9};
//Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins
byte colPins[COLS] = {2, 3, 4, 5};


//Create the keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


//Declaring PINS
int pinGreen = 12;
int pinYellow = 11;
int pinRed = 10;


//Declaring varibles used
String pin;
String pinSend;
int triesLeft = 0;


//Setup pins
void setup()
{
  // put your setup code here, to run once:
  pinMode(pinGreen, OUTPUT);
  pinMode(pinYellow, OUTPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(A4, INPUT);  // Button
  pinMode(A5, INPUT);  // Button
  pinMode(A3, OUTPUT); // Buzzer

  Serial.begin(9600);
}


//Sends you to main function of the alarm
void loop()
{
  alarmMain(0);
}


//Main system
void alarmMain(int guide)
{
  if (guide == 1)
  {
    buzzer(6);
  }
  while (true)
  {

    digitalWrite(pinGreen, HIGH);

    pinchk();
    int sensStatus01 = sensorFULL();
    if (sensStatus01 == 1)
    {
      buzzer(3);
    }
    int sensStatus02 = sensorSHELL();
    if (sensStatus02 == 1)
    {
      buzzer(3);
    }
  }
}

//Reads the keypad and sends back to PC/HCENTRAL
void pinchk()
{
  String receive;
  char key = kpd.getKey();
  if (key) //Check for a valid key
  {
    switch (key)
    {
    case '*':
      Serial.println(key);
      break;

    case '1':
      pin += "1";
      break;
    case '2':
      pin += "2";
      break;
    case '3':
      pin += "3";
      break;
    case '4':
      pin += "4";
      break;
    case '5':
      pin += "5";
      break;
    case '6':
      pin += "6";
      break;
    case '7':
      pin += "7";
      break;
    case '8':
      pin += "8";
      break;
    case '9':
      pin += "9";
      break;
    case 'A':
      Serial.println(key);
      break;
    case 'B':
      Serial.println(key);
      break;
    case 'C':
      Serial.println(key);
      break;
    case 'D':
      Serial.println(key);
      break;
    case '#':
      pinSend = 'A' + pin;
      Serial.print(pinSend);
      receive = Serial.readString();
      pin.remove(0);
      if (receive == "1")
      {
        triesLeft = 0;
        alarmOff(0);
      }
      if (receive != "1")
      {
        buzzer(8);
        triesLeft++;
        if (triesLeft == 3)
        {
          alarmLocked();
        }
      }
      break;
    default:
      Serial.println(key);
      break;
    }
  }
}


//Alarm off state
void alarmOff(int offGuide)
{
  if (offGuide == 1)
  {
    buzzer(7);
  }
  if (offGuide == 0)
  {
    buzzer(1);
  }

  while (true)
  {

    digitalWrite(pinGreen, LOW);
    digitalWrite(pinYellow, LOW);
    digitalWrite(pinRed, LOW);
    char key = kpd.getKey();
    if (key)
    {
      if (key == 'A')
      {
        AlarmON('A'); // FULL ALARM
      }
      if (key == 'B')
      {
        AlarmON('B'); //SHELLALARM
      }
    }
  }
}

//AlarmON State
void AlarmON(char signl)
{

  while (true)
  {
    char key = kpd.getKey();
    if (key) //Check for a valid key
    {
      switch (key)
      {

      case '1':
        pin += "1";
        break;
      case '2':
        pin += "2";
        break;
      case '3':
        pin += "3";
        break;
      case '4':
        pin += "4";
        break;
      case '5':
        pin += "5";
        break;
      case '6':
        pin += "6";
        break;
      case '7':
        pin += "7";
        break;
      case '8':
        pin += "8";
        break;
      case '9':
        pin += "9";
        break;
      case 'A':
        Serial.println(key);
        break;
      case 'B':
        Serial.println(key);
        break;
      case 'C':
        Serial.println(key);
        break;
      case 'D':
        Serial.println(key);
        break;

      case '*':
        Serial.println(key);
        break;
      case '#':
        pinSend = 'D' + pin;
        Serial.print(pinSend);
        String receive = Serial.readString();

        if (receive == "1")
        {
          if (signl == 'A')
          {
            buzzer(5);
            digitalWrite(pinRed, HIGH);
            buzzer(4);
            pin.remove(0);
            delay(200);
            digitalWrite(pinRed, LOW);
            int ifSensor = digitalRead(A4);
            //Sends you
            alarmMain(ifSensor);
          }

          if (signl == 'B')
          {
            buzzer(1);
            digitalWrite(pinRed, HIGH);
            buzzer(4);
            delay(200);
            pin.remove(0);
            digitalWrite(pinRed, LOW);
            alarmShell();
          }
        }

        if (receive != "1")
        {
          pin.remove(0);
          alarmOff(1);
        }

        break;
      default:
        Serial.println(key);
        break;
      }
    }
  }
}


//Shell funciton for the system
void alarmShell()
{
  while (true)
  {
    digitalWrite(pinGreen, HIGH);
    pinchk();
    //Starts alarm in shell
    int sensStatus02 = sensorSHELL();
    if (sensStatus02 == 1)
    {
      buzzer(3);
    }
  }
}


// Function for sensor 1
int sensorFULL()
{
  int sensorRead = digitalRead(A4);
  if (sensorRead == 1)
  {
    Serial.print('T');
    return 1;
  }
  return 0;
}

// function for sensor 2
int sensorSHELL()
{
  int sensorRead = digitalRead(A5);
  if (sensorRead == 1)
  {
    Serial.print('Q');
    return 1;
  }
  return 0;
}


//Creates the buzzer function and using IF to have different tones
void buzzer(int mode)
{
  if (mode == 1)
  {
    tone(A3, 800);
    digitalWrite(pinGreen, HIGH);
    delay(500);
    digitalWrite(pinGreen, LOW);
    noTone(A3);
    tone(A3, 800);
    digitalWrite(pinGreen, HIGH);
    delay(500);
    digitalWrite(pinGreen, LOW);
    noTone(A3);
  }
  if (mode == 2)
  {
    tone(A3, 1000);
    delay(1000);
    noTone(A3);
    delay(500);
    tone(A3, 1000);
    delay(1000);
    noTone(A3);
    delay(500);
    tone(A3, 1000);
    delay(1000);
    digitalWrite(pinGreen, LOW);
    noTone(A3);
  }
  if (mode == 3)
  {
    tone(A3, 1000);
    digitalWrite(pinGreen, HIGH);
    digitalWrite(pinYellow, HIGH);
    digitalWrite(pinRed, HIGH);
    delay(100);
    noTone(A3);
    delay(100);
    tone(A3, 500);
    delay(100);
    tone(A3, 1000);
    digitalWrite(pinGreen, LOW);
    digitalWrite(pinYellow, LOW);
    digitalWrite(pinRed, LOW);
    delay(100);
    noTone(A3);
    delay(100);
    tone(A3, 500);
    delay(100);
    noTone(A3);
  }
  if (mode == 4)
  {
    tone(A3, 500);
    delay(100);
    noTone(A3);
    tone(A3, 1000);
    delay(100);
    noTone(A3);
    tone(A3, 1500);
    delay(100);
    noTone(A3);
  }
  if (mode == 5)
  {
    tone(A3, 1000);
    digitalWrite(pinGreen, HIGH);
    delay(1000);
    digitalWrite(pinGreen, LOW);
    noTone(A3);
    delay(500);
    tone(A3, 1000);
    digitalWrite(pinGreen, HIGH);
    delay(1000);
    digitalWrite(pinGreen, LOW);
    noTone(A3);
    delay(500);
    tone(A3, 1000);
    digitalWrite(pinGreen, HIGH);
    delay(1000);
    digitalWrite(pinGreen, LOW);
    noTone(A3);
  }

  if (mode == 6)
  {
    digitalWrite(pinYellow, HIGH);
    for (int i = 0; i < 15; i++)
    {
      tone(A3, 500);
      digitalWrite(pinRed, HIGH);
      delay(100);
      noTone(A3);
      digitalWrite(pinRed, LOW);
      delay(100);
    }
  }
  if (mode == 7)
  {
    tone(A3, 300);
    digitalWrite(pinRed, HIGH);
    delay(200);
    noTone(A3);
    delay(50);
    tone(A3, 300);
    digitalWrite(pinRed, HIGH);
    delay(200);
    noTone(A3);
    delay(50);
    tone(A3, 300);
    digitalWrite(pinRed, HIGH);
    delay(200);
    noTone(A3);
    delay(50);
  }

  if (mode == 8)
  {
    tone(A3, 1000);
    digitalWrite(pinRed, HIGH);
    delay(100);
    noTone(A3);
    delay(100);
    tone(A3, 1000);
    digitalWrite(pinRed, HIGH);
    delay(100);
    noTone(A3);
    delay(100);
    tone(A3, 1000);
    digitalWrite(pinRed, HIGH);
    delay(100);
    noTone(A3);
    delay(100);
    digitalWrite(pinRed, LOW);
  }
}


// Locks system if user tried over 3 incorrect pins
void alarmLocked()
{
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinRed, LOW);
  digitalWrite(pinYellow, LOW);
  while (true)
  {
    tone(A3, 1000);
    digitalWrite(pinRed, HIGH);
    delay(1000);
    noTone(A3);
    digitalWrite(pinRed, LOW);
    delay(1000);
  }
}


void pinchkTheSequel()
{
  String receive;
  char key = kpd.getKey();
  if (key) //Check for a valid key
  {
    switch (key)
    {
    case '*':
      Serial.println(key);
      break;

    case '1':
      pin += "1";
      break;
    case '2':
      pin += "2";
      break;
    case '3':
      pin += "3";
      break;
    case '4':
      pin += "4";
      break;
    case '5':
      pin += "5";
      break;
    case '6':
      pin += "6";
      break;
    case '7':
      pin += "7";
      break;
    case '8':
      pin += "8";
      break;
    case '9':
      pin += "9";
      break;
    case 'A':
      Serial.println(key);
      break;
    case 'B':
      Serial.println(key);
      break;
    case 'C':
      Serial.println(key);
      break;
    case 'D':
      Serial.println(key);
      break;
    case '#':
      pinSend = 'D' + pin;
      Serial.print(pinSend);
      receive = Serial.readString();
      pin.remove(0);
      if (receive == "1")
      {
        triesLeft = 0;
        alarmOff(0);
      }
      if (receive != "1")
      {
        buzzer(8);
        triesLeft++;
        if (triesLeft == 3)
        {
          alarmLocked();
        }
      }
      break;
    default:
      Serial.println(key);
      break;
    }
  }
}
