#include <iostream>
#include "instruction.hpp"

Instruction::Instruction(string & str)
{
    this->text = str;
    
    // processa a string
    int ws = str.find_first_of(' ');    // white space index;
    string aux = str.substr(0, ws); 
    str = str.substr(ws+1, std::string::npos);
    
    if(aux == "nop");
    else if(aux == "j") 
    {
        
        ws = str.find_first_of(' ');
        r1 = str.substr(0, ws);
        str = str.substr(ws+1, std::string::npos);
        
        r2 = "\0";
        r3 = "\0";
        
    }
    else if(aux=="lw" || aux == "sw") 
    {
        
        ws = str.find_first_of(' ');
        r1 = str.substr(0, ws);
        str = str.substr(ws+1, std::string::npos);
        
        ws = str.find_first_of(' ');
        r2 = str.substr(0, ws);
        str = str.substr(ws+1, std::string::npos);
        
        r3 = "\0";
        
    }
    
    else
    {
        
        ws = str.find_first_of(' ');
        r1 = str.substr(0, ws);
        str = str.substr(ws+1, std::string::npos);
        
        ws = str.find_first_of(' ');
        r2 = str.substr(0, ws);
        str = str.substr(ws+1, std::string::npos);
        
        ws = str.find_first_of(' ');
        r3 = str.substr(0, ws);
        str = str.substr(ws+1, std::string::npos);
        
    }
}

std::ostream & operator<<(std::ostream &os, const Instruction &inst)
{
    os  <<  "\n{\nInstruction = "   << inst.text    << std::endl    \
        <<  "r1 = " <<  inst.r1     << std::endl                    \
        <<  "r2 = " <<  inst.r2     << std::endl                    \
        <<  "r3 = " <<  inst.r3 << "\n}";
    return os;
}
