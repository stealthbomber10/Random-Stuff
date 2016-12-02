
/*
 * The Header (.h) file declares things that belong at the "head"
 * (beginning) of a file to explain some aspects of the contents
 * that follow.  Headers often specify the public interface to 
 * a library or class.  In this case it provides the function 
 * prototypes and comments indicating how they are used. 
 * (So a programmer who needs to use these functions shouldn't 
 *  have to study their source code in the .cpp file)
 */

#include<WString.h> // For access to the Arduino String class 

// Argument: A character (letter, digit, or valid Morse punctuation) 
// Return Value: Either:
//                1) If given a valid Morse symbol, a null-terminated string containing the 
//                   dots/dashes for the symbol. Ex: morseEncode('Q') returns "--.-"
//                2) If the symbol is a space, a string containing a space. 
//                   Ex: morseEncode(' ') returns " "
//                3) If the symbol isn't a valid Morse symbol, an empty string.
//                   Ex: morseEncode('#') returns ""
// Typical Usage:
//               String code = morseEncode('a');
extern const char* morseEncode(char symbol);

// Argument: A null-terminated C-string or String object with a pattern of dots and dashes.
// Return Value: Either 
//               1) If the dots and dashes represent a valid Morse symbol, that symbol.
//                  Ex: morseDecode("--.-") returns 'Q'
//               2) If the dots and dashes are not a valid symbol, null (the value 0).
//                  Ex: morseDecode("-.-.-") returns 0 (0, not the symbol '0')
extern char morseDecode(const char* code);
extern char morseDecode(String encoded);

// Argument: Any character
// Return Value: Either:
//                  1) If the character is a letter, the upper case equivalent.  
//                  2) If the character is not a letter, the original value.
extern char toUpper(char c);
