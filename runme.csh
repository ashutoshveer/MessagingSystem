#!/bin/csh -f

rm -rf *.a *.o

g++ -g -std=c++17 -c MessageInstance.cpp MessageManager.cpp
ar rcs MessageManager.a MessageInstance.o MessageManager.o
g++ -g -std=c++17 -c Device.cpp -o Device.o
ar rcs Device.a Device.o MessageInstance.o
g++ -g -std=c++17 -c DeviceInstanceA.cpp -o DeviceInstanceA.o
ar crsT DeviceInstanceA.a Device.a MessageManager.a DeviceInstanceA.o
g++ -g -std=c++17 -c DeviceInstanceB.cpp -o DeviceInstanceB.o
ar crsT DeviceInstanceB.a Device.a MessageManager.a DeviceInstanceB.o
g++ -g -std=c++17 -c DeviceInstanceC.cpp -o DeviceInstanceC.o
ar crsT DeviceInstanceC.a Device.a MessageManager.a DeviceInstanceC.o
g++ -g -std=c++17 -c DeviceInstanceD.cpp -o DeviceInstanceD.o
ar crsT DeviceInstanceD.a Device.a MessageManager.a DeviceInstanceD.o
g++ -g -std=c++17 -c mainAPP.cpp -o mainAPP.o
g++ -g -std=c++17 mainAPP.o Device.a MessageManager.a DeviceInstanceA.a DeviceInstanceB.a DeviceInstanceC.a DeviceInstanceD.a -o mainAPP

