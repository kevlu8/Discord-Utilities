OutFile "Discord Utilities.exe"

InstallDir $PROGRAMFILES

Section

	UserInfo::getAccountType

	Pop $0

	StrCmp $0 "Admin" +3

	MessageBox MB_OK "You are not running as admin. $0"
	Return

	# install the program
	SetOutPath "$INSTDIR\Discord Utilities\"

	File /r /x *.pdb "x64\Release\" 

	WriteUninstaller "$INSTDIR\Discord Utilities\uninstall.exe"
	CreateShortcut "$DESKTOP\Discord Utilities.lnk" "$INSTDIR\Discord Utilities\DiscUtil.exe"

SectionEnd

Section "uninstall"
	Delete "$INSTDIR\Discord Utilities\uninstall.exe"
	Delete "$DESKTOP\Discord Utilities.lnk"

	RMDir /r "$INSTDIR\Discord Utilities\"
SectionEnd