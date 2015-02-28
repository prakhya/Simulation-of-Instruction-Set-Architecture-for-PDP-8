/*********************************************************************************
 * File:        TestLoadMemory.cpp
 * Description: Test loadMemory() method of LoadMemory.h
 * Project: 	ECE 586 PDP-8 ISA Simulator
 * Version: 	0.1
 * Date:		01/29/2015
 * Author:		Prakhya, Doguparthi, Mutyala, Produtturi
 *********************************************************************************/

#include "FD.h"
#include "Execute.h"

using namespace std;

int exit1 = 0;

ofstream myfile1;

int main()
{
    int pcOct = 200;
    int pcDec = oct2Dec(pcOct);
    int mbDec = 0;
    int pageNum = 0;
    int offsetNum = 0;
    int opcode = 8;
    int indirection = 0;
    int zeroOrCP = 0;
    int pageNo = 0;
    int offsetNo = 0;
    init();
    string traceFile;
    cout << "Please enter a file name: ";
    cin >> traceFile;
    loadMemory(traceFile);
    myfile1.open("TraceFile.txt");
    while (exit1==0)
    {
        mbDec = fetch(pcDec);
		pcDec++;
        tie(opcode, indirection, zeroOrCP) = decode(mbDec);
        tie(pageNo, offsetNo) = calculateEffAddr(mbDec, opcode, indirection, zeroOrCP, pcDec);
        if (opcode==7)
            pcDec = execute7(mbDec, pcDec);
		else if (opcode==6)
		{
			try 
			{
				pcDec = execute6(mbDec, pcDec);
			}
			catch (const char* msg)
			{
				//cerr << msg << endl;
				time--;
				if (time == 0)
					printerFlag = 1;
			}
			cout << "Time taken for printer to get ready: " << time << endl;
		}
        else
			pcDec = execute(opcode, pageNo, offsetNo, mbDec, pcDec);
    }
    myfile1.close();
    printMem();
    printStats();
	system("pause");
	//cin.get();
	return 0;
}