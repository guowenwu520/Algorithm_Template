#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    int k = 0;
    ifstream infile("log.txt");
    string line;
    string logs[2001][3];
    int max_p = 0, ant = 0;
    long long last_time = 0;
    while (getline(infile, line))
    {
        char a, b;
        long long cur = 0;
        bool fig = false;
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;

        while (std::getline(iss, token, ' '))
        {
            tokens.push_back(token);
        }

        a = tokens[0][0];
        b = tokens[1][0];
        cur = std::stoll(tokens[2]);
        if (a == b)
        {
            if (cur - last_time <= 1000)
            {
                max_p++;
            }
            else
            {
                if (max_p > ant)
                    ant = max_p;
                max_p = 1;
            }
        }
        else
        {
            if (max_p > ant)
                ant = max_p;
            max_p = 0;
        }
        last_time = cur;
        cout << last_time << endl;
    }

    cout << ant << endl;
    return 0;
}