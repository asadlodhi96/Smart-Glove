
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

/* SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
*/

#define rxPin   5  // Serial input (connects to Emic 2's SOUT pin)
#define txPin   6  // Serial output (connects to Emic 2's SIN pin)
const int chipSelect = 4;

File _myFile;
int count = 0;

int a = 1; int b = 0; int c = 0; int d = 0; int e = 0 ; int f = 0; bool flag = true;

SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);

void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(4, OUTPUT);

  Serial.begin(9600);
  Serial.setTimeout(5000);
  emicSerial.begin(9600);
  Serial.println("Serials Initialization Done");
  emicSerial.print('\n');             // Send a CR in case the system is already up
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (f == 1) {
    Serial.println("Ready To Receive Data, if you want to send data press send 'y' else ignore message .. ");
    if (Serial.available())
    {
      initializeSdCard();
      checkFileExist();
      receiveData_Parse();
      delay(1000);
    }
  }

  else {
    if (flag == true) {
      initializeSdCard();
      flag = false;
    }
    // Speak some text
    if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0))
    {
      String mes = getdata(0);
      sendToEmic(mes);
    }

    else if ((a == 1) && (b == 0) && (c == 0) && (d == 0) && (e == 0))
    {
      String mes = getdata(1);
      sendToEmic(mes);
    }

    else if ((a == 0) && (b == 1) && (c == 0) && (d == 0) && (e == 0))
    {
      String mes = getdata(2);
      sendToEmic(mes);
    }

    else if ((a == 0) && (b == 0) && (c == 1) && (d == 0) && (e == 0))
    {
      String mes = getdata(3);
      sendToEmic(mes);
    }

    else if ((a == 0) && (b == 0) && (c == 0) && (d == 1) && (e == 0))
    {
      String mes = getdata(4);
      sendToEmic(mes);
    }

    else if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 1))
    {
      String mes = getdata(5);
      sendToEmic(mes);
    }

    else if ((a == 1) && (b == 1) && (c == 0) && (d == 0) && (e == 0))
    {
      String mes = getdata(6);
      sendToEmic(mes);
    }

    else if ((a == 1) && (b == 0) && (c == 1) && (d == 0) && (e == 0))
    {
      String mes = getdata(7);
      sendToEmic(mes);
    }

    else if ((a == 1) && (b == 0) && (c == 0) && (d == 1) && (e == 0))
    {
      String mes = getdata(8);
      sendToEmic(mes);
    }

    else if ((a == 1) && (b == 0) && (c == 0) && (d == 0) && (e == 1))
    {
      String mes = getdata(9);
      sendToEmic(mes);
    }

    else if ((a == 0) && (b == 1) && (c == 1) && (d == 0) && (e == 0))
    {
      String mes = getdata(10);
      sendToEmic(mes);
    }

    else if ((a == 0) && (b == 1) && (c == 0) && (d == 1) && (e == 0))
    {
      String mes = getdata(11);
      sendToEmic(mes);
    }

    else if ((a == 0) && (b == 1) && (c == 0) && (d == 0) && (e == 1))
    {
      String mes = getdata(12);
      sendToEmic(mes);
    }

    else if ((a == 0) && (b == 0) && (c == 1) && (d == 1) && (e == 0))
    {
      String mes = getdata(13);
      emicSerial.println(mes);
      delay(5000);
    }

    else if ((a == 0) && (b == 0) && (c == 1) && (d == 0) && (e == 1))
    {
      String mes = getdata(14);
      sendToEmic(mes);
    }

    else if ((a == 0) && (b == 0) && (c == 0) && (d == 1) && (e == 1))
    {
      String mes = getdata(15);
      sendToEmic(mes);
    }

    else if ((a == 1) && (b == 1) && (c == 1) && (d == 0) && (e == 0))
    {
      String mes = getdata(16);
      sendToEmic(mes);
    }

    else if ((a == 1) && (b == 1) && (c == 0) && (d == 1) && (e == 0))
    {
      String mes = getdata(17);
      sendToEmic(mes);
    }

    else if ((a == 1) && (b == 1) && (c == 0) && (d == 0) && (e == 1))
    {
      String mes = getdata(18);
      sendToEmic(mes);
    }

    else if ((a == 1) && (b == 1) && (c == 1) && (d == 1) && (e == 0))
    {
      String mes = getdata(19);
      sendToEmic(mes);
    }
  }
}

void sendToEmic(String mes){
    emicSerial.println(mes);
    delay(5000);
}


// re-open the file for reading:
String getdata(int lineNumber)
{
  int count = 0;
  Serial.end();
  delay(20);
  Serial.begin(9600);
  Serial.setTimeout(2000);
  File  myFile = SD.open("test.txt");
  
  if (myFile) {
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      //Serial.write(myFile.read());
      if (count != lineNumber) {
        String data = myFile.readStringUntil('.');
        count++;
      }
      else
      {
        String data = myFile.readStringUntil('.');
        // close the file:
        myFile.close();
        return data;
        break;
      }
    }
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  Serial.end();
}



void initializeSdCard() {
  // Open serial communications and wait for port to open:
  Serial.end();
  delay(20);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void checkFileExist()
{
  if (SD.exists("test.txt"))
  {
    SD.remove("test.txt");
    Serial.println("test.txt File removed Successfully");
    _myFile = SD.open("test.txt", FILE_WRITE);
  }
  else
  {
    Serial.println("No such file found .. ");
    _myFile = SD.open("test.txt", FILE_WRITE);
  }
}

void receiveData_Parse() {

  String inpString;
  int index = 0;

  while (index < 20) {
    inpString = Serial.readStringUntil('.');
    writeToFile(inpString);
    index++;
  }
  closeFile();
  index = 0;
  inpString = "";
}

// if the file opened okay, write to it:
void writeToFile(String dataToWrite)
{
  if (_myFile) {
    _myFile.println('S' + dataToWrite + '.');
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
// close the file:
void closeFile()
{
  _myFile.close();
  if (!(_myFile))
    Serial.println("done Data Write to file.");
  else
    Serial.println("Data not Write");
  Serial.end();
}
