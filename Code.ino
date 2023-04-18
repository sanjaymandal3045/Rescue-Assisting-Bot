const int ina = 2;
const int inb = 3;
const int inc = 4;
const int ind = 5;

unsigned long int currtime;
bool flag = false;
const int trigPin = 7;
const int echoPin = 8;
long duration;
int distance;

const int buzzerpin = 10 ;
const int motion = 11; 

const int flamepin = 9 ; 

int Flame = HIGH ;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);

  
  pinMode(ina, OUTPUT);
  pinMode(inb, OUTPUT);
  pinMode(inc, OUTPUT);
  pinMode(ind, OUTPUT);

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  
  

  pinMode(buzzerpin,OUTPUT); 
  pinMode(flamepin, INPUT); 

  currtime = millis();

  //  digitalWrite(ina, HIGH);
  //  digitalWrite(ind, HIGH);
  //  delay(4000);
  //  digitalWrite(ina, LOW);
  //  digitalWrite(ind, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available())
  {
    char x = Serial1.read();
    Serial.println(x);
    if (x == 'F')
    {
      digitalWrite(ina, HIGH);
      digitalWrite(ind, HIGH);
      digitalWrite(inb, LOW);
      digitalWrite(inc, LOW);
    }
    else if (x == 'B')
    {
      digitalWrite(ina, LOW);
      digitalWrite(ind, LOW);
      digitalWrite(inb, HIGH);
      digitalWrite(inc, HIGH);
    }
    else if (x == 'L')
    {
      digitalWrite(ina, LOW);
      digitalWrite(ind, HIGH);
      digitalWrite(inb, HIGH);
      digitalWrite(inc, LOW);
    }
    else if (x == 'R')
    {
      digitalWrite(ina, HIGH);
      digitalWrite(ind, LOW);
      digitalWrite(inb, LOW);
      digitalWrite(inc, HIGH);
    }
    else if (x == 'S')
    {
      digitalWrite(ina, LOW);
      digitalWrite(ind, LOW);
      digitalWrite(inb, LOW);
      digitalWrite(inc, LOW);
    }
  }


  // Ultrasonic sensor codes...
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  // Set trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 20000); // 20ms er moddhe kisu na paile code niche jabe
  distance= (duration*0.034)/2;

  if(distance<=20){
    digitalWrite(buzzerpin,HIGH);
    
    //delay(500); // ...for 1 sec
    //
    //delay(500);
    if(millis() - currtime>500){
      currtime = millis();
      if(!flag){
        tone(buzzerpin,500); // Send 1KHz sound signal...
        flag = true;        
      }
      else{
        noTone(buzzerpin); // Stop sound...
        flag = false;
      }
    }    
  }
  else{
    noTone(buzzerpin);      
  }

  //Serial1.print("Distance(cm): ");
  //Serial1.print("Distance(cm): ");
  //Serial1.println(distance);



// Flame sensor working code...
  Flame = digitalRead(flamepin) ;

  if(Flame == LOW){
    digitalWrite(buzzerpin,HIGH);
    tone(buzzerpin,300); // Send 1KHz sound signal...
    delay(100); // ...for 1 sec
    noTone(buzzerpin); // Stop sound...
    delay(100);
    Serial1.println("Fire detected");
  }
  else{
   digitalWrite(buzzerpin,LOW);
  }
  int motionState = digitalRead(motion);  


  //Motion Sensor code
  if(motionState == 0)
  {
    Serial1.println("No Movement Detected");
  }  
  else
  {
    Serial1.println("Movement Detected Ahead!!!!!!!!!!!");
  }
  

}
