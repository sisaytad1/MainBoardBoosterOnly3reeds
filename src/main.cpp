#include <Arduino.h>
#include <pins.h>
#include <led.h>


// put function declarations here:
const int NumSamples = 10; // number of samples per reading period
const int NumReeds = 3; // number of reeds excluding emergency
const int Threshold = 1; //if everything fails, where to activate

//****** FUNCTION VARIABLES ***********
int RawValData = 0; //raw integer that comes in from reed sensor
int RawValEM = HIGH; //raw integer that comes in from reed sensor
int SampleCounter = 0; //counts number of samples appended to array
int BUFIncNum = 0; //buffer value before a it gets appended
int IncNum = 0; //holds increment number per sample after determination
int ledcount = 0; //for christmas lights when pump is on
int pumpstate = 0; //to have global record of pump's state

uint32_t rgb_green = ((uint32_t)0 << RGB_RED_SHIFT) | ((uint32_t)255 << RGB_GREEN_SHIFT) | ((uint32_t)0 << RGB_BLUE_SHIFT);
uint32_t rgb_red = ((uint32_t)255 << RGB_RED_SHIFT) | ((uint32_t)0 << RGB_GREEN_SHIFT) | ((uint32_t)0 << RGB_BLUE_SHIFT);
uint32_t rgb_white = ((uint32_t)255 << RGB_RED_SHIFT) | ((uint32_t)255 << RGB_GREEN_SHIFT) | ((uint32_t)255 << RGB_BLUE_SHIFT);
uint32_t rgb_blue = ((uint32_t)0 << RGB_RED_SHIFT) | ((uint32_t)0 << RGB_GREEN_SHIFT) | ((uint32_t)255 << RGB_BLUE_SHIFT);


//Assigns a level depending on analog reading. As RawVal increases, MaxInc/IncNum increases
int AssignIncrement(int rawval) {
  if (rawval < 1100 && rawval > 700){ //bottommost reed switch
    return 0;
  }
  else if (rawval < 2100 && rawval > 1800){
    return 1;
  }     
  else if (rawval < 3100 && rawval > 2800){ //topmost reed
    return 2;
  }           
  else { //undefined analog read
    return 3;
  }               
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PUMP_EN_PIN, OUTPUT);
  pinMode(TANK_HIGH_N_PIN, INPUT);
  pinMode(TANK_LOW_N_PIN, INPUT);
  pinMode(PRESSURE_ADC_PIN, INPUT);
  led_setup();
  leds_on();
  pinMode(BUZZER_PIN, OUTPUT); 
  ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RESOLUTION);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);

}

void loop() {
  // put your main code here, to run repeatedly:
  int Samples[NumSamples] = {0}; //initialize array of size NumSamples
  int IncrementCounter[NumReeds] = {0}; // hold number of occurences of each increment during a reading
  //Add samples to samples array [this while loop will repeat until samples array is full]
  while (SampleCounter < NumSamples) {
    RawValData = analogRead(TANK_LOW_N_PIN); // analog read on pad C of float sensor
    RawValEM = digitalRead(TANK_HIGH_N_PIN); // digital read on pad A of float sensor

    //if emergency pin (default HIGH) is LOW:
    while (!(RawValEM)){
      PUMP_ENABLE();
      BUZZER_PWM(128);
      RawValEM = digitalRead(TANK_HIGH_N_PIN); //update variable 
    }
    //keep buzzer off when system is normal
    BUZZER_DISABLE();

    //Serial.println(RawValData);

    BUFIncNum = AssignIncrement(RawValData); //determine which reed it's on
    if (BUFIncNum != NumReeds){ //if reed number is not undefined
      Samples[SampleCounter] = BUFIncNum; //add it to samples list
      SampleCounter++; //increment counter
    }
    else { //if reed number is undefined, ignore it
      continue;
    }
  }
  SampleCounter = 0; //reset counter

  //count occurrences of each reed in Samples array and append to IncrementCounter array
  for (int i = 0; i < NumSamples; i++){
    IncrementCounter[Samples[i]]++;
  }

  int MaxCount = 0;
  int MaxInc = 0;
  //assign final increment by finding most frequent increment in samples array
  for (int i = 0; i < NumReeds; i++){ //for each sum of occurences
    if (IncrementCounter[i] > MaxCount){ //if the current sum is larger than the current largest
      MaxCount = IncrementCounter[i]; //replace the max count
      MaxInc = i; //the increment for that sample size is the most frequent
    }
  }

  IncNum = MaxInc; //assign the most frequent value of the Samples array to IncNum
  //Serial.println(IncNum);

  //Christmas Lights for when the pump is active
  if (ledcount < 50 && pumpstate == 1){
    led_write_rgb(0, rgb_green);
    led_write_rgb(1, rgb_red);
    led_write_rgb(2, rgb_white);
  }
  else if (ledcount < 100 && pumpstate == 1){
    led_write_rgb(0, rgb_red);
    led_write_rgb(1, rgb_white);
    led_write_rgb(2, rgb_green);      
  }
  else if (ledcount < 150 && pumpstate == 1){
    led_write_rgb(0, rgb_white);
    led_write_rgb(1, rgb_green);
    led_write_rgb(2, rgb_red);      
  }
  else {
    leds_off();
    led_write_rgb(1, rgb_blue);
  }
  ledcount = (ledcount + 1) %150;

  //turns pump on when increment is greater than thresh, only turns off at 0
  if ((IncNum >= Threshold)){
    PUMP_ENABLE();
    pumpstate = 1;
  }
  else if (IncNum <1){
    PUMP_DISABLE();
    pumpstate = 0;
  }  
}
