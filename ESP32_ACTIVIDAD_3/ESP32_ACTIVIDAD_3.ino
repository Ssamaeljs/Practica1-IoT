//Actividad Punto 3 | Adrián Hernández
//Fecha: 05/05/2024
#include <WiFi.h>
#include <ESP32Ping.h>
#include <ESPmDNS.h>

const char* ssid     = "Internet_UNL";
const char* password = "UNL1859WiFi";

IPAddress ip(192,168,100,150);
IPAddress puerta_enlace(192,168,100,1);
IPAddress mascara(255,255,255,0);
IPAddress dns(8,8,8,8);

String modoOperacion(){
  switch (WiFi.getMode()) {
    case WIFI_STA: return "WIFI_STA";
    case WIFI_AP: return "WIFI_AP";
    case WIFI_AP_STA: return "WIFI_AP_STA";
    default: return "Desconocido";
  }
}
String tipoAutenticacion(){
  int num_redes = WiFi.scanNetworks();
  for (int i = 0; i < num_redes; i++) {
    if (WiFi.SSID(i) == WiFi.SSID()) {
      switch (WiFi.encryptionType(i)) {
        case (WIFI_AUTH_OPEN): return "Open";
        case (WIFI_AUTH_WEP):  return "WEP";
        case (WIFI_AUTH_WPA_PSK): return "WPA PSK";
        case (WIFI_AUTH_WPA2_PSK): return "WPA2 PSK";
        case (WIFI_AUTH_WPA_WPA2_PSK): return "WPA/WPA2 PSK";
        case (WIFI_AUTH_WPA2_ENTERPRISE): return "WPA2 Enterprise";
        default: return "Desconocida";
      }
      break;
    }
  }
}
void obtener_info_ap(){
  Serial.println("[*][*] Información del punto de acceso [*][*] ");
  Serial.println("[+] SSID : " + WiFi.SSID());
  Serial.println("[+] MAC : " + WiFi.BSSIDstr());
  Serial.print("[+] Canal de frecuencia : ");
  Serial.println(WiFi.channel());
  Serial.println((String)"[+] RSSI : " + WiFi.RSSI() + " dB");
  Serial.println("[+] Modo de operación : " + modoOperacion());
}
void obtener_detalles_conexion(){
  Serial.println("[*][*] Detalles de la conexión [*][*]");
  Serial.println("[+] Tipo de Autenticación : " + tipoAutenticacion());
  Serial.print("[+] Dirección IP : ");
  Serial.println(WiFi.localIP());
  Serial.print("[+] Máscara de subred: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("[+] Puerta de enlace : ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("[+] DNS : ");
  Serial.println(WiFi.dnsIP());
}
void obtener_estadisticas(){
  
  Serial.println("[*][*] Estadísticas de la conexión [*][*]");

  IPAddress ip_objetivo(192,168,100,1);
  int tamanio_paquete = 32;
  int paquetes_enviados = 0;
  int paquetes_recibidos = 0;
  int paquetes_perdidos = 0;
  int errores_transmicion = 0;
  int errores_recepcion = 0;

  if(Ping.ping(ip_objetivo, tamanio_paquete)){
    paquetes_recibidos++;
  }else{
    paquetes_perdidos++;
    errores_recepcion++;
    errores_transmicion++;
  }
  paquetes_enviados = paquetes_recibidos + paquetes_perdidos;

  Serial.println("[+] Cantidad de paquetes envíados : " + String(paquetes_enviados));
  Serial.println("[+] Cantidad de paquetes recibidos : " + String(paquetes_recibidos));
  Serial.println("[+] Cantidad de paquetes perdidos : " + String(paquetes_perdidos));
  Serial.println("[+] Cantidad de errores en la transmisión : " + String(errores_transmicion));
  Serial.println("[+] Cantidad de errores en la recepción : " + String(errores_recepcion));
  Serial.println("[+] Cantidad de bytes transferidos : " + String(tamanio_paquete));
  Serial.println("[+] Tiempo de conexión activa : " + String(Ping.averageTime()) + " segundos");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("\nConectando a ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  WiFi.config(ip, puerta_enlace, mascara, dns);
  Serial.println("\nConectado a la red WiFi!");

  if (!MDNS.begin("esp32")) {
    Serial.println("No se puede configuar el mDNS!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("Se ha configurado el mDNS");
  obtener_detalles_conexion();
  obtener_info_ap();
  obtener_estadisticas();
}

void loop() {
}
