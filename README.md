fastq_io
=======

Read bio sequence from fastq file

Build and Run Test
----------
    cd fastq_io/
    g++ src/fastq_io/fastq_*.cpp test/fastq_io/fastq_*.cpp -lgtest -lgtest_main -lpthread -o fastq_io_test
    ./fastq_io_test
