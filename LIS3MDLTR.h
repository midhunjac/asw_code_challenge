/**
 ******************************************************************************
 * @file    lis3mdl.h
 * @author  MCD Application Team
 * @brief   LIS3MDL header driver file
 ******************************************************************************

 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIS3MDL__H
#define __LIS3MDL__H

#include <stdbool.h>
#include "./i2c/i2c.h"
/************** I2C Address *****************/
// Page 12 of datasheet specifies two device addresses. 
// Connct SDO/SA1 pin to VDD to set device address to LIS3MDL_I2C_ADDRESS_HIGH
// Connect SDO/SA1 pin to GND to set device address to LIS3MDL_I2C_ADDRESS_LOW


#define LIS3MDL_I2C_ADDRESS_LOW    ((uint8_t)0x38)  // SAD[0] = 0
#define LIS3MDL_I2C_ADDRESS_HIGH   ((uint8_t)0x3C)  // SAD[0] = 1

struct LIS3MDL_CntrlConf
{
    uint8_t Register1;
    uint8_t Register2;
    uint8_t Register3;
    uint8_t Register4;
    uint8_t Register5;
};

typedef enum
{
    X_axis,
    Y_axis,
    Z_axis
} axis_name;

/************** Who am I  *******************/

#define I_AM_LIS3MDL                        ((uint8_t)0x3D)

/************** Device Register  *******************/

#define LIS3MDL_WHO_AM_I_REG    0x0F
#define LIS3MDL_CTRL_REG1       0x20
#define LIS3MDL_CTRL_REG2       0x21
#define LIS3MDL_CTRL_REG3       0x22
#define LIS3MDL_CTRL_REG4       0x23
#define LIS3MDL_CTRL_REG5       0x24
#define LIS3MDL_STATUS_REG      0x27
#define LIS3MDL_OUTX_L          0x28
#define LIS3MDL_OUTX_H          0x29
#define LIS3MDL_OUTY_L          0x2A
#define LIS3MDL_OUTY_H          0x2B
#define LIS3MDL_OUTZ_L          0x2C
#define LIS3MDL_OUTZ_H          0x2D
#define LIS3MDL_TEMP_OUT_L      0x2E
#define LIS3MDL_TEMP_OUT_H      0x2F
#define LIS3MDL_INT_CFG         0x30
#define LIS3MDL_INT_SRC         0x31
#define LIS3MDL_INT_THS_L       0x32
#define LIS3MDL_INT_THS_H       0x33
  
/* Mag Temperature Sensor Control*/ 
#define LIS3MDL_TEMPSENSOR_ENABLE        ((uint8_t) 0x80)   /*!< Temp sensor Enable */
#define LIS3MDL_TEMPSENSOR_DISABLE       ((uint8_t) 0x00)   /*!< Temp sensor Disable */

/* Mag_XY-axis Operating Mode */ 
#define LIS3MDL_OM_XY_LOWPOWER           ((uint8_t) 0x00)
#define LIS3MDL_OM_XY_MEDIUM             ((uint8_t) 0x20)
#define LIS3MDL_OM_XY_HIGH               ((uint8_t) 0x40)
#define LIS3MDL_OM_XY_ULTRAHIGH          ((uint8_t) 0x60)
   
/* Mag Data Rate */ 
#define LIS3MDL_ODR_0_625_HZ             ((uint8_t) 0x00)  /*!< Output Data Rate = 0.625 Hz */
#define LIS3MDL_ODR_1_25_HZ              ((uint8_t) 0x04)  /*!< Output Data Rate = 1.25 Hz  */
#define LIS3MDL_ODR_2_5_HZ               ((uint8_t) 0x08)  /*!< Output Data Rate = 2.5 Hz   */
#define LIS3MDL_ODR_5_0_HZ               ((uint8_t) 0x0C)  /*!< Output Data Rate = 5.0 Hz   */
#define LIS3MDL_ODR_10_HZ                ((uint8_t) 0x10)  /*!< Output Data Rate = 10 Hz    */
#define LIS3MDL_ODR_20_HZ                ((uint8_t) 0x14)  /*!< Output Data Rate = 20 Hz    */
#define LIS3MDL_ODR_40_HZ                ((uint8_t) 0x18)  /*!< Output Data Rate = 40 Hz    */
#define LIS3MDL_ODR_80_HZ                ((uint8_t) 0x1C)  /*!< Output Data Rate = 80 Hz    */

#define LIS3MDL_ODR_ENABLE                ((uint8_t) 0x01<<1)  /*!< Enable fast_ODR   */


