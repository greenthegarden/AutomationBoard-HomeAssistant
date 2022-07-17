#include <unity.h>
#include <Ethernet.h>
#include <ArduinoHA.h>
#include <AutomationBoard.h>

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

#define BROKER_ADDR IPAddress(192, 168, 1, 186)

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x38, 0x5C};
EthernetClient client;

HADevice haDevice(mac, sizeof(mac));
HAMqtt mqtt(client, haDevice);

AutomationBoard automationboard;

// Define relays as switches
// Set initial state of off (false)
void onBeforeSwitchStateChanged(bool state, HASwitch *s)
{
  // this callback will be called before publishing new state to HA
  // in some cases there may be delay before onStateChanged is called due to network latency
}

// Configure Relay 1
HASwitch relay_1("relay_1", false);
void relay1onSwitchStateChanged(bool state, HASwitch *s)
{
  digitalWrite(automationboard.getRelay1Pin(), (state ? HIGH : LOW));
}

void test_relay_1_on(void)
{
  TEST_ASSERT_EQUAL(true, mqtt.publish("homeassistant/switch/0010fa6e385c/relay_1/cmd", "1"));
  TEST_ASSERT_EQUAL(HIGH, digitalRead(automationboard.getRelay1Pin()));
}

void test_relay_1_off(void)
{
  mqtt.publish("homeassistant/switch/0010fa6e385c/relay_1/cmd", "0");
  TEST_ASSERT_EQUAL(LOW, digitalRead(automationboard.getRelay1Pin()));
}

void setup()
{
  UNITY_BEGIN(); // IMPORTANT LINE!

  automationboard.init();

  // Configure relay_1 specifics
  relay_1.setName("relay 1");
  relay_1.setRetain(true);
  // handle switch state
  relay_1.onBeforeStateChanged(onBeforeSwitchStateChanged);
  relay_1.onStateChanged(relay1onSwitchStateChanged);

  // you don't need to verify return status
  Ethernet.begin(mac);

  if(mqtt.begin(BROKER_ADDR))
  {
    RUN_TEST(test_relay_1_on);
    RUN_TEST(test_relay_1_off);
  }

  UNITY_END(); // stop unit testing
}

void loop()
{
}
