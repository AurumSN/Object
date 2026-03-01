#include <iostream>

#include "Directory.h"
#include "File.h"

int main()
{
	Directory d{ "./Experiment/" };

	{
		File f = d.createFile("Test.txt");

		f.writeLine("Test line 1!");
		f.writeLine("Test line 2!");
	}
}