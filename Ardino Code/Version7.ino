#include <SoftwareSerial.h>
//#include <dht.h>
//temp sensor
//dht DHT;
//#define DHT11_PIN 2;



//somke sensor 
const int sensorPin= 0;
int smoke_level=0;
int temSensor=0;
int humSensor=0;
String smokeString="Failed";
int smokeTemp=0;


const int ledPin = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
SoftwareSerial wifi(8,9);

char c;
String d;
bool dStarted = false;
String Len;
void setup(){
  smoke_level= analogRead(sensorPin); //arduino reads the value from the smoke sensor
  smokeTemp=smoke_level;
  dataSend("s"+smokeString);
  pinMode(sensorPin, INPUT);//the smoke sensor will be an input to the arduino
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  wifi.begin(115200);
  while(!wifi){;}
  Serial.begin(115200);
  while(!Serial){;}

 // atCommand("AT+RST");
  

 
  
  

 // atCommand("AT+CIPSTART=2,\"TCP\",\"192.168.1.101\",3500");



///////////////////////////////////////////////////////////////////////////////////////////

//atCommand("AT+CWMODE=3"); //Station mode or AP
 // atCommand("AT+CWJAP=\"WINGLE CLOUD-A8C\",\"FADF1D13\"");
//atCommand("AT+CIFSR");//GET IP ADDRESS  //Do'nt comment it 
//atCommand("AT+CIPMUX=1");   //SINGLE OR MULTIPLE CONNECTION 1=MULTIOPLE,0=SINGLE CONNECTION //do not comment it 

//atCommand("AT+CIPSERVERMAXCONN=5"); //max connection support by server 1-5 
//atCommand("AT+CIPSERVER=1,3500"); //SERVER MODE,PORT NUMBER  MODE=1=OPEN, MODE=0=CLOSE  //do not comment it

//atCommand("AT+CIPMODE=0"); //Transmission mode 0= sample 1= 
//atCommand("AT+CIPSTO=30"); //sever time out 0 ~ 7200s.  0 never timeout


//atCommand("AT+CIPSTART=0,\"TCP\",\"192.168.1.104\",3500");

  atCommand("AT+CWMODE=2");
  atCommand("AT+CIFSR");
  atCommand("AT+CIPMUX=1");
  atCommand("AT+CIPSERVER=1,3500");

  Serial.println("Server Started!!!");  
}

void loop(){

//dataSend("Lit");





  while(wifi.available()){
   
    c = wifi.read();
    if(c == '*') dStarted = true;
    else if(c == '#') dStarted = false;
    else if(dStarted) d += c;
    
    
    if(!dStarted && d.length() > 0){
    if(d=="1")
    {
     // Serial.println("Light is On");
      digitalWrite(ledPin, HIGH);
      dataSend("ALight1 is ON");
    }
    if(d=="0")
    {
      Serial.println("Light is OFF");
      digitalWrite(ledPin, LOW);
      dataSend("BTurned OFF");
    }

    if(d=="2")
    {
      Serial.println("Light is On");
      digitalWrite(ledPin2, HIGH);
      dataSend("Light is ON");
      
    }
    if(d=="02")
    {
      Serial.println("Light is OFF");
      digitalWrite(ledPin2, LOW);
      dataSend("Light is off");
    }


//fan code


//    if(d=="10")
//    {
//      Serial.println("Fan is ON");
//      digitalWrite(ledPin3, HIGH);
//      //dataSend("Light is ON");
//      
//    }
//    if(d=="01")
//    {
//      Serial.println("Fan is OFF");
//      digitalWrite(ledPin3, LOW);
//      
//    }

    
    //  Serial.println("DATA: "+d);
      //d var => data received from mobile socket
      //put your logic to controll devices below

      //Call dataSend(parameter => dataToSend(string))
      d = "";
    }
  }
//smoke sensor code

smoke_level= analogRead(sensorPin); //arduino reads the value from the smoke sensor

smokeString=smoke_level;

 // if(smoke_level > 200){ //if smoke level is greater than 200, the buzzer will go off
 
   if(smoke_level>=smokeTemp+30 || smoke_level<=smokeTemp-30)
   {
    smokeTemp=smoke_level;
dataSend("s"+smokeString);
   }
  
//}
//else{
//  if(smoke_level>=smokeTemp+4 || smoke_level<+smokeTemp-4)
//  {
//    smokeTemp=smoke_level;
//dataSend("s"+smokeString); 
//}}//end of somke sensor


//Temperture  sensor data

if(temSensor==0)
{
  temSensor=1;
dataSend("t20");
  
}
if(humSensor==0)
{
humSensor=1;
dataSend("h30");

  
}



  
}

void atCommand(String atc){
  wifi.println(atc);
  String r = "";
  long int ct = millis();
  while((ct + 10) > millis()){
    while(wifi.available()){
      r += (char)wifi.read();
    }
  }
  Serial.println("AT COMMAND: "+r);
  delay(500);
  atc="";
}

void dataSend(String Data){
  Len="";
  Len+=Data.length();
  //Len=Data.length();
  //Serial.println(Data);
  delay(200);
  atCommand("AT+CIPSEND=0,"+Len);
  delay(200);
  atCommand(Data);
//  atCommand("AT+CIPSENDBUF=0,"+Len);
  //atCommand(Data);
   
  
  
 //atCommand("AT+CIPCLOSE=1"); 
}

