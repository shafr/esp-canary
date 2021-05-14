Import("env")
import platform

if platform.system()  == 'Windows':
    print("Replace MKSPIFFSTOOL with mklittlefs.exe")
    env.Replace (MKSPIFFSTOOL = "tools/mklittlefs.exe")
else:
    print("Replace MKSPIFFSTOOL with mklittlefs")
    env.Replace (MKSPIFFSTOOL = "tools/mklittlefs")