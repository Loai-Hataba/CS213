// File: A1_T1_20230553.cpp
// Purpose: Assignment 1 Task 1 for CS213 Course
// Author: Loai Hataba
// Section: 20
// ID: 20230553
// TA: --
// Date: 6 Oct 2024
// The program has 4 main sub programs:
// 1) Split-> splits a sentence and add a delimiter of choice between the words
// 2) Binary Calculator-> has two options either two to convert a decimal number to binary one or two give all the possible permutations based on given number of bits
// 3) Teddy-> is a game where there are certain conditions for playing such as that you start with a given number and your goal is to reach exactly 42 bears, you start with a number if its even you give back the number you had divided by 2, if its divisible by 5 you give back exactly 42 bears, if its divisible by 3 or 4 you multiply its last two digits and give out that number
// 4) Phishing Scanner-> A program that finds potential words of phishing in a given email file

// ******************************************************* Test Cases ********************************************************
// Here are some test cases so you can test the program
/* 1) Split-> 

-> 90,9876,7890,7858
,

Output: ["90", "9876", "7890", "7858"]


-> Welcome ya user ya habiby to CS213 Assignment 1 Task 1 Program!
  
(one space Character)

Output: ['Welcome', 'ya', 'user', 'ya', 'habiby', 'to', 'CS213', 'Assignment', '1', 'Task', '1', 'Program!']


-> isa_hageeb_A+_:D
_

Output: ['isa', 'hageeb', 'A+', ':D']


-> "" (Empty String)
Output: [""]

*/

/* 2) Binary Calculator->
        1) one number->
            -> 10
            Output: 1010

            -> 5
            Output: 101

            -> 579
            Output: 10011000011

        2) many numbers->
         -> 3
            1000

            Output: 1000000
                    1000001
                    1000010
                    1000011
                    1000100
                    1000101
                    1000110
                    1000111

         -> 2
            111
            
            Output:
                    11100
                    11101
                    11110
                    11111            
*/

/* 3) Teddy->

-> 250
Output: True

-> 300
Output: False

-> 42
Output: True

-> 500 
Output: True

-> 100
Output: False

-> 10
Output: False
*/

/* 4) Phishing Scanner->
    add any of these to a .txt file and write the path to it in the program

    
    Email 1: Subject: Urgent Action Required - Unauthorized Access Detected
Dear User,
We have detected suspicious activity on your account. Unauthorized access was logged from an unfamiliar location. To secure your account, click here and follow the instructions to reset your password. Failure to act immediately may result in account suspension.
Sincerely,
Security Team

Email 2: Subject: You've Won a Free Gift!
Hello,
Congratulations! You've been selected to receive a free gift from our promotional event. This offer is valid for a limited time only, so click below to claim your reward! Make sure to verify your email to confirm eligibility.
Best regards,
Promotions Team

Email 3: Subject: Your Subscription Renewal Notice
Dear Subscriber,
This is a friendly reminder that your subscription will be renewed on the upcoming date. If you wish to make any changes to your payment method or cancel your subscription, please visit our website and update your details before the renewal date.
Thank you for choosing our services.
Customer Support

Email 4: Subject: Scheduled Maintenance Notification
Dear Valued Customer,
We will be performing routine maintenance on our servers next Tuesday. During this time, access to your account may be temporarily unavailable. There is no action required on your part. Thank you for your understanding and continued support.
Best regards,
Tech Team

*/
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <unordered_map>
#include <fstream>
// colors for terminal
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
using namespace std;

// Problem 1
vector<string> split(string sentence, string delimiter);
// Problem 2
void phishing(string file);
// Problem 3
class Binary_calculator{
    public:
        static void print_number(int n){
            if (n == 0){
                return;
            }
            print_number(n/2);
            cout << n%2;
    }

