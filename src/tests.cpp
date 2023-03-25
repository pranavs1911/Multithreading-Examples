/*****************************/
// Author : Pranav Shankar Srinivasam
// Email :spranav1911@gmail.com
// References: Geeks For Geeks, LinuxHint, Tutotials.cpp, CodeSpeedy, Stackoverflow

/*****************************/

#include "../include/multithreading.h"
#include <gtest/gtest.h>

using namespace ReadWriteFile;


class CheckReadWriteFile : public testing::Test{

    public:
        void SetUp() override;
        void TearDown() override;

       

        string  s2, s3, s4;
        int s1;
    protected:
        Task t;
};

void CheckReadWriteFile::SetUp(){
    t.set_read("read_file.txt");
    t.set_write("write_file.txt");
    t.set_items("items_file.txt");
    t.set_cache(3);

    read_write_file(t, t.cache_length(), "reader_file.txt", "writer_file.txt", "items_file.txt");    
 
}

void CheckReadWriteFile::TearDown(){
}

TEST_F(CheckReadWriteFile, ItemsFileBound){
    //Checks if item file bound is valid.
    bool b = true;
    for (auto itm: t.read_file_vector()){
        vector<string> index = t.read_file_index_[itm];
        for (auto line:index){
           b =  t.items_file_bound( line);
           if (b == false)
                break;
        }
        if (b == false) break;
    }
    ASSERT_EQ(b, true);

}

TEST_F(CheckReadWriteFile, CacheMemCheck){
    //tests the read_from_items and checks if it is correct.
    CacheClass cobj;
    t.read_from_items("NORMAL", cobj);
  
    ASSERT_EQ(cobj.cachemem_map().size(), t.cache_length());

}


int main(int argc, char** argv){

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}