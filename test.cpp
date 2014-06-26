
#include <boost/version.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

auto f(){ return 100'000'000; }

int main(int argc, char *argv[], char *envp[])
{
	vector<string> argstr(argv, argv + argc);;
	vector<string> envstr(envp, [](char *i[]){while (*++i); return i;}(envp));
	decltype(auto) y = f();
	cout << format("はろー %1%\n\n") % y;

	cout << format("Boost version : %1%.%2%.%3%\n\n") % (BOOST_VERSION / 100000) % (BOOST_VERSION / 100 % 1000) % (BOOST_VERSION % 100);

	cout << format("コマンドライン引数\n");
	for (auto &i : argstr)
		cout << format("%1%\n") % i;

	cout << format("\n環境変数\n");
	for (auto &i : envstr)
		cout << format("%1%\n") % i;

	cout << format("\nおわり\n");

	cin >> argstr[0];
	return 0;
}
