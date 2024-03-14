# AAC-Clydespace Avionics Software Challenge
A driver for the LIS3MDLTR 3-Axis Magnetometer sensor. Dveloped according to details in datasheet
located at `doc/lism3mdl.pdf`<br>
The provided stub implementation in i2c.c was utilized to achieve the following functions.<br>
- Get the full-scale configuration
- Get and set the output data rate
- Enable or disable the interrupt pin
- Read the output data of a specified axis

## Pre-requisites

System should have a compiler installed and make installed. This was tested on a windows 10 machine with GCC and make installed.
Once these are installed, add the paths of compiler and make in environment variable.

## How to build
Git checkout the directory. Open CLI and navigate to the folder. Run make. A new folder named ' build' appears. Within the folder, an executable Challenge.exe can be found. To debug the exe, gdb can be used.

## Development
The function implementations are added in LIS3MDLTR.c. main.c is a sample applicaion to work with the APIs and the completed functions.<br>
lis3mdltr_init() must be invoked first to initialise the sensor. Configuration registers are written in this stage.<br>
lis3mdltr_get_fullscaleconfig() should be used to get the full scale configuration<br>
lis3mdltr_get_datarate() is used to get the current datarate.<br>
lis3mdltr_set_datarate() is used to set a new datarate <br>
lis3mdltr_get_output() is used to get the output data along a particular axis<br>
lis3mdltr_set_int() is used to enable/disable the interrupt pin<br>

## Extra Thoughts
If you have time, answer the following questions:
- What changes you would make to this interfaces for use in an RTOS
environment?<br>
- Prioritise tasks based on application
- Thread safe programming using mutexes or semaphores to ensure that resources are aavailable when needed
- Avoid unnecessary polling, wait or sleep calls and rely more on interrupt mechanisms

- How might the I2C API be improved
- A conditional logging mechanism can be implemented
- Unit tests using a mock unit can be implemented to avoid dependency on hardware
- The functions are incomplete. New functions to read bulk data or write bulk data should be implemented to make writing configurations easier or reading data of all axes easier.
