
#include "DHT.h"  // BIBLIOTECA SENSOR TEMP
#include <Wire.h> //BIBLIOTECA RFID
#include <SPI.h> //BIBLIOTECA RFID
#include <MFRC522.h> //IBLIOTECA RFID
#define SS_PIN 10 //PINO SDA RFID
#define RST_PIN 9 //PINO DE RESET RFID
MFRC522 rfid(SS_PIN, RST_PIN); //PASSAGEM DE PARÂMETROS REFERENTE AOS PINOS RFID
const int pinoLedVerde = 3; //PINO DIGITAL REFERENTE AO LED VERDE RFID
const int pinoLedVermelho = 2; //PINO DIGITAL REFERENTE AO LED VERMELHO RFID
#define DHTPIN A1 // pino DHT
#define DHTTYPE DHT11 
int pino_d = 2; //Pino sensor de chuva
int pino_a = A5; //Pino sensor de chuva
int val_d = 0; //Armazena o valor lido do sensor DE CHUVA pino digital
int val_a = 0; //Armazena o valor lido do sensor DE CHUVA pino analogico
int mot_chuv = 7;
int mot_port = 9;
void setup()
{
  pinMode(pino_d, INPUT);
  pinMode(pino_a, INPUT);
  pinMode(mot_chuva, OUTPUT);
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  SPI.begin(); //INICIALIZA O BARRAMENTO SPI
  rfid.PCD_Init(); //INICIALIZA MFRC522
  pinMode(mot_port, OUTPUT); //DEFINE O PINO COMO SAÍDA da Porta
  digitalWrite(mot_port, LOW); //LED INICIA DESLIGADO
  Serial.begin(9600);
}

void loop()
{
  sens_chuva();
  sens_temp();
  rfid();
}

void sens_chuva(){
  val_d = digitalRead(pino_d);
  val_a = analogRead(pino_a);
  Serial.print("Valor digital : ");
  Serial.print(val_d);
  Serial.print(" - Valor analogico : ");
  Serial.println(val_a);
  if (val_a > 0 && val_a <900){
    digitalWrite(mot_chuva, HIGH);}
  delay(1000);
  }
 void sens_temp(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Algum problema DHT");
  } 
  else
  {
   /* Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
    delay(1000);
    */
    if (
  }
}
 }
 void rfid(){
   if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) //VERIFICA SE O CARTÃO PRESENTE NO LEITOR É DIFERENTE DO ÚLTIMO CARTÃO LIDO. CASO NÃO SEJA, FAZ
    return; //RETORNA PARA LER NOVAMENTE
 
  /***INICIO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
  String strID = ""; 
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
/***FIM DO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
 
  //O ENDEREÇO "27:41:AA:AB" DEVERÁ SER ALTERADO PARA O ENDEREÇO DA SUA TAG RFID QUE CAPTUROU ANTERIORMENTE
  if (strID.indexOf("17:07:83:B5") >= 0) { //SE O ENDEREÇO DA TAG LIDA FOR IGUAL AO ENDEREÇO INFORMADO, FAZ
    digitalWrite(pinoLedVerde, HIGH); //LIGA O LED VERDE
    delay(3000); //INTERVALO DE 4 SEGUNDOS
    digitalWrite(pinoLedVerde, LOW); //DESLIGA O LED VERDE
  }else{ //SENÃO, FAZ (CASO A TAG LIDA NÃO SEJÁ VÁLIDA)
    digitalWrite(pinoLedVermelho, HIGH); //LIGA O LED VERMELHO
    delay(3000); ////INTERVALO DE 6 SEGUNDOS
    digitalWrite(pinoLedVermelho, LOW); //DESLIGA O LED VERDE
  }
 
  rfid.PICC_HaltA(); //PARADA DA LEITURA DO CARTÃO
  rfid.PCD_StopCrypto1(); //PARADA DA CRIPTOGRAFIA NO PCD
  }
 }
