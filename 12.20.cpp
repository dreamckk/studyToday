#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <exception>
#include <12_2_19.h>
#include <fstream>

int main() {
	StrBlob b;
	string words;
	std::ifstream if1("../file/œ‡–≈Œ¥¿¥.txt");
	for (words; std::getline(if1,words);) {
		b.push_back(words);
	}
	for (StrBlobPtr pbeg(b.begin()), pend(b.end()); pbeg != pend; pbeg.incr()) {
		std::cout << pbeg.deref() << std::endl;
	}
	system("pause");
	return 0;
}