/*****************************/
// Author : Pranav Shankar Srinivasam
// Email :spranav1911@gmail.com
// References: Geeks For Geeks, LinuxHint, Tutotials.cpp, CodeSpeedy, Stackoverflow

/*****************************/
#include "../include/multithreading.h"
#include <iostream>

namespace ReadWriteFile{
    void CacheClass::cachemem_fill(string index, string val){
        //storing cachemem_ map;
        cachemem_[index] = val;
    }

    unordered_map<string, string> CacheClass::cachemem_map(){
        //returning cachemem_map;
        return cachemem_;
    }
                
    void Task::file_read(int c_size, string input1, string input2, string input3){
        /*
        input1: reader_file
        input2: writer_file
        input3: items_file
        */
        cache_size_ = c_size;
        items_file_ = input3;
        myfile_handler1_.open(input1);
        myfile_handler2_.open(input2);
        if (myfile_handler1_.is_open()){
            //read the read_file
            while(getline(myfile_handler1_, mylineread_)){
                temp_.push_back(mylineread_);
            }
        }
        myfile_handler1_.close();
        temp_ = {"Reader1.txt", "Reader2.txt", "Reader3.txt"};
        for (int i = 0; i < temp_.size(); i++){
            ifstream file(temp_[i]);
            if (file.is_open())
                {
                
                    read_file_.push_back(temp_[i]);
                    file.close();
                }
            else cout << "Check" << endl;
        }
        temp_ = {};

        if (myfile_handler2_.is_open()){
            //read the writer_file
            while(getline(myfile_handler2_, mylineread_)){
                temp_.push_back(mylineread_);
            }
        }
        myfile_handler2_.close();
        temp_ = {"Writer1.txt", "Writer2.txt", "Writer3.txt"};
        for (auto itm: temp_){
            ifstream file(itm);
            if (file.is_open())
                {
                
                    write_file_.push_back(itm);
                    file.close();
                }
            else
                file.close();
        }

    
        return;
        

    }


    fstream& Task::go_to_line(fstream& file, unsigned int num){

        //Goes to a particular line in a file.
        file.seekg(std::ios::beg);
        for(int i=0; i < num - 1; ++i){
            file.ignore(numeric_limits<std::streamsize>::max(),'\n');
        }
        return file;
    }

    int Task::check_no_of_lines(string item_file){
        //Checks the number of lines in a items file
        ifstream file(item_file);
        string line;
        int count = 0;
        if (file.is_open()){
            while(file.peek() != EOF){
                getline(file, line);
                count++;
            }
            file.close();
        }
        return count;

    }


    
    vector<string> Task::split_string(string fullString){
        //Splits the string 

        fstream my_file;
    
        stringstream ss(fullString);
        vector<string> sv;
        string word;
        while (ss>> word){
            sv.push_back(word); 
        }
        return sv;
            
    }

    
    bool Task::items_file_bound(string line_no){
        //checks the bound of the items_file.
        
        int item_lines = check_no_of_lines(items_file_);
        if (stoi(line_no) > item_lines)
            return false;

        return true;

    }


    void Task::reader_function(string file){
    
        //Reader function with file as the name of the string file name.
        //Storing all the values in a vector for the reader file
    
        lock_guard<mutex> lg(mtx_);
        string mylineread2;
        vector<string> Read;
        myfile_handler3_.open(file);
        if (myfile_handler3_.is_open()){
            
            //read the item index from the items file
            while (getline(myfile_handler3_, mylineread2)){
                if (mylineread2.compare(""))
                    Read.push_back(mylineread2);
            }
            read_file_index_[file] = Read;
            myfile_handler3_.close();

        }
        
        return;
    
    }
    
    Task::Task(int c, string a, string b, string w){
        //taking inputs for class task.
        read_ = a;
        write_ = b;
        cache_size_ = c;
        items_file_ = w;

    }

    Task::Task(){};

    void Task::writer_function(string file){
        
        //Writer function with file as the name of the string file name.
        //Storing all the values in an unordered_map for the reader file
    
        lock_guard<mutex> lg(mtx_);
        
        myfile_handler3_.open(file);
        string mylineread3;

        if (myfile_handler3_.is_open()){
            unordered_map<string,string> index;
            //get the items from the write file
            while (getline(myfile_handler3_, mylineread3)){
                if (mylineread3.compare("")){
                    vector<string> write = split_string(mylineread3);
                    index[write[0]] = write[1];
                }
            }
            write_file_index_[file] = index;
            myfile_handler3_.close();
        }
        
        return;

    }

    
    void Task::write_to_items(string purpose){

        //takes the values from write file and uploads them in the items file.

        lock_guard<mutex> lock2(mtx_);
        fstream myFile_Handler5;

        myFile_Handler5.open(items_file_);
        for (auto w_i : write_file_)
        {
            if (myFile_Handler5.is_open())
                {

                //writing from write file to items file.
                unordered_map<string, string> key;
                key = write_file_index_[w_i];
                for (auto itm : key)
                    
                    { 
                        if (!purpose.compare("ITEMS_FILE")){
                            go_to_line(myFile_Handler5, stoi(itm.first));
                            myFile_Handler5 << itm.second<<endl;
                        }
                    
                    }
                
                } 
            myFile_Handler5.close();
        }

            
        return;
    }
    


