@ECHO OFF
:releasetype
@SET /p releasever=��ѡ�񷢲��汾[0 VS2008��1 VS2013 2 VS2015]:
@REM ==================�����Ϸ�����֤=============================
@IF %releasever% EQU 0 (
    SET VER=2008
) ELSE (
	@IF %releasever% EQU 1 (
   		SET VER=2013
	) ELSE (
 		@IF %releasever% EQU 2 (
   			SET VER=2015
		) ELSE (
    		@ECHO ON
    		@ECHO �Ƿ������汾������������
    		@GOTO :releasetype
		)
	)
)

@REM ɾ�����а汾
ECHO ON
ECHO %~dp0..\..\LukeLibRC\duilib\%VER%
REM DEL /F /S /Q %~dp0..\..\LukeLibRC\duilib\%VER%\*
RD /S /Q %~dp0..\..\LukeLibRC\duilib\%VER%
MD %~dp0..\..\LukeLibRC\duilib\%VER%
XCOPY Unicode %~dp0..\..\LukeLibRC\duilib\%VER%\ /S

RD /S /Q %~dp0..\..\LukeLibRC\duilib\include
MD %~dp0..\..\LukeLibRC\duilib\include
XCOPY include %~dp0..\..\LukeLibRC\duilib\include\ /S

RD /S /Q Unicode
PAUSE
