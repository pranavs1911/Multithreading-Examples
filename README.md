# Multithreading-Examples
Contains my experimental work in multithreading using C++. 

I have written a few files in C++ that perform the following:

There are a few Reader.txt files and Writer.txt files. Each Reader.txt file outputs a Reader.out.txt file.
Multiple threads read the data in each reader file and store it in an unordered map.
Similar case for each writer's file.

Every index in Reader.txt is used to read data from an index in items_file.txt. The initial data is stored in a cache object.
The Reader.out.txt file outputs data from the Reader.txt file after reading a particular value at an index in the items_file.txt.

Once the Reader.out.txt file observes multiple occurrences of the same index in the Reader.out.txt file (say, index 1 occurs two times in the Reader1.txt file. The second time index 1 occurs, the data is now output as cache data in Reader.out.txt instead of disc data). 

The Writer.txt file has an 'index' and a 'value' corresponding to that particular index. Each writer file writes to the item file the value at that particular index.
Say, Writer1.txt has '3 45' in line 3. When a thread is passed to read values from Writer1.txt, it writes 45 in the third line of items_file.txt.





