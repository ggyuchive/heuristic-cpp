#include <fstream>
#include <string>

struct FileIO {
    FileIO(const std::string& in_file_)
        : in_file(in_file_), fin(in_file_), fout(make_outfile(in_file_)) {}

    // e.g. Make ./01_sudoku/output/01.out
    std::string make_outfile(const std::string& path) {
        size_t prob_s = path.find_first_of('/') + 1;
        size_t prob_e = path.find('/', 2) - 1;
        std::string prob_str = path.substr(prob_s, prob_e-prob_s+1);

        size_t num_s = path.find_last_of('/') + 1;
        size_t num_e = path.find_last_of('.') - 1;
        std::string prob_num_str = path.substr(num_s, num_e-num_s+1);
        problem_num = std::stoi(prob_num_str);
        out_file = "./" + prob_str + "/output/" + prob_num_str + ".out";
        return out_file;
    }

    int problem_num;
    std::string in_file;
    std::string out_file;
    std::ifstream fin;
    std::ofstream fout;
};
