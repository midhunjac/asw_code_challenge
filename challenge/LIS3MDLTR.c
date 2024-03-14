#include "LIS3MDLTR.h"
/**
 * @brief Initialize the sensor by writing proper values to the configuration registers.Returns STATUS_ERR in case operation failed or STATUS_OK if data was written successfully.
 * @param dev_addr : The device address. Depends on the way the SA1 pin is connected.
 *          LIS3MDL_InitStruct: Pointer to the structure that contains the configuration for all 5 registers.
*/
status_t lis3mdltr_init(int dev_addr, struct LIS3MDL_CntrlConf LIS3MDL_InitStruct)
{
  status_t err = STATUS_OK;
  err = i2c_write(dev_addr, LIS3MDL_CTRL_REG1, 1, &LIS3MDL_InitStruct.Register1);
  if(err == STATUS_ERROR)
    return err;
  err = i2c_write(dev_addr, LIS3MDL_CTRL_REG2, 1, &LIS3MDL_InitStruct.Register2);
  if(err == STATUS_ERROR)
    return err;
  err = i2c_write(dev_addr, LIS3MDL_CTRL_REG3, 1, &LIS3MDL_InitStruct.Register3);
  if(err == STATUS_ERROR)
    return err;
  err = i2c_write(dev_addr, LIS3MDL_CTRL_REG4, 1, &LIS3MDL_InitStruct.Register4);
  if(err == STATUS_ERROR)
    return err;
  err = i2c_write(dev_addr, LIS3MDL_CTRL_REG5, 1, &LIS3MDL_InitStruct.Register5);
  return err;

}

/**
 * @brief get the full scale configuration. Returns STATUS_ERR in case operation failed or STATUS_OK if data was read successfully.
 * @param dev_addr : Address of the sensor
 *          fullscaleconfig : pointer to the buffer in which the retrieved full scale configuration value is stored.
*/
status_t lis3mdltr_get_fullscaleconfig(int dev_addr, uint8_t *fullscaleconfig)
{
    uint8_t fs_config = 0;
    status_t err = STATUS_OK;
    err = i2c_read(dev_addr,LIS3MDL_CTRL_REG2, 1, &fs_config);
    *fullscaleconfig = fs_config & 0x60;
    return err;
}

/**
 * @brief Get the current datarate.Returns STATUS_ERR in case operation failed or STATUS_OK if data was read successfully
 * @param dev_addr: the device address
 *         datarate : pointer to the buffer where datarate is stored
*/
status_t lis3mdltr_get_datarate(int dev_addr, uint8_t *datarate)
{
    uint8_t dr_config;
    status_t err = STATUS_OK;
    err = i2c_read(dev_addr,LIS3MDL_CTRL_REG1, 1, &dr_config);
    *datarate = dr_config & 0x1C;
    return err;
}

/**
 * @brief Set the datarate.Returns STATUS_ERR in case operation failed or STATUS_OK if data was read successfully
 * @param dev_addr: the device address
 *          datrate : the new desired datarate
*/
status_t lis3mdltr_set_datarate(int dev_addr, uint8_t datarate)
{
    uint8_t dr_config;
    status_t err = STATUS_OK;
    err = i2c_read(dev_addr,LIS3MDL_CTRL_REG1, 1, &dr_config);
    if(err == STATUS_ERROR)
        return err;
    dr_config |= datarate;
    err = i2c_write(dev_addr,LIS3MDL_CTRL_REG1, 1, &dr_config);
    return err;
    
}

/**
 * @brief Get the output data of ny one axis. Returns STATUS_ERR in case operation failed or STATUS_OK if data was read successfully
 * @param dev_addr: the device address
 *        output : pointer to the location where the output data should be stored
 *        axis : The desired axis. Must be of type enum axis_name declared in LIS3MDLTR.h
*/
status_t lis3mdltr_get_output(int dev_addr, int *output,axis_name axis)
{
    uint8_t raw_data = 0;
    uint8_t ctrl_reg2 = 0;
    float sensitivity =0;
    uint8_t low_reg,high_reg;
    uint8_t low_data =0, high_data = 0;
    status_t err = STATUS_OK;
    switch(axis)
    {
        case 0:
            low_reg = LIS3MDL_OUTX_L;
            high_reg = LIS3MDL_OUTX_H;
            break;
        case 1:
            low_reg = LIS3MDL_OUTY_L;
            high_reg = LIS3MDL_OUTY_H;
            break;
        case 2:
            low_reg = LIS3MDL_OUTZ_L;
            high_reg = LIS3MDL_OUTZ_H;
            break;
    }

    err = i2c_read(dev_addr,low_reg, 1, &low_data);
    if(err == STATUS_ERROR)
        return STATUS_ERROR;
    err = i2c_read(dev_addr,high_reg, 1, &high_data);
    if(err == STATUS_ERROR)
        return STATUS_ERROR;
    raw_data = (uint16_t)high_data << 8 | (uint16_t)low_data;
    err = i2c_read(dev_addr,LIS3MDL_CTRL_REG2, 1, &ctrl_reg2);
    if(err == STATUS_ERROR)
        return STATUS_ERROR;
    switch(ctrl_reg2 & 0x60)
    {
        case LIS3MDL_FS_4_GA:
            sensitivity = LIS3MDL_SENSITIVITY_FOR_FS_4GA;
            break;
        case LIS3MDL_FS_8_GA:
            sensitivity = LIS3MDL_SENSITIVITY_FOR_FS_8GA;
            break;
        case LIS3MDL_FS_12_GA:
            sensitivity = LIS3MDL_SENSITIVITY_FOR_FS_12GA;
            break;
        case LIS3MDL_FS_16_GA:
            sensitivity = LIS3MDL_SENSITIVITY_FOR_FS_16GA;
            break;    
    }
    *output = (int16_t)(raw_data * sensitivity);
    return err;
}

/**
 * @brief Enable or Disable the interrupt pin
 * @param dev_addr : the devie address
 *         set : variable to choose whether to enable or disable interrupt pin. Set to true to enable the pin. False to disable the pin.
*/
status_t lis3mdltr_set_int(int dev_addr, bool set)
{
    status_t err = STATUS_OK;
    uint8_t enable = (set == true) ? 0x01: 0x00;
    uint8_t int_reg = 0;
    err = i2c_read(dev_addr,LIS3MDL_INT_CFG, 1, &int_reg);
    if(err == STATUS_ERROR)
        return err;
    int_reg |= enable;
    err = i2c_write(dev_addr,LIS3MDL_INT_CFG, 1, &int_reg);
    return err;
}



