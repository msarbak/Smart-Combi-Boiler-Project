#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

//1. Firebase veritabanı adresi, Token bilgisi ve ağ adresi bilgileri
#define FIREBASE_HOST "***" // http:// veya https:// olmadan yazın
#define FIREBASE_AUTH "***"
#define WIFI_SSID "**"
#define WIFI_PASSWORD "**"
int istenilen=0;
int sicaklik=0;
int relay=0;
//2. veritabanim adında bir firebase veritabanı nesnesi oluşturuyoruz
FirebaseData veritabanim;

void setup()
{

  Serial.begin(9200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Ağ Bağlantısı Oluşturuluyor");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP adresine bağlanıldı: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //3. Firebase bağlantısı başlatılıyor

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Ağ bağlantısı kesilirse tekrar bağlanmasına izin veriyoruz
  Firebase.reconnectWiFi(true);
 pinMode(D0,OUTPUT);
 digitalWrite(D0,LOW);
}

void loop()
{
  //////istenilen sıcaklığın bulunması
if(Firebase.getString(veritabanim, "/istenilen")) 
  {
     istenilen=veritabanim.stringData().toInt();
    //Serial.println(istenilen);
    //if(veritabanim.stringData()=="20"){Serial.print("oldu");}
   //Serial.println(veritabanim.stringData());
  }else{
    Serial.print("Str verisi çekilemedi, ");
    Serial.println(veritabanim.errorReason());
  }
  //sıcaklığın veritabanından çekilmesi
  if(Firebase.getFloat(veritabanim, "/sicaklik")) 
  {
     sicaklik=veritabanim.stringData().toInt();
    
    //Serial.println(sicaklik);
    
  }else{
    Serial.print("Str verisi çekilemedi, ");
    Serial.println(veritabanim.errorReason());
  }
  ////relay duurumu
  if(Firebase.getString(veritabanim, "/relay"))
  {
     relay=veritabanim.stringData().toInt();
    //Serial.println(istenilen);
    //if(veritabanim.stringData()=="20"){Serial.print("oldu");}
   //Serial.println(veritabanim.stringData());
  }else{
    Serial.print("Str verisi çekilemedi, ");
    Serial.println(veritabanim.errorReason());
  }
  if(Firebase.getString(veritabanim, "/otomatikmanuel")) 
  {
    //bağlantı başarılı ve veri geliyor ise
    //Serial.print("String tipinde veri alımı başarılı, veri = ");
    //Serial.println(veritabanim.stringData());
    if (veritabanim.stringData()=="1"){//otomatik
      if(sicaklik>=istenilen){
        digitalWrite(D0,LOW);
        }
      else{
        digitalWrite(D0,HIGH);
        }
      
      //Serial.println(sicaklik);
    }
    else {
      Serial.print("manuel\n");
     if(relay==1){
      digitalWrite(D0,HIGH);
      }
      else{
        digitalWrite(D0,LOW);
        }
      }
    
    

  }else{
    //hata varsa hata mesajı ve nedeni yazdırılıyor

    Serial.print("Str verisi çekilemedi, ");
    Serial.println(veritabanim.errorReason());
  }


  



  
}

