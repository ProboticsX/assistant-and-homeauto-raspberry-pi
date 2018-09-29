#include <SoftwareSerial.h>
//ground ka side wala rx h 
//aur software serial esp(9,10) mei humesha 10 pin rx se connect hogi esp k
SoftwareSerial esp(9,10);
int c=0;
int global=1000;


int led1 = 5;
int fan1 = 6;

void l_on() {
  digitalWrite (led1, HIGH);
 
}

void l_off() {
  digitalWrite (led1, LOW);
 }

void f_on(){
    digitalWrite (fan1, HIGH);
}

void f_off() {
  digitalWrite (fan1, LOW);
 }


void setup() {
  Serial.begin(115200);
  esp.begin(115200);
  
   pinMode(led1, OUTPUT);
  digitalWrite (led1, HIGH);
   pinMode(fan1, OUTPUT);
  digitalWrite (fan1, HIGH);
   pinMode(13, OUTPUT);
   digitalWrite (13, HIGH);
  
  esp.flush();




  
  connect_wifi();
  cipmux();
  cipserver();
  digitalWrite (13, LOW);
//  domain();
//  send_data();
//  domain();
//  check_data();
  }

void loop() {
  
   if(c==global){
    digitalWrite (13, HIGH);
    connect_wifi();
    cipmux();
    cipserver();
    c=0;
    digitalWrite (13, LOW);
   }
   
   c=0;
  esp.flush();

String got_ip=esp.readString();
Serial.println(got_ip);

String lon="380";
String loff="381";
String fon="382";
String foff="383";

if(got_ip.indexOf(lon)!=-1){
Serial.println("LIGHTS ONNNNNNNNN");
l_on();
}
if(got_ip.indexOf(loff)!=-1){
Serial.println("LIGHTS OFFFFFFF");
l_off();
}
if(got_ip.indexOf(fon)!=-1){
Serial.println("FAN ONNNNNNNNN");
f_on();
}
if(got_ip.indexOf(foff)!=-1){
Serial.println("FAN OFFFFF");
f_off();
}


esp.flush();
 
c++;  
  
  }

void connect_wifi(){
  c=0;
  esp.flush();
  esp.print("AT+CWJAP=\"shubham jain\",\"shubham123\"\r\n");

  while(!esp.find("CONNECTED"))
  {
    c++;
    if(c>=20){
      break;
    }
  }
String got_ip=esp.readString();
Serial.println(got_ip);

if(c>=20)
Serial.println("connect_wifi_timeout");

esp.flush();

}


void cipmux(){

c=0;
  esp.flush();
  esp.print("AT+CIPMUX=1\r\n");

  while(!esp.find("OK"))
  {
    c++;
    if(c>=20){
      break;
    }
  }
String got_ip=esp.readString();
Serial.println(got_ip);

if(c>=20)
Serial.println("cipmux timeout !!");

esp.flush();

  
}


void cipserver(){

c=0;
  esp.flush();
  esp.print("AT+CIPSERVER=1,80\r\n");

  while(!esp.find("OK")|| !esp.find("no"))
  {
    c++;
    if(c>=20){
      break;
    }
  }
String got_ip=esp.readString();
Serial.println(got_ip);

if(c>=20)
Serial.println("cipserver timeout !!");

esp.flush();
  
  
}


void domain(){

  esp.flush();
  esp.print("AT+CIPSTART=\"TCP\",\"locateurfamily.com\",80\r\n");
c=0;

  while(!esp.find("CONNECT")){
    c++;
    if(c>=20){
      break;
    }
  }

String j=esp.readString();
Serial.println(j);

if(c>=20)
Serial.println("timeout-2!");

esp.flush();}

void send_data(){

 c=0;
 esp.flush();
String send_wifi="GET http://locateurfamily.com/arduino1.php?temperature=80&humidity=70 HTTP/1.0\r\n\r\n";

 esp.print("AT+CIPSEND="+(String)send_wifi.length()+"\r\n");

 while(!esp.find("OK")){
  c++;
  if(c>=20){
    Serial.println("timeout-3a!");
    break;
  }
 }
 String k=esp.readString();
 Serial.println(k);
 esp.flush();

 int d=0;
 esp.print(send_wifi);

 while(!esp.find("IPD")){
  d++;
  if(d>=20){
    Serial.println("timeout-3b!");
    break;
  }
 }

 String m=esp.readString();
 Serial.println(m);
 esp.flush();
  
 }

void check_data(){
c=0;
esp.flush();

String check="GET http://locateurfamily.com/Home.php HTTP/1.0\r\n\r\n";
   esp.print("AT+CIPSEND="+(String)check.length()+"\r\n");

 while(!esp.find("OK")){
  c++;
  if(c>=20){
    Serial.println("timeout-4a!");
    break;
  }
 }
 String p=esp.readString();
 Serial.println(p);
 
 esp.flush();

 int d=0;
 esp.print(check);

 while(!esp.find("IPD")){
  d++;
  if(d>=20){
    Serial.println("timeout-4b!");
    break;
  }
 }

 String q=esp.readString();
 Serial.println(q);
 Serial.println(q.length());
 esp.flush();
  
 }


