﻿/*
╔══╦╗╔╗╔╦══╗╔══╗╔══╗  ╔══╦══╦════╦╗╔╗  ╔╗─╔══╦╗╔╦╗─╔╦══╦╗╔╦═══╦═══╗
║╔═╣║║║║║╔╗║║╔═╝╚╗╔╝  ║╔═╩╗╔╩═╗╔═╣║║║  ║║─║╔╗║║║║╚═╝║╔═╣║║║╔══╣╔═╗║
║╚═╣║║║║║╚╝╚╣╚═╗─║║   ║╚═╗║║──║║─║╚╝║  ║║─║╚╝║║║║╔╗─║║─║╚╝║╚══╣╚═╝║
╚═╗║║║║║║╔═╗║╔═╝─║║   ╚═╗║║║──║║─║╔╗║  ║║─║╔╗║║║║║╚╗║║─║╔╗║╔══╣╔╗╔╝
╔═╝║╚╝╚╝║╚═╝║║──╔╝╚╗  ╔═╝╠╝╚╗─║║─║║║║  ║╚═╣║║║╚╝║║─║║╚═╣║║║╚══╣║║║
╚══╩═╝╚═╩═══╩╝──╚══╝  ╚══╩══╝─╚╝─╚╝╚╝  ╚══╩╝╚╩══╩╝─╚╩══╩╝╚╩═══╩╝╚╝
Created by FOXente (Aradam)
License GPL-3.0
*/

#include <vcl.h>
#pragma hdrstop

#include "API.h"

#include "UnitLogo.h"
#include "UnitMainMenu.h"
#include "UnitSettings.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TAPIdata *APIdata;

__fastcall TAPIdata::TAPIdata (TComponent* Owner) : TForm (Owner)
 {
 }

//Vars for saving main data
TMemIniFile *SettingsFile = new TMemIniFile (GetLauncherDataPath () + "Settings.ini");
TMemIniFile *LanguageFile = new TMemIniFile ("");
UnicodeString LanguageStrings [100];

//Don't change theese consts
UnicodeString Author = "FOXente (Aradam)";

//Get GameData folder's path
UnicodeString GetGameDataPath ()
 {
  return ExtractFilePath (Application -> ExeName) + "GameData/";
 }

//Get LauncherData folder's path
UnicodeString GetLauncherDataPath ()
 {
  return ExtractFilePath (Application -> ExeName) + "LauncherData/";
 }

//Get file name without extension
UnicodeString GetOnlyFileName (UnicodeString FilePath)
 {
  return StringReplace (ExtractFileName (FilePath), ExtractFileExt (FilePath), "", TReplaceFlags ());
 }

//If ident doesnt exists that will writed this value in new ident
UnicodeString WriteNewStringToIniFile (TMemIniFile *IniFile, UnicodeString Section, UnicodeString Ident, UnicodeString Value)
 {
  Value = IniFile -> ReadString (Section, Ident, Value);
  IniFile -> WriteString (Section, Ident, Value);
  return Value;
 }

//Replace string mask with replacement
UnicodeString ReplaceStringMask (UnicodeString CurrentString, UnicodeString Mask, UnicodeString Replacement)
 {
  return StringReplace (CurrentString, "%" + Mask + "%", Replacement, TReplaceFlags () << rfReplaceAll);
 }

//Converte boolean to string type
String BoolToRealString (bool Value)
 {
  if (Value) return "true"; else return "false";
 }

//If file doesn't exists that will be error shown and the application terminate
void RequiredFileExists (UnicodeString FilePath)
 {
  if (!FileExists (FilePath))
   {
	ShowErrorM (ReplaceStringMask (LanguageStrings [1], "path", FilePath));
    Application -> Terminate ();
   }
 }

