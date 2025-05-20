# ESP32 UWB Positioning and Sensor Integration System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

[English](#english) | [中文](#chinese)

<a name="english"></a>
## English

### Project Overview
This project implements a multi-sensor integration system based on ESP32, combining UWB (Ultra-Wideband) positioning technology with GPS and motion sensors. The system provides real-time distance measurement, location tracking, and motion detection capabilities, with data transmitted through WebSocket connections.

### Features
- **UWB Positioning**: Uses DW1000 modules for accurate indoor distance measurement
- **GPS Tracking**: Integrates TinyGPS Plus for outdoor location data
- **Motion Detection**: Implements MPU6050 accelerometer for motion and orientation sensing
- **Real-time Data Transmission**: Transfers sensor data via WebSocket protocol
- **Multi-tasking**: Utilizes FreeRTOS for efficient task management
- **Adaptive Sampling**: Dynamic sampling rate based on detected motion intensity

### Hardware Requirements
- ESP32 microcontroller
- DW1000 UWB module
- MPU6050 accelerometer
- GPS module (compatible with TinyGPS Plus)
- Appropriate power supply and connections

### Software Dependencies
- ArduinoJson
- WiFi libraries (WiFi, WiFiMulti, WiFiClientSecure)
- WebSocketsClient
- TinyGPSPlus
- DW1000 libraries
- Adafruit MPU6050 and Adafruit Sensor libraries
- Custom libraries:
  - send_json
  - websocket_conn

### Project Structure
```
.
├── .vscode                   # VS Code configuration
│   ├── extensions.json
│   └── settings.json
├── include                   # Header files
│   └── README
├── lib                       # Library dependencies
│   ├── Adafruit_MPU6050-2.2.6
│   ├── Adafruit_Sensor-1.1.14
│   ├── TinyGPSPlus_ESP32-0.0.2
│   ├── arduino-dw1000-0.9
│   ├── send_json             # Custom JSON utilities
│   └── websocket_conn        # WebSocket connection handling
├── src                       # Source files
│   └── main.cpp              # Main application code
├── test                      # Test files
├── .gitignore
├── example.cpp               # Example implementation
└── platformio.ini            # PlatformIO configuration
```

### Installation and Setup
1. Clone this repository
2. Open the project with PlatformIO in VS Code
3. Install all required libraries through PlatformIO
4. Configure your WiFi credentials in the code:
   ```cpp
   websocket_setup("YourWiFiSSID", "YourWiFiPassword", "ServerIP", ServerPort);
   ```
5. Compile and upload to your ESP32 device

### Usage Modes
The system can operate in two UWB modes:
- **Anchor Mode**: Fixed reference point for distance measurements
- **Tag Mode**: Mobile device that calculates distance from anchors

You can switch between modes by uncommenting the appropriate setup function.

### Tasks and Their Functions
- **GPS Task**: Continuously reads GPS data to update location
- **Status Task**: Periodically sends system status data
- **MPU6050 Task**: Collects accelerometer data with adaptive sampling rate
- **DW1000 Task**: Manages UWB distance measurements

### License
This project is licensed under the MIT License - see the LICENSE file for details.

### Contributors
- [TOU ITEI]

---

<a name="chinese"></a>
## 中文

### 项目概述
这是一个基于ESP32的多传感器集成系统，结合超宽带(UWB)定位技术、GPS和运动传感器。该系统提供实时距离测量、位置跟踪和运动检测功能，并通过WebSocket连接传输数据。

### 功能特点
- **超宽带定位**：使用DW1000模块进行精确的室内距离测量
- **GPS跟踪**：集成TinyGPS Plus用于户外位置数据采集
- **运动检测**：通过MPU6050加速度计实现运动和方向感应
- **实时数据传输**：通过WebSocket协议传输传感器数据
- **多任务处理**：利用FreeRTOS进行高效任务管理
- **自适应采样**：根据检测到的运动强度动态调整采样率

### 硬件需求
- ESP32微控制器
- DW1000超宽带模块
- MPU6050加速度计
- GPS模块（兼容TinyGPS Plus）
- 适当的电源和连接线

### 软件依赖
- ArduinoJson
- WiFi库（WiFi, WiFiMulti, WiFiClientSecure）
- WebSocketsClient
- TinyGPSPlus
- DW1000相关库
- Adafruit MPU6050和Adafruit Sensor库
- 自定义库：
  - send_json
  - websocket_conn

### 项目结构
```
.
├── .vscode                   # VS Code配置
│   ├── extensions.json
│   └── settings.json
├── include                   # 头文件
│   └── README
├── lib                       # 库依赖
│   ├── Adafruit_MPU6050-2.2.6
│   ├── Adafruit_Sensor-1.1.14
│   ├── TinyGPSPlus_ESP32-0.0.2
│   ├── arduino-dw1000-0.9
│   ├── send_json             # 自定义JSON工具
│   └── websocket_conn        # WebSocket连接处理
├── src                       # 源文件
│   └── main.cpp              # 主应用代码
├── test                      # 测试文件
├── .gitignore
├── example.cpp               # 示例实现
└── platformio.ini            # PlatformIO配置
```

### 安装和设置
1. 克隆此仓库
2. 使用VS Code中的PlatformIO打开项目
3. 通过PlatformIO安装所有必需的库
4. 在代码中配置您的WiFi凭据：
   ```cpp
   websocket_setup("您的WiFi名称", "您的WiFi密码", "服务器IP", 服务器端口);
   ```
5. 编译并上传到您的ESP32设备

### 使用模式
系统可以在两种UWB模式下运行：
- **锚点模式（Anchor）**：作为距离测量的固定参考点
- **标签模式（Tag）**：计算与锚点距离的移动设备

您可以通过取消注释适当的设置函数来切换模式。

### 任务及其功能
- **GPS任务**：持续读取GPS数据以更新位置
- **状态任务**：定期发送系统状态数据
- **MPU6050任务**：以自适应采样率收集加速度计数据
- **DW1000任务**：管理UWB距离测量

### 许可证
本项目采用MIT许可证 - 详情请参阅LICENSE文件。

### 贡献者
- [D WC]
