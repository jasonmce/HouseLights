/**
 * Does NTP, DST, and sunrise/sunset.
 * @see https://github.com/neptune2/simpleDSTadjust/blob/master/examples/ntpTimedemo_DST/ntpTimedemo_DST.ino
 * @see https://www.arduino.cc/reference/en/libraries/sunset/
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
  updateNTP(); // Init the NTP time  
  sun.setPosition(LATITUDE, LONGITUDE, TIMEZONE);  
}

/**
 * @return bool
 *   If we are observing DST.
 */
bool isDST() {
  char *dstAbbrev;
  dstAdjusted.time(&dstAbbrev);
  return !strcmp(dstAbbrev, StartRule.abbrev);
}

/**
 * @return int
 *   Number of minutes since midnight.
 */
int timeInMinutes() {
  char *dstAbbrev;
  time_t t = dstAdjusted.time(&dstAbbrev);
  struct tm *timeinfo = localtime (&t);
  return (timeinfo->tm_hour * 60) + timeinfo->tm_min;
}

int minutesToSleepUntilDark() {
 
  sun.setCurrentDate(2022, 04, 22);
  sun.setTZOffset(TIMEZONE + (isDST() ? 1 : 0));
 
  int sunrise = sun.calcSunrise();
  int sunset = sun.calcSunset();
  int nowmins = timeInMinutes();

//  Serial.printf("Now %d:%02d pm\n", (nowmins / 60), nowmins % 60);
//  Serial.printf("Sunrise: %d:%02d am\n", sunrise / 60, sunrise % 60);
//  Serial.printf("Sunset %d:%02d pm\n", (sunset / 60) - 12, sunset % 60);
//  Serial.printf("isDST is %d\n", isDST() ? 1 : 0);

  // Before sunrise, return 0.
  if (nowmins < sunrise) {
    return 0;
  }
  // After sunset, return 0;
  if (nowmins > sunset) {
    return 0;
  }
  return sunset - nowmins;
}

int minutesToSunset() {
  char *dstAbbrev;

  time_t t = dstAdjusted.time(&dstAbbrev);
  struct tm *timeinfo = localtime (&t);
 
  sun.setCurrentDate(2022, 04, 22);

  int sunset = sun.calcSunset() + 60;
  int nowmins = timeInMinutes();

  // Before sunset is simple subtraction.
  if (sunset > nowmins) {
    return sunset - nowmins;
  }
  // Minutes to midnight + sunrise minutes. 
  return (1440 - nowmins) + sunset; 
}
