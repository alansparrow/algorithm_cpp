// Algorithm.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<string>
#include<map>
#include<unordered_map>
#include<numeric>

using namespace std;

double weighted_value(const pair<string, double>& a, const pair<string, double>& b) {
	return a.second * b.second;
}

void f1() {
	map<string, double> dow_price = {
		{ "MMM",81.86 },
		{ "AA",34.69 },
		{ "MO",54.45 },
	};

	unordered_map<string, double> dow_price1 = {
		{ "MMM",81.86 },
		{ "AA",34.69 },
		{ "MO",54.45 },
	};

	map<string, double> dow_weight = {
		{"MMM", 5.8549},
		{"AA", 2.4808},
		{"MO", 3.8940},
	};
	map<string, string> dow_name = {
		{ "MMM","3M Co." },
		{ "AA", "Alcoa Inc." },
		{ "MO", "Altria Group Inc." },
	};

	//double alcoa_price = dow_price["AAA"];
	//double boeing_price = dow_price["BA"];

	if (dow_price.find("INTC") != dow_price.end())
		cout << "Intel is in the Dow\n";

	for (const auto& p : dow_price) {
		const string& symbol = p.first;
		cout << symbol << '\t' << p.second << '\t'
			<< dow_name[symbol] << '\n';
	}

	double dji_index = inner_product(dow_price.begin(),
		dow_price.end(),
		dow_weight.begin(),
		0.0,
		plus<double>{},
		weighted_value);

	cout << "dji_index: " << dji_index << endl;

	cout << endl << endl;

	for (const auto& p : dow_price1) {
		const string& symbol = p.first;
		cout << symbol << '\t' << p.second << '\t'
			<< dow_name[symbol] << '\n';
	}

}

#include<set>

struct Fruit {
	string name;
	int count;
	double unit_price;

};

ostream& operator<<(ostream& os, const Fruit& f) {
	os << f.name << '\t' << f.count << '\t' << f.unit_price << endl;

	return os;
}

void f2() {


	struct Fruit_order {
		bool operator()(const Fruit& a, const Fruit& b) const {
			return a.name < b.name;
		}
	};

	set<Fruit, Fruit_order> inventory;

	inventory.insert(Fruit{ "quince", 5 });
	inventory.insert(Fruit{ "apple", 200, 0.37 });

	for (auto p = inventory.begin(); p != inventory.end(); ++p) {
		cout << *p << endl;
	}

	for (const auto& x : inventory)
		cout << x << endl;
}

namespace NS {
	template<typename I, typename Out>
	Out copy(I first, I last, Out res) {
		while (first != last) {
			*res = *first;
			++first;
			++res;
		}
		return res;
	}

	template<typename I, typename Out, typename Pred>
	Out copy_if(I first, I last, Out res, Pred p) {
		while (first != last) {
			if (p(*first)) *res = *first;
			first++;
			res++;
		}

		return res;
	}

	void error(const string& msg) {
		cout << msg << endl;
		throw;
	}
}

void f3() {
	vector<double> vd{ 1,2,3,4,5 };
	vector<double> vd1(4);

	if (vd1.size() < vd.size()) NS::error("size error");
	NS::copy(vd.begin(), vd.end(), vd1.begin());

	for (const auto& e : vd1)
		cout << e << '\t';

	cout << endl;
}

#include<iterator>

void f4() {
	ostream_iterator<string> oo{ cout };

	*oo = "Hello, ";
	++oo;
	*oo = "World!\n";

	istream_iterator<string> ii{ cin };

	string s1 = *ii;
	++ii;
	string s2 = *ii;

	*oo = *ii;
}

void f5() {
	vector<int> v1{ 1,2,3,4,5 };
	vector<int> v2{ v1.begin(), v1.end() };

	for (const auto& e : v2)
		cout << e << '\t';

	cout << endl;
}

#include<fstream>

