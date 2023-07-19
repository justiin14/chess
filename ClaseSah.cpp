//---------------------------------------------------------------------------


#pragma hdrstop

#include "ClaseSah.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Pozitie::Pozitie(int x0,int y0){
        x=x0;
        y=y0;
}

Tabla::Tabla(int x0,int y0,int rand0,int coloana0):Pozitie(x0,y0){
        rand=rand0;
        coloana=coloana0;
}

Piesa::Piesa(int tip0,bool culoare0,int x0,int y0,int id0):Pozitie(x0,y0){
        tip=tip0;
        culoare=culoare0;
        id=id0;
}

void Piesa::Muta(int x0,int y0){
        this->setX(x0);
        this->setY(y0);
}

void JocSah::asezarePiese(){
        int tipPiese[PIESEMAX] = {Pion, Pion, Pion, Pion, Pion, Pion, Pion, Pion, Pion, Pion, Pion, Pion, Pion, Pion,Pion, Pion, Nebun, Nebun, Nebun, Nebun, Cal, Cal, Cal, Cal, Tura, Tura, Tura, Tura, Regina, Regina, Rege, Rege};
        bool culoarePiese[PIESEMAX] = {Alb, Alb, Alb, Alb, Alb, Alb, Alb, Alb,Negru, Negru, Negru, Negru, Negru, Negru, Negru, Negru, Alb,Alb, Negru,Negru, Alb,Alb, Negru,Negru, Alb,Alb, Negru, Negru,Alb, Negru, Alb, Negru};
        int yCoordPieseInitial[PIESEMAX] = {6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 0, 0, 7, 7, 0, 0, 7, 7, 0, 0, 7, 0, 7, 0};
        int xCoordPieseInitial[PIESEMAX] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 2, 5, 2, 5, 1, 6, 1, 6, 0, 7, 0, 7, 3, 3, 4, 4};
        for(int i = 0 ; i < PIESEMAX ; i++)
        {
                piesa[i] = new Piesa(tipPiese[i], culoarePiese[i], xCoordPieseInitial[i], yCoordPieseInitial[i],i);

        }
}

void JocSah::asezareTabla(){
        int distPiece = 59.5781;
        for(int i = 0 ; i < DIM_TABLA ; i++)
                for(int j = 0 ; j < DIM_TABLA ; j++)
                      tabla[i][j] = new Tabla(35 + distPiece * i, 35 + distPiece * j,i,j);
}

void JocSah::creareJoc(){
        asezareTabla();
        asezarePiese();
        initializareImagini();
}

JocSah::~JocSah(){
       for(int i = 0 ; i < PIESEMAX ; i++)
                delete piesa[i];

	for(int i = 0 ; i < DIM_TABLA ; i++)
                for(int j = 0 ; j < DIM_TABLA ; j++)
                        delete tabla[i][j];

        for(int i = 0 ; i < DIM_TABLA ; i++)
                for(int j = 0 ; j < DIM_TABLA ; j++)
                {
                        delete imgTabla[i][j];
                }

        for(int i = 0 ; i < PIESEMAX ; i++)
        {
                delete imgPiesa[i];
        }

}

