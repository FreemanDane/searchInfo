#include "func.h"

void addChild(tree *father, tree *child)
{
	if (father->child == nullptr)//the parent don't have child
	{
		father->child = child;
		return;
	}
	else
	{
		tree *p = father->child;
		while (p->next != nullptr)//the node isn't the last child of parent
		{
			p = p->next;
		}
		p->next = child;
		return;
	}
}

tree *extractInfo(char *file)
{
	ifstream fin;
	fin.open(file);
	tree *root = nullptr, *current = nullptr;
	stack<tree *> s;
	stack<string *> label_stack;
	bool has_found = false;
	bool need_read = true;
	char new_text[5000];
	while (fin.getline(new_text, 5000))
	{
		string new_read(new_text);
		if (!has_found)//is looking for the label "html"
		{
			if (getLabel(new_read) == "html")
			{
				has_found = true;
				current = new tree;
				current->next = nullptr;
				current->child = nullptr;
				current->label = "html";
				current->data = "";
				current->type = "";
				root = current;
				s.push(root);
				label_stack.push(&(current->label));
			}
		}
		else
		{
			int index = 0;
			while (index < new_read.getLength())//the line isn't over
			{
				if (!need_read && new_read[index] != '<')//now in useless label and haven't read a new label
				{
					index++;
					continue;
				}
				else if (new_read[index] == '<' && new_read[index + 1] == '/')//has read the end label
				{
					if (getLabel(new_read, index) == "/strong")//label "strong" and "/strong" should be ignored
					{
						index = new_read.indexOf('>', index) + 1;
						continue;
					}
					int last_index = new_read.indexOf('>');
					if (meaningfulLabel(getLabel(new_read, index)))//new label is end of useful label
					{
						s.pop();
						if (!s.empty())
							root = s.top();
					}
					label_stack.pop();
					if (meaningfulLabel(*(label_stack.top())))
						need_read = true;
					else
						need_read = false;
					index = new_read.indexOf('>', index) + 1;//jump out of label
				}
				else if (new_read[index] == '<' && !meaningfulLabel(getLabel(new_read, index)))// read a useless label
				{
					label_stack.push(&(getLabel(new_read, index)));
					index = new_read.indexOf('>', index) + 1;
					need_read = false;
				}
				else if (new_read[index] == '<' && new_read[index + 1] != '/')//read a useful label
				{
					if (getLabel(new_read, index) == "strong" || getLabel(new_read, index) == "img" || getLabel(new_read, index) == "hr" || getLabel(new_read, index) == "br")//"strong" label and single label
					{
						index = new_read.indexOf('>', index) + 1;
						continue;
					}
					current = new tree;
					current->next = nullptr;
					current->child = nullptr;
					current->label = getLabel(new_read, index);
					current->type = getType(new_read, index);
					current->data = "";
					addChild(root, current);
					s.push(current);
					label_stack.push(&(current->label));
					root = current;
					index = new_read.indexOf('>', index) + 1;
				}
				else//don't have label
				{
					if (new_read[index] == '&')
					{
						while (new_read[index++] != ';');
						continue;
					}
					current->data.concat(new_read[index]);
					index++;
				}
			}
		}
	}
	return root;
}

void outputTree(tree *root, ofstream & fout)
{
	ifstream ig;
	char need_ignore[500];
	ig.open("ignore.txt");//get useless content
	ig.getline(need_ignore, 500);
	if (root == nullptr)
		return;
	if (root->data.getLength() > 0 && !(root->data.getLength() == 1 && root->data[0] == ' ') && root->data != need_ignore)//will not output useless content
		fout << root->data << std::endl;
	outputTree(root->child, fout);
	outputTree(root->next, fout);
}

void deleteTree(tree *root)
{
	if (root == nullptr)
		return;
	deleteTree(root->child);
	deleteTree(root->next);
	delete root;
}

string getLabel(string & s, int start)
{
	int first_index = s.indexOf('<', start);
	int last_index = s.indexOf('>', first_index);
	if (first_index == -1 || last_index == -1)//don't have label
		return "";
	string childString = s.substring(first_index + 1, last_index - 1);
	int middle_index = childString.indexOf(' ');
	if (middle_index == -1)
		return childString;
	else
	{
		childString = childString.substring(0, middle_index - 1);
		return childString;
	}
}

