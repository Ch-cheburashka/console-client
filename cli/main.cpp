#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <boost/program_options.hpp>

using fpath = std::filesystem::path;

void download(const std::string& file) {
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

void upload(const std::string& file) {
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



int main(int argc, char **argv) {

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("download","download the given file")
            ("upload", "upload the given file")
            ("filename",boost::program_options::value<std::string>()->required(),"set filename");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }
    std::string file;
    if (vm.count("filename"))
        file = vm["filename"].as<std::string>();

    if (vm.count("download")) {
        download(file);
    }

    if (vm.count("upload"))
        upload(file);
    return 0;
}