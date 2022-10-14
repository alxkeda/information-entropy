#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <iostream>
#include <math.h>
#include <iomanip>

class Symbol {
    public:
        uint32_t frequency;
        long double entropy;
        Symbol();
};

class Metadata {
    public:
        static std::map<char, Symbol> collect_ordered_freq(std::string sequence);
        static void calc_entropy(std::map<char, Symbol>* metadata, int len);
        static long double count_entropy(std::map<char, Symbol> metadata, std::string sequence);
};

Symbol::Symbol() : frequency(1) {}

std::map<char, Symbol> Metadata::collect_ordered_freq(std::string sequence) { // collects counts of each symbol
    std::map<char, Symbol> metadata;
    for(char character : sequence) {
        if(metadata.find(character) == metadata.end()) {
            metadata[character] = Symbol();
        } else {
            metadata[character].frequency++;
        }
    }
    return metadata;
}

void Metadata::calc_entropy(std::map<char, Symbol>* metadata, int len) {
    for(std::map<char, Symbol>::const_iterator iter = (*metadata).begin(); iter != (*metadata).end(); ++iter) {
        (*metadata)[iter->first].entropy = -std::log2((long double)iter->second.frequency / (long double)len);
    }
}

long double Metadata::count_entropy(std::map<char, Symbol> metadata, std::string sequence) {
    long double entropy = 0;
    for(char c : sequence) {
        entropy += metadata[c].entropy;
    }
    return entropy;
}

int main() {

    std::ifstream f("../data/input.txt");
    std::stringstream buffer;
    buffer << f.rdbuf(); std::string input = buffer.str();

    std::map<char, Symbol> metadata = Metadata::collect_ordered_freq(input);
    Metadata::calc_entropy(&metadata, input.length());

    std::cout << std::fixed << std::setprecision(10) << Metadata::count_entropy(metadata, input) << std::endl;

}