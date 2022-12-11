#include <conio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <regex>
#include <math.h>
#include <cstring>

using namespace std;
string myArray[1000][15];
queue <int> Dfront;
stack <int> Jfront;
stack <int> Trace;
stack <int> TraceV;
int* Input;
int* OUTN;
int sh = 0, chekpoint, LimO;
int inconsist = 0;
int* node = (int*)malloc(20 * sizeof(int));
int IN = 0, R = 0, Lim;
int AND(int PI1, int PI2)
{
	if (PI1 == 0 || PI2 == 0)
	{
		return 0;
	}
	else if (PI1 == 1 && PI2 == 1) {
		return 1;
	}
	else if (PI1 == 1 && PI2 == 5 || PI1 == 5 && PI2 == 1) {
		return 5;
	}
	else if (PI1 == 1 && PI2 == 4 || PI1 == 4 && PI2 == 1) {
		return 4;
	}
	else if (PI1 == 4 && PI2 == 5) {
		return 0;
	}
	else if (PI1 == 4 && PI2 == 4) {
		return 4;
	}
	else if (PI1 == 5 && PI2 == 5) {
		return 5;
	}
	else if (PI1 == 5 || PI2 == 4) {
		return 0;
	}
	else {
		return 4;
	}
}
int OR(int PI1, int PI2)
{
	if (PI1 == 1 || PI2 == 1)
	{
		return 1;
	}
	else if (PI1 == 0 && PI2 == 0) {
		return 0;
	}
	else if (PI1 == 0 && PI2 == 4 || PI1 == 4 && PI2 == 0) {
		return 4;
	}
	else if (PI1 == 0 && PI2 == 5 || PI1 == 5 && PI2 == 0) {
		return 5;
	}
	else if (PI1 == 4 && PI2 == 5|| PI1 == 5 && PI2 == 4) {
		return 1;
	}
	else if (PI1 == 5 && PI2 == 5) {
		return 5;
	}
	else if (PI1 == 4 || PI2 == 4) {
		return 4;
	}
	else {
		return 2;
	}
}
int NOT(int PI1)
{
	if (PI1 == 1)
	{
		return 0;
	}
	else if (PI1 == 0) {
		return 1;
	}
	else if (PI1 == 4) {
		return 5;
	}
	else if (PI1 == 5) {
		return 4;
	}
	else {
		return 2;
	}
}
int XOR(int PI1, int PI2)
{
	if (PI1 + PI2 == 1)
	{
		return 1;
	}
	else if (PI1 == PI2) {
		return 0;
	}
	else if ((PI1 == 0 && PI2 == 4) || (PI1 == 4 && PI2 == 0))
	{
		return 4;
	}
	else if ((PI1 == 0 && PI2 == 5) || (PI1 == 5 && PI2 == 0))
	{
		return 5;
	}
	else if ((PI1 == 1 && PI2 == 4) || (PI1 == 4 && PI2 == 1))
	{
		return 5;
	}
	else if ((PI1 == 1 && PI2 == 5) || (PI1 == 5 && PI2 == 1))
	{
		return 4;
	}
	else if ((PI1 == 5 && PI2 == 4) || (PI1 == 4 && PI2 == 5))
	{
		return 1;
	}
	else {
		return 2;
	}

}
int XNOR(int PI1, int PI2)
{
	if (PI1 + PI2 == 1)
	{
		return 0;
	}
	else if (PI1 == PI2) {
		return 1;
	}
	else if ((PI1 == 0 && PI2 == 5) || (PI1 == 5 && PI2 == 0))
	{
		return 4;
	}
	else if ((PI1 == 0 && PI2 == 4) || (PI1 == 4 && PI2 == 0))
	{
		return 5;
	}
	else if ((PI1 == 1 && PI2 == 5) || (PI1 == 5 && PI2 == 1))
	{
		return 5;
	}
	else if ((PI1 == 1 && PI2 == 4) || (PI1 == 4 && PI2 == 1))
	{
		return 4;
	}
	else if ((PI1 == 5 && PI2 == 4) || (PI1 == 4 && PI2 == 5))
	{
		return 0;
	}
	else {
		return 2;
	}
}
int condition(string str)
{
	if (str == "from"|| str == "fan")
		return 1;
	if (str == "and")
		return 2;
	if (str == "or")
		return 3;
	if (str == "not")
		return 4;
	if (str == "xor")
		return 5;
	if (str == "xnor")
		return 6;
	if (str == "nand")
		return 7;
	if (str == "nor")
		return 8;
	if (str == "buff")
		return 9;
}
void fancheck(int Node)
{
	int bcount1 = 0, LineN;
	for (int i = 18; i < Lim; i++) {
		if (stoi(myArray[i][1]) == Node)
		{
			LineN = i;
			break;
		}
	}
	//cout << "LineN" << LineN << endl;
	for (int i = 18; i <= Lim; i++) {
		if (myArray[LineN][2] == myArray[i][4] ||(myArray[LineN][3]=="from" && myArray[LineN][4] == myArray[i][2])|| (myArray[LineN][3] == "from" && myArray[LineN][4] == myArray[i][4]))
		{
			//cout << "LineN" << LineN << endl;
			if (Input[stoi(myArray[i][1])] == Input[stoi(myArray[LineN][1])] || Input[stoi(myArray[i][1])] == 3)
			{
				//cout << "flag1" << endl;
				if (i != LineN && Input[stoi(myArray[i][1])] == 3)
				{
					Input[stoi(myArray[i][1])] = Input[stoi(myArray[LineN][1])];
					Trace.push(stoi(myArray[i][1]));
					TraceV.push(Input[stoi(myArray[i][1])]);
					Jfront.push(stoi(myArray[i][1]));
					bcount1 += 1;
				}
			}
			else
			{
				while (bcount1 != 0)
				{
					Input[Trace.top()] = 3;
					Trace.pop();
					TraceV.pop();
					Jfront.pop();
					bcount1 -= 1;
				}
				inconsist = 1;
			}
		}
		if (inconsist == 1)
		{
			break;
		}

	}
}
void Propagate(string A, int i)
{
	int con = condition(A);
	switch (con) {
	case 2:
		for (int N = 1; N <= stoi(myArray[i - 1][5]); N++) {
			IN = stoi(myArray[i][N]);
			if (Input[IN] == 3)
			{
				Input[IN] = 1;
				fancheck(IN);
			}

			node[N - 1] = Input[IN];

		}


		for (int P = 1; P <= stoi(myArray[i - 1][5]); P++) {

			node[P] = AND(node[P - 1], node[P]);

		}
		Input[stoi(myArray[i - 1][1])] = node[stoi(myArray[i - 1][5]) - 1];
		if (Input[stoi(myArray[i - 1][1])] == 4 || Input[stoi(myArray[i - 1][1])] == 5)
			Dfront.push(i - 1);
		break;
	case 3:
		for (int N = 1; N <= stoi(myArray[i - 1][5]); N++) {
			IN = stoi(myArray[i][N]);
			if (Input[IN] == 3)
			{
				Input[IN] = 0;
				fancheck(IN);
			}
			node[N - 1] = Input[IN];

		}
		for (int P = 1; P <= stoi(myArray[i - 1][5]); P++) {
			node[P] = OR(node[P - 1], node[P]);
		}
		Input[stoi(myArray[i - 1][1])] = node[stoi(myArray[i - 1][5]) - 1];
		if (Input[stoi(myArray[i - 1][1])] == 4 || Input[stoi(myArray[i - 1][1])] == 5)
			Dfront.push(i - 1);
		break;
	case 5:
		for (int N = 1; N <= stoi(myArray[i - 1][5]); N++) {
			IN = stoi(myArray[i][N]);
			if (Input[IN] == 3)
			{
				Input[IN] = 1;
				fancheck(IN);
			}
			node[N - 1] = Input[IN];
		}


		for (int P = 1; P <= stoi(myArray[i - 1][5]); P++) {

			node[P] = XOR(node[P - 1], node[P]);

		}
		Input[stoi(myArray[i - 1][1])] = node[stoi(myArray[i - 1][5]) - 1];
		if (Input[stoi(myArray[i - 1][1])] == 4 || Input[stoi(myArray[i - 1][1])] == 5)
			Dfront.push(i - 1);
		break;
	case 6:
		for (int N = 1; N <= stoi(myArray[i - 1][5]); N++) {
			IN = stoi(myArray[i][N]);
			if (Input[IN] == 3)
			{
				Input[IN] = 1;
				fancheck(IN);
			}
			node[N - 1] = Input[IN];
		}

		for (int P = 1; P <= stoi(myArray[i - 1][5]); P++) {
			node[P] = XNOR(node[P - 1], node[P]);
		}
		Input[stoi(myArray[i - 1][1])] = node[stoi(myArray[i - 1][5]) - 1];
		if (Input[stoi(myArray[i - 1][1])] == 4 || Input[stoi(myArray[i - 1][1])] == 5)
			Dfront.push(i - 1);
		{

		}
		break;
	case 7:
		for (int N = 1; N <= stoi(myArray[i - 1][5]); N++) {
			IN = stoi(myArray[i][N]);
			if (Input[IN] == 3)
			{
				Input[IN] = 1;
				fancheck(IN);
				Trace.push(IN);
				TraceV.push(1);
				Jfront.push(IN);
			}

			node[N - 1] = Input[IN];

		}


		for (int P = 1; P <= stoi(myArray[i - 1][5]); P++) {

			node[P] = AND(node[P - 1], node[P]);

		}
		Input[stoi(myArray[i - 1][1])] = NOT(node[stoi(myArray[i - 1][5]) - 1]);
		Trace.push(stoi(myArray[i - 1][1]));
		TraceV.push(Input[stoi(myArray[i - 1][1])]);
		if (Input[stoi(myArray[i - 1][1])] == 4 || Input[stoi(myArray[i - 1][1])] == 5)
			Dfront.push(i - 1);
		break;
	case 8:
		for (int N = 1; N <= stoi(myArray[i - 1][5]); N++) {
			IN = stoi(myArray[i][N]);
			if (Input[IN] == 3)
			{
				Input[IN] = 1;
				fancheck(IN);
			}
			node[N - 1] = Input[IN];

		}


		for (int P = 1; P <= stoi(myArray[i - 1][5]); P++) {

			node[P] = AND(node[P - 1], node[P]);

		}
		Input[stoi(myArray[i - 1][1])] = NOT(node[stoi(myArray[i - 1][5]) - 1]);
		if (Input[stoi(myArray[i - 1][1])] == 4 || Input[stoi(myArray[i - 1][1])] == 5)
			Dfront.push(i - 1);
		break;
	case 9:
		for (int N = 1; N <= stoi(myArray[i - 1][5]); N++) {
			IN = stoi(myArray[i][N]);
			if (Input[IN] == 3)
			{
				Input[IN] = 1;
				fancheck(IN);
			}
			node[N - 1] = Input[IN];
		}


		for (int P = 1; P <= stoi(myArray[i - 1][5]); P++) {

			node[P] = OR(node[P - 1], node[P]);

		}
		Input[stoi(myArray[i - 1][1])] = node[stoi(myArray[i - 1][5]) - 1];
		if (Input[stoi(myArray[i - 1][1])] == 4 || Input[stoi(myArray[i - 1][1])] == 5)
			Dfront.push(i - 1);
		break;
	default:
		// operator is doesn't match any case constant (+, -, *, /)
		//cout << "Error! The operator is not correct" << endl;
		break;
	}
}
int Backtrack()
{
	int back, backV, count = 18, Line;
	string A;
	if (!Trace.empty())
	{
		back = Trace.top();
		//cout << "back------- = " << back << endl;
		backV = TraceV.top();
		//cout << "backV------- = " << backV << endl;
		Trace.pop();
		TraceV.pop();
		while (count != 0)
		{
			count += 1;
			if (stoi(myArray[count][1]) == back) {
				Line = count;
				count = 0;
			}
		}
		if (backV == 0)
		{
			Input[back] = 1;
			Jfront.push(back);
			Propagate(myArray[Line][3], Line);
		}
		else if (backV == 1)
		{
			Input[back] = 0;
			Jfront.push(back);
			Propagate(myArray[Line][3], Line);
		}

	}
	else
		return 0;
	return 1;
}

