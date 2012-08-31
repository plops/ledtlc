#include <SPI.h>
// http://arduino.cc/forum/index.php?topic=70479.0;wap2
// https://bitbucket.org/spirilis/tlc5917
#include <TLC5917.h>

TLC5917 *t;
byte a=0xff,b=0x0a;

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
  t->writeLEDs(&a);
  pinMode(pin_mma,OUTPUT);
  pinMode(pin_lcos,OUTPUT);
  attachInterrupt(0,shutter_in,RISING);
}

volatile byte state=LOW;

void
shutter_in() // gets called 2ms before camera integrates
{
  state = !state;
  digitalWrite(pin_mma,state);
  digitalWrite(pin_lcos,!state);
}

byte c=0;

void
loop()
{
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
