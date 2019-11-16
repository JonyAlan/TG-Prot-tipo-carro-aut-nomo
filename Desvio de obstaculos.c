//C=
int motores = 6; // motores na saida pwm
int direcao = 5;
int velocidade = 116;
int lado = 104;
char sentido = 'F';

const int pingTrigger = 8;
const int Sensor_1 = 2;
const int Sensor_2 = 3;

void setup() {
  Serial.begin(9600);    //configura comunicação serial com 9600 bps
  pinMode(motores,OUTPUT);   //configura como saída
  pinMode(direcao,OUTPUT);   //configura como saída
  pinMode(pingTrigger, OUTPUT);
  pinMode(Sensor_1, INPUT);
  pinMode(Sensor_2, INPUT);
}
 
void loop() {


long duration, cm; // estabelecer variáveis ​​para a duração do ping

  // SENSOR 1
  digitalWrite(pingTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pingTrigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingTrigger, LOW);

  duration = pulseIn(Sensor_1, HIGH);

  //Converte o tempo em cm de distância
  cm = microsecondsToCentimeters(duration);
  
  if(cm < 100){
	lado = 70;
	delay(3000);
  }
 
  // SENSOR 2
  // PING))) é acionado por um pulso ALTO de 2 ou mais microssegundos.
  // Um pulso LOW curto antecipadamente para garantir um pulso HIGH limpo:
  digitalWrite(pingTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pingTrigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingTrigger, LOW);

 // O mesmo pino é usado para ler o sinal do PING))): a HIGH
  // pulso cuja duração é o tempo (em microssegundos) desde o envio
  // do ping para a recepção do eco de um objeto.
  duration = pulseIn(Sensor_2, HIGH);

  //Converte o tempo em cm de distânciae
  cm = microsecondsToCentimeters(duration);
 if(cm < 100){
	lado = 130;
	delay(3000);
 }

   if(cm > 100 and Serial.available()){
    switch(Serial.read()) //verifica qual caracter recebido
      {
        case '=':            
          velocidade = 121;
        break;
        case 'F':            
          velocidade = 116;
          sentido = 'F';
        break;
        case 'T':            
          sentido = 'T';
        break;
        case 'E':            
          lado = 130;
        break;
        case 'D':            
          lado = 70;
        break;
        case 'C':            
          lado = 104;
        break;
      }
   }
   
   if(strcmp(sentido,'F') == 0){
     if(velocidade > 114 && velocidade < 122) {
       analogWrite(motores, velocidade);
     }
     if(velocidade > 121){
       velocidade = 121;
     }
     if(velocidade < 115){
       velocidade = 116;
     }
   }else if(strcmp(sentido,'T') == 0){
       analogWrite(motores, 104);
       lado = 100 ;
   }
   analogWrite(direcao, lado);   
}  

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

