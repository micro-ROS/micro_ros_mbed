# micro-ROS example for Mbed RTOS

This code has been tested in [Mbed v6.8](https://os.mbed.com/docs/mbed-os/v6.8), [Mbed v6.9](https://os.mbed.com/docs/mbed-os/v6.9) and [Mbed v6.10](https://os.mbed.com/docs/mbed-os/v6.10), with [ST B-L475E-IOT01A Discovery kit](https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/).

## Dependencies

If you do not have an ARM compiler you will need to install one:

```bash
sudo apt install gcc-arm-none-eabi
```

This component needs `CMake` >= 3.19.
If required, you can install the latest cmake version with the following commands:

```bash
apt update
apt install -y git gcc-arm-none-eabi python3 python3-pip sudo git curl apt-transport-https ca-certificates gnupg software-properties-common wget ninja-build
# Get latest CMake
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'
apt update
apt install -y cmake
```

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

## Example

In order to test a int32_publisher example:

```bash
mbed-tools deploy
mbed-tools compile -m DISCO_L475VG_IOT01A -t GCC_ARM -f
```

Is possible to use a micro-ROS Agent just with this docker command:

```bash
# Serial micro-ROS Agent
docker run -it --rm --net=host microros/micro-ros-agent:rolling serial --dev [PORT] -v6
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
