object Form1: TForm1
  Left = 215
  Top = 113
  Width = 1100
  Height = 615
  Caption = 'Joc Sah'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object circle1: TShape
    Left = 1096
    Top = 40
    Width = 17
    Height = 17
    Brush.Color = clRed
    Pen.Color = clRed
    Shape = stCircle
  end
  object circle2: TShape
    Left = 1096
    Top = 88
    Width = 17
    Height = 17
    Brush.Color = clRed
    Pen.Color = clRed
    Shape = stCircle
  end
  object Label1: TLabel
    Left = 1081
    Top = 280
    Width = 24
    Height = 25
    Caption = 'IP:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object consola: TMemo
    Left = 1072
    Top = 144
    Width = 201
    Height = 113
    Lines.Strings = (
      'consola')
    TabOrder = 0
  end
  object btnServer: TButton
    Left = 1120
    Top = 32
    Width = 113
    Height = 33
    Caption = 'Server'
    TabOrder = 1
    OnClick = btnServerClick
  end
  object btnClient: TButton
    Left = 1120
    Top = 80
    Width = 113
    Height = 33
    Caption = 'Client'
    TabOrder = 2
    OnClick = btnClientClick
  end
  object btnExit: TButton
    Left = 1096
    Top = 528
    Width = 113
    Height = 33
    Caption = 'Exit'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = btnExitClick
  end
  object btnSah: TButton
    Left = 632
    Top = 472
    Width = 113
    Height = 41
    Caption = 'Sah'
    TabOrder = 4
    OnClick = btnSahClick
  end
  object btnPar: TButton
    Left = 632
    Top = 414
    Width = 113
    Height = 43
    Caption = 'Par'
    TabOrder = 5
    OnClick = btnParClick
  end
  object btnSahMat: TButton
    Left = 632
    Top = 528
    Width = 113
    Height = 41
    Caption = 'Sah Mat'
    TabOrder = 6
    OnClick = btnSahMatClick
  end
  object btnSah2: TButton
    Left = 624
    Top = 24
    Width = 113
    Height = 41
    Caption = 'Sah'
    TabOrder = 7
    OnClick = btnSah2Click
  end
  object btnSahMat2: TButton
    Left = 624
    Top = 80
    Width = 113
    Height = 41
    Caption = 'Sah Mat'
    TabOrder = 8
    OnClick = btnSahMat2Click
  end
  object EditIP: TEdit
    Left = 1112
    Top = 280
    Width = 121
    Height = 21
    TabOrder = 9
    Text = '127.0.0.1'
  end
  object btnJocNou: TButton
    Left = 1096
    Top = 480
    Width = 113
    Height = 33
    Caption = 'Joc Nou'
    TabOrder = 10
    OnClick = btnJocNouClick
  end
  object ServerSocket: TServerSocket
    Active = False
    Port = 2100
    ServerType = stNonBlocking
    OnClientConnect = ServerSocketClientConnect
    OnClientRead = ServerSocketClientRead
    Left = 1191
    Top = 352
  end
  object ClientSocket: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 2100
    OnRead = ClientSocketRead
    Left = 1223
    Top = 352
  end
end
