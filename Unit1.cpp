//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "ClaseSah.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//Variabile Globale
TForm1 *Form1;
JocSah *JocSahNou;
AnsiString mesaj;

//Prototipuri functii
AnsiString codificare(AnsiString &mesaj,Piesa *piesa);
AnsiString codificareluare(AnsiString &mesaj,Piesa *piesa,Piesa *piesa2);
void decodificare(AnsiString &mesaj);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Form1->initializareImagineTablaJoc();
        JocSahNou=new JocSah();
        JocSahNou->creareJoc();
}


//----------------------------METODE--------------------------------------------

void TForm1::initializareImagineTablaJoc(){
       //pozitionare tabla
       TablaJocSah = new TImage(NULL);
       TablaJocSah->Parent = Form1;
       TablaJocSah->Stretch=true;
       TablaJocSah->Width=568;
       TablaJocSah->Height=568;
       TablaJocSah->Top=9.28;
       TablaJocSah->Left=9.28;
       TablaJocSah->Picture->LoadFromFile("tabla.bmp");

       //patrat ultima piesa neagra luata
       PiesaLuataNegru=new TImage(NULL);
       PiesaLuataNegru->Parent=Form1;
       PiesaLuataNegru->Left=650;
       PiesaLuataNegru->Top=200;
       PiesaLuataNegru->Width=60;
       PiesaLuataNegru->Height=60;
       PiesaLuataNegru->Picture->LoadFromFile("piesaluatanegru.bmp");

       //patrat ultima piesa alba luata
       PiesaLuataAlb=new TImage(NULL);
       PiesaLuataAlb->Parent=Form1;
       PiesaLuataAlb->Left=650;
       PiesaLuataAlb->Top=300;
       PiesaLuataAlb->Width=60;
       PiesaLuataAlb->Height=60;
       PiesaLuataAlb->Picture->LoadFromFile("piesaluataalb.bmp");
}
//______________________________________________________________________________

void JocSah::initializareImagini(){
 //incarcare patratele transparente si atribuire metode&stuff
 for(int i=0;i<DIM_TABLA;i++)
    for(int j=0;j<DIM_TABLA;j++)
    {
        imgTabla[i][j]=new TImage(NULL);
        imgTabla[i][j]->Parent=Form1;
        imgTabla[i][j]->Transparent=true;
        imgTabla[i][j]->Visible=true;
        imgTabla[i][j]->Center=true;
        imgTabla[i][j]->Top=tabla[i][j]->getY();
        imgTabla[i][j]->Left=tabla[i][j]->getX();
        imgTabla[i][j]->OnClick=tabla[i][j]->BoardClick;
        imgTabla[i][j]->OnMouseDown=tabla[i][j]->BoardRightClick;
        imgTabla[i][j]->Picture->LoadFromFile("transparent.bmp");
    }
 //incarcare piese si atribuire metode&stuff
 for(int i=0;i<PIESEMAX;i++)
 {
        imgPiesa[i]=new TImage(NULL);
        imgPiesa[i]->Parent=Form1;
        imgPiesa[i]->Transparent=true;
        imgPiesa[i]->Visible=true;
        imgPiesa[i]->Center=true;
        imgPiesa[i]->Top=tabla[piesa[i]->getX()][piesa[i]->getY()]->getY();
        imgPiesa[i]->Left=tabla[piesa[i]->getX()][piesa[i]->getY()]->getX();
        imgPiesa[i]->OnClick = piesa[i]->PieceClick;
        imgPiesa[i]->OnMouseDown=piesa[i]->PieceRightClick;
}

//incarcarea imaginilor pieselor in functie de tip si culoare
for(int i=0;i<PIESEMAX;i++)
{
        switch(piesa[i]->getTip())
        {
                case Pion:
               if(piesa[i]->getCuloare())
                        imgPiesa[i]->Picture->LoadFromFile("pionnegru.bmp");
                else
                        imgPiesa[i]->Picture->LoadFromFile("pionalb.bmp");break;
                case Cal:
                if(piesa[i]->getCuloare())
                        imgPiesa[i]->Picture->LoadFromFile("calnegru.bmp");
                else
                        imgPiesa[i]->Picture->LoadFromFile("calalb.bmp");break;
                case Nebun:
                if(piesa[i]->getCuloare())
                        imgPiesa[i]->Picture->LoadFromFile("nebunnegru.bmp");
                else
                        imgPiesa[i]->Picture->LoadFromFile("nebunalb.bmp");break;
                case Tura:
                if(piesa[i]->getCuloare())
                        imgPiesa[i]->Picture->LoadFromFile("turanegru.bmp");
                else
                        imgPiesa[i]->Picture->LoadFromFile("turaalb.bmp");break;
                case Regina:
                if(piesa[i]->getCuloare())
                        imgPiesa[i]->Picture->LoadFromFile("reginanegru.bmp");
                else
                        imgPiesa[i]->Picture->LoadFromFile("reginaalb.bmp");break;
                case Rege:
                if(piesa[i]->getCuloare())
                        imgPiesa[i]->Picture->LoadFromFile("regenegru.bmp");
                else
                        imgPiesa[i]->Picture->LoadFromFile("regealb.bmp");break;
        }
}
}
//______________________________________________________________________________

