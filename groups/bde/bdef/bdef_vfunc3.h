// bdef_vfunc3.h                -*-C++-*-
#ifndef INCLUDED_BDEF_VFUNC3
#define INCLUDED_BDEF_VFUNC3

#ifndef INCLUDED_BDES_IDENT
#include <bdes_ident.h>
#endif
BDES_IDENT("$Id: $")


//@PURPOSE: Provide a signature-specific function object (functor).
//
//@CLASSES:
//   bdef_Vfunc3: signature-specific function object (functor)
//
//@AUTHOR: John Lakos (jlakos)
//
//@DEPRECATED: This component should not be used in new code, and will be
// deleted in the near future.  Please see 'bdef_function', 'bdef_bind', etc.
// for alternatives that should be used for all future development.
//
//@DESCRIPTION: This component implements a function object (functor) that
// returns void and takes three arguments of arbitrary type; it is invoked in a
// manner similar to that of following free function:
//..
//   void functionObject(arg1, arg2, arg3);
//..
// The functors in the 'bdef' package are implemented using the envelope-letter
// pattern (see Coplien, Sections 5.5-5.6, pp.  133-179).  Functors are
// objects that implement a function-call operator whose signature
// characterizes the particular functor's type.  A valid functor will contain
// a pointer to an underlying (member or free) function and is invoked in a
// manner similar to that of free functions.  Unlike a function pointer, a
// functor may be created with one or more arbitrary objects (sometimes called
// "user data") to be passed (typically as trailing arguments) to the
// underlying function.  By "pre-binding" particular arguments to the
// underlying function, a functor reduces the number of arguments a caller
// must supply when the functor is invoked.  In this way, function objects can
// be used to coerce functions with extra arguments of arbitrary type into a
// standard calling signature.  Even (non-'static') *member* functions can be
// encapsulated within functors and treated uniformly, simply by supplying the
// appropriate representation object at construction.
//
// The 'bdef_Vfunc3' functor (envelope) holds a polymorphic, reference-counted,
// dynamically-allocated representation (letter), which is loaded by the
// immediate client.  Typical users do not load the functor representation
// directly, but instead rely on a suite of template functions (provided by
// components in the higher-level 'bdefu' package) to allocate and install the
// representation appropriate to (1) the desired function-call-operator
// signature and (2) the supplied user data.  See the 'bdefu_vfunc3' component
// for more information on populating 'bdef_Vfunc3' function objects with
// specific representations.
//
// Note that because each required argument type 'T' is passed by ('const'
// 'T&'), a compiler will generate an error if the user declares a callback
// function taking an argument via a non-'const' reference parameter.  This
// serendipitous side effect is truly a feature, and specifically not a bug,
// as we use references (and occasionally pointers) to pass constant
// arguments, and pointers (exclusively) to pass modifiable arguments.  This
// implementation enforces that rule.
//
///USAGE
///-----

#ifndef INCLUDED_BDESCM_VERSION
#include <bdescm_version.h>
#endif

#ifndef INCLUDED_BDEFR_VFUNC3
#include <bdefr_vfunc3.h>
#endif

namespace BloombergLP {

                        // =================
                        // class bdef_Vfunc3
                        // =================

template <class A1, class A2, class A3>
class bdef_Vfunc3 {
    // Provide an object that encapsulates a function or method along with zero
    // or more "extra" arguments of arbitrary type (collectively referred to
    // as "user data") to be passed as arguments to the underlying function on
    // invocation.  Clients invoke the underlying function by calling this
    // functor's function-call operator,
    //..
    //     (void) functionObject(arg1, arg2, arg3) // functor calling signature
    //..
    // which takes three arguments and returns void.  Note that pointer (but
    // not reference) types are supported.

    bdefr_Vfunc3<A1, A2, A3> *d_rep_p;  // polymorphic functor representation

  public:
    // CREATORS
    bdef_Vfunc3();
        // Create an uninitialized functor.  The resulting functor cannot be
        // invoked, but may subsequently be assigned an invokable value.

