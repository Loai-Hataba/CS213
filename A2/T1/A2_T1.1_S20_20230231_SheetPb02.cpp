#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
using namespace std;

class StringSet {
    vector<string> Set; // Internal storage for the set of strings
    // Helper function to get the current set
    vector<string> getSet() {return Set;}
    // Helper function to set tokens to the internal set
    void setTokens(const vector<string>& S) {Set = S;}
    // Add a string to the set
    void PushElement(const string& str) {Set.push_back(str);}
    // Parse a string into tokens and add/remove them to/from the set
    vector<string> parseString(const string &str, vector<string> set, bool Remove = false);
    // Check if a string is in a given set of strings
    bool IsInSet(const string& str, const vector<string>& S);
    string GetFilePath() ;

public:
    StringSet() {Set.clear();}// Default constructor
    StringSet(const string& input, bool isFile); // Constructor to initialize set from file or string input
    void addString(const string& str); // Add string to the set
    void removeString(const string& str); // Remove string from the set
    void clearSet() { Set.clear();}
    int getLength() {return Set.size();}
    bool isSetEmpty () {return getSet().empty() ;}
    void outputSet(); // Display the set contents
    StringSet operator+(StringSet& s); // Union operator
    StringSet operator*(StringSet& s); // Intersection operator
    void computeSimilarity(StringSet& s); // Compute similarity with another set
};

string GetPath() {
    string Res;
    cout << "\nPlease Enter The Path (e.g., C:\\Users\\YourUsername\\Documents\\example.txt): ";
    getline(cin, Res);
    return Res;
}
void displayMenu() {
    cout << "\n===== StringSet Application Menu =====" << endl ;
    cout << "1. Load Set 1 \n";
    cout << "2. Load Set 2 \n";
    cout << "3. Compute similarity between two documents\n";
    cout << "4. Run demo\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
  StringSet S1("Iam A funcking Gymrat", false ) , S2 ("Iam A fuNcKiNg Programmer" , false );
  StringSet s3 = S1+S2 ;
  s3.outputSet() ;
  s3.getLength() ;
  S1.computeSimilarity(s3) ;
  S2.computeSimilarity(s3) ;
  s3= S1 *S2 ;
  s3.outputSet() ;
 
  S1.computeSimilarity(s3);
  S2.removeString("Programmer") ;
  S2.addString("Gymrat") ;
  S2.outputSet();

  S1.computeSimilarity(S2) ;

}


///// Class Member Functions
// Constructor to initialize set from a file or string input
StringSet::StringSet(const string& input, bool isFile) {
    if (isFile) { // File input handling
        int numOfFails = 0;
        while (true) {
            string fileName = input;
            if (numOfFails > 0) {
                cout << "Please enter your Valid file path: ";
                fileName = GetFilePath(); // Get new file path if previous attempt failed
            }
            ifstream file(fileName);
            if (file.is_open()) {
                stringstream ss;
                ss << file.rdbuf();
                setTokens(parseString(ss.str(), vector<string>()));
                file.close(); // Close file after processing
                break; // Successfully processed file
            } else {
                cin.clear(); // Clear error flags
                cout << "Error opening the file. Please enter a valid path.\n" << endl;
                numOfFails++;
            }
        }
    } else { // String input handling
        setTokens(parseString(input, vector<string>()));
    }
}

// Add string to the set after parsing
void StringSet::addString(const string& str) {
    setTokens(parseString(str, this->getSet()));
}

// Remove string from the set
void StringSet::removeString(const string& str) {
    setTokens(parseString(str, this->getSet(), true));
}

// Output the current contents of the set
void StringSet::outputSet() {
    cout << "The Set: { ";
    for (size_t i = 0; i < Set.size(); ++i) {
        cout << Set[i];
        if (i != Set.size() - 1) {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

// Union operator for combining two StringSets
StringSet StringSet::operator+(StringSet& s) {
    StringSet res = *this;
    for (auto& val : s.getSet()) {
        if (!IsInSet(val, res.getSet())) {
            res.PushElement(val);
        }
    }
    return res;
}

// Intersection operator for finding common elements between two StringSets
StringSet StringSet::operator*(StringSet& s) {
    StringSet res;
    vector<string> intersection;
    for (const auto& val : Set) {
        if (IsInSet(val, s.getSet())) {
            intersection.push_back(val);
        }
    }
    res.setTokens(intersection);
    return res;
}

// Compute similarity between this set and another set
void StringSet::computeSimilarity(StringSet& s) {
    vector<string> setQ = this->getSet();
    vector<string> setD = s.getSet();
    int intersectionSize = 0;
    for (const string& word : setQ) {
        if (IsInSet(word, setD)) {
            intersectionSize++;
        }
    }
    int Q = setQ.size();
    int D = setD.size();
    double similarity = (Q > 0 && D > 0) ? (intersectionSize / (sqrt(Q) * sqrt(D))) : 0;
    cout << "Similarity: " << similarity << endl;
}

// Parse a string into words and optionally add/remove them from a set
vector<string> StringSet::parseString(const string &str, vector<string> set, bool Remove) {
    vector<string> res = set; // Copy input set for modifications
    string temp;
    for (char ch : str) {
        if (isalpha(ch)) {
            // Accumulate alphabetic characters (converted to lowercase)
            temp += tolower(ch);
        }
        else if (!temp.empty()) {
            // Process accumulated word
            auto it = find(res.begin(), res.end(), temp);
            if (!Remove) {
                // Add if not already present
                if (it == res.end()) {
                    res.push_back(temp);
                }
            } else {
                // Remove if found
                if (it != res.end()) {
                    res.erase(it);
                }
            }
            temp.clear(); // Clear temp for next word
        }
    }

    // Handle the last word if string ends without a delimiter
    if (!temp.empty()) {
        auto it = find(res.begin(), res.end(), temp);
        if (!Remove && it == res.end()) {
            res.push_back(temp);
        } else if (Remove && it != res.end()) {
            res.erase(it);
        }
    }

    return res; // Return the modified set
}

// Check if a string is present in a given vector of strings
bool StringSet::IsInSet(const string& str, const vector<string>& S) {
    return find(S.begin(), S.end(), str) != S.end();
}

string StringSet::GetFilePath()
{
    string Res;
    cout << "\nPlease Enter The Path (e.g., C:\\Users\\YourUsername\\Documents\\example.txt): ";
    getline(cin, Res);
    return Res;
}
