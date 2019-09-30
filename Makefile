

all: run

run: crc_rx.o crc_tx.o crc_vs_checksum.o
	g++ crc_rx.o crc_tx.o crc_vs_checksum.o -o run


crc_rx.o: crc_rx.cpp
	g++ -c crc_rx.cpp


crc_tx.o: crc_tx.cpp	
	g++ -c crc_tx.cpp

crc_vs_checksum.o: crc_vs_checksum.cpp
	g++ -c crc_vs_checksum.cpp
