#include <iostream>
#include "instruction.hpp"

using namespace std;
int main(void)
{
    // le a entrada
    // Enquanto tiver instrucoes, tente associalas
    string str_instrucion;
    Cycle cic;
    while(getline(cin, str_instrucion))
    {
        Instruction ins(str_instrucion);
#ifdef DEBUG
        {
            cout << "processando instrucao..." << ins << "\n";
        }
#endif
        while(!assoc_instruction(cic, ins))
        {
            next_cycle(cic);
            assoc_instruction(cic, Instruction("0"));
        }
        next_cycle(cic);

    }
}
