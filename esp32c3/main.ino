#include <ArduinoBLE.h>

BLECharacteristic correctCharacteristic;

bool displayDown = true;

bool buttonAlreadyPressed = false;

bool connectionEstablished = false;

void InitializeBluetooth() {
  if (!BLE.begin()) {
    while (1);
  }
  BLE.scanForName("DSD TECH");
}


void explorerPeripheral(BLEDevice peripheral) {
  // connect to the peripheral

  if (!peripheral.connect()) return;

  if (!peripheral.discoverAttributes()) {
    peripheral.disconnect();
    return;
  }

  bool correctServiceFound = false;

  // loop the services of the peripheral and explore each
  for (int i = 0; i < peripheral.serviceCount(); i++) {
    BLEService service = peripheral.service(i);

    bool isCorrectService = exploreService(service);
    if (isCorrectService) {correctServiceFound = true; break;}
  }

  if (!correctServiceFound) peripheral.disconnect();
}

bool exploreService(BLEService service) {

    bool foundCorrectCharacteristic = false;

  // loop the characteristics of the service and explore each
  for (int i = 0; i < service.characteristicCount(); i++) {
    BLECharacteristic characteristic = service.characteristic(i);

    bool isCorrectCharacteristic = exploreCharacteristic(characteristic);
    if (isCorrectCharacteristic) {
        foundCorrectCharacteristic = true;
        break;
    }
  }
  return foundCorrectCharacteristic;
}

void WriteVal(uint8_t value) {
 if (correctCharacteristic) correctCharacteristic.writeValue(value);
}

bool exploreCharacteristic(BLECharacteristic characteristic) {
  // print the UUID and properties of the characteristic
  char s[] = "ffe1";
  if (characteristic.uuid()[0] == s[0] && characteristic.uuid()[1] == s[1] && characteristic.uuid()[2] == s[2] && characteristic.uuid()[3] == s[3]){
    correctCharacteristic = characteristic;
    return true;
  }
    return false;
}

void InitializeButton() {
    pinMode(10, INPUT_PULLUP);
}

bool ButtonIsPressed() {
    return digitalRead(10) == LOW;
}

void ToggleDisplay() {
    if (displayDown) {
        // send message to move display up
        Serial.println("Writing 1");
        WriteVal(1); // 1 = UP
    }
    else {
        // send message to move display down
        Serial.println("Writing 2");
        WriteVal(2); // 2 = DOWN
    }
    displayDown = !displayDown;
}

void setup() {
  pinMode(D9, OUTPUT);
  digitalWrite(D9, HIGH);
    delay(1000);
    digitalWrite(D9, LOW);
    delay(1000);
    digitalWrite(D9, HIGH);
    delay(750);
    digitalWrite(D9, LOW);
    delay(500);
    digitalWrite(D9, HIGH);
    delay(250);
    digitalWrite(D9, LOW);
    delay(100);
    digitalWrite(D9, HIGH);
    delay(10);
    digitalWrite(D9, LOW);
    delay(10);
  Serial.begin(9600);
    InitializeButton();
    InitializeBluetooth();

}

void loop() {
    if (connectionEstablished) {
        bool buttonIsPressed = ButtonIsPressed();
        if (buttonIsPressed && !buttonAlreadyPressed) {
            buttonAlreadyPressed = true;
            ToggleDisplay();
            delay(1000);
        }
        else if (!buttonIsPressed) {
            buttonAlreadyPressed = false;
        }
    }
    else {
        // check if a peripheral has been discovered
        BLEDevice peripheral = BLE.available();

        if (peripheral) {
            if (peripheral.localName() == "DSD TECH") { //LED
            // stop scanning
            BLE.stopScan();

            explorerPeripheral(peripheral);

            connectionEstablished = true;
            Serial.println("Connection established");
            Serial.println(correctCharacteristic.uuid());
            }
        }
    }
}