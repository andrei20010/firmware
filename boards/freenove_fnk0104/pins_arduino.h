#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#ifndef DEVICE_NAME
#define DEVICE_NAME "Freenove FNK0104"
#endif

// UART
static const uint8_t TX = 43;
static const uint8_t RX = 44;

// I2C touch / user interface
static const uint8_t SDA = 16;
static const uint8_t SCL = 15;

// Main SPI defaults (placeholder until TFT_eSPI setup is provided)
static const uint8_t SS = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 13;
static const uint8_t SCK = 12;

// Display pins from the Freenove FNK0104 setup header
#define TFT_MISO 13
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS 10
#define TFT_DC 46
#define TFT_RST -1
#define TFT_BL 45
#define TFT_BACKLIGHT_ON HIGH

// SPI pin aliases used by the firmware codebase
#define SPI_SCK_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SS_PIN 10

// SDMMC pins
#define USE_SD_MMC 1
#define PIN_SD_CLK 38
#define PIN_SD_CMD 40
#define PIN_SD_D0 39
#define PIN_SD_D1 41
#define PIN_SD_D2 48
#define PIN_SD_D3 47

// Touch configuration
#define HAS_TOUCH 1
#define TOUCH_CS -1
#define TOUCH_INTERRUPT -1

// Display config
#define HAS_SCREEN 1
#define ROTATION 1
#define TFT_HEIGHT 320
#define TFT_WIDTH 240
#define FP 1
#define FM 2
#define FG 3
#define MINBRIGHT 1

// Audio placeholders
#define I2S_MCLK_PIN 4
#define BCLK 5
#define WCLK 7
#define DOUT 8
#define AMP_ENABLE 1

// Misc defaults
#define LED_ON HIGH
#define LED_OFF LOW
#define BAD_TX -1
#define BAD_RX -1

#endif /* Pins_Arduino_h */
