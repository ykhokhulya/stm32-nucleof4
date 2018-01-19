#include "../Lcd_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

extern LCD_DriverTypeDef HD44780_driver;

HAL_StatusTypeDef HD44780_init(LCD_IOTypeDef* io);
int16_t HD44780_getCols(LCD_IOTypeDef* io);
int16_t HD44780_getRows(LCD_IOTypeDef* io);
void HD44780_displayOn(LCD_IOTypeDef* io);
void HD44780_displayOff(LCD_IOTypeDef* io);
void HD44780_clear(LCD_IOTypeDef* io);
void HD44780_home(LCD_IOTypeDef* io);
void HD44780_cursor(LCD_IOTypeDef* io, int16_t cols, int16_t rows);
void HD44780_print(LCD_IOTypeDef* io, char ch);

void HD44780_IO_command(LCD_IOTypeDef* io, uint8_t cmd, int only_high_nibble);
void HD44780_IO_data(LCD_IOTypeDef* io, uint8_t data);
void HD44780_IO_writeNibble(LCD_IOTypeDef* io, uint8_t data);
void HD44780_IO_delay(uint32_t delay_us);

#ifdef __cplusplus
}
#endif
