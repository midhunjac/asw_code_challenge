# AAC-Clydespace Avionics Software Challenge
A driver for the LIS3MDLTR 3-Axis Magnetometer sensor. Developed according to details in datasheet
located at `doc/lism3mdl.pdf`<br>
The ./main.c is an example application that outlines all the new functions and their usages<br>
The provided stub implementation in i2c.c was utilized to achieve the following functions.<br>
- Get the full-scale configuration
- Get and set the output data rate
- Enable or disable the interrupt pin
- Read the output data of a specified axis

## Pre-requisites

System should have a compiler installed and make installed. 
Once these are installed, add the paths of compiler and make in environment variable.
This was tested on a windows 10 machine with GCC and make installed.

## How to build
Open command line and type git clone https://github.com/midhunjac/asw_code_challenge.git
```
git clone https://github.com/midhunjac/asw_code_challenge.git
```
Navigate to the checked out folder. 
Run ./build.sh
```
./build.sh
```
A new folder named ' build' appears. Within the folder, an executable Challenge.exe can be found. To debug the exe, gdb can be used.

## Development
The function implementations are added in LIS3MDLTR.c. main.c is a sample applicaion to work with the APIs and the completed functions.<br>
lis3mdltr_init() must be invoked first to initialise the sensor. Configuration registers are written in this stage. LIS3MDL_CntrlConf is  structure that contains the configuration values for all registers<br>
```
struct LIS3MDL_CntrlConf
{
    uint8_t Register1;
    uint8_t Register2;
    uint8_t Register3;
    uint8_t Register4;
    uint8_t Register5;
};

lis3mdltr_init(int dev_addr, struct LIS3MDL_CntrlConf LIS3MDL_InitStruct)
```
lis3mdltr_get_fullscaleconfig() should be used to get the full scale configuration. it takes the device address and pointer to a locations as parameters<br>
```
lis3mdltr_get_fullscaleconfig(int dev_addr, uint8_t *fullscaleconfig)
```
lis3mdltr_get_datarate() is used to get the current datarate. This function take device address and pointer to a location as parameters<br>
```
lis3mdltr_get_datarate(int dev_addr, uint8_t *datarate)
```
lis3mdltr_set_datarate() is used to set a new datarate. This function needs the device address and the new datarate to be passed as value<br>
```
lis3mdltr_set_datarate(int dev_addr, uint8_t datarate)
```
lis3mdltr_get_output() is used to get the output data along a particular axis. This function takes device address,pointer to a location and the desired axis as its parameters. The axis should be of type axis_name.<br>
```
lis3mdltr_get_output(int dev_addr, int *output,axis_name axis)
```
lis3mdltr_set_int() is used to enable/disable the interrupt pin. This takes device address and a boolean variable as its parameters. Set the boolean variable to true to enable the interrupt. False to disable interrupt.<br>
```
lis3mdltr_set_int(int dev_addr, bool set)
```

## Extra Thoughts
1. What changes you would make to this interfaces for use in an RTOS
environment?<br>
- Prioritise tasks based on application
- Thread safe programming using mutexes or semaphores to ensure that resources are aavailable when needed
- Avoid unnecessary polling, wait or sleep calls and rely more on interrupt mechanisms

2. How might the I2C API be improved
- A conditional logging mechanism can be implemented
- Unit tests using a mock unit can be implemented to avoid dependency on hardware
- The functions are incomplete. New functions to read bulk data or write bulk data should be implemented to make writing configurations easier or reading data of all axes easier.
