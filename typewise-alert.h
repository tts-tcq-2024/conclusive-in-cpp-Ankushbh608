#pragma once

typedef enum {
    PASSIVE_STRATEGY,
    HIGH_ACTIVE_STRATEGY,
    MEDIUM_ACTIVE_STRATEGY
} CoolingStrategy;

typedef enum {
    TEMP_NORMAL,
    TEMP_TOO_LOW,
    TEMP_TOO_HIGH
} TemperatureStatus;

typedef struct {
    int minTemp;
    int maxTemp;
} TemperatureRange;

TemperatureStatus assessTemperature(double currentTemp, double minTemp, double maxTemp);
TemperatureRange fetchTemperatureRange(CoolingStrategy strategy);
TemperatureStatus determineBreach(CoolingStrategy strategy, double tempCelsius);

typedef enum {
    CONTROLLER_ALERT,
    EMAIL_ALERT
} AlertMethod;

typedef struct {
    CoolingStrategy strategy;
    char brandName[48];
} BatteryDetails;

void monitorAndNotify(AlertMethod method, BatteryDetails battery, double tempCelsius);
void triggerAlert(AlertMethod method, TemperatureStatus status);
void alertController(TemperatureStatus status);
void alertViaEmail(TemperatureStatus status);
