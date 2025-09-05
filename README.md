SmartArray Command Pattern Project


**Description**
SmartArray is a flexible and extensible C++ project implementing a dynamic array container with a Command pattern interface. It supports operations such as adding, removing, printing, and clearing elements through modular commands. The project also features a command factory and parser integration to enable type-specific command behavior.


**Features**
- Template-based SmartArray container for generic data types.
- Command pattern with commands like Add, Pop, Print, Clear, and Help.
- Command factory for dynamic command creation.
- Parser integration for type-specific argument parsing and description.
- Local persistent storage: data saved to a binary file after every operation.
- Interactive CLI allowing command execution directly from the console.
- Built-in error handling for invalid inputs and command failures.


**Requirements**
- C++17 (or newer) compatible compiler.
- CMake (version 3.10 or higher recommended).
- Compatible with Windows, Linux, and macOS.


**Instalation**
1. Clone the repository:<br>
   git clone https://github.com/MikolajKos/SmartArrayProj.git<br>
   cd SmartArray

2. Build the project with CMake:<br>
   mkdir build<br>
   cd build<br> 
   cmake ..<br> 
   cmake --build . 

3. (Optional) To use the compiled executable globally from any terminal, add the executable directory to your system's environment PATH variable:<br>
   Windows:
   - Open System Properties -> Advanced -> Environment Variables.
   - Find and edit the Path variable.
   - Add the full path to your debug directory (e.g., C:\path\to\SmartArrayProj\SmartArray\build\Debug).
   - Restart your terminal or IDE.


**Usage**<br>
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
