#include <SoftwareSerial.h>
#include "EmonLIB/EmonLib.h"






#define SerialTX 10
#define SerialRX 11
#define SerialCTR 4

#define rs485_transmit HIGH
#define rs485_receive LOW

#define ct1_in 0
#define ct2_in 1
#define ct3_in 2

SoftwareSerial rs485(SerialRX,SerialTX);

EnergyMonitor current_meter1;
EnergyMonitor current_meter2;
EnergyMonitor current_meter3;

float current1 = 0.0;
float current2 = 0.0;
float current3 = 0.0;


unsigned long last_time = 0;





void setup()
{
  pinMode(SerialCTR,OUTPUT);
  pinMode(SerialRX,INPUT);
  pinMode(SerialTX,OUTPUT);
     
  rs485.begin(9600);
   
  current_meter1.current(ct1_in,55);
  current_meter2.current(ct2_in,55);
  current_meter3.current(ct3_in,55);
  digitalWrite(SerialCTR,rs485_receive);
  
  

}

void loop()
{

 
  digitalWrite(SerialCTR,rs485_receive);
  
  if(rs485.available()){
	  
	  char x = rs485.read();
	  
	  if(x=='s'){
		  
		  
		
		  
		   current1 = current_meter1.calcIrms(1480);
		   current2 = current_meter2.calcIrms(1480);
		   current3 = current_meter3.calcIrms(1480);
		  
		  digitalWrite(SerialCTR,rs485_transmit);
		  rs485.print("c^");
		  rs485.print(current1);
		  rs485.print("^");
		  rs485.print(current2);
		  rs485.print("^");
		  rs485.println(current3);
		  
		  
		  
		  
		    
	  }
	  
	  
  }
 
 


	
	

  
  
  
  
  

}
