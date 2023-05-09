#include "Parser.h"


Parser::Parser(std::string titlePath) : titlePath_(titlePath) {
	this->fin.open(titlePath_);
	if (!(this->fin.is_open())) {
		throw std::runtime_error("The file did not open!");
	}
}

Parser::~Parser() {
	fin.close();
}

std::vector<std::string> Parser::getVarName() {
	fin.seekg(0, std::ios::beg);
	if (countVarName == 0) {
		while (!fin.eof()) {
			getline(fin, name_var_);
			if (name_var_.find("[") == std::string::npos) {
				temp_name_ = "";
				for (int i = 0; i < name_var_.size(); i++) {
					if (name_var_[i] == '=' || name_var_[i] == ';') {
						break;
					}
					if (name_var_[i] != ' ') {
						temp_name_ += name_var_[i];
					}
				}
				flag = true;
				for (const auto& st : vec_var_name_) {
					if (st == temp_name_) {
						flag = false;
						break;
					}
					else {
						flag = true;
					}
				}
				if (flag && !temp_name_.empty()) {
					vec_var_name_.push_back(temp_name_);
				}
			}
			countVarName++;
		}
	}
	return vec_var_name_;
}

std::vector<std::string> Parser::getSecName() {
	fin.seekg(0, std::ios::beg);
	if (countSecName == 0) {
		while (!fin.eof()) {
			getline(fin, name_sec_);
			if (name_sec_.find("[") != std::string::npos) {
				temp_name_ = "";
				for (int i = name_sec_.find('['); i < name_sec_.size(); i++) {
					if (name_sec_[i] == '=' || name_sec_[i] == ';' || name_sec_[i] == ']') {
						break;
					}
					if (name_sec_[i] != ' ' && name_sec_[i] != '[') {
						temp_name_ += name_sec_[i];
					}
				}
				flag = true;
				for (const auto& st : vec_sec_name_) {
					if (st == temp_name_) {
						flag = false;
						break;
					}
					else {
						flag = true;
					}
				}
				if (flag && !temp_name_.empty()) {
					vec_sec_name_.push_back(temp_name_);
				}
			}
			countSecName++;
		}
	}
	return vec_sec_name_;
}

void Parser::printIni() {
	fin.seekg(0, std::ios::beg);
	while (!fin.eof()) {
		getline(fin, temp_name_);
		std::cout << temp_name_ << "\n";
	}
}