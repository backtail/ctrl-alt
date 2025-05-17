# CTRL+ALT

CTRL+ALT is a modular firmware and hardware platform for STM8 microcontrollers, focused on real-time audio, control voltage (CV), and digital/analog signal processing.  
It is designed for experimentation, modular synths, and embedded control projects.

### Features

- Modular program structure: easily switch between different firmware "programs" (e.g., blinky, master clock, sample & hold, wavetable LFO)
- Real-time analog and digital I/O (ADC/DAC, GPIO)
- Hardware abstraction for STM8 peripherals
- Automated dependency management for STM8S standard library includes
- Build system integration with PlatformIO

### Directory Structure

- **src/**  
  Core source code, kernel, hardware abstraction, and user programs.
  - `kernel/` – Core hardware drivers and kernel logic
  - `programs/` – Individual firmware programs (e.g., blinky, master_clock)
- **include/**  
  Shared headers (for external libraries or cross-program use)
- **lib/**  
  Custom libraries and tools (e.g., waveform generation, constants)
- **scripts/**  
  Helper scripts for dependency management and build automation
- **docs/**  
  Documentation and generated HTML (Doxygen, formulas, etc.)
- **test/**  
  Test code and test plans

### Getting Started

#### Prerequisites

- [PlatformIO](https://platformio.org/) (for building and uploading firmware)
- STM8 toolchain (installed via PlatformIO)

#### Building

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/ctrl-alt.git
    cd ctrl-alt
    ```
2. Build the project:
    ```sh
    platformio run
    ```
3. Upload to your STM8 device:
    ```sh
    platformio run --target upload
    ```

#### Switching Programs

Each firmware "program" (e.g., blinky, master_clock) has its own configuration in `src/programs/<program>/config.h`.  
To build a different program, set the appropriate build flag in `platformio.ini` or use PlatformIO's environment system.

#### Dependency Management

The build system uses scripts in [`scripts/`](scripts/) to automatically generate STM8S configuration headers and resolve dependencies based on the selected program.

### Documentation

- Doxygen-generated docs are in [`docs/html/`](docs/html/)
- Additional documentation and formulas in [`docs/pages/`](docs/pages/)

### Contributing

Pull requests and issues are welcome!  
Please see [`docs/`](docs/) for more information on contributing and the code structure.

---

© 2024 CTRL+ALT Project

