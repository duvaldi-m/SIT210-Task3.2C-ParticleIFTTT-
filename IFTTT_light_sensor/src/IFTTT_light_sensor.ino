/*
 * Project IFTTT_light_sensor
 * Description: Measuring light and publish to IFTTT
 * Author: Duvaldi Marneweck
 */

/*
light levels
1000 lux	Overcast day; typical TV studio lighting
10000–25000 lux	Full daylight (not direct sun)
32000–100000 lux	Direct sunlight
*/

#include "BH1750.h"

BH1750 lightSensor(0x23, Wire);
bool flag = true;


void setup() {
    Serial.begin(9600);
    lightSensor.begin(); 
    lightSensor.set_sensor_mode(BH1750::forced_mode_high_res2);
    
}

void loop() {

    lightSensor.make_forced_measurement();
    float  light_val = lightSensor.get_light_level();
    Serial.print("Light level: ");
    Serial.println(light_val);

    while (light_val > 32000)
    {
      if (flag)
      {
        Particle.publish("sunny");
        flag = false;
      }
      
      delay(1000);
      light_val = lightSensor.get_light_level();
    }
    
    flag = true;

    while (light_val < 32000)
    {
      if (flag)  
      {
        Particle.publish("shady");
        flag = false;
      }

      delay(1000);
      light_val = lightSensor.get_light_level();
    }
    flag = true; 

}