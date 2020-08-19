//C=
int motores = 6; // motores na saida pwm
int direcao = 5;
int velocidade = 116;
int lado = 104;
char sentido = 'F';
 
void setup() {
  Serial.begin(9600);    //configura comunicação serial com 9600 bps
  pinMode(motores,OUTPUT);   //configura como saída
  pinMode(direcao,OUTPUT);   //configura como saída
}
 
void loop() {

   if(Serial.available()){
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

