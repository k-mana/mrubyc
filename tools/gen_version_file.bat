REM SPDX-License-Identifier: BSD-3-Clause
REM gen_version_file.bat mrblib/global.rb

IF "%1" == "" (
	ECHO "missing argument"
	EXIT /B 1
)
IF NOT EXIST "%1" (
	ECHO "mrblib/global.rb file does not exist"
	EXIT /b 1
)

FOR /F "eol=# tokens=1*" %%a IN (%1) DO (
	echo "%%a" | find "_VERSION" > NUL
	IF NOT ERRORLEVEL 1 (
		ECHO %%a %%b>> VERSION
	)
)
IF NOT EXIST VERSION (
	EXIT /B 1
)
EXIT /B 0
