#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;

//Function to check if username or password is invalid
bool Login(string name, int password, vector<string> &names, vector<int> &passwords, vector<int> &ID, int *id)
{
	int it;
	int size = names.size();
	for (it = 0; it < size; it++)
	{
		if (names[it] == name)
		{
			break;
		}

		if (it == size - 1)
		{
			cout << "Invalid username or password\n\n";
			return false;
		}
	}

	if (passwords[it] != password)
	{
		cout << "Invalid username or password\n\n";
		return false;
	}

	*id = ID[it];

	return true;
}

//This function prints all the main questions to the user
void PrintToMe(int id)
{
	int from, to, anonymous;
	string qid;
	ifstream fin("Questions.txt");
	if (!fin.is_open())
	{
		cout << "File opening failed\n";
		return;
	}
	while(!fin.eof())
	{
		string s1, s2, s3;
		getline(fin, s1);
		if (s1 == "\0")
		{
			break;
		}
		istringstream ss1(s1);
		ss1 >> qid >> from >> to >> anonymous;
		if (to == id)
		{
			cout << "\nQuestion Id (" << qid << ") ";
			if (anonymous == 0)
			{
				cout << "from user id(" << from << ")";
			}
			cout << "\t";
			getline(fin, s2);
			cout << "Question: " << s2 << endl;
			getline(fin, s3);
			if (s3 == "\n" || s3 == "\0")
			{
				cout << endl;
			}
			else
			{
				cout << "\tAnswer: " << s3 << endl << endl;
			}
			ifstream fin2(qid+".txt");
			if (!fin2.is_open())
			{
				cout << "File opening failed\n";
				return;
			}
			int from2, to2, anonymous2;
			string qid2;
			while(!fin2.eof())
			{
				string s11, s22, s33;
				getline(fin2, s11);
				if (s11 == "\0")
				{
					break;
				}
				istringstream ss11(s11);
				ss11 >> qid2 >> from2 >> to2 >> anonymous2;
				cout << "\tThread: Question Id (" << qid2 << ") ";
				if (anonymous2 == 0)
				{
					cout << "from user id(" << from2 << ")";
				}
				cout << "\t";
				getline(fin2, s22);
				cout << "Question: " << s22 << endl;
				getline(fin2, s33);
				if (s33 == "\n" || s33 == "\0")
				{
					cout << endl;
				}
				else
				{
					cout << "\tThread: \tAnswer: " << s33 << endl << endl;
				}
			}
			fin2.close();
			cout << endl;
		}
		else
		{
			getline(fin, s1);
			getline(fin, s1);
		}
	}
	fin.close();
}

//This function prints all the questions from the user
void PrintFromMe(int id)
{
	int from, to, anonymous, from2, to2, anonymous2;
	string qid, qid2;
	ifstream fin("Questions.txt");
	if (!fin.is_open())
	{
		cout << "File opening failed\n";
		return;
	}
	while(!fin.eof())
	{
		string s1, s2, s3;
		getline(fin, s1);
		if (s1 == "\0")
		{
			break;
		}
		istringstream ss1(s1);
		ss1 >> qid >> from >> to >> anonymous;
		if (from == id)
		{
			cout << "Question Id (" << qid << ") ";
			if(anonymous == 0)
			{
				cout << "!AQ ";
			}
			cout << "to user id(" << to << ")\t";
			getline(fin, s2);
			cout << "Question: " << s2 << "    ";
			getline(fin, s3);
			if (s3 == "\n" || s3 == "\0")
			{
				cout << "NOT Answered YET\n";
			}
			else
			{
				cout << "Answer: " << s3 << endl;
			}
		}
		else
		{
			getline(fin, s1);
			getline(fin, s1);
		}
		ifstream fin2(qid+".txt");
		if (!fin2.is_open())
		{
			cout << "File opening failed\n";
			return;
		}
		while (!fin2.eof())
		{
			string s11, s22, s33;
			getline(fin2, s11);
			if (s11 == "\0")
			{
				break;
			}
			istringstream ss11(s11);
			ss11 >> qid2 >> from2 >> to2 >> anonymous2;
			if (from2 == id)
			{
				cout << "Question Id (" << qid2 << ") ";
				if(anonymous2 == 0)
				{
					cout << "!AQ ";
				}
				cout << "to user id(" << to2 << ")\t";
				getline(fin2, s22);
				cout << "Question: " << s22 << "    ";
				getline(fin2, s33);
				if (s33 == "\n" || s33 == "\0")
				{
					cout << "NOT Answered YET\n";
				}
				else
				{
					cout << "Answer: " << s33 << endl;
				}
			}
			else
			{
				getline(fin2, s11);
				getline(fin2, s11);
			}
		}
		fin2.close();
	}
	fin.close();
	cout << endl;
}

