@echo off

set UE_CMD_PATH=%UE_git_5_6%\Binaries\Win64\UnrealEditor-Cmd.exe
set PROJECT_DIR=%UE_Projects%\TestCiCd\CiCdProject
set PROJECT_PATH=%PROJECT_DIR%\CiCdProject.uproject
set REPORT_PATH=%PROJECT_DIR%\TestReports
REM --- Запуск ---
"%UE_CMD_PATH%" ^
  "%PROJECT_PATH%" ^
  -NoSplash -Unattended -NullRHI ^
  -ExecCmds="Automation RunTest TrainingTests.PIE.GetActor+ModuleTests.SimpleTest; Quit" ^
  -ReportExportPath="%REPORT_PATH%" ^
  -log

pause
