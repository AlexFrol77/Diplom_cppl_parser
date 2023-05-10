#include "Parser.h"


Parser::Parser(std::string titlePath) : titlePath_(titlePath) {
	this->fin.open(titlePath_);
	if (!(this->fin.is_open())) {
		throw std::runtime_error("The file did not open!");
	}
	while (!fin.eof()) {
		std::string temp = "";
		getline(fin, temp);
		this->source_ini_.push_back(temp);
	}
	fin.close();
}

Parser::~Parser() { }

std::vector<std::string> Parser::getVarName() {
	std::string temp = "";
	if (countVarName == 0) {
		for (int i = 0; i < source_ini_.size(); i++) {
			if (source_ini_[i].find("[") == std::string::npos) {
				temp_name_ = "";
				name_var_ = source_ini_[i];
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
		}
	}
	return vec_var_name_;
}

std::vector<std::string> Parser::getSecName() {
	if (countSecName == 0) {
		for (int i = 0; i < source_ini_.size(); i++) {
			if (source_ini_[i].find("[") != std::string::npos) {
				temp_name_ = "";
				name_sec_ = source_ini_[i];
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
	for (const auto& st : source_ini_) {
		std::cout << st << "\n";
	}
}
