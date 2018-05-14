#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include "instruction.hpp"

using namespace std;

int main( int argc, char * argv[] )
{
    // le a entrada
    // Enquanto tiver instrucoes, tente associalas
    ifstream * in_file;
    ofstream * out_file;
    istream  * is = &cin;
    ostream  * os = &cout;
    if(argc >= 2)
    {
        for(auto i(1); i < argc; i++)
        {
            if(argv[i][0] == '-' and argv[i][1] == 'o')
            {
                out_file = new ofstream(argv[i+1]);
                os = out_file;
            }
            else
            {
                in_file = new ifstream(argv[i]);
                is = in_file;
            }
        }
    }
    
    string str_instruction;
    Cycle cic;
    cout << "Numero de mémorias ou primeira instrução:\n";
    if ( ! getline(cin, str_instruction) )
    {
        cout << "[Runtime error]: Invalid input\nExiting...\n";
        return 1;
    }else
    {
        try 
        {
            cic.memory_number = stoi(str_instruction);
        } 
        catch( const std::invalid_argument & e  )
        {
            cic.memory_number = 1; 
        }
    }
    getline(*is, str_instruction);
    Instruction ins;
    vector<Instruction> ins_list;
    char answer;
    do
    {
        if(str_instruction[0] == ' ' or str_instruction[0] == '\0')
            continue;
        ins = Instruction(str_instruction);
        ins_list.push_back(ins);
        // se for uma label adicione na lista, mas continue
        if(str_instruction.find_first_of(':') != string::npos)
            continue;
        
#ifdef DEBUG
        {
            cout << "Processando instrucao..." << ins << "\n";
        }
#endif
        if(ins.inst != "j")
        {
            while(!assoc_instruction(cic, ins))
            {
                next_cycle(cic, *os);
                assoc_instruction(cic, Instruction("0"));
            }
            next_cycle(cic, *os);
        }
        
        // se for um branch, pergunta ao usuario se o branch foi tomado.
        
        if(ins.inst == "beq")
        {
            cout << "O salto irá ocorrer? (s/n): ";
            cin >> answer;
            if(answer == 's')
            {
                ins.inst = "j";
                ins.r1 = ins.r3; 
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } 
        // se for um jump, procure a label e processe todas as instruções seguintes
        if(ins.inst == "j")
        {
            bool found = false;
            vector<Instruction>::iterator begin = ins_list.begin();
            vector<Instruction>::iterator end = ins_list.end() - 1;
            // prucura nas instruções já processadas
            
            while(begin < end)
            {
                if(begin->inst == ins.r1 + ":")
                {
                    found = true;
                    ++begin;
                    break;
                }
            }
            
            // se achar, processe todas as instruções armazenadas depois da label e continue a execução
            if(found == true)
            {
                while(begin < end)
                {
                    while(!assoc_instruction(cic, *begin))
                    {
                        next_cycle(cic, *os);
                        assoc_instruction(cic, Instruction("0"));
                    }
                    next_cycle(cic, *os);
                }
                continue;
            }
            // se não achar procura nas instrucoes posteriores
            else
            {
                Instruction current_instruction;
                while(getline(*is, str_instruction))
                {
                    current_instruction = Instruction(str_instruction);
                    ins_list.push_back(current_instruction);
                    if(current_instruction.inst == ins.r1 + ":")
                    {
                        found = true;
                        break;
                    }
                }
            }
            // se achar continue a execução
            if(found == true)
            {
                continue;
            }
            else
            {
                cout << "[Runtime error] Label not found.\n";
                return 1;
            }
        }

    }while(getline(*is, str_instruction));
    // termina os ciclos
    next_cycle(cic, *os);
    next_cycle(cic, *os);
    next_cycle(cic, *os);
    next_cycle(cic, *os);
}




























