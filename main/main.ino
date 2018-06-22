#include "common.h"
#include "Players.h"
#include "Bases.h"
#include "functions.h"


#define TCAPTURA 3   //TIEMPO EN SEGUNDOS PARA CAPTURAR UNA BASE
#define ACCURACY 1000  //Accuracy del RFID
#define CMDBUFFER_SIZE 50

//Initalizes the Rfid, serial and the color at the base
void setup(){
  initRfid();
  initSerial();
  initColor();
  //time = millis();
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);

  //#Serial.println("Setup Done!");
}


/*****************************************************MAIN PROGRAM*************************************************************************/
void loop() {
  unsigned long ReferenceTime, ElapsedTime,PresentTime;
  bool detected= false;
  bool capturado = false;
  static char sendBuff[CMDBUFFER_SIZE] = "";
  String DronCatching = "";
  String DronCatch = "";
  if((DronCatching=rfidDetect())!= "")
  {
    if(contador() == true)
    {
      //Serial.println("Capturado");
      capturado=true;
    }else{
      //Serial.print("NO CAPTURADO");
      //Serial.println();
    }
  }

  if(capturado==true)
  {
    //Serial.println("****DETECTADO!****");
    //Serial.println(DronCatching);
   // Serial.println("******************");
   /****************************************BORRAR 2a Funcion dentro de los asteriscos********************************************/
    int j=0;
    int det = 0;
    for (j=0;j<NUMDRONES;j++)
    {
      //Serial.print("DRIONES[i]: ");
      //Serial.println(DRONES[j]);
      //Serial.print("DronID: ");
      //Serial.println(DronCatching);
      if(DRONES[j] == DronCatching){                                //COMPROBAMOS SI EL DRON EXISTE (MITIGAMOS POSIBLE RUIDO)
        det=j;
        DronCatch=DronCatching;
        
      }
    }
                                                       
    char str[1];                                                    //Simamos uno para poder printarlo correctamente (DRON[0] realmente es DRON1)
    sprintf(str, "%d",(det+1));
    //Serial.print("El drone es:");
    //Serial.println(DronCatch);

/*************************************************************************************************************************************/
    
    strncat(sendBuff,"CATCH,",strlen("CATCH,"));
    strncat(sendBuff, BASEID,strlen(BASEID));
    strncat(sendBuff,",drone,",strlen(",drone"));
    strncat(sendBuff,str,strlen(str));
    strncat(sendBuff,"/",strlen("/"));
    Serial.print(sendBuff);
    //mySerial.print(sendBuff);
    memset(sendBuff, 0, sizeof(sendBuff));
  }
}
/****************************************************************************CALLBACK @ SERIAL EVENT******************************************************************************/
void serialEvent()
{
 static char cmdBuffer[CMDBUFFER_SIZE] = "";
 static char BaseToR[CMDBUFFER_SIZE] = "";
 static char color[CMDBUFFER_SIZE] = "";
 static char Message[CMDBUFFER_SIZE] = "";
 
 char c;
 int w[3];

   memset(cmdBuffer, 0, sizeof(cmdBuffer));
   memset(BaseToR, 0, sizeof(BaseToR));
   memset(color, 0, sizeof(color));
   memset(Message, 0, sizeof(Message));
   memset(w, 0, sizeof(w));
 
 while(Serial.available()) 
 {

   //Serial.println("1");
   //c = processCharInput(cmdBuffer, mySerial.read());
   c = processCharInput(cmdBuffer, Serial.read());
   //Serial.print(c);

   /*LECTURA DE MENSAJE, DEBE SEGUIR EL PROTOCOLO*/
   if (c == '/') 
   {
     //Mensaje entero  
     //Serial.print("Buffer Recibido desde el Server: ");
     //Serial.print(cmdBuffer); 
     //Serial.println("#END#");
     
     int f=0;
     int k=0;
     while (cmdBuffer[f]!= '/'){
      //#serial.print(cmdBuffer[f]);
      if(cmdBuffer[f] == ',')
      {
        w[k]=f;
        k++;
      }

      f++;
     }
     w[2]=f;
     //#serial.println();
     //#serial.print(w[0]);
     //#serial.print(" ");
     //#serial.print(w[1]);
     //#serial.print(" ");
     //#serial.print(w[2]);
     //#serial.println();

     /*GUARDAMOS LOS 3 CAMPOS DEL MENSAJE*/
     for(int i=0; i<w[0];i++){
      processCharInput(Message,cmdBuffer[i]);
     }
     for(int i=w[0]+1; i<w[1];i++){
      processCharInput(BaseToR,cmdBuffer[i]);
     }
     //#serial.println();
     for(int i=w[1]+1; i<w[2];i++){
      processCharInput(color,cmdBuffer[i]);
     }
     
     //#serial.print("Base que recive el mensaje: ");
     //#serial.println(BaseToR); 

     //#serial.print("El color es:_");
     //#serial.print(color); 
     //#serial.print("_");

     String colorS = String(color);
     String BaseToRS = String(BaseToR);
     String MSG =String();
     if (String(BASEID).equals(BaseToRS))
     {
      //mySerial.println("color");
      //mySerial.println(color);
      ////////////////////////*AQUI, hacer swich case en funcion del mensaje
        offColor();
        if(colorS.equals("blue")){
          blue();
        }else if(colorS.equals("red")){
          red();
        }else if(colorS.equals("blue")){
          blue();
        }else{
          white();
        }
      }
     memset(cmdBuffer, 0, sizeof(cmdBuffer));
     memset(BaseToR, 0, sizeof(BaseToR));
     memset(color, 0, sizeof(color));
     memset(w, 0, sizeof(w));
   }
 }
 delay(1);
}

char processCharInput(char* cmdBuffer, const char c)
{
    if (strlen(cmdBuffer) < CMDBUFFER_SIZE) 
   { 
     strncat(cmdBuffer, &c, 1);   //Add it to the buffer
   }
   else  
   {   
     return '\n';
   }
 return c;
}
