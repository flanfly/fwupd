# Genesys Logic

## Introduction

This plugin allows updating the Genesys Logic USB Hub devices.

* GL3523
* GL3590

Additionally, this plugin allows updating the MStar Semiconductor Scaler connected via an I²C bus.

* TSUM G

## Firmware Format

The daemon will decompress the cabinet archives and extract the firmware blob in an unspecified binary file format.

This plugin supports the following protocol IDs:

* com.genesys.usbhub
* com.mstarsemi.scaler

## GUID Generation

These devices use the standard USB DeviceInstanceId values for the USB Hub, e.g.

* HP Mxfd FHD Monitor: `USB\VID_03F0&PID_0610`

These devices also use custom GUID values for the Scaler, e.g.

* HP M24fd USB-C Monitor: `GENESYS_SCALER\MSTAR_TSUM_G&PUBKEY_B335BDCE-7073-5D0E-9BD3-9B69C1A6899F`
* HP M27fd USB-C Monitor: `GENESYS_SCALER\MSTAR_TSUM_G&PUBKEY_847A3650-8648-586B-83C8-8B53714F37E3`

The Public Key is product-specific and is required to identify the product.

## Quirk Use

This plugin uses the following plugin-specific quirks:

### has-mstar-scaler

USB Hub has a MStar Semiconductor Scaler attached via I²C.

Since 1.7.6.

### GenesysUsbhubSwitchRequest

USB Hub Switch Request value.

* HP Mxfd FHD Monitors: `0xA1`

Since 1.7.6.

### GenesysUsbhubReadRequest

USB Hub Read Request value.

* HP Mxfd FHD Monitors: `0xA2`

Since 1.7.6.

### GenesysUsbhubWriteRequest

USB Hub Write Request value.

* HP Mxfd FHD Monitors: `0xA3`

Since 1.7.6.

### use-i2c-ch0

Scalar uses I²C channel 0.

Since 1.7.6.

### pause-r2-cpu

Scalar pause R2 CPU.

Since 1.7.6.

### GenesysScalerDeviceTransferSize

Scaler Block size to use for transfers.

* MStar Semiconductor TSUM G: `0x40`

Since 1.7.6.

### GenesysScalerGpioOutputRegister

Scaler GPIO Output Register value.

* MStar Semiconductor TSUM G: `0x0426`

Since 1.7.6.

### GenesysScalerGpioEnableRegister

Scaler GPIO Enable Register value.

* MStar Semiconductor TSUM G: `0x0428`

Since 1.7.6.

### GenesysScalerGpioValue

Scaler GPIO value.

* MStar Semiconductor TSUM G: `0x01`

Since 1.7.6.

## Runtime Requirement

The USB Hub devices and its attached Scaler require libgusb version [0.3.8][1] or later to be detected.

## Update Behavior

The devices are independently updated at runtime using USB control transfers.

The firmware is deployed when the device is in normal runtime mode, and the device will reset when the new firmware has been written.

The HP Mxfd FHD Monitors must be connected to host via the USB-C cable to apply an update. The devices remain functional during the update; the Scaler update is ~10 minute long.

## Vendor ID Security

The vendor ID is set from the USB vendor, for example set to `USB:0x03F0` for HP.

## External Interface Access

This plugin requires read/write access to `/dev/bus/usb`.

[1]: https://github.com/hughsie/libgusb/commit/4e118c154dde70e196c4381bd97790a9413c3552