int Tokenize()
{
	int OT = 0;
	ifstream fin;
	string line;
	queue <string> q;
	string s, str;
	int CL = 0, count = 0;
	vector<string> tokens;
	//int limitTR = round(NT * 1593);
	//int limitTS = 1593 - limitTR;
	string address = "C:\\Test\\ISCAS\\c17.txt";
	fin.open(address);
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			sh = sh + 1;
			stringstream ss(line);
			q.push(ss.str());
		}
	}
	fin.close();
	const int Nline = OT;
	//cout << "The size of queue is: " << q.size() << "\n";
	count = 0;


	while (!q.empty())
	{
		str = q.front();
		q.pop();

		regex reg("\\s+");
		sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
		sregex_token_iterator end;
		vector<string> tokens(iter, end);
		//cout << str << "\n";
		CL = 0;
		//cout << "string is :";
		for (const string &s : tokens) {
			myArray[count][CL] = s;
			//cout << myArray[count][CL] << " ";
			CL = CL + 1;
		}
		//cout << endl;
		count = count + 1;
	}
	return count;
}
void Justification(int Lim)
{
	int Jline, count, Diline, OUT, con, counter = 0, Num = 0, TN = 0, C = 0, bcount, bcount1;
	//cout << "--------- Jline------ = " << endl;
	while (!Jfront.empty())
	{
		Jline = Jfront.top();
		Jfront.pop();
		C = 0;
		while (C == 0)
		{
			for (int i = 0; i < LimO; i++)
			{
				C = 1;
				if (Jline == OUTN[i])
				{
					//cout << "Jline--------------" << Jline << "--------------OUTN= " << OUTN[i] << endl;
					Jline = Jfront.top();
					Jfront.pop();
					C = 0;
					break;
				}
			}
		}
		//cout << " Final --------- Jline------ = " << Jline << endl;
		count = 17;
		while (count != 0)
		{
			count += 1;
			if (stoi(myArray[count][1]) == Jline) {
				Diline = count;
				count = 0;
				OUT = Input[Jline];
				//cout << "OUT-----------------= " << OUT << "--------------- Jline" << Jline << endl;
				con = condition(myArray[Diline][3]);
				inconsist = 0;
				switch (con) {
				case 1:
					bcount = 0;
					bcount1 = 0;
					for (int i = 18; i <= Lim; i++) {
						if (myArray[Diline][4] == myArray[i][4] || myArray[Diline][4] == myArray[i][2])
						{
							if (Input[stoi(myArray[i][1])] == Input[stoi(myArray[Diline][1])] || Input[stoi(myArray[i][1])] == 3)
							{
								if (i != Diline && Input[stoi(myArray[i][1])] == 3)
								{
									Input[stoi(myArray[i][1])] = Input[stoi(myArray[Diline][1])];
									Trace.push(stoi(myArray[i][1]));
									TraceV.push(Input[stoi(myArray[i][1])]);
									Jfront.push(stoi(myArray[i][1]));
									bcount1 += 1;
								}
							}
							else
							{
								while (bcount1 != 0)
								{
									Input[Trace.top()] = 3;
									Trace.pop();
									TraceV.pop();
									Jfront.pop();
									bcount1 -= 1;
								}
								inconsist = 1;
								break;
							}
						}
					}
					break;
				case 2:
					if (OUT == 1)
					{
						inconsist = 1;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 1)
							{
								inconsist = 0;
								break;
							}
							else if (Input[IN] == 3)
							{
								Input[IN] = 1;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
								inconsist = 0;
								break;
							}

						}
					}
					else if (OUT == 0) {
						inconsist = 0;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 0;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(0);
								Jfront.push(IN);
							}
							else if (Input[IN] == 1)
							{
								inconsist = 1;
								break;
							}

						}
					}
					else if (OUT == 4) {
						inconsist = 1;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 1;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
								inconsist = 0;
								break;
							}
							else if (Input[IN] == 1)
							{
								inconsist = 0;
								break;
							}

						}
					}

					if (OUT == 5)
					{
						inconsist = 0;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 0;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
							}
							else if (Input[IN] = 1)
							{
								inconsist = 1;
								break;
							}

						}
					}
					break;
				case 3:
					if (OUT == 1)
					{
						inconsist = 0;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 1;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
							}
							else if (Input[IN] == 0)
							{
								inconsist = 1;
								break;
							}

						}
					}
					else if (OUT == 0) {
						inconsist = 1;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 0;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(0);
								Jfront.push(IN);
								inconsist = 0;
								break;
							}
							else if (Input[IN] == 0)
							{
								inconsist = 0;
								break;
							}

						}
					}
					else if (OUT == 5) {
						inconsist = 1;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 0;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(0);
								Jfront.push(IN);
								inconsist = 0;
								break;
							}
							else if (Input[IN] == 0)
							{
								inconsist = 0;
								break;
							}

						}
					}

					if (OUT == 4)
					{
						inconsist = 0;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 1;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
							}
							else if (Input[IN] == 0)
							{
								inconsist = 1;
								break;
							}

						}
					}
					break;
				case 4:
					inconsist = 0;
					IN = stoi(myArray[Diline + 1][1]);
					if (OUT == 0)
					{
						if (Input[IN] == 3)
						{
							Input[IN] = 1;
							//fancheck(IN);
							Trace.push(IN);
							TraceV.push(1);
							Jfront.push(IN);
						}
						else if (Input[IN] == 0)
						{
							inconsist = 1;
							break;
						}
					}
					else if (OUT == 1)
					{
						if (Input[IN] == 3)
						{
							Input[IN] = 0;
							//fancheck(IN);
							Trace.push(IN);
							TraceV.push(0);
							Jfront.push(IN);
						}
						else if (Input[IN] == 1)
						{
							inconsist = 1;
							break;
						}
					}


					break;
				case 5:
					for (int N = 1; N <= stoi(myArray[Diline][5]); N++)
					{
						IN = stoi(myArray[Diline + 1][N]);
						if (Input[IN] == 3)
						{
							counter += 1;
							TN = IN;
						}
						if (Input[IN] == 1)
							Num += 1;
					}
					if (counter > 1 || counter == 0)
					{
						inconsist = 1;
						break;
					}
					else if (OUT == 0 || OUT == 5)
					{
						if ((counter % 2) == 0)
						{
							Input[TN] = 0;
							//fancheck(IN);
							Trace.push(TN);
							TraceV.push(0);
							Jfront.push(TN);
						}
						else
						{
							Input[TN] = 1;
							//fancheck(IN);
							Trace.push(TN);
							TraceV.push(1);
							Jfront.push(TN);
						}
					}
					else if (OUT == 1 || OUT == 4)
					{
						if ((counter % 2) == 0)
						{
							Input[TN] = 1;
							//fancheck(IN);
							Trace.push(TN);
							TraceV.push(1);
							Jfront.push(TN);
						}
						else
						{
							Input[TN] = 0;
							//fancheck(IN);
							Trace.push(TN);
							TraceV.push(0);
							Jfront.push(TN);
						}
					}
					break;
				case 6:
					for (int N = 1; N <= stoi(myArray[Diline][5]); N++)
					{
						IN = stoi(myArray[Diline + 1][N]);
						if (Input[IN] == 3)
						{
							counter += 1;
							TN = IN;
						}
						if (Input[IN] == 1)
							Num += 1;
					}
					if (counter > 1 || counter == 0)
					{
						inconsist = 1;
						break;
					}
					else if (OUT == 0 || OUT == 5)
					{
						if ((counter % 2) == 0)
						{
							Input[TN] = 1;
							//fancheck(IN);
							Trace.push(TN);
							TraceV.push(1);
							Jfront.push(TN);
						}
						else
						{
							Input[TN] = 0;
							//fancheck(IN);
							Trace.push(TN);
							TraceV.push(0);
							Jfront.push(TN);
						}
					}
					else if (OUT == 1 || OUT == 4)
					{
						if ((counter % 2) == 0)
						{
							Input[TN] = 0;
							//fancheck(IN);
							Trace.push(TN);
							TraceV.push(0);
							Jfront.push(TN);
						}
						else
						{
							Input[TN] = 1;
							//fancheck(IN);
							Trace.push(TN);
							TraceV.push(1);
							Jfront.push(TN);
						}
					}
					break;
				case 7:

					if (OUT == 0)
					{

						inconsist = 0;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								
								Input[IN] = 1;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
							}
							else if (Input[IN] == 0)
							{
								inconsist = 1;
								break;
							}

						}
					}
					else if (OUT == 1) {
						inconsist = 1;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 0;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(0);
								Jfront.push(IN);
								inconsist = 0;
								break;
							}
							else if (Input[IN] == 0)
							{
								inconsist = 0;
								break;
							}

						}
					}
					else if (OUT == 4) {

						inconsist = 1;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								
								Input[IN] = 0;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(0);
								Jfront.push(IN);
								inconsist = 0;
								break;
							}
							else if (Input[IN] == 0)
							{
								inconsist = 0;
								break;
							}

						}
					}

					if (OUT == 5)
					{
						inconsist = 0;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{

								Input[IN] = 1;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
							}
							else if (Input[IN] == 0)
							{
								inconsist = 1;
								break;
							}

						}
					}
					break;
				case 8:

					if (OUT == 0)
					{
						inconsist = 1;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 1)
							{
								inconsist = 0;
								break;
							}
							else if (Input[IN] == 3)
							{
								Input[IN] = 1;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
								inconsist = 0;
								break;
							}

						}
					}
					else if (OUT == 1) {
						inconsist = 0;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 0;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(0);
								Jfront.push(IN);
							}
							else if (Input[IN] == 1)
							{
								inconsist = 1;
								break;
							}

						}
					}
					else if (OUT == 5) {
						inconsist = 1;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 1;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
								inconsist = 0;
								break;
							}
							else if (Input[IN] == 1)
							{
								inconsist = 0;
								break;
							}

						}
					}

					if (OUT == 4)
					{
						inconsist = 0;
						for (int N = 1; N <= stoi(myArray[Diline][5]); N++) {
							IN = stoi(myArray[Diline + 1][N]);
							if (Input[IN] == 3)
							{
								Input[IN] = 0;
								//fancheck(IN);
								Trace.push(IN);
								TraceV.push(1);
								Jfront.push(IN);
							}
							else if (Input[IN] = 1)
							{
								inconsist = 1;
								break;
							}

						}
					}
					break;
				case 9:
					inconsist = 0;
					IN = stoi(myArray[Diline + 1][1]);
					if (OUT == 0)
					{
						if (Input[IN] == 3)
						{
							Input[IN] = 0;
							//fancheck(IN);
							Trace.push(IN);
							TraceV.push(0);
							Jfront.push(IN);
						}
						else if (Input[IN] == 1)
						{
							inconsist = 1;
							break;
						}
					}
					else if (OUT == 1)
					{
						if (Input[IN] == 3)
						{
							Input[IN] = 1;
							//fancheck(IN);
							Trace.push(IN);
							TraceV.push(1);
							Jfront.push(IN);
						}
						else if (Input[IN] == 0)
						{
							inconsist = 1;
							break;
						}
					}
					break;
				default:
					// operator is doesn't match any case constant (+, -, *, /)
					//cout << "Error! The operator is not correct" << endl;
					break;

				}
			}
			if (inconsist == 1)
				break;
		}
		if (inconsist == 1)
			break;
	}
}

