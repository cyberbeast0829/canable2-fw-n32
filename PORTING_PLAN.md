# CANable2 固件移植方案：STM32G431 → N32H473

## 一、芯片对比总览

| 特性 | STM32G431C8T6 (原) | N32H473CEU7 (目标) |
|------|---------------------|---------------------|
| **内核** | Cortex-M4F | Cortex-M4F |
| **最高主频** | 170 MHz | 240 MHz |
| **Flash** | 128 KB | 512 KB |
| **SRAM** | 32 KB | ~128 KB (含TCM) |
| **CAN** | FDCAN1 | FDCAN1 / FDCAN2 |
| **USB** | USB Device + CRS | USBFS Device |
| **HAL 风格** | STM32 HAL (`HAL_xxx`) | Nations HAL (类STM32，不同命名) |
| **封装** | LQFP48 | QFN48 (需确认引脚) |

---

## 二、硬件引脚映射（待确认）

CANable2 原版使用以下引脚，需要在 N32H473 上找到对等引脚：

| 功能 | STM32G431 引脚 | 说明 | N32H473 建议引脚 |
|------|---------------|------|------------------|
| CAN_RX | PB8 (FDCAN1_RX) | CAN 接收 | PB8 / PB5 等 (FDCANx_RX) |
| CAN_TX | PB9 (FDCAN1_TX) | CAN 发送 | PB9 / PB6 等 (FDCANx_TX) |
| CAN_STB | PA0 | 收发器待机控制 | 任意 GPIO |
| CAN_PWR | PC13 | CAN IO 电源控制 | 任意 GPIO |
| LED_BLUE | PA15 | 蓝色 LED | 任意 GPIO |
| LED_GREEN | PB11 | 绿色 LED | 任意 GPIO |
| USB_DM | PA11 | USB D- | PA11 (固定) |
| USB_DP | PA12 | USB D+ | PA12 (固定) |
| SWCLK | PA14 | 调试 | PA14 (固定) |
| SWDIO | PA13 | 调试 | PA13 (固定) |

> ⚠️ **重要**: 实际引脚分配需根据 N32H473CEU7 的 Datasheet 和硬件板卡设计确定。

---

## 三、移植工作分解（9大模块）

### 模块 1：HAL 库替换

**当前**: STM32G4xx HAL Driver (`Drivers/STM32G4xx_HAL_Driver/`)  
**目标**: N32H47x_48x HAL Driver（来自 Nation 官方 SDK）

**需替换的 HAL 模块**:
- `stm32g4xx_hal.c` → N32 HAL 核心
- `stm32g4xx_hal_rcc.c` / `_ex.c` → N32 RCC 时钟模块
- `stm32g4xx_hal_gpio.c` → N32 GPIO 模块
- `stm32g4xx_hal_fdcan.c` → N32 FDCAN 模块
- `stm32g4xx_hal_cortex.c` → N32 NVIC/系统模块
- `stm32g4xx_hal_flash.c` → N32 Flash 模块
- `stm32g4xx_hal_pwr.c` / `_ex.c` → N32 电源模块
- `stm32g4xx_hal_pcd.c` → ~~USB用N32 USB库替代~~

**操作**:
1. 从 Nation SDK 复制 `n32h47x_48x.h`、`n32h47x_48x_conf.h` 及所有 HAL 源文件
2. 替换 CMSIS → Nation 提供的 CMSIS Core（通常兼容，直接用 ARM 官方即可）
3. 删除旧的 `Drivers/STM32G4xx_HAL_Driver/`

---

### 模块 2：启动文件 + 系统初始化

**需改文件**:
- `src/startup_stm32g431xx.s` → 替换为 N32H47x 的 GCC 启动文件
- `src/system_stm32g4xx.c` → 替换为 `system_n32h47x_48x.c`（参考 ODrive）

**关键差异**:

| 项目 | STM32G431 | N32H473 |
|------|-----------|---------|
| 中断向量表 | 102 个条目 | 约 100+ 条目（不同映射） |
| SystemCoreClock | 170 MHz | 240 MHz |
| 时钟源 | HSI16 + PLL | HSE + PLL（推荐）或 HSI + PLL |
| Flash 等待周期 | FLASH_LATENCY_8 | 对应 240MHz 的等待周期 |
| 电压调节 | `HAL_PWREx_ControlVoltageScaling` | `PWR_CTRL_PLS_LVLx` |

