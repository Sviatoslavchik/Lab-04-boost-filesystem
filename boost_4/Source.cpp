#include <boost/filesystem.hpp>
#include <iostream>
#include <map>
#include<string>
std::map<std::string, std::string> Account_Broker;
std::multimap<std::string, int> Account_Date;

void Bypass(boost::filesystem::path s) {
	const boost::filesystem::path p{ s };
	for (boost::filesystem::directory_entry& x : boost::filesystem::directory_iterator(p))
	{
		if (boost::filesystem::is_directory(x))	Bypass(x.path());
		else if (boost::filesystem::is_regular_file(x) && x.path().stem().string().substr(x.path().stem().string().length() - 3, 3) != "old" && x.path().filename().string().substr(0, 7) == "balance") {
			std::cout << x.path().parent_path().filename() << " " << x.path().filename() << '\n';
			Account_Broker.insert(std::pair<std::string, std::string>(x.path().filename().string().substr(8, 8), x.path().parent_path().filename().string()));
			Account_Date.insert(std::pair<std::string, int>(x.path().filename().string().substr(8, 8), atoi(x.path().filename().string().substr(17, 8).c_str())));
		}
	}
	return;
}
int main() {
	const boost::filesystem::path p{ "C:\\Users\\repos\\Boost Filesystem\\ftp" };
	Bypass(p);
	std::vector<int>MAX;
	std::cout << std::endl;
	for (auto it = Account_Broker.begin(); it != Account_Broker.end(); ++it) {
		int max = -1;
		for (auto at = Account_Date.begin(); at != Account_Date.end(); ++at) {
			if (it->first == at->first) {
				if (at->second > max)	max = at->second;
			}
		}
		std::cout << "broker: " << it->second << " account: " << it->first << " files: " << Account_Date.count(it->first) << " last update: " << max << std::endl;
	}
	return 0;
}