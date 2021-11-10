#!/bin/sh
clear
g++ -std=c++17 \
-I ./include/ \
-L ./lib/ \
./src/TcpSocket.cpp \
./src/TcpConnection.cpp \
./src/TcpClient.cpp \
./src/TcpServer.cpp \
./src/SpecialServer.cpp \
./src/FlexTime.cpp \
./src/LogWriter.cpp \
./src/ServerApp.cpp \
-o ./bin/server \
-lpthread
g++ -std=c++17 \
-I ./include/ \
-L ./lib/ \
./src/TcpSocket.cpp \
./src/TcpConnection.cpp \
./src/TcpClient.cpp \
./src/TcpServer.cpp \
./src/SpecialClient.cpp \
./src/ClientApp.cpp \
-o ./bin/client \
-lpthread
