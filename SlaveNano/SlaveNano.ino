
// Projeto de estudos - Marcio Winter 


//______________________________________ BIBLIOTECAS __________
#include <Wire.h>
#include <Thermistor.h>


//______________________________________  DEFINICOES ____________


#define meuendereco 0x100

#define botao_2 2
#define botao_3 3
#define botao_4 4
#define botao_5 5

#define led_7 7

Thermistor temp(1);     //pino analogico para conectar o  termistor


//______________________________________  Variaveis _____________

int temperatura = 0;
unsigned long anterior_Millis = 0;
unsigned long atual_Millis = 0;


//______________________________________  SETUP    _____________

void setup() {
  Wire.begin(meuendereco);   // endereço i2c do slave
  Wire.onReceive(recebeEventos);   //  registra evento enviado pelo master
  Wire.onRequest(enviaEventos);    //  envia evento requisitado pelo master

  Serial.begin(9600);

  pinMode(botao_2, INPUT_PULLUP);
  pinMode(botao_3, INPUT_PULLUP);
  pinMode(botao_4, INPUT_PULLUP);
  pinMode(botao_5, INPUT_PULLUP);

  pinMode(led_7, OUTPUT);

}


//______________________________________  LOOP    _____________

void loop() {

  


  unsigned long atual_Millis = millis();
  if (atual_Millis - anterior_Millis > 200)
  {
    
    lerTemperatura();
    Serial.println(temperatura);
    anterior_Millis = atual_Millis;
  }
    



}




//______________________________________  FUNÇÕES      _____________


// Recebe os comandos do mestre.
void recebeEventos(int numBytes)
{
  if (Wire.available())
  {
    char valor = Wire.read();
    Serial.println("DADO RECEBIDO");
    if (valor == 0)
    {
      digitalWrite(led_7, LOW);
      Serial.println("Led 7 DESLIGADO");
    }
    else if (valor == 1)
    {
      digitalWrite(led_7, HIGH);
      Serial.println("Led 7 LIGADO");
    }
    else
    {
      Serial.println("Dados Desconhecidos");
    }
  }
}


// Envia uma mensagem ao mestre.
void enviaEventos()
{
  Wire.write(temperatura);
}


void lerTemperatura() {

    float soma = 0;
    float valor = 0;
    for(int i =0; i<50; i++)
    {
    soma += temp.getTemp();    //o temp.getTemp() pega a temperatura do sensor e soma com a proxima temperatura até ter 50 registro 
    };
    valor = soma/50;
    temperatura = valor;

}

