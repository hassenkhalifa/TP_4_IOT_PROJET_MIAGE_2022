#include "WiFi.h"
#include "PubSubClient.h"
#include "ArduinoJson.h"
#include "OneWire.h"
#include "DallasTemperature.h"

// WiFi
//const char *ssid = "Freebox-08247B"; // Enter your WiFi name
//const char *password = "0493705536";  // Enter WiFi password
const char *ssid = "HKN"; // Enter your WiFi name
const char *password = "12345678";  // Enter WiFi password

const char *lat = "43.63386535644531"; //coordoné 24 Chemin de Saint-Marc, Grasse, France
const char *lgn = "6.961919784545898"; 

const int ledPin = 19;
const int ledPin2 = 18;

String CoolerStatus;
String HeaterStatus;

const int LightPin = A5;

OneWire oneWire(23); 
DallasTemperature tempSensor(&oneWire) ;

// MQTT Broker
const char *mqtt_broker = "test.mosquitto.org";
const char *topic = "iot/M1Miage2022";
const char *mqtt_username = "darkvador";
const char *mqtt_password = "6poD2R2";
const int mqtt_port = 1883;

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
    String client_id = "deathstar";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println(" mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // publish and subscribe
  // client.publish(topic, "TEST HASSEN KHALIFA");
  // client.subscribe(topic);
}
void publishinfo(String temps, String light, String Ip, String Mac, String SSiD, String CoolerStatus, String HeaterStatus) {
  DynamicJsonDocument doc(2048);
  doc["status"]["temperature"] = temps;
  doc["status"]["light"] = light;
  doc["status"]["ledCooler"] = CoolerStatus;
  doc["status"]["ledHeater"] = HeaterStatus;
  doc["status"]["running"] = "RUNNING";

  doc["info"]["loc"] = "Grasse";
  doc["info"]["user"] = "21711996";
  doc["info"]["uptime"] = "getUptime()";
  doc["info"]["ssid"] = SSiD;
  doc["info"]["ident"] = Mac;
  doc["info"]["ip"] = Ip;

  doc["reporthost"]["target_ip"] = "target_ip";
  doc["reporthost"]["target_port"] = "target_port";
  doc["reporthost"]["sp"] = "target_sp";
  
  doc["regul"]["threshold"] = "DAY_LIGHT";
  doc["regul"]["sbn"] = "TEMP_NIGHT_LOW";
  doc["regul"]["shn"] = "TEMP_NIGHT_HIGH";
  doc["regul"]["sbj"] = "TEMP_DAY_LOW";
  doc["regul"]["shj"] = "TEMP_DAY_HIGH";

  doc["lat"] = lat;
  doc["lgn"] = lgn;
  String json;
  serializeJson(doc, json);
  char jsonChar[100];

  json.toCharArray(jsonChar, 100);
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
  publishinfo(get_temperature(tempSensor), get_light(LightPin), get_Ip().c_str(), get_Mac(), get_Ssid(), get_CoolerStatus(), get_HeaterStatus());
  client.loop();
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