//Muta pe tabla, incarca patrat transparent pe fosta pozitie
void __fastcall Tabla::BoardClick(TObject *Sender){
        if(Form1->selectat==true)
        {
                JocSahNou->piesa[Form1->id_selectat]->Muta(this->getRand(),this->getColoana());
                JocSahNou->imgPiesa[Form1->id_selectat]->Left=this->getX();
                JocSahNou->imgPiesa[Form1->id_selectat]->Top=this->getY();
                JocSahNou->imgTabla[Form1->oldposx][Form1->oldposy]->Picture->LoadFromFile("transparent.bmp");

                codificare(mesaj,JocSahNou->piesa[Form1->id_selectat]);

                if(Form1->ServerSocket->Active==true) {
                        Form1->ServerSocket->Socket->Connections[0]->SendText(mesaj);
                }

                if(Form1->ClientSocket->Active==true) {
                        Form1->ClientSocket->Socket->SendText(mesaj);
                }
        }
        Form1->selectat=false;
}
//______________________________________________________________________________

//La click pe o piesa, se verifica daca sunt piese diferite(piesa se trimite in patratul cu piese luate)
void __fastcall Piesa::PieceClick(TObject *Sender){



         if((Form1->selectat==true) && this->getCuloare()!=Form1->culoarePiesa && this->getTip()!=6)
        {
                if(this->getCuloare()==Negru)
                {
                        JocSahNou->imgPiesa[this->getId()]->Left=630;
                        JocSahNou->imgPiesa[this->getId()]->Top=175;
                }

                else
                {
                        JocSahNou->imgPiesa[this->getId()]->Left=630;
                        JocSahNou->imgPiesa[this->getId()]->Top=275;
                }

                JocSahNou->piesa[Form1->id_selectat]->Muta(this->getX(),this->getY());
                JocSahNou->imgPiesa[Form1->id_selectat]->Left=JocSahNou->tabla[this->getX()][this->getY()]->getX();
                JocSahNou->imgPiesa[Form1->id_selectat]->Top=JocSahNou->tabla[this->getX()][this->getY()]->getY();
                JocSahNou->imgTabla[Form1->oldposx][Form1->oldposy]->Picture->LoadFromFile("transparent.bmp");
                Form1->selectat=false;

                codificareluare(mesaj,JocSahNou->piesa[Form1->id_selectat],this);

                if(Form1->ServerSocket->Active==true) {
                        Form1->ServerSocket->Socket->Connections[0]->SendText(mesaj);
                }

                if(Form1->ClientSocket->Active==true) {
                        Form1->ClientSocket->Socket->SendText(mesaj);
                }


        }
        else if(Form1->selectat==false)
        {
                Form1->id_selectat=this->getId();
                JocSahNou->imgTabla[this->getX()][this->getY()]->Picture->LoadFromFile("piesaselectata.bmp");
                Form1->oldposx=this->getX();
                Form1->oldposy=this->getY();
                Form1->selectat=true;
                Form1->culoarePiesa=this->getCuloare();
        }
       
}
//______________________________________________________________________________

//Se deselecteaza atat piesa, cat si patratul selectat de pe tabla
void __fastcall Tabla::BoardRightClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y){
        if(Button==mbRight)
        {
                Form1->selectat=false;
                JocSahNou->imgTabla[Form1->oldposx][Form1->oldposy]->Picture->LoadFromFile("transparent.bmp");
        }
}
//______________________________________________________________________________

void __fastcall Piesa::PieceRightClick(TObject *Sender, TMouseButton Button,TShiftState Shift, int X, int Y){
        if(Button==mbRight)
        {
                Form1->selectat=false;
                JocSahNou->imgTabla[Form1->oldposx][Form1->oldposy]->Picture->LoadFromFile("transparent.bmp");
        }
}


//---------------------------CODURI BUTOANE ------------------------------------


void __fastcall TForm1::btnExitClick(TObject *Sender)
{
        delete JocSahNou;
        exit(0);
}
//______________________________________________________________________________

void __fastcall TForm1::btnServerClick(TObject *Sender)
{
        ServerSocket->Active=true;
        btnServer->Hide();
        btnClient->Hide();
        circle1->Brush->Color=clGreen;
        consola->Show();
}
//______________________________________________________________________________

void __fastcall TForm1::btnClientClick(TObject *Sender)
{
        ClientSocket->Address=EditIP->Text;
        ClientSocket->Active=true;
        btnClient->Hide();
        btnServer->Hide();
        circle1->Brush->Color=clGreen;
        circle2->Brush->Color=clGreen;
}
//______________________________________________________________________________

void __fastcall TForm1::btnParClick(TObject *Sender)
{
        AnsiString strMessage =  "         Egalitate!    ";
        AnsiString strMessage2 = "Incepeti un joc nou";
	ShowMessage(strMessage + sLineBreak + strMessage2);
}
//______________________________________________________________________________