string getType(string & s, int start)
{
	int first_index = s.indexOf('<', start);
	int last_index = s.indexOf('>', first_index);
	if (first_index == -1 || last_index == -1)
		return "";
	string childString = s.substring(first_index + 1, last_index - 1);
	int middle_index = childString.indexOf(' ');
	if (middle_index == -1)
		return "";
	else
	{
		first_index = childString.indexOf('\"');
		if (first_index == -1)
			return "";
		last_index = childString.indexOf('\"', first_index + 1);
		childString = childString.substring(first_index + 1, last_index - 1);
		return childString;
	}
}

bool hasLabel(string & s)
{
	int i = s.indexOf('<'), j = s.indexOf('>');
	if (i == -1 || j == -1)
		return false;
	else
		return true;
}

bool meaningfulLabel(string & s)
{
	if (s == "meta" || s == "link" || s == "script" || s == "a" || s == "i" || s == "base" || s == "head" ||
		s == "/meta" || s == "/link" || s == "/script" || s == "/a" || s == "/i" || s == "/base" || s == "/head")//useless label
		return false;

	else
		return true;
}

void outputTitle(tree *root, ofstream & fout)
{
	if (root == nullptr)
		return;
	if (root->label == "h1" || (root->label == "h2" && root->type == "question-title"))
	{
		fout << root->data << std::endl;
	}
	else
	{
		outputTitle(root->child, fout);
		outputTitle(root->next, fout);
	}
}

void outputAuthor(tree *root, ofstream & fout)
{
	if (root == nullptr)
		return;
	if (root->type == "author")
	{
		fout << root->data << std::endl;
	}
	else
	{
		outputAuthor(root->child, fout);
		outputAuthor(root->next, fout);
	}
}

void outputContent(tree *root, ofstream & fout)
{
	if (root == nullptr)
		return;
	if (root->type == "content" && root->label == "div")
	{
		outputTree(root, fout);
	}
	else
	{
		outputContent(root->child, fout);
		outputContent(root->next, fout);
	}
}

void informationOut(tree *root, ofstream & fout, string out_file_name)
{
	fout.open(out_file_name.ctr());
	outputTitle(root, fout);
	outputAuthor(root, fout);
	outputContent(root, fout);
	fout.close();
}

void getFileName(string path, list<string> & fileName)
{
	long hFile = 0;
	_finddata_t fileInfo;
	string p;     
	p = path;
	p = p + "//*";
	if((hFile = _findfirst(p.ctr(), &fileInfo)) != -1)
	{
		do
		{
			if(fileInfo.attrib & _A_SUBDIR)
			{
				if(strcmp(fileInfo.name, ".") && strcmp(fileInfo.name, ".."))
					getFileName(path + "//" + fileInfo.name, fileName);
			}
			else
				fileName.add(path + "//" + fileInfo.name);
		}
		while(_findnext(hFile, &fileInfo) == 0);
	}
	_findclose(hFile);
}

void getInfomation()
{
	list<string> fileName;
	getFileName("input", fileName);
	std::cout << "total " << fileName.size() << " files, start to extract information\n";
	ofstream fout;
	for (int i = 0; i < fileName.size(); ++i)
	{
		std::cout << i << std::endl;
		string name = fileName[i];
		int first_index = name.indexOf("//");
		int last_index = name.indexOf('.');
		name = name.substring(first_index, last_index);
		string out_name("output");
		out_name = out_name + name + "info";
		tree *root = extractInfo(fileName[i].ctr());
		informationOut(root, fout, out_name);
		ofstream fout;
		string out_name_2("content");
		out_name_2 = out_name_2 + name + "txt";
		fout.open(out_name_2.ctr());
		outputContent(root, fout);
		fout.close();
		deleteTree(root);
	}
	std::cout << "extract information completed\n";
}

void lineDivideWords(string & content, list<string> & word_list, dictionary & dic)
{
	int index = 0;
	while (index < content.getLength())
	{
		if (content[index] > 0)
		{
			index++;
			continue;
		}
		for (int i = 48; i > 0; i -= 3)
		{
			string word = content.substring(index, index + i - 1);
			if (i == 3)
			{
				if (isChineseSymbol(word))
				{
					index += 3;
					break;
				}
				else
				{
					word_list.add(word);
					index += 3;
					break;
				}
			}
			if (dic.findWords(word))
			{
				index += i;
				word_list.add(word);
				break;
			}
		}
	}
}

void articalDivideWords(char *fileName, dictionary & dic, list<string> & word_list)
{
	ifstream fin;
	fin.open(fileName);
	char new_text[10000];
	while (fin.getline(new_text, 10000))
	{
		string content(new_text);
		lineDivideWords(content, word_list, dic);
	}
}

