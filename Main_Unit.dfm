object Main_Form: TMain_Form
  Left = 180
  Top = 113
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'ZM Magic File'
  ClientHeight = 320
  ClientWidth = 484
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Brows_SpeedButton: TSpeedButton
    Left = 336
    Top = 120
    Width = 137
    Height = 33
    Caption = '&Parcourir'
    OnClick = Brows_SpeedButtonClick
  end
  object File_Path_Label: TLabel
    Left = 24
    Top = 88
    Width = 44
    Height = 13
    Caption = 'Chemin : '
  end
  object Processing_SpeedButton: TSpeedButton
    Left = 152
    Top = 200
    Width = 225
    Height = 41
    Caption = '&Traiter'
    OnClick = Processing_SpeedButtonClick
  end
  object File_Path_Edit: TEdit
    Left = 72
    Top = 88
    Width = 401
    Height = 21
    TabOrder = 0
  end
  object Edit1: TEdit
    Left = 168
    Top = 152
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'Edit1'
  end
  object Button1: TButton
    Left = 152
    Top = 256
    Width = 225
    Height = 41
    Caption = 'Build'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 120
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 3
    OnClick = Button2Click
  end
  object OpenDialog1: TOpenDialog
    Left = 376
    Top = 16
  end
end
