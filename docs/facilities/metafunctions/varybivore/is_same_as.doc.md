<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsSameAs`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-same-as">To Index</a></p>

## Description

`Varybivore::IsSameAs` accepts a variable and returns a function.
When invoked by an argument, the function returns true if the argument is the same as the variable and returns false if otherwise.

<pre><code>   Target
-> Variable
-> Variable `same as` Target ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSameAs ::   auto...
           -> auto...
           -> auto
```

## Structure

```C++
template<auto>
struct IsSameAs
{
    template<auto>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto>
    static constexpr bool Page_v 
    {RESULT};
};
```

## Examples

```C++
template<auto...Args>
using Metafunction = IsSameAs<1>
::Page<Args...>;

static_assert(!Metafunction<1.0>::value);
static_assert(Metafunction<1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto Target>
struct IsSameAs
{
    template<auto Variable>
    struct ProtoPage
    { static constexpr bool value {false}; };

    // This partial specialization will be chosen
    // if `Variable` is deduced as `Target`.
    template<>
    struct ProtoPage<Target>
    { static constexpr bool value {true}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v 
    {ProtoPage<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAnKSuADJ4DJgAcj4ARpjEAVykAA6oCoRODB7evgHBaRmOAuGRMSzxif7JdpgOWUIETMQEOT5%2BQbaY9sUMjc0EpdFxCUm2TS1teZ0KE4MRwxWj1QCUtqhexMjsHASYLCkGeyb%2BbkxeRADUACrNwJgEJ9gmGgCCs8ReDpcAkgpCrEw7xerxMAHYrG9LtDLnsDkdMCczhdUJcAGrNPBMWL0J4gmGXD5fAiXZTEVBEZRMe74mHgiyEpqOZCXNAMWaYVQpYiXWKoTyXABuYi8mEu9KoYiU4IAIicGbL5SDadCAPSqm4IPAKS4pAZY2iElJ1A14ABeTF6lwA7nRDfFWQh0owVZd1Zc8FRxQA2DQY4hYnGI30enVYdBfTDoS5MHUmX23Yj3R6%2BgB0rrhh0tiNOeKhMKJ3zJFNQVJpp0TybzrwJ9MZlrwLLZHK5PL5AuF3jF9IIn0RYLl/gVA6Vbwz%2Byzx1O5yIqbnr2AxEw%2B0YBAU1YJXgyRlJ1O7/hlpPJlL3SIXS5XggUc/T/meQ%2BV%2BehmYRSJnqBvryT67vrtmDabAQW25GMUV3e4AH1BXFJ9xQhYsT3LNwv2Aa85yeEAQE7UVFQfMcRzw0E3lVAAqMjyIo1UQVIsjrmwIRrnIqjiIo1iSOYojXhfbM3xRT9v2rLcImAS4AFkHiYKgvAYeoBHFA9fn%2BQFgVOLhq0wssc2Q78bzxQiQX/ZkINjJQWggMAwHEpopJk3okS4VMNAwrCRUwFZR3eJlG2MhRTIICArMk6TZIYeznOwtz5Q4NZaE4ABWXg/A4LRSFQTg3GsaxCQ2LZuzMapeAITRorWABrEA4skRzJC4MF/A0OKNDMb1vTMAAONr9E4SReBYCQNA0UgkpStKOF4BQQEGorkui0g4FgGBEBADYCBSC5yEoNADjoBIokBThVDa70AFpvUkS5gGQFkpFTMxeCjQgSDwdA9H4QQRDEdgpBkQRFBUdQZtIXRkmtYgmBSTgeBi%2BLEuK1LOAAeQuNaSVQL1DpOs6Lquy4brMS4IA8bb6B5cxVkK4q1ggJAtpSHayAoCBafpkBgCkMw%2BDoPZiAmiBYjh2IImaABPSHeEF5hiGFhHYm0Oppp4UgtrYQQEYYWhRcBrBYi8YAzloWgJu4XgsBYQxgHELW8CXepBUwI2Us5OoLh2RWIj2WLAdoPBYjBqWPCwOHezwPrjdIO3iD5JQZX2c3vaMSm%2BAMVC0TwTBrQR40ksVt7hFEcRvtzv61Dh4H9HNlBMssfQfYmyA1lQFJeiN47ZnQE4ZVMSxrDMEaI4DLA64gNZahClwGHcTx2j0MIFnKSo9EKTIBCmPxkiX3ohnn0Yam6eWGjmVe9FH3p%2BhaLeRkSGpD6nvJr4GC%2Blivkecu2CRoY4BKhrh0bLgx07zqXWulVfGEBcCPVJvlLgKwKYzRWGsBAmAmBYESMPUg5VJD%2BFTIEfwYJJAaEkGYSQvoGremCJ7HqpA%2BrVFTN6Lg3o2qBDavQyqXA4o4O9N/QGo1xqTVINNLQVNFrU2WsjdajNmYkz2mwTgzQWCCjBMdJgrIDA7i4IEVMDlHb4CIAPV6sgPoF2kEXJQJdAa6A5qDcGYsP5f2GrwUaSNVoXEuGjGMxB5GKOUcgVRIl1GaMcgTImdMSbinymYGB/DE4iMkQkDaTNUDE1GHIhRx0fHm3UVwQaNBaDc15vzQGEsRZi1IEUqWMs5YOBKcrVcasNZw21rrfWhsSmmzjjsFK%2BAbaODtg7e6qhnZ7BKe7bocNva%2BxFgHDphUAyh0VhHKOmAY5myMPHUAcCk7UgUKndOmdGAlNzoYr6xjZDFwBilCx5cE5dysNXcZQ8G5NyyC3NuHcbk9z7gkAe9t4Ajz3mPCArgj7JFnmUS%2Bi90jL2yLfNeqRIWbznuC3ePQD4DGBV0FFAgz7zDBU/Y%2BN9ciwv/OfRFeLoHrE2G/clns7E/04O4zxSiVHm1xhorRBNwG6LCeTKJcCEFIJQZQD%2BlDqEaIIWCdhYI6qEOITVLhI1OC8KmtE4RSAVoo3ibE4g0idhyKxiwBQgoWSCn8QiWY90dFPReskQ5%2Bdjk/XkKY85OgAikCsRDY2tjYbcMRmI1GXo9XnQNUaoUprsyzCCYkkJCRuX%2BEiQI2aMSo3001cmkmWFkApBSFBdREEzUEGMh4s6nNckJHyQLIWUsSllOlrLeW1TEkqwIHUzWnTMA6z1mIFpYc2mrOmaQLp%2B9elwydsgF2wzBCjK9j7P2wsplB1mSUhZzpllx2EonKgydtlpwzlnA5Bi7USBOb9J1pdXW%2BMrt3O5tdfmpSeUBTgqo26XtuRYXuDj%2B7PR%2BfXDF%2B9nCAonui0FiwF7r3hVkdFG8siP1A7%2BkK2L0Un1RSS3FsHiWtBhfih%2BpLQMv0pV9L18qHH0sDZcYNxqw17AjWAy1kCeUJvgaQRByDRhoIob1EAZgNH%2BH8HFRqNUBo8bBAwoj8Mxq2D4QxsqIBJBxWwXFNqzVAiSECHVXBXB/BdQ4P4b1CrxNSa03dUTPDeWCLWBHDIzhJBAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/is_same_as.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/is_same_as.test.hpp)
