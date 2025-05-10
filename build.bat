@echo off
setlocal enabledelayedexpansion

if not exist build (
    mkdir build
) else (
    pushd build
    for /d %%D in (*) do (
        if /I not "%%D"=="_deps" (
            rmdir /s /q "%%D"
        )
    )
    for %%F in (*) do (
        del /f /q "%%F"
    )
    popd
)

cd build

cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release

endlocal