int DAL(int NUMline)
{
	int Nline, Diline, Dfault, First=1;
	while (!Dfront.empty())
	{
		Diline = Dfront.front();
		Dfront.pop();
		Nline = stoi(myArray[Diline][1]);
		Dfault = Input[Nline];
		int Var = 0;
		string Gate;
		Jfront.push(stoi(myArray[Diline][1]));
		Trace.push(Nline);
		TraceV.push(Dfault);
		if (First == 1)
		{
			for (int i = 18; i < Diline; i++)
			{
				if (myArray[Diline][4] == myArray[i][2])
				{
					//cout << "========  " << Diline << endl;
					//cout << "-----------" << i << endl;
					Var = stoi(myArray[i][1]);
					if (Input[Nline] == 4)
					{
						Input[Var] = 1;
					}
					else if (Input[Nline] == 5)
					{
						Input[Var] = 0;
					}
					else
					{
						Input[Var] = Input[Nline];
					}
					Trace.push(Var);
					TraceV.push(Input[Var]);
					Jfront.push(Var);
				}
				
			}
			First = 0;
		}
		for (int i = Diline + 1; i < NUMline; i++)
		{
			if (myArray[i][3] == "from" && myArray[Diline][4] == myArray[i][4])
			{
				//cout << "-----------" << i << endl;
				Var = stoi(myArray[i][1]);
				Input[Var] = Input[Nline];
				Trace.push(Var);
				TraceV.push(Input[Nline]);
				if (Input[Nline] == 4 || Input[Nline] == 5)
					Dfront.push(i);
				else
					Jfront.push(Var);
			}
			if (myArray[i][3] == "nand" || myArray[i][3] == "and" || myArray[i][3] == "or" || myArray[i][3] == "nor" || myArray[i][3] == "xor" || myArray[i][3] == "xnor" || myArray[i][3] == "not" || myArray[i][3] == "buff")
			{
				//cout << "========  " << Diline << endl;
				for (int j = 1; j <= stoi(myArray[i][5]); j++)
				{
					if (stoi(myArray[i + 1][j]) == Nline)
					{
						Gate = myArray[i][3];
						//cout << "Gate is= " << myArray[i][2] << endl;
						Propagate(Gate, i + 1);
					}
				}
			}

		}
	}
	Justification(NUMline);
	while (inconsist == 1 && !Trace.empty())
	{
		inconsist = 0;
		Backtrack();
		Justification(NUMline);
	}
	return inconsist;
}

