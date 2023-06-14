@echo off
@echo Building IDP documentation:
@rem require lua script to be in path (winget install )
lua main.lua
@echo Building HTMLHelp:
"%ProgramFiles(x86)%\HTML Help Workshop\hhc.exe" idp.hhp
@echo Done.
@pause
@echo on