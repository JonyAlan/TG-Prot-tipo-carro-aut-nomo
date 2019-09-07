int motores = 6; // motores na saida pwm
int direcao = 5;
int velocidade = 115;
int lado = 105;
char sentido = 'F';
 
void setup() {
  Serial.begin(9600);    //configura comunicação serial com 9600 bps
  pinMode(motores,OUTPUT);   //configura como saída
  pinMode(direcao,OUTPUT);   //configura como saída
}
 
void loop() {

   if(Serial.available()){
    switch(Serial.read())      //verifica qual caracter recebido
      {
        case '=':            
          velocidade = velocidade + 2;
        break;

        case '-':            
          velocidade = velocidade - 2;
        break;
        
        case 'F':            
          velocidade = 115;
          sentido = 'F';
        break;
        
        case 'T':            
          sentido = 'T';
        break;

        case 'D':            
          lado = 150;
        break;

        case 'E':            
          lado = 50;
        break;

        case 'C':            
          lado = 105;
        break;
      }
   }
   if(strcmp(sentido,'F') == 0){
     if(velocidade > 114 && velocidade < 148) {
       analogWrite(motores, velocidade);
     }
     if(velocidade > 148){
       velocidade = 147;
     }
     if(velocidade < 114){
       velocidade = 115;
     }
   }else if(strcmp(sentido,'T') == 0){
       analogWrite(motores, 76);
       lado = 105 ;
   }
   analogWrite(direcao, lado);
   
      
}  
