// bslmf_addreference.t.cpp                                           -*-C++-*-

#include <bslmf_addreference.h>

#include <bslmf_issame.h>          // for testing only

#include <cstdlib>    // atoi()
#include <iostream>

using namespace BloombergLP;
using namespace std;

//=============================================================================
//                                TEST PLAN
//-----------------------------------------------------------------------------
//                                Overview
//                                --------
// TBD
//-----------------------------------------------------------------------------
// [ 1] bslmf_AddReference
// [ 2] USAGE EXAMPLE
//=============================================================================
//                  STANDARD BDE ASSERT TEST MACRO
//-----------------------------------------------------------------------------
static int testStatus = 0;

static void aSsErT(int c, const char *s, int i) {
    if (c) {
        cout << "Error " << __FILE__ << "(" << i << "): " << s
             << "    (failed)" << endl;
        if (testStatus >= 0 && testStatus <= 100) ++testStatus;
    }
}
#define ASSERT(X) { aSsErT(!(X), #X, __LINE__); }

//-----------------------------------------------------------------------------
#define LOOP_ASSERT(I,X) { \
    if (!(X)) { cout << #I << ": " << I << "\n"; aSsErT(1, #X, __LINE__);}}

#define LOOP2_ASSERT(I,J,X) { \
    if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " \
        << J << "\n"; aSsErT(1, #X, __LINE__); } }
//=============================================================================
#define P(X) cout << #X " = " << (X) << endl; // Print identifier and value.
#define Q(X) cout << "<| " #X " |>" << endl;  // Quote identifier literally.
#define P_(X) cout << #X " = " << (X) << ", " << flush; // P(X) without '\n'
#define L_ __LINE__                           // current Line number
#define T_() cout << '\t' << flush;           // Print tab w/o linefeed.

#define ASSERT_SAME(X, Y) ASSERT((bslmf_IsSame<X, Y>::VALUE))

//=============================================================================
//                  GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

enum   Enum   {};
struct Struct {};
union  Union  {};
class  Class  {};

typedef int INT;

typedef void      F ();
typedef void ( & RF)();
typedef void (*  PF)();
typedef void (*&RPF)();

typedef void    Fi  (int);
typedef void (&RFi) (int);
typedef void    FRi (int&);
typedef void (&RFRi)(int&);

typedef char    A [5];
typedef char (&RA)[5];

//=============================================================================
//                     GLOBAL TYPES FOR USAGE EXAMPLE
//-----------------------------------------------------------------------------

///Usage
///-----
// For example:
//..
     struct MyType {};
     typedef MyType& MyTypeRef;

//=============================================================================
//                              MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    int verbose = argc > 2;
    int veryVerbose = argc > 3;

    (void) verbose;          // eliminate unused variable warning
    (void) veryVerbose;      // eliminate unused variable warning

    cout << "TEST " << __FILE__ << " CASE " << test << endl;

    switch (test) { case 0:  // Zero is always the leading case.
      case 2: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //   Simple example illustrating use of 'bslmf_AddReference'.
        //
        // Concerns:
        //
        // Plan:
        //
        // Tactics:
        //   - Add-Hoc Data Selection Method
        //   - Brute-Force implementation technique
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) cout << endl << "USAGE EXAMPLE" << endl
                                  << "=============" << endl;

//
        ASSERT_SAME(bslmf_AddReference<int >::Type, int&);
        ASSERT_SAME(bslmf_AddReference<int&>::Type, int&);
        ASSERT_SAME(bslmf_AddReference<int volatile >::Type, volatile int&);
        ASSERT_SAME(bslmf_AddReference<int volatile&>::Type, volatile int&);
//
        ASSERT_SAME(bslmf_AddReference<MyType >::Type, MyType&);
        ASSERT_SAME(bslmf_AddReference<MyType&>::Type, MyType&);
        ASSERT_SAME(bslmf_AddReference<MyTypeRef>::Type, MyType&);
        ASSERT_SAME(bslmf_AddReference<MyType const >::Type, const MyType&);
        ASSERT_SAME(bslmf_AddReference<MyType const&>::Type, const MyType&);
//..

      } break;
      case 1: {
        // --------------------------------------------------------------------
        // Test Plan:
        //   Instantiate 'bslmf_AddReference' with various types and verify
        //   that its 'Type' typedef is set to a non-reference type.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "bslmf_AddReference" << endl
                          << "=====================" << endl;

        ASSERT_SAME(bslmf_AddReference<int       >::Type, int&);
        ASSERT_SAME(bslmf_AddReference<int&      >::Type, int&);
        ASSERT_SAME(bslmf_AddReference<int const >::Type, const int&);
        ASSERT_SAME(bslmf_AddReference<int const&>::Type, const int&);

        ASSERT_SAME(bslmf_AddReference<void *          >::Type, void *&);
        ASSERT_SAME(bslmf_AddReference<void *&         >::Type, void *&);
        ASSERT_SAME(bslmf_AddReference<void volatile *&>::Type,
                                          volatile void *&);
        ASSERT_SAME(bslmf_AddReference<char const *const&>::Type,
                                          const char *const&);

        ASSERT_SAME(bslmf_AddReference<Enum        >::Type, Enum&);
        ASSERT_SAME(bslmf_AddReference<Enum&       >::Type, Enum&);
        ASSERT_SAME(bslmf_AddReference<Struct      >::Type, Struct&);
        ASSERT_SAME(bslmf_AddReference<Struct&     >::Type, Struct&);
        ASSERT_SAME(bslmf_AddReference<Union       >::Type, Union&);
        ASSERT_SAME(bslmf_AddReference<Union&      >::Type, Union&);
        ASSERT_SAME(bslmf_AddReference<Class       >::Type, Class&);
        ASSERT_SAME(bslmf_AddReference<const Class&>::Type, const Class&);

        ASSERT_SAME(bslmf_AddReference<INT >::Type, int&);
        ASSERT_SAME(bslmf_AddReference<INT&>::Type, int&);

        ASSERT_SAME(bslmf_AddReference<int Class::* >::Type, int Class::*&);
        ASSERT_SAME(bslmf_AddReference<int Class::*&>::Type, int Class::*&);

        ASSERT_SAME(bslmf_AddReference<  F>::Type,  F&);
        ASSERT_SAME(bslmf_AddReference< RF>::Type,  F&);
        ASSERT_SAME(bslmf_AddReference< PF>::Type, PF&);
        ASSERT_SAME(bslmf_AddReference<RPF>::Type, PF&);

        ASSERT_SAME(bslmf_AddReference< Fi >::Type, Fi&);
        ASSERT_SAME(bslmf_AddReference<RFi >::Type, Fi&);
        ASSERT_SAME(bslmf_AddReference< FRi>::Type, FRi&);
        ASSERT_SAME(bslmf_AddReference<RFRi>::Type, FRi&);

        ASSERT_SAME(bslmf_AddReference< A>::Type, A&);
        ASSERT_SAME(bslmf_AddReference<RA>::Type, A&);
      } break;
      default: {
        cerr << "WARNING: CASE `" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = "
             << testStatus << "." << endl;
    }
    return testStatus;
}

// ---------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2005
//      All Rights Reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ---------------------------------
