#include <Arduino.h>
// #include <SPI.h>
#include <Ethernet2.h>
#include <ArduinoHA.h>
#include <AutomationBoard.h>

#define BROKER_ADDR IPAddress(192, 168, 1, 186)

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x38, 0x5C};
EthernetClient client;

HADevice haDevice(mac, sizeof(mac));
HAMqtt mqtt(client, haDevice);
const char DEVICE_NAME[] = "automationboard";

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

// Configure Relay 2
HASwitch relay_2("relay_2", false);
void relay2onSwitchStateChanged(bool state, HASwitch *s)
{
  digitalWrite(automationboard.getRelay2Pin(), (state ? HIGH : LOW));
}

// Configure Relay 3
HASwitch relay_3("relay_3", false);
void relay3onSwitchStateChanged(bool state, HASwitch *s)
{
  digitalWrite(automationboard.getRelay3Pin(), (state ? HIGH : LOW));
}

// Configure Relay 4
HASwitch relay_4("relay_4", false);
void relay4onSwitchStateChanged(bool state, HASwitch *s)
{
  digitalWrite(automationboard.getRelay4Pin(), (state ? HIGH : LOW));
}

void setup()
{
  // put your setup code here, to run once:
  // Serial.begin(9600); // open the serial port at 9600 bps:

  automationboard.init();

  haDevice.setName("Automation Board");
  haDevice.setModel("Automation Board");
  haDevice.setManufacturer("GarageLab, LLC");
  haDevice.setSoftwareVersion("0.1");

  // This method enables availability for all device types registered on the device.
  // For example, if you have 5 sensors on the same device, you can enable
  // shared availability and change availability state of all sensors using
  // single method call "device.setAvailability(false|true)"
  haDevice.enableSharedAvailability();

  // Optionally, you can enable MQTT LWT feature. If device will lose connection
  // to the broker, all device types related to it will be marked as offline in
  // the Home Assistant Panel.
  haDevice.enableLastWill();

  // Configure relay_1 specifics
  relay_1.setName("relay 1");
  relay_1.setRetain(true);
  // handle switch state
  relay_1.onBeforeStateChanged(onBeforeSwitchStateChanged);
  relay_1.onStateChanged(relay1onSwitchStateChanged);

  // Configure relay_2 specifics
  relay_2.setName("relay 2");
  relay_2.setRetain(true);
  // handle switch state
  relay_2.onBeforeStateChanged(onBeforeSwitchStateChanged);
  relay_2.onStateChanged(relay2onSwitchStateChanged);

  // Configure relay_3 specifics
  relay_3.setName("relay 3");
  relay_3.setRetain(true);
  // handle switch state
  relay_3.onBeforeStateChanged(onBeforeSwitchStateChanged);
  relay_3.onStateChanged(relay3onSwitchStateChanged);

  // Configure relay_4 specifics
  relay_4.setName("relay 4");
  relay_4.setRetain(true);
  // handle switch state
  relay_4.onBeforeStateChanged(onBeforeSwitchStateChanged);
  relay_4.onStateChanged(relay4onSwitchStateChanged);

  // you don't need to verify return status
  Ethernet.begin(mac);

  mqtt.begin(BROKER_ADDR);
}

void loop() {
  // put your main code here, to run repeatedly:
  Ethernet.maintain();
  mqtt.loop();
}
