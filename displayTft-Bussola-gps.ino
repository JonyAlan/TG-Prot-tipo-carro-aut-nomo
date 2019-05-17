#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <HMC5883L.h>
#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

#define TFT_CS     10 // azul
#define TFT_RST    8  // verde
#define TFT_DC     9 // azul

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST); // Instância do objeto tipo Adafruit_ST7735 que recebe como argumentos os pinos de controle
SoftwareSerial serial1(5, 6); // RX Azul, TX Verde
TinyGPS gps1;
HMC5883L compass;

float sentido;
float distancia_entre;
int i; //Variável para contagem
float headingDegrees;
float headingDegreesAnt;
float precisao; //Variável parar o melhorar a precisao do valor aferido
    
String sentidotxt = "";

void setup() {
  serial1.begin(9600);
  Serial.begin(9600);
  //Define as configurações iniciais do display
  tft.setCursor(15,15); // Move o cursor para a coluna 30 na linha 0 
  tft.initR(INITR_BLACKTAB); // Inicializa a tela com um fundo preto
  tft.setTextSize(2); // Seta o tamanho da fonte de texto para o tamanho 2
  tft.fillScreen(ST7735_BLACK); // Preenche a tela com a cor preta
  tft.setTextColor(ST7735_BLUE); // Seta a cor do texto para Azul
  tft.println("Fatec-SO");//Escreve no display
  tft.println(" ");//Escreve no display
  tft.setTextColor(ST7735_RED); 
  tft.println("Loading...");
;
  
  //tft.drawTriangle(20, 120, 120, 120, 160, 120, ST7735_BLUE);

  delay(4000);
  tft.setTextSize(1); // Seta o tamanho da fonte de texto para o tamanho 2
  tft.fillScreen(ST7735_BLACK); // Preenche a tela com a cor preta
    
  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_30HZ);
  compass.setSamples(HMC5883L_SAMPLES_8);
  compass.setOffset(0, 0);
}

void loop(){
  bool recebido = false;
  static unsigned long delayPrint;
  // Correct for heading < 0deg and heading > 360deg
precisao = 0;
for(i = 0; i < 2 ; i++){ //Faz a leitura 50 e armazenar a somatória
  Vector norm = compass.readNormalize();
  float heading = atan2(norm.YAxis, norm.XAxis);
  
  // Insere a declinação magnética da localidade formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;
  //Converte o valor aferido para angulo
  if (heading < 0){
    heading += 2 * PI;
  }
  if (heading > 2 * PI){
    heading -= 2 * PI;
  }
  // Convert to degrees
  headingDegrees = heading * 180/M_PI;
  precisao = precisao + headingDegrees;
  }
  headingDegrees = precisao / 2; //Pega a somatória e tira a média dos valores aferidos
  
  if(headingDegrees > 337 and headingDegrees < 361 || headingDegrees >= 0 and headingDegrees < 23 ){
    sentidotxt =  "Norte: ";}
  if(headingDegrees > 22 and headingDegrees < 68){
    sentidotxt = "Nordeste: ";}
  if (headingDegrees > 67 and headingDegrees < 113){
    sentidotxt = "Leste: ";}
  if(headingDegrees > 112 and headingDegrees < 157){
    sentidotxt ="Sudeste: ";} 
  if(headingDegrees > 156 and headingDegrees < 203){
    sentidotxt = "Sul: ";}
  if(headingDegrees > 202 and headingDegrees < 248){
    sentidotxt = "Sudoeste: ";}
  if(headingDegrees > 247 and headingDegrees < 293){
    sentidotxt = "Oeste: ";}
  if(headingDegrees > 292 and headingDegrees < 338){
    sentidotxt = "Noroeste: ";} 
  while (serial1.available()) {
    char cIn = serial1.read();
    recebido = (gps1.encode(cIn) || recebido); 
  }
  
  Serial.print(sentidotxt);
  Serial.print(headingDegrees);
  Serial.println(" Graus");
  tft.setCursor(0,15); // Move o cursor para a coluna 30 na linha 0
  tft.setTextColor(ST7735_BLUE);
  tft.fillRect(0,0, 50, 28, ST7735_BLACK);
  tft.print(" ");
  tft.println(headingDegrees);
  tft.fillTriangle(53,25, 64, 7, 75, 25, ST7735_BLUE);
  if (recebido){    
    float latitude, longitude;
    gps1.f_get_position(&latitude, &longitude); 
   
    if(latitude != TinyGPS::GPS_INVALID_F_ANGLE and longitude != TinyGPS::GPS_INVALID_F_ANGLE){
      sentido = gps1.course_to(latitude, longitude,-23.480502 , -47.425667);
      distancia_entre = gps1.distance_between(latitude, longitude, -23.480502 , -47.425667);
      Serial.print("SENTIDO = ");
      Serial.println(sentido);
      Serial.print("Distancia = ");
      Serial.println(distancia_entre);
      Serial.print("Longitude: ");
      Serial.println(longitude, 6);
      Serial.print("Latitude: ");
      Serial.println(latitude, 6);
      Serial.print(sentidotxt);
      Serial.print(headingDegrees);
      Serial.println(" Graus");
           //satelites 
      unsigned short satelites;  
      satelites = gps1.satellites();  
      if (satelites != TinyGPS::GPS_INVALID_SATELLITES) {
        Serial.print("Satelites: ");
        Serial.println(satelites);
      }
        Serial.println("");  
    }
    //Configuração do display 
    
    tft.setTextColor(ST7735_RED);
    tft.setCursor(28,40); // Move o cursor para a coluna 30 na linha 0 
    //Mensagens enviadas ao display
    tft.println(" COORDENADAS");
    //A função drawRect é responsável por desenhar um retângulo na tela, passando um ponto de origem, sua largura e altura.
    tft.fillRect(0, 60, 128, 100, ST7735_BLACK);
    tft.println("");
    tft.println("");
    tft.print(" La: ");
    tft.println(latitude, 6);
    tft.println("");
    tft.print(" Lo: "); 
    tft.println(longitude, 6);
    tft.println("");
    tft.print(" Sentido = ");
    tft.println(sentido);
    tft.println("");
    tft.print(" Distancia = ");
    tft.println(distancia_entre);
  } 
}
