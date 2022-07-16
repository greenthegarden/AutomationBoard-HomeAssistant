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

#define UNKNOWN_PIN 0xFF

// Source: https://forum.arduino.cc/t/check-current-pinmode/232140/4
uint8_t getPinMode(uint8_t pin)
{
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);

  // I don't see an option for mega to return this, but whatever...
  if (NOT_A_PIN == port)
    return UNKNOWN_PIN;

  // Is there a bit we can check?
  if (0 == bit)
    return UNKNOWN_PIN;

  // Is there only a single bit set?
  if (bit & bit - 1)
    return UNKNOWN_PIN;

  volatile uint8_t *reg, *out;
  reg = portModeRegister(port);
  out = portOutputRegister(port);

  if (*reg & bit)
    return OUTPUT;
  else if (*out & bit)
    return INPUT_PULLUP;
  else
    return INPUT;
}

AutomationBoard automationboard;

void test_pinmode_relay_1(void)
{
  TEST_ASSERT_EQUAL(OUTPUT, getPinMode(automationboard.getRelay1Pin()));
}

void test_pinmode_relay_2(void)
{
  TEST_ASSERT_EQUAL(OUTPUT, getPinMode(automationboard.getRelay2Pin()));
}

void test_pinmode_relay_3(void)
{
  TEST_ASSERT_EQUAL(OUTPUT, getPinMode(automationboard.getRelay3Pin()));
}

void test_pinmode_relay_4(void)
{
  TEST_ASSERT_EQUAL(OUTPUT, getPinMode(automationboard.getRelay4Pin()));
}

void setup()
{
  automationboard.init();

  UNITY_BEGIN(); // IMPORTANT LINE!

  RUN_TEST(test_pinmode_relay_1);
  RUN_TEST(test_pinmode_relay_2);
  RUN_TEST(test_pinmode_relay_3);
  RUN_TEST(test_pinmode_relay_4);

  UNITY_END(); // stop unit testing
}

void loop()
{}
