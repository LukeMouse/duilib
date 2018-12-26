@ECHO OFF
:releasetype
@SET /p releasever=请选择发布版本[0 VS2008，1 VS2013 2 VS2015]:
@REM ==================参数合法性验证=============================
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
    		@ECHO 非法发布版本，请重新输入
    		@GOTO :releasetype
		)
	)
)

@REM 删除现有版本
ECHO ON
ECHO %~dp0..\..\LukeLibRC\duilib\%VER%
REM DEL /F /S /Q %~dp0..\..\LukeLibRC\duilib\%VER%\*
RD /S /Q %~dp0..\..\LukeLibRC\duilib\%VER%
MD %~dp0..\..\LukeLibRC\duilib\%VER%
XCOPY %VER% %~dp0..\..\LukeLibRC\duilib\%VER%\ /S

RD /S /Q %~dp0..\..\LukeLibRC\duilib\include
MD %~dp0..\..\LukeLibRC\duilib\include
XCOPY include %~dp0..\..\LukeLibRC\duilib\include\ /S

RD /S /Q %VER%
PAUSE
