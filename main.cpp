#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<string> file_content;

class File{
    fstream file;
    file_content content;
    size_t pos = 1;

    void readlines(){
        file.open(path, ios::in);
        if(file.is_open())
            for(string line; getline(file, line);)
                content.push_back(line);
        file.close();
    }
public:
    string path;

    /* Checks if a file exists
    NOTE: Does not support directories. */
    static bool exists(string path){
        fstream tmp;
        tmp.open(path, ios::in);
        if(!tmp.is_open())
            return false;
        tmp.close();
        return true;
    }

    bool exists() const {
        return File::exists(path);
    }

    /* Creates a file if it doesn't exists */
    static void create(string path){
        if(exists(path))
            return;
        fstream tmp;
        tmp.open(path, ios::out);
        tmp.close();
    }

    /* Returns the name of the file without the entire path
    my\\example.txt -> example */
    string name() const {
        int find = path.rfind('/');
        int start = (find != string::npos)? find + 1 : 0;

        find = path.rfind('.');
        int end = (find != string::npos)? find : path.size();

        return path.substr(start, end - start);
    }

    /* Returns the extention of the file
    my\\example.txt -> txt */
    string exten() const {
        int find = path.rfind('.');
        if(find == string::npos)
            return "";
        return path.substr(find + 1);
    }

    File(string path): path(path){
        if(!exists())
            create(path);
        file.open(path, ios::in | ios::app);
        if(!file.is_open())
            cerr << "[ERROR] Cannot open the file: " << name() + "." + exten() << '\n' << "Whole path: " << path;
        this->readlines();
    }

    string& operator[](size_t index){
        this->readlines();
        return this->content[index];
    }

    friend string& operator>>(File& input, string& output){
        input.file.open(input.path, ios::in);
        if(input.file.is_open())
            getline(input.file, output);
        return output;
    }

    friend File& operator<<(File& output, string& input){
        output.file.open(output.path, ios::app);
        output.file << input;
        return output;
    }
};

#define PRINT_VECTOR(vect) for(auto i : vect){ cout << i << endl; }

int main(){

    File file("data.txt");

    string a;
    cout << a;

    return 0;
}