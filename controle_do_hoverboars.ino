int motores = 6; // motor pwm
int velocidade = 122;
char direcao = 'F';
 
void setup() {
  Serial.begin(9600);    //configura comunicação serial com 9600 bps
  pinMode(motores,OUTPUT);   //configura como saída
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
          velocidade = 122;
          direcao = 'F';
        break;
        
        case 'R':            
          velocidade = 122;
          direcao = 'R';
        break;
      }
   }
   if(strcmp(direcao,'F') == 0){
     if(velocidade > 121 && velocidade < 141) {
       analogWrite(motores, velocidade);
     }
     if(velocidade > 141){
       velocidade = 140;
     }
     if(velocidade < 121){
       velocidade = 122;
     }
   }else if(strcmp(direcao,'R') == 0){
     if(velocidade > 78 && velocidade < 120){
       analogWrite(motores, velocidade);
     }
     if(velocidade > 119){
       velocidade = 119;
     }
     if(velocidade < 79){
       velocidade = 79;
     }
     
   }
      
}  
