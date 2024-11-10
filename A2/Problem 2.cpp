#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std ;
vector<string> parseString(const string &str,  vector<string> set , bool Remove = false ) ;
bool IsInSet(string str, vector<string> S);

class StringSet
{
    vector <string> Set ;
    public :
    StringSet() ; // Empty Constructor
    StringSet (string str) ; // Parametrized Constructor
    void addString(string str) ;
    void removeString (string str) ;
    void clearSet() { Set.clear(); }
    void outputSet() ;
    StringSet operator + (StringSet s) ;
    StringSet operator * (StringSet s) ;
    void computeSimilarity (StringSet s) ;
    vector<string> getSet() {return Set; }
    void setSet(vector<string> S) {Set = S ;}
    void PushElement(string str) {Set.push_back(str);}
};
int main()
{

    StringSet s1("IAM UNstoppable and You are nothing ") , s2("Iam UNstoppable and You are nothing ");
    s1.outputSet() ;
    s1.computeSimilarity(s2) ;
    StringSet s3 = s1*s2 ;
    s3.outputSet() ;
    return 0 ;

}
//////////////////////////////////////////////////////////////////////////////////////
StringSet::StringSet(string str) // Parametrized Constructor
{
   setSet( parseString(str, this -> getSet() )) ;
}
StringSet::StringSet()
{
    setSet(vector<string> (0 , "")) ;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void StringSet::addString(string str)
{
setSet(parseString(str, this -> getSet())) ;
}
//////////////////////////////////////////////////////////////////////////////////////
void StringSet::removeString(string str)
{
    setSet(parseString(str, this -> getSet() , true  )) ;
}

//////////////////////////////////////////////////////////////////////////////////////
void StringSet::outputSet()
{
    cout << "The Set  :  { " ;
    for (size_t i = 0; i < Set.size(); i++)
    {
        if(i != Set.size() - 1)
        {
            cout << Set[i] << " , " ;
        }
        else
        {
            cout << Set[i] << " } " ;
        }
    }
    cout << endl;


}

StringSet StringSet::operator+( StringSet  s)
{
    StringSet res = *this ;
   for(auto val : s.getSet() )
   {
       if(IsInSet(val , res.getSet())) {

       };
   }
   return res;

}

StringSet StringSet::operator*(StringSet s)
{
    StringSet res = *this;
    vector<string> tokens = res.getSet();
    vector<string> intersection;  // To store the intersection of the two sets

    // Iterate through each element of the current set and check if it exists in the other set
    for (auto val : tokens)
    {
        if (IsInSet(val, s.getSet()))  // Check if val is in s.getSet()
        {
            intersection.push_back(val);  // If yes, add to the intersection
        }
    }

    res.setSet(intersection);  // Set the new set as the intersection
    return res;
}

void StringSet::computeSimilarity(StringSet s)
{
    vector<string> setQ = this->getSet();  // Get the current set
    vector<string> setD = s.getSet();      // Get the other set
    int intersectionSize = 0;
    // Calculate the size of the intersection of the two sets
    for (const string& word : setQ)
    {
        if (IsInSet(word, setD))  // Check if word is in both sets
        {
            intersectionSize++;
        }
    }
    // Calculate the similarity
    int Q = setQ.size();
    int D = setD.size();
   cout <<  (intersectionSize) / (sqrt(Q) * sqrt(D)) << endl;
}


////////////////////////////////////////////////////////////////////////////
vector<string> parseString(const string &str, vector<string> set, bool Remove)
{
    vector<string> res = set;
    string temp;

    for (char ch : str)
    {
        if (isalpha(ch))
        {
            temp += tolower(ch);
        }
        else if (!temp.empty())
        {
            if (!IsInSet(temp, res))
            {
                res.push_back(temp);
            }
            else if (Remove)
            {
                // Find and erase the element if it exists
                auto it = find(res.begin(), res.end(), temp);
                if (it != res.end())
                {
                    res.erase(it);
                }
            }
            temp.clear();
        }
    }

    // Check the final temp after the loop ends
    if (!temp.empty() && !IsInSet(temp, res))
    {
        res.push_back(temp);
    }

    return res;
}

//////////////////////////////////////////////////////////////////////////////////////
bool IsInSet(string str, vector<string> S)
{
    for (size_t i = 0; i < S.size(); i++)
    {
        if (S[i] == str)
            return true;
    }

    return false;
}
//////////////////////////////////////////////////////////////////////////////////////