void f6() {
	string from{ "in.txt" };
	string to{ "out.txt" };

	ifstream is{ from };
	ofstream os{ to };

	istream_iterator<string> ii{ is };
	istream_iterator<string> eos;

	ostream_iterator<string> oo{ os, "\n" };

	vector<string> b{ ii, eos };
	sort(b.begin(), b.end());
	//copy(b.begin(), b.end(), oo);
	unique_copy(b.begin(), b.end(), oo);
}

void f7() {
	ifstream is{ "in.txt" };
	ofstream os{ "out1.txt" };

	set<string> b{ istream_iterator<string>{is},
					istream_iterator<string>{} };
	copy(b.begin(), b.end()
		, ostream_iterator<string> {os, " "});
}

class Larger_than {
private:
	int v;
public:
	Larger_than(int vv) : v{ vv } {};
	bool operator()(int x) {
		return x > v;
	}
};

void f8() {
	vector<int> v{ 6,5,7,83,2,1, 10 };
	vector<int> v2(10);

	NS::copy_if(v.begin(), v.end(), v2.begin()
		, Larger_than{ 6 });

	for (const auto& e : v2)
		cout << e << ' ';

	cout << endl;
}

void f9() {
	struct No_case {
		bool operator()(const string& x, const string& y) const {
			for (int i = 0; i < x.length(); i++) {
				if (i == y.length()) return false; // y < x
				char xx = tolower(x[i]);
				char yy = tolower(y[i]);
				if (xx < yy) return true;
				if (xx > yy) return false;
			}

			if (x.length() == y.length()) return false; // x == y

			return true;
		}
	};

	string s1{ "NBCabcdeAWE" };
	string s2{ "aweAWCXC" };

	vector<string> v{ s1, s2 };

	for (const auto& e : v)
		cout << e.c_str() << ' ';
	cout << endl;

	sort(v.begin(), v.end(), No_case{});


	for (const auto& e : v)
		cout << e.c_str() << ' ';
	cout << endl;

}

namespace NS {
	template<typename T>
	void sort(T& t) {
		std::sort(t.begin(), t.end());
	}

	class A {
		int* x;
	public:
		A() : x{ new int{0} } {
			cout << "A()" << endl;
		}
		A(int xx) : x{ new int{xx} } {
			cout << "A(x)" << endl;
		}
		A(const A& a) : x{ new int{*a.x} } {
			cout << "A a {aa} \t copy constructor" << endl;
		}
		A(A&& a) : x{ a.x } {
			cout << "A a { f() } \t move constructor" << endl;
			a.x = nullptr;
		}

		A& operator=(const A& a) {
			cout << "=(const A& a) \t copy assignment" << endl;

			delete x;
			x = new int{ *a.x };

			return *this;
		}

		A& operator=(A&& a) {
			cout << "=(A&& a) \t move assignment" << endl;

			delete x;
			x = a.x;
			a.x = nullptr;

			return *this;
		}

		~A() { 
			delete x; 
			cout << "~A()" << endl;
		}
	};
}


void f10() {
	vector<int> v {5, 4, 1, 2, -1, 5, 8, 7, 0};

	sort(v.begin(), v.begin() + v.size() / 2);

	sort(v.begin() + v.size() / 2, v.end());

	NS::sort(v);

	for (const auto& e : v)
		cout << e << ' ';

	cout << endl;
}

NS::A a_test() {
	NS::A a{ 123 };
	return a;
}

void f11() {
	//NS::A a1;
	//NS::A a1{ 10 };

	// copy constructor
	//NS::A a1;
	//NS::A a2{ a1 };
	
	// move constructor
	//NS::A a1{ a_test() };

	// copy assignment
	//NS::A a1{ 3 };
	//NS::A a2{ 4 };
	//a1 = a2;

	// move assignment
	NS::A a1{ 3 };
	a1 = a_test();

}

int main()
{
	f11();
	//f10();
	//f9();
	//f8();
	//f7();
	//f6();
	//f5();
	//f4();
	//f3();
	//f2();
	//f1();
	return 0;
}

