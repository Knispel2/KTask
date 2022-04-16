#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
using namespace std;

class Cord
{
private:
    double x, y;
public:    
    Cord(double a, double b) : x(a), y(b)
    {}
    friend double dist(Cord a, Cord b);
};

double dist(Cord a, Cord b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

vector <string> list_files(string dir)
{
    vector <string> result;
    for (const auto& entry : filesystem::directory_iterator(dir))
        result.push_back(entry.path().string().substr(5));
    return result;
}

Cord split(string & data, string file_debug = "")
{
    auto pos = data.find(" ");
    int transp;
    if (data.find("  ") != string::npos) transp = 2;
    else transp = 1;
    return Cord(stod(data.substr(0, pos)), stod(data.substr(pos + transp)));
}

}

int main()
{
    vector <string> data = list_files("data");
    string buf;
    ofstream fout;
    fout.open("result.txt");
    string x;
    for (int k = 0; k < data.size(); k++)
    {
        x = data[k];
        vector <Cord> cords;
        ifstream file("data/" + x);
        getline(file, buf);
        double result = -1;
        while (getline(file, buf))
        {
            if (buf == "") continue;
            cords.push_back(split(buf, x));
        }
        file.close();

        fout << x << ":" << result << endl;      
    }
    fout.close();
}


bool check_perm(const vector <unsigned int>& base)
{
    for (int i = 0; i < base.size(); i++)
        if (base[base[i] - 1] == i + 1) return false;
    return true;
}

double cost_perm(vector <unsigned int>& permutations, vector <Cord>& cords)
{
    double result = 0;
    for (int i = 0; i < permutations.size(); i++)
        result += dist(cords[i + 1], cords[permutations[i] - 1]);
    return result;

double brutforce_method(vector <Cord> cords, double result)
{
    vector <unsigned int> permutations(cords.size());
    for (int i = 0; i < cords.size(); i++)
        permutations[i] = i + 1;
    double buf;
    do {
        if (check_perm(permutations))
        {
            buf = cost_perm(permutations, cords);
            if (buf > result)
                result = buf;
        }
    } while (next_permutation(permutations.begin(), permutations.end()));
}