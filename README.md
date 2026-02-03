💡 **SmartArray Command Pattern Project**

## Description
SmartArray is a flexible and extensible C++ project implementing a dynamic array container with a Command pattern interface. It supports operations such as adding, removing, printing, and clearing elements through modular commands. The project also features a command factory and parser integration to enable type-specific command behavior.

## Docs
The entire documentation is generated with the help of Doxygen and is available online: 
https://mkosiorek.pl/docs/smart_array/html/index.html

## Features
- Template-based SmartArray container for generic data types.
- Command pattern with commands like Add, Pop, Print, Clear, and Help.
- Command factory for dynamic command creation.
- Parser integration for type-specific argument parsing and description.
- Local persistent storage: data saved to a binary file after every operation.
- Interactive CLI allowing command execution directly from the console.
- Built-in error handling for invalid inputs and command failures.


## Requirements
- C++17 (or newer) compatible compiler.
- CMake (version 3.10 or higher recommended).
- Compatible with Windows, Linux, and macOS.


## Installation & Build

### Prerequisites
* **Compiler:** C++17 compliant compiler.
    * *Windows:* **Microsoft Visual C++ (MSVC)** is recommended to fully utilize the built-in memory leak detection features.
* **Build System:** CMake (3.10+).

### Building form Source
1.  Clone the repository:
    ```bash
    git clone [https://github.com/MikolajKos/SmartArrayProj.git](https://github.com/MikolajKos/SmartArrayProj.git)
    cd SmartArray
    ```

2.  Create a build directory and compile:
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

3.  **Running the application:**
    For the automatic path detection to work correctly, run the executable directly from the `build` directory:
    ```bash
    .\sa.exe   # Windows
    ./sa       # Linux/macOS
    ```

*(Optional) Adding to PATH:*
To use the `sa` command globally, add the full path of your `build` directory to your system's Environment Variables.


## Usage
Run the executable from your terminal or command prompt. Commands are structured as follows:<br>
`sa <command> [arguments]`<br>
Where `sa` is program name

Example commands:
- Add a new element:<br>
  `sa add 123 John Doe "Team Lead" 25000 1987`
- Print all elements:<br>
  `sa print`
- Remove last element:<br>
  `sa pop`
- Remove all elements:<br>
  `sa clear`
- Get help informations:<br>
  `sa help`
- Get command description:<br>
  `sa help <command>`
