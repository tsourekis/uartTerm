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