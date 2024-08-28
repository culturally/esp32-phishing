# ESP32 Phishing - Fake WiFi Captive Portal

![ESP32 Phishing](https://1.bp.blogspot.com/-GuWilb37otg/XTe1FBKampI/AAAAAAAADe8/nLT2nCWXoD0mqk4-SD7yUHiod4jCyA2JQCLcBGAs/s400/ESP32-Module.png)

## Overview

ESP32 Phishing is a powerful tool designed to demonstrate potential security vulnerabilities in WiFi networks. The project leverages the ESP32 microcontroller to create a fake WiFi access point. When unsuspecting users connect to this deceptive network, they are redirected to an automatic captive portal. Any credentials submitted on this portal are saved locally on the ESP32 device at `172.0.0.1/pass`.

## Features

- **ESP32 Compatibility**: This project is specifically designed to work with ESP32 microcontrollers, expanding the possibilities for WiFi security testing.

- **Modified Captive Portal**: Inspired by Hugo's code [https://github.com/HUGOW04/FakeWifi/tree/main], the captive portal has been carefully modified to appear more convincing and realistic, increasing the chances of successful phishing attempts.

## Prerequisites

To set up the ESP32 Phishing project, you'll need the following:

- ESP32 Development Board
- Arduino IDE (or PlatformIO) with ESP32 support

## Installation

1. Clone the repository: `git clone https://github.com/culturally/esp32-phishing`

## Usage

1. Connect your ESP32 board to your computer.
2. Open the project in Arduino IDE or PlatformIO.
3. Configure the necessary settings such as SSID and password for the fake WiFi access point.
4. Flash the code to your ESP32 board.

## Important Note

**Please use this tool responsibly and only on networks that you have explicit permission to test. Unauthorized use of this tool is illegal and unethical.**

## Contributing

I welcome contributions from the community to enhance the project. If you have any suggestions, bug fixes, or new features, please feel free to submit a pull request.

## License

This project is licensed under the [MIT License](https://github.com/culturally/esp32-phishing/blob/main/LICENSE), which allows you to use, modify, and distribute the code freely. Refer to the License file for more details.

## Acknowledgments

We extend our gratitude to Hugo for inspiring this project with his work on ESP8266 WiFi phishing.

## Contact

If you have any questions or need further assistance, please feel free to contact us at [0day@yin.sh].