**参考文件** (ODrive):
- `ODrive/Firmware/Board/v3/Src/system_n32h47x_48x.c` — 时钟配置
- Nation SDK 中的 `startup_n32h47x_48x.s`

---

### 模块 3：FDCAN 驱动适配

**需改文件**: `src/can.c`、`inc/can.h`

**STM32 HAL API → N32 HAL API 映射**:

| STM32 原 API | N32 对应 API | 说明 |
|-------------|-------------|------|
| `HAL_FDCAN_Init()` | `FDCAN_Init()` | 初始化 |
| `HAL_FDCAN_Start()` | `FDCAN_Start()` | 启动 |
| `HAL_FDCAN_Stop()` | `FDCAN_Stop()` / `FDCAN_DeInit()` | 停止 |
| `HAL_FDCAN_GetTxFifoFreeLevel()` | `FDCAN_GetTxFifoFreeLevel()` | 发送 FIFO 空闲 |
| `HAL_FDCAN_AddMessageToTxFifoQ()` | `FDCAN_TransmitToTxFifoQ()` | 发送消息 |
| `HAL_FDCAN_GetRxMessage()` | `FDCAN_ReceiveMsgFromRxFifo0()` | 接收消息 |
| `FDCAN_HandleTypeDef` | `FDCAN_InitType` | 句柄结构体 |
| `FDCAN_TxHeaderTypeDef` | `FDCAN_TxHeaderType` | 发送帧头 |
| `FDCAN_RxHeaderTypeDef` | `FDCAN_RxHeaderType` | 接收帧头 |
| `__HAL_RCC_FDCAN_CLK_ENABLE()` | `RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_FDCAN1/2, ENABLE)` | 时钟使能 |
| `GPIO_AF9_FDCAN1` | `GPIO_AF_FDCANx_RX/TX` | GPIO 复用 |

**FDCAN 初始化差异（重要！）**:

N32H473 的 FDCAN 需要在 **用户指定的 RAM 区** 分配消息缓冲：
```c
// N32 FDCAN 必须手动分配 RAM 缓冲
uint32_t FDCAN_ram[1024];           // 1024 words 的 CAN 消息 RAM
FDCAN_MsgRamType Node_msg;          // 消息 RAM 布局描述

FDCAN_InitType hcan = {
    .MsgRamStrAddr = (uint32_t)FDCAN_ram,  // 缓冲区首地址
    .MsgRamOffset = 0,
    .pMsgInfo = &Node_msg,
    .StdFilterSize = 4,              // 标准滤波器数量
    .ExtFilterSize = 4,              // 扩展滤波器数量
    .RxFifo0Size = 8,                // RX FIFO0 深度
    .RxFifo0DataSize = FDCAN_DATA_BYTES_64,
    .TxFifoQueueSize = 8,            // TX FIFO 深度
    // ...
};
```

STM32G4 的 FDCAN 通过 `HAL_FDCAN_Init()` 自动管理 RAM 缓冲，N32 则需要显式管理。

**CAN 位时序计算注意**：
- STM32G431：CAN 时钟 = PCLK1 (170MHz)，`ClockDivider = FDCAN_CLOCK_DIV1`
- N32H473：CAN 时钟通过 PLL 独立产生，需调用 `RCC_ConfigFDCANPllClk()` 设置分频
  ```c
  RCC_ConfigFDCANPllClk(RCC_FDCAN_PLLSRC_DIV6);  // 240M / 6 = 40M
  RCC_ConfigFDCANClksrc(RCC_FDCAN_CLKSRC_PLL);
  ```
- 所有 Prescaler 值需要基于新的 CAN 时钟频率重新计算！

---

### 模块 4：USB CDC 驱动适配

**需改文件**: `src/usbd_cdc_if.c`、`src/usb_device.c`、`src/usbd_conf.c`、`src/usbd_desc.c`

**STM32 USB 库 → N32 USB 库映射**:

| STM32 原组件 | N32 对应组件 | 说明 |
|-------------|-------------|------|
| `USBD_HandleTypeDef` | N32 USBFS 句柄（不同结构） | USB 设备句柄 |
| `USBD_CDC_ItfTypeDef` | N32 的 CDC 接口回调（不同结构） | CDC 接口 |
| `USBD_CDC_SetTxBuffer()` | `USB_Send_DATA()` | 发送数据 |
| `USBD_CDC_SetRxBuffer()` | `USB_Receive_DATA()` | 接收准备 |
| `USBD_CDC_ReceivePacket()` | N32 USB 的接收方式不同 | 接收 |
| `CDC_DATA_FS_MAX_PACKET_SIZE` | `VIRTUAL_COM_PORT_DATA_SIZE` (64) | 包大小 |
| `HAL_PCD_IRQHandler()` | N32 对应的 USB 中断处理 | 中断处理 |

