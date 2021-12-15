/*
 * Helper program to be used for ECE 6745 Final Project
 * Converts a string into its hexadecimal representation
 * then generates its corresponding polynomials
 */

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <unordered_map>
#include <vector>

std::string generate_poly(std::string poly_name, char var, std::string bits, std::string byte_name); 
std::string to_hex(std::string bits);
void write_file(std::string filename, std::vector<std::string> lines);
//void convert(std::string name, std::string filename, std::string poly_name, std::string byte_name, std::string text);
void convert(std::string name, std::string filename, std::string byte_name, std::string text);
std::string bytes_to_text(std::string bytes);
int hex_to_int(char hex);

static const std::unordered_map<std::string, char> bin_to_hex = 
{{"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
 {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
 {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
 {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};

int main(int argc, char *argv[]) {
  // Store name of string to convert
  std::string name = argv[1];

  // Store base name of the polynomials that represent this string (e.g. p for poly p0 = ...)
  //std::string poly_name = argv[2];

  // Store base name of each byte of the message (e.g. k for k_0 to k_3)
  // Polynomials are given name k0-k3 and byte variables are k_0 to k_3
  std::string byte_name = argv[2];

  // Store the filename
  std::string filename = argv[3];
  
  // Store text or bytes to convert
  std::string text = argv[4];

  // If bytes were passed in, convert to text first
  if(text.length() > 4) {
    text = bytes_to_text(text);
    std::cout << "Converted input bytes to text: " << text << std::endl;
  }

  convert(name, filename, byte_name, text);
  return 0;
}

/**
 * Reads a string from stdin and converts it to a set of 
 * polynomials. The polynomials are written to the corresponding file
 */
//void convert(std::string name, std::string filename, std::string poly_name, std::string byte_name, std::string text) {
void convert(std::string name, std::string filename, std::string byte_name, std::string text) {
  char root_name = 'A';

  std::vector<std::string> lines;

  lines.push_back("// Polynomials for " + name);

  // Convert text to hex representation and polynomials
  for(int i = 0; i < text.length(); i++) {
    char ch = text[i];
    std::string bits = std::bitset<8>((int)ch).to_string();
    std::string poly = generate_poly(byte_name + std::to_string(i), root_name, bits, byte_name + "_" + std::to_string(i));
    std::cout << "Converting: " << ch << " = " << to_hex(bits) << " to " << poly << std::endl;
    lines.push_back(poly);
  }

  write_file(filename, lines);
  std::cout << "Polynomials written to " << filename << std::endl;
}

/**
 * Converts an byte from binary into its hex representation
 */
std::string to_hex(std::string bits) {
  std::ostringstream ss;
  ss << "0x";
  ss << bin_to_hex.at(bits.substr(0, 4));
  ss << bin_to_hex.at(bits.substr(4, 4));
  return ss.str();
}

std::string generate_poly(std::string poly_name, char var, std::string bits, std::string byte_name) {
  std::ostringstream ss;
  // Generate declaration
  ss << "poly " << poly_name << " = ";

  // Add byte name
  ss << byte_name;

  // Generate the polynomial from the bits
  int exp = bits.length() - 1;
  for(int i = 0; i < bits.length() && exp >= 0; i++) {
    if(bits[i] == '1') {
      ss << " + " << var << exp; 
    }
    exp--;
  }

  // End the line
  ss << ";";

  return ss.str();
}

void write_file(std::string filename, std::vector<std::string> lines) {
  std::ofstream outfile;
  outfile.open(filename);

  for(std::string s : lines) {
    outfile << s << std::endl;
  }

  outfile.close();
}

std::string bytes_to_text(std::string bytes) {
  std::string s = "";
  for(int i = 0; i < bytes.length(); i += 2) {
    int t1 = hex_to_int(bytes[i]); 
    int t2 = hex_to_int(bytes[i+1]); 

    char ch = (char)((t1 << 4) | t2);
    s.push_back(ch);
  }
  return s;
}

int hex_to_int(char hex) {
  int val;
  switch(hex) {
    case 'A':
    case 'a':
      return 10;
    case 'B':
    case 'b':
      return 11;
    case 'C':
    case 'c':
      return 12;
    case 'D':
    case 'd':
      return 13;
    case 'E':
    case 'e':
      return 14;
    case 'F':
    case 'f':
      return 15;
    default:
      return (int)hex - '0';
  }

}
