int motores = 6; // motores na saida pwm
int direcao = 5;
int velocidade = 128;
int lado = 116;
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
          velocidade = 126;
          sentido = 'F';
        break;
        
        case 'T':            
          sentido = 'T';
        break;

        case 'D':            
          lado = 210;
        break;

        case 'E':            
          lado = 0;
        break;

        case 'C':            
          lado = 116;
        break;
      }
   }
   if(strcmp(sentido,'F') == 0){
     if(velocidade > 127 && velocidade < 148) {
       analogWrite(motores, velocidade);
     }
     if(velocidade > 148){
       velocidade = 147;
     }
     if(velocidade < 127){
       velocidade = 128;
     }
   }else if(strcmp(sentido,'T') == 0){
       analogWrite(motores, 76);
       lado = 116 
   }
   analogWrite(direcao, lado);
   
      
}  
