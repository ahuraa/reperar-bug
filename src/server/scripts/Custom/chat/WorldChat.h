using namespace std; 

string canal = "Chat_Web";
string Canal1 = "Mundo";
string ColorBase1 = "9bf943";
string GM_ICON1 = "|TINTERFACE/CHATFRAME/UI-CHATICON-BLIZZ:13:13:0:-1|t";
string Alianza1 = "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Human.png:13|t";
string Horda1 = "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Orc.png:13|t";


///Configuraciones WorldChat
enum Rango{ r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, rt };
enum RangoColor{ rc0, rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8, rc9, rc10, rct };
enum RangoColorChat{ rcc0, rcc1, rcc2, rcc3, rcc4, rcc5, rcc6, rcc7, rcc8, rcc9, rcc10, rcct };
enum ClaseColor{
	cc0,		//null
	cc1,		//warrior
	cc2,		//paladin
	cc3,		//hunter
	cc4,		//rogue
	cc5,		//priest
	cc6,		//dk
	cc7,		//shaman
	cc8,		//mage
	cc9,		//warlock
	cc10,		//
	cc11,		//druid
	cct
};

class worldchat
{
private:
	string rRango[rt];
	string rRangoColor[rct];
	string rRangoColorChat[rcct];
	string rClaseColor[cct];
public:
	static worldchat* instance();
	bool iniciado = false;
	void iniciar();

	void mensaje_db(uint32 account, std::string name, std::string  mensaje, std::string local);
	void mensaje();

	string GRango(uint8 rango){
		return rango < rt ? rRango[rango] : rRango[r1];
	};
	string GRangoColor(uint8 rango){
		return rango < rct ? rRangoColor[rango] : rRangoColor[rc1];
	};
	string GRangoColorChat(uint8 rango){
		return rango < rcct ? rRangoColorChat[rango] : rRangoColorChat[r1];
	};
	string GClaseColor(uint8 rango){
		return rango < cct ? rClaseColor[rango] : rClaseColor[cc1];
	};

};

#define sworldchat worldchat::instance()