void articalDivideWords(char *fileName, AVLtree<string> & dic, list<string> & word_list)
{
	ifstream fin;
	fin.open(fileName);
	char new_text[10000];
	while (fin.getline(new_text, 10000))
	{
		string content(new_text);
		lineDivideWords(content, word_list, dic);
	}
}

void lineDivideWords(string & content, list<string> & word_list, AVLtree<string> & dic)
{
	int index = 0;
	while (index < content.getLength())
	{
		if (content[index] > 0)
		{
			index++;
			continue;
		}
		for (int i = 48; i > 0; i -= 3)
		{
			string word = content.substring(index, index + i - 1);
			if (i == 3)
			{
				if (isChineseSymbol(word))
				{
					index += 3;
					break;
				}
				else
				{
					word_list.add(word);
					index += 3;
					break;
				}
			}
			if (dic.find(word))
			{
				index += i;
				word_list.add(word);
				break;
			}
		}
	}
}

void outputDividedWords(list<string> & word_list, char *fileName)
{
	ofstream fout;
	fout.open(fileName);
	while (word_list.size() != 0)
	{
		fout << word_list[0].ctr() << std::endl;
		word_list.remove(0);
	}
	fout.close();
}

void divideWords()
{
	list<string> fileName;
	getFileName("content", fileName);
	ofstream fout;
	dictionary dic;
	dic.addWords("词库.dic");
	std::cout << "start to divided words\nusing hash table";
	//AVLtree<string> dic;
	//dic.addWords("词库.dic");
	//std::cout << "start to divided words\nusing AVLtree";
	for (int i = 0; i < fileName.size(); ++i)
	{
		std::cout << i << std::endl;
		list<string> word_list;
		string name = fileName[i];
		int first_index = name.indexOf("//");
		int last_index = name.indexOf('.');
		string mainName = name.substring(first_index, last_index);
		string out_name("output");
		out_name = out_name + mainName + "txt";
		articalDivideWords(name.ctr(), dic, word_list);
		outputDividedWords(word_list, out_name.ctr());
	}
	system("del /q content");
	system("rmdir /q content");
}

void findAritical(string & a, dictionary & dic, ofstream & fout, docTree & doc_list)
{
	list<string> word_list;
	lineDivideWords(a, word_list, dic);
	struct show_doc
	{
		doc d;
		int has_word;
		bool operator >= (const show_doc & show_d)
		{
			return ((has_word > show_d.has_word) || (has_word == show_d.has_word && d.occurTime >= show_d.d.occurTime));
		}
		bool operator < (const show_doc & show_d)
		{
			return ((has_word < show_d.has_word) || (has_word == show_d.has_word && d.occurTime < show_d.d.occurTime));
		}
		bool operator == (const show_doc & show_d)
		{
			return d == show_d.d;
		}
	};
	list<show_doc> sd;
	for (int i = 0; i < word_list.size(); ++i)
	{
		list<doc> & dl = doc_list.findWord(word_list[i]).docs;
		for (int j = 0; j < dl.size(); ++j)
		{
			bool has_joined = false;
			for (int k = 0; k < sd.size(); ++k)
			{
				if (dl[j] == sd[k].d)
				{
					sd[k].d.occurTime += dl[j].occurTime;
					sd[k].has_word++;
					has_joined = true;
					break;
				}
			}
			if (!has_joined)
			{
				show_doc new_doc;
				new_doc.d = dl[j];
				new_doc.has_word = 1;
				sd.add(new_doc);
			}
		}
	}
	sd.sort();
	for (int i = 0; i < sd.size(); ++i)
	{
		fout << sd[i].d << ' ';
	}
	fout << std::endl;
}

void searchData()
{
	std::cout << "start to create tranverse documents\n";
	dictionary dic;
	dic.addWords("词库.dic");
	ifstream fin, wordFile;
	fin.open("query.txt");
	ofstream fout;
	fout.open("result.txt");
	list<string> fileName;
	docTree doc_list;
	getFileName(string("output"), fileName);
	int num = 0;
	for (int i = 0; i < fileName.size(); ++i)
	{
		if (fileName[i][fileName[i].getLength() - 1] == 't')
		{
			wordFile.open(fileName[i].ctr());
			num++;
			std::cout << num << std::endl;
			char content[100];
			while (wordFile.getline(content, 100))
			{
				doc_list.findWord(string(content)).addDoc(num);
			}
			wordFile.close();
		}
	}
	char content[100];
	while (fin.getline(content, 100))
	{
		findAritical(string(content), dic, fout, doc_list);
	}
	std::cout << "completed!\n";
}
