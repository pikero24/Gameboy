#include "screen.h"
#include "Z80.h"
#include <iostream>
#include <fstream>

#include <QtGui>

using namespace std;

//from class INCORRECT ROM!!!
//unsigned char memory[]={0x06,17,0xe,0x16,0x1,0x78,0xb9,0xca,0x15,0x00,0xda,0x15,0x00,0x14,0x78,0x91,0x47,0xc3,0x06,0x00,0x76};

char* rom; //[]={0x06,0x06,0x3e,0x00,0x80,0x05,0xc2,0x04,0x00,0x76};

unsigned char memoryread(int address)
{
	return rom[address];
}

void memorywrite(int address, unsigned char value)
{}

extern QApplication* app;

//Global Variables to hold memory
unsigned char graphicsRAM[8192];
int palette[4];
int tileset, tilemap, scrollx, scrolly;


int main(int argc, char** argv)
{
	setup(argc,argv);

	//Load the rom from file
	ifstream romfile("testrom.gb", ios::in|ios::binary|ios::ate);
    streampos size = romfile.tellg();
    rom = new char[size]; //ERROR
    int romSize=size;
    romfile.seekg(0,ios::beg);
    romfile.read(rom,size);
    romfile.close();

    //Read screendump into graphicsRAM
    int n;
	ifstream vidfile("screendump.txt",ios::in);
	for(int i=0; i<8192; i++){
		int n;
		vidfile>>n;
		graphicsRAM[i]=(unsigned char)n;
	}
    vidfile >> tileset;
    vidfile >> tilemap;
    vidfile >> scrollx;
    vidfile >> scrolly;

    vidfile >> palette[0];
    vidfile >> palette[1];
    vidfile >> palette[2];
    vidfile >> palette[3];


    //create new processor
	Z80* z80 = new Z80(memoryread,memorywrite);
	z80->reset();
	//  z80->PC=0;
	cout<< "A: "<< z80->A<< " B: "<< z80->B<< " C: "<<z80->C << " D: "<<z80->D <<endl;

	while(!z80->halted){
		//run instructions
		z80->doInstruction();
		cout<<"A: "<< z80->A<< " B: "<< z80->B<< " C: "<<z80->C << " D: "<<z80->D <<endl;
	}

	app->exec();
	return 0;
}