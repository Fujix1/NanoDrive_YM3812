#include "FM.hpp"
extern "C" {
#include "lcd/lcd.h"
}
// Output Pins
#define D0 PC15
#define D1 PC14
#define D2 PC13
#define D3 PA0
#define D4 PA1
#define D5 PA2
#define D6 PA3
#define D7 PA4

#define WR PA11
//#define CS1_PIN PB4
#define A0 PA12
#define IC PB4
#define CS0_PIN PA8

// #define CS2_PIN PB5

#define WR_HIGH   (GPIO_BOP(GPIOA) = GPIO_PIN_11)
#define WR_LOW    (GPIO_BC(GPIOA)  = GPIO_PIN_11)
#define A0_HIGH   (GPIO_BOP(GPIOA) = GPIO_PIN_12)
#define A0_LOW    (GPIO_BC(GPIOA)  = GPIO_PIN_12)
#define IC_HIGH   (GPIO_BOP(GPIOB) = GPIO_PIN_4)
#define IC_LOW    (GPIO_BC(GPIOB)  = GPIO_PIN_4)

#define CS0_HIGH  (GPIO_BOP(GPIOA) = GPIO_PIN_8)  // HIGH
#define CS0_LOW   (GPIO_BC(GPIOA)  = GPIO_PIN_8)  // LOW
//#define CS1_HIGH  (GPIO_BOP(GPIOB) = GPIO_PIN_4)  // HIGH
//#define CS1_LOW   (GPIO_BC(GPIOB)  = GPIO_PIN_4)  // LOW
//#define CS2_HIGH (GPIO_BOP(GPIOB) = GPIO_PIN_5)  // HIGH
//#define CS2_LOW  (GPIO_BC(GPIOB)  = GPIO_PIN_5)  // LOW


void FMChip::begin() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  pinMode(WR, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(IC, OUTPUT);

  pinMode(CS0_PIN, OUTPUT);
  //pinMode(CS1_PIN, OUTPUT);
  //pinMode(CS2_PIN, OUTPUT);
}

void FMChip::reset(void) {
  CS0_LOW;
  // CS1_LOW;
  // CS2_LOW;
  Tick.delay_us(20);
  WR_HIGH;
  A0_LOW;
  IC_LOW;
  Tick.delay_us(100);  // at least 72 cycles // at 4MHz: 0.25us * 72 = 18us
  IC_HIGH;
  CS0_HIGH;
  // CS1_HIGH;
  // CS2_HIGH;
  Tick.delay_us(20);
}


void FMChip::set_register(byte addr, byte data, uint8_t chipno = CS0) {
  // LOW
  GPIO_BC(GPIOC) = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_BC(GPIOA) =
      GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0;
  // HIGH
  GPIO_BOP(GPIOC) =
      ((addr & 0b1) << 15) | ((addr & 0b10) << 13) | ((addr & 0b100) << 11);
  GPIO_BOP(GPIOA) = (addr & 0b11111000) >> 3;  // D3, D4 ,D5, D6, D7
  A0_LOW;
  CS0_LOW;

  /*
  switch (chipno) {
    case CS0:
      CS0_LOW;
      //CS1_HIGH;
      break;
    case CS1:
      CS0_HIGH;
      //CS1_LOW;
      break;
  }*/
  WR_LOW;
  Tick.delay_us(2);
  WR_HIGH;
  A0_HIGH;

  //---------------------------------------
  // data

  Tick.delay_us(3);  // At least 2

  // LOW
  GPIO_BC(GPIOC) = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_BC(GPIOA) =
      GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0;
  // HIGH
  GPIO_BOP(GPIOC) =
      ((data & 0b1) << 15) | ((data & 0b10) << 13) | ((data & 0b100) << 11);
  GPIO_BOP(GPIOA) = (data & 0b11111000) >> 3;

  WR_LOW;
  Tick.delay_us(3);
  WR_HIGH;

  CS0_HIGH;
  /*
  switch (chipno) {
    case CS0:
      CS0_HIGH;
      break;
    case CS1:
      //CS1_HIGH;
      break;
  }*/

  Tick.delay_us(16);
}

FMChip FM;
