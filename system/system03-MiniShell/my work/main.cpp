#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdio>
#include <cctype>
#include <algorithm>

enum class Status {
    CONTINUE, ERROR, EXIT
}status;

Status Execute();
Status foo_pwd(std::vector<std::string>);
Status foo_ls(std::vector<std::string>);
Status foo_touch(std::vector<std::string>);
Status foo_cat(std::vector<std::string>);
Status foo_echo(std::vector<std::string>);
Status foo_exit(std::vector<std::string>);
bool is_valid_name(const std::string &name);

std::map<std::string, std::string> files;

int main() {
    while (true) {
        status = Execute();
        if (status == Status::CONTINUE) {
            continue;
        } else if (status == Status::ERROR) {
            std::printf("ERROR\n");
        } else if (status == Status::EXIT) {
            break;
        }
    }
    return 0;
}

Status Execute() {
    std::string command_line, command_code, temp;
    getline(std::cin, command_line);
    std::istringstream sstr(command_line);
    std::vector<std::string> command; command.clear();
    if (!(sstr >> command_code)) {
        return Status::CONTINUE;
    } // The command is empty.
    while (sstr >> temp) {
        command.push_back(temp);
    }
    if (command_code == "pwd") {
        return foo_pwd(command);
    } else if (command_code == "ls") {
        return foo_ls(command);
    } else if (command_code == "touch") {
        return foo_touch(command);
    } else if (command_code == "cat") {
        return foo_cat(command);
    } else if (command_code == "echo") {
        return foo_echo(command);
    } else if (command_code == "exit") {
        return foo_exit(command);
    }
    return Status::ERROR;
}
Status foo_pwd(std::vector<std::string> command) {
    if (!command.empty()) {
        return Status::ERROR;
    }
    putchar('/');
    putchar('\n');
    return Status::CONTINUE;
}
Status foo_ls(std::vector<std::string> command) {
    if (!command.empty()) {
        return Status::ERROR;
    }
    for (auto [name_, content_] : files) {
        std::cout << name_ << '\n';
    }
    return Status::CONTINUE;
}
bool is_valid_name(const std::string &name) {
    if (name == "." || name == "..") {
        return false;
    } // exceptions
    for (auto ch : name) {
        // Check whether ch is a letter.
        if ('a' <= ch && ch <= 'z') {
            continue;
        }
        if ('A' <= ch && ch <= 'Z') {
            continue;
        }
        // Check whether ch is a digit;
        if (isdigit(ch)) {
            continue;
        }
        // Check whether ch is a special letter.
        if (ch == '_' || ch == '.' || ch == '-') {
            continue;
        }
        return false;
    }
    return true;
}
Status foo_touch(std::vector<std::string> command) {
    if (command.size() != 1) {
        return Status::ERROR;
    }
    if (!is_valid_name(command[0])) {
        return Status::ERROR;
    }
    auto it = files.find(command[0]);
    if (it == files.end()) {
        files.emplace(command[0], "");
    }
    return Status::CONTINUE;
}
Status foo_cat(std::vector<std::string> command) {
    if (command.size() != 1) {
        return Status::ERROR;
    }
    if (!is_valid_name(command[0])) {
        return Status::ERROR;
    }
    auto it = files.find(command[0]);
    if (it == files.end()) {
        return Status::ERROR;
    }
    std::cout << it->second << '\n';
    return Status::CONTINUE;
}
Status foo_echo(std::vector<std::string> command) {
    auto it = find(command.begin(), command.end(), ">");
    bool redirected = (it != command.end());
    if (redirected) {
        if (command.end() - it != 2) {
            return Status::ERROR;
        }
        if (!is_valid_name(command.back())) {
            return Status::ERROR;
        }
        std::string temp;
        for (auto str : command) {
            if (str == ">") {
                break;
            }
            temp = temp + str + " ";
        }
        files[command.back()] = temp;
    } else {
        for (auto str : command) {
            std::cout << str << ' ';
        }
        std::cout << '\n';
    }
    return Status::CONTINUE;
}
Status foo_exit(std::vector<std::string> command) {
    if (!command.empty()) {
        return Status::ERROR;
    }
    return Status::EXIT;
}