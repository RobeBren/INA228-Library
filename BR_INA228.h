/*
 * ***************************************************************************
 * Component:    INA228 - Power Monitor
 * Manufacturer: Adafruit
 * Product:      INA228 - I2C 85V, 20-bit High or Low Side Power Monitor
 * Product ID:   5832
 *
 * Product Page:
 *     https://www.adafruit.com/product/5832
 *
 * Datasheet:
 *     https://www.ti.com/lit/ds/symlink/ina228.pdf
 *
 * ***************************************************************************
 */
#ifndef BR_INA228_H
#define BR_INA228_H

#include <Arduino.h>


class BR_INA228 {
    public:
    
        // INA228 Addresses
        enum class Addresses : uint8_t {
            ADR_1 = 0x40,       // A1 = GND, A0 = GND
            ADR_2 = 0x41,       // A1 = GND, A0 = VS
            ADR_3 = 0x42,       // A1 = GND, A0 = SDA
            ADR_4 = 0x43,       // A1 = GND, A0 = SCL
            ADR_5 = 0x44,       // A1 = VS, A0 = GND
            ADR_6 = 0x45,       // A1 = VS, A0 = VS
            ADR_7 = 0x46,       // A1 = VS, A0 = SDA
            ADR_8 = 0x47,       // A1 = VS, A0 = SCL
            ADR_9 = 0x48,       // A1 = SDA, A0 = GND
            ADR_10 = 0x49,      // A1 = SDA, A0 = VS
            ADR_11 = 0x4A,      // A1 = SDA, A0 = SDA
            ADR_12 = 0x4B,      // A1 = SDA, A0 = SCL
            ADR_13 = 0x4C,      // A1 = SCL, A0 = GND
            ADR_14 = 0x4D,      // A1 = SCL, A0 = VS
            ADR_15 = 0x4E,      // A1 = SCL, A0 = SDA
            ADR_16 = 0x4F       // A1 = SCL, A0 = SCL
        };
        

        // INA228 Registers [Acronym, Address, Register Name, Register Size]
        static constexpr uint8_t CONFIG = 0x00;            // Configuration                            16 bits
        static constexpr uint8_t ADC_CONFIG = 0x01;        // ADC Configuration                        16 bits
        static constexpr uint8_t SHUNT_CAL = 0x02;         // Shunt Calibration                        16 bits
        static constexpr uint8_t SHUNT_TEMPCO = 0x03;      // Shunt Temperature Coefficient            16 bits
        static constexpr uint8_t VSHUNT = 0x04;            // Shunt Voltage Measurement                24 bits
        static constexpr uint8_t VBUS = 0x05;              // Bus Voltage Measurement                  24 bits
        static constexpr uint8_t DIETEMP = 0x06;           // Temperature Measurement                  16 bits
        static constexpr uint8_t CURRENT = 0x07;           // Current Result                           24 bits
        static constexpr uint8_t POWER = 0x08;             // Power Result                             24 bits
        static constexpr uint8_t ENERGY = 0x09;            // Energy Result                            40 bits
        static constexpr uint8_t CHARGE = 0x0A;            // Charge Result                            40 bits
        static constexpr uint8_t DIAG_ALRT = 0x0B;         // Diagnostic Flags and Alert               16 bits
        static constexpr uint8_t SOVL = 0x0C;              // Shunt Overvoltage Threshold              16 bits
        static constexpr uint8_t SUVL = 0x0D;              // Shunt Undervoltage Threshold             16 bits
        static constexpr uint8_t BOVL = 0x0E;              // Bus Overvoltage Threshold                16 bits
        static constexpr uint8_t BUVL = 0x0F;              // Bus Undervoltage Threshold               16 bits
        static constexpr uint8_t TEMP_LIMIT = 0x10;        // Temperature Over-Limit Threshold         16 bits
        static constexpr uint8_t PWR_LIMIT = 0x11;         // Power Over-Limit Threshold               16 bits
        static constexpr uint8_t MANUFACTURER_ID = 0x3E;   // Manufacturer ID                          16 bits
        static constexpr uint8_t DEVICE_ID = 0x3F;         // Device ID                                16 bits

        // Constructor
        BR_INA228(Addresses adr);

        // Initialization
        bool begin();

        // INA228 Measurement Requests
        bool requestCurrent(int32_t &current);
        bool requestVoltage(uint32_t &voltage);
        bool requestPower(uint32_t &power);
        bool requestEnergy(uint64_t &energy);
        bool requestCharge(int64_t &charge);
        bool requestTemperature(int16_t &temperature);


    private:
        Addresses _address;

        // INA228 Register Requests
        bool readUnsignedRegister16(uint8_t reg, uint16_t &data);
        bool readSignedRegister16(uint8_t reg, int16_t &data);

        bool readUnsignedRegister24(uint8_t reg, uint32_t &data);
        bool readSignedRegister24(uint8_t reg, int32_t &data);

        bool readUnsignedRegister40(uint8_t reg, uint64_t &data);
        bool readSignedRegister40(uint8_t reg, int64_t &data);

};



#endif