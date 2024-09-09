# Esp32-SSD1306-Simple-Menu-Framework

A simple framework designed to help you create a thread-safe menu interface for the SSD1306 OLED display using the ESP32 and FreeRTOS. This framework leverages FreeRTOS's task synchronization features, making it robust and efficient for handling multiple tasks, while ensuring the display remains responsive and reliable.

## Requirements

This project requires the SSD1306 driver, which can be found at:  
[SSD1306 Driver for ESP-IDF](https://github.com/nopnop2002/esp-idf-ssd1306)

Make sure you include this library in your project for proper functionality with the SSD1306 OLED display.

## Features

- **Thread-Safe Menu Framework**  
  The framework provides a thread-safe environment for creating and navigating menus on an OLED display. It ensures smooth task management and synchronization between various threads.

## File Overview

- **`ssd1306_final.c`**  
  This file contains the complete implementation of the menu framework for use with the SSD1306 OLED display. It includes functions for rendering menus, handling user inputs, and managing tasks.

## Usage

1. **For OLED Display Projects**  
   - Include the `ssd1306_final.c` file in your project's `main` directory.
   - Ensure the SSD1306 driver is installed and configured properly.
   - Use the provided functions to create and navigate your menu system.



## How to Integrate

- Clone or download the [SSD1306 driver](https://github.com/nopnop2002/esp-idf-ssd1306).
- Add the necessary source files (`ssd1306_final.c` or `ssd1306_normal_tasks_tested.c`) to your project.
- Modify your `CMakeLists.txt` file to include the selected source file.

## License

This project is open-source and available under the MIT License.

---

This framework simplifies the process of creating a thread-safe menu system, offering flexibility for both OLED and non-OLED projects using ESP-IDF and FreeRTOS.
