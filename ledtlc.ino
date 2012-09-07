#include <SPI.h>
#include <avr/sleep.h>
// http://arduino.cc/forum/index.php?topic=70479.0;wap2
// https://bitbucket.org/spirilis/tlc5917
#include <TLC5917.h>

TLC5917 *t;
byte a=0xff,b=127;

byte
pin_shutter=2, // interrupt 0
pin_mma=3,
pin_lcos=4;

void setup()
{
  t= new TLC5917(1,13,10,9);
  t->begin();
  //t->config(.9,1);
  t->config(1,1);
  t->enable();
  t->writeLEDs(&b);
  pinMode(pin_shutter,INPUT);
  pinMode(pin_mma,OUTPUT);
  pinMode(pin_lcos,OUTPUT);
}

void shutter_in() {} // gets called 2ms before camera integrates

byte c=0;


void sleep_now()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(0,shutter_in,RISING);
  sleep_mode();  // this puts arduino to sleep
  sleep_disable();
  detachInterrupt(0); // first thing after wake-up
}

void
loop()
{
  sleep_now();
  //cli();
 // delayMicroseconds(2000-840);
  digitalWrite(pin_mma,HIGH);
  delayMicroseconds(50);
  digitalWrite(pin_mma,LOW);
  delayMicroseconds(940-396-50);
  digitalWrite(pin_lcos,HIGH);
  delayMicroseconds(396);
  t->enable();
 // delayMicroseconds(4000);
 // delayMicroseconds(300);
  
  digitalWrite(pin_lcos,LOW);
  
  delay(20);
  t->disable();
  //sei();
//  c++;
//  
//  if(c<128)   // change current for the leds
//    t->config(c/128.0,0);
//  else
//    t->config((c-128)/128.0,1);
//    
//  t->writeLEDs(&a); // one led is on, the other is off
//  delay(1);
//  t->writeLEDs(&b);
//  delay(2);
  //t->disable();
  //delay(20);
  //t->enable();
  //delay(20);
}
