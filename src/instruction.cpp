#include <iostream>
#include "instruction.hpp"

Instruction::Instruction(std::string str)
{

    this->text = str;
    // processa a string
    int ws = str.find_first_of(' ');    // white space or comma index;
    string aux = str.substr(0, ws); 
    str = str.substr(ws+1, std::string::npos);

    this->inst = aux;

    if(aux == "" || aux == "0" || aux == "nop"); // nop
    else if(aux == "j") 
    {

        ws = str.find_first_of(',');
        r1 = str.substr(0, ws);

        r2 = "\0";
        r3 = "\0";

    }
    else if(aux=="lw" || aux == "sw") 
    {

        ws = str.find_first_of(',');
        r1 = str.substr(0, ws);
        str = str.substr(ws+2, std::string::npos);
        
        ws = str.find_first_of('(');
        str = str.substr(ws+1, string::npos);

        ws = str.find_first_of(')');
        r2 = str.substr(0, ws);

        r3 = "\0";

    }

    else
    {
        ws = str.find_first_of(',');
        r1 = str.substr(0, ws);
        str = str.substr(ws+2, std::string::npos);

        ws = str.find_first_of(',');
        r2 = str.substr(0, ws);
        str = str.substr(ws+2, std::string::npos);

        ws = str.find_first_of(' ');
        r3 = str.substr(0, ws);

    }
}

Cycle::Cycle(): number(1)
{}
// precondicao: recebe um ciclo com um IF vazio
// este codigo esta propositalmente mal optimizado para facilitar a abstracao 
bool assoc_instruction(Cycle & cic, const Instruction & inst)
{
    // Dependência em posição de memória
    if(inst.inst == "lw" or inst.inst == "sw")
    {
        if(inst.r2 == cic.ift.r2)
            return false;
        if(inst.r2 == cic.idc.r2)
            return false;
        if(inst.r2 == cic.exe.r2)
            return false;
        if(inst.r2 == cic.mem.r2)
            return false;
    }

    // Testar dependencia em registrador
    // note que a Dependência em posição de memória será tratada aqui
    if(inst.r2 != "\0") // verifica se o r2 esta sendo usado para escrita em algum lugar
    { 
        if(inst.r2 == cic.ift.r1)
            return false;
        if(inst.r2 == cic.idc.r1)
            return false;
        if(inst.r2 == cic.exe.r1)
            return false;
        if(inst.r2 == cic.mem.r1)
            return false;
    }
    if(inst.r3 != "\0") // verifica se o r3 esta sendo usado para escrita em algum lugar
    { 
        if(inst.r3 == cic.ift.r1)
            return false;
        if(inst.r3 == cic.idc.r1)
            return false;
        if(inst.r3 == cic.exe.r1)
            return false;
        if(inst.r3 == cic.mem.r1)
            return false;
    }
    cic.ift = inst;
    return true; 
}

void next_cycle(Cycle & cic)
{
    std::cout <<    "-------------------------------------------------------\n" <<  \
        "Ciclo " << cic.number << std::endl <<                          \
        "BI:  " << cic.ift.text << std::endl     <<                          \
        "DI:  " << cic.idc.text << std::endl     <<                          \
        "EX:  " << cic.exe.text << std::endl     <<                          \
        "MEM: " << cic.mem.text << std::endl     <<                          \
        "WB:  " << cic.wbc.text << std::endl     <<                          \
        "-------------------------------------------------------\n";
    cic.wbc = cic.mem;
    cic.mem = cic.exe;
    cic.exe = cic.idc;
    cic.idc = cic.ift;
    cic.ift = Instruction("0");
    cic.number++;
    /*
       -------------------------------------------------------
       Ciclo 1
BI:  add $t0, $t1, $t2
DI:  0
EX:  0
MEM: 0
WB:  0
---------------------------------------------------------
*/
    return;
}

std::ostream & operator<<(std::ostream & os, const Instruction & inst)
{
    os  <<  "\n{\nInstruction = "   << inst.text    << std::endl    \
        <<  "r1 = " <<  inst.r1     << std::endl                    \
        <<  "r2 = " <<  inst.r2     << std::endl                    \
        <<  "r3 = " <<  inst.r3 << "\n}";
    return os;
}
