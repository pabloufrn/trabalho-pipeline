#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <string>

/*! Define uma instrução
 *\note uma instrução pode ser nop, caso se queira criar bolhas (stalls)
 */
using namespace std;

class  Instruction
{
	public:
		string text;
        string inst;
		string r1; // registrador de escrita
		string r2; // registrador de leitura 1
		string r3; // registrador de leitura 2
		string memory_position; // só é usado nas instuções lw e sw
        // precondicao: o texto da instrucao eh valido
        Instruction(string = "0");
        friend std::ostream & operator<<(std::ostream &, const Instruction &);
};

struct Cycle
{
    enum Stage
    {
        IF,
        ID,
        EXE,
        MEM,
        WB,
        EOS // end of stages
    };
    
    Cycle();
    
    uint number = 1; 
    Instruction ift;
    Instruction idc;
    Instruction exe;
    Instruction mem;
    Instruction wbc;
    uint memory_number;
        
};

/*! Associa uma instrução a algum estágio;
 * \param ciclo ciclo para qual sera feita a tentativa de associação
 * \param inst intrução que será ou não associada
 * \return retona true, caso a instrução tenha sido associada ao ciclo; ou false caso contrário
 * \note a referencia do ciclo final sera um ciclo apos o ciclo de associacao
 */
bool assoc_instruction(Cycle & , const Instruction &);

/*! Imprime o ultimo ciclo e cria um novo baseado no anterior.
 * \param cyclo Último ciclo
 *
 */
void next_cycle(Cycle &, std::ostream &);
#endif