//Apply new program's language from file
void ApplyLanguageFromFile (UnicodeString FilePath)
 {
  //Loading
  LanguageFile = new TMemIniFile (FilePath);
  LanguageStrings [2] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "Name", "SWBF I The Sith Launcher");
  LanguageStrings [0] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "Logo", "Created by %name%");
  LanguageStrings [7] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "Settings", "Settings");
  LanguageStrings [1] = WriteNewStringToIniFile (LanguageFile, "Error", "1", "File '%path%' doesn't exsists!");
  LanguageStrings [21] = WriteNewStringToIniFile (LanguageFile, "Error", "2", "The version identifier must consist of exactly 3 characters!");
  LanguageStrings [3] = WriteNewStringToIniFile (LanguageFile, "Button", "1", "Play");
  LanguageStrings [4] = WriteNewStringToIniFile (LanguageFile, "Button", "2", "Set additional maps");
  LanguageStrings [5] = WriteNewStringToIniFile (LanguageFile, "Button", "3", "About SWBF I The Sith Launcher");
  LanguageStrings [8] = WriteNewStringToIniFile (LanguageFile, "Button", "4", "Save");
  LanguageStrings [9] = WriteNewStringToIniFile (LanguageFile, "Button", "5", "Cancel");
  LanguageStrings [22] = WriteNewStringToIniFile (LanguageFile, "Button", "6", "Download");
  LanguageStrings [23] = WriteNewStringToIniFile (LanguageFile, "Button", "7", "Video instruction");
  LanguageStrings [6] = WriteNewStringToIniFile (LanguageFile, "Label", "1", "Coming Soon");
  LanguageStrings [10] = WriteNewStringToIniFile (LanguageFile, "Label", "2", "Launch settings");
  LanguageStrings [11] = WriteNewStringToIniFile (LanguageFile, "Label", "3", "Multiplayer settings");
  LanguageStrings [19] = WriteNewStringToIniFile (LanguageFile, "Label", "4", "The current version identifier of the game");
  LanguageStrings [20] = WriteNewStringToIniFile (LanguageFile, "Label", "5", "Global LAN network");
  LanguageStrings [12] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "1", "Run the game in the windowed mode");
  LanguageStrings [13] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "2", "Skip logos and splash screens");
  LanguageStrings [14] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "3", "Skip music at startup");
  LanguageStrings [15] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "4", "Disable the animated background in the menu");
  LanguageStrings [16] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "5", "Size of audio buffer (milliseconds)");
  LanguageStrings [17] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "6", "Sound quality");
  LanguageStrings [18] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "7", "Host of servers (Internet)");
  LanguageStrings [24] = WriteNewStringToIniFile (LanguageFile, "Link", "TunngleDownload", "http://www.softpedia.com/get/Internet/File-Sharing/Tunngle.shtml#download");
  LanguageStrings [25] = WriteNewStringToIniFile (LanguageFile, "Link", "TunngleVideoInstruction", "https://www.youtube.com/watch?v=WyggZSWwRAE");
  LanguageStrings [26] = WriteNewStringToIniFile (LanguageFile, "Link", "GameRangerDownload", "http://www.gameranger.com/download/");
  LanguageStrings [27] = WriteNewStringToIniFile (LanguageFile, "Link", "GameRangerInstruction", "");
  LanguageFile -> UpdateFile ();
  //Apply
  FormLogo -> Caption = LanguageStrings [2];
  FormMainMenu -> Caption = LanguageStrings [2];
  FormMainMenu -> sBitBtnPlay -> Caption = LanguageStrings [3];
  FormMainMenu -> sBitBtnSetAdditionalMap -> Caption = LanguageStrings [4];
  FormMainMenu -> sBitBtnAboutLauncher -> Caption = LanguageStrings [5];
  FormMainMenu -> sLabelComingSoon -> Caption = LanguageStrings [6];
  FormSettings -> Caption = LanguageStrings [7];
  FormSettings -> sBitBtnSave -> Caption = LanguageStrings [8];
  FormSettings -> sBitBtnCancel -> Caption = LanguageStrings [9];
  FormSettings -> sLabelLaunchSettings -> Caption = LanguageStrings [10];
  FormSettings -> sLabeMultiplayerSettings -> Caption = LanguageStrings [11];
  FormSettings -> sCheckBoxWindowedMode -> Caption = LanguageStrings [12];
  FormSettings -> sCheckBoxSkipSpalshScreens -> Caption = LanguageStrings [13];
  FormSettings -> sCheckBoxSkipStartupMusic -> Caption = LanguageStrings [14];
  FormSettings -> sCheckBoxDisableAnimatedMenuBackground -> Caption = LanguageStrings [15];
  FormSettings -> sCheckBoxAudioBufferSize -> Caption = LanguageStrings [16];
  FormSettings -> sCheckBoxSoundQuality -> Caption = LanguageStrings [17];
  FormSettings -> sCheckBoxInternetHost -> Caption = LanguageStrings [18];
  FormSettings -> sLabelCurrentGameVersion -> Caption = LanguageStrings [19];
  FormSettings -> sLabelLANNetwork -> Caption = LanguageStrings [20];
  FormSettings -> sBitBtnDownloadTunngle -> Caption = LanguageStrings [22];
  FormSettings -> sBitBtnTunngleVideo -> Caption = LanguageStrings [23];
  FormSettings -> sBitBtnDownloadGameRanger -> Caption = LanguageStrings [22];
  FormSettings -> sBitBtnGameRangerVideo -> Caption = LanguageStrings [23];
  //Changing elements positions
  FormMainMenu -> sLabelComingSoon -> Left = (FormMainMenu -> Width - FormMainMenu -> sLabelComingSoon -> Width) / 2; //change pos for this label to center of form with
  FormSettings -> sEditMilliseconds -> Left = FormSettings -> sCheckBoxAudioBufferSize -> Left + FormSettings -> sCheckBoxAudioBufferSize -> Width + 5;
  FormSettings -> sTrackBarSoundQuality -> Left = FormSettings -> sCheckBoxSoundQuality -> Left + FormSettings -> sCheckBoxSoundQuality -> Width + 5;
  FormSettings -> sLabelCurQuality -> Left = FormSettings -> sTrackBarSoundQuality -> Left + FormSettings -> sTrackBarSoundQuality -> Width + 5;
  FormSettings -> sLabelMinQuality -> Left = FormSettings -> sTrackBarSoundQuality -> Left;
  FormSettings -> sLabelMaxQuality -> Left = FormSettings -> sTrackBarSoundQuality -> Left + FormSettings -> sTrackBarSoundQuality -> Width - FormSettings -> sLabelMaxQuality -> Width;
  FormSettings -> sEditHost -> Left = FormSettings -> sCheckBoxInternetHost -> Left + FormSettings -> sCheckBoxInternetHost -> Width + 5;
  FormSettings -> sEditVersion -> Left = FormSettings -> sLabelCurrentGameVersion -> Left + FormSettings -> sLabelCurrentGameVersion -> Width + 8;
  FormSettings -> sBitBtnDownloadTunngle -> Left = FormSettings -> sLabelLANNetwork -> Left + FormSettings -> sLabelLANNetwork -> Width;
  FormSettings -> sBitBtnTunngleVideo -> Left = FormSettings -> sBitBtnDownloadTunngle -> Left;
  FormSettings -> sImageTunngle -> Left = FormSettings -> sBitBtnDownloadTunngle -> Left + FormSettings -> sBitBtnDownloadTunngle -> Width / 2 - FormSettings -> sImageTunngle -> Width / 2;
  FormSettings -> sLabelTunngle -> Left = FormSettings -> sBitBtnDownloadTunngle -> Left + FormSettings -> sBitBtnDownloadTunngle -> Width / 2 - FormSettings -> sLabelTunngle -> Width / 2;
  FormSettings -> sBitBtnDownloadGameRanger -> Left = FormSettings -> sBitBtnDownloadTunngle -> Left + 130;
  FormSettings -> sBitBtnGameRangerVideo -> Left = FormSettings -> sBitBtnDownloadGameRanger -> Left;
  FormSettings -> sImageGameRanger -> Left = FormSettings -> sImageTunngle -> Left + 130;
  FormSettings -> sLabelGameRanger -> Left = FormSettings -> sBitBtnDownloadGameRanger -> Left + FormSettings -> sBitBtnDownloadGameRanger -> Width / 2 - FormSettings -> sLabelGameRanger -> Width / 2;
 }

//Set form position to screen center
void SetFormToScreenCenter (TForm* Form)
 {
  Form -> Left = (Screen -> Width - Form -> Width) / 2;
  Form -> Top = (Screen -> Height - Form -> Height) / 2;
 }

//Unvisible form
void UnvisibleForm (TForm* Form)
 {
  Form -> Enabled = false;
  Form -> Left = -99999;
  Form -> Top = -99999;
 }

//Show error message
void ShowErrorM (UnicodeString Error)
 {
  Application -> MessageBox (Error.c_str (), UnicodeString ("ERROR").c_str (), MB_OK);
 }