**N32 USB 初始化参考** (来自 ODrive `usb.c`):
```c
void MX_USB_Init(void) {
    // 1. 配置 USB 时钟: PLL → Prescaler → USBFS 48MHz
    RCC_ConfigUSBFSClk(RCC_USBFS_CLKSRC_PLLPRES);
    RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV5);
    RCC->CFG3 |= RCC_CFG3_USBFSTM;
    
    // 2. 使能时钟
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USBFS, ENABLE);
    
    // 3. 配置 GPIO (PA11=DM, PA12=DP, AF10)
    // 4. 配置 NVIC (USB_FS_LP_IRQn, USB_FS_WKUP_IRQn)
    // 5. 配置 EXTI Line18 (USB Wakeup)
    // 6. USB_Init()
}
```

**N32 USB 库头文件**:
```c
#include "usbfsd_lib.h"     // USB Full Speed Device 库
#include "usbfsd_type.h"
#include "usbfsd_regs.h"
#include "usbfsd_mem.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
```

**STM32G4 的 CRS 功能**：STM32G4 用 CRS 将 HSI48 校准到 USB SOF，N32H473 不支持此功能。N32 直接使用 PLL 生成的 48MHz，精度由外部晶体 HSE 保证。

---

### 模块 5：GPIO/LED 适配

**需改文件**: `src/led.c`、`inc/led.h`

**API 变化**:

| STM32 原 API | N32 对应 API |
|-------------|-------------|
| `HAL_GPIO_Init(GPIOx, &init)` | `GPIO_InitPeripheral(GPIOx, &init)` |
| `HAL_GPIO_WritePin(PORT, PIN, val)` | `GPIO_WriteBit(PORT, PIN, val)` 或 `GPIO_SetBits`/`GPIO_ResetBits` |
| `GPIO_InitTypeDef` | `GPIO_InitType` |
| `GPIO_PIN_x` | `GPIO_PIN_x` (兼容) |
| `GPIO_MODE_OUTPUT_PP` | `GPIO_MODE_OUTPUT_PP` (兼容) |
| `__HAL_RCC_GPIOA_CLK_ENABLE()` | `RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA, ENABLE)` |
| `HAL_GetTick()` | 需实现 SysTick (参考原 firmware) |

**N32 GPIO 结构体字段差异**:
```c
// N32 GPIO_InitType 比 STM32 多两个字段
GPIO_InitType gpio = {
    .Pin = GPIO_PIN_0,
    .GPIO_Mode = GPIO_MODE_OUTPUT_PP,
    .GPIO_Pull = GPIO_PULL_UP,
    .GPIO_Current = GPIO_DC_2mA,      // 驱动电流 (N32 新增)
    .GPIO_Slew_Rate = GPIO_SR_SLOW,   // 压摆率 (N32 新增)
    .GPIO_Alternate = 0,
};
GPIO_InitPeripheral(GPIOA, &gpio);
```

---

### 模块 6：中断处理适配

**需改文件**: `src/interrupts.c`

**中断向量差异**:

| STM32G431 IRQ | N32H473 IRQ |
|--------------|-------------|
| `USB_LP_IRQHandler` | `USB_FS_LP_IRQHandler` |
| `USB_HP_IRQHandler` → `USB_FS_WKUP_IRQHandler` | WAKEUP 中断名不同 |
| `SysTick_Handler` | `SysTick_Handler` (相同) |
| `FDCAN1_IT0_IRQHandler` | `FDCANx_INT0_IRQHandler` |

N32 NVIC 优先级配置：
```c
NVIC_InitType NVIC_InitStructure;
NVIC_InitStructure.NVIC_IRQChannel = FDCAN2_INT0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
```

> N32 使用 `NVIC_Init()` 而非 STM32 的 `HAL_NVIC_SetPriority()` + `HAL_NVIC_EnableIRQ()`。

---

### 模块 7：链接脚本 + Makefile

**需改文件**: `STM32G431CBTx_FLASH.ld`、`Makefile`

**链接脚本变化**:
- Flash 起始地址: `0x08000000`（相同）
- Flash 大小: 128KB → 512KB
- RAM 起始地址: 需确认 N32H473 的 RAM 分布（可能有多个 SRAM 区块）
- 栈顶地址: 根据 RAM 末尾调整

