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


