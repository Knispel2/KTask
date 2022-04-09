#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
using namespace std;

class Cord
{
    
    Cord
};


vector <string> list_files(string dir)
{
    vector <string> result;
    for (const auto& entry : filesystem::directory_iterator(dir))
        result.push_back(entry.path().string().substr(5));
    return result;
}

item split(string data, int num, string file_debug = "")
{
    auto pos = data.find(" ");
    int transp;
    if (data.find("  ") != string::npos) transp = 2;
    else transp = 1;
    return item(stoi(data.substr(0, pos)), stoi(data.substr(pos + transp)), num);
}

int main()
{
    vector <string> data = list_files("data");
    string buf;
    ofstream fout;
    fout.open("result.txt");
    for (string x : data)
    {
        int counter = 0;
        vector <item> items;
        ifstream file("data/" + x);
        getline(file, buf);
        item start_data = split(buf, 0, x);
        double capacity = start_data.w;
        vector <short int> result(start_data.v, 0);
        while (getline(file, buf))
        {
            if (buf == "") continue;
            auto bufer = split(buf, counter, x);
            ++counter;
            if (bufer.w * bufer.v == 0) continue;
            items.push_back(bufer);
        }
        file.close();
        sort(items.begin(), items.end(), [](item a, item b)
            {return ((double)a.v / a.w > (double)b.v / b.w) or (((double)a.v / a.w == (double)b.v / b.w) and (a.w < b.w)); });
        int weight = 0;
        int cost = 0;
        for (const auto obj : items)
            if (weight >= capacity) break;
            else
                if (obj.w <= capacity - weight)
                {
                    weight += obj.w;
                    cost += obj.v;
                    result[obj.num] = 1;
                }
        fout << x << ":" << cost << endl;
        //fout << cost << " " << capacity - weight << endl;
        //for (auto obj : result)
        //    fout << obj << " ";
        //fout << endl;        
    }
    fout.close();
}