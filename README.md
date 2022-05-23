![banner](.images/banner-dark-theme.png#gh-dark-mode-only)
![banner](.images/banner-light-theme.png#gh-light-mode-only)

# micro-ROS example for Mbed RTOS [EXPERIMENTAL]

This code has been tested in [Mbed v6.8](https://os.mbed.com/docs/mbed-os/v6.8), [Mbed v6.9](https://os.mbed.com/docs/mbed-os/v6.9) and [Mbed v6.10](https://os.mbed.com/docs/mbed-os/v6.10), with [ST B-L475E-IOT01A Discovery kit](https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/).

## Dependencies

If you do not have an ARM compiler you will need to install one:

```bash
sudo apt install gcc-arm-none-eabi
```

Make sure you have [all the mbed prerequisite software](https://os.mbed.com/docs/mbed-os/v6.15/build-tools/install-or-upgrade.html#prerequisite) installed on your computer.

This component needs `colcon` and other Python 3 packages in order to build micro-ROS packages:

```bash
sudo apt install python3-pip ninja-build
pip3 install catkin_pkg lark-parser empy colcon-common-extensions mbed-tools
```

These are optional:

```bash
pip3 install prettytable future jinja2 intelhex
```

## Add packages
Custom packages inside of the `extra_packages` folder will be included on the micro-ROS library build.
This allows the use of custom messages or other ROS packages.

To rebuild the microros lib after including new packages, you can run `make -f libmicroros.mk clean` before `mbed-tools compile`

## Example

In order to test a int32_publisher example:

```bash
mbed-tools deploy
mbed-tools compile -m DISCO_L475VG_IOT01A -t GCC_ARM -f
```

| Board                       | -m                  |
| ----------------------------| ------------------- |
| Arduino Portenta H7 M7 Core | PORTENTA_H7_M7      |
| Arduino Disco IOT           | DISCO_L475VG_IOT01A |

Is possible to use a micro-ROS Agent just with this docker command:

```bash
# Serial micro-ROS Agent
docker run -it --rm --net=host microros/micro-ros-agent:humble serial --dev [PORT] -v6
```

## Purpose of the Project

This software is not ready for production use. It has neither been developed nor
tested for a specific use case. However, the license conditions of the
applicable Open Source licenses allow you to adapt the software to your needs.
Before using it in a safety relevant setting, make sure that the software
fulfills your requirements and adjust it according to any applicable safety
standards, e.g., ISO 26262.

## License

This repository is open-sourced under the Apache-2.0 license. See the [LICENSE](LICENSE) file for details.

For a list of other open-source components included in ROS 2 system_modes,
see the file [3rd-party-licenses.txt](3rd-party-licenses.txt).

## Known Issues/Limitations

There are no known limitations.
