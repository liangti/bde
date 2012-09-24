// baetzo_localtimedescriptor.cpp                                     -*-C++-*-
#include <baetzo_localtimedescriptor.h>

#include <bdes_ident.h>
BDES_IDENT_RCSID(baetzo_localtimedescriptor_cpp,"$Id$ $CSID$")

#include <bslim_printer.h>

#include <bsl_ios.h>
#include <bsl_ostream.h>

namespace BloombergLP {

                        // --------------------------------
                        // class baetzo_LocalTimeDescriptor
                        // --------------------------------

// ACCESSORS

                                  // Aspects

bsl::ostream& baetzo_LocalTimeDescriptor::print(
                                            bsl::ostream& stream,
                                            int           level,
                                            int           spacesPerLevel) const
{
    bslim::Printer printer(&stream, level, spacesPerLevel);
    printer.start();
    printer.printAttribute("utcOffsetInSeconds", d_utcOffsetInSeconds);
    printer.printAttribute("dstInEffectFlag",    d_dstInEffectFlag);
    printer.printAttribute("description",        d_description.c_str());
    printer.end();

    return stream;
}

// FREE OPERATORS
bsl::ostream& operator<<(bsl::ostream&                     stream,
                         const baetzo_LocalTimeDescriptor& object)
{
    bslim::Printer printer(&stream, 0, -1);
    printer.start();
    printer.printValue(object.utcOffsetInSeconds());
    printer.printValue(object.dstInEffectFlag());
    printer.printValue(object.description().c_str());
    printer.end();

    return stream;
}

}  // close enterprise namespace

// ---------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2011
//      All Rights Reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ---------------------------------

