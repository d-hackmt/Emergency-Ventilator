

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <Servo.h>
#include <LiquidCrystal_I2C.h>

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double BPM;
double servar;
LiquidCrystal_I2C lcd_I2C_0x27(0x27, 16, 2);
double currentTime = 0;
double lastTime = 0;
Servo servo_5;
double getLastTime(){
      return currentTime = millis()/1000.0 - lastTime;
}



void setup(){
    lcd_I2C_0x27.init();
    lcd_I2C_0x27.backlight();
    lcd_I2C_0x27.setBacklight( 1 );
    lcd_I2C_0x27.setCursor( (1) - 1, (1) - 1 );
    lcd_I2C_0x27.print( "Taiwan can Help!" );
    lcd_I2C_0x27.setCursor( (2) - 1, (2) - 1 );
    lcd_I2C_0x27.print( "EV-02 by Bio" );
    _delay(3);
    
    pinMode(A3,INPUT);
    pinMode(A2,INPUT);
    pinMode(A1,INPUT);
    servo_5.attach(5); // init pin
}

void loop(){
    
    lastTime = millis()/1000.0;
    lcd_I2C_0x27.clear();
    lcd_I2C_0x27.setCursor( (1) - 1, (1) - 1 );
    lcd_I2C_0x27.print( String("V:")+String((7) * (round(((analogRead(A3)) * (10)) / (1000)))) );
    lcd_I2C_0x27.setCursor( (6) - 1, (1) - 1 );
    lcd_I2C_0x27.print( String(" ET:")+String((1.5) + ((0.2) * (round(((analogRead(A2)) * (20)) / (1000))))) );
    lcd_I2C_0x27.setCursor( (1) - 1, (2) - 1 );
    lcd_I2C_0x27.print( String("SP:")+String((0) + ((0.21) * (round(((analogRead(A1)) * (10)) / (1000))))) );
    lcd_I2C_0x27.setCursor( (9) - 1, (2) - 1 );
    lcd_I2C_0x27.print( String("BPM:")+round((60) / (BPM)) );
    servo_5.write(110); // write to servo
    _delay((0.8) + ((0.2) * (round(((analogRead(A2)) * (20)) / (1000)))));
    servar = 110; 
    while(!((servar) < ((110) - ((7) * (round(((analogRead(A3)) * (10)) / (1000))))))) 
    {
        _loop();
        servo_5.write(servar); // write to servo
        _delay((0) + ((0.003) * (round(((analogRead(A1)) * (10)) / (1000)))));
        servar += -1;
    }
    _delay(1); 
    servo_5.write(110); 
    BPM = getLastTime();
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}
