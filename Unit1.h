//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMemo *consola;
        TButton *btnServer;
        TButton *btnClient;
        TButton *btnExit;
        TButton *btnSah;
        TButton *btnPar;
        TButton *btnSahMat;
        TButton *btnSah2;
        TButton *btnSahMat2;
        TShape *circle1;
        TShape *circle2;
        TServerSocket *ServerSocket;
        TClientSocket *ClientSocket;
        TEdit *EditIP;
        TLabel *Label1;
        TButton *btnJocNou;
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnServerClick(TObject *Sender);
        void __fastcall btnClientClick(TObject *Sender);
        void __fastcall btnParClick(TObject *Sender);
        void __fastcall btnSahClick(TObject *Sender);
        void __fastcall btnSahMatClick(TObject *Sender);
        void __fastcall btnSah2Click(TObject *Sender);
        void __fastcall btnSahMat2Click(TObject *Sender);
        void __fastcall ServerSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnJocNouClick(TObject *Sender);
private:	// User declarations
       TImage *TablaJocSah;
       TImage *PiesaLuataNegru;
       TImage *PiesaLuataAlb;
public:		// User declarations
        void initializareImagineTablaJoc();
        bool selectat;
        int id_selectat;
        int oldposx,oldposy;
        bool culoarePiesa;
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 