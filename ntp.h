/**
 * Does NTP and DST.
 * @see https://github.com/neptune2/simpleDSTadjust/blob/master/examples/ntpTimedemo_DST/ntpTimedemo_DST.ino
 */

#include <ESP8266WiFi.h>
#include <sunset.h>
#include <time.h>
#include <simpleDSTadjust.h>

const char *ssid     = "HelloWardrivers!";
const char *password = "aaaa1111";

#define NTP_SERVERS "us.pool.ntp.org", "pool.ntp.org", "time.nist.gov"

#define TIMEZONE  -5
#define LATITUDE  39.10895
#define LONGITUDE -77.11047

// US Eastern Time Zone (New York, Boston).
struct dstRule StartRule = {"EDT", Second, Sun, Mar, 2, 3600};    // Daylight time = UTC/GMT -4 hours
struct dstRule EndRule = {"EST", First, Sun, Nov, 2, 0};       // Standard time = UTC/GMT -5 hour
simpleDSTadjust dstAdjusted(StartRule, EndRule);

SunSet sun;

void updateNTP() {
  configTime(TIMEZONE * 3600, 0, NTP_SERVERS);
  delay(500);
  while (!time(nullptr)) {
    Serial.print("#");
    delay(1000);
  }
}

void ntp_setup() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  sun.setPosition(LATITUDE, LONGITUDE, TIMEZONE);  
}

void ntp_loop() {
  updateNTP(); // Init the NTP time

  char buf[30];
  char *dstAbbrev;

  time_t t0 = ::time(nullptr);
  struct tm *timeinfo0 = localtime (&t0);

  time_t t = dstAdjusted.time(&dstAbbrev);
  struct tm *timeinfo = localtime (&t);
 
  int hour = (timeinfo->tm_hour+11)%12+1;  // take care of noon and midnight
  sprintf(buf, "%02d/%02d/%04d %02d:%02d:%02d%s %s\n",timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_year+1900, hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_hour>=12?"pm":"am", dstAbbrev);
  Serial.print(buf);

  sun.setCurrentDate(2022, 04, 22);
  
  int dstOffsetMinutes = (1 - (timeinfo->tm_hour - timeinfo0->tm_hour)) * 60;
  Serial.printf("dst Offset: %d\n", dstOffsetMinutes);
  
  double sunrise = sun.calcSunrise() + dstOffsetMinutes;
  Serial.printf("Sunrise: %d:%02d am\n", (int)sunrise / 60, (int)sunrise % 60);
  double sunset = sun.calcSunset() + dstOffsetMinutes;
  Serial.printf("Sunset %d:%02d pm\n", ((int)sunset / 60) - 12, (int)sunset % 60);
}
