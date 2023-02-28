#define EX_OK 0       /* successful termination */
#define EX_FAILED 111 /* program failed */

#include "parser.h"
#include "const_variables.h"
#include "compressor.h"
#include "decompressor.h"
#include "iostream"

int main(int argc, char** argv) {
    Parser pr = Parser(argc, argv);
    try {
        pr.Parse();
    } catch (const Parser::WrongFormatException& exception) {
        std::cout << WRONG_FORMAT << std::endl;
        return EX_FAILED;
    }
    if (pr.GetMode() == Parser::Help) {
        std::cout << HELP_TEXT << std::endl;
        return EX_OK;
    }
    if (pr.GetMode() == Parser::Compress) {
        try {
            Compressor c = Compressor(pr.GetFileNames(), pr.GetArchiveName());
            c.CompressFiles();
        } catch (const FileReader::FileOpenException& e) {
            std::cout << CANNOT_OPEN_INPUT_FILE << std::endl;
            return EX_FAILED;
        } catch (const FileWriter::FileOpenException& e) {
            std::cout << CANNOT_OPEN_OUTPUT_FILE << std::endl;
            return EX_FAILED;
        } catch (...) {
            std::cout << SOMETHING_WENT_WRONG << std::endl;
            return EX_FAILED;
        }
        std::string files;
        std::vector<std::string> file_names = pr.GetFileNames();
        std::cout << "Successfully compressed files: \n";
        for (size_t i = 0; i < file_names.size(); ++i) {
            std::cout << file_names[i] << "\n";
        }
        std::cout << "Archive: " << pr.GetArchiveName();
        return EX_OK;
    } else {
        std::vector<std::string> file_names;
        try {
            Decompressor dc = Decompressor(pr.GetArchiveName());
            file_names = dc.DecompressArchive();
        } catch (const FileReader::FileOpenException& e) {
            std::cout << CANNOT_OPEN_INPUT_FILE << std::endl;
            return EX_FAILED;
        } catch (const FileWriter::FileOpenException& e) {
            std::cout << CANNOT_OPEN_OUTPUT_FILE << std::endl;
            return EX_FAILED;
        } catch (const Decompressor::BadArchive& e) {
            std::cout << BAD_ARCHIVE << std::endl;
            return EX_FAILED;
        } catch (...) {
            std::cout << SOMETHING_WENT_WRONG << std::endl;
            return EX_FAILED;
        }
        std::cout << "Successfully decompressed archive ";
        std::cout << pr.GetArchiveName() << "\n";
        std::cout << "Files: \n";
        std::string files;
        for (size_t i = 0; i < file_names.size(); ++i) {
            std::cout << file_names[i] << "\n";
        }
        return EX_OK;
    }
}
