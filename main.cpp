#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// Define the ScriptQuote structure
struct ScriptQuote
{
    int32_t bid[5];
    int32_t ask[5];
    int32_t ltp;
    int32_t volume;
    string ScriptName;
    long long TmFrame;
};

// Function to split a string by delimiter
vector<string> split(const string &str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to read the next line from a CSV file and parse it
bool readNextLine(ifstream &file, ScriptQuote &quote)
{
    string line;
    if (getline(file, line))
    {
        vector<string> tokens = split(line, ',');
        quote.TmFrame = stoll(tokens[0]);
        for (int i = 0; i < 5; ++i)
        {
            quote.bid[i] = stoi(tokens[1 + i]);
            quote.ask[i] = stoi(tokens[6 + i]);
        }
        quote.ltp = stoi(tokens[21]);
        quote.volume = stoi(tokens[22]);
        return true;
    }
    return false;
}

// Comparator for priority queue to order by timestamp
struct Compare
{
    bool operator()(const pair<ScriptQuote, int> &a, const pair<ScriptQuote, int> &b)
    {
        return a.first.TmFrame > b.first.TmFrame;
    }
};

// Function to process the files and update ScriptQuote structure
void processFiles(const vector<string> &filenames)
{
    vector<ifstream> fileHandles(filenames.size());
    priority_queue<pair<ScriptQuote, int>, vector<pair<ScriptQuote, int> >, Compare> pq;

    // Initialize file handles and priority queue
    for (size_t i = 0; i < filenames.size(); ++i)
    {
        fileHandles[i].open(filenames[i].c_str());
        ScriptQuote quote;
        if (readNextLine(fileHandles[i], quote))
        {
            quote.ScriptName = filenames[i];
            pq.push(make_pair(quote, i));
        }
    }

    // Open output file
    ofstream outputFile("output.txt");

    // Process data and update the structure
    while (!pq.empty())
    {
        pair<ScriptQuote, int> top = pq.top();
        pq.pop();

        ScriptQuote quote = top.first;
        int index = top.second;

        // Write to output file
        outputFile << quote.ScriptName << ","
                   << quote.TmFrame << ","
                   << quote.bid[0] << "," << quote.bid[1] << "," << quote.bid[2] << "," << quote.bid[3] << "," << quote.bid[4] << ","
                   << quote.ask[0] << "," << quote.ask[1] << "," << quote.ask[2] << "," << quote.ask[3] << "," << quote.ask[4] << "\n";

        // Read the next line from the same file and push to priority queue
        if (readNextLine(fileHandles[index], quote))
        {
            quote.ScriptName = filenames[index];
            pq.push(make_pair(quote, index));
        }
    }

    // Close all files
    outputFile.close();
    for (size_t i = 0; i < fileHandles.size(); ++i)
    {
        fileHandles[i].close();
    }
}

// Main function
int main()
{
    // Define the list of files (for example)
    string filenamesArray[] = {"input1.csv","input2.csv","input3.csv","input4.csv","input5.csv"};
    vector<string> filenames(filenamesArray, filenamesArray + sizeof(filenamesArray) / sizeof(string));

    // Process the files
    processFiles(filenames);

    return 0;
}