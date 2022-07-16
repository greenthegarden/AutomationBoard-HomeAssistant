#include <unity.h>
#include <AutomationBoard.h>

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

AutomationBoard automationboard;

void test_relay_1_pin_number(void)
{
  TEST_ASSERT_EQUAL(5, automationboard.getRelay1Pin());
}

void test_relay_2_pin_number(void)
{
  TEST_ASSERT_EQUAL(6, automationboard.getRelay2Pin());
}

void test_relay_3_pin_number(void)
{
  TEST_ASSERT_EQUAL(7, automationboard.getRelay3Pin());
}

void test_relay_4_pin_number(void)
{
  TEST_ASSERT_EQUAL(8, automationboard.getRelay4Pin());
}

byte *relay_pins = automationboard.getRelayPins();

void test_relaypins_length(void)
{
  TEST_ASSERT_EQUAL(4, sizeof(relay_pins)/sizeof(relay_pins[0]));
}

void test_relaypins_1(void)
{
  TEST_ASSERT_EQUAL(5, relay_pins[0]);
}

void test_relaypins_2(void)
{
  TEST_ASSERT_EQUAL(6, relay_pins[1]);
}

void test_relaypins_3(void)
{
  TEST_ASSERT_EQUAL(7, relay_pins[2]);
}

void test_relaypins_4(void)
{
  TEST_ASSERT_EQUAL(8, relay_pins[3]);
}

void setup()
{
  UNITY_BEGIN(); // IMPORTANT LINE!

  RUN_TEST(test_relay_1_pin_number);
  RUN_TEST(test_relay_2_pin_number);
  RUN_TEST(test_relay_3_pin_number);
  RUN_TEST(test_relay_4_pin_number);

  RUN_TEST(test_relaypins_length);
  RUN_TEST(test_relaypins_1);
  RUN_TEST(test_relaypins_2);
  RUN_TEST(test_relaypins_3);
  RUN_TEST(test_relaypins_4);

  UNITY_END(); // stop unit testing
}

void loop()
{}
