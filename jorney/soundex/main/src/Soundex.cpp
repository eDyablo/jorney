#include "soundex/Soundex.h"

#include <locale>

Soundex::Soundex()
	: encodings(makeEncodings())
	, NotADigit("*") {
}

std::string Soundex::encode(const std::string& word) const {
	return zeroPad(upperFront(head(word)) + tail(encodedDigits(word)));
}

std::string Soundex::encodedDigit(char letter) const {
	auto found = encodings.find(lower(letter));
	return found != encodings.end() ? found->second : NotADigit;
}

std::unordered_map<char, std::string> Soundex::makeEncodings() {
	std::unordered_map<char, std::string> e;
	e['b'] = "1", e['f'] = "1", e['p'] = "1", e['v'] = "1";
	e['c'] = "2", e['g'] = "2", e['j'] = "2", e['k'] = "2", e['q'] = "2", e['s'] = "2", e['x'] = "2", e['z'] = "2";
	e['d'] = "3", e['t'] = "3";
	e['l'] = "4";
	e['m'] = "5", e['n'] = "5";
	e['r'] = "6";
	return e;
}

std::string Soundex::head(const std::string& word) const {
	return word.substr(0, 1);
}

std::string Soundex::tail(const std::string& word) const {
	return word.substr(1);
}

std::string Soundex::upperFront(const std::string& word) const {
	return std::string(1, upper(word.front()));
}

std::string Soundex::encodedDigits(const std::string& word) const {
	std::string encoded;
	encodeHead(encoded, word);
	encodeTail(encoded, word);
	return encoded;
}

void Soundex::encodeHead(std::string& encoding, const std::string& word) const {
	encoding += encodedDigit(word.front());
}

void Soundex::encodeTail(std::string& encoding, const std::string& word) const {
	for (auto i = 1u; i < word.length(); ++i) {
		if (!isComplete(encoding))
			encodeLetter(encoding, word[i], word[i - 1]);
	}
}

void Soundex::encodeLetter(std::string& encoding, char letter, char prevLetter) const {
	auto digit = encodedDigit(letter);
	if (digit != NotADigit && (digit != lastDigit(encoding) || isVowel(prevLetter)))
		encoding += digit;
}

bool Soundex::isComplete(std::string& encoding) const {
	return encoding.length() == MaxCodeLength;
}

std::string Soundex::lastDigit(const std::string& encoding) const {
	return encoding.empty() ? NotADigit : std::string(1, encoding.back());
}

bool Soundex::isVowel(char letter) const {
	const std::string vowels = "aeiouy";
	return vowels.find(letter) != std::string::npos;
}

std::string Soundex::zeroPad(const std::string& word) const {
	auto zerosNeeded = MaxCodeLength - word.length();
	return word + std::string(zerosNeeded, '0');
}

char Soundex::lower(char c) const {
	std::locale loc;
	return std::tolower(c, loc);
}

char Soundex::upper(char c) const {
	std::locale loc;
	return std::toupper(c, loc);
}