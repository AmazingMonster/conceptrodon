<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateReverse`

## Description

`Pagelivore::CognateReverse` accepts an operation and returns a function.
When invoked, the function instantiates the operation with its argument list but in reversed order.

<pre><code>   Operation
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Operation&lt;V<sub>n</sub>, V<sub>n-1</sub>, ..., V<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateReverse ::   template<auto...> class...
                 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateReverse
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will turn over `0, 1, 2, 2` and instantiate `Operation` with the result.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<2, 2, 1, 0>;

template<auto...Args>
using Metafunction = CognateReverse<Operation>::Page<Args...>;

using Result = Metafunction<0, 1, 2, 2>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateReverse` with the help of `TypicalTurnOver`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Shuttle`.
When the entire list is turned over, we transfer the variables from the final `Shuttle` to the operation.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several variables in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

We will use `ExtendBack` to concatenate two flipped parts.

```C++
template<typename>
struct ExtendBack {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Endings>
    using Page = Sequence<Variables..., Endings...>;
};
```

We will use `TypicalTurnOver` to turn over the variable list.

```C++
template<auto...>
struct Shuttle;

template<auto...>
struct TypicalTurnOver {};

template<auto First>
struct TypicalTurnOver<First>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second>
struct TypicalTurnOver<First, Second>
{
    using type = Shuttle<Second, First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Page<Second, First>;
};
```

We will use `Send` to transfer variables from the final `Shuttle`.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct CognateReverse
{
    template<auto...Variables>
    using Page = Send<typename TypicalTurnOver<Variables...>::type>
    ::template Rail<Operation>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM1ykrgAyeAyYAHI%2BAEaYxCAAbNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwc5gDMYcjeWADUJltuXo60hACex9gmGgCC27v7mEcnyKPoWFQ3d48PAHoAFQgoEHIQIM4EegHUFAgF/AiYFjJAxI45uJhnVAAOjxvweo2IXgc4MhBGhmGOVgef2BoIO2FUSIY6AsTGQAGtYaCEYCAQcAOqvADudFoBy8SgOBAQeAUByoXgYDkyMtQBzQKqYLJ1rwIIo1yV6ChxiORqL1GIIl2SjFYmDxZq2t0JBGJpKZLLZHO5JgA7FZ/QARal/c0otFUk5/A5xmUWqMYrFEJ03TUGBQKoSYACOXkY61IsfjKdxeIAak08ExovQFOGXX8iSSCIzma52VyMTn84Xo24q8Qa3XMKb8U2m7TAyW40jI1aTmWnfdgMRMMjGAQG1P7vHJekjAdlExgK9jsHwXmCyqB0OR/WnaQDqv15vBOPnbctjTHiGw7SgJwlerI8iCfL3POlroicNp2swbBpruLakjmoEBkGoY/uGDxQUmsGJoumLYkh2AZkwWZXn2t7PsulbVrW9YEvcKFtmh6A9te/YYvejFjqRzEYbOCYLjBbh4URdFfuRlEAPJ2sQOqZMx%2B6sQcwaYI0dDCUJDz7vuUphMAMq2ueWyXvJcRKQIPEMaOn6/NhenxgGWG/sJEliZ5A5SemewUZ%2Br4bmwH4qfGhlHgASkwdBvJeGlabQGJBe%2B26kSAIBwdG7n/k5/z3PSIIHAAKraeCiLQxWrAwskAG5xGB8IRtBPkkROrose6rYlWVFVVcQNX1cQRwzrl7m4YRYllgcABieDEKMzFqaVyTlWI/WDXEGJzQtBCCTOzlxhFxlZXFZJQvQ23zYtk45W5OGQZNrVELN10ELR2JXlqHHIV1pIrWtlXVXVW0nDtozPjm337b%2BBmHidplnRCF0DlDAjoM%2B4N7bd4ZjQ93nJp9WMfS9aOsiT5Y4rJspxDuHXLb163A0NV27ZDmDfc%2B1MILTAnTrD4XwyZdo6eZ7bel2nLWqZCGvADfXM6Dbjc7z7UZVlYVxurT3HqeqMc%2BjmNvY5d0AflhVgh4wDMEikWYEN0pwhBBMEaJz2U35mYKpZil1Etf1tlbNuYHbDtUvzHlPYTqb0cOfF08Jx262eSOuNL8EOj1q0KwNIPELZcf2elmWmZrBza27BzRdpJw%2B9ZDAm7j92AQVcJt%2B3EEWyVY7bo1nftwP4EPU8KovG8pznFcgkTW70ce79HptnXft5X8SdCF4yQFJg6B2woXi0G2F4HMvyknGYz4XwcgQHBojcty7xExzi9zEMACcPEnACymlMEqKp1DOkHPUodaYDlPjZF0GUTxnmSm/ByOMW5Jz3gfI%2BYsf6NH/qqSBbgNDPhvlfMw998rTEcMgAA%2BgFOIBAICfAygoB0lCdxuA3lvNIO8UGH2fJw7G2AFjUg4EsWgnAACsvA/AcC0KQVAnA3DWGsAcBQKw1jnjMFsHgpACCaEEUsTkIARFmBxP6MwkgAAcpiREaAAJwGI0AkUxWx9CcEkLwFgEgNB4IkVImRHBeAKBAHgrRkjBGkDgLAGAiAQArAIMkM45BKBoBRHQOIEQHScFUKYhIABaJIBxgDIGQNfSQOIzC8B3oQEgeB0B6H4IIEQYh2BSBkIIRQKh1DBNILoQIIpFLJE4DwIRojxHaOkZwWSZxYltlQFQA4GTsm5PyYUqQJSDgQA8Ek%2Bgw1thcAWLwIJWglgQCQIk1amz4kQBOck%2BIwApAXxoIfWmlBogjOiGEJolx%2Bm8FecwYglxZLRG0BzIJGjEkhQILJBgtAPkdKwNELwwBMS0FoP47gvAsAsEMMAcQML5pArwPVFFUjMCqA5mcDYGiwhImER0i40RFK/I8FgEZ7o8BuNRaQIa0R2EaQxUYC4RhtFLCoAYd%2BFY8CYBFJZCRGjanCAqo06QsrWlqBGV0/QmKUDyMsPoPA0R/GQCWKgZIdQUVZM%2BBeUwlhrBmG8UNYcWB9UQCWHYPFzgICuAmH4QIIQwgDHKEMfIaQMgCE9XoAowaGCzEGPEQILrsH1DGC0TwbQ9BxrqD0ZoUb/UxtsIm0NsbE1ZvmDs5Yqx1gSEGRwMRpAvG8B8bMzJOTJB5IKUUlZEBcAVK2WonZezBVLB5kwLA8QnWkD0ZILYOIrFbH9JIDQkgTEJA8SIhIVinEcBcaQNx6icQJC4PYqxpj90iMkFwER06Eg1pGT4vxATNGCtCREo5USJlxIoBc1AGyUlpI4E0FgtV/RZKYORI8XArE4i4DiIl%2BAiD2pqbIep4gmlKqUCqjpugL49KYH01Flbq21tGRwcZMSzgHGmQcP9AGgMgeMmBiDUHVnrNOQ1bYZhdn3uCYc45n7mNkHfZczZIBKOAf8kYMDXA8H3KRAtJ5Ly3m/M%2BaQb57z/mAocIp0FW4IVQpGbC%2BFiLkWKfRZi7FUj8DrlVASkZxLSVIkU5SmoIzaX0suIyjYUiWVso0Zy7lyITNGQfcK08CgxUSqlYp2ViGFXNPkKh9pUiMPqoFZaqw2raWOsNcazIprzXmRS9a21cR7VjngM6morq/DutZPmoIrIi0BtIOGuoNWmuZHqzmtN3Q83JtyLG8r8aM19F9XMBr0xxg9a9bmmYw3o0VtLSoub1L8PXs4BR4g/7APAdE7R8DkGNCrM7bBo4Pb2P7J0aQQdw7KCVs3du8D87/Tnv9P6LYC7JBJECARm9tg71ncOU%2BpA0TJnnIE9%2BtgnA/25JYAoWqhTap0ajKMMpMHKnVMCJF%2BVEhFWyGVfFnQIBHFYZwwM9dy2Ok%2BOI5MsjMzIfNuh7Dg48PwOI7bGsnjVzjtbC2Kdh9z7Qd8YSezwTsOt7kKZ%2BQlnlD1tVCk48iAzyOnKYU%2BypXfyAVAo05%2BsF2noVmcwHChFYhDPsuM3y9zaLcWWZKx0mzyAyX2cEI5mluqXNueZcOLzvAfNKB5f5gVnG%2BAipC%2BKyV8EIsIcx8hnHcXVUE6S8YLVNh0ulekVlgQKKAR0Py5YG1da7VVJKwazoFWXDVYm3oH1pRZuBsKJkFrQa6jtdTf19N3WciTc6wIQbTeC29Bq2NobVfs1zaUWWxpeHhnk9W7Tg49O4cI71KMA7KPu3qJ55xgdmAh1DFHdS27/hwNc5EZY09Hiuf%2BnsVeqfvifuBP7WOkAkh/QlMe1wKQViHvTq4P6ddWxJ/eM4D7Q33XVKSvwAJvz%2ByWAdkyEfyAA)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_reverse.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_reverse.test.hpp)
