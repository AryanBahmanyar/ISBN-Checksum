#include <algorithm>  // for std::transform
#include <iostream>
#include <regex>
#include <string>

void prompt_input() {
	std::cout << std::endl;
	std::cout << "Enter all digits except for the last one to get the check digit, or enter the full ISBN to\n"
			  << "validate it, based on its checksum (or type (Q)uit):"
			  << std::endl;
}

int get_checksum(const std::string& input) {
	int a = 0;
	int checksum = 0;
	
	// ISBN-10
	if (input.length() <= 10) {
		for (int i = 0; i < 9; i++) {
			int d = std::stoi(std::string(1, input[i]));
			a += (d * (10 - i));
		}
		checksum = (11 - (a % 11)) % 11;
	}
	// ISBN-13
	else {
		int b = 0;
		
		for (int i = 0; i < 12; i++) {
			int d = std::stoi(std::string(1, input[i]));
			
			if (i % 2 == 0) a += d;
			else b += d;
		}
		b *= 3;
		checksum = (10 - (a + b) % 10) % 10;
	}
	return checksum;
}

void print_checksum(const std::string& input) {
	int check_digit = get_checksum(input);
	bool isbn_10 = input.length() <= 10;
	
	std::string check_str = check_digit == 10 ? (isbn_10 ? "X" : "0") : std::to_string(check_digit);
	std::string isbn;
	
	if (isbn_10) isbn += std::string(1, input[0]) + "-" + input.substr(1, 4) + "-" + input.substr(4, 9) + "-" + check_str;
	else isbn += input.substr(0, 3) + "-" + input.substr(3, 5) + "-" + input.substr(5, 10) + "-" + input.substr(10, 12) + "-" + check_str;
	
	std::cout << std::endl;
	std::cout << "Checksum: " << check_str << std::endl;
	std::cout << "ISBN-1" << (isbn_10 ? "0" : "3") << ":  " << isbn << std::endl;
}

void validate_checksum(const std::string& input) {
	int digit = input.back() == 'X' || input.back() == 'x' ? 10 : std::stoi(std::string(1, input.back()));
	int checksum = get_checksum(input);
	bool valid = digit == checksum;
	
	std::cout << std::endl;
	std::cout << "The checksum is" << (valid ? "" : " not") << " valid" << std::endl;
	if (!valid) std::cout << "The actual checksum is: " << checksum << std::endl;
}

// helper function to return lowercase version of string
std::string lowercase(const std::string& str) {
	std::string result(str.size(), '\0');
	std::transform(str.begin(), str.end(), result.begin(), [](unsigned char c) {
		return static_cast<char>(std::tolower(c));
	});
	return result;
}

int main() {
	std::cout << "An International Standard Book Number (ISBN) is used as an identifier for each item published,\n"
			  << "primarily books. The last digit is the check digit and is used for validating the ISBN. ISBNs\n"
			  << "come in 2 forms; ISBN-10 and ISBN-13, the latter of which starts with the digits, 978.\n\n"
			  << "More info at: https://en.wikipedia.org/wiki/ISBN"
			  << std::endl;
	prompt_input();
	
	while (true) {
		std::string input;
		std::cout << "> ";
		std::getline(std::cin, input);
		
		input = std::regex_replace(input, std::regex("[-_\\s]"), "");
		std::regex pattern("\\d{1,}[Xx]?");
		
		if (std::regex_match(input, pattern)) {
			size_t input_len = input.length();
			bool validating = input_len == 10 || input_len == 13;
			
			if (input_len != 9 && input_len != 12 && !validating) {
				std::cout << "Please enter a sequence with a valid number of digits" << std::endl;
				continue;
			}
			if (input_len > 10 && input.substr(0, 3) != "978") {
				std::cout << "ISBN-13 must begin with the digits, 978" << std::endl;
				continue;
			}
			if (validating)
				validate_checksum(input);
			else
				print_checksum(input);
			
			prompt_input();
			continue;
		}
		else {
			input = lowercase(input);
			
			if (input == "q" || input == "quit") {
				std::cout << "Exiting program..." << std::endl;
				return 0;
			}
		}
		std::cout << "Please enter a valid sequence of digits" << std::endl;
	}
	return 0;
}
