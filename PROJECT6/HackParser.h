#ifndef HACKPARSER_H
#define HACKPARSER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "HackSymbolTable.h"

class HackParser {
    private:
        // Tables for instruction components
        std::map<std::string, uint16_t> compTable;
        std::map<std::string, uint16_t> destTable;
        std::map<std::string, uint16_t> jumpTable;
        
        // Initialize lookup tables
        void initializeTables();
        
        // Check if string is a valid symbol (starts with a letter or certain symbols)
        bool isSymbol(const std::string& str);
        
    public:
        HackParser();
        ~HackParser();
        
        // Set the symbol table to use
        static void SetSymbolTable(HackSymbolTable* symTable);
        
        // Parse instruction components
        uint16_t parseAInstruction(const std::string& mnemonic);
        uint16_t parseCInstruction(const std::string& mnemonic);
        
        // Parse C-instruction parts
        std::string parseDestination(const std::string& mnemonic);
        std::string parseComputation(const std::string& mnemonic);
        std::string parseJump(const std::string& mnemonic);
        
        // Get binary code for instruction components
        uint16_t getDestCode(const std::string& dest);
        uint16_t getCompCode(const std::string& comp);
        uint16_t getJumpCode(const std::string& jump);
};

// Include HackCode.h here to break circular dependency
#include "HackCode.h"

#endif // HACKPARSER_H