# PySFML

This project uses CMake, MingGW(on Windows) and pybind11 to bind SFML 3.0 with Python 3.10.

## Requirements

1. **Python 3.10**: This project requires Python 3.10. Make sure to have it installed on your system.
2. **pybind11**: You need to have the `pybind11` folder placed in the root of the project.

### If you are using Windows
1. **Required DLLs**: After building the `.pyd` file, you need to ensure the following DLLs are present in the same directory as the `.pyd` file:
    - `msvcp140.dll`
    - `vcruntime140.dll`
    - `vcruntime140_1.dll`
2. **SFML source code**: You need to have the `SFML-3.0.0` folder placed in the root of the project.

### If you are using macOS
1. **SFML source code**: You need to have the `SFML-3.0.0` folder placed in the root of the project.

## Building the Project

### Step 1: Preparation
Install SFML, pybind11 in your folder.

Ensure that the following folders are in your project directory:

- `SFML-3.0.0`: SFML 3.0 source files
- `pybind11`: pybind11 source files

You can download pybind11 from [here](https://github.com/pybind/pybind11).

You can download SFML from [here](https://github.com/SFML/SFML/releases/tag/3.0.0#:~:text=SFML%2D3.0.0%2Dsources.zip).

### Step 2: Build the library

You can just run the `build.bat` or `build.sh` file to build the project.

If you want to build the project manually, follow these steps:

Open a terminal in the root directory of the project, and run:

```bash
mkdir build
cd build
```

Run the following CMake command to configure the project:

#### **If you are using Windows**
```bash
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release -- /m

```

#### **If you are using macOS**
```bash
cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_BUILD_TYPE=Release .. --trace-expand
cmake --build . -- -j$(sysctl -n hw.ncpu)
```

This will generate the `pysf.pyd/pysf.so` file in the `build` directory.

### Step 3: Copy Required DLLs(Windows only)
After building the project, copy the necessary DLL files into the directory where the .pyd file is located.

### Step 4: Using the Binding in Python
You can now import the SFML bindings in your Python project like this:

```python
import pysf
```

You should now be able to use SFML through Python.

## Related Repository
[PySFBoost](https://github.com/JasonLeon01/PySFBoost): Compiled pysf with pyi files and some enhancements. It's still under development. 
