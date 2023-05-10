#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Parser {
public:
	Parser(std::string titlePath);
	~Parser();
	
	template <class T>
	T getValue(std::string section, std::string variable) {
		fin.seekg(0, std::ios::beg);
		T result_ = 0;
		while (!(fin.eof())) {
			if (flag) {
				getline(fin, find_section_);
			}
			flag = true;
			if (find_section_.find(section) != std::string::npos) {
				do {
					getline(fin, find_str_);
					if (find_str_.find(variable) != std::string::npos) {
						bool check = true;
						int check_count = 0;
						result_ = 0;
						for (int i = find_str_.find(variable) + variable.size();
							i < find_str_.size(); i++) {
							if (find_str_[i] == '.') {
								check = false;
							}
							if (find_str_[i] >= '0' && find_str_[i] <= '9' && check
								&& find_str_[i] != '.' && check_count == 0) {
								result_ += static_cast<char>(find_str_[i]) - '0';
							}
							if (find_str_[i] >= '0' && find_str_[i] <= '9' && check 
								&& find_str_[i] != '.' && check_count != 0) {
								result_ *= 10;
								result_ += static_cast<char>(find_str_[i]) - '0';
							}
							if (find_str_[i] >= '0' && find_str_[i] <= '9' && !check
								&& find_str_[i] != '.' && check_count != 0) {
								double num = static_cast<char>(find_str_[i]) - '0';
								result_ += (num / 10);
							}
							if (find_str_[i] == ' ') {
								break;
							}
							check_count++;
						}
					}
					if (find_str_.find("[") != std::string::npos) {
						flag = false;
						find_section_ = find_str_;
					}
				} while (!fin.eof() && flag);
			}
		}
		if (result_ == 0) {
			throw std::runtime_error("NO VALUE!!!");
		}
		
		return result_;
	}
	template <>
	std::string getValue(std::string section, std::string variable) {
		fin.seekg(0, std::ios::beg);
		std::string result_ = "";
		while (!(fin.eof())) {
			if (flag) {
				getline(fin, find_section_);
			}
			flag = true;
			if (find_section_.find(section) != std::string::npos) {
				do {
					getline(fin, find_str_);
					if (find_str_.find(variable) != std::string::npos) {
						bool check = true;
						int check_count = 0;
						result_ = "";
						for (int i = find_str_.find(variable) + variable.size();
							i < find_str_.size(); i++) {
							if (find_str_[i] != '=' && find_str_[i] != ';') {
								result_ += find_str_[i];
							}
							if (find_str_[i] == ';' || find_str_[i] == '\n') {
								break;
							}
						}
					}
					if (find_str_.find("[") != std::string::npos) {
						flag = false;
						find_section_ = find_str_;
					}
				} while (!fin.eof() && flag);
			}
		}
		if (result_.empty()) {
			throw std::runtime_error("NO VALUE!!!");
		}

		return result_;
	}
	std::vector<std::string> getVarName();
	std::vector<std::string> getSecName();
	void printIni();

private:

	std::string titlePath_,
				find_str_,
				find_section_,
				name_var_,
				name_sec_,
				temp_name_;

	bool flag = true;

	std::vector<std::string> vec_var_name_,
							 vec_sec_name_;
	std::ifstream fin;
	int countSecName = 0,
		countVarName = 0;

};
