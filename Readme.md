## Projects for the STM32Nucleo-F4 developing board.

### Required tools

* GNU toolchain for  the ARM.
```
# Ubuntu
sudo apt install gcc-arm-none-eabi gdb-arm-none-eabi libnewlib-arm-none-eabi
#Arch Linux
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-gdb arm-none-eabi-newlib
```

* The stlink utility written by texane.
```
# Ubuntu
sudo apt-get install git build-essential libusb-1.0-0-dev libgtk-3-dev
# Arch Linux
sudo pacman -S libusb

git clone git://github.com/texane/stlink.git
cd stlink
make release
cd build/Release ; sudo make install
sudo ldconfig

sudo cp etc/udev/rules.d/49-stlinkv1.rules /etc/udev/rules.d
sudo cp etc/udev/rules.d/49-stlinkv2.rules /etc/udev/rules.d
sudo udevadm control --reload-rules
```

### How to build
```
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../stm32-cmake/cmake/gcc_stm32.cmake -DSTM32_FAMILY=F4 ..
make
```
