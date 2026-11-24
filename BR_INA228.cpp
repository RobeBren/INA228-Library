#include "BR_INA228.h"
#include <Arduino.h>
#include <Wire.h>

bool BR_INA228::begin() {
    return Wire.begin();
}

BR_INA228::BR_INA228(Addresses adr) {
    _address = adr;

}

// Request Current
bool BR_INA228::requestCurrent(int32_t &current) {

    int32_t rawData;

    if (!readSignedRegister24(CURRENT, rawData))
        return false;

    current = rawData / 16;

    return true;
}

// Request Voltage
bool BR_INA228::requestVoltage(uint32_t &voltage) {

    uint32_t rawData;

    if (!readUnsignedRegister24(VBUS, rawData))
        return false;

    voltage = rawData >> 4;

    return true;
}

// Request Power
bool BR_INA228::requestPower(uint32_t &power) {

    uint32_t rawData;

    if (!readUnsignedRegister24(POWER, rawData))
        return false;

    // TODO: Convert rawData to power

    return false; // Update to true when conversion is added
}


// Request Energy
bool BR_INA228::requestEnergy(uint64_t &energy) {

    uint64_t rawData;

    if (!readUnsignedRegister40(ENERGY, rawData))
        return false;

    // TODO: Convert rawData to energy

    return false; // Update to true when conversion is added
}


// Request Charge
bool BR_INA228::requestCharge(int64_t &charge) {

    int64_t rawData;

    if (!readSignedRegister40(CHARGE, rawData))
        return false;

    // TODO: Convert rawData to charge

    return false; // Update to true when conversion is added
}


// Request Temperature
bool BR_INA228::requestTemperature(int16_t &temperature) {

    int16_t rawData;

    if (!readSignedRegister16(DIETEMP, rawData))
        return false;

    // TODO: Convert rawData to temperature

    return false; // Update to true when conversion is added
}


// INA228 Register Requests

// Read Unsigned 16-bit Register
bool BR_INA228::readUnsignedRegister16(uint8_t reg, uint16_t &data) {

    // Convert I2C Address
    uint8_t adr = static_cast<uint8_t>(_address);

    // Select Register
    Wire.beginTransmission(adr);
    Wire.write(reg);

    if (Wire.endTransmission(false) != 0)
        return false;

    // Request 2 Bytes
    if (Wire.requestFrom(adr, (uint8_t)2) != 2)
        return false;

    if (Wire.available() < 2)
        return false;

    // Retrieve and Combine Data
    uint16_t rawData = 0;

    rawData |= (uint16_t)Wire.read() << 8;
    rawData |= (uint16_t)Wire.read();

    // Assign Output
    data = rawData;

    return true;
}


// Read Signed 16-bit Register
bool BR_INA228::readSignedRegister16(uint8_t reg, int16_t &data) {

    uint16_t rawData;

    if (!readUnsignedRegister16(reg, rawData))
        return false;

    data = (int16_t)rawData;

    return true;
}


// Read Unsigned 24-bit Register
bool BR_INA228::readUnsignedRegister24(uint8_t reg, uint32_t &data) {
    
    // Convert I2C Address
    uint8_t adr = static_cast<uint8_t>(_address);


    // Select Register
    Wire.beginTransmission(adr);
    Wire.write(reg);

    if (Wire.endTransmission(false) != 0)
        return false;

    // Request 3 Bytes
    if (Wire.requestFrom(adr, (uint8_t)3) != 3)
        return false;

    if (Wire.available() < 3)
        return false;

    // Retrieve and Combine Data
    uint32_t rawData = 0;

    rawData |= (uint32_t)Wire.read() << 16;
    rawData |= (uint32_t)Wire.read() << 8;
    rawData |= (uint32_t)Wire.read();

    // Assign Output
    data = rawData;

    return true;
}


// Read Signed 24-bit Register
bool BR_INA228::readSignedRegister24(uint8_t reg, int32_t &data) {

    uint32_t rawData;

    if (!readUnsignedRegister24(reg, rawData))
        return false;

    // Sign Extend 24-bit Value
    if (rawData & (1UL << 23))
        rawData |= 0xFF000000;

    data = (int32_t)rawData;

    return true;
}


// Read Unsigned 40-bit Register
bool BR_INA228::readUnsignedRegister40(uint8_t reg, uint64_t &data) {

    // Convert I2C Address
    uint8_t adr = static_cast<uint8_t>(_address);

    // Select Register
    Wire.beginTransmission(adr);
    Wire.write(reg);

    if (Wire.endTransmission(false) != 0)
        return false;

    // Request 5 Bytes
    if (Wire.requestFrom(adr, (uint8_t)5) != 5)
        return false;

    if (Wire.available() < 5)
        return false;

    // Retrieve and Combine Data
    uint64_t rawData = 0;

    rawData |= (uint64_t)Wire.read() << 32;
    rawData |= (uint64_t)Wire.read() << 24;
    rawData |= (uint64_t)Wire.read() << 16;
    rawData |= (uint64_t)Wire.read() << 8;
    rawData |= (uint64_t)Wire.read();

    // Assign Output
    data = rawData;

    return true;
}


// Read Signed 40-bit Register
bool BR_INA228::readSignedRegister40(uint8_t reg, int64_t &data) {

    uint64_t rawData;

    if (!readUnsignedRegister40(reg, rawData))
        return false;

    // Sign Extend 40-bit Value
    if (rawData & (1ULL << 39))
        rawData |= 0xFFFFFF0000000000ULL;

    data = (int64_t)rawData;

    return true;
}