/**********************************************************
*
*   File:
*       thermo-logger-firmware.ino
*
*   Description:
*       Arduino code for the thermocouple logger.
*
**********************************************************/

/**********************************************************
 Includes
**********************************************************/
#include <Adafruit_MAX31855.h>

/**********************************************************
 Constants
**********************************************************/
#define SCLK_PIN 13       /* SPI clock            */
#define MISO_PIN 12       /* master-in slave-out  */
#define SS_PIN 10         /* slave select         */
#define LOGGING_RATE 1  /* logs per second (hz) */
//#define DEBUG

/**********************************************************
 Global Variables
**********************************************************/
Adafruit_MAX31855 tc( SS_PIN ); /* Thermocouple object */

/**********************************************************
 Procedures
**********************************************************/

/**********************************************************
*
*   Procedure:
*       setup
*
*   Description:
*       Configure serial connection and connect TC.
*
**********************************************************/
void setup
  (
  void
  ) 
{
Serial.begin( 57600 ); /* baud rate must match server */

/* wait for server connection */
while ( !Serial ) 
  {
  delay(1);
  }

#ifdef DEBUG
Serial.println("Connected!");
#endif /* DEBUG */

/* wait for TC to stabilize */
delay(500);
if (!tc.begin()) 
  {
  while ( 1 )
    {
    delay(1);
    }
  }

#ifdef DEBUG
Serial.println("TC Initialized!");
#endif /* DEBUG */

} /* setup() */


/**********************************************************
*
*   Procedure:
*       loop
*
*   Description:
*       Runs until reset or poweroff. Logs TC values.
*
**********************************************************/
void loop
  (
  void
  ) 
{
double c = tc.readCelsius();
if (isnan(c)) 
  {
  #ifdef DEBUG
  Serial.println("Thermocouple fault(s) detected!");
  uint8_t e = tc.readError();
  if (e & MAX31855_FAULT_OPEN) Serial.println("FAULT: Thermocouple is open - no connections.");
  if (e & MAX31855_FAULT_SHORT_GND) Serial.println("FAULT: Thermocouple is short-circuited to GND.");
  if (e & MAX31855_FAULT_SHORT_VCC) Serial.println("FAULT: Thermocouple is short-circuited to VCC.");
  #endif /* DEBUG */
  }
  else 
  {
  Serial.println(c);
  }

delay( (int)(1000 / LOGGING_RATE) );

} /* loop() */

/**********************************************************
 EOF
**********************************************************/
