/*
 * fastq_io_test.cpp
 *
 *   Copyright (c) 2013, Shuji Suzuki
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
#include "../src/fastq_io.hpp"

using namespace std;

TEST(FastqIoTest, ReadRecode) {
	ifstream is("./test/test_dna.fq");
	ASSERT_TRUE(is);
	string header;
	string sequence;
	string quality;
	int ret = 0;
	ret = fastq_io::ReadRecode(is, header, sequence, quality);
	EXPECT_EQ(0, ret);
	EXPECT_EQ("I354_1_FC30M2LAAXX:6:1:3:511/2", header);
	EXPECT_EQ(
			"TATTGCTGTACCATACGGATNNGCTNTTTGTCCGATTGATACGAAAAGACATATTGATGCACAAACATCACACAA",
			sequence);
	EXPECT_EQ(
			"hhhhhhhhhhhhdhhhhhhh;;h\\h;ehhchdghghhhWha[aRUhbZh[__Yfh_Ve[PWOPQ[E^RPQRKJFS",
			quality);

	ret = fastq_io::ReadRecode(is, header, sequence, quality);
	EXPECT_EQ(0, ret);
	EXPECT_EQ("I354_1_FC30M2LAAXX:6:1:3:183/2", header);
	EXPECT_EQ(
			"GGCAAAGGCCATCAAGGCGGNNTTCCCGTGCCGCAAGGTGGGCATGGCAGTGCTCGGGCTGGAGGTAGCCCACGC",
			sequence);
	EXPECT_EQ(
			"hhhhhhhhhhhhFhhh\\b\\c;;^hKXPbW]WOWTWV\\fDJ`MOUTDVGNMGIGO<KHQ@PM?=MI@=I<CC=<D@",
			quality);

	ret = fastq_io::ReadRecode(is, header, sequence, quality);
	EXPECT_EQ(0, ret);
	EXPECT_EQ("I354_1_FC30M2LAAXX:6:1:4:1335/2", header);
	EXPECT_EQ(
			"GGTGTTCATCACCCTATGGANNGGGGGCGACAAGGCCACCGTCACCGTACAGCAGAACTTCCGTTCGGGTAAAAT",
			sequence);
	EXPECT_EQ(
			"hhhhhhhhhchhJhhhhhhh;;c\\d_hbahUehhfeP]SYaRT[PPgK\\OVOBIQTOMQGIKNIFGHPH@MQGQH",
			quality);

	ret = fastq_io::ReadRecode(is, header, sequence, quality);
	EXPECT_EQ(0, ret);
	EXPECT_EQ("I354_1_FC30M2LAAXX:6:1:4:1650/2", header);
	EXPECT_EQ(
			"GTGGCCGATGAGGAGATGCCCNGCGGGCCCGGCCAGGCCGGGGAAACAGTCCTCGTCGGCGGCTCGGGGGGGGGC",
			sequence);
	EXPECT_EQ(
			"hhhhhhhDAhhhUhchQIWA>;>E\\TIEULGKNL@OJSAZIWJJB@BDDFBEDGMCED<?I>@=@=G>AFF@=<A",
			quality);

	ret = fastq_io::ReadRecode(is, header, sequence, quality);
	EXPECT_NE(0, ret);
	is.close();
}

TEST(FastqIoTest, WriteRecode) {
	string filename = "./FastqIoTestWriteRecodefile.fa";
	ofstream os(filename.c_str());
	ASSERT_TRUE(os);
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
		int ret = fastq_io::WriteRecode(os, headers[i], sequences[i],
				qualities[i]);
		EXPECT_EQ(0, ret);
	}

	os.close();
	ifstream is(filename.c_str());
	ASSERT_TRUE(is);
	for (size_t i = 0; i < headers.size(); ++i) {
		string header;
		string sequence;
		string quality;
		int ret = fastq_io::ReadRecode(is, header, sequence, quality);
		EXPECT_EQ(0, ret);
		EXPECT_EQ(headers[i], header);
		EXPECT_EQ(sequences[i], sequence);
		EXPECT_EQ(qualities[i], quality);
	}
}

