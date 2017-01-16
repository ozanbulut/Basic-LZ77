# Basic-LZ77
  This is the basic implementation of the LZ77 algorithm(https://en.wikipedia.org/wiki/LZ77_and_LZ78). LZ77 is the basis for the algorithm called DEFLATE(zip uses this algorithm, for details see: https://en.wikipedia.org/wiki/DEFLATE). Only difference is that DEFLATE takes the output of the LZ77 then constructs huffman encoding.
  
## Feature Work
  * Turn this into DEFLATE by adding huffman encoding.
  * Instead of brute force approach use suffix array or suffix tree.