void __fastcall TForm1::btnSahClick(TObject *Sender)
{
        AnsiString strMessage =  "Jucatorul 1(Alb) v-a dat sah!";
	ShowMessage(strMessage);
}
//______________________________________________________________________________

void __fastcall TForm1::btnSahMatClick(TObject *Sender)
{
        AnsiString strMessage =  "Sah mat! Alb castiga!";
	ShowMessage(strMessage);
}
//______________________________________________________________________________

void __fastcall TForm1::btnSah2Click(TObject *Sender)
{
        AnsiString strMessage =  "Jucatorul 2(Mov) v-a dat sah!";
	ShowMessage(strMessage);
}
//______________________________________________________________________________

void __fastcall TForm1::btnSahMat2Click(TObject *Sender)
{
        AnsiString strMessage =  "Sah mat! Mov castiga!";
	ShowMessage(strMessage);
}
//______________________________________________________________________________
void __fastcall TForm1::ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        consola->Lines->Add("S-a conectat clientul ");
        consola->Lines->Add("Numele clientului este " + Socket->RemoteHost);
        consola->Lines->Add("Adresa clientului este " + Socket->RemoteAddress);
        circle2->Brush->Color=clGreen;
}
//______________________________________________________________________________

void __fastcall TForm1::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        AnsiString mesajprimit=Socket->ReceiveText();
        decodificare(mesajprimit);
}
//______________________________________________________________________________

void __fastcall TForm1::ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        AnsiString mesajprimit=Socket->ReceiveText();
        decodificare(mesajprimit);
}

void __fastcall TForm1::btnJocNouClick(TObject *Sender)
{
        delete JocSahNou;
        Form1->initializareImagineTablaJoc();
        JocSahNou=new JocSah();
        JocSahNou->creareJoc();
}

//----------------FUNCTII CODIFICARE SI DECODIFICARE----------------------------
AnsiString codificare(AnsiString &mesaj,Piesa *piesa)
{
        mesaj.Delete(1,mesaj.Length());  //initializez mesaj nul
        mesaj.Insert(piesa->getX(),1);
        mesaj.Insert(piesa->getY(),2);
        mesaj.Insert(piesa->getId(),3);
        return mesaj;  //pixel x pixel y id piesa
}
AnsiString codificareluare(AnsiString &mesaj,Piesa *piesa,Piesa *piesa2)
{
        mesaj.Delete(1,mesaj.Length());
        mesaj.Insert(piesa->getX(),1); 		// X Y de la prima ID piesa adversa
        mesaj.Insert(piesa->getY(),2);
        mesaj.Insert(piesa2->getId()+10,3);		//se suprascrie daca nu e 10(loc pt 2 cifre la id)
        mesaj.Insert(piesa->getId(),5);

        return mesaj;
}

void decodificare(AnsiString &mesaj)
{
        int coord1=mesaj[1]-48;
        int coord2=mesaj[2]-48;
        mesaj.Delete(1,2);

        if(mesaj.Length()>2)   //DECODIFICARE LUARE
        {
                int idluat=StrToInt(mesaj.SubString(1,2)); //ID-UL piesei luate din char in int
                idluat=idluat-10; //-10 DIN CODIFICARE LUARE PE CARE L-AM FOLOSIT SA OCUP 2 SPATII
                mesaj.Delete(1,2); //sterg ce am folosit
                int id=StrToInt(mesaj);// id-ul piesei care se  misca

	//daca am luat ceva, muta pe spatiul culorii coresp
                if(JocSahNou->piesa[idluat]->getCuloare()==Negru)
                {
                        JocSahNou->imgPiesa[idluat]->Left=630;
                        JocSahNou->imgPiesa[idluat]->Top=175;
                }

                else
                {
                        JocSahNou->imgPiesa[idluat]->Left=630;
                        JocSahNou->imgPiesa[idluat]->Top=275;
                }

                JocSahNou->imgPiesa[id]->Left=JocSahNou->tabla[coord1][coord2]->getX();
                JocSahNou->imgPiesa[id]->Top=JocSahNou->tabla[coord1][coord2]->getY();
                JocSahNou->piesa[id]->Muta(JocSahNou->tabla[coord1][coord2]->getRand(),JocSahNou->tabla[coord1][coord2]->getColoana());
        }

        else //DECODIFICARE SIMPLA
        {
                int id=StrToInt(mesaj);
                JocSahNou->imgPiesa[id]->Left=JocSahNou->tabla[coord1][coord2]->getX();
                JocSahNou->imgPiesa[id]->Top=JocSahNou->tabla[coord1][coord2]->getY();
                JocSahNou->piesa[id]->Muta(JocSahNou->tabla[coord1][coord2]->getRand(),JocSahNou->tabla[coord1][coord2]->getColoana());
        }
        mesaj.Delete(1,mesaj.Length());//GOLESTE MESAJ

}

//---------------------------------------------------------------------------

