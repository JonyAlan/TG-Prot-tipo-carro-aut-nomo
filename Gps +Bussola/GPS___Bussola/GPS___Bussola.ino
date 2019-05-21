#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include "HMC5883L.h"

SoftwareSerial serial1(10,11); // RX, TX
TinyGPS gps1;
HMC5883L compass;

void setup() {
  
   serial1.begin(9600);
   Serial.begin(9600);
   
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
  bool recebido = false;

  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = gps1.encode(cIn);
      recebido = true;
        
      
  }


  if (recebido) {
     Serial.println("----------------------------------------");
     
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
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
    Serial.print(" Norte = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    
  }
  
   if (headingDegrees > 22 and headingDegrees < 68)
  {
 
    

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
    
    Serial.print(" Nordeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    
  } 
  
  if (headingDegrees > 67 and headingDegrees < 113)
  {
 
    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
    
    Serial.print(" Leste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    
  } 
  if (headingDegrees > 112 and headingDegrees < 157)
  {
 
    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
    
    Serial.print(" Sudeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
   
  } 
  if (headingDegrees > 156 and headingDegrees < 203)
  {

    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
    
    Serial.print(" Sul = ");
    Serial.print(headingDegrees);
    Serial.println("  Graus");
   
  }
  
  if (headingDegrees > 202 and headingDegrees < 248)
  {

    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
    
    Serial.print(" Sudoeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
    
  }
  if (headingDegrees > 247 and headingDegrees < 293)
  {

    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
    
    Serial.print(" Oeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");

  }
  
  if (headingDegrees > 292 and headingDegrees < 338)
  {
         
     
    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
    
    Serial.print(" Noroeste = ");
    Serial.print(headingDegrees);
    Serial.println(" Graus");
   
  }
    delay (1000);
  }
}
//Lembrete, esta versão esta desatualizada, 
//Nova lógica para obter a direão.
if(graus >= sentido -1 && graus <= sentido +1){
  servo(90);
}else if(graus < sentido -1 && graus < 180 ){
  servo(180);
} else if(graus > sentido + 1 && graus < 180){
  servo (0);
}else if(graus < sentido && graus > 180){
  servo(-1)
}else if(graus < sentido && graus < 180){
  servo(-2)
}


