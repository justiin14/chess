
#ifndef ClaseSahH
#define ClaseSahH
#include <StdCtrls.hpp>
#include <vcl.h>
#define DIM_TABLA 8
#define PIESEMAX 32
#define Alb false
#define Negru true
#define Pion 1
#define Cal 2
#define Nebun 3
#define Tura 4
#define Regina 5
#define Rege 6
//---------------------------------------------------------------------------
class Pozitie
{
        int x;
        int y;
  public:
        Pozitie(int x0,int y0);
        ~Pozitie(){};
		
        int getX(){return x;};
        int getY(){return y;};
		
        void setX(int x0){x=x0;};
        void setY(int y0){y=y0;};
};

class Tabla:public Pozitie
{
		int rand;
		int coloana;
public:
                Tabla();
		Tabla(int x0,int y0,int rand0,int coloana0);
		~Tabla(){};
		
		int getColoana(){return coloana;}
		int getRand(){return rand;}

                void __fastcall BoardClick(TObject *Sender);
                void __fastcall BoardRightClick(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y);


};

class Piesa:public Pozitie
{
		int tip,id;  //pt un switch-case la piese(#define type id)
		bool culoare;  //#define Alb false/Negru true
  public:
                Piesa();
		Piesa(int tip,bool culoare,int x,int y,int id0);
		~Piesa(){};
	
		int getTip(){return tip;};
		int getId(){return id;};
		bool getCuloare(){return culoare;};

		void Muta(int x0,int y0);
                void __fastcall PieceClick(TObject *Sender);
                void __fastcall PieceRightClick(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y);

};

class JocSah
{
  public:
        Tabla *tabla[DIM_TABLA][DIM_TABLA];
        Piesa *piesa[PIESEMAX];
        TImage *imgTabla[DIM_TABLA][DIM_TABLA];
        TImage *imgPiesa[PIESEMAX];

        JocSah(){};
        ~JocSah();
		
        void asezarePiese();
        void asezareTabla();
        void initializareImagini();
        void creareJoc();
};

#endif
