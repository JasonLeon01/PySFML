# PySFML

This project uses CMake, MingGW(on Windows) and pybind11 to bind SFML 3.0 with Python 3.10.

## Requirements

1. **Python 3.10**: This project requires Python 3.10. Make sure to have it installed on your system.
2. **pybind11**: You need to have the `pybind11-master` folder placed in the root of the project.

### If you are using Windows
1. **Required DLLs**: After building the `.pyd` file, you need to ensure the following DLLs are present in the same directory as the `.pyd` file:
2. **SFML 3.0.0**: You need to have the `SFML-3.0.0` folder placed in the root of the project.
    - `dll from SFML/bin`
    - `libgcc_s_seh-1.dll`
    - `libstdc++-6.dll`
    - `libwinpthread-1.dll`

### If you are using macOS
1. **SFML source code**: You need to have the `SFML-3.0.0` folder placed in the root of the project.

## Building the Project

### Step 1: Preparation
Install SFML, pybind11 in your folder.

Ensure that the following folders are in your project directory:

- `SFML-3.0.0`: SFML 3.0 source files
- `pybind11-master`: pybind11 source files

You can download pybind11 from [here](https://github.com/pybind/pybind11).

#### **If you are using Windows**

You can download SFML from [here](https://www.sfml-dev.org/files/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit.zip) and MinGW from [here](https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2.7z).

Find your path of python310.dll, and run the following command:
```sh
gendef python310.dll
dlltool -D python310.dll -d python310.def -l libpython310.a
```

#### **If you are using macOS**

You can download SFML from [here](https://github.com/SFML/SFML/releases/tag/3.0.0#:~:text=SFML%2D3.0.0%2Dsources.zip).

### Step2: Generate libpython310.a(Windows only)
Find your path of python310.dll, and run the following command:
```sh
gendef python310.dll
dlltool -D python310.dll -d python310.def -l libpython310.a
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
cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_BUILD_TYPE=Release .. --trace-expand
cmake --build .
```
This will generate the `pysf.pyd` file in the `build` directory.

### Step 5: Copy Required DLLs(Windows only)
After building the project, copy the necessary DLL files (dll from SFML/bin, libgcc_s_seh-1.dll, libstdc++-6.dll, libwinpthread-1.dll) into the directory where the .pyd file is located.

### Step 6: Using the Binding in Python
You can now import the SFML bindings in your Python project like this:
```python
import pysf
```
You should now be able to use SFML through Python.
