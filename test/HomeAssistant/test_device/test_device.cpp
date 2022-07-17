#include <unity.h>
#include <ArduinoHA.h>

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x38, 0x5C};
HADevice haDevice(mac, sizeof(mac));

void ha_device_name(void)
{
  TEST_ASSERT_EQUAL(OUTPUT, haDevice.getUniqueId());
}

void setup()
{
  UNITY_BEGIN(); // IMPORTANT LINE!

  RUN_TEST(ha_device_name);

  UNITY_END(); // stop unit testing
}

void loop()
{
}
