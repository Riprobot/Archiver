#pragma once

#include <climits>
#include <string_view>

const std::string_view HELP_TEXT = "help text";
const std::string_view WRONG_FORMAT = "wrong format";
const std::string_view SOMETHING_WENT_WRONG = "something went wrong";
const std::string_view CANNOT_OPEN_INPUT_FILE = "cannot open input file";
const std::string_view CANNOT_OPEN_OUTPUT_FILE = "cannot open output file";
const std::string_view BAD_ARCHIVE = "bad archive";
const int FILENAME_END = 256;
const int ONE_MORE_FILE = 257;
const int ARCHIVE_END = 258;
const int BIT_NUMBER = 9;
const int BITS_IN_BYTE = __CHAR_BIT__;
const int ALF_LEN = ((1 << BITS_IN_BYTE) + 3);
