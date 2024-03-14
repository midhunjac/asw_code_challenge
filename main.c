#include <stdio.h>
#include <stdint.h>
#include "LIS3MDLTR.h"

#define dev_addr LIS3MDL_I2C_ADDRESS_HIGH
int main()
{
    uint8_t fullscaleconfig = 0 ;
    uint8_t datarate = 0;
    uint8_t new_datarate = 0;
    int output = 0;
    axis_name axis = X_axis;
    status_t ret = STATUS_OK;
    struct LIS3MDL_CntrlConf LIS3MDL_InitStruct;

    /* Register 1 : Disable Temperature sensor[7] | medium performance X & Y mode[6-5] | Output data rate 80Hz[4-2] | High data rate enable [1] | Selftest enable [0]*/
    LIS3MDL_InitStruct.Register1 = LIS3MDL_TEMPSENSOR_DISABLE | LIS3MDL_OM_XY_MEDIUM | LIS3MDL_ODR_80_HZ |LIS3MDL_ODR_ENABLE| LMS303C_MAG_SELFTEST_ENABLE;

    /* Register 2: 0 [7] | Full scale configuration of 8 gauss [6-5] | 0 [4] | Reboot normally [3] | Configuration and user register reset[2]| 0 [1-0]*/
    LIS3MDL_InitStruct.Register2 = LIS3MDL_FS_8_GA | LIS3MDL_REBOOT_DEFAULT | LIS3MDL_SOFT_RESET_DEFAULT;

    /* Regiser 3: 0[7] | 0[6] | Normal Power mode [5] | 0 [4] | 0 [3] | SPI interface [2] | Continous conversion mode [1-0]*/
    LIS3MDL_InitStruct.Register3 = LIS3MDL_CONFIG_NORMAL_MODE | LIS3MDL_CONTINUOUS_MODE ;

    /*Register 4 : 0 [7-4] | Medium performace Z-axis [3-2] | Endianness - LSB at lower address [1] | 0 [0]*/
    LIS3MDL_InitStruct.Register4 = LIS3MDL_OM_Z_MEDIUM | LIS3MDL_BLE_LSB;

    /*Register 5 : Enable Fast read [7] | Update continously [6] | 0 [5-0]*/
    LIS3MDL_InitStruct.Register5 = LIS3MDL_FAST_READ | LIS3MDL_BDU_CONTINUOUS;
    
    ret = lis3mdltr_init(dev_addr,LIS3MDL_InitStruct); // Initialize the device with necessary parameters
    if(ret == STATUS_ERROR)
        printf("Failed to initiate device");

    ret = lis3mdltr_get_fullscaleconfig(dev_addr,&fullscaleconfig); // Read full scale configuration
    if(ret == STATUS_ERROR)
        printf("Failed to get full scale configuration");
    else
        printf("Full scale configuration is %d",fullscaleconfig);

    ret = lis3mdltr_get_datarate(dev_addr, &datarate); // Get the current output data rate
    if(ret == STATUS_ERROR)
        printf("Failed to get output data rate");
    else
        printf("Output data rate is %d", datarate);

    ret = lis3mdltr_set_datarate(dev_addr, new_datarate); //Update the registers with a new datarate
    if(ret == STATUS_ERROR)
        printf("Failed to update new datarate");

    ret = lis3mdltr_get_output(dev_addr,&output,axis); // Get the output data of any of X,Y or Z axis
    if(ret == STATUS_ERROR)
        printf("Failed to get output data");
    else
        printf("Output data for %d axis is %d",axis,output);

    ret = lis3mdltr_set_int (dev_addr, true); // Enable or disable interrupt pin. true to enable interrupts and false to disable interrupts
    if(ret == STATUS_ERROR)
        printf("Failed to set interrupt status");
        
    return 0;
}
