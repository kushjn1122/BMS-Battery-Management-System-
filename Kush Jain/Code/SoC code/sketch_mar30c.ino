#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11); // RX | TX
double Vc = 0;
double Current = 0;
//double Q=0;
double voltage=0;
float Q[100];
double SOC;
int i=0,t=0;
float  V =0,q;
int C=0;
int n=1,f=0;
int state=0;
int flag=0;
void setup(){
Serial.begin(9600);
BTserial.begin(9600);
do{
  
SOC==0;
for(int i = 0; i < 1000; i++) {
int volt = analogRead(A1);// Voltage Sensor
V = (V + map(volt,0,1023, 0, 2500)); // (5 V / 1024 (Analog) = 0.0049) which converter Measured analog input voltage to 5 V Range
delay(1);
}
V /=100000;// divide by 100 to get the decimal values
//voltage -=0.15;
V=V-1.7;
//Serial.print("Voltage Sensed (V) = "); // shows the measured voltage
//Serial.println(V); // the ‘2’ after voltage allows you to display 2 digits after decimal point  if(V >= 3.3 && V < 3.452) // seg-1 

 if(V >= 3.3 && V < 3.452) // seg-1 
   {state=1;}
    
  else if(V >= 3.452 && V < 3.508) // seg-2
    {state=2;}
    
  else if(V >= 3.508 && V < 3.595) // seg-3
    {state=3;}
    
  else if(V >= 3.595 && V < 3.676) // seg-4
    {state=4;}
    
  else if(V >= 3.676 && V < 3.739) // seg-5
    {state=5;}
    
  else if(V >= 3.739 && V < 3.967) // seg-6
   {state=6;}
    
  else if(V >= 3.967 && V < 4.039) // seg
    {state=7;}
    
  else if(V >= 4.039 && V < 4.132) // 
    {state=8;}
    
switch (state)
{
 case 1:
    SOC = (26.55*(V)) - 88.6;
    flag==1;
    break;
case 2:
    SOC = (125*(V)) - 431.1;
        flag==1;
     break;
case 3:
  //if(V >= 3.508 && V < 3.595) // seg-3
    SOC = (149*(V)) - 516.1;
        flag==1;

        break;
case 4:
   //if(V >= 3.595 && V < 3.676) // seg-4
    SOC = (344*(V)) - 1225.0;
        break;
case 5:
   //if(V >= 3.676 && V < 3.739) // seg-5
    SOC = (229.5*(V)) - 800.9;
        flag==1;

        break;
case 6:
   //if(V >= 3.739 && V < 3.967) // seg-6
    SOC = (111.9*(V)) - 359.9;
        flag==1;

        break;
case 7:
   //if(V >= 3.967 && V < 4.039) // seg
    SOC = (104.8*(V)) - 332.0;
        flag==1;

        break;
case 8:
   //if(V >= 4.039 && V < 4.132) // 
    SOC = (90.61*(V)) - 274.7;//
        flag==1;

        break;
default:
SOC=0;
Serial.println("N/A");
    delay(1000);
}

}while(SOC<=0);

  //Serial.print("Intial SOC is: ");
  Serial.println(SOC);
  
  
}
void loop(){

// Voltage is Sensed 1000 Times for precision

   for(i=0;i<n+1;i++)
    {
   //Serial.print("Raw Value = "); // shows the measured voltage
//Serial.println(analogRead(A0));//Current Sensor
for(int i = 0; i < 1000; i++) {
Vc = (Vc + (0.00488758553 * analogRead(A0))); // (5 V / 1024 (Analog) = 0.0049) which converter Measured analog input voltage to 5 V Range
delay(1);
}
Vc = Vc /1000;
//Serial.print("Voltage of current sensor (V) = "); // shows the measured voltage
//Serial.println(V); // the ‘2’ after voltage allows you to display 2 digits after decimal point
Current = (V -2.51)/(0.185); // Sensed voltage is converter to current
Current+=0.04;
//Serial.print(" Current (A) = "); // shows the voltage measured
//Serial.println(Current,2); // the ‘2’ after voltage allows you to display 2 digits after decimal point
  f=f+Current;
  f=(f/n);    //current
  //Serial.print("Average Current: ");
  //Serial.println(f);
  Q[i]=((f*10)/3600);  //InstantaneousmAH
  //Serial.print("Charge at an instant: ");
  //Serial.println(Q[i]);
  SOC=(SOC-(Q[i]*100/2.2));
  //SOC=19;
  //Serial.print("Current SOC: ");
  Serial.println(SOC);
      n=n++;
C+=Q[i];
//Serial.print("Total Charge:");
//Serial.println(C);
BTserial.print(SOC);

BTserial.print(";");
 delay(10000);


    }
    }
