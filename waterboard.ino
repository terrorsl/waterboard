#include"src/waterboard.h"

WaterBoard wb;

void setup()
{
  Serial.begin(9600);
  wb.setup();  
}
void loop()
{
  wb.loop();
}
