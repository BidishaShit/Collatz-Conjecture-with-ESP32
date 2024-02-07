# Exploring Collatz Conjecture with ESP32

## Project Overview

This project delves into the mathematics surrounding a puzzle introduced by Lothar Collatz in 1937. At its core, this conjecture is deceptively simple – begin with any positive integer; if it's even, halve it, and if it's odd, triple it and add 1. Repeat this process, and regardless of your starting point, the conjecture hints at an eventual convergence to the elusive number 1.

## Key Features

- **Sequential Exploration:** Let the ESP32 module methodically verify the sequence for numbers starting from 2^68. Traverse the patterns embedded in this numerical enigma.

- **Computational Insights:** Gain a subtle understanding of the ESP32's computational power by observing the time taken for verifying the Collatz Conjecture across different sets of numbers. This feature offers tangible insights into the device's computational efficiency.

- **BigNumbers Library Integration:** We implemented efficient handling of large numerical values within the Arduino environment through the discreet integration of the BigNumbers library. 

## Getting Started

### Hardware Essentials

- ESP32 module
- Arduino IDE

### Software Dependencies

- BigNumbers Library: https://github.com/nickgammon/BigNumber/

## Installation Guide

1. Clone the repository onto your local machine.

    ```bash
    git clone https://github.com/your-username/your-repository-name.git
    ```

2. Launch the Arduino IDE and load the project.

3. Upload the code to the ESP32 module.

## Usage Instructions

1. Connect the ESP32 module to your computer.

2. Open the Arduino IDE and load the project.

3. Tailor the code if necessary (e.g., adjust the range of numbers for verification).

4. Upload the code to the ESP32 module.

5. Observe the serial output to track the verification process and the time taken for each set of numbers.

## Computational Efficiency Insights

This project provides real-time glimpses into the computational efficiency of the ESP32 by unveiling the time required to verify the Collatz Conjecture for specific numerical ranges. Currently, it takes about 2.3x10^7 microseconds to verify 10,000 numbers. 

## Contributions

You are invited to contribute to the project by initiating discussions or submitting enhancements. Your valuable insights are warmly welcomed.


