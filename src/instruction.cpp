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
        str = str.substr(ws+1, std::string::npos);
        
        ws = str.find_first_not_of(' ');
        str = str.substr(ws, std::string::npos);
        
        ws = str.find_first_of('(');
        memory_position = str.substr(0, ws);
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
    // -- Dependência em posição de memória
    if(inst.inst == "sw" || inst.inst == "lw")
    {
        if(cic.wbc.inst == "sw" and inst.memory_position == cic.wbc.memory_position)
            return false;
    }

    // -- Dependência em registrador e RAW - read-after-write
    if(inst.inst != "sw" and inst.r2 != "\0") // verifica se o r2 esta sendo usado para escrita em algum lugar
    { 
        if(cic.idc.inst != "sw" and inst.r2 == cic.idc.r1)
            return false;
        if(cic.exe.inst != "lw" and cic.exe.inst != "sw" and inst.r2 == cic.exe.r1)
            return false;
        if(cic.mem.inst != "lw" and cic.exe.inst != "sw" and inst.r2 == cic.mem.r1)
            return false;
    }
    if(inst.r3 != "\0") // verifica se o r3 esta sendo usado para escrita em algum lugar
    { 
        if(cic.idc.inst != "sw" and inst.r3 == cic.idc.r1)
            return false;
        if(cic.exe.inst != "sw" and inst.r3 == cic.exe.r1)
            return false;
        if(cic.mem.inst != "sw" and inst.r3 == cic.mem.r1)
            return false;
    }
    // Caso especial do sw. O sw lê de r1.
    if(inst.inst == "sw")
    {
        if(inst.r1 == cic.ift.r1)
            return false;
        if(inst.r1 == cic.idc.r1)
            return false;
        if(inst.r1 == cic.exe.r1)
            return false;
        if(inst.r1 == cic.mem.r1)
            return false;
    }
    // -- Conflitos estruturais
    
    uint memory_count = 1; // mede a quantidade de memorias que estão sendo usadas
    // Verifica se eh possivel encaixar a instruction dependendo da quantidade de memórias.
    if(cic.mem.inst == "lw" or cic.mem.inst == "sw")
        ++memory_count;
    if(cic.wbc.inst == "sw")
        ++memory_count;
    if(memory_count > cic.memory_number)
        return false;
    // Se a instrução atual for de memoria
    if(inst.inst == "lw" or inst.inst == "sw")
    {
        // Verifica se está fazendo o decode de alguma instrução que use o write-back
        // e, se tiver só uma mémoria, não poderemos encaixar a instrução.
        if(cic.idc.inst == "sw" and cic.memory_number == 1)
            return false;
    }
    
    cic.ift = inst;
    return true; 
}

void next_cycle(Cycle & cic, std::ostream & os)
{
    os  <<                                                                  \
        "-------------------------------------------------------\n" <<      \
        "Ciclo " << cic.number  << std::endl      <<                        \
        "BI:   " << cic.ift.text << std::endl     <<                        \
        "DI:   " << cic.idc.text << std::endl     <<                        \
        "EX:   " << cic.exe.text << std::endl     <<                        \
        "MEM:  " << cic.mem.text << std::endl     <<                        \
        "WB:   " << cic.wbc.text << std::endl     <<                        \
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
