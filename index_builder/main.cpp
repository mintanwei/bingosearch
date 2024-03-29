#include "log.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace bingo::common;

struct Node
{
	string thumbnailUrl;
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

void BuildIndex(const string& query, const char* visualRankPath, const char* indexPath)
{
	vector<Node> A;
	vector<string> metaData;
	vector<double> visualRank;

	string file("../data/meta_data/");
	file.append(query);
	ifstream in1(file.c_str());
	if (in1.fail()) 
	{
		Log::Output("index_builder", (string)("FAIL TO OPEN FILE ../data/meta_data/") + query, Log::ERROR);
		exit(1);
	}

	string cur;
	while (getline(in1, cur)) 
	{
		metaData.push_back(cur);
	}

	file.assign(visualRankPath);
	file.append(query);
	ifstream in2(file.c_str());
	if (in2.fail()) 
	{
		Log::Output("index_builder", (string)("FAIL TO OPEN FILE ") + visualRankPath + query, Log::ERROR);
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
		curNode.thumbnailUrl = metaData[5 * i];
		curNode.imageSrc = metaData[5 * i + 1];
		curNode.pageUrl = metaData[5 * i + 2];
		curNode.size = metaData[5 * i + 3];
		curNode.format = metaData[5 * i + 4];
		curNode.rank = visualRank[i];
		curNode.id = i;
		A.push_back(curNode);
	}
	sort(A.begin(), A.end());

	file.assign(indexPath);
	file.append(query);
	ofstream out(file.c_str());

	if (out.fail()) 
	{
		Log::Output("index_builder", (string)("FAIL TO CREATE FILE ") + indexPath + query, Log::ERROR);
		exit(1);
	}

	for (size_t i = 0; i < A.size(); ++i) 
	{
		out << A[i].id << endl;
		out << A[i].thumbnailUrl << endl;
		out << A[i].imageSrc << endl;
		out << A[i].pageUrl << endl;
		out << A[i].size << endl;
		out << A[i].format << endl;
		out << A[i].rank << endl;
		out << endl;
	}
}

int main(int argc, const char *argv[])
{

	ifstream in("../data/query_list");

	if (in.fail()) 
	{
		Log::Output("index_builder main.cpp", "FAIL TO OPEN FILE ../data/query_list", Log::ERROR);
		exit(1);
	}

	string query;
	while (in >> query) 
	{
		BuildIndex(query, "../data/visual_rank/", "../data/index/");
		BuildIndex(query, "../data/visual_rank_sift/", "../data/index_sift/");
	}
	return 0;
}
