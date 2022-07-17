#include <unity.h>
#include <Ethernet.h>

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x38, 0x5C};

// https://www.arduino.cc/reference/en/libraries/ethernet/ethernet.hardwarestatus/
void hardware_status()
{
  TEST_ASSERT_EQUAL(EthernetW5500, Ethernet.hardwareStatus());
}

// https://www.arduino.cc/reference/en/libraries/ethernet/ethernet.linkstatus/
void link_status()
{
  TEST_ASSERT_EQUAL(LinkON, Ethernet.linkStatus());
}

void ethernet_ip(void)
{
  IPAddress ip = Ethernet.localIP();
  IPAddress ip_test(10, 0, 0, 177);
  TEST_ASSERT_EQUAL(ip_test, ip);
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
