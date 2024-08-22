#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, AssessesTemperatureAccordingToLimits) {
    EXPECT_EQ(assessTemperature(18, 15, 25), TEMP_NORMAL);
    EXPECT_EQ(assessTemperature(12, 15, 25), TEMP_TOO_LOW);
    EXPECT_EQ(assessTemperature(28, 15, 25), TEMP_TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, DeterminesTemperatureBreach) {
    EXPECT_EQ(determineBreach(PASSIVE_STRATEGY, 34), TEMP_NORMAL);
    EXPECT_EQ(determineBreach(HIGH_ACTIVE_STRATEGY, 50), TEMP_TOO_HIGH);
    EXPECT_EQ(determineBreach(MEDIUM_ACTIVE_STRATEGY, 41), TEMP_TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, SendsAlertToController) {
    testing::internal::CaptureStdout();
    alertController(TEMP_TOO_LOW);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 1\n");
}

TEST(TypeWiseAlertTestSuite, SendsAlertToEmail) {
    testing::internal::CaptureStdout();
    alertViaEmail(TEMP_TOO_LOW);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is below the threshold\n");
}

TEST(TypeWiseAlertTestSuite, MonitorAndNotify) {
    BatteryDetails battery = {PASSIVE_STRATEGY, "BrandX"};
    
    testing::internal::CaptureStdout();
    monitorAndNotify(CONTROLLER_ALERT, battery, 36);
    std::string outputController = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outputController, "feed : 2\n");

    testing::internal::CaptureStdout();
    monitorAndNotify(EMAIL_ALERT, battery, -1);
    std::string outputEmail = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outputEmail, "To: a.b@c.com\nHi, the temperature is below the threshold\n");
}

