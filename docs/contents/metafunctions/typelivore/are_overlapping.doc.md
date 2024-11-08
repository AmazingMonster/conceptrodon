<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreOverlapping`

## Description

`Typelivore::AreOverlapping` accepts a list of nonrepetitive elements and returns a predicate.
When invoked, the predicate checks if the list created by appending arguments to the previously provided elements contains repetitive members.
<pre><code>   Elements...
-> Arguments...
-> IsMathematicalSet(Elements..., Arguments...) ?
   false : true</code></pre>

## Type Signature

```Haskell
AreOverlapping ::   typename...
                 -> typename...
                 -> auto
```

## Structure

```C++
template<typename...>
struct AreOverlapping
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename>
    static constexpr bool Mold_v 
    {RESULT};
};
```

## Example

We will showcase three examples.

Check whether `int*, void` and `int, int*, int**` overlap:

```C++
template<typename...Args>
using Metafunction = AreOverlapping<int*, void>
::Mold<Args...>;

static_assert(Metafunction<int, int*, int**>::value);
```

Check whether `int*, void` and `int, int**, int**` overlap:

```C++
static_assert(Metafunction<int, int**, int**>::value);
```

Check whether `int*, void` and `int, int***, int**` overlap:

```C++
static_assert(! Metafunction<int, int***, int**>::value);
```

## Implementation

The name `AreOverlapping` is probably a bit misleading.
This function used to be a helper class for `Typelivore::AreUnique`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

After instantiating two layers, `AreOverlapping` has two lists of elements to deal with. The first list must be a set, meaning repetitive elements are prohibited. The reason for this will be apparent later on. We will check two things about the second list:

- Every element in the second list is not also contained in the first one.
- The second list does not contain repetitive elements.

To check if an element is in the first list, we use a method that is described in `Typelivore::SetContains`.
Namely, we will create a class that inherits every element we would like to check against and use `std::is_base_of` to inspect whether an element is a base of our class.
Since inheriting the same type multiple times is illegal in C++, elements in the first list must be nonrepetitive.

We will implement `AreOverlapping` using recursion over the second list:

**Base step**: When only one element exists, the function returns true if it is in the first list and false otherwise.

**Recursive step**: Pop the first element from the list. The function returns true if the element is in the first list. Otherwise, we append the element to the first list and pass the result back to the function for recursion.

Here's the entire implementation:

```C++
template<typename...>
struct Capsule;

template<typename...InspectedElements>
struct AreOverlapping
: public std::type_identity<InspectedElements>...
{
    struct Detail
    {
        template<typename...>
        struct ProtoMold
        { using type = void; };
    };

// Recursive Step:
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        // `Detail` will stop recursion, achieving short-circuit.
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>,AreOverlapping>::value, 
            Detail, 
            AreOverlapping<InspectedElements..., InspectingElement>
        >::type::template ProtoMold<RestElements...>::type;

        static constexpr bool value {std::is_same_v<type, void>};
    };

