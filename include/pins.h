#ifndef PINS_H
#define PINS_H


// Motor direction 
#define SOLENOID_DIR2_PIN   2
#define SOLENOID_DIR1_PIN   18
#define SOLENOID_EN_PIN     16

#define SOLENOID_EN_V       1
#define SOLENOID_DIS_V      0
#define SOLENOID_FREQ       200
#define SOLENOID_CHANNEL    0
#define SOLENOID_RESOLUTION 8
#define SOLENOID_HOLD_DUTY 64
#define SOLENOID_LATCH_DUTY 255


#define SOLENOID_PWM(duty)              ledcWrite(SOLENOID_CHANNEL, duty)
#define SOLENOID_ENABLE()               digitalWrite(SOLENOID_EN_PIN, SOLENOID_EN_V)
#define SOLENOID_DISABLE()              digitalWrite(SOLENOID_EN_PIN, SOLENOID_DIS_V)
#define SOLENOID_IS_ENABLED()           (digitalRead(SOLENOID_EN_PIN) == SOLENOID_EN_V ? true : false)

#define BUZZER_FREQ       2000
#define BUZZER_CHANNEL    2
#define BUZZER_RESOLUTION 8

#define BUZZER_PIN 4
#define BUZZER_PWM(duty)        ledcWrite(BUZZER_CHANNEL, duty)
#define BUZZER_DISABLE()        ledcWrite(BUZZER_CHANNEL, 0)


// Digital sensors 
#define LID_DET_N_PIN           14
#define OVERFLOW_DET_N_PIN      13
#define FILTER_DET_N_PIN        25
#define POD_DET_N_PIN           26
#define TANK_HIGH_N_PIN         32
#define TANK_LOW_N_PIN          39
#define CANISTER_DET_N_PIN      35

#define PRESSURE_ADC_PIN 36

#define PB_EVENT_PIN    27
#define PB_KILL_N_PIN   33 
#define PB_INT_N_PIN    19

#define PB_KILL_ENABLE()    digitalWrite(PB_KILL_N_PIN, LOW);
#define PB_KILL_DISABLE()   digitalWrite(PB_KILL_N_PIN, HIGH);


#define PUMP_EN_PIN 17
#define PUMP_ON_V 1
#define PUMP_OFF_V 0

#define PUMP_ENABLE()   digitalWrite(PUMP_EN_PIN, PUMP_ON_V);
#define PUMP_DISABLE()  digitalWrite(PUMP_EN_PIN, PUMP_OFF_V);
#define PUMP_IS_ON()    (digitalRead(PUMP_EN_PIN) == PUMP_ON_V ? true : false)


#define LED_DATA_PIN 23

#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22


#endif