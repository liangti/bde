// bbldc_basicactual365fixed.cpp                                      -*-C++-*-
#include <bbldc_basicactual365fixed.h>

#include <bsls_ident.h>
BSLS_IDENT_RCSID(bbldc_basicactual365fixed_cpp,"$Id$ $CSID$")

namespace BloombergLP {
namespace bbldc {

                        // --------------------------
                        // struct BasicActual365Fixed
                        // --------------------------

// CLASS METHODS
double BasicActual365Fixed::yearsDiff(const bdlt::Date& beginDate,
                                      const bdlt::Date& endDate)
{

    // Storing the result value in a 'volatile double' should remove
    // any extra-precision available in floating-point registers.

    const volatile double rv = (endDate - beginDate) / 365.0;

    return rv;
}

}  // close package namespace
}  // close enterprise namespace

// ----------------------------------------------------------------------------
// Copyright 2017 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
