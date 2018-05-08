#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include "HMC5883L.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

SoftwareSerial serial1(3,5); // RX, TX
TinyGPS gps1;
HMC5883L compass;

void setup() {
  
   serial1.begin(9600);
   Serial.begin(9600);
   display.begin();
   
   Serial.println("Bulssola HMC5883L e GPS");
    // Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_30HZ);

  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(0, 0);
  

}
   
      
void loop() {
  
  display.setContrast(50); //Ajusta o contraste do display
  display.clearDisplay();   //Apaga o buffer e o display
  display.setTextSize(1);  //Seta o tamanho do texto
  display.setTextColor(BLACK); //Seta a cor do texto
  display.setCursor(0,1);  //Seta a posição do cursor
  
  bool recebido = false;

  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = gps1.encode(cIn);
      recebido = true;  
      
  }


  if (recebido) {
     Serial.println("----------------------------------------");
     display.println("RECEBENDO COORDENADAS");//Escreve no display  
     display.display();
     display.clearDisplay();//limpa o display
  
     
     Vector norm = compass.readNormalize();
     long latitude, longitude;
        gps1.get_position(&latitude, &longitude); 


  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);
 
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0)
  {
    heading += 2 * PI;
  }

  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }

  // Convert to degrees
  int headingDegrees = heading * 180/M_PI;

     
     
       if (headingDegrees > 337 and headingDegrees < 361 || headingDegrees >= 0 and headingDegrees < 23 )
  {
   

      if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 7);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 7);
     }
    Serial.print(" Norte = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    
    display.println(" Coordenadas");
    display.println("");
    display.print("La:");
    display.println(float(latitude) / 100000, 7);
    display.print("Lo:"); 
    display.println(float(longitude) / 100000, 7);
    display.println("");
    display.print("Norte: ");
    display.print(headingDegrees); 
    display.display();
    display.clearDisplay();//limpa o display
  }
  
   if (headingDegrees > 22 and headingDegrees < 68)
  {
  if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 7);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 7);
     }
    
    Serial.print(" Nordeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    display.println(" Coordenadas");
    display.println("");
    display.print("La:");
    display.println(float(latitude) / 100000, 7);
    display.print("Lo:"); 
    display.println(float(longitude) / 100000, 7);
    display.println("");
    display.print("Nordeste: ");
    display.print(headingDegrees); 
    display.display();
    display.clearDisplay();//limpa o display
  } 
  
  if (headingDegrees > 67 and headingDegrees < 113)
  {
 
    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 7);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 7);
     }
    
    Serial.print(" Leste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    display.println(" Coordenadas");
    display.println("");
    display.print("La:");
    display.println(float(latitude) / 100000, 7);
    display.print("Lo:"); 
    display.println(float(longitude) / 100000, 7);
    display.println("");
    display.print("Leste: ");
    display.print(headingDegrees); 
    display.display();
    display.clearDisplay();//limpa o display
    
  } 
  if (headingDegrees > 112 and headingDegrees < 157)
  {
 
    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 7);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 7);
     }
    
    Serial.print(" Sudeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    display.println(" Coordenadas");
    display.println("");
    display.print("La:");
    display.println(float(latitude) / 100000, 7);
    display.print("Lo:"); 
    display.println(float(longitude) / 100000, 7);
    display.println("");
    display.print("Sudeste: ");
    display.print(headingDegrees); 
    display.display();
    display.clearDisplay();//limpa o display
   
  } 
  if (headingDegrees > 156 and headingDegrees < 203)
  {

    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 7);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 7);
     }
    
    Serial.print(" Sul = ");
    Serial.print(headingDegrees);
    Serial.println("  Graus");
    display.println(" Coordenadas");
    display.println("");
    display.print("La:");
    display.println(float(latitude) / 100000, 7);
    display.print("Lo:"); 
    display.println(float(longitude) / 100000, 7);
    display.println("");
    display.print("Sul: ");
    display.print(headingDegrees); 
    display.display();
    display.clearDisplay();//limpa o display
   
  }
  
  if (headingDegrees > 202 and headingDegrees < 248)
  {

    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 7);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 7);
     }
    
    Serial.print(" Sudoeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    display.println(" Coordenadas");
    display.println("");
    display.print("La:");
    display.println(float(latitude) / 100000, 7);
    display.print("Lo:"); 
    display.println(float(longitude) / 100000, 7);
    display.println("");
    display.print("Sudoeste: ");
    display.print(headingDegrees); 
    display.display();
    display.clearDisplay();//limpa o display
    
  }
  if (headingDegrees > 247 and headingDegrees < 293)
  {

    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 7);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 7);
     }
    
    Serial.print(" Oeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    display.println(" Coordenadas");
    display.println("");
    display.print("La:");
    display.println(float(latitude) / 100000, 7);
    display.print("Lo:"); 
    display.println(float(longitude) / 100000, 7);
    display.println("");
    display.print("Oeste: ");
    display.print(headingDegrees); 
    display.display();
    display.clearDisplay();//limpa o display

  }
  
  if (headingDegrees > 292 and headingDegrees < 338)
  {
         
     
    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 7);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 7);
     }
    
    Serial.print(" Noroeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    display.println(" Coordenadas");
    display.println("");
    display.print("La:");
    display.println(float(latitude) / 100000, 7);
    display.print("Lo:"); 
    display.println(float(longitude) / 100000, 7);
    display.println("");
    display.print("Noroeste: ");
    display.print(headingDegrees); 
    display.display();
    display.clearDisplay();//limpa o display
   
  }
    delay (500);
  }
}
