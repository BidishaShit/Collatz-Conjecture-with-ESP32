
// This program will check 10,000 numbers for convergence verification of the Collatz conjecture. 
// Read more about the Collatz conjecture: https://medium.com/the-wisest-friends/a-simple-problem-mathematicians-couldnt-solve-till-date-d51fbadf98e5
// The last checked number is saved in the SPIFFS memory so that when the device is booted next time, we start from the last checked number. 
// BigNumber library: https://github.com/nickgammon/BigNumber/
// Click on the '<> Code' button and download ZIP. To add the ZIP library, go to Sketch -> Include Library -> Add .ZIP Library, in your Arduino IDE.

// We are using the BigNumber library to handle big numbers
#include "BigNumber.h"

// For saving checked numbers using SPIFFS
// Serial Peripheral Interface Flash File System (SPIFFS) is the file system of ESP32. 
// We can choose the size of the SPIFFS memory before uploading the code to ESP32 by choosing a partition scheme.
#include "FS.h"
#include "SPIFFS.h"
#define FORMAT_SPIFFS_IF_FAILED true

// For saving last checked number
String lastCheckedNumberFilePath = "/lastchecked.txt";

// the last checked number (in string format)
String lastCheckedString;
// default last checked number
String defaultLastChecked = "295147905179352830000"; // 2^68 value

// this method reads the last checked number from the SPIFFS memory
String readLastChecked(fs::FS &fs){
  String fileContent = "";
  File file = fs.open(lastCheckedNumberFilePath); // open the file
  if(!file || file.isDirectory()) // if the file does not exist, i.e, we are running the program for the first time
      fileContent = defaultLastChecked; // use the default lastChecked value we defined earlier
  while (file.available()){
    char charRead = file.read(); // read one character at a time
    fileContent += charRead; // build the String by appending each new character read to the exisitng string
  }
  file.close(); // close the file
  return fileContent;
}

// save the last checked number into the SPIFFS memory
bool saveLastChecked(fs::FS &fs, String lastCheckedString){
  File file = fs.open(lastCheckedNumberFilePath, FILE_WRITE); // open the file in write more. 
  // the FILE_WRITE mode overwrites anything pre-written in the file
  if(!file) // if file does not exist
      return false;
  if(!file.print(lastCheckedString)) // try to write the value to the file using file.print()
      return false; // return false if we can't write to the file
  file.close(); // close the file
  return true; // return true if everything goes alright
}

// A number is said to be converged (meaning it follows the conjecture) when the number becomes smaller 
// than the number we started with, after a finite iterations of applying the Collatz function to the number, 
// given that every number upto that starting number is known to follow the conjecture. 
// We can also put it as, when the number we are verifying reaches a smaller value than the last checked number
// after a finite iterations of applying the Collatz function to the number, we say that the number achieved 
// convergence, given that all numbers are known to be convergent upto the last checked number. 
String checkCollatz(){
  BigNumber lastChecked = BigNumber(lastCheckedString.c_str()); // convert the lsat checked number string to a BigNumber
  BigNumber num = BigNumber(lastChecked); // copy the value to another variable called num. we will work with this num variable
  // we can't add or multiply integers with BigNumber objects, so we turned commonly used integers into BigNumber objects
  BigNumber two = BigNumber("2");
  BigNumber three = BigNumber("3");

  num = num + two; // we know we are starting the check from an odd number. so just move to the next odd number to check
  while(true) { // loop to continue until the number converges
    if (num < lastChecked) { // the current number is lesser than the last checked number, meaning we achieved convergence. 
      break;
    }
    BigNumber moduloTwo = num % two; // check if the number is divisible by 2
    if(moduloTwo.isZero()){
      num = num/two; 
    } else {
      num = num * three;
      num++;
    }
  }
  lastChecked = lastChecked + two; // update the last checked number
  return lastChecked.toString(); // return the last checked number as a string
}

// make the last checked number an odd number by adding 1 to it, in case it's not. 
String makeLastCheckedOdd(String lastCheckedString) {
  BigNumber zero = "0";
  BigNumber two = "2";
  BigNumber lastChecked = BigNumber(lastCheckedString.c_str());
  if ((lastChecked % two) == zero){
    lastChecked++;
  }
  return lastChecked.toString();
}

// setup method
void setup ()
{
  Serial.begin (115200);
  Serial.println ();
  Serial.println ("Serial monitor started!");

  //SPIFFS.format(); // format for a fresh start (don't do it if not needed)

  // Starting the SPIFFS file system.
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
    Serial.println("SPIFFS Mount Failed!");
    return;
  }

  BigNumber::begin ();  // initialize BigNumber library
  
  // read the last checked from SPIFFS
  lastCheckedString = readLastChecked(SPIFFS);
  // Make the last checked number odd. This way we can skip every even number from being checked for convergence
  // by incrementing the iterator by 2 in checkCollatz() method, since every even number converges in one step anyways. 
  // This is because for all m = n/2, m<n, where n>2. 
  lastCheckedString = makeLastCheckedOdd(lastCheckedString);
  Serial.print("Starting to check collatz conjecture from: ");
  Serial.println(lastCheckedString);

  // get the start time in micro seconds
  long int startTime = micros();

  // check convergence of 10,000 numbers
  // the checkCollatz function skips every even number, so we are actually checking convergence 
  // of 10,000 numbers in 5000 iterations only. 
  for (int i=0; i<5000; i++){ 
    lastCheckedString = checkCollatz();
  }

  // save the last checked number in the SPIFFS memory
  saveLastChecked(SPIFFS, lastCheckedString); // save the last checked number in SPIFFS memory
  Serial.print("Collatz conjecture checked till: ");
  Serial.println(lastCheckedString);

  // get the end time in microseconds
  long int endTime = micros();
  // calculate the total time taken to check 10,000 numbers for convergence verification
  long int diffTime = endTime - startTime;
  Serial.println("Time taken for checking 10,000 numbers (in microseconds): " + String(diffTime));
} 

// nothing to loop. keeping it blank.
void loop () {
}