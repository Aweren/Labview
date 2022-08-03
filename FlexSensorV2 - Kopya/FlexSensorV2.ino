#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

int X_PIN = 33;                                                                          
int Y_PIN = 39;                                                                    
                                                                           
int X_PIN_Zero, Y_PIN_Zero;                                                                       
int X_PIN_Value, Y_PIN_Value;     

const int FLEX_PIN = 32; //27
const int FLEX_PIN1 = 27; 
const int FLEX_PIN2 = 35; //
const int FLEX_PIN3 = 34; // 
const int FLEX_PIN4 = 26; // pini bt de hata veriyor  BT OLARAK ÇALIŞMA


  bool trgButton;
  bool grab;

  int trgButton_time_true = 0;
  int trgButton_time_false = 0;

  
  int grab_time_true = 0;
  int grab_time_false = 0;

  int flexADC_min = 4096;
  int flexADC_max = 0;
  
  int flexADC_min1 = 4096;
  int flexADC_max1 = 0;
  
  int flexADC_min2 = 4096;
  int flexADC_max2 = 0;
  
  int flexADC_min3 = 4096;
  int flexADC_max3 = 0;
  
  int flexADC_min4 = 4096;
  int flexADC_max4 = 0;
  
  int bos=0;
void setup() 
{
  Serial.begin(115200);
  SerialBT.begin("lucidgloves-rigth"); //Bluetooth device name
  pinMode(FLEX_PIN, INPUT);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
  pinMode(FLEX_PIN4, INPUT);  

  
  pinMode(X_PIN, INPUT);                                                                        
  pinMode(X_PIN, INPUT);                                                                                                                                       
  delay(100);                                                                               
  X_PIN_Zero = analogRead(X_PIN);                                                              
  Y_PIN_Zero = analogRead(Y_PIN);  
     
}

void loop() 
{
  int flexADC = analogRead(FLEX_PIN);
  int flexADC1 = analogRead(FLEX_PIN1);
  int flexADC2 = analogRead(FLEX_PIN2);
  int flexADC3 = analogRead(FLEX_PIN3);
  int flexADC4 = analogRead(FLEX_PIN4);

  X_PIN_Value = analogRead(X_PIN) - X_PIN_Zero;                                                   
  Y_PIN_Value = analogRead(Y_PIN) - Y_PIN_Zero;                                                

  X_PIN_Value = X_PIN_Value + 2048;
  Y_PIN_Value = Y_PIN_Value + 2048;

if (X_PIN_Value < 2300 && X_PIN_Value > 1800) X_PIN_Value = 2048;
if (Y_PIN_Value < 2300 && Y_PIN_Value > 1800) Y_PIN_Value = 2048;


  flexADC = 4096 - flexADC;
  if (flexADC > flexADC_max) flexADC_max = flexADC;
  if (flexADC < flexADC_min) flexADC_min = flexADC;
  
  flexADC = map(flexADC, flexADC_min, flexADC_max, 0, 4096);

  if (flexADC1 > flexADC_max1) flexADC_max1 = flexADC1;
  if (flexADC1 < flexADC_min1) flexADC_min1 = flexADC1;
  
  flexADC1 = map(flexADC1, flexADC_min1, flexADC_max1, 4096, 0);

  if (flexADC2 > flexADC_max2) flexADC_max2 = flexADC2;
  if (flexADC2 < flexADC_min2) flexADC_min2 = flexADC2;
  
  flexADC2 = map(flexADC2, flexADC_min2, flexADC_max2, 0, 4096);
  
  if (flexADC3 > flexADC_max3) flexADC_max3 = flexADC3;
  if (flexADC3 < flexADC_min3) flexADC_min3 = flexADC3;
  
  flexADC3 = map(flexADC3, flexADC_min3, flexADC_max3, 4096, 0);  

  if (flexADC4 > flexADC_max4) flexADC_max4 = flexADC4;
  if (flexADC4 < flexADC_min4) flexADC_min4 = flexADC4;
  
  flexADC4 = map(flexADC4, flexADC_min4, flexADC_max4, 4096, 0); // Serial Port için bunu kullan

///////////////////////////////////////////////
  if(flexADC1 > 2750){
  trgButton_time_true++;
  trgButton_time_false = 0;
  if(trgButton_time_true > 15) {
  trgButton = true;
 }
}


if(flexADC1 < 2750){
  trgButton_time_true = 0;
  trgButton_time_false++;
   if(trgButton_time_false > 15) {
  trgButton = false;
 }
}

///////////////////////////////////////////////

  if(flexADC2 > 2750 && flexADC3 > 2750 && flexADC4 > 2750 ){
  grab_time_true++;
  grab_time_false = 0;
  if(grab_time_true> 15) {
  grab = true;
 }
}


if(flexADC2 < 2750 && flexADC3 < 2750 && flexADC4 < 2750 ){
  grab_time_true = 0;
  grab_time_false++;
   if(grab_time_false > 15) {
  grab = false;
 }
}


if(grab == true && trgButton == true  ) SerialBT.println((String)"A"+flexADC+"B"+flexADC1+"C"+flexADC2+"D"+flexADC3+"E"+flexADC4+"F"+X_PIN_Value+"G"+Y_PIN_Value+"I"+"L");
if(grab == true && trgButton == false  ) SerialBT.println((String)"A"+flexADC+"B"+flexADC1+"C"+flexADC2+"D"+flexADC3+"E"+flexADC4+"F"+X_PIN_Value+"G"+Y_PIN_Value+"L");
if(grab == false && trgButton == true  ) SerialBT.println((String)"A"+flexADC+"B"+flexADC1+"C"+flexADC2+"D"+flexADC3+"E"+flexADC4+"F"+X_PIN_Value+"G"+Y_PIN_Value+"I");
if(grab == false && trgButton == false  ) SerialBT.println((String)"A"+flexADC+"B"+flexADC1+"C"+flexADC2+"D"+flexADC3+"E"+flexADC4+"F"+X_PIN_Value+"G"+Y_PIN_Value);

 delay(10);
}
