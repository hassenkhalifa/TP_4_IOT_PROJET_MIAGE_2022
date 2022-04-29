#include "WiFi.h"
#include "PubSubClient.h"
#include "ArduinoJson.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "time.h"

// WiFi
//const char *ssid = "Freebox-08247B"; // Enter your WiFi name
//const char *password = "0493705536";  // Enter WiFi password
const char *ssid = "HKN"; // Enter your WiFi name
const char *password = "12345678";  // Enter WiFi password


const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

//const char *lat = "43.63386535644531"; //coordoné 24 Chemin de Saint-Marc, Grasse, France
//const char *lgn = "6.961919784545898";

const int ledPin = 19;
const int ledPin2 = 18;

String CoolerStatus;
String HeaterStatus;

const int LightPin = A5;

OneWire oneWire(23);
DallasTemperature tempSensor(&oneWire) ;

// MQTT Broker
//const char *mqtt_broker = "test.mosquitto.org";
//const char *topic = "iot/M1Miage2022";
//const char *mqtt_username = "darkvador";
//const char *mqtt_password = "6poD2R2";
//const int mqtt_port = 1883;

const char *mqtt_broker = "j20ae20e.us-east-1.emqx.cloud";
const char *topic = "esp32/test";
const char *mqtt_username = "HassenTest";
const char *mqtt_password = "12345678";
const int mqtt_port = 15304;


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

String printLocalTime()
{
  char timeSend[45];

  String formatTime;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");

  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  strftime(timeSend, 45, "%A, %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(timeSend);
  formatTime = String(timeSend);
  return formatTime;
}

void publishinfo(String temps, String light, String Ip, String Mac, String SSiD, String CoolerStatus, String HeaterStatus, String timeSend ) {
  int random_int = random(25, 55);
  float random_float = random_int / 1.0;
  int random_int2 = random(5, 15);
  float random_float2 = random_int2 / 1.0;
  int random_int3 = random(1000, 9999);
  DynamicJsonDocument doc(4096);
  doc["status"]["temperature"] = temps;
  doc["status"]["light"] = light;
  doc["status"]["ledCooler"] = CoolerStatus;
  doc["status"]["ledHeater"] = HeaterStatus;
  doc["status"]["lat"] = random_float;
  doc["status"]["lgn"] = random_float2;

  doc["info"]["loc"] = "Grasse";
  doc["info"]["user"] = random_int3;
  doc["info"]["time"] = timeSend;
  //  doc["info"]["ip"] = Ip;
  //  doc["info"]["ident"] = Mac;


  String json;
  serializeJson(doc, json);
  char jsonChar[4096];

  json.toCharArray(jsonChar, 200);
  client.publish(topic, jsonChar);
  delay(2000);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void loop() {
  float t;
  tempSensor.requestTemperaturesByIndex (0) ;
  t = tempSensor.getTempCByIndex (0) ;
  if (t < 25) {
    digitalWrite(ledPin, HIGH);
    delay(1 * 1000);
    digitalWrite(ledPin, LOW);
    delay(1 * 1000);
    CoolerStatus = "off";
    HeaterStatus = "on";
  } else if (t > 25) {
    digitalWrite(ledPin2, HIGH);
    delay(1 * 1000);
    digitalWrite(ledPin2, LOW);
    delay(1 * 1000);
    CoolerStatus = "on";
    HeaterStatus = "off";
  }
  publishinfo(get_temperature(tempSensor), get_light(LightPin), get_Ip().c_str(), get_Mac(), get_Ssid(), get_CoolerStatus(), get_HeaterStatus(), printLocalTime());

  printLocalTime();
  client.loop();


  delay(1000);
}

String get_HeaterStatus() {

  Serial.println ( "Heater Status :  " + HeaterStatus ) ;
  return HeaterStatus;
}
String get_CoolerStatus() {
  Serial.println ( "Cooler Status :  " + CoolerStatus ) ;
  return CoolerStatus;
}

String get_Ip() {


  String ip;
  ip = WiFi.localIP().toString();
  Serial.println("ip : " + ip ); // for debug
  return ip;
}
String get_Mac() {

  String s;
  String mac;
  mac = WiFi.macAddress();
  s = String(mac);
  Serial.println("mac : " + s ); // for debug
  return s;
}
String get_Ssid() {

  String s;
  String ssid;
  ssid = WiFi.SSID();
  s = String(ssid);
  Serial.println("SSID : " + s ); // for debug
  return s;
}
String get_temperature(DallasTemperature tempSensor) {
  /* Renvoie la valeur du capteur de temperature dans une String
     Attention !!
        J'ai enleve le delay mais convertir prend du temps !
        moins que les requetes Http.
  */
  float t;
  String s;
  tempSensor.requestTemperaturesByIndex(0);
  t = tempSensor.getTempCByIndex(0);
  s = String(t);
  Serial.println("Temperature : " + s + " C"); // for debug
  return s;
}
/*--------------------------------*/
String get_light(int LightPin) {
  /* Renvoie la valeur du capteur de lumiere dans une String
  */
  int sensorValue;
  sensorValue = analogRead(LightPin);
  String s = String(sensorValue);
  Serial.println("Light : " + s + " Lum"); // for debug
  return s;
}