    bdef_Vfunc3(bdefr_Vfunc3<A1, A2, A3> *representation);
        // Create a functor that assumes shared ownership of the specified,
        // dynamically allocated, reference-counted representation.  If 0 is
        // specified, the functor is created in a null state (i.e., cannot be
        // invoked), but may subsequently be assigned a value.
        //
        // Note that typical clients of this class do not use this constructor
        // directly, but instead use utilities provided in higher level
        // components (see 'bdefu_vfunc3') to create an appropriate
        // representation and load it into an existing functor.

    bdef_Vfunc3(const bdef_Vfunc3<A1, A2, A3>& functionObject);
        // Create a copy of the specified 'functionObject'.  If
        // 'functionObject' is null, an independent null functor is created.
        // Otherwise, both functors will share ownership of the same internal
        // representation.

    ~bdef_Vfunc3();
        // If this functor holds a non-null representation, decrement the
        // reference count of that internal representation object, and, if the
        // count is now 0, destroy and deallocate that representation (using
        // the static 'deleteObject' method of 'bdefr_Vfunc3' base class).

    // MANIPULATORS
    bdef_Vfunc3<A1, A2, A3>& operator=(
        const bdef_Vfunc3<A1, A2, A3>& functionObject);
        // Assign the value of the specified 'functionObject' to this object.
        // If 'functionObject' is not null, both functors will share ownership
        // of the same internal representation; otherwise, both functors will
        // be null.  If this object was not initially null (and did not
        // already share ownership of the same internal representation with
        // 'functionObject'), first decrement the reference count of this
        // functor's internal representation object, and, if the count is now
        // 0, destroy and deallocate the representation (using the static
        // 'deleteObject' method of 'bdefr_Vfunc3' base class.

    // ACCESSORS
    void operator()(const A1& argument1, const A2& argument2,
                    const A3& argument3) const;
        // Invoke this functor.  The behavior is undefined if this functor is
        // null.

    operator const void *() const;
        // Return 0 if this functor is null, and non-zero otherwise.
};

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

template <class A1, class A2, class A3>
inline bdef_Vfunc3<A1, A2, A3>::bdef_Vfunc3()
: d_rep_p(0)
{
}

template <class A1, class A2, class A3>
inline bdef_Vfunc3<A1, A2, A3>::bdef_Vfunc3(bdefr_Vfunc3<A1, A2, A3> *rep)
: d_rep_p(rep)
{
    if (d_rep_p) {
        d_rep_p->increment();
    }
}

template <class A1, class A2, class A3>
inline bdef_Vfunc3<A1, A2, A3>::bdef_Vfunc3(const bdef_Vfunc3& functor)
: d_rep_p(functor.d_rep_p)
{
    if (d_rep_p) {
        d_rep_p->increment();
    }
}

template <class A1, class A2, class A3>
inline bdef_Vfunc3<A1, A2, A3>::~bdef_Vfunc3()
{
    if (d_rep_p && 0 == d_rep_p->decrement()) {
        bdefr_Vfunc3<A1, A2, A3>::deleteObject(d_rep_p);
    }
}

template <class A1, class A2, class A3> inline
bdef_Vfunc3<A1, A2, A3>&
bdef_Vfunc3<A1, A2, A3>::operator=(const bdef_Vfunc3<A1, A2, A3>& rhs)
{
    if (d_rep_p != rhs.d_rep_p) {
        if (d_rep_p && 0 == d_rep_p->decrement()) {
            bdefr_Vfunc3<A1, A2, A3>::deleteObject(d_rep_p);
        }
        d_rep_p = rhs.d_rep_p;
        if (d_rep_p) {
            d_rep_p->increment();
        }
    }
    return *this;
}

template <class A1, class A2, class A3>
inline void bdef_Vfunc3<A1, A2, A3>::operator()(const A1& argument1,
                                                const A2& argument2,
                                                const A3& argument3) const
{
    d_rep_p->execute(argument1, argument2, argument3);
}

template <class A1, class A2, class A3>
inline bdef_Vfunc3<A1, A2, A3>::operator const void *() const
{
    return d_rep_p;
}

}  // close namespace BloombergLP

#endif

// ---------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2002
//      All Rights Reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ---------------------------------
