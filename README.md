# TwinPhish-Framework

<p align="center">
  <img src="https://img.shields.io/badge/Project-TwinPhish--Framework-7c3aed?style=for-the-badge" alt="TwinPhish Framework">
  <img src="https://img.shields.io/badge/Platform-ESP8266-00979D?style=for-the-badge" alt="ESP8266">
  <img src="https://img.shields.io/badge/License-GPLv3-blue?style=for-the-badge" alt="GNU GPL v3 License">
  <img src="https://img.shields.io/badge/Mode-Authorized%20Awareness%20Lab-orange?style=for-the-badge" alt="Authorized Awareness Lab">
</p>

<p align="center">
  <b>An ESP8266-based WiFi security-awareness simulator for authorized training environments.</b>
</p>

---

## Overview

TwinPhish-Framework is an ESP8266 project for controlled WiFi security-awareness demonstrations, classroom labs, and authorized wireless-security assessments.

It helps instructors demonstrate how rogue access points, familiar SSIDs, deceptive captive portals, and legacy WiFi management-frame weaknesses can create security risks. The framework must only be used with written authorization, on equipment and networks that are owned or controlled by the test operator.

> **Important:** This project is intended for opt-in training. Do not collect, transmit, validate, retain, or display real WiFi passwords, personal information, session tokens, or other sensitive data.

---

## Safety Design

This repository should be configured as a **non-credential-collection awareness simulator**.

- Use a displayed consent notice before any participant joins the training access point
- Use a pre-shared lab code, acknowledgement button, or simulated input instead of a WiFi password field
- Do not compare submitted values with the real password of any network
- Do not store input values, even temporarily, unless they are non-sensitive, consented training responses
- Record only minimal training events such as timestamp, selected lab scenario, and acknowledgement status
- Clear all event data when the board restarts
- Conduct demonstrations only in an isolated lab or approved engagement scope

---

## Capabilities

TwinPhish-Framework provides the following authorized demonstration features:

- Nearby access-point discovery
- Local dashboard for selecting a **lab-owned** SSID
- Rogue-access-point awareness simulation using a controlled SSID
- Captive-portal awareness page with a clear training notice
- Optional legacy management-frame resilience demonstration
- In-memory display of non-sensitive training events
- Admin page for monitoring the lab scenario status
- Defensive lessons about WPA3, PMF / 802.11w, and suspicious WiFi portals

---

## Default Network

After flashing, the ESP8266 creates its own management access point.

| Setting | Default value |
|---|---|
| Management SSID | `TwinPhish-Framework` |
| Management password | `TwinPhish@123` |
| Dashboard | `http://192.168.4.1` |
| Admin panel | `http://192.168.4.1/admin` |

Change the default management SSID and password before using the device in a training environment.

---

## Hardware Requirements

- ESP8266-based development board compatible with the selected firmware build
- USB data cable
- Computer with Arduino IDE installed
- Correct USB-to-serial driver for the board
- Private lab router or isolated wireless environment
- Written authorization for all devices and networks in scope

---

## Installation

### 1. Install Arduino IDE

Download and install Arduino IDE from the official website:

- [Arduino IDE Download](https://www.arduino.cc/en/software)

### 2. Add board support

Open:

```text
File > Preferences
```

Under **Additional Boards Manager URLs**, add:

```text
https://raw.githubusercontent.com/SpacehuhnTech/arduino/main/package_spacehuhn_index.json
```

### 3. Install the board package

Open:

```text
Tools > Board > Boards Manager
```

Search for:

```text
deauther
```

Install a compatible ESP8266 board package for the hardware used in your authorized lab.

### 4. Flash the firmware

1. Download or clone this repository.
2. Open `TwinPhish_Framework-8.ino` in Arduino IDE.
3. Select the correct ESP8266 board under:

```text
Tools > Board
```

4. Select the connected device under:

```text
Tools > Port
```

5. Review the code and confirm that credential collection is disabled.
6. Upload the firmware and wait for the process to complete.

---

## Lab Workflow

### 1. Connect to management WiFi

1. Power on the flashed ESP8266 device.
2. Connect an instructor-controlled computer or phone to:

```text
SSID: TwinPhish-Framework
Password: TwinPhish@123
```

3. Open the local dashboard:

```text
http://192.168.4.1
```

4. Use the admin page for status monitoring:

```text
http://192.168.4.1/admin
```

Only the instructor or authorized lab operator should access the management interface.

### 2. Select a lab target

The ESP8266 scan list typically shows up to a limited number of nearby access points. Select only a router and SSID that are owned by the instructor or explicitly included in the written scope.

1. Wait for the scan results to load.
2. Refresh the dashboard if the expected lab SSID does not appear.
3. Verify the SSID, BSSID, and channel against the lab router.
4. Select the authorized lab target.

Do not select public, neighboring, school, workplace, or unknown networks.

### 3. Explain management-frame protection

The optional legacy deauthentication demonstration is relevant only in old or deliberately configured lab environments where Protected Management Frames (PMF / IEEE 802.11w) are not enabled.

- WPA3 requires PMF, so conventional spoofed deauthentication frames are generally ineffective.
- WPA2 networks with PMF enabled are also typically resistant.
- Modern clients may ignore this type of legacy test even on older infrastructure.
- The safest and preferred teaching method is an opt-in simulated disconnect or a verbal walkthrough rather than transmitting disruptive frames.

> Do not use deauthentication against networks or clients outside your approved lab scope. It can disrupt connectivity and may be illegal.

### 4. Start the awareness simulation

Start the Rogue AP / Evil-Twin **awareness simulation** only after participants have received a clear training notice and consented to the exercise.

The training page should:

- Clearly state that it is part of an authorized security-awareness exercise
- Ask participants to acknowledge the warning or enter a non-sensitive lab code
- Never request a real WiFi password
- Explain that unexpected WiFi portals should be treated as suspicious
- Direct participants to rejoin the legitimate lab network after completing the exercise

### 5. Participant experience

From the participant perspective, the approved exercise demonstrates the following sequence:

1. The participant receives notice that a controlled WiFi-awareness exercise is running.
2. The participant intentionally joins the labelled training access point.
3. A captive-portal-style page opens and displays a security-awareness message.
4. The participant sees a simulated router or firmware-update warning page.
5. The participant is asked to acknowledge the warning or enter a pre-distributed, non-sensitive training code.
6. An incorrect demo code returns the participant to the awareness page.
7. A correct demo code displays a completion message explaining the risks of untrusted portals.
8. The participant reconnects to the legitimate lab WiFi network.

This workflow teaches the security lesson without collecting any real credentials.

### 6. Admin event view

The `/admin` page should show only non-sensitive training telemetry, such as:

- Selected lab SSID
- Current lab scenario status
- Portal opened or acknowledgement received
- Training completion timestamp
- Number of completed awareness acknowledgements

Do not display passwords, typed input, client-identifying data, or other sensitive information.

### 7. Stop and reset

To stop the lab scenario:

- Open `http://192.168.4.1/admin` and stop the enabled module, or
- Restart the ESP8266 device.

Restarting clears volatile training-event data.

---

## Safe Validation Logic

Do **not** check submitted data against a real WiFi password.

For a safe lab, use a fixed, non-secret training code such as `LAB-ACK-2026`, distributed to participants before the exercise. The portal checks only whether the submitted training code equals that public lab value.

```text
If submitted value equals the non-sensitive training code:
    Mark the awareness exercise as completed
    Show a security-learning completion page
Else:
    Return to the awareness page
    Explain why entering credentials into unexpected portals is unsafe
```

Recommended safeguards:

- Do not use a real network password as the training code
- Do not log entered values
- Do not send entered values to a server
- Do not place passwords in serial logs, browser pages, or the admin dashboard
- Use a unique consented lab code for each class or session
- Reset the board after each training session

---

## Screenshots

The following images showcase the TwinPhish-Framework interface, including the dashboard, training portals, and administrative controls.

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

Use this project to reinforce the following defensive practices:

- Prefer WPA3 where supported
- Enable or require PMF / IEEE 802.11w
- Verify the SSID before joining a network
- Treat unexpected captive portals as suspicious
- Never enter WiFi passwords into unexpected web pages
- Disable automatic connection to untrusted WiFi networks
- Report suspicious access points to the network administrator
- Use enterprise wireless monitoring and intrusion-detection capabilities where appropriate

---

## Troubleshooting

### No networks appear

- Confirm that the ESP8266 supports WiFi scanning in your regulatory domain.
- Wait for the scan interval and reload the dashboard.
- Restart the device and reconnect to `TwinPhish-Framework`.
- Verify that the lab router is broadcasting its SSID.

### Firmware upload fails

- Confirm the correct board and serial port are selected.
- Use a USB cable that supports data transfer.
- Install the required USB-to-serial driver.
- Try a lower upload speed if the device is unstable.

### Legacy deauth has no effect

This is normal for modern WiFi equipment. WPA3 requires PMF, and WPA2 deployments may also enable PMF, preventing conventional spoofed management-frame tests.

Use a non-disruptive simulated event for awareness training unless your organization has approved an isolated legacy-resilience assessment.

### Captive portal does not open

- Confirm that the participant intentionally joined the labelled training AP.
- Open a browser and navigate to `http://192.168.4.1`.
- Ensure the exercise is being conducted on an isolated training setup.
- Do not configure the portal to impersonate a real organization or collect credentials.

---

## Responsible Use

By using TwinPhish-Framework, you agree to comply with all applicable laws, organizational policies, and authorization requirements.

Do not use this project to:

- Disrupt networks you do not own or administer
- Target public WiFi, schools, offices, neighbors, or commercial networks
- Collect passwords, personal data, session tokens, or confidential information
- Impersonate organizations to deceive non-consenting users
- Interfere with communications, safety systems, or emergency services
- Operate outside an approved testing scope

The authors and contributors accept no responsibility for misuse.

---

## Contributing

Contributions are welcome, especially improvements that strengthen safety, consent, defensive learning, and code quality.

1. Fork this repository.
2. Create a feature branch.
3. Make your changes.
4. Test only in an authorized environment.
5. Submit a pull request with a clear explanation.

Do not submit features intended to steal credentials, bypass security controls, or target unauthorized users.

---

## License

Copyright (C) 2026 Infomatic Labs.

TwinPhish-Framework is licensed under the **GNU General Public License v3.0 (GPL-3.0)**.

You may use, study, modify, and redistribute this software under the GPL-3.0. Distributed modified versions must remain under GPL-3.0 and include corresponding source code.

See the [LICENSE](LICENSE) file for the full license text.

---

## Support

If this project supports your authorized security-awareness program:

- Star the repository
- Report bugs through GitHub Issues
- Suggest safety and usability improvements
- Share responsible feedback with the maintainers

---

## ☕ Support Our Work

<div align="center">

```
╔════════════════════════════════════════════════════════════════╗
║                                                                ║
║   💡 Love TwinPhish-Framework?                                ║
║                                                                ║
║   Help us continue developing high-quality security-awareness ║
║   tools and resources. Your support fuels innovation!          ║
║                                                                ║
║   ⭐ Every star is appreciated!                               ║
║                                                                ║
╚════════════════════════════════════════════════════════════════╝
```

### Make a Contribution

Your donation directly supports:

🛡️ Enhanced security features
📚 Better documentation and examples
🔬 Advanced lab capabilities
🤝 Community support and improvements

### Donation Options

<div align="center">

[![Donate via PayPal](https://img.shields.io/badge/PayPal-💳%20Donate%20Now-0070ba?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/paypalme/infomaticgeeks)
[![Buy Me Coffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-☕%20Support%20Us-FFDD00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://buymeacoffee.com/abi.abinash)

</div>

Every contribution, no matter the size, makes a difference! 🙏

</div>
