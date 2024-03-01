#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const string FILE_END = "" + (char)EOF;
namespace mode {
    const char input = 0b1;
    const char output = 0b10;
};


class File{
    fstream self;
    size_t pos = 1;
    string path;
    bool is_open;

    // Read a line and returns it (cycles).
    string read(){
        if(pos > this->height()){
            this->restart();
            return FILE_END;
        }
        
        string line;
        for(size_t i = 0; i < this->pos; i++)
            getline(self, line);
        pos += 1;

        return line;
    }

public:
    
    /*A file class with his read and write oprations and much more! :D*/
    File(string path): path(path){
        this->is_open = this->open(mode::input | mode::output);
        if(!is_open)
            cerr << "Cannot open the input file: (" << this->path << ")";
    }

    bool open(const char open_mode){
        if(open_mode == mode::input)
            self.open(this->path.c_str(), ios::in);
        else if(open_mode == mode::output)
            self.open(this->path.c_str(), ios::app);
        else if(open_mode == mode::input | mode::output)
            self.open(this->path.c_str(), ios::in | ios::app);
        return self.is_open();
    }

    // Returns the size of the file (see File::height)
    size_t size(){
        cerr << "[DEV ERROR] File size not implemented yet. :/";
    }

    // Returns the amount of lines in the file (see File::size)
    size_t height(){
        string line;
        size_t i = 0;
        while(getline(self, line)) i++;
        return i;
    }

    /* Returns the extention of the file (text after the dot).
    example.txt -> txt */
    string extention(){
        int ext_index = this->path.rfind('.');
        if(ext_index != string::npos){
            string ext;
            for(size_t i = ext_index + 1; i < path.size(); i++)
                ext += path[i];
            return ext;
        }
        return "";
    }

    /* Returns the name of the file.
    ex/samples.txt -> samples */
    string name(){
        int slash_i = this->path.rfind("/");
        int dot_i = this->path.rfind(".");
        
        int start = (slash_i != string::npos) ? slash_i + 1 : 0;
        int end = (dot_i != string::npos) ? dot_i : path.size();
        string name;
        for(size_t i = start; i < end; i++)
            name += path[i];
        return name;
    }

    // Restart the position of the line.
    void restart(){
        this->pos = 1;
    }

    // Reads a line in a buffer (returns a state).
    bool read(string& buffer){
        string line = this->read();
        if(line != FILE_END){
            buffer = line;
            return true;
        }
        return false;
    }

    // Push back all the file lines in a vector.
    void read(vector<string>& lines){
        for(string line; this->read(line);)
            lines.push_back(line);
    }

    // Reads a line and concatenates it to a string.
    friend string& operator>>(File& input, string& output){
        string line;
        input.read(line);
        output += line;
        return output;
    }

    // Reads a line and push backs it to a vector.
    friend vector<string>& operator>>(File& input, vector<string>& output){
        string line;
        input.read(line);
        output.push_back(line);
        return output;
    }

    void write(const string& input = "\n"){
        self << input;
    }

    void write(vector<string>& input){
        for(string line : input)
            self << line << '\n';
    }

    friend File& operator<<(File& output, string& input){
        output.write(input);
        return output;
    }

    friend File& operator<<(File& output, vector<string>& input){
        output.write(input);
        return output;
    }
};

#define print(vect) for(size_t i = 0; i < vect.size(); i++){cout << vect[i] << '\n';}

int main(int argc, char* argv[]){
    
    // TODO: fix the open and close file operations.
    // Cannot read or write because the file opens in the constructor.

    return 0;
}