/* Mag Data Rate */ 
#define LMS303C_MAG_SELFTEST_DISABLE         ((uint8_t) 0x00)     
#define LMS303C_MAG_SELFTEST_ENABLE          ((uint8_t) 0x01)
   
/* Mag Full Scale */ 
#define LIS3MDL_FS_DEFAULT               ((uint8_t) 0x00)
#define LIS3MDL_FS_4_GA                  ((uint8_t) 0x00)  
#define LIS3MDL_FS_8_GA                  ((uint8_t) 0x20)
#define LIS3MDL_FS_12_GA                 ((uint8_t) 0x40)  
#define LIS3MDL_FS_16_GA                 ((uint8_t) 0x60)  /*!< Full scale = ±16 Gauss */

/* Mag_Reboot */ 
#define LIS3MDL_REBOOT_DEFAULT           ((uint8_t) 0x00)
#define LIS3MDL_REBOOT_ENABLE            ((uint8_t) 0x08)
   
/* Mag Soft reset */ 
#define LIS3MDL_SOFT_RESET_DEFAULT       ((uint8_t) 0x00)
#define LIS3MDL_SOFT_RESET_ENABLE        ((uint8_t) 0x04)
   
/* Mag_Communication_Mode */ 
#define LIS3MDL_SIM_4_WIRE               ((uint8_t) 0x00)
#define LIS3MDL_SIM_3_WIRE               ((uint8_t) 0x04)
   
/* Mag Lowpower mode config */ 
#define LIS3MDL_CONFIG_NORMAL_MODE       ((uint8_t) 0x00)
#define LIS3MDL_CONFIG_LOWPOWER_MODE     ((uint8_t) 0x20)
   
/* Mag Operation Mode */ 
#define LIS3MDL_CONTINUOUS_MODE          ((uint8_t) 0x00)
#define LIS3MDL_SELECTION_MODE           ((uint8_t) 0x03) /* CTRL_REG3 */
#define LIS3MDL_SINGLE_MODE              ((uint8_t) 0x01)
#define LIS3MDL_POWERDOWN1_MODE          ((uint8_t) 0x02)
#define LIS3MDL_POWERDOWN2_MODE          ((uint8_t) 0x03)

/* Mag_Z-axis Operation Mode */ 
#define LIS3MDL_OM_Z_LOWPOWER            ((uint8_t) 0x00)
#define LIS3MDL_OM_Z_MEDIUM              ((uint8_t) 0x04)
#define LIS3MDL_OM_Z_HIGH                ((uint8_t) 0x08)
#define LIS3MDL_OM_Z_ULTRAHIGH           ((uint8_t) 0x0C)   

/* Mag Big little-endian selection */ 
#define LIS3MDL_BLE_LSB                  ((uint8_t) 0x00)
#define LIS3MDL_BLE_MSB                  ((uint8_t) 0x02)

/* Fast read selection */
#define LIS3MDL_FAST_READ                ((uint8_t) 0x80)

/* Mag_Bloc_update_magnetic_data */ 
#define LIS3MDL_BDU_CONTINUOUS           ((uint8_t) 0x00)
#define LIS3MDL_BDU_MSBLSB               ((uint8_t) 0x40)
   
   
/* Magnetometer_Sensitivity */
#define LIS3MDL_SENSITIVITY_FOR_FS_4GA   ((float)0.14f)  /**< Sensitivity value for 4 gauss full scale  [mgauss/LSB] */
#define LIS3MDL_SENSITIVITY_FOR_FS_8GA   ((float)0.29f)  /**< Sensitivity value for 8 gauss full scale  [mgauss/LSB] */
#define LIS3MDL_SENSITIVITY_FOR_FS_12GA  ((float)0.43f)  /**< Sensitivity value for 12 gauss full scale [mgauss/LSB] */
#define LIS3MDL_SENSITIVITY_FOR_FS_16GA  ((float)0.58f)  /**< Sensitivity value for 16 gauss full scale [mgauss/LSB] */


/** Exported functions **/

status_t lis3mdltr_init(int addr, struct LIS3MDL_CntrlConf);
status_t lis3mdltr_get_fullscaleconfig(int addr, uint8_t *fullscaleconfig);
status_t lis3mdltr_get_datarate(int addr, uint8_t *datarate);
status_t lis3mdltr_set_datarate(int dev_addr, uint8_t datarate);
status_t lis3mdltr_get_output(int dev_addr, int *output, axis_name);
status_t lis3mdltr_set_int(int dev_addr, bool set);

#endif
