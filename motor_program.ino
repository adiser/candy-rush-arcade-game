//Arduino PWM Speed Control：
int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7;                        
int right_reader = 13;
int left_reader = 12;
void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT);
    pinMode(right_reader, INPUT);
    pinMode(left_reader, INPUT);
    Serial.begin(9600);
} 

void loop() 
{ 
  int right;
  int left; 
  right = digitalRead(right_reader);
  left = digitalRead(left_reader);
  if (right==1 && left == 0)
  {
    Serial.println("right");
    digitalWrite(M1, HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, 255);   //PWM Speed Control
    analogWrite(E2, 255);   //PWM Speed Control
    delay(30); 
  }
  if (right == 0 && left == 1)
  {
    Serial.println("left");
    digitalWrite(M1, LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, 255);   //PWM Speed Control
    analogWrite(E2, 255);   //PWM Speed Control
    delay(30); 
  }
  if ((right == 0 && left == 0) || (right == 1 && left == 1))
  {
    Serial.println("nothing");
    digitalWrite(M1, LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, 0);   //PWM Speed Control
    analogWrite(E2, 0);   //PWM Speed Control
  }
}
