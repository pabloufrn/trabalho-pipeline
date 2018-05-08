#include <iostream>
#include <stringstream>

using namespace std;
int main(void)
{
    // le a entrada
    
    // Enquanto tiver instrucoes, tente associalas
    string instrucion;
    while(getline(cin, instrucion))
    {
#ifdef DEBUG
        cout << "processando instrucao: " << instrucion << endl;
#endif
    }
}
