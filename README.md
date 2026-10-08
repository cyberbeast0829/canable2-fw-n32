# CANable 2.0 (N32H473) — gs_usb / candleLight firmware

USB-to-CAN / CAN-FD adapter firmware for the CANable 2.0 hardware, ported to the
Nations **N32H473CEU7** MCU. This branch implements the **gs_usb** binary
protocol (candleLight-compatible) over a single vendor-specific USB interface.

Because it speaks gs_usb, the device works out of the box with:

- **Linux** — the in-tree `gs_usb` SocketCAN driver creates a `can0` interface
- **Windows** — WinUSB, bound automatically through Microsoft OS descriptors
  (no Zadig / manual driver install required)
- **Cross-platform tools** — Cangaroo, Candle.NET, python-can (`gs_usb` backend),
  etc., addressed by `VID:PID = 0x1d50:0x606f`

> The `master` branch still carries the original LAWICEL/slcan (CDC-ACM)
> firmware. This `candlelight` branch replaces the slcan command interface with
> the gs_usb binary protocol.

## Features

- gs_usb protocol, single CAN channel
- Classical CAN and **CAN-FD** (separate nominal / data bitrates, BRS)
- Bus modes: normal, listen-only, loopback; one-shot transmit
- USB vendor class with bulk IN/OUT (64-byte max packet)
- `VID:PID = 0x1d50:0x606f` (same as candleLight, so host drivers bind automatically)
- **Windows driverless** via MS OS descriptors:
  - Compatible ID `WINUSB`
  - DeviceInterfaceGUID `{c15b4308-04d3-11e6-b3ea-6057189e6443}`
- Unique USB serial number derived from the 96-bit chip UID

## Hardware

| Item       | Value                                     |
|------------|-------------------------------------------|
| MCU        | Nations N32H473CEU7 (Cortex-M4F, 240 MHz) |
| USB        | Full-Speed device — DM = PA11, DP = PA12  |
| CAN        | FDCAN1 — RX = PB12, TX = PB13             |
| CAN clock  | 40 MHz (PLL / 6)                          |
| Status LED | PA0                                       |
| Flash      | 512 KB @ `0x08000000`                     |

## Building

The firmware builds with the GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`).
Install it (e.g. `sudo apt install gcc-arm-none-eabi`, or download from the
[Arm developer site](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)),
make sure `arm-none-eabi-gcc` is on your `PATH`, then run:

```
make
```

Output artifacts are written to `build/` (`.elf`, `.bin`, `.hex`).

### Build options

The following Make variables can be overridden on the command line (defaults in
parentheses). They are mainly useful for derivative boards or for testing on a
host that has already cached a particular USB identity.

| Variable        | Default  | Description                                                                |
|-----------------|----------|----------------------------------------------------------------------------|
| `USB_VID`       | `0x1d50` | USB vendor ID                                                              |
| `USB_PID`       | `0x606f` | USB product ID                                                             |
| `USB_BCDDEVICE` | `0x0200` | USB `bcdDevice` (device revision)                                          |
| `MSOS_USE_20`   | `0`      | `0` = MS OS 1.0 (default, bcdUSB 2.00); `1` = also advertise BOS + MS OS 2.0 (bcdUSB 2.01) |

Example:

```
make USB_PID=0x6070
```

## Flashing

Flash the resulting `build/canable2-n32-*.bin` (or `.hex`) with your SWD probe or
the on-board bootloader, for example:

- **J-Link**:

  ```
  JLink.exe -device N32H473CE -if SWD -speed 4000 -autoconnect 1
  ```

- **OpenOCD / ST-Link / DAPLink**: program flash at base `0x08000000` using the
  memory layout from `N32H473CEUx_FLASH.ld`.

- **dfu-util** (if a DFU bootloader is present):

  ```
  dfu-util -D build/canable2-n32-*.bin -a 0 -s 0x08000000:leave
  ```

## Usage

### Linux (SocketCAN)

The kernel `gs_usb` driver binds automatically. Bring the interface up and use
the standard `can-utils`:

```
# Classical CAN at 1 Mbit/s
sudo ip link set can0 up type can bitrate 1000000

# CAN-FD: 1 Mbit/s nominal + 5 Mbit/s data
sudo ip link set can0 up type can bitrate 1000000 dbitrate 5000000 fd on

candump can0
cansend can0 123#DEADBEEF
```

> CAN-FD requires a kernel with the FD-capable `gs_usb` driver (Linux 6.x).

### Windows

WinUSB binds automatically through the MS OS descriptors, so the device appears
as a "WinUSB device" exposing the interface GUID
`{c15b4308-04d3-11e6-b3ea-6057189e6443}`. No driver installation is required.

## Notes and limitations

- Single CAN channel (`icount = 0`).
- Hardware timestamps are not implemented (the timestamp field is currently 0).
- TX frames are echoed back to the host as soon as they are queued to the CAN
  peripheral, not when the frame is actually acknowledged on the bus. This
  matches upstream candleLight behaviour and affects one-shot and timestamp
  edge cases.

## License

See LICENSE.md
