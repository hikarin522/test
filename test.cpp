// test.cpp
// hikari

#include <iostream>
#include <vector>
#include <string>
#include <boost/version.hpp>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

auto f()
{
	return 100'000'000;
}

int main(int argc, char *argv[], char *envp[])
{
	vector<string> argstr(argv, argv + argc);
	vector<string> envstr(envp, [](char *i[]){while (*++i); return i;}(envp));
	decltype(auto) y = f();
	cout << format("�͂�[ %1%\n\n") % y;

	cout << format("Boost version : %1%.%2%.%3%\n\n") % (BOOST_VERSION / 100'000) % (BOOST_VERSION / 100 % 1'000) % (BOOST_VERSION % 100);

	cout << format("�R�}���h���C������\n");
	for (auto &i : argstr)
		cout << format("%1%\n") % i;

	cout << format("\n���ϐ�\n");
	for (auto &i : envstr)
		cout << format("%1%\n") % i;

	cout << format("\n�����\n");

	cin >> argstr[0];
	return 0;
}
