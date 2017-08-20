
using namespace std;

typedef struct filtro
{
	void SCantidad(int c)
	{
		Cantidad = c;
		Texto = new string[c];
		Accion = new int[c];
	}
	int Cantidad;
	string* Texto;
	int* Accion;
};

class filtrochat
{
public:
	static filtrochat* instance();
	void Iniciar();
	bool Activar = false;
	bool Iniciado = false;
	filtro Censura;
	

};

#define sfiltrochat filtrochat::instance()