//This function is used to copy all the lines of a file to a vector
vector<string> copy(string str)
{
	vector<string> LINES;
	ifstream fin(str);
	if (!fin.is_open())
	{
		cout << "File opening failed\n";
		exit(0);
	}
	if (fin.peek() == fin.eof())
	{
		fin.close();
		return LINES;
	}
	string s;

	while (!fin.eof())
	{
		getline(fin, s);
		LINES.push_back(s);
	}
	fin.close();

	return LINES;
}

//Function to copy all the strings in a vector to a file
void copytofile(vector<string> &v, string str)
{
	ofstream of(str);
	if (!of.is_open())
	{
		cout << "File cannot be opened\n";
		return;
	}
	int size = v.size();
	for (int i = 0; i < size - 1; i++)
	{
		of << v[i] << endl;
	}
	of << v[size - 1];
	of.close();
}

//This function is called whenever the used wants to answer a question asked to him
void AnswerQuestion(string QID, int id)
{
	int from, to, anonymous, from2, to2, anonymous2;
	string qid, qid2;
	vector<string> lines = copy("Questions.txt");

	int size = lines.size();
	for (int i = 0; i < size; i += 3)
	{
		string s1, s2, s3;
		s1 = lines[i];
		istringstream ss1(s1);
		ss1 >> qid >> from >> to >> anonymous;

		if (QID == qid)
		{
			if (to != id)
			{
				cout << "Sorry, this question was not asked to you\n";
				return;
			}
			else
			{
				cout << "Question Id (" << qid << ") from user id(" << from << ")\t";
				cout << "Question: ";
				s2 = lines[i + 1];
				cout << s2 << endl;
				s3 = lines[i + 2];
				if (s3 != "\n" && s3 != "\0")
				{
					cout << "\tAnswer: " << s3 << endl;
					cout << "\n\nWarning: Already answered. Answer will be updated\n";
				}
				string ans;
				cout << "Enter answer: ";
				getline(cin, ans);
				if ((i + 2) != size - 1)
				{
					lines[i + 2] = ans;
				}
				else
				{
					lines.pop_back();
					lines.push_back(ans);
				}
				copytofile(lines, "Questions.txt");
				cout << "\n";
				return;
			}
		}
		vector<string> lines2 = copy(qid+".txt");

		int size2 = lines2.size();
		for (int j = 0; j < size2; j += 3)
		{
			string s11, s22, s33;
			s1 = lines2[j];
			istringstream ss11(s1);
			ss11 >> qid2 >> from2 >> to2 >> anonymous2;
			if (QID == qid2)
			{
				if (to2 != id)
				{
					cout << "Sorry, this question was not asked to you\n";
					return;
				}
				else
				{
					cout << "Question Id (" << qid2 << ") from user id(" << from2 << ")\t";
					cout << "Question: ";
					s22 = lines2[j + 1];
					cout << s22 << endl;
					s33 = lines2[j + 2];
					if (s33 != "\n" && s33 != "\0")
					{
						cout << "\tAnswer: " << s33 << endl;
						cout << "\n\nWarning: Already answered. Answer will be updated\n";
					}
					string ans;
					cout << "Enter answer: ";
					getline(cin, ans);
					cout << endl;
					lines2[j + 2] = ans;
					copytofile(lines2, qid+".txt");
					return;
				}
			}
		}
	}

	cout << "Invalid Question ID\n\n";
}

