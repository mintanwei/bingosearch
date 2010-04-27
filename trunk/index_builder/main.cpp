#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    string imageSrc;
    string pageUrl;
    string size;
    string format;
    double rank;
    int id;
};

bool operator<(const Node& A, const Node& B)
{
    if (A.rank != B.rank) 
    {
        return A.rank > B.rank;
    }
    return A.id < B.id;
}

int main(int argc, const char *argv[])
{
    
    ifstream in("../data/query_list");

    if (in.fail()) 
    {
        cerr << "FAIL TO OPEN FILE ../data/query_list" << endl;
        exit(1);
    }

    string cur;
    string query;
    while (in >> query) 
    {
        vector<Node> A;
        vector<string> metaData;
        vector<double> visualRank;

        string file("../data/meta_data/");
        file.append(query);
        ifstream in1(file.c_str());
        if (in1.fail()) 
        {
            cerr << "FAIL TO OPEN FILE ../data/meta_data/" << query << endl;
            exit(1);
        }
        while (getline(in1, cur)) 
        {
            metaData.push_back(cur);
        }

        file.assign("../data/visual_rank/");
        file.append(query);
        ifstream in2(file.c_str());
        if (in2.fail()) 
        {
            cerr << "FAIL TO OPEN FILE ../data/visual_rank/" << query << endl;
            exit(1);
        }
        double tmp;
        while (in2 >> tmp) 
        {
            visualRank.push_back(tmp);
        }

        Node curNode;
        A.reserve(visualRank.size());
        for (size_t i = 0; i < visualRank.size(); ++i) 
        {
            curNode.imageSrc = metaData[4 * i];
            curNode.pageUrl = metaData[4 * i + 1];
            curNode.size = metaData[4 * i + 2];
            curNode.format = metaData[4 * i + 3];
            curNode.rank = visualRank[i];
            curNode.id = i;
            A.push_back(curNode);
        }
        sort(A.begin(), A.end());

        file.assign("../data/index/");
        file.append(query);
        ofstream out(file.c_str());

        if (out.fail()) 
        {
            cerr << "FAIL TO CREATE FILE ../data/index/" << query << endl;
            exit(1);
        }

        for (size_t i = 0; i < A.size(); ++i) 
        {
            out << A[i].id << endl;
            out << A[i].imageSrc << endl;
            out << A[i].pageUrl << endl;
            out << A[i].size << endl;
            out << A[i].format << endl;
            out << A[i].rank << endl;
            out << endl;
        }
    }


    return 0;
}
