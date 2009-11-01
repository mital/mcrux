#include <iostream>

using namespace std;

#include<mcrux/MCrux.h>

int main(int argc, char **argv)
{
  MCrux mcrux;
  mcrux.InitializeAndRunWith("/home/mital/test.mcruxspec", argc, argv);
	return 0;
}
