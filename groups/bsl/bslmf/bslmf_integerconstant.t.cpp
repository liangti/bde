// bslmf_integerconstant.t.cpp                  -*-C++-*-

#include "bslmf_integerconstant.h"

#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace BloombergLP;
using namespace std;

//=============================================================================
//                             TEST PLAN
//-----------------------------------------------------------------------------
//                              Overview
//                              --------
// The component under test implements a trivial mechanism class template
// containing public compile-time values and types. An instantiation of this
// class template is immutable and, therefore, there are no primary
// manipulators.  There is, however, one accessor that provides an alternate
// interface to the (public static) value of the object.
//
// Basic Accessors:
//: o 'operator TYPE() const'
//
// Although it is an empty class, an instantiation is nevertheless
// default-constructible, copy-constructible and assignable.  The class is not
// value-semantic, however, as the constructors and assignment operator are
// no-ops and there is no equality comparison operator.
//
// Global Concerns:
//: o The test driver is robust w.r.t. reuse in other, similar components.
//: o The template can be instantiated with different integer types.
//: o The template can be instantiated with different integer values,
//:   including min and max values for the instance type.
//: o ACCESSOR methods are declared 'const'.
//
// Global Assumption:
//: o The component under test does not allocate memory from the heap or from
//:   any allocator.
//: o All operations a fully thread safe (because there is no runtime code
//:   executed).
// ----------------------------------------------------------------------------
// VARIABLES:
// [ 3] const TYPE value;
//
// TYPES:
// [ 3] type
// [ 3] value_type
// [ 4] bslmf::false_type
// [ 4] bslmf::true_type
//
// CREATORS
// [ 3] integer_constant();
// [ 3] integer_constant(const integer_constant&);
// [ 3] ~integer_constant();
//
// MANIPULATORS
// [ 3] integer_constant& operator=(const integer_constant&);
//
// ACCESSORS
// [ 3] operator TYPE() const;
//-----------------------------------------------------------------------------
// [ 1] BREATHING TEST
// [ 5] USAGE EXAMPLE
// [ 3] CONCERN: The template can be instantiated with different integer types.
// [ 3] CONCERN: The template can be instantiated with different integer
//      values, including min and max values for the instance type.
// [ 3] CONCERN: ACCESSOR methods are declared 'const'.
//
// TEST APPARATUS
// [ 2] IsSameType<class A, class B>
// [ 2] bool isConst(T&);
// [ 2] CONCERN: This test driver is reusable w/other, similar components.
//-----------------------------------------------------------------------------

//==========================================================================
//                  STANDARD BDE ASSERT TEST MACRO
//--------------------------------------------------------------------------
// NOTE: THIS IS A LOW-LEVEL COMPONENT AND MAY NOT USE ANY C++ LIBRARY
// FUNCTIONS, INCLUDING IOSTREAMS.

namespace {

int verbose = 0;
int veryVerbose = 0;
int veryVeryVerbose = 0;
int testStatus = 0;

void aSsErT(int c, const char *s, int i) {
    if (c) {
        printf("Error " __FILE__ "(%d): %s    (failed)\n", i, s);
        if (testStatus >= 0 && testStatus <= 100) ++testStatus;
    }
}

}  // close unnamed namespace

# define ASSERT(X) { aSsErT(!(X), #X, __LINE__); }

//=============================================================================
//                  STANDARD BDE LOOP-ASSERT TEST MACROS
//-----------------------------------------------------------------------------
// NOTE: This implementation of LOOP_ASSERT macros must use printf since
//       cout uses new and must not be called during exception testing.