//This function deletes a question asked by the user
void DeleteQuestion(string QID, int id)
{
	int from, to, anonymous, from2, to2, anonymous2;
	string qid, qid2;
	vector<string> lines = copy("Questions.txt");

	for (auto it = lines.begin(); it != lines.end(); it += 3)
	{
		string s1, s2, s3;
		s1 = *it;
		istringstream ss1(s1);
		ss1 >> qid >> from >> to >> anonymous;
		if (QID == qid)
		{
			if (from != id)
			{
				cout << "You are not allowed to delete the question which is not yours\n";
				return;
			}
			else
			{
				lines.erase(it);
				lines.erase(it);
				lines.erase(it);
				copytofile(lines, "Questions.txt");
				return;
			}
		}

		vector<string> lines2 = copy(qid+".txt");
		for (auto itr = lines2.begin(); itr != lines2.end(); itr += 3)
		{
			string s11, s22, s33;
			s11 = *itr;
			istringstream ss11(s11);
			ss11 >> qid2 >> from2 >> to2 >> anonymous2;
			if (QID == qid2)
			{
				if (from2 != id)
				{
					cout << "You are not allowed to delete the question which is not yours\n";
					return;
				}
				else
				{
					lines2.erase(itr);
					lines2.erase(itr);
					lines2.erase(itr);
					copytofile(lines2, qid+".txt");
					return;
				}
			}
		}
	}

	cout << "Invalid Question ID\n\n";
}

//Function that is called when user wants to ask a question
void AskQuestion(string qid, int to, int from, int anonymous)
{
	vector<string> lines;
	string qid1;

	if (qid == "-1")
	{
		lines = copy("Questions.txt");
		srand(time(0));
		int q = rand();
		qid1 = to_string(q);
		ofstream of;
		of.open(qid1+".txt", ios::out);
		if (!of.is_open())
		{
			cout << "Cannot create file\n";
			return;
		}
		of.close();
	}
	else
	{
		lines = copy(qid+".txt");
		srand(time(0));
		int q = rand();
		qid1 = to_string(q);
	}

	string str, str2;
	str = qid1 + " " + to_string(from) + " " + to_string(to) + " " + to_string(anonymous);
	lines.push_back(str);
	cout << "Enter question text: ";
	getline(cin, str2);
	lines.push_back(str2);
	lines.push_back("\0");

	if (qid == "-1")
	{
		copytofile(lines, "Questions.txt");
	}
	else
	{
		copytofile(lines, qid+".txt");
	}

	cout << endl;
}

//Function that lists all the answered questions
void ListFeed()
{
	int from, to, anonymous, from2, to2, anonymous2;
	string qid, qid2;
	ifstream fin("Questions.txt");
	if (!fin.is_open())
	{
		cout << "File opening failed\n";
		return;
	}
	while(!fin.eof())
	{
		string s1, s2, s3;
		getline(fin, s1);
		istringstream ss1(s1);
		ss1 >> qid >> from >> to >> anonymous;
		getline(fin, s2);
		getline(fin, s3);
		if (s3 != "\0")
		{
			cout << "Question Id (" << qid << ") ";
			if (anonymous == 0)
			{
				cout << "from user id(" << from << ") ";
			}
			cout << "To user id(" << to;
			cout << ")\t" << s2 << endl;
			cout << "\tAnswer: " << s3 << endl;
		}
		ifstream fin2(qid+".txt");
		if (!fin2.is_open())
		{
			cout << "File opening failed\n";
			return;
		}
		if (fin2.peek() == fin2.eof())
		{
			fin2.close();
			continue;
		}
		while(!fin2.eof())
		{
			string s11, s22, s33;
			getline(fin2, s11);
			istringstream ss11(s11);
			ss11 >> qid2 >> from2 >> to2 >> anonymous2;
			getline(fin2, s22);
			getline(fin2, s33);
			if (s33 != "\0")
			{
				cout << "Thread Parent Question Id (" << qid << ") Question Id (" << qid2 << ") ";
				if (anonymous == 0)
				{
					cout << "from user id(" << from2 << ") ";
				}
				cout << "To user id(" << to2;
				cout << ")\t" << s22 << endl;
				cout << "\tAnswer: " << s33 << endl;
			}
		}
	}
	cout << endl;
}

