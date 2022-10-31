#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

/////////////////////////////////// 1 номер //////////////////////////////////////

void split(const string &text, vector <string> &elems) {
	string word;
	stringstream ss(text);
	while (getline(ss, word, ' '))
		elems.push_back(word);
}

void remove_punctuation(string &text){
	while (text.find(',') != -1)
		text.erase(text.find(','), 1);
}

void remove_spaces(string &str)
{
	for (std::string::iterator it = str.begin(); it != str.end(); it++)
	{
		string::iterator begin = it;
		while (it != str.end() && isspace(*it) )
			it++;
		if (it - begin > 1)
			it = str.erase(begin + 1, it) - 1;
	}
}

void find_starts_with(const string &target, string &text){
	vector<string> words;
	vector<string> answer;
	remove_punctuation(text);
	remove_spaces(text);
	split(text, words);
	for (int i=0; i<words.size(); i++){
		if (target.size() <= words[i].size()){
			bool flag = true;
			for (int j=0; j<target.size(); j++){
				if (target[j] != words[i][j])
					flag = false;
			}
			if (flag){
				cout << words[i] << endl;
				answer.push_back(words[i]);
			}
		}
	}
}

void _1(){
	string text = "hello, ,,   friend,        hellohello, fries ,,  fr, fri, efri";
	string target = "fri";
	find_starts_with(target, text);
}
/////////////////////////////////// 2 номер //////////////////////////////////////
#define SIZE 128

int* bad_char(const string &target){
	int* table = new int[SIZE]; // размер алфавита
	for (int i=0; i<=SIZE-1; i++)
		table[i] = target.size();
	for (int i=0; i<=target.size()-2; i++){
		table[target[i]] = target.size() - 1 - i;
	}
	return table;
}

bool is_prefix(const string &target, int p){
	int j = 0;
	for (int i=p; i<=target.size()-1; i++){
		if (target[i] != target[j])
			return false;
		++j;
	}
	return true;
}

int suffix_length(const string &target, int p){
	int len = 0;
	int i = p;
	int j = target.size() - 1;
	while (i >= 0 && target[i] == target[j]){
		++len;
		--i;
		--j;
	}
	return len;
}

int* good_suffix(const string &target){
	int* table = new int[target.size()];
	int lastPrefixPosition = target.size();
	for (int i=target.size()-1; i>=0; i--){
		// Если подстрока x[i+1..m-1] является префиксом, то запомним её начало
		if (is_prefix(target, i + 1))
			lastPrefixPosition = i + 1;
		table[target.size() - 1 - i] = lastPrefixPosition - i + target.size() - 1;
	}
	// Вычисление функции по определению
	for (int i=0; i<=target.size()-2; i++){
		int slen = suffix_length(target, i);
		table[slen] = target.size() - 1 - i + slen;
	}
	return table;
}

/*
 *   function BM(char[n] y, char[m] x): vector <int>
     vector <int> answer // вектор, содержащий все вхождения подстроки в строку
     if m == 0
        answer.pushBack(-1) // Искомая подстрока является пустой
        return answer

     // Предварительные вычисления
     int[ |Σ| ] bmBc = preBmBc(x)
     int[m] bmGs = preBmGs(x)

     // Поиск подстроки
     for i = m - 1 .. n - 1
        int j = m - 1
        while x[j] == y[i]
           if j == 0
              answer.pushBack(i) // Найдена подстрока в позиции i
           --i
           --j
        i += max(bmGs[m - 1 - j], bmBc[y[i]])
     if (answer == ∅)
        answer.pushBack(-1) // Искомая подстрока не найдена
     return answer
 */


vector<int> BM(const string &text,const string &target){
	vector<int> answer;
	if (target.size() == 0){
		answer.push_back(-1);
		return answer;
	}

	// Предварительные вычисления
	int* bc = bad_char(target);
	int* gs = good_suffix(target);

	// Поиск подстроки
	for (int i=target.size()-1; i<=text.size()-1; i++){
		int j = target.size() - 1;
		while (target[j] == text[i]){
			if (j == 0)
				answer.push_back(i);
			--i;
			--j;
		}
		i += max(gs[target.size() - 1 - j], bc[text[i]]);
	}
	return answer;
}

void get_data(string &text, string &target){
	ifstream input("input.txt");
	if (input.is_open())
	{
		getline(input, target);
		cout << target << endl;
		getline(input, text);
		cout << text << endl;
	}
}

void _2(){
	string target;
	string text;
	get_data(text, target);
	vector<int> ans = BM(text, target);
	cout << ans.size() << endl;
	for (int i=0; i<ans.size(); i++){
		cout << ans[i] << endl;
	}
}

int main(){
//	_1();
	_2();
	return 0;
}