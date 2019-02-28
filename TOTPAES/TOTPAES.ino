// Date and time functions using a DS3231 RTC connected via I2C and Wire lib 
#include <Wire.h> 
#include "RTClib.h" 


#include <AESLib.h>
#include <LiquidCrystal_I2C.h>
String stringOne, stringTwo, stringThree;
RTC_DS3231 rtc; 
int a,b,c,d,e,f;
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup () { 


   Serial.begin(9600); 
 
   lcd.init(); //initialize the lcd
   lcd.backlight(); //open the backlight 
    
  if (! rtc.begin()) { 
    Serial.println("Couldn't find RTC"); 
    while (1); 
  } 

   if (rtc.lostPower()) { 
     Serial.println("RTC lost power, lets set the time!"); 
     // following line sets the RTC to the date & time this sketch was compiled 
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
     // This line sets the RTC with an explicit date & time, for example to set 
     // January 21, 2014 at 3am you would call: 
     // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); 
   } 
 } 
 
 void loop () { 
     DateTime now = rtc.now(); 
     uint8_t key[] = {3,2,6,7,1,5,3,4,8,9,9,0,1,7,9,1};
     char Time[20] =" ";
     char text[128] = " ";
     char code[6] =" ";
//     Serial.print(now.year(), DEC); 
//     Serial.print('/'); 
//     Serial.print(now.month(), DEC); 
//     Serial.print('/'); 
//     Serial.print(now.day(), DEC); 
//     Serial.print(" ("); 
//     Serial.print(now.hour(), DEC); 
//     Serial.print(':'); 
//     Serial.print(now.minute(), DEC); 
//     Serial.print(':'); 
//     Serial.print(now.second()); 
//     Serial.print(" )"); 
//     Serial.println(); 
     
     sprintf(Time,"%d:%d:%d %d%d%d",now.hour(),now.minute(),now.second(),now.month(),now.day(),now.year());
     sprintf(text,"%d%d%d%d%d",now.year(),now.month(),now.day(),now.hour(),now.minute());
     lcd.setCursor(0,0);
     lcd.print(Time);
     aes128_enc_single(key,text);
     a = abs(int(text[3])%10);
     b = abs(int(text[6])%10);
     c = abs(int(text[9])%10);
     d = abs(int(text[1])%10);
     e = abs(int(text[4])%10);
     f = abs(int(text[7])%10);
//     Serial.print(a);
//     Serial.print(b);
//     Serial.print(c);
//     Serial.print(d);
//     Serial.print(e);
//     Serial.print(f);
//     Serial.println(); 
   
     lcd.setCursor(0,1);
     sprintf(code,"code: %d%d%d%d%d%d",a,b,c,d,e,f);
     lcd.print(code);
     delay(1000);
     lcd.clear();
 } 


