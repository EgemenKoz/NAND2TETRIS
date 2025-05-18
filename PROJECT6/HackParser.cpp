#include "HackParser.h"
#include <cctype>

// Global variable to hold the symbol table pointer
static HackSymbolTable* g_symbolTablePtr = nullptr;

// Function to get reference to symbol table
static HackSymbolTable& GetSymbolTable() {
    // Use the global pointer set by SetSymbolTable
    if (!g_symbolTablePtr) {
        // Create a default symbol table if not set
        static HackSymbolTable defaultTable;
        g_symbolTablePtr = &defaultTable;
    }
    return *g_symbolTablePtr;
}

// Function to set the symbol table pointer
void HackParser::SetSymbolTable(HackSymbolTable* symTable) {
    // Set the global symbol table pointer
    g_symbolTablePtr = symTable;
}

HackParser::HackParser() {
    initializeTables();
}

HackParser::~HackParser() {
    // Nothing to clean up
}

// Helper function to check if a string is a valid symbol
bool isValidSymbol(const std::string& str) {
    if (str.empty()) return false;
    
    // First character must be a letter or one of the permitted symbols
    char first = str[0];
    if (!isalpha(first) && first != '_' && first != '.' && first != '$' && first != ':') {
        return false;
    }
    
    // Rest of characters can be letters, digits, or the permitted symbols
    for (size_t i = 1; i < str.length(); i++) {
        char c = str[i];
        if (!isalnum(c) && c != '_' && c != '.' && c != '$' && c != ':') {
            return false;
        }
    }
    
    return true;
}

void HackParser::initializeTables() {
    // Comp bits (a cccccc)
    compTable = {
        {"0",   0b0101010},
        {"1",   0b0111111},
        {"-1",  0b0111010},
        {"D",   0b0001100},
        {"A",   0b0110000}, {"M",   0b1110000},
        {"!D",  0b0001101},
        {"!A",  0b0110001}, {"!M",  0b1110001},
        {"-D",  0b0001111},
        {"-A",  0b0110011}, {"-M",  0b1110011},
        {"D+1", 0b0011111},
        {"A+1", 0b0110111}, {"M+1", 0b1110111},
        {"D-1", 0b0001110},
        {"A-1", 0b0110010}, {"M-1", 0b1110010},
        {"D+A", 0b0000010}, {"D+M", 0b1000010},
        {"D-A", 0b0010011}, {"D-M", 0b1010011},
        {"A-D", 0b0000111}, {"M-D", 0b1000111},
        {"D&A", 0b0000000}, {"D&M", 0b1000000},
        {"D|A", 0b0010101}, {"D|M", 0b1010101}
    };
    
    // Dest bits (ddd)
    destTable = {
        {"",    0b000},
        {"M",   0b001},
        {"D",   0b010},
        {"DM",  0b011}, {"MD", 0b011},
        {"A",   0b100},
        {"AM",  0b101}, {"MA", 0b101},
        {"AD",  0b110}, {"DA", 0b110},
        {"ADM", 0b111}, {"AMD", 0b111}, {"DAM", 0b111}, {"DMA", 0b111}, {"MAD", 0b111}, {"MDA", 0b111}
    };
    
    // Jump bits (jjj)
    jumpTable = {
        {"",    0b000},
        {"JGT", 0b001},
        {"JEQ", 0b010},
        {"JGE", 0b011},
        {"JLT", 0b100},
        {"JNE", 0b101},
        {"JLE", 0b110},
        {"JMP", 0b111}
    };
}

uint16_t HackParser::parseAInstruction(const std::string& mnemonic) {
    std::string symbolOrValue = mnemonic.substr(1); // Remove the '@' prefix
    uint16_t value = 0;

    // Try to convert the string to an integer
    std::stringstream ss(symbolOrValue);
    if (ss >> value) {
        // It's a numeric value, use it directly
        return (value & 0x7FFF); // 0x7FFF = 0111 1111 1111 1111 (ensures MSB is 0)
    } else if (isValidSymbol(symbolOrValue)) {
        // It's a symbol, look it up in the symbol table
        HackSymbolTable& symTable = GetSymbolTable();
        
        if (!symTable.contains(symbolOrValue)) {
            // Symbol not in table, it must be a variable (not a label)
            // Add it with the next available RAM address (starting from 16)
            int address = symTable.getNextAvailableAddress();
            symTable.addEntry(symbolOrValue, address);
            symTable.setNextAvailableAddress();
            return (address & 0x7FFF);
        } else {
            // Symbol is in the table, get its address
            // This is either a predefined symbol, a label, or a previously defined variable
            return (symTable.getAddress(symbolOrValue) & 0x7FFF);
        }
    }
    
    // If we reach here, it's an invalid value, return 0
    return 0;
}

uint16_t HackParser::parseCInstruction(const std::string& mnemonic) {
    uint16_t value = 0xE000; // Set the 3 MSBs to 1 (binary: 1110 0000 0000 0000)
    
    std::string dest = parseDestination(mnemonic);
    std::string comp = parseComputation(mnemonic);
    std::string jump = parseJump(mnemonic);
    
    // Set comp bits (bit 12 is a, bits 6-11 are cccccc)
    value |= (getCompCode(comp) << 6);
    
    // Set dest bits (bits 3-5 are ddd)
    value |= (getDestCode(dest) << 3);
    
    // Set jump bits (bits 0-2 are jjj)
    value |= getJumpCode(jump);
    
    return value;
}

std::string HackParser::parseDestination(const std::string& mnemonic) {
    size_t equalsPos = mnemonic.find('=');
    
    if (equalsPos != std::string::npos) {
        return mnemonic.substr(0, equalsPos);
    }
    
    return ""; // No destination
}

std::string HackParser::parseComputation(const std::string& mnemonic) {
    size_t equalsPos = mnemonic.find('=');
    size_t semicolonPos = mnemonic.find(';');
    
    if (equalsPos != std::string::npos) {
        if (semicolonPos != std::string::npos) {
            return mnemonic.substr(equalsPos + 1, semicolonPos - equalsPos - 1);
        } else {
            return mnemonic.substr(equalsPos + 1);
        }
    } else if (semicolonPos != std::string::npos) {
        return mnemonic.substr(0, semicolonPos);
    } else {
        return mnemonic;
    }
}

std::string HackParser::parseJump(const std::string& mnemonic) {
    size_t semicolonPos = mnemonic.find(';');
    
    if (semicolonPos != std::string::npos) {
        return mnemonic.substr(semicolonPos + 1);
    }
    
    return ""; // No jump
}

uint16_t HackParser::getDestCode(const std::string& dest) {
    return destTable.find(dest) != destTable.end() ? destTable[dest] : 0;
}

uint16_t HackParser::getCompCode(const std::string& comp) {
    return compTable.find(comp) != compTable.end() ? compTable[comp] : 0;
}

uint16_t HackParser::getJumpCode(const std::string& jump) {
    return jumpTable.find(jump) != jumpTable.end() ? jumpTable[jump] : 0;
}
