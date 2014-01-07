/*
 * fastq_reader_test.cpp
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
#include "../../src/fastq_io/fastq_reader.h"

using namespace std;

TEST(FastqIoTest, ReadRecode) {
	fastq_io::FastqReader reader;
	reader.Open("./test/test_dna.fq");
	ASSERT_TRUE(reader);
	string header;
	string sequence;
	string quality;
	int ret = 0;
	ret = reader.Read(header, sequence, quality);
	EXPECT_EQ(0, ret);
	EXPECT_EQ("I354_1_FC30M2LAAXX:6:1:3:511/2", header);
	EXPECT_EQ(
			"TATTGCTGTACCATACGGATNNGCTNTTTGTCCGATTGATACGAAAAGACATATTGATGCACAAACATCACACAA",
			sequence);
	EXPECT_EQ(
			"hhhhhhhhhhhhdhhhhhhh;;h\\h;ehhchdghghhhWha[aRUhbZh[__Yfh_Ve[PWOPQ[E^RPQRKJFS",
			quality);

	ret = reader.Read(header, sequence, quality);
	EXPECT_EQ(0, ret);
	EXPECT_EQ("I354_1_FC30M2LAAXX:6:1:3:183/2", header);
	EXPECT_EQ(
			"GGCAAAGGCCATCAAGGCGGNNTTCCCGTGCCGCAAGGTGGGCATGGCAGTGCTCGGGCTGGAGGTAGCCCACGC",
			sequence);
	EXPECT_EQ(
			"hhhhhhhhhhhhFhhh\\b\\c;;^hKXPbW]WOWTWV\\fDJ`MOUTDVGNMGIGO<KHQ@PM?=MI@=I<CC=<D@",
			quality);

	ret = reader.Read(header, sequence, quality);
	EXPECT_EQ(0, ret);
	EXPECT_EQ("I354_1_FC30M2LAAXX:6:1:4:1335/2", header);
	EXPECT_EQ(
			"GGTGTTCATCACCCTATGGANNGGGGGCGACAAGGCCACCGTCACCGTACAGCAGAACTTCCGTTCGGGTAAAAT",
			sequence);
	EXPECT_EQ(
			"hhhhhhhhhchhJhhhhhhh;;c\\d_hbahUehhfeP]SYaRT[PPgK\\OVOBIQTOMQGIKNIFGHPH@MQGQH",
			quality);

	ret = reader.Read(header, sequence, quality);
	EXPECT_EQ(0, ret);
	EXPECT_EQ("I354_1_FC30M2LAAXX:6:1:4:1650/2", header);
	EXPECT_EQ(
			"GTGGCCGATGAGGAGATGCCCNGCGGGCCCGGCCAGGCCGGGGAAACAGTCCTCGTCGGCGGCTCGGGGGGGGGC",
			sequence);
	EXPECT_EQ(
			"hhhhhhhDAhhhUhchQIWA>;>E\\TIEULGKNL@OJSAZIWJJB@BDDFBEDGMCED<?I>@=@=G>AFF@=<A",
			quality);

	ret = reader.Read(header, sequence, quality);
	EXPECT_NE(0, ret);
	reader.Close();
}

