#ifndef HACKSYMBOLTABLE_H
#define HACKSYMBOLTABLE_H

#include <string>
#include <unordered_map>

class HackSymbolTable
{
    private:
        std::unordered_map<std::string, int> symbolTable; //for fast search
        int nextAvailableAddress;
        
    public:
        HackSymbolTable();
        ~HackSymbolTable();
        
        void addEntry(const std::string& symbol, int address);
        bool contains(const std::string& symbol);
        int getAddress(const std::string& symbol);
        void reset();
        void setNextAvailableAddress();
        int getNextAvailableAddress();
};

#endif // HACKSYMBOLTABLE_H