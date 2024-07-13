# hal-core

**hal-core** is a Linux-based application designed for controlling CNC machines using POSIX real-time and non-real-time capabilities. 
It is currently under active development and has undergone testing on production machines.

## Specification

- Realtime hal layer to interact with kernel.
- Equipped with modules: ethercat, parport.
- 9-axis scurve motion planning.
- Opencascade cad interface.
- Qt gui interface.
- Enable 5 axis tooldir blending algoritme for a-axis, b-axis, c-axis.
- Enable tangential knife on c-axis.
- Enable plasma 3d cut compensation on a-axis, b-axis. 
- Manual mode, Auto mode.
- Reads gcode from file.
- Gcode editor.
- Uses no .ini file but a config tab instead.

![Screenshot](https://github.com/krcwrhvgyxzqelljes/hal-core/blob/master/app.jpg)

## Installation

### Prerequisites

Ensure your system meets the following requirements:
- Linux operating system

### Appimage cnc simulator
https://github.com/krcwrhvgyxzqelljes/hal-core/blob/master/appimage/runtest_cnc-x86_64.AppImage

### Steps
1. **Make the AppImage Executable**:  
   Open a terminal, navigate to the directory where you downloaded `runtest_cnc-x86_64.AppImage`, and make it executable:
   ```bash
   chmod +x /path/to/downloaded/runtest_cnc-x86_64.AppImage
	```
	
### Test video's
https://www.youtube.com/@michel3499

### Forum discussion's
https://forum.linuxcnc.org/38-general-linuxcnc-questions/50268-trajectory-planner-using-ruckig-lib

