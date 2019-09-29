#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define lit1 D0
#define lit2 D1
#define lit3 D2

// Set these to run example.
#define FIREBASE_HOST "home-64c6b.firebaseio.com"
#define FIREBASE_AUTH "YK0zt70RAMi3OQ3jCNU3fYxSoY5Nv864twqBCdfN"
#define WIFI_SSID "Thick India"
#define WIFI_PASSWORD "thick@123#"

void setup() {
  Serial.begin(115200);
  pinMode(lit1,OUTPUT);
  pinMode(lit2,OUTPUT);
  pinMode(lit3,OUTPUT);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("L1",0);
  Firebase.set("L2",0);
  Firebase.set("M1",0);
}
void firebasereconnect(){
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  }
int n = 0;
char L1[5];
char L2[5];
char M1[5];
void loop() {
  // set value
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());  
      firebasereconnect();
      return;
  }
Firebase.getString("L1").toCharArray(L1,sizeof(L1));
Firebase.getString("L2").toCharArray(L2,sizeof(L2));
Firebase.getString("M1").toCharArray(M1,sizeof(M1));

delay(1000);
int Li1 = atoi(L1);
int Li2 = atoi(L2);
int M = atoi(M1);

if(Li1==1)
{
  digitalWrite(lit1,1);
  Serial.println(" l1 on");
}
if(Li1==0)
{
  digitalWrite(lit1,0);
  Serial.println(" l1 off");
}
if(Li2==1)
{
  digitalWrite(lit2,1);
  Serial.println(" l2 on");
}
if(Li2==0)
{
  digitalWrite(lit2,0);
  Serial.println(" l2 off");
}
if(M==1)
{
  digitalWrite(lit3,1);
  Serial.println(" m1 on");
}
if(M==0)
{
  digitalWrite(lit3,0);
  Serial.println(" m1 off");
}
}
