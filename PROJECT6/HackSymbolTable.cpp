#include "HackSymbolTable.h"

HackSymbolTable::HackSymbolTable()
{
    nextAvailableAddress = 16;

    // Initialize predefined symbols
    addEntry("SP", 0);
    addEntry("LCL", 1);
    addEntry("ARG", 2);
    addEntry("THIS", 3);
    addEntry("THAT", 4);
    addEntry("SCREEN", 16384);
    addEntry("KBD", 24576);

    for(int i = 0; i < 16; i++)
    {
        addEntry("R" + std::to_string(i), i);
    }
    
}

HackSymbolTable::~HackSymbolTable()
{
    reset();
}

void HackSymbolTable::reset()
{
    symbolTable.clear();
    nextAvailableAddress = 16;
}

void HackSymbolTable::setNextAvailableAddress()
{
    nextAvailableAddress++;
}

int HackSymbolTable::getNextAvailableAddress()
{
    return nextAvailableAddress;
}


void HackSymbolTable::addEntry(const std::string& symbol, int address)
{
    symbolTable[symbol] = address;
}

bool HackSymbolTable::contains(const std::string& symbol)
{
    return symbolTable.find(symbol) != symbolTable.end();
}

int HackSymbolTable::getAddress(const std::string& symbol)
{
    return symbolTable[symbol];
}

