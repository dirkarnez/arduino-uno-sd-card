#include <SPI.h>
#include <SD.h>
File myFile;

String randomFileNameSelected;
size_t randomNumber;

// const byte ledPin = 13;
const byte interruptPin = 2;

String full_file_names[] = { 
  //full name does not work, use shortened name and map it
};

String shorten_file_names[] = { 
  //
};

const size_t length = sizeof(shorten_file_names) / sizeof(String);

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect. Needed for native USB port only
  Serial.println("Initializing...");
  Serial.println("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }

  pinMode(interruptPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  randomSeed(analogRead(0));

  Serial.println("Initialization done.");
  randomNumber = random(length);
  randomFileNameSelected = shorten_file_names[randomNumber];
}

void loop() {
}

void blink() {
  Serial.println("blink");

  randomNumber = random(length);
  randomFileNameSelected = shorten_file_names[randomNumber];

  // close previously opened file for safety
  if (myFile) {
    myFile.close();
  }

  myFile = SD.open(randomFileNameSelected, O_RDONLY);
  if (myFile) {
    Serial.print("opened: ");
    Serial.println(full_file_names[randomNumber]);
    // LCD print
    // random sample inside .mat file
    // // read from the file until there's nothing else in it:
    // while (myFile.available()) {
    //   // Serial.write(myFile.read());
    // }
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.print("error opening ");
    Serial.println(randomFileNameSelected);
  }
}
