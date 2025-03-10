#ifndef LADDER_CPP
#define LADDER_CPP

#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << msg << ": " << word1 << " " << word2 << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    return abs(int(str1.length() - str2.length())) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (!edit_distance_within(word1, word2, 1))
        return false;
    int difs = 0;
    int length1 = word1.length(), length2 = word2.length();
    for (int i = 0, j = 0; i < length1 || j < length2; ++i, ++j) {
        if (i >= length1 || j >= length2) {
            ++difs;
        }
        else if (word1[i] != word2[j]) {
            ++difs;
            if (length1 > length2)
                --j; //stop the j pointer and let i increment, skipping char in word1
            else if (length2 > length1)
                --i; //stop the i pointer, let j increment -> skips char in word2
        }
    }
    return difs == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    //check for end_word in word list
    
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = *(ladder.end() - 1);
        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                visited.insert(word);
                vector<string> new_ladder(ladder);
                new_ladder.push_back(word);
                if (word == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }

    return vector<string>();
}

void load_words(set<string> & word_list, const string& file_name) {
    fstream fin;
    fin.open(file_name);
    if (!fin.is_open())
        error("", file_name, "Cannot open file");

    for (string word; getline(fin, word); )
        word_list.insert(word);

    fin.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (auto word : ladder)
        cout << word << " ";
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    const string file_name = "src/words.txt";
    load_words(word_list, file_name);

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}


#endif