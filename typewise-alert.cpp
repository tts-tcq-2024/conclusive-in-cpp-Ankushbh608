#include "typewise-alert.h"
#include <stdio.h>

TemperatureStatus assessTemperature(double currentTemp, double minLimit, double maxLimit) {
    return (currentTemp < minLimit) ? TEMP_TOO_LOW : (currentTemp > maxLimit) ? TEMP_TOO_HIGH : TEMP_NORMAL;
}

TemperatureRange fetchTemperatureRange(CoolingStrategy strategy) {
    static const TemperatureRange ranges[] = {
        {0, 35},  // PASSIVE_STRATEGY
        {0, 45},  // HIGH_ACTIVE_STRATEGY
        {0, 40}   // MEDIUM_ACTIVE_STRATEGY
    };
    return ranges[strategy];
}

TemperatureStatus determineBreach(CoolingStrategy strategy, double tempCelsius) {
    TemperatureRange range = fetchTemperatureRange(strategy);
    return assessTemperature(tempCelsius, range.minTemp, range.maxTemp);
}

void monitorAndNotify(AlertMethod method, BatteryDetails battery, double tempCelsius) {
    TemperatureStatus status = determineBreach(battery.strategy, tempCelsius);
    triggerAlert(method, status);
}

void triggerAlert(AlertMethod method, TemperatureStatus status) {
    if(method == CONTROLLER_ALERT) {
        alertController(status);
    } else if(method == EMAIL_ALERT) {
        alertViaEmail(status);
    }
}

void alertController(TemperatureStatus status) {
    const unsigned short protocolHeader = 0xfeed;
    printf("%x : %x\n", protocolHeader, status);
}

void alertViaEmail(TemperatureStatus status) {
    const char* recipient = "a.b@c.com";
    if (status == TEMP_TOO_LOW) {
        printf("To: %s\n", recipient);
        printf("Hi, the temperature is below the threshold\n");
    } else if (status == TEMP_TOO_HIGH) {
        printf("To: %s\n", recipient);
        printf("Hi, the temperature exceeds the safe limit\n");
    }
}
