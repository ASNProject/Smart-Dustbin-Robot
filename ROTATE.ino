//                                                     Program Robot Tempat Sampah Otomatis
//                                                              Rizky, Ega, Nasir
//                                                            Program  Studi  Fisika
//                                                           Universitas Ahmad Dahlan
//                                           Kampus IV, Jln.Ringroad Utara, Tamanan, Banguntapan, Bantul
//                                                                  Yogyakarta
//===================================================================================================================================================
//                                                           NodeMCU ESP8266 Lolin V3
//                                                          Blynk  Application Android
//                                                         Developed by ASNProject 2019
//                                                            asnproject02@gmail.com
//                                                                 087837964394
//===================================================================================================================================================
//                                                 ======   ====  ========  ====   ======== ======
//                                                 ==   == ==  ==    ==    ==   ==    ==    ==
//                                                 == ==   ==  ==    ==    == = ==    ==    ======
//                                                 ==  ==  ==  ==    ==    ==   ==    ==    ==
//                                                 ==   ==  ====     ==    ==   ==    ==    ======
//===================================================================================================================================================

//Masukan Library Blynk
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Pengaturan Wifi NodeMCU
char auth[] = "c7d2576bb4024967b0d7ea069817211d";
char ssid[] = "ROTATE";
char pass[] = "hajiwada";

//Masukan pin dan nilai sensor inframerah untuk deteksi sampah penuh
int inputPin = 15; // choose input pin (for Infrared sensor) 
int val = 0; // variable for reading the pin status 

//Masukan pin motor DC
int m1 = 16;
int m2 = 5;
int m3 = 4;
int m4 = 0;

//Masukan pin sensor garis
int s1 = 1;
int s2 = 3;

//Masukan pin dan inisialisasi sensor ultrasonik
const int trigPin = 2;
const int echoPin = 14;
long duration;
int distance;

const int trig = 12;
const int echo = 13;
long durasi;
int jarak;

void setup(){
  Serial.begin(115200);
  pinMode(inputPin, INPUT); // declare Infrared sensor as input
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop(){
  //Menjalankan Blynk
  Blynk.run();
  //Nilai Val akan membaca sensor pada pin
  val = digitalRead(inputPin);
  if (val == HIGH){
    Blynk.notify("Tempat Sampah Penuh, Menuju Tempat Pembuangan");
    linefollower1();
    ultrasonik();
    ultra();
  }
  else{
Blynk.notify("Tempat Sampah Kosong, Menuju Tempat Awal");
linefollower();
ultrasonik2();
ultra1();
  }

}

//Program LineFollower
void linefollower(){
  
  int kiri = digitalRead(s1);
  int kanan = digitalRead(s2);

  if ((kiri==HIGH)&&(kanan==LOW)){
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
  }
  else if ((kiri==LOW)&&(kanan==HIGH)){

    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
  }
  else if ((kiri==HIGH)&&(kanan==HIGH))
  {
    stopp();

  }
   else
  {

    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
  }
}

//Program Ultrasonik
void ultrasonik(){
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
delay(1);
if (distance <= 10){
stopp();
if (distance >= 10){
  linefollower1();
}
}
}

void maju(){
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);

}
void stopp(){
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
}

void belok(){
      digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
}

//program ultrasonik2
void ultra(){
// Clears the trigPin
digitalWrite(trig, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
durasi = pulseIn(echo, HIGH);
jarak= durasi*0.034/2;
delay(1);

if (jarak <= 20){
stopp();
  }
  if (jarak >= 20){
    linefollower1();;
  }
}

void linefollower1(){
  int kiri = digitalRead(s1);
  int kanan = digitalRead(s2);

  if ((kiri==HIGH)&&(kanan==LOW)){
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
  }
  else if ((kiri==LOW)&&(kanan==HIGH)){

    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
  }
  else if ((kiri==HIGH)&&(kanan==HIGH))
  {
    belok();
    delay(1500);//GANTI NILAI DELAY UNTUK MENGATUR WAKTU BERBELOK PADA SAAT TEMPAT SAMPAH PENUH!!
  }
   else
  {

    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
  }
}

void ultrasonik2(){
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
delay(1);
if (distance <= 10){
belok();
delay(1500);//GANTI NILAI DELAY UNTUK MENGATUR WAKTU BERBELOK PADA SAAT TEMPAT SAMPAH KOSONG!!
if (distance >= 10){
  linefollower();
}
}
}

void ultra1(){
// Clears the trigPin
digitalWrite(trig, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
durasi = pulseIn(echo, HIGH);
jarak= durasi*0.034/2;
delay(1);

if (jarak <= 20){
stopp();
  }
  if (jarak >= 20){
    linefollower();;
  }
}

