#ifndef LADDER_CPP
#define LADDER_CPP

#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << msg << ": " << word1 << " " << word2 << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int length1 = str1.length(), length2 = str2.length();
    if (abs(length1 - length2 > d))
        return false;
    int difs = 0;
    for (int i = 0, j = 0; i < length1 || j < length2; ++i, ++j) {
        if (i >= length1 || j >= length2) {
            ++difs;
        }
        else if (str1[i] != str2[j]) {
            ++difs;
            if (length1 > length2) {
                ++i;
                while (i < length2 && str1[i] != str2[j]) {
                    ++difs;
                    ++i;
                }
            }
            else if (length2 > length1) {
                ++j;
                while (j < length2 && str1[i] != str2[j]) {
                    ++difs;
                    ++j;
                }
            }
        }
        if (difs > d)
            return false;
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

void insert_map(string key, string word, map<string, vector<string>> & map) {
    if (!map.contains(key))
        map[key] = vector<string>();
    map[key].push_back(word);
}

void create_key_map(map<string, vector<string>> & keys, const set<string> word_list) {
    for (string word : word_list) {
        keys[word] = vector<string>();
        int length = word.size();
        for (int i = 0; i < length; ++i) {
            string key = word;
            insert_map(key.replace(i, 1, "*"), word, keys);

            string key2 = word;
            insert_map(key.insert(i, "*"), word, keys);
        }
        keys[word].push_back(word + "*");
    }
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    //check for end_word in word list
    if (!word_list.contains(end_word) || begin_word == end_word)
        return vector<string>();
    
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    /*
    map<string, vector<string>> keys;
    create_key_map(keys, word_list);
    set<string> visited_patterns
    */
    
    while (!ladder_queue.empty()) {
        /*
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = *(ladder.end() - 1);
        if (visited.contains(last_word))
            continue;
        vector<string> patterns;
        int length = last_word.length();
        for (int i = 0; i < length; ++i) {
            string pattern = last_word;
            patterns.push_back(pattern.replace(i, 1, "*"));
            pattern = last_word;
            patterns.push_back(pattern.insert(i, "*"));
        }
        patterns.push_back(last_word + "*");

        for (string p : patterns) {
            if (visited_patterns.contains(p))
                continue;
            visited_patterns.insert(p);
            vector<string> neighbors = keys[p];
            for (string n : neighbors) {
                visited.insert(n);
                vector<string> new_ladder(ladder);
                new_ladder.push_back(n);
                if (n == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }*/

        
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = *(ladder.end() - 1);
        if (visited.contains(last_word))
            continue;
        visited.insert(last_word);
        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
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
    if (ladder.empty())
        cout << "No word ladder found." << endl;
    else {
        cout << "Word ladder found: ";
        for (auto word : ladder)
            cout << word << " ";
        cout << endl;
    }
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