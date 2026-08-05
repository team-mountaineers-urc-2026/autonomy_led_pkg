//note current PINS are not PWM so RGB blending effect does no work
#define RED_PIN 10
#define GREEN_PIN 9
#define BLUE_PIN 11

int mode = 0; //basic tester default

void setup()
{
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop()
{
  if(Serial.available() > 0){
    int temp = Serial.read();
    if(temp == 48 || temp == 49 || temp == 50 || temp == 51 || temp == 52 || temp == 53 || temp == 54 || temp == 55){ //if data is either '0', '1', '2', '3', '4', '5', '6', '7'
      mode = temp; //change mode
      //Serial.println(mode);  //test print
    }
    Serial.write(6); //some other function...
  }

  switch (mode){
    case 0: //startup case
      startup_sequence();
      break;
    
    case 1: //Generic idle sequence after startup
      color_RGB(0, 0, 255);
      break;

    case 48: //Ascii for 0 (Autonomous)
      color_RGB(255, 0, 0); //display red
      break;

    case 49: //Ascii for 1 (Telop)
      color_RGB(0, 0, 255); //display blue
      break;

    case 50: //Ascii for 2 (Arrival)
      color_RGB_blink(0,  255,  0,  500); //green
      color_RGB_blink(0,    0,  0,  500); //black or off
      break;

    case 51: //Ascii for 3 (WeeWoo)
      color_RGB_blink(  0,    0,    255,  500); //blue
      color_RGB_blink(255,    0,      0,  500); //red
      break;


     case 52: //Ascii for 4 (Party)
      color_RGB_blink(  255,    0,  0,  100); //Red
      color_RGB_blink(255,  128,    0,  100); //Orange
      color_RGB_blink(255,  255,    0,  100); //Yellow
      color_RGB_blink(  0,  255,    0,  100); //Green
      color_RGB_blink(  0,    0,  255,  100); //Blue
      color_RGB_blink(128,    0,  255,  100); //Purple
      break;

     case 53: //Ascii for 5 (WVU)
      color_RGB_blink(255,  255,    0,  500); //Yellow
      color_RGB_blink(  0,    0,  255,  500); //Blue
      break;
     
     case 54: //Ascii for 6 (Rainbow)
      fade_to(255,   0,   0, 10);   // Red
      fade_to(255, 128,   0, 10);   // Orange
      fade_to(255, 255,   0, 10);   // Yellow
      fade_to(  0, 255,   0, 10);   // Green
      fade_to(  0,   0, 255, 10);   // Blue
      fade_to(128,   0, 255, 10);   // Purple
      break;

     case 55: //Ascii for 7 (Monash)
      color_RGB(252, 76, 78); //monash
      break;

     default: //Do nothing for unknown values.
      break;
  }

}

void color_RGB(int red_val, int green_val, int blue_val){ //0~256
  analogWrite(RED_PIN, red_val); //leds work on Deimos via "usually on."
  analogWrite(GREEN_PIN, green_val);
  analogWrite(BLUE_PIN, blue_val);
}

void color_RGB_blink(int red_val, int green_val, int blue_val, int delay_val){ //0~256
  analogWrite(RED_PIN, red_val);
  analogWrite(GREEN_PIN, green_val);
  analogWrite(BLUE_PIN, blue_val);
  delay(delay_val);
}

//variables only used in rainbow helper
int cur_red = 0, cur_green = 0, cur_blue = 0;

//For fun rainbow helper function...
//for refernce 5 translates roughly to 1.3s fade time.
void fade_to(int red_val, int green_val, int blue_val, int delay_val)
{
  while (cur_red != red_val || cur_green != green_val || cur_blue != blue_val)
  {
    if (cur_red < red_val) cur_red++; else if (cur_red > red_val) cur_red--;
    if (cur_green < green_val) cur_green++; else if (cur_green > green_val) cur_green--;
    if (cur_blue < blue_val) cur_blue++; else if (cur_blue > blue_val) cur_blue--;

    color_RGB(cur_red, cur_green, cur_blue);
    delay(delay_val);
  }
}

//flash white between brightnesses for "some point"
void startup_sequence() {
  
  for(int i = 0; i < 15; i++){ // 67 is about 20 seconds
    color_RGB_blink(60, 60, 60, 150);         // dim white
    color_RGB_blink(255, 255, 255, 150);      // bright white
  }

  fade_to(  0,  0,  255,  10);
  fade_to(  0,    0,    255,  10);
  mode = 1; //leave startup
}
