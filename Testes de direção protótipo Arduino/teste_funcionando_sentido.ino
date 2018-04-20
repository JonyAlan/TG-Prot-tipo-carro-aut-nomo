#include <AFMotor.h> // Importa a biblioteca do controle de motor
#include <Wire.h>
#include <HMC5883L.h>

#define TrigPin 12 // pino do sensor ultra sonico
#define EcoPin 13 // pino do sensor ultra sonico

HMC5883L compass;

  AF_DCMotor motor1(3,MOTOR12_64KHZ); // frecuencia dos motores
  AF_DCMotor motor2(4,MOTOR12_64KHZ); //


  void setup() {
  
  Serial.begin(9600); // iniciamos a comunicação serial 
 
  pinMode(TrigPin, OUTPUT); // Pino para enviar as ondas sonoras)

  pinMode(EcoPin, INPUT); // Pino que recebe as ondas sonoras)  
  
   // Initialize Initialize HMC5883L
  Serial.println("Initialize HMC5883L");
  while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
  }

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
    
    Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
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

  
  long duracao, distancia; // Creamos 2 variables de tamaño extendido para almacenar numeros
  digitalWrite(TrigPin, LOW); // Enviamos a bajo el Pin de Trigger
  delayMicroseconds(2); // Un delays es requerido para que la operacion del sensor se complete
  digitalWrite(TrigPin, HIGH); // Enviamos a alto el Pin de Trigger
  delayMicroseconds(10); // Mantenemos en alto el Pin de Trigger por 10 us esto es necesario
  digitalWrite(TrigPin, LOW); // Enviamos a bajo el Pin de Trigger
  duracao = pulseIn(EcoPin, HIGH); // Calculamos la duracion del Pulso
  distancia = (duracao/2) / 29.1; // Convertimos la distancia en centimetros (velocidad Sonido 340m/s o 29.1 us x cm)

  if (headingDegrees > 337 and headingDegrees < 361 || headingDegrees >= 0 and headingDegrees < 23 )
  {
    Serial.print(" Norte = ");
    Serial.print(headingDegrees);
    Serial.print("Graus");
    Serial.println();
    
    motor1.setSpeed(205); // Establecemos la velocidad de los motores, entre 0-255
    motor2.setSpeed(205);
    
    if (distancia < 30)  {  // distancia for menor que 30 cm
        
          motor1.run(FORWARD);
          motor2.run (BACKWARD); // Giro en sentido inverso el motor2 - motor de la izquierda
 
          delay (500); //tempo de giro para a esquerda
          }
  
      else {
        delay (10); // Estabiliza os motores
        motor1.run(FORWARD); 
        motor2.run(FORWARD);  
        
          }
    
  }  
  
   if (headingDegrees > 22 and headingDegrees < 68)
  {
    Serial.print(" Nordeste = ");
    Serial.print(headingDegrees);
    Serial.print("Graus");
    Serial.println();
  } 
  
  if (headingDegrees > 67 and headingDegrees < 113)
  {
    Serial.print(" Leste = ");
    Serial.print(headingDegrees);
    Serial.print(" Graus");
    Serial.println();
  } 
  if (headingDegrees > 112 and headingDegrees < 157)
  {
    Serial.print(" Sudeste = ");
    Serial.print(headingDegrees);
    Serial.print(" Graus");
    Serial.println();
  } 
  if (headingDegrees > 156 and headingDegrees < 203)
  {
    Serial.print(" Sul = ");
    Serial.print(headingDegrees);
    Serial.print(" Graus");
    Serial.println();
  }
  
  if (headingDegrees > 202 and headingDegrees < 248)
  {
    Serial.print(" Sudoeste = ");
    Serial.print(headingDegrees);
    Serial.print(" Graus");
    Serial.println();
  }
  if (headingDegrees > 247 and headingDegrees < 338)
  {
    Serial.print(" Sudoeste = ");
    Serial.print(headingDegrees);
    Serial.print(" Graus");
    Serial.println();
  }
        
  delay(500);
 
}

