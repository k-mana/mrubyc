REM SPDX-License-Identifier: BSD-3-Clause
REM build_docker.bat <MRUBY_TAG file> [<CURRENT_MRUBY_TAG file>]

IF "%1" == "" (
	ECHO "missing argument"
	EXIT /B 1
)
iF NOT EXIST "%1" (
	ECHO "MRUBY_TAG file does not exist"
	EXIT /b 1
)
FOR /F %%a IN (%1) DO SET MRUBY_TAG=%%a
IF NOT "%2" == "" (
	IF NOT EXIST "%2" (
		ECHO "CURRENT_MRUBY_TAG file does not exist"
		EXIT /b 1
	)
	FOR /F %%a IN (%2) DO SET CURRENT_MRUBY_TAG=%%a
	IF "%CURRENT_MRUBY_TAG%" == "%MRUBY_TAG%" (
		ECHO "skip docker build"
		EXIT /B 0
	)
)

docker build -t mrubyc-dev --build-arg MRUBY_TAG=%MRUBY_TAG% --build-arg USER_ID=0 %options% .
