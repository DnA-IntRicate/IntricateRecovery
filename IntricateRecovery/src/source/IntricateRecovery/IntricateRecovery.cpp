#include <irpch.hpp>

static const char* jpg_signature = "\xFF\xD8\xFF\xE0";  // JPEG signature
static const char* png_signature = "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"; // PNG signature
static const char* gif_signature = "GIF87a"; // GIF 87a
static const char* bmp_signature = "BM"; // BMP

static const char* pdf_signature = "%PDF"; // PDF

static const char* docx_signature = "\x50\x4B\x03\x04"; // Microsoft Word (DOCX)
static const char* xlsx_signature = "\x50\x4B\x03\x04"; // Microsoft Excel (XLSX)
static const char* pptx_signature = "\x50\x4B\x03\x04"; // Microsoft PowerPoint (PPTX)
static const char* doc_signature = "\xD0\xCF\x11\xE0\xA1\xB1\x1A\xE1"; // Microsoft Word (DOC)

static const char* mp3_signature = "\x49\x44\x33"; // MP3
static const char* wav_signature = "\x52\x49\x46\x46"; // WAV (RIFF header)

static const char* avi_signature = "\x52\x49\x46\x46"; // AVI (RIFF header)
static const char* mp4_signature = "ftyp3"; // MP4

static const char* zip_signature = "\x50\x4B\x03\x04"; // ZIP

constexpr static int BUFFER_SIZE = 1024 * 1024 * 50;
constexpr static int MAX_LENGTH_FILENAME = 50;

struct FileType
{
    FileType(const char* ext, const char* headSig, const char* footSig)
        : Extension(ext), HeaderSignature(headSig), FooterSignature(footSig) { };
    FileType() = default;

    const char* Extension = ".";
    const char* HeaderSignature = "\x00\x00\x00\x00";
    const char* FooterSignature = "\x00\x00\x00\x00";
};

static const FileType g_Jpeg = { "jpg", "\xFF\xD8\xFF\xE0", "\xFF\xD9" };
static const FileType g_Png = { "png", "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", "\x00\x00\x00\x00" };


static void recoverFiles(HANDLE disk, const std::vector<FileType>& fileTypes)
{
    char* buffer = new char[BUFFER_SIZE];
    DWORD bytesRead;

    int fileCounter = 0;
    char* filename = new char[MAX_LENGTH_FILENAME];

    while (ReadFile(disk, buffer, BUFFER_SIZE, &bytesRead, nullptr) && (bytesRead > 0))
    {
        for (auto& type : fileTypes)
        {
            size_t signatureSize = strlen(type.HeaderSignature);
            int i = 0;
            while (i < bytesRead - signatureSize)
            {
                if (memcmp(buffer + i, type.HeaderSignature, signatureSize) == 0)
                {
                    snprintf(filename, MAX_LENGTH_FILENAME, "recovered%d.%s", fileCounter, type.Extension);

                    // Handle filename collisions
                    while (GetFileAttributesA(filename) != INVALID_FILE_ATTRIBUTES)
                        snprintf(filename, MAX_LENGTH_FILENAME, "recovered%d.%s", ++fileCounter, type.Extension);

                    // Create the full path for the output file
                    char outputPath[MAX_PATH];
                    GetCurrentDirectoryA(MAX_PATH, outputPath);
                    strcat(outputPath, "\\");
                    strcat(outputPath, filename);

                    // Open the output file for writing
                    FILE* outFile = fopen(outputPath, "wb");
                    if (outFile)
                    {
                        // Write the data from the start of the buffer up to the signature
                        fwrite(buffer + i, 1, signatureSize, outFile);

                        // Continue writing until the "end of file" marker is detected
                        int bytesWritten = signatureSize;
                        while (bytesWritten < bytesRead - i) 
                        {
                            if (memcmp(buffer + i + bytesWritten, type.FooterSignature, 4) == 0)
                                break;

                            fwrite(buffer + i + bytesWritten, 1, 1, outFile);
                            bytesWritten++;
                        }

                        fclose(outFile);
                        printf("Recovered: %s\n", outputPath);
                    }
                }

                i++;
            }
        }
    }
}

int main(int argc, char** argv) 
{
    std::cout << "Enter drive letter/path for recovery: "; 

    std::string driveLetter;
    std::cin >> driveLetter;

    std::stringstream drivePath;
    drivePath << "\\\\.\\" << driveLetter << ":";

    HANDLE disk = CreateFileA(drivePath.str().c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
        OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL);

    if (disk != INVALID_HANDLE_VALUE) 
    {
        std::cout << "Drive opened..\n" << std::endl;

        std::vector<FileType> fileTypes =
        {
        //    { png_signature, "png" },
        //    { jpg_signature, "jpg" },
        //    { gif_signature, "gif" },
        //    { bmp_signature, "bmp" },
        //    { pdf_signature, "pdf" }
            g_Jpeg,
            g_Png
        };

        recoverFiles(disk, fileTypes);
        CloseHandle(disk);
    }
    else 
    {
        std::cerr << "Error opening drive " << driveLetter <<  ": " << GetLastError() << std::endl;
        std::cin.get();
    }

    std::cout << "DONE" << std::endl;

    std::cin.get();
    return 0;
}
