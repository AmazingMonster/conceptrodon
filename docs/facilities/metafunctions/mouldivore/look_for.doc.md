<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::LookFor`

<p style='text-align: right;'><a href="../../../index.md#list-examinations">To Index</a></p>

## Description

`Mouldivore::LookFor` accepts a predicate and returns a function.
When invoked, the function returns the index of the first argument that satisfies the predicate, or `-1` if it cannot find the argument.

<pre><code>   Predicate
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Exist Predicate&lt;Arg<sub>I</sub>&gt;::value ?
   I : -1</code></pre>

## Type Signature

```Haskell
LookFor ::   template<typename...> class...
          -> typename...
          -> auto
```

## Structure

```C++
template<template<typename...> class>
struct LookFor
{
    template<typename...>
    alias Mold
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<typename...> class>
    static constexpr std::make_signed_t<size_t>
    Mold_v {RESULT};
};
```

## Examples

We will find the indices of `int**` in list `int, int*, int**, int***` and `int, int*, int***`.

```C++
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

template<typename...Args>
using Metafunction = LookFor<IsIntDoubleStar>
::Mold<Args...>;

static_assert(Metafunction<int, int*, int**, int***>::value == 2);
static_assert(Metafunction<int, int*, int***>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||(++counter, Predicate<Elements>::value)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right element is found.

If no element satisfies the predicate, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<template<typename...> class Predicate>
struct LookFor
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||( (++counter, Predicate<Elements>::value) ? true : false)) ? 
                counter : -1;
            }()
        };
    };
        template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQgkhqkAA6oCoRODB7evgFBaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHOYAzOHI3lgA1Cbbbl6OtIQAnifYJhoAgjt7B5jHp8hj6FhUt/dPjwImBYKQMQJObiBILBmAhBCuKUYrEwADo0bdDvsmAoFIdlMRMPhRODtndHmNiF4HIcQqhUABrABiJH%2BJgA7FZHoduYcoaCmCTIQikWw0SjsPQ2IIFH8uTyKVSCHjiKgiABZTzof4844c7U6%2BVNRzITECMaYVQpYiHJjnVCHABuYi8sLlBt1nIe7vdJgArFZfQARCCLQ4AWgxXxAIBYTHpmAA%2BhlgBF0AmCBCMgAvRMZ0n67089mewuFqMxuOJ5Op9OZvA52uk01eQTxD1hrjswMnEul90EghrBgFvs8iBi9luScQQ4QazWNAtoFkZWEvDE2GnCXAxgEGWk6NO7yYUMnRm8ylvECHKhiJSLU/bc8j0fN1vW68dnsv71dkM/7ku2/N1dW7bZe3dPkYThYVmFFNFtylPdZS9HkvAyIxDg1Wh0HeQNlVVVBsK1LdJV3BQJ3zcDWTZMDPX%2BAB6AAqFjWLY9iGMYtjDgAFUwMZcTYzjHmY9ixNY4SASeMxdgYfYvCOCFzjoa4UP%2BKCBU3IVETgt5EN3FCFWpABJBRjMEQNVhiehemIf5rxSLxrPXQ5yzwBQk2RCF9MEUhDnCAgWIxYsgOox51OBflBXhHTkTFB5iGAfcyQedDwmALDMCaKgWwcLI8JpOkmRZU5TPMghLKcmzxhQ6NiIhBKksou4wqkmZjQTbElBaCA1Sypgcrk%2BoIQCvyAqYsbBBYybAqCg8QCPF08JOfCzEWYCHna9dOpxeICF6/rBrygQRt8/yppm1jbkPZ03hWlbwy4dbwI4ZZaE4X1eD8DgtFIVBOCnSxrFc1Z1jumSeFIAhNFe5Z6RAX02RRbYAA5/DZbZ0Y0VGMYATm2fROEkXgWAkDRkm%2B37/o4XgFBAZJoZ%2B17SDgWAYEQEBVgIRyCHISg0BBOh4kiZFOFUNGw38SRDmAZATSkFEzF4NciGIPB0D0fhBBEMR2CkGRBEUFR1CZ0hdCCAB3YgmBSTgeDej6vphv7OAAeXOHnDlQKhDnF/xJel2X5ckRXZw8QX6GtHYnt4RmtGWCAkAFlIhbICgIGT1OQGAKQzD4OhlzpiAYmdmJwmaK47d4MvmGIK5XZibRMAcKvSAFpDXYYWhK9NrAYi8YA3DEWg6e4XgsFjIxxF7vACTyh1%2BOdi1m/OTZIYC2pncuGJrbrjwsGdgg1dJsfSAX4gYnSTBA2BQxgEuIwYeWKgDCSgA1PBMAt12dNbrXhFEOIfW/8jZqGdubfQd8UDzksPoPAMQ6aQGWKgFI9RR5hi%2BCtUwQNLBmCpufNWWBEEhi6M3eoLgGDuE8O0PQoRwiDAqMMAo6RMgCEmH4ZhRQshzCGAkIIdgyE9HGK0aheR%2BG1EEQIWy/R6HzCYbYYR7C9AzBaDwxhfDlgKFBhsCQDsOCfVIJTXg1NfYSyljLOWhwFZmFnLgQgJBjgQ0WLHJ%2BywECYCYFgBIJD4aSG2CifGbIkiSDMJIfw5NfT%2BFxoTDgxNSCk22FwFEgR/Ao1xijLg/hfSSC4L6fG/hDHO2prTemUMn4s3ZonTmHtzh8wzqgCOwtRYcGaCwB0bIwxMExAYTCXBcYoiSb9FWJB1aa1kDrIB0gQFKDAabXQecrY2yrnogxRiXYcHdtzc4XsfatPaZ07pd8rH9MGWHBpKdI6OO2GtFxTME5J3OanOpmdI4gD2R0rERg%2BlcGSDQWghdKAl1NjXCurcQV1wbk3Fup9267k7t3Z2fcB5D1oCPVuE877T1%2BvgOejgF6jyGaoFeQJW4b3eqbbeu8rj702L9I%2BeAT6Q3PpfJQN9J733SuUl%2BTB36f2/r/U%2B/8Jl6ymbIUBJtfrzMgY/bBVhYHb2Icg1BWR0GYO2IGWV1g8HGIIerReSDSHHT8BAVwSigh0LKLwvQhRWHZFERw1ILD6hqIWOI7oUjFH2uURIo10iXXyJUSI3IDrA3%2Bo0SsNYOinoxNWUUzgNpiBtI6V0z5GU%2BkDJRBoWx%2BBVZXJjmUu5biPFeMoHouJCT%2BkaEkGyPJbIMYhLCTkwpptim2FKXHZmrMOZcx5s8x5kcRZsE4K08xLAFAOhNA6dNMIxjKxzSMjWQQhWAJFQbeQMyJU6BAATRZtsx4rKdi2t2NSlTewTSwUd47J3Ts0mMM5jSo4yW2M4gt8cWYPIfX2h9C1kApBSAmKduMEwzoIJ1RNUt87/PiEXIFv1wU90hvByFZDW6wsEPCnu2LMD90HsPUekMMVT1pePWegj8VLyJcgVepLWzkt%2BpSiuNLD7H1bsyq%2BbLMWcruXwV%2BCgP5fx/owP%2B4yV0SFFYbDd4Dt3SuMDAmwCr4BKrQZwBiUZNW4PwfEQh%2BqSECKNRQqhwbaGULDdap1WQzWOq4SUWRVq3WSIaJ6oz9nfXCNM/wpzNCPOzFs%2Bo3REawb%2BfJbGo9HBz2XonY6G9QI70QDsbm6OL6O0PlIO4zxwwSHkvLSAMw/TtjbF9L6KtPzsbbDZKk5tVNOAlIZq40gvizDJK4Nc/w1zcaBDMOEtkMTtiHqqzTV9sMYlK0q8Y6rg2UvnwyM4SQQA)

## Links

- [source code](../../../../conceptrodon/mouldivore/look_for.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/look_for.test.hpp)
