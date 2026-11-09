# STM32F1 Peripheral Drivers

Bare-metal peripheral drivers for the **STM32F103C8T6 (Blue Pill)**, written in C from scratch using direct register access, with no HAL or LL libraries.

![Language](https://img.shields.io/badge/language-C-blue)
![MCU](https://img.shields.io/badge/MCU-STM32F103C8T6-green)
![IDE](https://img.shields.io/badge/IDE-STM32CubeIDE-informational)


## Table of Contents

- [Overview](#overview)
- [Supported Peripherals](#supported-peripherals)
- [Repository Structure](#repository-structure)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Getting Started](#getting-started)
- [Usage Example](#usage-example)
- [Driver API Reference](#driver-api-reference)
- [Roadmap](#roadmap)
- [Contributing](#contributing)


## Overview

This project is a collection of peripheral drivers for the STM32F1 series, built to understand how the microcontroller works at register level. It includes the MCU-specific header, peripheral drivers, startup code and linker script, so it can be built without ST's HAL.

## Supported Peripherals

| Peripheral | Driver files | Status |
|------------|--------------|--------|
| GPIO | `stm32f1xx_gpio_driver.c/.h` | Done |
| RCC / Clock | `stm32f1xx_rcc_driver.c/.h` | Done |
| EXTI / Interrupts | `stm32f1xx_exti_driver.c/.h` | Done |
| SPI | `stm32f1xx_spi_driver.c/.h` | Done |
| I2C | `stm32f1xx_i2c_driver.c/.h` | Done|
| USART | `stm32f1xx_usart_driver.c/.h` | Done |
| ADC | `stm32f1xx_adc_driver.c/.h` | In progress|
| Timers / PWM | `stm32f1xx_tim_driver.c/.h` | In progress|


## Repository Structure

```
stm32f1_drivers/
├── stm32f1xx_drivers/               # STM32CubeIDE project
│   ├── drivers/
│   │   ├── Inc/                     # Driver header files
│   │   │   ├── stm32f1xx.h          # MCU header (register maps, base addresses)
│   │   │   └── stm32f1xx_gpio_driver.h
│   │   └── Src/                     # Driver source files
│   │       └── stm32f1xx_gpio_driver.c
│   ├── Src/                         # Application code
│   │   ├── main.c
│   │   ├── syscalls.c
│   │   └── sysmem.c
│   ├── Startup/
│   │   └── startup_stm32f103c8tx.s  # Startup code and vector table
│   ├── STM32F103C8TX_FLASH.ld       # Linker script
│   ├── .project                     # CubeIDE project files
│   └── .cproject
├── .gitignore
├── LICENSE
└── README.md
```


## Hardware Requirements

- STM32F103C8T6 board (Blue Pill)
- ST-Link V2 programmer/debugger
- Jumper wires, breadboard, LED and resistor for the examples

## Software Requirements

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
- [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) for flashing

## Getting Started

**1. Clone the repository**

```bash
git clone https://github.com/<abhi98323>/stm32f1_drivers.git
```

**2. Import into STM32CubeIDE**

1. Open STM32CubeIDE.
2. Go to **File → Open Projects from File System...**
3. Click **Directory...** and select the `stm32f1xx_drivers` folder.
4. Click **Finish**.

**3. Build**

Right-click the project → **Build Project** (or press `Ctrl + B`).

**4. Flash and debug**

1. Connect the ST-Link to the Blue Pill (SWDIO, SWCLK, GND, 3.3V).
2. Click **Run** or **Debug** in CubeIDE.

## Usage Example

Blink the on-board LED on PC13:

```c
#include "stm32f1xx.h"
#include "stm32f1xx_gpio_driver.h"

static void delay(volatile uint32_t count)
{
    while (count--);
}

int main(void)
{
    GPIO_Handle_t led;

    led.pGPIOx = GPIOC;
    led.GPIO_PinConfig.GPIO_PinNumber = 13;
    led.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT_PP;
    led.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_SPEED_2MHZ;

    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&led);

    while (1)
    {
        GPIO_ToggleOutputPin(GPIOC, 13);
        delay(500000);
    }
}
```

## Driver API Reference

### GPIO

| Function | Description |
|----------|-------------|
| `GPIO_PeriClockControl(pGPIOx, state)` | Enable or disable the peripheral clock |
| `GPIO_Init(pGPIOHandle)` | Configure a pin (mode, speed, pull-up/down) |
| `GPIO_DeInit(pGPIOx)` | Reset the GPIO port registers |
| `GPIO_ReadFromInputPin(pGPIOx, pin)` | Read one input pin |
| `GPIO_ReadFromInputPort(pGPIOx)` | Read the whole input port |
| `GPIO_WriteToOutputPin(pGPIOx, pin, value)` | Write one output pin |
| `GPIO_ToggleOutputPin(pGPIOx, pin)` | Toggle one output pin |



## Roadmap

- [x] GPIO driver
- [x] RCC clock configuration
- [x] EXTI and NVIC interrupt handling
- [x] SPI driver
- [x] I2C driver
- [x] USART driver
- [ ] ADC driver
- [ ] Timer and PWM driver

## Contributing

Contributions, issues and feature requests are welcome.

1. Fork the repository
2. Create a branch: `git checkout -b feature/my-feature`
3. Commit your changes: `git commit -m "Add my feature"`
4. Push the branch: `git push origin feature/my-feature`
5. Open a Pull Request



## Author

**Abhishek Shete**
GitHub: [@abhi98323](https://github.com/abhi98323)
