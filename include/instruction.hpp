#include <string>

/*! Define uma instrução
 *\note uma instrução pode ser nop, caso se queira criar bolhas (stalls)
 */
using namespace std;

class  Instruction
{
	public:
		string text;
		string r1;
		string r2;
		string r3;
        // precondicao: o texto da instrucao eh valido
        Instruction(string &);
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
    
    Instruction ift;
    Instruction idc;
    Instruction exe;
    Instruction mem;
    Instruction wbc;
        
};

/*! Associa uma instrução a algum estágio;
 * \param ciclo ciclo para qual sera feita a tentativa de associação
 * \param inst intrução que será ou não associada
 * \return retona true, caso a instrução tenha sido associada ao ciclo; ou false caso contrário
 * \note a referencia do ciclo final sera um ciclo apos o ciclo de associacao
 */
bool assoc_intruction(Cycle & , const Instruction &);

/*! Imprime o ultimo ciclo e cria um novo baseado no anterior.
 * \param cyclo Último ciclo
 *
 */
void next_ciclo(Cycle &);







