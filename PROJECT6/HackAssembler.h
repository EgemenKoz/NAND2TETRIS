#ifndef HACKASSAMBLER_H
#define HACKASSAMBLER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "HackSymbolTable.h"
#include "HackCode.h"
#include "HackParser.h"

class HackAssembler {
    private:
        HackSymbolTable symbolTable;
        HackCode code;
        
    public:
        HackAssembler();
        ~HackAssembler();
        void assemble(const std::string& filename);
};

#endif // HACKASSAMBLER_H