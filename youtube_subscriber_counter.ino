//For More Info Contact 
//sreeramzeno@gmail.com
//www.youtube.com/ZenoModiff

#include <YoutubeApi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <Wire.h>  
#include <SSD1306.h>

char ssid[] = "zenomodiff";     
char password[] = "zenomodiff@123";
#define API_KEY "Paste your API KEY"
#define CHANNEL_ID "Paste your channel id"
 
SSD1306  display(0x3c, 2,4);
WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long api_mtbs = 1000; 
unsigned long api_lasttime;
long subs = 0;
String subs_count;
String view_count;

void setup() {

  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
  

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  display.drawString(0,6, "ZenoModiff");
  display.display();
  delay(5000);
  display.clear();
  display.drawString(0,6, "Youtube");
  display.drawString(0,32, "Sub Count");
  display.display();
  delay(3000);
  display.clear();
  Serial.print("Connecting Wifi: ");
  display.drawString(0,6, "Connecting ");
  display.drawString(0,32, "  Wifi... ");
  display.display();
  delay(250);
  display.clear();
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  }
  Serial.println("");
  Serial.println("WiFi");


  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  
  display.drawString(0,6, "Connected ");
  display.display();
  display.clear();
  delay(2000);
  display.drawString(0,6, "Getting");
  display.drawString(0,32, "Data.....");
  display.display();
  display.clear();
  delay(250);
}

void loop() {

  if (millis() - api_lasttime > api_mtbs)  {
    if(api.getChannelStatistics(CHANNEL_ID))
    {
      subs_count = api.channelStats.subscriberCount ;
      view_count = api.channelStats.viewCount ;
      
      Serial.println("---------Status---------");
      Serial.println("Zeno_Modiff");
      Serial.print("S: ");
      Serial.println(subs_count);
      display.clear();
      display.drawString(0,8, "S: ");
      display.drawString(24,8, subs_count);
      Serial.print("V: ");
      Serial.println(view_count);
      display.drawString(0,32,"V: ");
      display.drawString(24,32, view_count);
      Serial.println("------------------------");
      display.display();
    }
    api_lasttime = millis();
  }
}
