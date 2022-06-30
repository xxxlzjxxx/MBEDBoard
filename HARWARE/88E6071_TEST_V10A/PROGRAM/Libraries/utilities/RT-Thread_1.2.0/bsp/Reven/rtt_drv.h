#ifndef __RTT_DRV_H__
#define __RTT_DRV_H__

#include <rtdef.h>
#include <stdint.h>


#define NIOCTL_GET_PHY_DATA     (0x05)

#define RT_DEVICE_CTRL_BEEP_START           0x00
#define RT_DEVICE_CTRL_BEEP_STOP            0x01
#define RT_DEVICE_CTRL_SET_BEEP_FRQ         0x02

#define RT_DEVICE_CTRL_LED_ON           0x00
#define RT_DEVICE_CTRL_LED_OFF          0x01
#define RT_DEVICE_CTRL_LED_TOGGLE       0x02
#define RT_DEVICE_GET_LED_NUM           0x03

struct kinetis_spi_cs
{
    uint32_t ch;
};

struct at24cxx_attr
{
    const char* name;
    uint32_t total_size;    /* total size */
    uint16_t page_size;     /* page size */
    uint8_t  chip_addr;     /* base addr */
};

struct at24cxx_device
{
    struct rt_device                parent;
    struct rt_device_blk_geometry   geometry;
    struct rt_i2c_bus_device *      bus;
    struct rt_mutex                 lock;
    struct at24cxx_attr             attr;
};


int rt_hw_i2c_bit_ops_bus_init(const char *name);
int rt_hw_uart_init(const char *name, uint32_t instance);
void rt_hw_spi_init(void);
void rt_hw_sd_init(const char *name);
int rt_hw_spi_bus_init(void);
int rt_hw_rtc_init(void);
rt_err_t at24cxx_init(const char * device_name, const char * i2c_bus_name);
int rt_hw_enet_phy_init(void);
int rt_hw_dflash_init(const char *name);
int rt_hw_lcd_init(const char *name);
int rt_hw_pin_init(const char *name);
rt_err_t rt_hw_ads7843_init(const char * name, const char * spi_device_name);
rt_err_t w25qxx_init(const char * flash_device_name, const char * spi_device_name);


#endif
