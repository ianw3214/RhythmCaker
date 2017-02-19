@echo off
echo "+======================================================================================+"
pushd ..\build
cl /EHsc ..\src\main.cpp ..\src\engine.cc ..\src\state.cc ..\src\sprite.cc ..\src\animatedSprite.cc ..\src\audioLoader.cc ..\src\level.cc ..\src\bear.cc ..\src\background.cc ..\src\text.cc /MP50 /I ..\src\headers /I ..\libs\SDL2-2.0.4\include /I ..\libs\SDL2_image-2.0.1\include /I ..\libs\SDL2_image-2.0.1\include /I ..\libs\SDL2_mixer-2.0.1\include /link  ..\libs\SDL2-2.0.4\lib\x86\SDL2.lib ..\libs\SDL2-2.0.4\lib\x86\SDL2main.lib ..\libs\SDL2_image-2.0.1\lib\x86\SDL2_image.lib ..\libs\SDL2_mixer-2.0.1\lib\x86\SDL2_mixer.lib /SUBSYSTEM:CONSOLE
popd
echo "+======================================================================================+"
echo on
