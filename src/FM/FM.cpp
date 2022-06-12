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

#define WR PB5
#define CS1_PIN PB4
#define A0 PA12
#define IC PA11
#define CS0_PIN PA8

//#define CS2_PIN PB5

#define WR_HIGH   (GPIO_BOP(GPIOB) = GPIO_PIN_5)
#define WR_LOW    (GPIO_BC(GPIOB)  = GPIO_PIN_5)
#define A0_HIGH   (GPIO_BOP(GPIOA) = GPIO_PIN_12)
#define A0_LOW    (GPIO_BC(GPIOA)  = GPIO_PIN_12)
#define IC_HIGH   (GPIO_BOP(GPIOA) = GPIO_PIN_11)
#define IC_LOW    (GPIO_BC(GPIOA)  = GPIO_PIN_11)

#define CS0_HIGH  (GPIO_BOP(GPIOA) = GPIO_PIN_8)  // HIGH
#define CS0_LOW   (GPIO_BC(GPIOA)  = GPIO_PIN_8)  // LOW
#define CS1_HIGH  (GPIO_BOP(GPIOB) = GPIO_PIN_4)  // HIGH
#define CS1_LOW   (GPIO_BC(GPIOB)  = GPIO_PIN_4)  // LOW
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

void FMChip::write(byte data, byte chipno = CS1) {
  if ((data & 0x80) == 0) {
    if ((psgFrqLowByte & 0x0F) == 0) {
      if ((data & 0x3F) == 0) psgFrqLowByte |= 1;
    }
    writeRaw(psgFrqLowByte, chipno);
    writeRaw(data, chipno);
  } else if ((data & 0x90) == 0x80 && (data & 0x60) >> 5 != 3)
    psgFrqLowByte = data;
  else
    writeRaw(data, chipno);
}

void FMChip::writeRaw(byte data, byte chipno = CS1) {
  uint32_t data_bits = 0;
  CS0_LOW;
  /*
  switch (chipno) {
    case CS0:
      CS0_LOW;
      CS1_HIGH;
      // CS2_HIGH;
      break;
    case CS1:
      CS0_HIGH;
      CS1_LOW;
      // CS2_HIGH;
      break;
          case CS2:
            CS0_HIGH;
            CS1_HIGH;
            //CS2_LOW;
            break;
  }
  */

  WR_HIGH;

  //---------------------------------------
  // data
  if (data & 0b00000001) {
    data_bits += GPIO_PIN_15;
  }
  if (data & 0b00000010) {
    data_bits += GPIO_PIN_14;
  }
  if (data & 0b00000100) {
    data_bits += GPIO_PIN_13;
  }
  // LOW
  GPIO_BC(GPIOC) = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_BC(GPIOA) =
      GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0;

  // HIGH
  GPIO_BOP(GPIOC) = data_bits;
  GPIO_BOP(GPIOA) = (data & 0b11111000) >> 3;
  /*  if (data & 0b10000000) {
      GPIO_BOP(GPIOA) = GPIO_PIN_6;
    }*/
  // コントロールレジスタに登録するには WR_LOW → WR_HIGH 最低32クロック
  // 4MHz     :　0.25us   * 32 = 8 us
  // 3.579MHz :  0.2794us * 32 = 8.94 us
  // 3.5MHz   :  0.2857us * 32 = 9.14 us
  // 1.5MHz   :  0.66us   * 32 = 21.3 us
  WR_LOW;
  Tick.delay_us(9);
  WR_HIGH;
  CS0_HIGH;
  //CS1_HIGH;
  // CS2_HIGH;
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

  Tick.delay_us(20);
}

FMChip FM;
