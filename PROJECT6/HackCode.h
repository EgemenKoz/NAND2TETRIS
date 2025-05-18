#ifndef HACKCODE_H
#define HACKCODE_H

#include <string>
#include <stdint.h>
#include <sstream>
#include "HackSymbolTable.h"

class HackCode {
    private:
        HackSymbolTable& symbolTable;
    
    public:
        HackCode(HackSymbolTable& symTable);
        ~HackCode();
        std::string getCode(const std::string& mnemonic);
};

#endif // HACKCODE_H