        static void printManyNumber(string prefix, int n){
            int possible = pow(2,n);
            for (int i = 0; i<possible;i++){
                cout << prefix;
                //turn i into binary
                cout << bitset<16>(i).to_string().substr(16-n) << endl;
            }
        }
};
// Problem 4
class Teddy{
    public:
        static bool bear(int n){
            // Win
            if (n == 42)
            {
                return true;
            }
            // Lose
            if (n < 42)
            {
                return false;
            }
            // divisible by 5
            if (n % 5 == 0)
            {
                if(bear(n-42))
                {
                    return true;
                }
            }
            // divisible by 3 or 4
            if (n % 3 == 0 || n % 4 == 0)
            {
                int first = n % 10;
                int second = ((n % 100)/ 10);
                int nBack = first * second;
                if (nBack > 0 && nBack < n)
                {
                    if(bear(n-nBack))
                    {
                        return true;
                    }
                }
            }
            // even
            if (n % 2 == 0)
            {
                if (bear(n /= 2))
                {
                    return true;
                }
            }
            return false;
        }
};

int main(){
    // Menu
    cout << GREEN << "         _____   _____   ______       "<<RED<<"______     _      " << endl;
    cout << GREEN << "        /\\  __`\\/\\  __`\\/\\  __`\\     "<<RED<<"/\\  _  \\  /' \\     " << endl;
    cout << GREEN << "        \\ \\ \\/\\ \\ \\ \\/\\ \\ \\ \\ \\ \\    "<<RED<<"\\ \\ \\L\\ \\/\\_, \\    " << endl;
    cout << GREEN << "         \\ \\ \\ \\ \\ \\ \\ \\ \\ \\  __/     "<<RED<<"\\ \\  __ \\/_/\\ \\   " << endl;
    cout << GREEN << "          \\ \\ \\_\\ \\ \\ \\_\\ \\ \\ \\/       "<<RED<<"\\ \\ \\/\\ \\ \\ \\ \\  " << endl;
    cout << GREEN << "           \\ \\_____\\ \\_____\\ \\_\\        "<<RED<<"\\ \\_\\ \\_\\ \\ \\_\\ " << endl;
    cout << GREEN << "            \\/_____/\\/_____/\\/_/         "<<RED<<"\\/_/\\/_/  \\/_/ " << endl;
    cout << GREEN << "                                                       " << RESET << endl;
    cout << "-------------------------------------------------------------------------------------\n";
    cout << "                  \033[1;34mWelcome ya user ya habiby to CS213 Assignment 1 Task 1 Program!\033[0m\n";
    cout << "                   " << GREEN << "                  Made by Loai Hataba\n" << RESET;

    while (true){
    // Menu
    cout << "\033[4;36m\nMain Menu:\033[0m\n";
    cout << "----------------------------------\n";
    cout << "1. Split\n";
    cout << "2. Binary Calculator\n";
    cout << "3. Teddy\n";
    cout << "4. Phishing Scanner\n";
    cout << "5. Exit\n";
    cout << "----------------------------------\n";
    cout << "Please select an option (1-5):\n";
    char ans;
    cin >> ans;
        // not a digit
    while (isdigit(ans) == 0)
    {
        cout << "Invalid option. Please try again.\n";
        cin >> ans;
    }
    if (ans == '1')
    {
        //take input
        string sentence;
        string delimeter;
        cin.ignore();
        cout << "Enter the sentence: ";
        getline(cin, sentence);
        if(sentence.empty())
        {
            cout << "Output: [\"\"]\n";
            continue;
        }
        cout << "Enter the delimiter: ";
        getline(cin, delimeter);
        if(delimeter.empty())
        {
            cout << "Output: [\""<< sentence <<"\"" << endl;
            continue;
        }
        cout << endl;
        split(sentence, delimeter);
    }
    else if (ans == '2')
    {
        cout << "\n----------------------------------\n";
        cout << "1. One Number\n";
        cout << "2. Permutations\n";
        char ans_2;
        cin >> ans_2;
        if (ans_2 == '1')
        {
            int n_one;
            cout << "Enter the number: ";
            cin >> n_one;
            cout << endl;
            // if 0
            if (n_one == 0)
            {
                cout << "0\n";
                continue;
            }
            cout << "Output: " << flush;
            Binary_calculator::print_number(n_one);
            cout << endl;
        }
        else if (ans_2 == '2')
        {
            int n_many;
            string prefix;
            cout << "Enter the number of bits: ";
            cin >> n_many;
            cin.ignore();
            cout << "Enter the prefix: ";
            getline(cin, prefix);
            cout << "\nOutput: \n";
            Binary_calculator::printManyNumber(prefix, n_many);
            cout << endl;
        }
        else
        {
            cout << "Invalid option. Please try again.\n";
        }
    }
    else if (ans == '3')
    {
        int n_three = -1;
        //start until exit code "0"
        while (n_three != 0){
            cout << "Enter Starting bears number: (0->Exit)";
            cin >> n_three;
            if (n_three == 0)
            {
                break;
            }
            bool ted = Teddy::bear(n_three);
            if (ted)
            {
                cout << "\n***True***\n\n";
            }
            else 
            {
                cout << "\n***False***\n\n";
            }
        }
    }
    else if (ans == '4')
    {
        // Enter name of path of desired email.txt file
        cout << "Enter File Path: ";
        string file_path;
        cin >> file_path;
        phishing(file_path);
    }
    else if (ans == '5')
    {
        cout << "Exiting...\n";
        return false;
    }
    else{
        cout << "Invalid option. Please try again.\n";
        return false;
    
    }
    }
    return 0;
}

