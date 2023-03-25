/*****************************/
// Author : Pranav Shankar Srinivasam
// Email :spranav1911@gmail.com
// References: Geeks For Geeks, LinuxHint, Tutotials.cpp, CodeSpeedy, Stackoverflow

/*****************************/

#ifndef MULTITHREADIN_H
#define MULTITHREADING_H

#include<fstream>
#include<string>
#include <thread>
#include <mutex>
#include<bits/stdc++.h>
#include<condition_variable>
#include<cstring>
#include<stdio.h>
#include <iostream>
#include<limits>

using namespace std;

namespace ReadWriteFile{

        class CacheClass {
                
                private:
                        unordered_map<string, string> cachemem_;
                public: 
                        void cachemem_fill(string index_, string val_);
                        unordered_map<string, string> cachemem_map();
        };
        

        class Task{
                private:
                        vector<string> read_file_;
                        vector<string> write_file_;
                        string read_;
                        string write_;
                        int cache_size_;
                        string items_file_;
                public:
                        
                        vector<string> temp_;
                        mutex mtx_;
                        vector<thread> reader_thread_;
                        vector<thread> writer_thread_;
                        unordered_map<string, vector<string>> read_file_index_;
                       
                        unordered_map<string, unordered_map<string,string>> write_file_index_;
                        ifstream myfile_handler1_;
                        ifstream myfile_handler2_;
                        ifstream myfile_handler3_;
                        string mylineread_;
                        string mylinewrite_;

                        Task(int a_, string r_, string w_, string i_);
                        Task();

                        void set_read(string r_);
                        void set_write(string w_);
                        void set_items(string i_);
                        void set_cache(int c_);
                        
                        int read_file_size();
                        void file_read(int c_size_, string input1_, string input2_, string input3_);
                        fstream& go_to_line(fstream& file_, unsigned int num_);
                        void display_read_file(unordered_map<string, vector<string>> read_file_index_);
                        vector<string> split_string(string fullstring_);
                        void reader_function(string file_);
                        void  writer_function(string file_);
                        void write_to_items(string s_);
                        void read_from_items(string items_file_, CacheClass& cclass_obj_);
                        bool items_file_bound(string line_np_);
                        int check_no_of_lines(string item_file_);
                        vector<string> read_file_vector();
                        vector<string> write_file_vector();
                        unordered_map<string, unordered_map<string,string>> write_file_index_data();
                        unordered_map<string, vector<string>> read_file_index_data();
                        int cache_length();

        };
        
        void read_write_file(Task& t_, int a_, string r_, string w_, string i_);
       
        

}

#endif