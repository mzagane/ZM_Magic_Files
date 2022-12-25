//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main_Unit.h"
#include <FileCtrl.hpp> //pour SelectDirectory
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain_Form *Main_Form;
//---------------------------------------------------------------------------
__fastcall TMain_Form::TMain_Form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Brows_SpeedButtonClick(TObject *Sender)
{
        if(OpenDialog1->Execute())
        {
                File_Path_Edit->Text = OpenDialog1->FileName;
        }
}


//---------------------------------------------------------------------------


void __fastcall TMain_Form::Processing_SpeedButtonClick(TObject *Sender)
{
        Magic_Processing(File_Path_Edit->Text.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Button1Click(TObject *Sender)
{
        AnsiString Dir;
        if(SelectDirectory("Choisir le Lecteur ou le dossier de base","",Dir))
        {
                Build(Dir);
        }

}
//---------------------------------------------------------------------------


void __fastcall TMain_Form::Button2Click(TObject *Sender)
{
        AnsiString t;

        char a[]="azerty";

        for(int i=1;i<=strlen(a);i++)
        {
                t.Insert(AnsiString(a[i]).c_str(),i);
        }

        ShowMessage(t);
}
//---------------------------------------------------------------------------

