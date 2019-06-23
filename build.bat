:: Borro el directorio de binarios si ya existiera
IF EXIST .\bin RMDIR /S /Q .\bin

:: Creo los directorios para el binario y las bibliotecas
MD .\bin

## Compilo todo
g++ -Wall -std=c++11 -I.\include\ main.cpp -o .\bin\main.exe
g++ -shared -Wall -std=c++11 -I.\include\ .\src\Application\Application.cpp -o .\bin\Application.dll
g++ -shared -Wall -std=c++11 -I.\include\ .\src\ConsoleGreeter\ConsoleGreeter.cpp -o .\bin\Greeter.dll
g++ -shared -Wall -std=c++11 -I.\include\ .\src\Messenger\Messenger.cpp -o .\bin\Messenger.dll