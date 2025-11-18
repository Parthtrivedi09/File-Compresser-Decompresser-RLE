1. create the executable files for all 3 - main.cpp , decompress.cpp , merge_chunks.cpp using 
    g++ -std=c++17 main.cpp file_utils.cpp -o compress.exe
    g++ -std=c++17 decompress.cpp file_utils.cpp -o decompress.exe
    g++ -std=c++17 merge_chunks.cpp -o merge.exe


2. so now we have 3 executable files which we'll use to demonstrate our project
   
3. STEP 3: Run the whole pipeline
   1️⃣ Run compression   //will compress the file using rle so that it cna easiely be stored and sending cost is small
   2️⃣ Run decompression //at receivers end which will decompress all the files and make it ready for further merging
   3️⃣ Merge decompressed chunks //now we'll merge all these decompressed files to again get the final output file at receivers end



//main moto of the project
“In real-world systems, when a large file needs to be transferred, it is often compressed and split into chunks so that the transfer is faster and more reliable.

In my project, I implemented the same idea:

First, the file is split into chunks.

Each chunk is compressed using RLE.

These compressed chunks can be sent to another system or stored.

On the receiver side, they simply:

Decompress each chunk independently

Merge the chunks back in the correct order

And reconstruct the original file exactly.

So the project demonstrates a complete sender–receiver compression system with multithreading and chunk-based file processing.”