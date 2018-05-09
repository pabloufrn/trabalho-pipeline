#include <iostream>
#include "instruction.hpp"

using namespace std;
int main(void)
{
    // le a entrada
    // Enquanto tiver instrucoes, tente associalas
    string str_instrucion;
    while(getline(cin, str_instrucion))
    {
#ifdef DEBUG
        {
            Instruction ins(str_instrucion);
            cout << "processando instrucao..." << ins << "\n";
        }
#endif
    }
}
