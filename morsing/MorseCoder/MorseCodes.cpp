#include"MorseCodes.h"

#include<string.h>  // For strcmp

// Morse Code can also be thought of as a substitution cipher.  
// A "code word" (dots and dashes) is substituted for a symbol

// This struct provides the "structure" for one row of the substitution table
typedef struct {      // A struct is like a simple class with just public fields (no methods)
  char symbol;        // The Unencoded Symbol
  char *codeString;   // The Encoded value to substitute for the symbol
} Code;  

// **** The actual substitution table.  ****
// Codes via: http://morsecode.scphillips.com/morse2.html
// This is declared as "const" for two reasons:
//   1) Morse codes won't change (and shouldn't be changed by the program)
//   2) Declaring this const puts it in the "read-only" part of Memory (where the program 
//       code is also located).  The Arduino has little RAM compared to ROM. Making this 
//       const leaces more RAM available in case the program needs to use it)
// It's declared as static to confine the scope to this file (another file could also use 
// a variable called MorseCodeTable)
static const Code MorseCodeTable[] = { 
  {'A',".-"},
  {'B',"-..."},
  {'C',"-.-."},
  {'D',"-.."},
  {'E',"."},
  {'F',"..-."},
  {'G',"--."},
  {'H',"...."},
  {'I',".."},
  {'J',".---"},
  {'K',"-.-"},
  {'L',".-.."},
  {'M',"--"},
  {'N',"-."},
  {'O',"---"},
  {'P',".--."},
  {'Q',"--.-"},
  {'R',".-."},
  {'S',"..."},
  {'T',"-"},
  {'U',"..-"},
  {'V',"...-"},
  {'W',".--"},
  {'X',"-..-"},
  {'Y',"-.--"},
  {'Z',"--.."},
  {'0',"-----"},
  {'1',".----"},
  {'2',"..---"},
  {'3',"...--"},
  {'4',"....-"},
  {'5',"....."},
  {'6',"-...."},
  {'7',"--..."},
  {'8',"---.."},
  {'9',"----."},
  {'.',".-.-.-"},
  {',',"--..--"},
  {':',"---..."},
  {'?',"..--.."},
  {'\'',".----."},
  {'-',"-....-"},
  {'/',"-..-."},
  {'"',".-..-."},
  {'@',".--.-."},
  {'=',"-...-"},
  // Special, non-Morse codes
  {' '," "},
};

// The number of rows in the table (computed from the table itself)
static const unsigned MorseCodeTableSize = sizeof(MorseCodeTable)/sizeof(Code);

const char* morseEncode(char symbol) {
  // Treat the table somewhat like a Hash-map (A topic of Data Structures & Algorithms)
  //    The Symbol (letter) is the "Key"
  //    The Morse Code is the corresponding value
  //    The Hashcode function computes an index based on the Key
  
  // If it's a letter, look up the code
  char upper = toUpper(symbol);
  if(upper>='A' && upper<='Z') {
    return  MorseCodeTable[upper-'A'].codeString;
  }

  // If it's a digit, look up the code
  if(symbol>='0' && symbol<='9') {
    return MorseCodeTable[symbol-'0'+26].codeString;
  }

  // If it's another symbol, search for it and return a code if it's in the table
  for(int i=26+10;i<MorseCodeTableSize;i++) {
    if(MorseCodeTable[i].symbol == symbol) {
      return MorseCodeTable[i].codeString;
    }
  }
  // Default: Return no match
  return "";
}


// The function name morseDecode() is overloaded (same name can take different parameter lists):
//    There's a version that will work with an Arduino String object
//    and a version that works with C-style strings (character arrays)

// If the given code is in the table return the corresponding symbol
char morseDecode(const char* encoded) {
  // Try to find it in the table
  for(int i=0;i<MorseCodeTableSize;i++) {
    if(strcmp(MorseCodeTable[i].codeString, encoded) == 0) {
      return MorseCodeTable[i].symbol;
    }
  }
  return 0;  // Returns null if no valid symbol for the given code.
}

// Overloaded version simply calls the alternate version with appropriate data.
// Again, if the given code is in the table return the corresponding symbol
char morseDecode(String encoded) {
  return morseDecode(encoded.c_str());
}

