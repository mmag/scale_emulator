
/*
  Scale indicator emulator.
  
  Emulates CAS-series analog indicators and digital HBM emulator 
*/


int sensorPin = A0;    
int sensorValue = 0;  
int modePin = A4;
int mode = LOW;
int button = PUSH2;
int button_state = LOW;
int incomingByte = 0; 
char command[] = "";
int i = 0;

void setup() {
  
  pinMode(GREEN_LED, OUTPUT);  
  pinMode(button, INPUT_PULLUP);
  pinMode(modePin, INPUT);
  Serial.begin(9600);
}

void loop() {
  mode = digitalRead(modePin);

  if(mode == LOW)
  {  
    digitalWrite(GREEN_LED, LOW);
    
    sensorValue = analogRead(sensorPin);    
  
    button_state = digitalRead(button);
    if (button_state == LOW)
    {
      Serial.print("US,GS,<8,");
      digitalWrite(GREEN_LED, HIGH);
    }
    else
    {
      Serial.print("ST,GS,<8,");
      digitalWrite(GREEN_LED, LOW);
    }  
  
    if (sensorValue < 10)
    {
       Serial.print("<<<<<<<"); 
    }
    else if (sensorValue < 100)
    {
      Serial.print("<<<<<<");
    }
    else if (sensorValue < 1000)
    {
      Serial.print("<<<<<");
    }
    else 
    {
      Serial.print("<<<<");
    } 
    Serial.print(sensorValue);
    Serial.println("0kg"); 
    delay(30);
  } 
  else
  {
    digitalWrite(GREEN_LED, HIGH);
    i = 0;
    sensorValue = analogRead(sensorPin);  
    while (Serial.available() > 0) {  
        command[i] = Serial.read();
        i++;
        if (i > 5)
        {
          i = 0;
          break;
        }
    }
    //command = command.toLowerCase();
    if((command[0] == 77))
    {
        //Serial.print("I received: ");
        Serial.print("0000");
        Serial.print(sensorValue);
        Serial.println(" kg");
        //Serial.println(command);
        command[0] = 0;
        i = 0;
        /*
        
        delay(50);
        digitalWrite(GREEN_LED, LOW);*/
    }
    
    //Serial.println("HBM mode on");
    delay(30);

  }
}
