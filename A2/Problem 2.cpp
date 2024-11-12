#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

// Function declarations
vector<string> parseString(const string &str, vector<string> set, bool Remove = false);
bool IsInSet(const string& str, const vector<string>& S);

class StringSet {
    vector<string> Set;
public:
    StringSet(); // Empty Constructor
    StringSet(const string& input, int type = 2); // Constructor with input type
    void addString(const string& str);
    void removeString(const string& str);
    void clearSet() { Set.clear(); }
    void outputSet() const;
    StringSet operator+(const StringSet& s);
    StringSet operator*(const StringSet& s);
    void computeSimilarity(const StringSet& s);
    vector<string> getSet() const { return Set; }
    void setTokens(const vector<string>& S) { Set = S; }
    void PushElement(const string& str) { Set.push_back(str); }
};

// Main function
int main() {
    StringSet s1("IAM UNstoppable and You are nothing " ), s2("Iam Abdallah and You are nothing ");
    s1.outputSet();
    s1.computeSimilarity(s2);
    StringSet s3 = s1 + s2;
    s3.outputSet();
    StringSet s4 ;
    s4.outputSet();
    return 0;
}

// Empty Constructor
StringSet::StringSet() {
    Set.clear();
}

// Constructor with input type indicator (1 for file, 2 for string)
StringSet::StringSet(const string& input, int type) {
    if (type == 1) { // File input
        ifstream file(input);
        if (file) {
            stringstream ss;
            ss << file.rdbuf();
            setTokens( parseString(ss.str(), vector<string>()) );
        } else {
            cerr << "Error opening file: " << input << endl;
        }
    } else { // String input
        setTokens(parseString(input, vector<string>()));
    }
}

void StringSet::addString(const string& str) {
    Set = parseString(str, this->getSet());
}

void StringSet::removeString(const string& str) {
    Set = parseString(str, this->getSet(), true);
}

void StringSet::outputSet() const {
    cout << "The Set: { ";
    for (size_t i = 0; i < Set.size(); ++i) {
        cout << Set[i];
        if (i != Set.size() - 1) {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

StringSet StringSet::operator+(const StringSet& s) {
    StringSet res = *this;
    for (const auto& val : s.getSet()) {
        if (!IsInSet(val, res.getSet())) {
            res.PushElement(val);
        }
    }
    return res;
}

StringSet StringSet::operator*(const StringSet& s) {
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

void StringSet::computeSimilarity(const StringSet& s) {
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

vector<string> parseString(const string &str, vector<string> set, bool Remove) {
    vector<string> res = set;
    string temp;
    for (char ch : str) {
        if (isalpha(ch)) {
            temp += tolower(ch);
        } else if (!temp.empty()) {
            if (!IsInSet(temp, res)) {
                res.push_back(temp);
            } else if (Remove) {
                auto it = find(res.begin(), res.end(), temp);
                if (it != res.end()) {
                    res.erase(it);
                }
            }
            temp.clear();
        }
    }
    if (!temp.empty() && !IsInSet(temp, res)) {
        res.push_back(temp);
    }
    return res;
}

bool IsInSet(const string& str, const vector<string>& S) {
    return find(S.begin(), S.end(), str) != S.end();
}
