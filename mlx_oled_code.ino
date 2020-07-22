#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define trigg 9 // pulse trigger
#define echo 8  // pulse note
#define buzz 7 // buzzer
#define led1 6 // not in range
#define led2 5 // correct range
#define gatekey 4 // correct range

int distance;
float time;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {  
	mlx.begin(); 
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
	display.clearDisplay();
	display.display();
	Serial.begin(9600);
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(buzz, OUTPUT);
	pinMode(gatekey, OUTPUT);
	pinMode(trigg, OUTPUT); // Sets the trigPin as an OUTPUT
	pinMode(echo, INPUT);
	

}

void loop() {
	measure_distance();
	if ((distance >2.5) && (distance < 30))
		{
			temperature();
			 if (temperature()<35)
			{
			digitalWrite(led2, HIGH);
			digitalWrite(gatekey,HIGH);
			delay(20);
			digitalWrite(led2, LOW);
			delay(20);
			
			}
			else if (temperature() > 35)
			{
				for (int j=0; j<5; j++){
					digitalWrite(buzz, HIGH);
					digitalWrite(led1, HIGH);
					delay(500);
					digitalWrite(buzz, LOW);
					digitalWrite(led1, LOW);
					delay(500);
					}
			
			}
		for (int i=0; i<3; i++){
				digitalWrite(led1,HIGH);
				digitalWrite(led2,HIGH);
				delay(500);
				digitalWrite(led1,LOW);
				digitalWrite(led2,LOW);
				delay(500);

		}
		}

	//temperature();
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
	
	Serial.println(distance);
}

float temperature() 
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
	float readval =((0.0121*pow(mlx.readObjectTempC(), 3)) - (1.0833*pow(mlx.readObjectTempC(),2)) + (32.391*(mlx.readObjectTempC())) - 288.48);
	if ((readval < 25) ){
		display.println("low");
	}
	else if ((readval > 42)){
		display.println("Over");
		}
	else {
	display.println(readval,1);
	display.setCursor(110,17);
	display.println("C");
	}
	
	display.display();
	delay(100);
	return readval;
	
}