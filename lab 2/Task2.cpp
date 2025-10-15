#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;
namespace fs = filesystem;

// Helper function to check if a character is a vowel
bool isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// Split a line into words
vector<string> splitWords(const string &line) {
    vector<string> words;
    string word = "";
    for (char c : line) {
        if (isalpha(c))
            word += tolower(c);
        else if (!word.empty()) {
            words.push_back(word);
            word = "";
        }
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

int main() {
    string directoryPath, outputPath;
    cout << "Enter directory path containing text files: ";
    getline(cin >> ws, directoryPath);
    cout << "Enter output file path (e.g., report.csv): ";
    getline(cin >> ws, outputPath);

    // List of common stop words to ignore
    set<string> stopWords = {"the", "and", "in", "on", "is", "it", "of", "to", "a", "an", "for"};

    ofstream report(outputPath);
    if (!report.is_open()) {
        cout << "Error: Cannot open output file!" << endl;
        return 1;
    }

    report << "File Name,Lines,Words,Top 3 Words,Avg Word Length,Vowel/Consonant Ratio\n";

    int totalFiles = 0;

    try {
        for (const auto &entry : fs::directory_iterator(directoryPath)) {
            if (entry.path().extension() == ".txt") {
                totalFiles++;

                ifstream file(entry.path());
                if (!file.is_open()) {
                    cout << "Skipping file: " << entry.path().filename() << endl;
                    continue;
                }

                int lineCount = 0, wordCount = 0;
                double totalWordLength = 0;
                int vowels = 0, consonants = 0;
                map<string, int> wordFrequency;

                string line;
                while (getline(file, line)) {
                    lineCount++;
                    vector<string> words = splitWords(line);

                    for (string word : words) {
                        wordCount++;
                        totalWordLength += word.length();
                        for (char ch : word) {
                            if (isalpha(ch)) {
                                if (isVowel(ch)) vowels++;
                                else consonants++;
                            }
                        }
                        if (stopWords.find(word) == stopWords.end())
                            wordFrequency[word]++;
                    }
                }

                // Find top 3 most common words
                vector<pair<string, int>> freqVec(wordFrequency.begin(), wordFrequency.end()); //convert to vector for sorting 
                sort(freqVec.begin(), freqVec.end(), [](auto &a, auto &b) {
                    return a.second > b.second;
                });

                string topWords = "";
                for (int i = 0; i < min(3, (int)freqVec.size()); i++) {
                    if (i > 0) topWords += " ";
                    topWords += freqVec[i].first + "(" + to_string(freqVec[i].second) + ")";
                }

                double avgWordLength = (wordCount == 0) ? 0 : totalWordLength / wordCount;
                double ratio = (consonants == 0) ? 0 : (double)vowels / consonants;

                // Write to report
                report << entry.path().filename().string() << ","
                       << lineCount << ","
                       << wordCount << ","
                       << "\"" << topWords << "\","
                       << fixed << setprecision(2) << avgWordLength << ","
                       << fixed << setprecision(2) << ratio << "\n";

                file.close();
            }
        }

        cout << "\nAnalysis complete. Total files analyzed: " << totalFiles << endl;
        cout << "Report saved to: " << outputPath << endl;

    } catch (const exception &e) {
        cout << "Error accessing directory: " << e.what() << endl;
    }

    report.close();
    return 0;
}
