//Actividad Punto 4 | Adrián Hernández
//Fecha: 05/05/2024
#include <WiFi.h>

const char* ssid = "Practica1-Adrian";
const char* password = "Hernandez123.";
int max_clientes = 2;
IPAddress ip(192, 168, 1, 2);
IPAddress puerta_enlace(192, 168, 1, 1);
IPAddress mascara(255, 255, 255, 0);
IPAddress dhcp(192, 168, 1, 5);

void obtener_informacion_ap() {
  Serial.println("[*][*]Información del punto de acceso[*][*]");
  Serial.println("[+] SSID: " + String(WiFi.softAPSSID()));
  Serial.print("[+] Canal de frecuencia : ");
  Serial.println(WiFi.channel());
  Serial.println("[+] Modo de encriptación: WPA2_PSK");
  Serial.println("[+] Máximo de clientes: "+ String(max_clientes));
  Serial.print("[+] Rango de direcciones IP: ");
  Serial.print(String(dhcp[0]) + "." + String(dhcp[1]) + "." + String(dhcp[2]) + "." + String(dhcp[3]) + " - ");
  Serial.println(String(dhcp[0]) + "." + String(dhcp[1]) + "." + String(dhcp[2]) + "." + String(dhcp[3] + max_clientes - 1));
  Serial.print("[+] Dirección IP del AP: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("[+] Puerta de enlace del AP: ");
  Serial.println(puerta_enlace);
  Serial.print("[+] Máscara de subred del AP: ");
  Serial.println(WiFi.softAPSubnetMask());
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password, 6, WIFI_AUTH_WPA2_PSK, 2);
  WiFi.softAPConfig(ip, puerta_enlace, mascara, dhcp);
  obtener_informacion_ap();
}

void loop() {
}
