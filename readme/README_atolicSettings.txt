Enter the following settings in the project's properties to build a .bin file.
Otherwise, it will only produce a .elf file.

-----------------------------------------------------------------------------------

Project Properties ---> 

C/C++ Build -> Settings --> Tool Settings:

-> Output format: Tick "Convert build output" and select the "Binary" format

-----------------------------------------------------------------------------------

C/C++ Build -> Settings --> Build Steps:

Under "Post-build steps" add the following:

Command: arm-atollic-eabi-objcopy -O binary ${ProjName}.elf ${ProjName}.bin
Description: ${ProjName}

-----------------------------------------------------------------------------------


-----------------------------------------------------------------------------------
PROGRAMMING NOTES:
-------------------

Using ST-Link over USB in Ubuntu

From the terminal:

>> st-flash write "$(Path)/File.bin" 0x8000000 

example: st-flash write /home/aleko/codingWorkspace/uartTerm/Debug/uartTerm.bin 0x8000000 

Using ST-Flash over UART in Ubuntu

>> stm32-flash -w "${Path}/File.bin" -v -g 0x0 /dev/ttyXXX

example: stm32-flash -w /home/aleko/codingWorkspace/uartTerm/Debug/uartTerm.bin -v -g 0x0 /dev/ttyS0