**Makefile 变化**:
```makefile
# 目标设备
TARGET_DEVICE = N32H473

# 定义
USER_DEFS = -DHSE_VALUE=8000000 -DN32H473

# 源码 (替换为 N32 的文件)
SOURCES = main.c system.c can.c slcan.c led.c error.c printf.c
SOURCES += n32h47x_it.c usb.c usb_desc.c usb_prop.c usb_pwr.c usb_istr.c
SOURCES += system_n32h47x_48x.c

# 启动文件
OBJECTS += $(BUILD_DIR)/startup_n32h47x_48x.o

# HAL 驱动路径
DRIVER_PATH = Drivers/N32H47x_48x_HAL_Driver

# USB 库: 替换为 N32 USB 库
# 不再使用 ST Middlewares/ST/STM32_USB_Device_Library
```

**编译器不变**: 仍使用 `arm-none-eabi-gcc`，目标为 `cortex-m4`，需加上 `-mfloat-abi=hard -mfpu=fpv4-sp-d16`。

---

### 模块 8：SLAN 协议层 (无需修改)

`src/slcan.c` / `inc/slcan.h` — 纯逻辑代码，与 MCU 无关，但需注意：
- 所有 `FDCAN_xxx` 结构体类型名变化 → 使用 typedef 或条件编译适配
- `hal_dlc_code_to_bytes()` 函数需要适配 N32 HAL 的 DLC 编码
- 建议在 `slcan.h` 中加入条件编译：

```c
#ifdef N32H473
  #define CAN_TX_HEADER_TYPE FDCAN_TxHeaderType
  #define CAN_RX_HEADER_TYPE FDCAN_RxHeaderType
#else
  #define CAN_TX_HEADER_TYPE FDCAN_TxHeaderTypeDef
  #define CAN_RX_HEADER_TYPE FDCAN_RxHeaderTypeDef
#endif
```

### 模块 9：printf / error (轻微适配)

- `src/printf.c` — 依赖 `usbd_cdc_if.h` 中的 CDC 发送函数，需适配 USB 发送 API
- `src/error.c` — 纯逻辑，无需修改

---

## 四、推荐移植顺序

```
Phase 1: 基础框架搭建
├── 1.1 建立新的工程目录结构
├── 1.2 集成 N32 HAL 库 + CMSIS
├── 1.3 替换启动文件 + 链接脚本
├── 1.4 改编 Makefile
└── 1.5 实现 system_init() (时钟配置) → 验证 LED 闪烁

Phase 2: 外设逐模块验证
├── 2.1 适配 GPIO / LED → 验证 LED 亮灭
├── 2.2 适配 SysTick → 验证 HAL_GetTick()
├── 2.3 适配 FDCAN → 验证 CAN 收发 (回环模式)
└── 2.4 适配 USB CDC → 验证 USB 枚举和通信

Phase 3: 联调与优化
├── 3.1 整合 slcan 协议层
├── 3.2 中断处理整合
├── 3.3 全功能测试 (CAN ↔ USB)
└── 3.4 性能优化 (利用 240MHz 主频)
```

---

## 五、已知风险与注意事项

| 风险项 | 说明 | 缓解措施 |
|--------|------|---------|
| **CAN 时钟树差异** | N32H473 CAN 时钟来自 PLL 独立分频，可能与 STM32 的 PCLK 分频不兼容 | 仔细对照 N32 时钟树，重新计算所有 bitrate prescaler |
| **USB 库不兼容** | STM32 的 USB Device 库与 N32 的 USBFS 库结构完全不同 | 需要重写 USB 相关文件，参考 ODrive 的 `usb.c`/`usb_prop.c` 等 |
| **FDCAN 消息 RAM** | N32 需手动分配和管理消息 RAM 缓冲区 | 参照 ODrive 的 `FDCAN_ram[1024]` 方式 |
| **HSE 精度依赖** | STM32G4 用 CRS 校准 HSI48 给 USB；N32 无 CRS，依赖 HSE 精度 | 务必使用外部 8MHz 晶体，确保 USB 时钟精度 |
| **NVIC 优先级位宽** | N32H473 是否使用 4-bit 优先级？ | 查阅 N32H473 参考手册确认 |
| **Flash 等待周期** | 240MHz 可能需要不同的 Flash latency | 参考 `system_n32h47x_48x.c` 配置 |

---

## 六、参考文件索引

