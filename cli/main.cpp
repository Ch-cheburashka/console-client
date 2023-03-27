#include <iostream>
#include <filesystem>
#include <boost/program_options.hpp>

using fpath = std::filesystem::path;

void download(const fpath& path) {
    if (exists(path))
        std::cout << "such file already exists\n";
    else
        std::cout << "downloading of file: \"" << path << "\" started\n";
}

void upload(const fpath& path) {
    if (!exists(path))
        std::cout << "such file doesn't exists\n";
    else
        std::cout << "uploading of file: \"" << path << "\" started\n";
}



int main(int argc, char **argv) {

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("download","download the given file")
            ("upload", "upload the given file")
            ("filename",boost::program_options::value<fpath>()->required(),"set filename");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }
    std::filesystem::path p;

    if (vm.count("filename"))
        p = vm["filename"].as<fpath>();

    if (vm.count("download")) {
        download(p);
    }

    if (vm.count("upload"))
        upload(p);
    return 0;
}