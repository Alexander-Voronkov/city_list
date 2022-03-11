#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using std::map;
using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::_Node_handle;
using std::cout;
using std::endl;

void print(const vector<string>& elem)
{
	for (int i=0; i <elem.size(); i++)
	{
		cout << elem[i] << endl;
	}
}

class Country_city
{
	map<string, vector<string>> cc;
public:
	Country_city(string& where) {
		ifstream in(where);
		string temp;
		string temp1;
		bool id1;
		while (!in.eof())
		{
			in >> id1;
			if (!id1)
				in >> temp;
			else
			{
				in >> temp1;
				vector<string> tempv;
				tempv.push_back(temp1);
				cc[temp] = tempv;
			}
			if (id1&&cc.find(temp)!=cc.end())
			{			
				auto z=cc.find(temp);
				z->second.push_back(temp1);
			}				
		}
		in.close();
	}
	void print_cities(string& country)
	{
		if (cc.find(country)==cc.end())
		{
			cout << "Страны по запросу не найдено." << endl;
		}
		else
		{
			print(cc[country]);
		}
	}
	void add_cities(string& country,vector<string>&a)
	{
		try { if (cc.find(country) == cc.end())throw "Такой страны не найдено, будет создан новый элемент дерева."; }
		catch (string i)
		{
			cout << i; 
			cc[country] = a;
		}
		for (auto i = a.begin(); i !=a.end();  i++)
		{
			if (cc.find(country) != cc.end())
			{
				cc.find(country)->second.push_back(*(i));
			}
		}
	}
	bool is_country(string& country)
	{
		if (cc.find(country) != cc.end())
			return 1;
		return 0;
	}
	void country_delete(string& country) 
	{
		if(cc.find(country)!=cc.end())
		cc.erase(country);
	}
	void country_replace(string& country1,string&country2)
	{
		if (cc.find(country1) != cc.end()&& cc.find(country2) == cc.end())
		{
			auto z = cc.extract(country1);
			z.key() = country2;
			cc.insert_or_assign(z.key(),z.mapped());
		}
	}
	void print_all_countries()
	{
		for (auto i = cc.begin(); i != cc.end(); i++)
		{
			cout << i->first << endl;
		}
	}
	int count_cities()
	{
		int count = 0;
		for (auto i=cc.begin();i!=cc.end();i++)
		{
			count+=i->second.size();
		}
		return count;
	}
	void replace_city_name(string& city1, string& city2)
	{
		bool o = 0;
		for (auto i = cc.begin(); i != cc.end(); i++)
		{
			for (auto j = 0; j < i->second.size(); j++)
			{
				if (i->second[j] == city1)
				{
					i->second[j] = city2;
					o = 1;
				}
			}
		}
		if (!o)
			throw"Не найден такой город.";
	}
	void save(string& where)
	{
		ofstream out(where);
		for (auto i = cc.begin(); i != cc.end(); i++)
		{
			out << 0 << endl<< i->first << endl;
			for (size_t j = 0; j < i->second.size(); j++)
			{
				out <<1<<endl<< i->second[j] << endl;
			}
		}
		out.close();
	}
};