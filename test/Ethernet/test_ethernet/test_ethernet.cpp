#include <unity.h>
#include <Ethernet2.h>

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x38, 0x5C};
EthernetClient client;

void hardware_status()
{
  TEST_ASSERT_NOT_EQUAL(EthernetNoHardware, Ethernet.hardwareStatus());
}

void link_status()
{
  TEST_ASSERT_NOT_EQUAL(LinkOFF, Ethernet.linkStatus());
}

void ethernet_ip(void)
{
  TEST_ASSERT_EQUAL(OUTPUT, Ethernet.localIP());
}

void setup()
{
  UNITY_BEGIN(); // IMPORTANT LINE!

  Ethernet.begin(mac);

  RUN_TEST(hardware_status);
  RUN_TEST(link_status);
  RUN_TEST(ethernet_ip);

  UNITY_END(); // stop unit testing
}

void loop()
{
}
