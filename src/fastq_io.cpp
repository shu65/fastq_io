/*
 * fasta_io.cpp
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

#include "fastq_io.hpp"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int fastq_io::ReadRecode(std::istream &istream, std::string &header,
		std::string &sequence, std::string &quality) {
	header.clear();
	sequence.clear();
	quality.clear();
	string line;
	size_t position;
	bool bad_record = false;
	if (!istream) {
		return 1;
	}
	while (!istream.eof() && (line.length() == 0 || line.at(0) != '@')) {
		std::getline(istream, line);
	}
	if (istream.eof()) {
		return 1;
	}

	if (line.at(line.length() - 1) == '\r') {
		line = line.substr(0, line.length() - 1);
	}
	position = line.find_first_not_of("@");
	if (position != std::string::npos) {
		header = line.substr(position);
	}

	// set sequence
	std::getline(istream, line);
	if (line.length() != 0) {
		std::string::iterator left = std::find_if(line.begin(), line.end(),
				std::not1(std::ptr_fun<int, int>(isspace)));
		std::string::reverse_iterator right = std::find_if(line.rbegin(),
				line.rend(), std::not1(std::ptr_fun<int, int>(isspace)));
		line = std::string(left, right.base());
		sequence = line;
	}
	if (sequence.empty()) {
		bad_record = true;
	}

	std::getline(istream, line);
	position = line.find_first_not_of("+");
	if (position == std::string::npos) {
		bad_record = true;
	}

	// set quality
	std::getline(istream, line);
	if (line.length() != 0) {
		std::string::iterator left = std::find_if(line.begin(), line.end(),
				std::not1(std::ptr_fun<int, int>(isspace)));
		std::string::reverse_iterator right = std::find_if(line.rbegin(),
				line.rend(), std::not1(std::ptr_fun<int, int>(isspace)));
		line = std::string(left, right.base());
		quality = line;
	}
	if (quality.empty() || sequence.length() != quality.length()) {
		bad_record = true;
	}
	return bad_record ? 1 : 0;
}

int fastq_io::WriteRecode(std::ostream &ostream, const std::string &header,
		const std::string &sequence, std::string &quality) {
	if (!ostream || sequence.length() != quality.length()) {
		return 1;
	}

	ostream << "@" << header << endl;
	ostream << sequence << endl;
	ostream << "+" << header << endl;
	ostream << quality << endl;
	return 0;
}

