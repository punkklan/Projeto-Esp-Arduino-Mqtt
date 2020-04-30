// Projeto de estudos - Marcio Winter 

#include <Wire.h>


#define enderecoNano 0x100    //  endereço pode ser de 0 a 255

#define tempo 1000


int estadoLed7 = 0;   



//________________________________________________________________________

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start Serial for output

}


//________________________________________________________


void loop()
{
  
  // Inicia a transmissão START e envia os comandos ao escravo.
  Wire.beginTransmission(enderecoNano);

  if (estadoLed7 == 1) {
    Wire.write(1);   
  }
  else if (estadoLed7 == 0) {
    Wire.write(0);   
  }
  else {
    Serial.println("Desconhecido");
  }
  
  // Fecha a transmissão STOP
  Wire.endTransmission();




 estadoLed7 = !estadoLed7;





  // Recebe do escravo de endereço 0x0A a mensagem de 16 bytes.
  Wire.requestFrom(enderecoNano, 16);
  while (Wire.available()) { 
    char mensagem = Wire.read(); 
    Serial.println(mensagem);
  } 
  
  
 delay(tempo);


}