int main()
{
	cout << "--------------------------ISCAS module----------------------------" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	int PI = 0;

	Lim = Tokenize();
	Input = (int *)malloc(sizeof(int) * (Lim - 18));
	OUTN = (int *)malloc(sizeof(int) * (stoi(myArray[7][7])));
	int* IN = (int *)malloc(sizeof(int) * (stoi(myArray[6][7])));
	int* OUT_c = (int *)malloc(sizeof(int) * (stoi(myArray[7][7])));
	int* IN_c = (int *)malloc(sizeof(int) * (stoi(myArray[6][7])));
	int counter = 0;
	LimO = 0;
	for (int i = 18; i < Lim; i++)
	{
		if (myArray[i][4] == "0")
		{
			OUTN[counter] = stoi(myArray[i][1]);
			OUT_c[counter] = stoi(myArray[i][1]);
			//cout << "OUT--------- = " << OUTN[counter] << endl;
			counter += 1;
			LimO += 1;
		}
	}

	for (int i = 1; i <= stoi(myArray[7][7]); i++)
	{
		cout << "Output " << i << " = " << OUT_c[i - 1] << endl;
	}


	for (int k = 0; k < 1; k++)
	{
		while (!Dfront.empty())
		{
			Dfront.pop();
		}
		while (!Jfront.empty())
		{
			Jfront.pop();
		}
		while (!Trace.empty())
		{
			Trace.pop();
		}
		while (!TraceV.empty())
		{
			TraceV.pop();
		}
		inconsist = 0;
		if (myArray[k + 18][5] == ">sa1" ||myArray[k + 18][6] == ">sa1"|| myArray[k + 18][7] == ">sa1")
		{
			for (int i = 0; i <= Lim - 18; i++)
			{
				Input[i] = 3;
			}
/*#####################################################INPUT LINE############################################# */
			Input[stoi(myArray[34][1])] = 4;
			Dfront.push(34);
/*#####################################################INPUT LINE############################################# */
			int Unvalid = DAL(Lim);
			if (Unvalid == 0)
			{
				cout << "----------Test vector is produced---------" << k + 18 << endl;
				int Icount = 1, Ocount = 1;
				for (int i = 0; i <= Lim - 18; i++)
				{
					if (myArray[i + 18][3] == "inpt")
					{
						IN_c[Icount - 1] = Input[stoi(myArray[i + 18][1])];
						cout << "PI  " << Icount << " in Line " << i + 18 << " = ";
						if (IN_c[Icount - 1] == 4)
							cout << "D" << endl;
						else if (IN_c[Icount - 1] == 5)
							cout << "DN" << endl;
						else if (IN_c[Icount - 1] == 3)
							cout << "X" << endl;
						else
							cout << IN_c[Icount - 1] << endl;
						Icount += 1;
					}
					if (myArray[i + 18][4] == "0")
					{
						OUT_c[Ocount - 1] = Input[stoi(myArray[i + 18][1])];
						cout << "PO  " << Ocount << " in Line " << i + 18 << " = ";
						if (OUT_c[Ocount - 1] == 4)
							cout << "D" << endl;
						else if (OUT_c[Ocount - 1] == 5)
							cout << "DN" << endl;
						else if (OUT_c[Ocount - 1] == 3)
							cout << "X" << endl;
						else
							cout << OUT_c[Ocount - 1] << endl;
						Ocount += 1;
					}
				}
			}
			else
				cout << "----------Test vector is failed---------" << k + 18 << endl;
			/*int Icount = 1, Ocount = 1;
			for (int i = 1; i <= Lim - 18; i++) {
				cout << "PI  " << Ocount << " in Line " << i << " = " << Input[i] << endl;
				Ocount += 1;
			}*/
			
			
			
				

			
		}
		//if (myArray[k + 18][5] == ">sa0" || myArray[k + 18][6] == ">sa0")
		//{
		//	for (int i = 0; i <= Lim - 18; i++)
		//	{
		//		Input[i] = 3;
		//	}
		//	Input[stoi(myArray[k + 18][1])] = 5;
		//	////fancheck(19,Lim);
		//	Dfront.push(k + 18);
		//	int Unvalid = DAL(Lim);
		//	if (Unvalid == 0)
		//	{
		//		cout << "----------Test vector is produced---------" << k + 18 << endl;
		//		int Icount = 1, Ocount = 1;
		//		for (int i = 0; i <= Lim - 18; i++)
		//		{
		//			if (myArray[i + 18][3] == "inpt")
		//			{
		//				IN_c[Icount - 1] = Input[stoi(myArray[i + 18][1])];
		//				cout << "PI  " << Icount << " in Line " << i + 18 << " = ";
		//				if (IN_c[Icount - 1] == 4)
		//					cout << "D" << endl;
		//				else if (IN_c[Icount - 1] == 5)
		//					cout << "DN" << endl;
		//				else if (IN_c[Icount - 1] == 3)
		//					cout << "X" << endl;
		//				else
		//					cout << IN_c[Icount - 1] << endl;
		//				Icount += 1;
		//			}
		//			if (myArray[i + 18][4] == "0")
		//			{
		//				OUT_c[Ocount - 1] = Input[stoi(myArray[i + 18][1])];
		//				cout << "PO  " << Ocount << " in Line " << i + 18 << " = ";
		//				if (OUT_c[Ocount - 1] == 4)
		//					cout << "D" << endl;
		//				else if (OUT_c[Ocount - 1] == 5)
		//					cout << "DN" << endl;
		//				else if (OUT_c[Ocount - 1] == 3)
		//					cout << "X" << endl;
		//				else
		//					cout << OUT_c[Ocount - 1] << endl;
		//				Ocount += 1;
		//			}
		//		}
		//	}
		//	else
		//		cout << "----------Test vector is failed---------" << endl;



		//	//cout << "PI  " << Ocount << " in Line " << i << " = " << Input[i] << endl;

		//}
	}
	
	_getch();
	return 0;
}
