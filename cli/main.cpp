#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <argparse/argparse.hpp>

using fpath = std::filesystem::path;

struct command {
    command() = default;
};

struct upload : public command {
    explicit upload(const std::string& file) {
        const fpath p{std::filesystem::current_path()};
        bool found = false;
        for (const std::filesystem::directory_entry &x: std::filesystem::directory_iterator{p}) {
            auto entry_str = std::string(x.path());
            if (entry_str.substr(entry_str.find_last_of('/') + 1) == file) {
                found = true;
                break;
            }
        }
        if (!found)
            std::cout << "such file doesn't exists\n";
        else {
            std::string res;
            std::ifstream file_to_read;
            file_to_read.open(file);
            char ch;
            int str_index = 0;
            while (file_to_read.get(ch)) {
                if (ch == '\n') {
                    str_index++;
                    if (str_index > 2 && str_index%100 == 0) {
                        std::cout << res << "hundred\n";
                        res.clear();
                    }
                }
                res += ch;
            }
            std::cout << res << "\n";
        }
    }
};

struct download : public command {
    explicit download(const std::string& file) {
        const fpath p{std::filesystem::current_path()};
        bool found = false;
        for (const std::filesystem::directory_entry &x: std::filesystem::directory_iterator{p}) {
            auto entry_str = std::string(x.path());
            if (entry_str.substr(entry_str.find_last_of('/') + 1) == file) {
                found = true;
                break;
            }
        }
        if (found)
            std::cout << "such file already exists\n";
        else {
            std::ofstream file_to_download;
            file_to_download.open(std::string(p) + "/" + file);
            file_to_download.close();
            std::cout << "\"" << file << "\" is downloaded\n";
        }
    }
};


int main(int argc, char **argv) {

    argparse::ArgumentParser opt_desc("console-client");

    opt_desc.add_argument("--download")
    .default_value(false)
    .implicit_value(true);

    opt_desc.add_argument("--upload")
    .default_value(false)
    .implicit_value(true);

    opt_desc.add_argument("--filename")
    .required()
    .default_value(std::string{});

    opt_desc.parse_args(argc,argv);

    auto file = opt_desc.get<std::string>("--filename");

    if (opt_desc["--download"] == true) {
        download{file};
    }

    if (opt_desc["--upload"] == true) {
        upload{file};
    }

    return 0;
}