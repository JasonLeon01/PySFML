# PySFML

This project uses CMake, MingGW and pybind11 to bind SFML 3.0 with Python 3.9.

## Requirements

1. **Python 3.9**: This project requires Python 3.9. Make sure to have it installed on your system.
2. **SFML 3.0.0**: You need to have the `SFML-3.0.0` folder placed in the root of the project.
3. **pybind11**: You need to have the `pybind11-master` folder placed in the root of the project.
4. **Required DLLs**: After building the `.pyd` file, you need to ensure the following DLLs are present in the same directory as the `.pyd` file:
    - `dll from SFML/bin`
    - `python39.dll`
    - `libgcc_s_seh-1.dll`
    - `libstdc++-6.dll`
    - `libwinpthread-1.dll`

## Building the Project

### Step 1: Clone the Repositories

Ensure that the following folders are in your project directory:

- `SFML-3.0.0`: SFML 3.0 source files
- `pybind11-master`: pybind11 source files

You can download SFML from [here](https://www.sfml-dev.org/files/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit.zip), MinGW from [here](https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2.7z) and pybind11 from [here](https://github.com/pybind/pybind11).

### Step2: Generate libpython39.a
Find your path of python39.dll, and run the following command:
```sh
gendef python39.dll
dlltool -D python39.dll -d python39.def -l libpython39.a
```

### Step 3: Create the Build Directory

Open a terminal in the root directory of the project, and run:

```bash
mkdir build
cd build
```

### Step 4: Configure the Project with CMake
Run the following CMake command to configure the project:
```bash
cmake ..
```

### Step 5: Build the Project
Once the configuration is done, build the project using:
```bash
cmake --build .
```
This will generate the `pysf.pyd` file in the `build` directory.

### Step 6: Copy Required DLLs
After building the project, copy the necessary DLL files (dll from SFML/bin, python39.dll, libgcc_s_seh-1.dll, libstdc++-6.dll, libwinpthread-1.dll) into the directory where the .pyd file is located.

### Step 7: Using the Binding in Python
You can now import the SFML bindings in your Python project like this:
```python
import pysf
```
You should now be able to use SFML through Python.
