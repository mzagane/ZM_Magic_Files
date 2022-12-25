//---------------------------------------------------------------------------

#ifndef Main_UnitH
#define Main_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "magic.h"//Magic_Processing

class TMain_Form : public TForm
{
__published:	// IDE-managed Components
        TSpeedButton *Brows_SpeedButton;
        TLabel *File_Path_Label;
        TEdit *File_Path_Edit;
        TOpenDialog *OpenDialog1;
        TSpeedButton *Processing_SpeedButton;
        TEdit *Edit1;
        TButton *Button1;
        TButton *Button2;
        void __fastcall Brows_SpeedButtonClick(TObject *Sender);
        void __fastcall Processing_SpeedButtonClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMain_Form(TComponent* Owner);

        //Fonctions
        
};
//---------------------------------------------------------------------------
extern PACKAGE TMain_Form *Main_Form;
//---------------------------------------------------------------------------
#endif
