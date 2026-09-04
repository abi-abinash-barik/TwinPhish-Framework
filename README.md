# TwinPhish-Framework 

<p align="center">
  <img src="https://img.shields.io/badge/Project-TwinPhish--Framework-7c3aed?style=for-the-badge" alt="TwinPhish Framework">
  <img src="https://img.shields.io/badge/Platform-ESP8266-00979D?style=for-the-badge" alt="ESP8266">
  <img src="https://img.shields.io/badge/License-GPLv3-blue?style=for-the-badge" alt="GNU GPL v3 License">
  <img src="https://img.shields.io/badge/Status-Research%20Project-orange?style=for-the-badge" alt="Research Project">
</p>

<p align="center">
  <b>An ESP8266-based wireless security awareness and authorized testing framework.</b>
</p>

---

## Overview

TwinPhish-Framework is an open-source ESP8266 project designed for controlled WiFi security demonstrations and authorized wireless-security assessments.

It provides a browser-based interface for exploring the risks posed by rogue access points, deceptive captive portals, and legacy WiFi management-frame weaknesses. The project is intended for training labs, classroom demonstrations, personal hardware, and environments where written authorization has been obtained.

> **Use this framework only on networks, access points, and devices that you own or are explicitly authorized to assess.**

---

## Capabilities

TwinPhish-Framework includes the following research and demonstration features:

- Nearby WiFi access-point discovery
- Target network selection through a local web interface
- Rogue access-point simulation using an Evil-Twin-style SSID
- Captive-portal demonstration for security-awareness testing
- Optional legacy deauthentication testing module
- Credential submission validation against the selected lab network
- In-memory result display through the local dashboard
- Concurrent operation of the rogue AP and legacy deauth testing functions

---

## Default Device Network

After flashing the firmware, the ESP8266 creates its own management access point.

| Setting | Value |
|---|---|
| Default SSID | `TwinPhish-Framework` |
| Default Password | `TwinPhish@123` |
| Management Address | `http://192.168.4.1` |
| Control Panel | `http://192.168.4.1/admin` |

For safer use, change these default values before deploying the project in a training environment.

---

## Modern WiFi Limitation

### Why deauthentication may fail

The deauthentication component is primarily relevant to **older WiFi devices and legacy WPA/WPA2 networks** where Protected Management Frames (PMF) are not enabled.

Modern routers and clients commonly support IEEE 802.11w, also called **Protected Management Frames**. PMF helps prevent spoofed deauthentication and disassociation frames by verifying that management frames are legitimate. PMF is mandatory in WPA3-certified networks, so traditional forged deauth frames are generally rejected by WPA3 and many newer WiFi devices.

### Expected behavior

| Network or device type | Expected deauth result |
|---|---|
| Older router with PMF disabled | May be susceptible during an authorized test |
| Legacy WPA/WPA2 environment | May be susceptible depending on client and AP configuration |
| WPA2 with PMF enabled | Usually resistant |
| WPA3 network | Expected to resist conventional forged deauth frames |
| Modern WiFi 6 / WiFi 6E devices | Usually resistant when PMF is active |

The Evil-Twin awareness demonstration does not depend on deauthentication. In a controlled lab, it can still be used to teach users why they should verify SSIDs, avoid entering passwords into unexpected captive portals, and prefer WPA3 with PMF enabled.

---

## Hardware Requirements

- ESP8266-based deauther-compatible development board
- USB data cable
- Computer with Arduino IDE installed
- Stable USB driver for your ESP8266 board
- A private lab network or written permission for any testing activity

> A regular ESP8266 board may require firmware adjustments depending on its chipset, flash size, antenna configuration, and board definition.

---

## Installation

### 1. Install Arduino IDE

Download and install the Arduino IDE from the official Arduino website.

### 2. Add the board repository

Open Arduino IDE and navigate to:

```text
File > Preferences
```

Under **Additional Boards Manager URLs**, add:

```text
https://raw.githubusercontent.com/SpacehuhnTech/arduino/main/package_spacehuhn_index.json
```

### 3. Install the board package

Navigate to:

```text
Tools > Board > Boards Manager
```

Search for:

```text
deauther
```

Install the compatible ESP8266 Deauther board package.

### 4. Open the project

1. Download or clone this repository.
2. Open the main `.ino` file using Arduino IDE.
3. Select the appropriate ESP8266 Deauther board from:

```text
Tools > Board
```

4. Select your device under:

```text
Tools > Port
```

5. Click **Upload** and wait for the firmware flashing process to complete.

---

## Using the Framework

### Connect to TwinPhish

1. Power on the flashed ESP8266 device.
2. From your computer or test phone, connect to:

```text
SSID: TwinPhish-Framework
Password: TwinPhish@123
```

3. Open the local dashboard:

```text
http://192.168.4.1
```

### Select a lab target

1. Allow the device to scan nearby wireless networks.
2. Refresh the dashboard if the access-point list does not immediately show the desired lab SSID.
3. Select only a network that is part of your authorized testing environment.

### Start an awareness test

Depending on the modules enabled in your build:

- Start the **Rogue AP / Evil-Twin demonstration** to create a lab clone of the selected SSID.
- Use the **legacy deauthentication test** only where you own the target network and are specifically evaluating its resistance to unprotected management frames.
- Monitor events and test submissions through the local interface.

### Stop and reset

To stop active modules:

- Open `http://192.168.4.1/admin` while connected to the device AP, or
- Restart the ESP8266 board.

Any captured demonstration data is held in volatile memory. Restarting or removing power from the device clears stored results.

---

## Screenshots

The following images showcase the TwinPhish-Framework interface and capabilities.

<p align="center">
  <img src="Screenshots/Screenshot (1).png" alt="TwinPhish Framework - Screenshot 1" width="600"> 
</p>

<p align="center">
  <img src="Screenshots/Screenshot (2).png" alt="TwinPhish Framework - Screenshot 2" width="600">
</p>

<p align="center">
  <img src="Screenshots/Screenshot (3).png" alt="TwinPhish Framework - Screenshot 3" width="600">
</p>

<p align="center">
  <img src="Screenshots/Screenshot (4).png" alt="TwinPhish Framework - Screenshot 4" width="600">
</p>

<p align="center">
  <img src="Screenshots/Screenshot (5).png" alt="TwinPhish Framework - Screenshot 5" width="600">
</p>

<p align="center">
  <img src="Screenshots/Screenshot (6).png" alt="TwinPhish Framework - Screenshot 6" width="600">
</p>

---

## Defensive Learning Outcomes

TwinPhish-Framework is best used to demonstrate practical WiFi defense concepts:

- Enable WPA3 where possible.
- Enable or require PMF / 802.11w on compatible infrastructure.
- Avoid joining unknown networks with familiar-looking SSIDs.
- Do not enter WiFi passwords into unexpected portal pages.
- Disable automatic connection to untrusted WiFi networks.
- Train users to report suspicious access points.
- Use wireless intrusion detection and monitoring in enterprise environments.

---

## Troubleshooting

### No networks appear in the dashboard

- Confirm that the ESP8266 supports scanning in your regulatory domain.
- Reload the web page after waiting for the scan interval.
- Restart the board and reconnect to `TwinPhish-Framework`.

### Firmware upload fails

- Confirm that the correct board and serial port are selected.
- Use a USB cable that supports data transfer, not only charging.
- Install the required USB-to-serial driver for your board.
- Try a lower upload speed if your board is unstable.

### The deauth module has no visible effect

This is expected on many modern networks. PMF protects deauthentication and disassociation frames, and WPA3 requires PMF support, making conventional deauth testing ineffective in many current environments.

For training purposes, use an isolated legacy test router where PMF is disabled and every participant has approved the exercise.

---

## Responsible Use

By using TwinPhish-Framework, you agree that you are responsible for complying with applicable laws, institutional policies, and authorization requirements.

Do not use this project to:

- Disrupt networks that you do not own
- Attempt to obtain passwords or personal information without permission
- Target public WiFi, offices, schools, neighbors, or commercial networks
- Interfere with communications or emergency services
- Conduct testing outside an approved lab or engagement scope

The authors and contributors accept no responsibility for misuse.

---

## Credits

TwinPhish-Framework is an independent educational project that acknowledges the wider open-source ESP8266 wireless-security research community.

The project has been informed by publicly available research and open-source work related to:

- ESP8266 Deauther projects
- Captive portal research
- Rogue access-point awareness demonstrations
- WiFi management-frame security research

---

## Contributing

Contributions are welcome.

If you would like to improve the project:

1. Fork this repository.
2. Create a feature branch.
3. Make your changes.
4. Test them in an authorized environment.
5. Open a pull request with a clear explanation.

Please do not submit code intended to bypass security controls, target unauthorized users, or facilitate illegal activity.

---

## License

Copyright (C) 2026 Infomatic Labs.

TwinPhish-Framework is free software: you can redistribute it and/or modify it under the terms of the **GNU General Public License version 3.0**, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but **WITHOUT ANY WARRANTY**; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

Distributed modified versions must remain licensed under GPL-3.0 and must provide the corresponding source code.

See the [`LICENSE`](LICENSE) file for the complete GNU General Public License v3.0 text.

---

## ☕ Support Our Work

<div align="center">


                                                                
   💡 Love TwinPhish-Framework?                                
                                                                
   Help us continue developing high-quality security tools     
   for pentesters and security researchers!                    
                                                                
   ⭐ Every star is appreciated!                               
                                                                


### Make a Contribution

Your donation directly supports:

🛡️ Enhanced security features
📚 Better documentation and examples
🔬 Advanced testing capabilities
🤝 Community support and improvements

### Donation Options

<div align="center">

[![Donate via PayPal](https://img.shields.io/badge/PayPal-💳%20Donate%20Now-0070ba?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/paypalme/infomaticgeeks)
[![Buy Me Coffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-☕%20Support%20Us-FFDD00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://buymeacoffee.com/abi.abinash)

</div>

Every contribution, no matter the size, makes a difference! 🙏

</div>

---

## Support

If this project helps your research, learning, or security-awareness program:

- Star the repository
- Report bugs through GitHub Issues
- Suggest improvements through feature requests
- Share responsible feedback with the project maintainers
