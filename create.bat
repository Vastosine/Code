@echo off


set pre=%2
if "%pre%" == "" set pre=CF

SET dir=D:\code\OI\contests\%pre%\%~1  

mkdir %dir%
code %dir%