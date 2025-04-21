# Mock Sensor Module (Radar)

This project provides a simple **Linux kernel module** simulating a mock radar sensor for ADAS (Advanced Driver Assistance Systems) applications.

## 🧩 Components

- **mock_radar.c**: Kernel module simulating radar data.
- **read_mock_radar.c**: User-space program to read data from the mock radar device.
- **Makefile**: For building the kernel module using `make`.

## 🔧 Build Instructions

```bash
make
```

## 📦 Load the Module

```bash
sudo insmod mock_radar.ko
dmesg | grep "Mock radar"
# Use the printed major number below:
sudo mknod /dev/mock_radar c <major_number> 0
```

## 📡 Read Radar Data

```bash
gcc read_mock_radar.c -o read_radar
./read_radar
```

## 🧹 Cleanup

```bash
sudo rmmod mock_radar
make clean
```