#include <iostream>

#pragma pack(push, 1)
struct BMPHeader {
    char signature[2];       // "BM"
    uint32_t fileSize;       // File size in bytes
    uint32_t reserved;       // Reserved (unused)
    uint32_t pixelArrayOffset; // Offset to the pixel data
    uint32_t dibHeaderSize;  // DIB header size
    int32_t width;           // Image width
    int32_t height;          // Image height
    uint16_t planes;         // Number of color planes (must be 1)
    uint16_t bitsPerPixel;   // Bits per pixel (should be 24 for RGB)
};
#pragma pack(pop)

// comment - spored men parametrite, koito ste dali ne sa dostatuchni (davashe mi vse corrupt-nat file) tova sa nujnite parametri ot header-a, koito chata mi dade i bachkat za razlika ot samo vashite, moje i az da sum baven ama ne boli da gi ima kato raboti sega ;D