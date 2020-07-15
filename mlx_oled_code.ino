

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define trigg 9 // pulse trigger
#define echo 8  // pulse note
float distance;
float time;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {  
  mlx.begin(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.clearDisplay();
  display.display();
  Serial.begin(9600);

}

void loop() {
  /*measure_distance();
  if (distance < 40)
    {
      temperature();
    } */
  temperature();
}

void measure_distance()
{
  digitalWrite(trigg, LOW);
  delayMicroseconds(2);
  digitalWrite(trigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigg, LOW);
  delayMicroseconds(2);
  time = pulseIn(echo, HIGH);
  distance = time * 340 / 20000;
}


void temperature() 
{
  display.clearDisplay();
  
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Ambient"); 
  
  display.setTextSize(2);
  display.setCursor(50,0);
  display.println(mlx.readAmbientTempC(),1);
 
  display.setCursor(110,0);
  display.println("C");
  
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,20);                
  display.println("Target"); 
  
  display.setTextSize(2);
  display.setCursor(50,17);
  float readval = ((mlx.readObjectTempC() * 0.7188) + 15.744);
  Serial.println(readval);
  display.println(readval,1);
  
  display.setCursor(110,17);
  display.println("C");
  
  display.display();
  
  delay(100);

  
}
