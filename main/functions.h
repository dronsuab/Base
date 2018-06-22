
#define RST_PIN  9    //Reset RFID
#define SS_PIN  10   //SDA RFID


const int whiteLight = 2;
const int redLight = 3;
const int blueLight = 4;
unsigned long time;

MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
SoftwareSerial mySerial(0, 1); // 0->RX, 1->TX

void initRfid(void);
void initSerial(void);
void initColor(void);
void offColor(void);
void white(void);
void red(void);
void blue(void);
bool contador(void);
String rfidDetect(void);
String test(void);
