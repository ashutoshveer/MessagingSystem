Description:

    This C++ application is aimed to create a thread safe messaging infrastructure for reading messages from a number of Devices.
    All devices are generating messages on different threads and the messages are being consumed in a seperate thread.
    This application could further be extended to be used in a publish and subscribe messaging infrastructure.
    We are also using a string based message counting mechanism to keep track of the messages.

Message Producer:
    The devices (created using DeviceInstanceA.cpp/DeviceInstanceB.cpp/DeviceInstanceC.cpp/DeviceInstanceD.cpp) continously 
    push messages to queue and the messaging system reads from the queue.The devices are using a seperate thread for pushing
    messages to the queue.

Message Consumer:
    Messages are read in MessageManager.cpp.The MessageManager is using a seperate thread for reading the messages from the queue.
    So the main thread is free to execute operations if any. 

Main Application:
    We are using the main thread for printing the message count after every 0.5 seconds.
    The message count is saved in a string instead of integer in order to avoid the issue of buffer overflow. 
    A seperate utility function is written to increment the message count saved in string.

Build steps:

    Run "runme.csh" script on linux machine. This creates mainAPP executable for to be used for running the application
    "runme.csh" creates the following static libraries:
      1. MessageManager.a   - This library is responsible for adding/removing messages from queue. 
                              We have a seperate thread for consuming messsages and printing the messages to "DevicesMsg.log".
      2. Device.a           - This library is responsible for creating the basic functionality of all devices.
      3. DeviceInstanceA.a  - This library is for creating specific device named Device_A . This library consumes the Device.a library.
      3. DeviceInstanceB.a  - This library is for creating specific device named Device_B . This library consumes the Device.a library.
      3. DeviceInstanceC.a  - This library is for creating specific device named Device_C . This library consumes the Device.a library.
      3. DeviceInstanceD.a  - This library is for creating specific device named Device_D . This library consumes the Device.a library.

Execute: 

    Run ./mainAPP executable. This is built using the above libraries using "runme.csh" script. this executable automatucally 
    starts producing messages from different devices (DeviceInstanceA.cpp/DeviceInstanceB.cpp/DeviceInstanceC.cpp/DeviceInstanceD.cpp)
    and consuming the messages in message manager (MessageManager.cpp).

Debug messages:

    We are printing the debug messages evey time a device pushes a message the queue.
    We are consuming the messages using the message manager and pushing it to the file named "DevicesMsg.log".
    We are pritning the message count in the main application after every 0.5 seconds which is main application thread's only work.
    At the end when user sends a interrupt signal (for example ctrl-c), we are catching the signal and printing the final message count in the end.

ToDo:
    Seperate consumer from message manger
    Implement publish subscribe model using topics like in RabbitMQ
    Add try catch blocks for handling exceptions
