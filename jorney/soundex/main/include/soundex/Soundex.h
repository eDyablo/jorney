#pragma once

#include <string>
#include <unordered_map>

class Soundex {
	static const size_t MaxCodeLength = 4;

	const std::unordered_map<char, std::string> encodings;

public:
	const std::string NotADigit;

public:
	Soundex();

	std::string encode(const std::string& word) const;

	std::string encodedDigit(char letter) const;

private:
	static std::unordered_map<char, std::string> makeEncodings();

	std::string head(const std::string& word) const;

	std::string tail(const std::string& word) const;

	std::string upperFront(const std::string& word) const;

	std::string encodedDigits(const std::string& word) const;

	void encodeHead(std::string& encoding, const std::string& word) const;

	void encodeTail(std::string& encoding, const std::string& word) const;

	void encodeLetter(std::string& encoding, char letter, char prevLetter) const;

	bool isComplete(std::string& encoding) const;

	std::string lastDigit(const std::string& encoding) const;

	bool isVowel(char letter) const;

	std::string zeroPad(const std::string& word) const;

	char lower(char c) const;

	char upper(char c) const;
};
