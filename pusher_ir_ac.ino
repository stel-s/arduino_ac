#include <SPI.h>
#include <Ethernet.h>
#include <avr/pgmspace.h>
#include <PusherClient.h>
#include <IRremote.h>

IRsend irsend;
PROGMEM prog_uint16_t power[60]={8400,4200,550,1600,550,550,550,550,550,550,500,1600,550,600,500,550,550,550,550,550,500,550,550,550,550,550,500,600,500,550,550,550,550,550,500,550,550,1600,600,1550,600,1600,550,550,550,550,500,1600,600,550,500,1600,600,550,500,550,550,1600,550};

void setup() 
{
  
  Serial.begin(9600);
 pinMode(8,OUTPUT);
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  if (Ethernet.begin(mac) == 0)
  {
    for(;;);
  }
  
  if (!Pusher.connect())
  {
    Serial.println("connected");
    for(;;);
  } 
  Pusher.bind("client-turnon", turnon);
  Pusher.bind("client-turnoff", turnoff);
  Pusher.subscribePrivate("private-channel");
  //Pusher.triggerPrivateEvent("private-ChannelName", "client-eventName", "\"\"");
}

  unsigned long lasttime;
  bool toggle;
  int k;
 void turnon(const String& name,const String& data){
     digitalWrite(8,HIGH);
     for(int i=1;i<3;i++){
      irsend.sendRaw(power,60,38); 
      delay(402);
     }
  }
  void turnoff(const String& name,const String& data){
     digitalWrite(8,LOW);

     for(int i=1;i<3;i++){
          //irsend.sendRaw(display,60,38); 
          
     }
  }
void loop() 
  {   
  Pusher.monitor();  


  unsigned long time = millis();  
  if (time > lasttime + 1000)
  {
    //signalActualState();
    lasttime = time;
  }
}

void signalActualState()
{
    if (toggle)
      Pusher.triggerPrivateEvent("private-ChannelName", "client-eventName", "\"1\"");
    else
      Pusher.triggerPrivateEvent("private-ChannelName", "client-eventName", "\"0\"");
}
