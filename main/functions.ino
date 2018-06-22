#include "common.h"

void initRfid(void) {
  SPI.begin();       
  mfrc522.PCD_Init(); 
}

void initSerial(void){
  Serial.begin(115200); 
  mySerial.begin(115200);
}

//initColor
//Inicializes the base at the white color
void initColor(void){
  digitalWrite(blueLight, 0);
  digitalWrite(redLight, 0);
  digitalWrite(whiteLight, 1);
}
//offColor
//Switches off all the leds from the base
void offColor(void){
  digitalWrite(blueLight, 0);
  digitalWrite(redLight, 0);
  digitalWrite(whiteLight, 0);
}
//white()
//Switches on the white color at the base
void white(void){
  digitalWrite(whiteLight, 1);
}
//red()
//Switches on the red color at the base
void red(void){
  digitalWrite(redLight, 1);
}
//blue()
//Switches on the blue color at the base
void blue(void){
  digitalWrite(blueLight, 1);
}

//Cuenta si hemos estado el timepo necesario en la base
//como para considerar que ha sido capturada
bool contador(void)
{
  
  bool presence = true;
  int i=0;

  int wait= TCAPTURA*1000/ACCURACY;      
   
  while((i<wait)&&(presence == true))
  {
    if(isDron()==false)
    {
      presence= false;
    }
    i += 1;
    //#Serial.print(i);
  }
  
  return(presence);
  
}

//isDron: Cuenta por x milisegundos si hay un dron
//        en la base
bool isDron()
{
  bool presence = false;
  unsigned long elap, act;
  unsigned long ref = millis();

  elap=0.0;
  while(elap<ACCURACY)
  {
    if(rfidDetect()!= ""){
      presence=true;
    }
    act=millis();
    elap=act-ref;
  }
  return(presence);
}

//rfidDetect:
//Indica si se ha detectado una dron o no
String rfidDetect(void){
  String Id = "";
  int  NFC_id =0;
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent())
    {  
    //Seleccionamos una tarjeta
    if ( mfrc522.PICC_ReadCardSerial()) 
    {
      //var=true;
      // Enviamos serialemente su UID
      //Serial.print("Card UID:");
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
        //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        //Serial.print(mfrc522.uid.uidByte[i]); 
          
      } 
      //Serial.println();
      // Terminamos la lectura de la tarjeta  actual
      // mfrc522.PICC_HaltA();  
        
        String valA=String((mfrc522.uid.uidByte[0]),HEX);
        String valB=String((mfrc522.uid.uidByte[1]),HEX);
        String valC=String((mfrc522.uid.uidByte[2]),HEX);
        String valD=String((mfrc522.uid.uidByte[3]),HEX);
        Id=valA+valB+valC+valD;       
       
        //Serial.print("Esto es lo que devolvemos del la func del reasd: ");
        //Serial.println(Id);
      }    
    } 
  return Id;
}

String test(void){
  static char DronID[10] = "aaaaaaaaaa";
  String Id = String(DronID);
  return(Id);
}

void SetDronID(String(IdDron))
{
  
}

void ReadDronsID()
{

}
