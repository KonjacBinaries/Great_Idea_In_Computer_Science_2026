#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace {

using FileTable = std::map<std::string, std::string>;
enum class Result { Continue, Exit, Error };

bool valid_filename(const std::string& name) {
    if (name.empty() || name == "." || name == "..") {
        return false;
    }
    return std::all_of(name.begin(), name.end(), [](unsigned char ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
               (ch >= '0' && ch <= '9') || ch == '_' || ch == '.' || ch == '-';
    });
}

Result execute(const std::vector<std::string>& words, FileTable& files) {
    const std::string& command = words.front();
    if (command == "pwd" || command == "ls" || command == "exit") {
        if (words.size() != 1) {
            return Result::Error;
        }
        if (command == "exit") {
            return Result::Exit;
        }
        if (command == "pwd") {
            std::cout << "/\n";
        } else {
            // std::map keeps file names in lexicographical order.
            for (const auto& entry : files) {
                std::cout << entry.first << '\n';
            }
        }
        return Result::Continue;
    }

    if (command == "touch" || command == "cat") {
        if (words.size() != 2 || !valid_filename(words[1])) {
            return Result::Error;
        }
        if (command == "touch") {
            // emplace leaves an existing file's content unchanged.
            files.emplace(words[1], "");
        } else {
            const auto file = files.find(words[1]);
            if (file == files.end()) {
                return Result::Error;
            }
            std::cout << file->second;
        }
        return Result::Continue;
    }

    if (command == "echo") {
        const auto redirect = std::find(words.begin() + 1, words.end(), ">");
        const bool redirected = redirect != words.end();
        if (redirected) {
            // Validate the whole suffix before printing or changing files.
            if (words.end() - redirect != 2 || !valid_filename(words.back())) {
                return Result::Error;
            }
        }
        std::string output;
        for (auto word = words.begin() + 1; word != redirect; ++word) {
            if (word != words.begin() + 1) {
                output += ' ';
            }
            output += *word;
        }
        output += '\n';
        if (redirected) {
            files[words.back()] = output;
        } else {
            std::cout << output;
        }
        return Result::Continue;
    }
    return Result::Error;
}

}  // namespace

int main() {
    // The single virtual root directory is implicit; no real files are used.
    FileTable files;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        std::istringstream input(line);
        std::vector<std::string> words;
        std::string word;
        while (input >> word) {
            words.push_back(word);
        }
        if (words.empty()) {
            continue;
        }
        const Result result = execute(words, files);
        if (result == Result::Exit) {
            break;
        }
        if (result == Result::Error) {
            std::cout << "ERROR\n";
        }
    }
    return 0;
}