// Split
vector<string> split(string sentence, string delimiter)
{
    vector<string> arr;
    size_t pos = 0;
    // Find delimeter
    while ((pos = sentence.find(delimiter)) != string::npos)
    {
        arr.push_back(sentence.substr(0, pos));
        //erase word and delimeter to start again from the beginning of the new sentence
        sentence.erase(0, pos + delimiter.length());
    }
    arr.push_back(sentence);

    // Printing the result
    cout << "Output: [";
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << "'" << arr[i] << "'";
        if (i != arr.size() - 1)
            cout << ", ";
    }
    cout << "]\n\n";

    return arr;
}

// Lowercase
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Phishing Scanner
void phishing(string filepath)
{
    // List of Phrases with their weights
    unordered_map<string, int> phrases = {
    {"urgent action required", 3},
    {"account suspended", 3},
    {"verify your identity", 3},
    {"login immediately", 3},
    {"your password has expired", 3},
    {"click here to reactivate", 3},
    {"unauthorized access detected", 3},
    {"your account has been compromised", 3},
    {"security alert", 3},
    {"update payment information", 3},
    {"confirm your account", 3},
    {"you've won a prize", 3},
    {"limited time offer", 3},
    {"suspicious activity", 3},
    {"reset your password", 3},
    {"Your account will be locked unless you take action", 3},
    {"customer support", 2},
    {"verify payment details", 2},
    {"unusual login attempt", 2},
    {"secure your account", 2},
    {"free gift", 2},
    {"click below", 2},
    {"apple support", 2},
    {"paypal account", 2},
    {"amazon notification", 2},
    {"confirm your email", 2},
    {"congratulations!", 1},
    {"final notice", 1},
    {"claim your reward", 1},
    {"microsoft support", 1}
    };
    
    // Read file
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    // Occurrences
    unordered_map<string, int> counts;
    // Store email in string
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    content = toLowerCase(content);
    int totalScore = 0;
    // Look for phrases
     for (const auto& phrase : phrases) {
        int pos = 0;
        while ((pos = content.find(phrase.first, pos)) != std::string::npos) {
            totalScore += phrase.second; // Update total score
            counts[phrase.first]++;       // Increment the count for the found phrase
            pos += phrase.first.length();  // Move past teh found phrase
        }
    }

    for (const auto& count : counts) {
        if (count.second > 0) {
            std::cout << "Phrase: '" << count.first << "' | Count: " << count.second << std::endl;
        }
    }

    if (totalScore > 6) {
        cout << "\nPotential phishing detected! (Something Smells PHISHY in here...)" << endl;
        return;
    }
    else {
        cout << "\nEmail looks legit!!" << endl;
        return;
    }


}