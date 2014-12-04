#include "screen.h"
#include "Z80.h"
#include <iostream>
#include <fstream>



#include <QtGui>

using namespace std;

//from class INCORRECT
unsigned char memory[]={0x06,17,0xe,0x16,0x1,0x78,0xb9,0xca,0x15,0x00,0xda,0x15,0x00,0x14,0x78,0x91,0x47,0xc3,0x06,0x00,0x76};

char* rom; //[]={0x06,0x06,0x3e,0x00,0x80,0x05,0xc2,0x04,0x00,0x76};

unsigned char memoryread(int address)
{
	return rom[address];
}

void memorywrite(int address, unsigned char value)
{}

extern QApplication* app;

int main(int argc, char** argv)
{
	setup(argc,argv);

	ifstream romfile("testrom.gb", ios::in|ios::binary|ios::ate);
    streampos size = romfile.tellg();
    rom = new char[size]; //ERROR
    int romSize=size;
    romfile.seekg(0,ios::beg);
    romfile.read(rom,size);
    romfile.close();

	Z80* z80 = new Z80(memoryread,memorywrite);
	z80->reset();
	//  z80->PC=0;
	cout<< "A: "<< z80->A<< " B: "<< z80->B<< " C: "<<z80->C << " D: "<<z80->D <<endl;

	while(!z80->halted){
		z80->doInstruction();
		cout<<"A: "<< z80->A<< " B: "<< z80->B<< " C: "<<z80->C << " D: "<<z80->D <<endl;
	}

	app->exec();
	return 0;
}