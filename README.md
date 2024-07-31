# <ins>The Powder Sim</ins>
High performant falling sand simulation made with OpenGL and C++.

# Controls:
	'1' - select Sand.
 	'2' - select Water.
  	'3' - select Stone.
   	 Left Mouse Button - place selected element.
     Right Mouse Button - erase elements.

# Windows
The build is not available at the moment.
<!--Windows build can be downloaded [here](https://github.com/NemGam/Snake/releases/download/v1.2.0/Pong.zip). Just unpack to any folder and run snake.exe. -->
# Linux
## Requirements
- CMake (version 3.13 or higher recommended)
- C++ Compiler: Compatible with C++17 standard
- Drivers support for OpenGL (version 3.3 and higher)

## Downloading
### Clone the repository:
	git clone https://github.com/NemGam/The-Powder-Sim
### Navigate to the project directory:
	cd ThePowderSim

## Building the Project
From the project root directory, generate the build system:

	cmake -S . -B build

Compile and install the project:

    cmake --build build && cmake --install build

### Running the Application
Execute the compiled application:

	./dist/bin/ThePowderSim
