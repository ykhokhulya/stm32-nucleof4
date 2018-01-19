#include "../Temp_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

extern TEMP_DriverTypeDef DHT11_driver;

HAL_StatusTypeDef DHT11_init(TEMP_IOTypeDef* io);
int DHT11_read(TEMP_IOTypeDef* io, int8_t* t, int8_t* h);

void DHT11_IO_request(TEMP_IOTypeDef* io);
int DHT11_IO_read(TEMP_IOTypeDef* io, int8_t* t, int8_t* h);
void DHT11_IO_delay(uint32_t delay_us);

#ifdef __cplusplus
}
#endif