// Base Step:
    template<typename InspectingElement>
    struct ProtoMold<InspectingElement>
    {
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>, AreOverlapping>::value, 
            void,
            Capsule<InspectedElements..., InspectingElement>
        >::type;
        
        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = ProtoMold<Elements...>::type;
    
    template<typename...Elements>
    static constexpr bool Mold_v 
    {not std::is_same_v<typename ProtoMold<Elements...>::type, void>};;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArADspAAOqAqETgwe3r566ZmOAqHhUSyx8Qm2mPbFDEIETMQEuT5%2BgXaYDtmNzQSlkTFxiSkKTS1t%2BVy2EwNhQxUjCQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnBDepmAD6BGITEICnujxeZn2DEOXhOZzcyHG6CwVDBz3BBEwLFSBkx8O%2Bv2YbAAdKS0U9xsQvA5jm4mKkFF56GcrOjnpjsbjMPifoxWJhScSAJIMBS/ByYdDYehsQSg/wPZ6U6kEY5PYiYADyADc4gZUqkwsBwSBjqkvNFrshjkiQCACf88FhBLd4SKxd1MVKZYwCPLsILwSYkqynsdwzbASrjgARTBNOjgiOnENJ5MRjk4ph4r68okCskKtPpyNUmnKYioIgAWU86GL6eDFmOXkyRmODs%2BMeO2tQTpZKZjLIbwaH/lD4IA9JPjgAlbqbTK646NTCpEANzNcnmE/nHd3ixxGaVY32kDt5/mC%2BfjE%2Byv3k5PK8uVmt1kep54l8PT04ANg0OME1oEwAOOAB3OhaEjVBUmODVkEXbJzyYZAEDwTBtSNG0EBIAgAFpkDwLYvEIYkG2TVtsM7M5u1tFABHweoxAoiN4VYkt6LwBQ/miJglD%2BVBUXOeiHT%2BJ1fVdc4D09I0719e5SHVLVdWIfVDSMe47W1MQvEwc8OPTIDgVoAyv2/ZNlJ1PV6Q041pNFQ9JXkuVBXPGSemPH1BEfb8tPtXk7S3bMPgrKtUFrWh63OG8CBcv1AwVILeWHNkw2/cZszwa00FFTFVFSYhjmiVBPB7XSPibLieIUfk/m1Hd9J7PtooeJIx1DZNR1Sl5nl/Cx%2BI%2BVd103LEsxzNwHXzfdHNkrzTx8otzPDZ9VTCt8ordWbPOAeLfPDJtDKo9saP8OiCHQO1cqY7IWOWxtzkMp8LrtbjeMGwThLcUTeXE51HG%2BLaPR2vaFXPKzVPUo1/J07wmqeiNeydUgEfDOkGSZbkHOBr14oUNyZpxuTvIIfaHuwZLfh6izDMyxwcoEcZMAKoqSrK2G9JTCwGCrSNLpAN7arYerGvPJHWu68cPw6oN7uCiapqvUk8bJ47gGOSL0C7Y51oi99zjxxKHiltLk3lrHJsvEllZJ/0GzVjW6wBbXdc1%2BFDcLCmAqpk30oOuWxu3XNd2t4kVaWv3Iyyhm8uZwritK6DNfq057qbHnVWqv4hf%2BBrg75NgddfPXNoN22jcpprxbBdrh19yWJz6gAqFvW7bycp1bgAVbAhC71uO%2Bbtvh8H3qIShGE4XOXLtlSB8I4xQOQsa/NBXVYA7eeB3q3jJgqC8aF6m1iGbINaHzjCAgm7FlryTtN3znX/HPZ68E6eyv5%2BKUFoIB3pp98PtkeEl9zyX2vscMBTcYYVRWD1d%2ByBP4KG/gQX%2Bu8AE9AEMAwQoDBAtxwVfKBSUQAc0wLA328DEHIIgGAMAGs0EHwwQwLBBB8Gt1YYQr2JCyEWA4GsWgnAEi8D8NwXgqBOBuGsNYG0GwtiVUhDwUgBBNC8LWAAaxAH%2BfwxIAAc2ikgaD/AkDQGh/BmG0WYAAnBY/QnBJC8BYBIYxpBhFaFIGIjgvAFAgA0Io5Raw4CwBgIgEAGwCDmhYRQCAaBsR0DiBEfknBVDaL/PhP8khjjAGQNaKQxIzC8ElIQEgTo9D8EECIMQ7ApAyEEIoFQ6gOCuN0DMcCQJ1wiL4QIoRyi3GcE1JccJxwhLHCSSktJGSsnHByWYY4EAPAxPoEVPYXAVi8CUQ03hpAIBIGiYaBZ5BKA7NifEYAUgzB8DoJiYgXiIDRG6dEMIzQbicAUfc5gxAbiamiNoT0zzeDRPvJqBgtAnnrNIFgaIXhgB0loLQLxIiwVYkMMAcQoL8AIUcLqOFrjmYLkxL88gghajdOuNEIE7yPBYG6YCPADj4WqRKkoOMLAkXXCMH4vgBgN4ADUMLgU1ISfFpThCiHEFUoVtS1DdKafoJFKBJGWH0HgaIXjIBrFgvUOF%2BEkS0VMJYawZhXGoFUsQCSKqIBrC6IwlwDB3CeHaHoEICxyiVAKBkLIAgph%2BBmIUd1DBBjOpGDMS19Q%2BiTDtdMGodRehzH9cMeIQa5ier0JlFosaljxotTI7YEgOkcEEc47p7jhnJNSekzJ2TJC5JmbgQpiz5ErN8eslYawECYCYFgeI5rSDqMkFoix/gkiSA0JIMwkgAIaASH%2Bax/COB2NIA4/wXBiR/i4H%2BbRFjtGroSJILgCR%2B1/gLaC9xnjvGNq0P4oJWyQn9MuPsqJqB5lxISRwZoLBtRJHwkwY4hwkWTIscSJd2KmJFMujMIV5TRXSHFUoSVoLdBnJafSX5ub80uNEb0m9qohmvvfZ%2B79Bh2xcH/YBmZczdlxFOJCMwDa1nns2dsh95GyCRMOQskAOGP0/qMERrgPiaC0Eudc25oLXmPPxaJ95nzvkOHxf830gLgXdPBZC6FsL8VYGZUYFFri0WyUxd0nFiE8XwsvkS0FJKyU3ApTsVx1LaUKPpRkTATKWVGnZVQTlCgeWYD5QK%2BF4GRWVKg7ICV9TGkgDOQR4w8qbAkrNWque2RNXarOrqqwlgDWiONaa%2BAFraiyWcBAVwSaZiOrKHG11RRsglbSG6%2BoaaXVBvy4w0NrRw1esjQVhoManUVYTf0GrKb5jlfTTm9Ymxs3LJsXmrpR7ODHA43hrj6siMAeJBoatwG62Lpo34ltbaO2UFzXOhd/7h1JD3UkJI/gR1jp3Yew1nAT0%2BNoxsgJwTQnhLvaxp9bBOCvrGSwBQ2prTalW1ycY%2BStvFLA7ICDQXqnyBg2FnQARSCIbaTwFDs3HscD6WEy4gyqALeICwQHwPQfg5CuMUjjGjmUf8P4XbTb6MMUfcxg5dO2Mg4NPVIjfwIcEE/qTtJ5yBNxCE3ch57zxPS4%2BV8n58K5OCAUyCnTmAIVQrEGp%2BFGmWU2d4Lpno%2BnQWGcuDsBRpmZ2uIs486zVKTX2d4I5xliKtNuZZx5pg3LeX8sYIKuHgWJDBZqcjqVaOotyr1QquLuW3GJcZpwScto0v6sNdlrA8XOtWqKzamrZXFiNdq1Vj17XKu%2Boa4G7PIbE1l6a1GgQrXK/xtmANuvrfU29dG1NhQWbKnY4e%2BhjgJOyfpKByDnsVPMQ04gDWog23lmrL26QVt7aRhdpnSdiL/7GcJCMTu4xjOkhrsHz0jxthT2vebd2gIf4ANcEsTdqxf4khcH0TMGd/gcdD6X023NeTT9j0z0VFSBVJMhnBJAgA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/are_overlapping.hpp)
- [unit test](../../../../tests/unit/typelivore/are_overlapping.test.hpp)