    void Task::read_from_items(string purpose, CacheClass& cache_obj){
        //Reads the values from the read_file and uploads them in Reader.out.txt
        
        std::lock_guard<mutex> lock3(mtx_);
        fstream file_id;
        ofstream output_file;
        
        int cache_var = cache_size_;
        file_id.open(items_file_);
        int cache_index = 1, cache_s = cache_size_;
        bool written = false;
        for (auto itm : read_file_){
            output_file.open(itm.substr(0,7)+".out.txt");
            if (output_file.is_open())
                if (file_id.is_open())
                {

                    for (auto line_no : read_file_index_[itm]){
                        
                        string a;
                        go_to_line(file_id, stoi(line_no));
                        
                        if (items_file_bound(line_no)) 
                            {
                                file_id >> a;
                        
                                if (!purpose.compare("NORMAL"))
                                {
                                    if (cache_obj.cachemem_map().size() > 0)
                                        {
                                            for (auto it : cache_obj.cachemem_map()){
                                                if ((it.second == line_no) && (cache_s > 0)){
                                                    string reader_out = a;
                                                    output_file << reader_out<<" Cache"<<endl;
                                                    written = true;
                                                    cache_s --;
                                                    break;
                                                }
                                                if (cache_s == 0){
                                                    string reader_out = a;
                                                    output_file << reader_out<<" Disc"<<endl;
                                                    written = true;
                                                }
                                            }
                                            if (written != true && cache_s == 0){
                                                string reader_out = a;
                                                output_file << reader_out<<" Disc"<<endl;
                                            }

                                        }
                                    else{
                                        string reader_out = a;
                                        output_file << reader_out<<" Disc"<<endl;
                                    }
                                    
                                    
                                    if (cache_var > 0){
                                        cache_obj.cachemem_fill(to_string(cache_index), line_no);
                                        cache_var--;
                                        cache_index++;
                                    }
                                }
                            }
                        
                        go_to_line(file_id, 1);

                    }
                    output_file.close();
                    file_id.close();
                
                }   
        }
        
        return;
    }

    vector<string> Task::read_file_vector(){
        //returns read_file
        return read_file_;
    }

    vector<string> Task::write_file_vector(){
        //returns write_file
        return write_file_;
    }
    
    unordered_map<string, unordered_map<string,string>> Task:: write_file_index_data(){
        //returns write_file_index
        return write_file_index_;
    }

    unordered_map<string, vector<string>> Task::read_file_index_data(){
        //returns read_file_index
        return read_file_index_;
    }

    int Task::cache_length(){
        //returns cache_length
        return cache_size_;
    }

    void Task::set_read(string r){
        //sets the read file.
        read_ = r;
        return;
    }

    void Task::set_write(string w){
        //sets the write file
        write_ = w;
        return;
    }

    void Task::set_items(string i){
        //sets the items file.
        items_file_ = i;
        return;
    }

    void Task:: set_cache(int c){
        //sets the cache file.
        cache_size_ = c;
        return;
    }

    void read_write_file(Task& t, int csize, string r, string w, string items){

        //Passing threads to get data from each reader_file and writer file.
        fstream myfile_handler4;
        t.file_read(csize, r, w, items);
       
        CacheClass caclass;
        for (int i = 0; i < t.read_file_vector().size(); i++)
            {
                
                myfile_handler4.open(t.read_file_vector().at(i) + "", ios::in);
                if (!myfile_handler4.is_open()) continue;
                else 
                {
                    t.reader_thread_.push_back(std::thread(&Task::reader_function, &t,  t.read_file_vector().at(i)));
                    myfile_handler4.close();

                };
                myfile_handler4.close();  
            }

        for (int i = 0; i < t.reader_thread_.size(); i++)
            if (t.reader_thread_.at(i).joinable())
                t.reader_thread_.at(i).join();

        
        for (int i = 0; i < t.write_file_vector().size(); i++)
            {
                t.myfile_handler3_.open(t.write_file_vector().at(i), ios::in);
                if (!t.myfile_handler3_.is_open()) continue ;
                
                else
                {
                    t.writer_thread_.push_back(std::thread(&Task::writer_function, &t,  t.write_file_vector().at(i)));
                    t.myfile_handler3_.close();
                } 
                    
                t.myfile_handler3_.close();
            }
            

        for (int i = 0; i < t.writer_thread_.size(); i++)
            if (t.writer_thread_.at(i).joinable())
                t.writer_thread_.at(i).join();

        string n = "NORMAL";
        string i = "ITEMS_FILE";

        //Passing threads for writing to items_file.txt and Reader.out.txt
        std::thread t1(&Task::read_from_items, &t, n, std::ref(caclass));
        std::thread t2(&Task::write_to_items, &t, i);

    
        if (t1.joinable())
            t1.join();
           
        
        
        if (t2.joinable())
            t2.join();
            
        
        return;
    }
}