### CANable 原工程关键文件
| 文件 | 作用 |
|------|------|
| `src/main.c` | 主循环：轮询 CAN 消息 → SLCAN 解析 → USB 发送 |
| `src/system.c` | 时钟初始化 (HSI+PLL→170MHz, USB 48MHz) |
| `src/can.c` | FDCAN 初始化、启停、位速率设置、收发处理 |
| `src/slcan.c` | slcan 协议解析 |
| `src/led.c` | GPIO LED 控制 |
| `src/usbd_cdc_if.c` | USB CDC 收发缓冲管理 |
| `src/interrupts.c` | 中断服务函数 |
| `src/usb_device.c` | USB 设备初始化 |
| `src/usbd_conf.c` | USB 底层配置 |
| `src/usbd_desc.c` | USB 描述符 |
| `src/startup_stm32g431xx.s` | 启动代码 |
| `src/system_stm32g4xx.c` | CMSIS 系统时钟配置 |
| `STM32G431CBTx_FLASH.ld` | 链接脚本 |
| `Makefile` | 构建系统 |
| `inc/stm32g4xx_hal_conf.h` | HAL 配置 |

### ODrive N32H473 参考文件
| 文件 | 作用 |
|------|------|
| `Board/v3/Src/system_n32h47x_48x.c` | N32H473 时钟配置模板 |
| `Board/v3/Src/can.c` / `Inc/can.h` | FDCAN2 初始化和使用示例 |
| `Board/v3/Src/usb.c` / `Inc/usb.h` | USBFS 初始化 |
| `Board/v3/Src/usb_prop.c` / `Inc/usb_prop.h` | USB 应用层属性 |
| `Board/v3/Src/usb_desc.c` / `Inc/usb_desc.h` | USB 描述符 |
| `Board/v3/Src/usb_pwr.c` / `Inc/usb_pwr.h` | USB 电源管理 |
| `Board/v3/Src/usb_istr.c` / `Inc/usb_istr.h` | USB ISR 处理 |
| `Board/v3/Src/n32h47x_it.c` / `Inc/n32h47x_it.h` | 中断服务函数 |
| `Board/v3/Src/gpio.c` / `Inc/gpio.h` | GPIO 初始化 |
| `Board/v3/Inc/main.h` | 主头文件（含引脚宏定义） |
| `Board/v3/Inc/usb_conf.h` | USB 配置（端点、缓冲区等） |
| `Drivers/N32/n32_system.h` | 系统辅助（临界区、IRQ 计数） |
| `Drivers/N32/n32_gpio.cpp/hpp` | GPIO 封装参考 |

---

## 七、建议的新工程目录结构

```
canable2-fw-n32/
├── Makefile
├── N32H473CEUx_FLASH.ld          # 新的链接脚本
├── Drivers/
│   ├── CMSIS/                    # ARM CMSIS (通用)
│   └── N32H47x_48x_HAL_Driver/   # Nation HAL 驱动
│       ├── Inc/
│       └── Src/
├── USB_Device_Library/           # N32 USB 设备库
│   ├── Inc/                      # usbfsd_lib.h, usb_prop.h, ...
│   └── Src/                      # usb_prop.c, usb_istr.c, ...
├── inc/
│   ├── can.h
│   ├── error.h
│   ├── led.h
│   ├── printf.h
│   ├── slcan.h
│   ├── system.h
│   ├── n32h47x_it.h
│   ├── n32h47x_48x_conf.h        # N32 HAL 配置
│   └── usb_conf.h
├── src/
│   ├── main.c
│   ├── system.c                  # 重写：N32 时钟配置
│   ├── can.c                     # 适配：N32 FDCAN API
│   ├── slcan.c                   # 微调：类型适配
│   ├── led.c                     # 适配：N32 GPIO API
│   ├── error.c
│   ├── printf.c
│   ├── n32h47x_it.c              # 新建：N32 中断处理
│   ├── usb_device.c              # 重写：N32 USB 初始化
│   ├── usb_prop.c                # 新建：USB 应用属性
│   ├── usb_desc.c                # 新建：USB 描述符
│   ├── usb_pwr.c                 # 新建：USB 电源管理
│   ├── usb_istr.c                # 新建：USB ISR
│   ├── system_n32h47x_48x.c      # 新建：N32 CMSIS 系统初始化
│   └── startup_n32h47x_48x.s     # 新建：启动文件
└── PORTING_PLAN.md               # 本文档
```

---

*文档版本: v1.0 | 日期: 2026-06-17*