#define LOOP_ASSERT(I,X) { \
    if (!(X)) { printf("%s", #I ": "); dbg_print(I); printf("\n"); \
                fflush(stdout); aSsErT(1, #X, __LINE__); } }

#define LOOP2_ASSERT(I,J,X) { \
    if (!(X)) { printf("%s", #I ": "); dbg_print(I); printf("\t"); \
                printf("%s", #J ": "); dbg_print(J); printf("\n"); \
                fflush(stdout); aSsErT(1, #X, __LINE__); } }

#define LOOP3_ASSERT(I,J,K,X) {                    \
    if (!(X)) { printf("%s", #I ": "); dbg_print(I); printf("\t"); \
                printf("%s", #J ": "); dbg_print(J); printf("\t"); \
                printf("%s", #K ": "); dbg_print(K); printf("\n"); \
                fflush(stdout); aSsErT(1, #X, __LINE__); } }

#define LOOP4_ASSERT(I,J,K,L,X) {                  \
    if (!(X)) { printf("%s", #I ": "); dbg_print(I); printf("\t"); \
                printf("%s", #J ": "); dbg_print(J); printf("\t"); \
                printf("%s", #K ": "); dbg_print(K); printf("\t"); \
                printf("%s", #L ": "); dbg_print(L); printf("\n"); \
                fflush(stdout); aSsErT(1, #X, __LINE__); } }

#define LOOP5_ASSERT(I,J,K,L,M,X) {                \
    if (!(X)) { printf("%s", #I ": "); dbg_print(I); printf("\t"); \
                printf("%s", #J ": "); dbg_print(J); printf("\t"); \
                printf("%s", #K ": "); dbg_print(K); printf("\t"); \
                printf("%s", #L ": "); dbg_print(L); printf("\t"); \
                printf("%s", #M ": "); dbg_print(M); printf("\n"); \
                fflush(stdout); aSsErT(1, #X, __LINE__); } }

//=============================================================================
//                  SEMI-STANDARD TEST OUTPUT MACROS
//-----------------------------------------------------------------------------
#define Q(X) printf("<| " #X " |>\n");     // Quote identifier literally.
#define P(X) dbg_print(#X " = ", X, "\n")  // Print identifier and value.
#define P_(X) dbg_print(#X " = ", X, ", ") // P(X) without '\n'
#define L_ __LINE__                        // current Line number
#define T_ putchar('\t');                  // Print a tab (w/o newline)

//=============================================================================
//                  GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

enum { VERBOSE_ARG_NUM = 2, VERY_VERBOSE_ARG_NUM, VERY_VERY_VERBOSE_ARG_NUM };

struct DummyType
{
    int d_x;
};

//=============================================================================
//                      GLOBAL HELPER FUNCTIONS FOR TESTING
//-----------------------------------------------------------------------------

void dbg_print_char(int val)
    // Print the specified integer 'val' as a signed char.  If called with an
    // argument of unsigned char type, the promotion rules will cause it to
    // be printed as a positive value.
{
    if (val < 0) {
        printf("-");
        val = -val;
    }
    if (' ' <= val && val < '\177')
        printf("'%c'", val);  // Printable character
    else
        printf("'\\%o'", val);  // Unprintable character (print as octal)
    fflush(stdout);
}

// Fundamental-type-specific print functions.
inline void dbg_print(char val) { dbg_print_char(val); }
inline void dbg_print(unsigned char val) { dbg_print_char(val); }
inline void dbg_print(signed char val) { dbg_print_char(val); }
inline void dbg_print(short val) { printf("%hd", val); fflush(stdout); }
inline void dbg_print(unsigned short val) {printf("%hu", val); fflush(stdout);}
inline void dbg_print(int val) { printf("%d", val); fflush(stdout); }
inline void dbg_print(unsigned int val) { printf("%u", val); fflush(stdout); }
inline void dbg_print(long val) { printf("%ld", val); fflush(stdout); }
inline void dbg_print(unsigned long val) { printf("%lu", val); fflush(stdout);}
inline void dbg_print(long long val) { printf("%lld", val); fflush(stdout); }
inline void dbg_print(unsigned long long val)
    { printf("%llu", val); fflush(stdout);}
inline void dbg_print(float val) { printf("'%f'", val); fflush(stdout); }
inline void dbg_print(double val) { printf("'%f'", val); fflush(stdout); }
inline void dbg_print(const char* val)
    { printf("\"%s\"", val); fflush(stdout); }

template <class A, class B>
struct IsSameType
{
    // Provide a member enum 'VALUE' that has a true value if 'A' and 'B' are
    // the same type and a false value otherwise.

    enum { VALUE = false };
};

template <class A>
struct IsSameType<A, A>
{
    // Provide a member enum 'VALUE' that has a true value if 'A' and 'B' are
    // the same type and a false value otherwise.

    enum { VALUE = true };
};

template <class T> inline bool isConst(T&) { return false; }
template <class T> inline bool isConst(const T&) { return true; }
    // Return 'true' if the specified argument is 'const' and false otherwise.

//=============================================================================
//                  CODE FOR TESTING USAGE EXAMPLES
//-----------------------------------------------------------------------------

///Usage
///-----
// This section illustates intended usage of this component
//
///Example 1: Compile-Time Function Dispatching
/// - - - - - - - - - - - - - - - - - - - - - - 
// The most common use of this structure is to perform compile-time function
// dispatching based on a compile-time calculation.  Often the calculation is
// nothing more than a simple predicate, allowing us to select one of two
// functions based on whether the predicate holds.  The following function,
// 'doSomething', uses a fast implementation (e.g., using 'memcpy') if the
// parameterized type allows for such operations, otherwise it will use a more
// generic and slower implementation (e.g., using the copy constructor).  This
// example uses the types 'true_type' and 'false_type', which are simple
// typedefs for 'integer_constant<bool, true>' and
// 'integer_constant<bool, false>', respectively.
//..
      #include <bslmf_integerconstant.h>
  
      template <class T>
      int doSomethingImp(T *t, bslmf::true_type)
      {
          // slow, generic implementation
          // ...
          (void) t;
          return 11; 
      }
  
      template <class T>
      int doSomethingImp(T *t, bslmf::false_type)
      {
          // fast implementation that works only for some types of T
          // ...
          (void) t;
          return 55; 
      }
  
      template <bool IsSlow, class T>
      int doSomething(T *t)
      {
          // Dispatch to an implementation depending on the (compile-time)
          // value of 'IsSlow'.
          return doSomethingImp(t, bslmf::integer_constant<bool, IsSlow>());
      }
//..
// For some parameter types, the fast version of 'doSomethingImp' is not
// legal.  The power of this approach is that the compiler will not attempt
// semantic anlysis on the implementation that does not match the appropriate
// 'integer_constant' argument.
//..
      int usageExample1()
      {
          int r;
  
          int i;
          r = doSomething<false>(&i);   // select fast version for int
          ASSERT(55 == r);
  
          double m;
          r = doSomething<true>(&m); // select slow version for double
          ASSERT(11 == r);

          return 0;
      }
//..
///Example 2: Base class for metafunctions
/// - - - - - - - - - - - - - - - - - - - 
// Hard-coding the value of an 'integer_constant' is not especially useful.
// Rather, 'integer_constant' is typically used as the base class for
// "metafunction" classes, classes that yield the value of compile-time
// properties, including properties that are associated with types, rather
// than with values.  For example, the following metafunction can be used at
// compile time to determine whether a type is a floating point type:
//..
      template <class TYPE> struct IsFloatingPoint    : bslmf::false_type { };
      template <> struct IsFloatingPoint<float>       : bslmf::true_type { };
      template <> struct IsFloatingPoint<double>      : bslmf::true_type { };
      template <> struct IsFloatingPoint<long double> : bslmf::true_type { };
//..
// The value 'IsFloatingPoint<int>::value' is false and
// 'IsFloatingPoint<double>::value' is true.  The 'integer_constant' base
// class has a member type, 'type', that refers to itself and is inherited by
// 'IsFloatingPoint'. Thus 'IsFloatingPoint<float>::type' is 'true_type' and
// 'IsFloatingPoint<char>::type' is 'false_type'.  'IsFloatingPoint' is an a
// member of a common category of metafunctions known as "type traits" because
// they express certain properties (traits) of a type.  Using this
// metafunction, we can rewrite the 'doSomething' function from first example
// so that it does not require the user to specify the 'IsSlow' template
// argument:
//..
      template <class T>
      int doSomething2(T *t)
      {
          // Automatically detect whether to use slow or fast imp.
          const bool isSlow = IsFloatingPoint<T>::value;
          return doSomethingImp(t, bslmf::integer_constant<bool, isSlow>());
      }
  
      int usageExample2()
      {
          int r;
  
          int i;
          r = doSomething2(&i); // select fast version for int
          ASSERT(55 == r);
  
          double m;
          r = doSomething2(&m); // select slow version for double
          ASSERT(11 == r);

          return 0;
      }
//..

//=============================================================================
//                   FUNCTIONS FOR INDIVIDUAL TEST CASES
//-----------------------------------------------------------------------------

template <class TYPE, TYPE VAL>
void fullTest(const char TYPENAME[])
    // Preform the full suite of tests on 'integer_constant' instantiated with
    // the specified 'TYPE' and 'VAL'.  The specified 'TYPENAME' string
    // contains a printable representation of the name of 'TYPE'.  This
    // function reads the global 'verbose' variable and (if an error is
    // detected) changes the value of the global 'status' variable.  See the
    // "FULL TEST" case in 'main' for a full description of the concerns and
    // plan for this test.
{
    if (verbose) {
        printf("\nRun fullTest<%s, ", TYPENAME);
        dbg_print(VAL);
        printf(">()\n");
    }

    typedef bslmf::integer_constant<TYPE, VAL> Obj;

    if (verbose) printf("\tTest 'value' static member constant\n");
    LOOP2_ASSERT(TYPENAME, VAL, isConst(Obj::value));
    const TYPE* p = &Obj::value; (void) p;  // Test that address can be taken
    LOOP2_ASSERT(TYPENAME, VAL, VAL == Obj::value);

    if (verbose) printf("\tTest 'type' and 'value_type' member types\n");
    LOOP2_ASSERT(TYPENAME, VAL, VAL == Obj::type::value);
    LOOP2_ASSERT(TYPENAME, VAL, (IsSameType<Obj, typename Obj::type>::VALUE));
    LOOP2_ASSERT(TYPENAME, VAL,
                 (IsSameType<TYPE, typename Obj::value_type>::VALUE));

    if (verbose) printf("\tTest default constructor\n");
    Obj x; const Obj& X = x;

    if (verbose) printf("\tTest conversion to 'TYPE'\n");
    TYPE v = X;
    LOOP2_ASSERT(TYPENAME, VAL, VAL == v);

    if (verbose) printf("\tTest copy constructor\n");
    // Result of copy constructor is same as result of default constructor.
    Obj x2(x); const Obj& X2 = x2;
    v = X2;
    LOOP2_ASSERT(TYPENAME, VAL, VAL == v);

    if (verbose) printf("\tTest assignment operator\n");
    // Assignment has no effect
    Obj x3; const Obj& X3 = x3;
    x3 = x;
    v = X3;
    LOOP2_ASSERT(TYPENAME, VAL, VAL == v);
}

//=============================================================================
//                              MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    verbose = argc > 2;
    veryVerbose = argc > 3;
    veryVeryVerbose = argc > 4;

    printf("TEST " __FILE__ " CASE %d\n", test);

    switch (test) { case 0:  // Zero is always the leading case.
      case 5: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //
        // Concerns:
        //: 1 The usage example provided in the component header file
        //:   compiles, links, and runs as shown.
        //
        // Plan:
        //: 1 Copy the usage examples from the header into this test
        //:   driver.  (C-1)
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) printf("\nTesting USAGE EXAMPLE"
                            "\n=====================\n");

        usageExample1();
        usageExample2();

      } break;
      case 4: {
        // --------------------------------------------------------------------
        // TESTING false_type AND true_type
        //
        // Concerns:
        //: 1 'false_type' is identical to 'integer_constant<bool, false>'.
        //:
        //: 2 'true_type' is identical to 'integer_constant<bool, true>'.
        //
        // Plan:
        //: 1 Use 'IsSameType' to verify the type of 'false_type' and
        //:   'true_type'.  (C-1..2)
        //
        // Testing:
        //   bslmf::false_type
        //   bslmf::true_type
        // --------------------------------------------------------------------

        if (verbose) printf("\nTesting false_type and true_type"
                            "\n================================\n");

        ASSERT((IsSameType<bslmf::false_type,
                           bslmf::integer_constant<bool, false> >::VALUE));
        ASSERT((IsSameType<bslmf::true_type,
                           bslmf::integer_constant<bool, true> >::VALUE));
        
      } break;
      case 3: {
        // --------------------------------------------------------------------
        // FULL TEST
        //
        // Concerns:
        //: 1 'value' type is a const lvalue of type 'TYPE' with value 'VAL'
        //:
        //: 2 'type' member is the same as 'integer_constant<TYPE, VAL>'
        //:
        //: 3 'value_type' member is the same as 'TYPE'
        //:
        //: 4 An 'integer_constant<TYPE, VAL>' object is convertible to an
        //:   object of type 'TYPE' with a 'value' of 'VAL.
        //:
        //: 5 'integer_constant<TYPE, VAL>' is default constructible.
        //:
        //: 6 'integer_constant<TYPE, VAL>' is copy constructible such that
        //:   the copy constructor has exactly the same behavior as the default
        //:   constructor (i.e., the argument to the copy constructor is
        //:   ignored). 
        //:
        //: 7 'integer_constant<TYPE, VAL>' is assignable, though the
        //:   assignment operator has no effect.
        //:
        //: 8 'integer_constant<TYPE, VAL>' is destructible.
        //:
        //: 9 All of the above concerns apply to each built-in integer type.
        //:
        //: 10 All of the above concerns apply to multiple values, including
        //     the minimum and maximum values of of 'TYPE'.
        //
        // Plan:
        //: 1 Assert that 'value' is const and verify that its address can be
        //:   taken and stored in a pointer to 'const TYPE'.  (C-1)
        //:
        //: 2 Use 'IsSameType' verify that the 'type' and 'value_type' are as
        //:   expected. (C-2 and C-3)
        //:
        //: 3 Construct an object of type 'integer_constant<TYPE, VAL>' and
        //:   use it to initialize a variable of type 'TYPE'.  Verify that
        //:   the variable compares equal to 'VAL'. (C-4)
        //:
        //: 4 Default construct, copy construct, and assign objects of type
        //:   'integer_constant<TYPE, VAL>'.  In each case, verify that
        //:   converting the result to 'TYPE' yields 'VAL'.  (C5..7)
        //:
        //: 5 The destructor is tested automatically when the objects created
        //:   in step 4 go out of scope. (C-8)
        //:
        //: 6 Instantiate the entire test in a template function, 'fullTest',
        //:   instantiate 'fullTest' with each C++ integer type and with
        //:   several different values, including the minimum and maximum
        //:   values for the type.  (C-9..10)
        //
        // Testing:
        //   value
        //   type
        //   value_type
        //   operator TYPE() const;
        //   compiler-generated default constructor
        //   compiler-generated copy constructor
        //   compiler-generated assignment operator
        //   compiler-generated destructor
        // --------------------------------------------------------------------

        if (verbose) printf("\nFULL TEST"
                            "\n=========\n");

        fullTest<bool, false>("bool");
        fullTest<bool, true>("bool");

        fullTest<char, 0>("char");
        fullTest<char, 'x'>("char");
        fullTest<char, CHAR_MIN>("char");
        fullTest<char, CHAR_MAX>("char");

        fullTest<unsigned char, 'y'>("unsigned char");
        fullTest<unsigned char, 0>("unsigned char");
        fullTest<unsigned char, 255>("unsigned char");

        fullTest<signed char, 0>("signed char");
        fullTest<signed char, -128>("signed char");
        fullTest<signed char, 127>("signed char");
        
        fullTest<short, -5>("short");
        fullTest<short, SHRT_MIN>("short");
        fullTest<short, SHRT_MAX>("short");

        fullTest<unsigned short, 6>("unsigned short");
        fullTest<unsigned short, 0>("unsigned short");
        fullTest<unsigned short, USHRT_MAX>("unsigned short");

        fullTest<int, 0>("int");
        fullTest<int, -1>("int");
        fullTest<int, 99>("int");
        fullTest<int, INT_MIN>("int");
        fullTest<int, INT_MAX>("int");

        fullTest<unsigned, 1>("unsigned");
        fullTest<unsigned, 99>("unsigned");
        fullTest<unsigned, 0>("unsigned");
        fullTest<unsigned, UINT_MAX>("unsigned");

        fullTest<long, -7>("long");
        fullTest<long, LONG_MIN>("long");
        fullTest<long, LONG_MAX>("long");

        fullTest<unsigned long, 8>("unsigned long");
        fullTest<unsigned long, 0>("unsigned long");
        fullTest<unsigned long, ULONG_MAX>("unsigned long");

        // Not all implementations define LLONG_MIN/MAX, so use hard-coded
        // 64-bit hex values instead.
        fullTest<long long, 0>("long long");
        fullTest<long long, 0x1000000000000000LL>("long long");
        fullTest<long long, 0x7fffffffffffffffLL>("long long");

        // Not all implementations define ULLONG_MAX, so use hard-coded
        // 64-bit hex value instead.
        fullTest<unsigned long long, 10>("unsigned long long");
        fullTest<unsigned long long, 0>("unsigned long long");
        fullTest<unsigned long long, 0xffffffffffffffffULL>(
            "unsigned long long");

      } break;
      case 2: {
        // --------------------------------------------------------------------
        // TESTING TEST APPARATUS
        //
        // Concerns:
        //: 1 When called with values of the same type, 'IsSameType' returns
        //:   true
        //:
        //: 2 When called with values of different type, 'IsSameType' returns
        //:   false
        //:
        //: 3 When called with values of the same type but where
        //:   one is a reference, 'IsSameType' returns false.
        //:
        //: 4 When called with values of the same type but with
        //:   different cv-qualifiers, 'IsSameType' returns false.
        //:
        //: 5 Arguments to 'IsSameType' can be class type or integral type.
        //:
        //: 6 For a variable 'x', 'isConst(x)' returns true if 'x' is 'const'
        //:   and false otherwise.
        //
        // Plan:
        //: 1 Instantiate 'IsSameType' with every combination of types 'int',
        //:   'char', 'DummyType'; with every combination of 'int', 'const
        //:   int', 'volatile int', and with every combination of 'int'
        //:   'int&' and 'const int&'.  Verify that its 'VALUE' member is
        //:   true only when the types are identically the same.  (C-1..5)
        //:
        //: 2 Call 'isConst' for both const and non-const variables and
        //:   verify the result.  (C-6)
        //
        // Testing:
        //   IsSameType<class A, class B>
        //   bool isConst(T&);
        // --------------------------------------------------------------------

        if (verbose) printf("\nTESTING TEST APPARATUS"
                            "\n======================\n");

        if (verbose) printf("Testing IsSameType<A, B>\n");
        ASSERT((  IsSameType<int,       int>::VALUE));
        ASSERT((! IsSameType<int,       char>::VALUE));
        ASSERT((! IsSameType<int,       DummyType>::VALUE));
        ASSERT((! IsSameType<char,      int>::VALUE));
        ASSERT((  IsSameType<char,      char>::VALUE));
        ASSERT((! IsSameType<char,      DummyType>::VALUE));
        ASSERT((! IsSameType<DummyType, int>::VALUE));
        ASSERT((! IsSameType<DummyType, char>::VALUE));
        ASSERT((  IsSameType<DummyType, DummyType>::VALUE));
                             
        ASSERT((  IsSameType<               int,                int>::VALUE));
        ASSERT((! IsSameType<               int, const          int>::VALUE));
        ASSERT((! IsSameType<               int,       volatile int>::VALUE));
        ASSERT((! IsSameType<               int, const volatile int>::VALUE));
        ASSERT((! IsSameType<const          int,                int>::VALUE));
        ASSERT((  IsSameType<const          int, const          int>::VALUE));
        ASSERT((! IsSameType<const          int,       volatile int>::VALUE));
        ASSERT((! IsSameType<const          int, const volatile int>::VALUE));
        ASSERT((! IsSameType<      volatile int,                int>::VALUE));
        ASSERT((! IsSameType<      volatile int, const          int>::VALUE));
        ASSERT((  IsSameType<      volatile int,       volatile int>::VALUE));
        ASSERT((! IsSameType<      volatile int, const volatile int>::VALUE));
        ASSERT((! IsSameType<const volatile int,                int>::VALUE));
        ASSERT((! IsSameType<const volatile int, const          int>::VALUE));
        ASSERT((! IsSameType<const volatile int,       volatile int>::VALUE));
        ASSERT((  IsSameType<const volatile int, const volatile int>::VALUE));

        ASSERT((  IsSameType<      int ,       int >::VALUE));
        ASSERT((! IsSameType<      int ,       int&>::VALUE));
        ASSERT((! IsSameType<      int , const int&>::VALUE));
        ASSERT((! IsSameType<      int&,       int >::VALUE));
        ASSERT((  IsSameType<      int&,       int&>::VALUE));
        ASSERT((! IsSameType<      int&, const int&>::VALUE));
        ASSERT((! IsSameType<const int&,       int >::VALUE));
        ASSERT((! IsSameType<const int&,       int&>::VALUE));
        ASSERT((  IsSameType<const int&, const int&>::VALUE));

        if (verbose) printf("Testing isConst(T&)\n");
        int                i;
        const int          ci = 0;
        volatile int       vi;
        const volatile int cvi = 0;

        DummyType d;
        const DummyType& D = d;

        ASSERT(! isConst(i));
        ASSERT(  isConst(ci));
        ASSERT(! isConst(vi));
        ASSERT(  isConst(cvi));
        
        ASSERT(! isConst(d));
        ASSERT(  isConst(D));

      } break;
      case 1: {
        // --------------------------------------------------------------------
        // BREATHING TEST
        //
        // Concerns:
        //: 1 The basic functionality of 'integer_constant' works as
        //:   expected.
        //
        // Plan:
        //: 1 Instantiate 'integer_constant' with several combinations of
        //:   types and values.  For each combination test that the (static)
        //:   'value' member has the expected value, that the 'type' member
        //:   exists and has the same 'value', that the 'value_type' member
        //:   exists and can hold 'value', and that an object of
        //:   'integer_constant' can be constructed and is convertible to the
        //:   specified 'TYPE'.  (C-1)
	//
        // Testing:
        //   BREATHING TEST
        // --------------------------------------------------------------------

        if (verbose) printf("\nBREATHING TEST"
                            "\n==============\n");

        using namespace BloombergLP::bslmf;

        if (verbose) printf("... With 'bool' type\n");
        {
            typedef integer_constant<bool, false> TypeFalse;
            typedef integer_constant<bool, true>  TypeTrue;

            ASSERT(false == TypeFalse::value);
            ASSERT(true  == TypeTrue::value);

            ASSERT(false == TypeFalse::type::value);
            ASSERT(true  == TypeTrue::type::value);

            TypeFalse icFalse; const TypeFalse& ICFALSE = icFalse;
            TypeFalse::value_type vFalse = ICFALSE;
            ASSERT(false == vFalse);

            TypeTrue icTrue; const TypeTrue& ICTRUE = icTrue;
            bool vTrue = ICTRUE;
            ASSERT(true == vTrue);
        }

        if (verbose) printf("... With 'int' type\n");
        {
            typedef integer_constant<int, 0>  Type0;
            typedef integer_constant<int, 99> Type99;

            ASSERT(0  == Type0::value);
            ASSERT(99 == Type99::value);

            ASSERT(0  == Type0::type::value);
            ASSERT(99 == Type99::type::value);

            Type0 ic0; const Type0& IC0 = ic0;
            Type0::value_type v0 = IC0;
            ASSERT(0 == v0);

            Type99 ic99; const Type99& IC99 = ic99;
            int v99 = IC99;
            ASSERT(99 == v99);
        }

        if (verbose) printf("... With 'unsigned char' type\n");
        {
            typedef integer_constant<unsigned char, 0>  Type0;
            typedef integer_constant<unsigned char, 99> Type99;

            ASSERT(0  == Type0::value);
            ASSERT(99 == Type99::value);

            ASSERT(0  == Type0::type::value);
            ASSERT(99 == Type99::type::value);

            Type0 ic0; const Type0& IC0 = ic0;
            Type0::value_type v0 = IC0;
            ASSERT(0 == v0);

            Type99 ic99; const Type99& IC99 = ic99;
            unsigned char v99 = IC99;
            ASSERT(99 == v99);
        }

      } break;

      default: {
        fprintf(stderr, "WARNING: CASE `%d' NOT FOUND.\n", test);
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        fprintf(stderr, "Error, non-zero test status = %d.\n", testStatus);
    }

    return testStatus;
}

// ---------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2011
//      All Rights Reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ---------------------------------
