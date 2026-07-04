#include "core/powerSave.h"
#include "core/utils.h"
#include <Arduino.h>
#include <Wire.h>
/*****************************************************************
** FT6336 Capacitive Touch Driver (I2C)
** Confirmed address: 0x38
** Pins: SDA=16, SCL=15 (Freenove FNK0104)
*****************************************************************/
#define FT6336_ADDR 0x38
#define FT6336_REG_STATUS 0x02
#define FT6336_REG_TOUCH1_XH 0x03
#define FT6336_REG_TOUCH1_XL 0x04
#define FT6336_REG_TOUCH1_YH 0x05
#define FT6336_REG_TOUCH1_YL 0x06

bool ft6336_readTouch(int16_t *x, int16_t *y) {
    Wire.beginTransmission(FT6336_ADDR);
    Wire.write(FT6336_REG_STATUS);
    if (Wire.endTransmission(false) != 0) { return false; }

    Wire.requestFrom(FT6336_ADDR, 5);
    if (Wire.available() < 5) { return false; }

    uint8_t status = Wire.read();
    uint8_t xh = Wire.read();
    uint8_t xl = Wire.read();
    uint8_t yh = Wire.read();
    uint8_t yl = Wire.read();

    uint8_t touchCount = status & 0x0F;
    if (touchCount == 0) { return false; }

    *x = ((xh & 0x0F) << 8) | xl;
    *y = ((yh & 0x0F) << 8) | yl;

    return true;
}

void ft6336_init() { delay(50); }
void _setup_gpio() {
    Wire.begin(16, 15); // SDA=16, SCL=15 — FT6336 touch controller
    ft6336_init();

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    bruceConfig.colorInverted = 0;
}

/***************************************************************************************
** Function name: _post_setup_gpio()
** Description:   second stage gpio setup to make a few functions work
***************************************************************************************/
void _post_setup_gpio() {
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
}

/***************************************************************************************
** Function name: getBattery()
** Description:   placeholder battery reading for this board
***************************************************************************************/
int getBattery() { return 0; }

/*********************************************************************
** Function: setBrightness
** set brightness value
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    if (TFT_BL < 0) return;
    if (brightval == 0) {
        analogWrite(TFT_BL, 0);
    } else {
        analogWrite(TFT_BL, map(brightval, 1, 100, 32, 255));
    }
}

/*********************************************************************
** Function: InputHandler
** Handles the variables PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
**********************************************************************/
void InputHandler(void) {
    static unsigned long tm = millis();
    if (!(millis() - tm > 200 || LongPress)) return;
    tm = millis();
    touchPoint.pressed = false;
}

/*********************************************************************
** Function: powerOff
** Turns off the device (or try to)
**********************************************************************/
void powerOff() {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, LOW);
    esp_deep_sleep_start();
}

/*********************************************************************
** Function: checkReboot
**********************************************************************/
void checkReboot() {}
/*****************************************************************
** Function name: _loop_gpio()
** Description:   runs continuously, updates touch state
*****************************************************************/
void _loop_gpio() {
    int16_t tx, ty;
    if (ft6336_readTouch(&tx, &ty)) {
        touchPoint.x = (uint16_t)tx;
        touchPoint.y = (uint16_t)ty;
        touchPoint.pressed = true;
    } else {
        touchPoint.Clear();
    }
}
