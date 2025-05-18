#include "HackCode.h"
#include "HackParser.h"

HackCode::HackCode(HackSymbolTable& symTable) : symbolTable(symTable) {
}

HackCode::~HackCode() {
    // Nothing to clean up
}

static std::string castInstructiontoString(const uint16_t& value)
{
    std::string binary;
    
    // Convert to 16-bit binary representation
    for (int i = 15; i >= 0; i--) {
        binary += ((value >> i) & 1) ? '1' : '0';
    }
    
    return binary;
}

std::string HackCode::getCode(const std::string& mnemonic)
{   
    static HackParser parser;
    uint16_t value;
    
    if(mnemonic[0] == '@')
    {
        value = parser.parseAInstruction(mnemonic);
    }
    else
    {
        value = parser.parseCInstruction(mnemonic);
    }
    
    return castInstructiontoString(value);
}