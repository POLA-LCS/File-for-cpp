#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<string> file_content;

class File{
    const string END = "" + (char)EOF;
    fstream file;
    size_t pos = 1;
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
    }

    size_t len(){
        size_t i = 0;
        string line;
        while(getline(file, line))
            i++;
        
        return i;
    }

    string read(){
        if(pos > len()){
            pos = 1;
            return File::END;
        }
        string line;
        for(size_t i; i < pos; i++)
            getline(file, line);
            
        pos += 1;
        return line;
    }

    void write(string line, const char end = '\n'){
        file << line + end;
    }
};

#define PRINT_VECTOR(vect) for(auto i : vect){ cout << i << endl; }

int main(){

    File file("data.txt");

    cout << file.read() << '\n';
    cout << file.read() << '\n';


    return 0;
}