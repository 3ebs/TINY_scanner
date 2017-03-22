#include "TINY Scanner.h"

using namespace std;

Scanner::Scanner(string f)
{
    file.open(f);
    outFile.open("scannerOutput.txt");
}

bool Scanner::scanSpecialSymbols(unsigned char c, string & tempID)
{
    TokenRecord tok;
    for(int i = 0; i < num_of_ss; i++)
    {
        if(c==specialSymbols[i])
        {
			if (tempID != "")
			{
				tok.tokentype = ID;
				tok.stringValue = tempID;
				tokenlist.push_back(tok);
				tempID = "";
			}
			tok.tokentype = i;
            tok.stringValue = c+'\0';
            tokenlist.push_back(tok);
			//c = ' ';
            return true;
        }
    }
    return false;
}

int Scanner::scanReservedWords(string x, string line)
{
	smatch m;
	regex _exp_(".*\\s*(" + x + ")\\s*.*");
	regex_match(line, m, _exp_);
	for (unsigned int i = 0; i < m.size(); i++)
	{
		if (m.length(i) == x.length())
		{
			return m.position(i);
		}
	}
	return -1;
}

void Scanner::getTokens(void)
{
    string line;
    bool flag;
    TokenRecord tok;
	ReservedWord rewo;
	list<ReservedWord>::iterator ii;
    while(getline(file, line))
    {
		/****************************initializing************************/
		string tempID = "";
		RW.clear();
		for (unsigned int i = 0; i < line.length(); i++) //remove comments from line
		{
			if (line[i] == '{')
			{
				for (i; line[i] != '}'; i++)
				{
					line[i] = ' ';
				}
				break;
			}
		}
		//tokenlist.clear();
		/****************************************************************/
		/***********************reserved words + ':='************************/
		for (int k = 0; k < num_of_rw+3; k++)
		{
			rewo.index = scanReservedWords(reservedWords[k], line);
			rewo.value = k + index_of_RW;
			RW.push_back(rewo);
		}
		/*******************************************************************/

        for(unsigned int i = 0; i < line.length(); i++)
        {
			/*******************white space************************/
			if (line[i] == ' ' || line[i] == '\t' || line[i] == '}'	)
			{
				if (tempID != "")
				{
					tok.tokentype = ID;
					tok.stringValue = tempID;
					tokenlist.push_back(tok);
					tempID = "";
				}
				continue;
			}
			/************************************************************/
			/*********************************Numbers********************/
			if ((i > 0 && line[i-1] == ' ' && line[i] - 48 >= 0 && line[i] - 48 <= 9) || (line[i]=='-' && line[i+1] - 48 >= 0 && line[i+1] - 48 <= 9))
			{
				string tempNum = "";
				tempNum += line[i];
				i++;
				for (int j = i; (line[j] - 48 >= 0 && line[j] - 48 <= 9) || line[j] == '.'; j++)
				{
					tempNum += line[j];
					i++;
				}
				tok.tokentype = NUM;
				tok.stringValue = tempNum;
				tokenlist.push_back(tok);
				i--;
				continue;
			}
			/***********************************************************/
			/**************************reserved words + ':='*************/
			for (ii = RW.begin(); ii != RW.end(); ii++)
			{
				if (i == ii->index)
				{
					if (tempID == "")
					{
						int tempIndex = i + reservedWords[ii->value - index_of_RW].length();
						if (line[tempIndex] == ' ' || line[tempIndex] == '\0' || line[tempIndex] == '\t' || line[tempIndex] == '\n')
						{
							i += reservedWords[ii->value - index_of_RW].length() - 1;
							tok.tokentype = ii->value;
							tok.stringValue = reservedWords[ii->value - index_of_RW];
							tokenlist.push_back(tok);
							flag = true;
						}
						break;
					}
				}
			}
			if (flag)
			{

				flag = false;
				continue;
			}
			/**********************************************************/
			/**************Special symbols except ':='*****************/
			flag = scanSpecialSymbols(line[i], tempID);
			if (flag)
			{
				if (tempID != "")
				{
					tok.tokentype = ID;
					tok.stringValue = tempID;
					tokenlist.push_back(tok);
					tempID = "";
				}
				flag = false;
				continue;
			}
			/************************************************************/
			/*****************************identifiers******************/
			tempID += line[i];
			/*********************************************************/
        }
    }
}

void Scanner::getTokenTable(void)
{
	getTokens();
	list<TokenRecord>::iterator ii;
	for (ii = tokenlist.begin(); ii != tokenlist.end(); ii++)
	{
		outFile << ii->stringValue << "," << tokens[ii->tokentype] << "\n";
	}
	outFile << "--";
	file.close();
	outFile.close();
}
