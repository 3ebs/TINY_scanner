#include "TINY Scanner.h"
#include <stdio.h>

using namespace std;

int main(int argc, const char * argv[])
{
	string fileName = argv[1];
    Scanner s(fileName);
    s.getTokenTable();
    return 0;
}
