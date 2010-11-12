// bdex_byteoutstreamraw.cpp                                          -*-C++-*-
#include <bdex_byteoutstreamraw.h>

#include <bdes_ident.h>
BDES_IDENT_RCSID(bdex_byteoutstreamraw_cpp,"$Id$ $CSID$")

#include <bsl_ostream.h>
#include <bsl_iomanip.h>

namespace BloombergLP {

// FREE OPERATORS

bsl::ostream& operator<<(bsl::ostream&                stream,
                         const bdex_ByteOutStreamRaw& object)
{
    const int   len  = object.d_streambuf.length();
    const char *data = object.d_streambuf.data();

    bsl::ios::fmtflags flags = stream.flags();
    stream << bsl::hex;
    for (int i = 0; i < len; i++) {
        if (0 < i && 0 != i % 8) {
            stream << ' ';
        }
        if (0 == i % 8) {  // print new line and address after 8 bytes
            stream << '\n' << bsl::setw(4) << bsl::setfill('0') << i << '\t';
        }

        char array[8];
        for (int j = 7; j >= 0; j--) {
            array[7-j] = '0' + ((data[i] >> j) & 0x01);
        }
        
        stream.write(array, sizeof array);
    }
    stream.flags(flags);  // reset stream format flags
    return stream;
}

}  // close namespace BloombergLP

// ---------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2004
//      All Rights Reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ---------------------------------
