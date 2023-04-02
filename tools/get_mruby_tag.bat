REM SPDX-License-Identifier: BSD-3-Clause
REM get_mruby_tag.bat mrblib/global.rb

IF "%1" == "" (
	ECHO "missing argument"
	EXIT /B 1
)
IF NOT EXIST "%1" (
	ECHO "mrblib/global.rb file does not exist"
	EXIT /b 1
)

FOR /F "eol=# tokens=1,2,3,4*" %%a IN (%1) DO (
	IF "%%a"=="MRUBY_VERSION" (
		ECHO %%~c > MRBUY_TAG
		EXIT /B 0
	)
)
EXIT /b 1