int main()
{
	vector<string> usernames;
	vector<int> passwords;
	vector<int> ID;
	vector<int> ANONY;
	vector<string> names;
	usernames.reserve(10000);
	passwords.reserve(10000);
	ID.reserve(10000);
	string name, NAME, email; int password, anony, choice, id;
	int z = 1;

	ifstream fin("Users.txt");
	if (!fin.is_open())
	{
		cout << "File opening failed\n";
		return 0;
	}
	while(!fin.eof())
	{
		string s;
		getline(fin, s);
		istringstream ss(s);
		ss >> id >> name >> password >> anony >> NAME;
		usernames.push_back(name);
		passwords.push_back(password);
		ID.push_back(id);
		ANONY.push_back(anony);
		names.push_back(NAME);
	}
	fin.close();

	/*This do while loop terminates only when:
	  1. User enters 1 and gives valid username and password
	  2. User enters 2 and gives a unique username
	*/
	do
	{
		cout << "Menu:\n";
		cout << "\t1: Login\n\t2: Sign Up\n\n";
		cout << "Enter number in range 1 - 2: ";
		cin >> choice;

		//User wants to login
		if (choice == 1)
		{
			cout << "Enter username & password: ";
			cin >> name >> password;
			if (Login(name, password, usernames, passwords, ID, &id))
			{
				cout << endl;
				break;
			}
		}

		//User wants to sign up
		else if (choice == 2)
		{
			ofstream of;
			of.open("Users.txt", ios::app);
			if (!of.is_open())
			{
				cout << "File opening failed\n";
				return 0;
			}
			cout << "Enter user name. (No spaces): ";
			cin >> name;
			for (auto it : usernames)
			{
				if (name == it)
				{
					cout << "Username already in use\n\n";
					z = 0;
					break;
				}
			}
			if (!z)
			{
				continue;
			}
			usernames.push_back(name);
			cout << "Enter password: ";
			cin >> password;
			passwords.push_back(password);
			cout << "Enter name: ";
			cin >> NAME;
			cout << "Enter email: ";
			cin >> email;
			cout << "Allow anonymous questions?: (0 or 1) ";
			cin >> anony;
			srand(time(0));
			id = rand();
			ID.push_back(id);
			ANONY.push_back(anony);
			names.push_back(NAME);
			of << endl << id << " " << name << " " << password;
			of << " " << anony << " " << NAME << " ";
			of << email;
			of.close();
			cout << endl;
			break;
		}

		else
		{
			cout << "Invalid choice\n\n";
		}
	}while(true);


	string qid;
	int uid, x, i, y, b = 1;
	//This do while loop terminates only when the user logouts, i.e. gives choice as 8
	do
	{
		cout << "Menu:\n";
		cout << "\t1: Print Questions To Me\n";
		cout << "\t2: Print Questions From Me\n";
		cout << "\t3. Answer Question\n";
		cout << "\t4. Delete Question\n";
		cout << "\t5. Ask Question\n";
		cout << "\t6. List System Users\n";
		cout << "\t7. Feed\n";
		cout << "\t8. Logout\n\n";
		cout << "Enter number in range 1 - 8: ";
		cin >> choice;

		switch(choice)
		{
		//User wants to see the questions asked to him
		case 1:
			PrintToMe(id);
			break;

		//User wants to see the questions asked by him
		case 2:
			PrintFromMe(id);
			break;

		//User wants to answer a question
		case 3:
			cout << "Enter Question id or -1 to cancel: ";
			cin >> qid;
			cout << endl;
			cin.ignore(1, '\n');
			if (qid != "-1")
			{
				AnswerQuestion(qid, id);
			}
			break;

		//User wants to delete a question
		case 4:
			cout << "Enter Question id or -1 to cancel: ";
			cin >> qid;
			cout << endl;
			if (qid != "-1")
			{
				DeleteQuestion(qid, id);
			}
			cout << endl;
			break;

		//User wants to ask a question
		case 5:
			cout << "Enter User id or -1 to cancel (Note: You can ask a thread question only to the user who answered the main question): ";
			cin >> uid;
			cout << endl;
			if (uid != -1)
			{
				x = ID.size();
				for (i = 0; i < x; i++)
				{
					if (ID[i] == uid)
					{
						break;
					}
				}
				if (i == x)
				{
					cout << "Invalid User ID\n\n";
				}
				else
				{
					if (ANONY[i] == 0)
					{
						cout << "Note: Anonymous questions are not allowed for this user\n";
						y = 0;
					}
					else
					{
						cout << "Enter if you want to ask the question anonymously or not: (1 or 0) ";
						cin >> y;
					}
					cout << "For thread question: Enter Question id or -1 for new question: ";
					cin >> qid;
					cin.ignore(1, '\n');
					AskQuestion(qid, ID[i], id, y);
					b++;
				}
			}
			break;

		//User wants to see all the system users
		case 6:
			x = ID.size();
			for (int i = 0; i < x; i++)
			{
				cout << "ID: " << ID[i] << "\tName: " << names[i] << endl;
			}
			cout << endl;
			break;

		//User wants to see his feed
		case 7:
			ListFeed();
			break;

		//User wants to logout
		case 8:
			b = 0;
			break;

		default: cout << "ERROR: invalid number...Try again\n\n";
		}
	}while(b);

	return 0;
}
