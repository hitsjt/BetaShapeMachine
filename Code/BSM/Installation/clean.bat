rmdir include /s /q
rmdir lib /s /q

rmdir ..\Build\bin /s /q
rmdir ..\Build\Release /q
rmdir ..\Build\lib /q
rmdir ..\Build\Output /s /q
rmdir ..\Build\CMakeFiles /s /q
rmdir ..\Build\Debug /s /q
rmdir ..\Build\x64 /s /q
rmdir ..\Build\ipch /s /q
rmdir ..\Build\SNL.dir /s /q

rmdir ..\Build\Common\bin /s /q
rmdir ..\Build\Common\Release /q
rmdir ..\Build\Common\lib /q
rmdir ..\Build\Common\Output /s /q
rmdir ..\Build\Common\CMakeFiles /s /q
rmdir ..\Build\Common\Debug /s /q
rmdir ..\Build\Common\x64 /s /q
rmdir ..\Build\Common\ipch /s /q
rmdir ..\Build\Common\SNL.dir /s /q

rmdir ..\Build\Plugins\S12\bin /s /q
rmdir ..\Build\Plugins\S12\Release /q
rmdir ..\Build\Plugins\S12\lib /q
rmdir ..\Build\Plugins\S12\Output /s /q
rmdir ..\Build\Plugins\S12\CMakeFiles /s /q
rmdir ..\Build\Plugins\S12\Debug /s /q
rmdir ..\Build\Plugins\S12\x64 /s /q
rmdir ..\Build\Plugins\S12\ipch /s /q
rmdir ..\Build\Plugins\S12\SNLPluginS12.dir /s /q

rmdir ..\Build\Plugins\DL13\bin /s /q
rmdir ..\Build\Plugins\DL13\Release /q
rmdir ..\Build\Plugins\DL13\lib /q
rmdir ..\Build\Plugins\DL13\Output /s /q
rmdir ..\Build\Plugins\DL13\CMakeFiles /s /q
rmdir ..\Build\Plugins\DL13\Debug /s /q
rmdir ..\Build\Plugins\DL13\x64 /s /q
rmdir ..\Build\Plugins\DL13\ipch /s /q
rmdir ..\Build\Plugins\DL13\SNLPluginDL13.dir /s /q

del ..\Build\SNL* /s /q
del ..\Build\ALL_* /s /q
del ..\Build\INSTALL* /s /q
del ..\Build\CMakeCache.txt 
del ..\Build\cmake_install.cmake /s /q
del ..\Build\ZERO_CHECK* /s /q
del ..\Build\*.suo /s /q /A:H 



REM install-snl-win64.bat > output_snl.txt 2>&1
