#ifndef I2C_H_
#define I2C_H_

void i2c_init (void);

uint8_t i2c_start (void);
uint8_t i2c_write(uint8_t data,uint8_t status_cmd);
uint8_t i2c_read(void);
void i2c_stop (void);

uint8_t i2c_wait_status (uint8_t u8status);

uint8_t i2c_read_buffer (uint8_t device_addr,uint8_t u32startAddr, uint8_t *u8ptr2arr, unsigned int u32len);
uint8_t i2c_write_buffer (uint8_t device_addr,uint8_t u32startAddr, uint8_t *u8ptr2arr, unsigned int u32len);

#endif /* I2C_H_ */
