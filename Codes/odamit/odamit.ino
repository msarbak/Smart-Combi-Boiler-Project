#include <Wire.h>
#include "OLED.h"
OLED display(2, 14);
String myNum = "";
String myNum1 = "";
int deger=1;

#include "FirebaseESP8266.h"	
#include <ESP8266WiFi.h>
#include <DHT.h>		


#define FIREBASE_HOST "**" 
#define FIREBASE_AUTH "**"
#define WIFI_SSID "**"
#define WIFI_PASSWORD "**"


#define DHTPIN 4		
int led = D5;			

#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;


void setup()
{

  Serial.begin(9600);

  dht.begin();
  pinMode(led,OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
display.begin();
display.on();

display.print("Sicaklik: " , 1, 0); //2. parametre satir atlatiyor. 3. parametre satir basi yapıyor
display.print("Nem: " , 3, 0);

}

void sensorUpdate(){
 
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);



char b[3],a[3];
itoa(t,b,2);                // Int to Array
itoa(h,a,2);
myNum = String(t);
myNum1 = String(h);
myNum.toCharArray(b,3);   // Int to Array
myNum1.toCharArray(a,3);  
display.print(b , 1, 11);
display.print(a , 3, 11);


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C  ,"));
  Serial.print(f);
  Serial.println(F("°F  "));

  if (Firebase.setFloat(firebaseData, "/sicaklik", t))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  if (Firebase.setFloat(firebaseData, "/nem", h))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}
void loop() {
  sensorUpdate();
 
  delay(100);
}
