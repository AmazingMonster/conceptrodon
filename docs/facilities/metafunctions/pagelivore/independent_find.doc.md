<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IndependentFind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-independent-find">To Index</a></p>

## Description

`Pagelivore::IndependentFind` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
IndependentFind
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct IndependentFind
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto...Args>
using Metafunction = IndependentFind<IsTwo>
::Page<Args...>;

static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

We will implement `IndependentFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct IndependentFind
{
    template<auto...>
    struct ProtoPage
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<auto First>
    struct ProtoPage<First>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    ProtoPage<Others...>
                    ::value != -1
                )
                { 
                    return 2 + ProtoPage<Others...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAOyJpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAMzhyN5YANQmO24EAJ6pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fI43QWCoLzenw%2BBEwLFSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc8dq8PuNiF4HEcAJIMLDXVmMAgAMXC6DBJkSVg%2BRxFR0h0NhmHhaMx2OpYNFRzpDIIRxJqCIyiYwClwtFAosSuajmQuIE40wqlSxCN6BAIBYTAA1rdMsAIug7vDMgAvW4EHEANzEXl%2BBoAtFwBQARU6GmNx/l6kXipEotwy1BHHnEcag5NG%2BmM9Wa7VSs45vPygsG/UFxWzE1mhgWq02zNHYPeMP1/WChWKwcikz%2BKz%2BaMQJZHcM4wH2x0um5uj1es6%2B/3595DocGgfb7d4KjN1vWo5QInmABsV5JZLwFMwVLclYD1PtXdDSyWe/3g9rpIIdYGCODQ4xORJYw%2BH9f1FOolGgmDwMNACgOnKMdnjCCEJ3CDJ2w8DYwwn8EyIqCC1TSVpXRLMX1II4OyETA0FZOjMyJAB5AgEHiKkaS3UVlWLYgNVQLUdXhWijkY5j0DozjuNzC9q344dBTrFTB0be9j0hNt6OozsQx7DTFV3Xsd1HEcJynGdqVtednVdPB3TJVc3HXVc%2BMQpD8P3Q8dMta1fO3c9sTMa9wtvclkUfCS8FzV9sHfIyv2CnDkMwQDiGA0CMIIpMTMQuDfn85iT2INLB1CjErxvUlospeFpIEPk3xAD9MFS8zf3/TLUPQzDIPBQqYOKo5SvNXSgu6/cIEq/cS1Est4XknilK87zt2S7sjjAMBTmjND5tFb8Zu3WtjqHFDsqOMwTksNVhNLcSzlWxS5Q2zbB220MwMu/KyJG39iv%2B3qsuAyM/qws7VOs/CSKFDSEYKxUKJiqjZQxd5gFJKFOV4n8vEyIw1TLP5DsWsTyzcbHcbYQRCQ%2BxMoKw0jhoAegAKm5nneb59mwS5nmjgAFUfAgFCOXmBY%2BIW%2Bfl7mZeGr4GAOLxjnhZjNlSCXNzBNH0w7JlN0E1UmQUEWAHdUDBEAjlSLwYlobS5xAGJUE8G4yuaQR4SZcmDtunFd1ZxH9cRSjUWool3mIYACY%2BInwmAI4AFlMqYKgvFVhpyeZDl2SwQQeVZP2Letzd7Sp%2BFY/j9bmeGrTkBufElFaCB0%2BaLOc%2ByeENDooJbronYXh%2BsMdkIw6zG/Nmm5bgl4gIDuM%2B7hxe7OfujkHke2o6gOJ7QmfEY4FZaE4fxeD8DgtFIVBODcaxrCVNYNjDMwdh4UgCE0E%2BVidAJJAYg0JILgiQdgaH8BocKl4zAAA5YH6E4JIXgLAJAaH7lfG%2Bd8OC8AUCAfu39r4n1IHAWAMBEAgDWAQB2BByCUDQNCOg8RIisC2KoWBl5wyXkkEcYAyBTRSAxGYXgd4iDEDwHaII/BBAiDEOwKQMhBCKBUOoIhpBdBBEtg8VInAeCn3PpfH%2Bt9ODsXRDQo4qAjzsM4dw3h/Ct6ALuhADwjD6A2l2FwJYvBCFaBWBAJADDUhMLIBQCAgTgkgGAFIMwfA6CQlzJQGIRiYjhBaBcXRvAUnMGIBcdiMRtBMUIZ/Bh9MCDsQYLQdJaisAxC8MADMtBaB4O4LwLAjojDiGqfFQpeBAyPiMZaJi6Itif3CJCM%2BajnYxAeDkjwWAjH3DwKglppA%2BnEHdkoaMUJDDAGdkYH%2BKwqAGHjgANTwJgS27F2QZMUcIUQ4gFHSPkEoNQRiNH6B2SgR%2Blh9B4BiHgyAKxUA62yM08MgIDqmEsNYMwWC1niKwACyc3QenOAgK4KYfggihHCEMSoIxCgZCyAITFegijEoYPMYYCQgh2FRY0CYbRPAdD0HSteAg%2BitCpfimlthGWktpYy7lixPGrHWJsCQ%2BiOAX1IJg3g2CjjWK4TwvhAjHFnlwIQEg90P5eK/gclY3EmBYASMi/%2BkgdgYgAJw7ESJIYBZhJCXnQf4S8VrEEcGQaQVBH8MSXi4JeWBVrYEBv8CA/wNrLyyqMdg3B%2BD9VEL8eQ/xlCzHojoWE1ArjmGsM4C0FggZEjhiYLiAwJMuBWoxFwIBIj8BiIkXoJ5siHnSCeco15ajdAxK0UwHRLSpUyrlcYjgpjqHogsUefNhbi2lp2VvSt1aNBnhcUEtxOrp7eIOSQgJWbV3xAzeEtxIAp1FrxEYCtXB%2B40FoPEvBEAklqKyWkm5T6cl5IKQ4G5JTOTlMqUYmpdSGlNJuW0nZnSb74FJGvPpzSb6DOQMMm5Yy6hGKmTMi4cytg30Wcsz%2BayNmYC2e03Zyct1HO1AoM5FyrmMBuU2%2B58jW2yHbaom%2BXaPn7KhVYH5UykVApBeaTg4KCCtWjFxmFcL4gIv6YClF7K/DotZAK4IrJhUErSEShoynyUNDU7ytlDROVMryFiuThmhW4oWOp2YkxmX5EFXMSz1LJVitfi5iZg6Y2cHosQAtRaS1npThWqtQCNV1u1R4vVPjf6kCNSaygUqvU%2BsrcAxIEbkg7EkI67hQQh2xtsPG6LSb4ApqoTQg9u7gksLYHm3ztiWAKEDKaQMwXJTjFrVqhFjbZDNsY7cljbyQA7FID2vteiPWebUdg0d5jLE%2BZYPVxrzXWsxXGMuyra7dg7Ci1ulNh792hP2wkJrqRUg3Ba1am4bWCAtzq62uJPFEnJNSTkl9L3cn5MKV%2BrNpTf1VIg5gWp9SxDAZWaBjpWHWndOg/0tR8HEMrOQxMm%2BaG0mYYWeI3DvB8MZEI9sjppHE18GOZR85lzrkrPo3IiQTGlEvNYzoIbHHjDfJsLx%2BA/GGjNPZnOcTlhYXyvhRImTyKDPZBcEpuzpmcXlGc4S4o2RtOaeyHp1ldR6VGeU2LjlFnZc8tZfyqXBvHN65FSsBQL8JWio84Yqb3n82Laa52FblJVQQE1WInVnjN2JsNZgY1IxkUTKSyAMwladg7H8JAkB6CI%2BJEDdGu3OCCsEINaQc1/hrX%2BFgeFK1kgrVgNtVwYbEydi26wZwH3vipXCMTxX5PRWVhrMyM4SQQA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/independent_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/independent_find.test.hpp)
