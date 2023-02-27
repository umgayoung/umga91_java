//① 번에는 헤더 파일 포함, 네트워크 접속 정보 외 각종 선언들이 들어가고
#include <ESP8266WiFi.h>

const char*  ssid = "itschool303";   
const char* password = "!itschool303";
// Create an instance of the server

// specify the port to listen on as an argument
WiFiServer server(80);

//②번은 setup() 함수로 WiFi 연결을 설정합니다.
void setup() {
  //모니터링과 디버깅을 위해 Serial 통신을 설정
  Serial.begin(9600);
  delay(10);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // WiFi 연결 시도
  WiFi.begin(ssid, password);
  // 연결될 때 까지 계속 실행
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

//③번은 loop() 함수이고, Client 접속이 들어올 때마다 웹페이지를 전송합니다.
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available(); // 클라이언트 접속이 들어오는지 체크
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  //while(!client.available()){
  //  delay(1);
  //}
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Prepare the response
  String s="<html>";
  s=s+"<meta name='viewport' content='width=device-width, initial-scale=1.0'/>";
  //s=s+"<meta http-equiv='refresh' content='5'/>";
  s=s+"<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />";
  s=s+"<head></head><body>반갑습니다!!</body></html>";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed  
}
