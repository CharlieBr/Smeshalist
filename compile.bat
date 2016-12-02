set SMESHALIST_PATH=C:\Users\Katarzyna\Documents\Studia\Semestr_7\ingeniero\Smeshalist
set CPPAPI_PATH=%SMESHALIST_PATH%\CppAPI
set CORE_PATH=%SMESHALIST_PATH%\CoreModule
set STRUCTURES_PATH=%CORE_PATH%\STRUCTURES
set COMMUNICATION_PATH=%CORE_PATH%\COMMUNICATION_MODULE
set FILTERS_PATH=%CORE_PATH%\FILTERS_MODULE

set FLAGS=-std=c++11 -Wall -L%SMESHALIST_PATH%\Make\Linux\lib
set INCLUDES=-I%STRUCTURES_PATH%\include -I%COMMUNICATION_PATH%\include -I%FILTERS_PATH%\include -I%CPPAPI_PATH% -I%CORE_PATH%\SmeshalistManager\proto -IC:\Users\Katarzyna\Downloads\freeglut-MSVC-3.0.0-2.mp\freeglut\include
set LIBS=Make\Linux\lib\libGLU.a -lGL -lglut -lprotobuf

mkdir obj

g++ %FLAGS% %INCLUDES% -c %STRUCTURES_PATH%\src\AbstractDataTree.cpp -o obj\AbstractDataTree.o
g++ %FLAGS% %INCLUDES% -c %STRUCTURES_PATH%\src\Color.cpp -o obj\Color.o
g++ %FLAGS% %INCLUDES% -c %STRUCTURES_PATH%\src\Data.cpp -o obj\Data.o
g++ %FLAGS% %INCLUDES% -c %STRUCTURES_PATH%\src\LinuxDataTree.cpp -o obj\LinuxDataTree.o
g++ %FLAGS% %INCLUDES% -c %STRUCTURES_PATH%\src\Statistics.cpp -o obj\Statistics.o
g++ %FLAGS% %INCLUDES% -c %STRUCTURES_PATH%\src\Structures.cpp -o obj\Structures.o

g++ %FLAGS% %INCLUDES% -c %COMMUNICATION_PATH%\src\AbstractServer.cpp -o obj\AbstractServer.o %LIBS% 
g++ %FLAGS% %INCLUDES% -c %COMMUNICATION_PATH%\src\WindowsServer.cpp -o obj\WindowsServer.o %LIBS% 