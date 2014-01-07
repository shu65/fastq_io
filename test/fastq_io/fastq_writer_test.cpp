/*
 * fastq_writer_test.cpp
 *
 *   Copyright (c) 2014, Shuji Suzuki
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1. Redistributions of source code must retain the above Copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above Copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. Neither the name of the authors nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include "../../src/fastq_io.h"

using namespace std;

TEST(FastqWriterTest, Write) {
	string filename = "./FastqIoTestWriteRecodefile.fa";
	fastq_io::FastqWriter writer;
	writer.Open(filename.c_str());
	ASSERT_TRUE(writer);
	vector<string> headers(2);
	vector<string> sequences(2);
	vector<string> qualities(2);
	headers[0] = "I354_1_FC30M2LAAXX:6:1:3:511/2";
	sequences[0] =
			"TATTGCTGTACCATACGGATNNGCTNTTTGTCCGATTGATACGAAAAGACATATTGATGCACAAACATCACACAA";
	qualities[0] =
			"hhhhhhhhhhhhdhhhhhhh;;h\\h;ehhchdghghhhWha[aRUhbZh[__Yfh_Ve[PWOPQ[E^RPQRKJFS";
	headers[1] = "I354_1_FC30M2LAAXX:6:1:3:183/2";
	sequences[1] =
			"GGCAAAGGCCATCAAGGCGGNNTTCCCGTGCCGCAAGGTGGGCATGGCAGTGCTCGGGCTGGAGGTAGCCCACGC";
	qualities[1] =
			"hhhhhhhhhhhhFhhh\\b\\c;;^hKXPbW]WOWTWV\\fDJ`MOUTDVGNMGIGO<KHQ@PM?=MI@=I<CC=<D@";

	for (size_t i = 0; i < headers.size(); ++i) {
		int ret = writer.Write(headers[i], sequences[i], qualities[i]);
		EXPECT_EQ(0, ret);
	}

	writer.Close();
	fastq_io::FastqReader reader;
	reader.Open(filename.c_str());
	ASSERT_TRUE(reader);
	for (size_t i = 0; i < headers.size(); ++i) {
		string header;
		string sequence;
		string quality;
		int ret = reader.Read(header, sequence, quality);
		EXPECT_EQ(0, ret);
		EXPECT_EQ(headers[i], header);
		EXPECT_EQ(sequences[i], sequence);
		EXPECT_EQ(qualities[i], quality);
	}
	reader.Close();
}

