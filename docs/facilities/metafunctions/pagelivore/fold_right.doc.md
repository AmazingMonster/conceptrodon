<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldRight`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-right">To Index</a></p>

## Description

`Pagelivore::FoldRight` accepts an operation. Its first layer accepts an initiator and returns a function.
When invoked, the function right-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::value
   &gt;::value
        &vellip;
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldRight
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldRight
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        {
            static constexpr auto value
            {RESULT};
        };
    
        template<auto...>
        static constexpr auto Page_v
        {RESULT};

    };
};
```

## Examples

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

template<auto...Args>
using Metafunction 
= FoldRight<Subtract>
::Page<Args...>;

static_assert(Metafunction<3>::Page<1, 3, 4>::value == -1);
```

## Implementation

We will implement `FoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldRight
{
    template<auto Initiator>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...Variables >
            struct ProtoPage {};

            // Base Case:

            // Fold once.
            template<auto Variable>
            struct ProtoPage<Variable>
            {
                static constexpr auto value
                { Operation<Variable, Initiator>::value };
            };

            // Fold twice.
            template<auto First, auto Second>
            struct ProtoPage<First, Second>
            {
                static constexpr auto value 
                { 
                    Operation<First,
                    Operation<Second,
                        Initiator
                    >::value
                    >::value
                };
            };

            // Recursive Case:

            // Write out the last two folds, handle the first two parameters,
            // and recurse using the rest to obtain the initiator.
            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {
                static constexpr auto value
                {
                    Operation<First,
                    Operation<Second,
                        FoldRight
                        ::template ProtoPage<Initiator>
                        ::Slash
                        ::template ProtoPage<Others...>
                        ::value
                    >::value
                    >::value
                };
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };
        
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwapK4AMngMmAByPgBGmMQgABxmpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuO3sHmMduTF5EAHQPx9gA1MgGCgrPAPKp8UwNTxMGgAguNiF4HM8AGKedAAJTwwAQBCBwJMAHYrCDnjjnmd9v9LicbkRngBJBhZf4kQHY3FgiEEZ7KYioIjKJjAS50nEYrHA3GC54MyFCd4IVFC3F8yVSoX4i5XEmoB53ABqLTwTBi9E%2BtIFcsFIqZLLZqA5XOeMvRABFjvzZYacQB6Z3PCxMJTPa5KECox1O13Q2HPASbO4Bw0KwlK26oZ4a4hanVE7CRuXG5ms9mcoluRPJ%2Bj6p3SzHpkuzRzIV4CcaYVSpYjPZXPABuYi83INJcFfO%2Bv2I/2yVwL2vopHJlMc1OITxAIHb3kwVtt9vLQoxdqODp5gbdMNo6DxAHc8OH14Lo4diXHoXhiOMJy2hJg0Ax0MWe5nTTmuVcofej7PC%2Bb4fkcaa7oaMqQV%2BzRVjWDB1g2TYtounZWjBJZ9hePY/H8AInABD4EKQOElnhg4EW4IECOgpGYT2UoUlSRCzgxjFzguHZdoxUHgfOaE8bxvKrtuZErluO7dnuzxwq%2B6yZK2y4%2Buw/rsbiQYAOpJjsoa3HiCDLu8TIEMe8b8IeCgTgghjoPQBnLjQxEnvGqQtKwmA7A%2B9HSYaQa2c8xDyQ%2By5eJkRgOYFmDjHi8aoDEzThJF4QsSQEbqTiV55i2RFAc%2Br60U%2Bcaql8BCGQ%2Bn4VgQ4KQj%2B5q5v%2BgEkcBBXvhOpXlQoqqVU60G%2BbBQ7Vm%2BSGNs2t6CeJvZlhlToUUOAiNcRPnCVKc1UTRbWTT2B7woiyJbSW85ZVmZoWnmzHTqxPUrUK85ip6EozYxR27ASul1WdVwdfEXWPOBB1OgJ3EA72/FcUuIPSmDE1PaWkniZua4MYjYnIwxWWxvcDzAsAQW7IwBAKNduJheEwDMrmVpHDawHii95yEidv55jjeNsIIv0Rv9qPSSj/JQbuGM3ljdys5g%2BMcz1pMRWdVM0x9DUnGLEuE913MOqJUnOgAVLrev6wbzqojrevPAAKtFhPPPrRsgibBsO7rttoiCQvXLewJFaSVj/SCmZCF4CWDg4/rTdJlZnghI0oeNwO7n2AoALTuhJSNopranAm7yqqsCxDAETvvAtL5MALKeUwVBeAwDjZBhaLU8Gh4IkiKInAHQdMCHRfzp9Sv55zgI86iEfIAA%2Bp6SitBA5fNFXNdUUcnF924XATkcE6SJxgly8cNOJ1wSz2hwKy0JwACsvB%2BBwWikKgnBuNY1jCmsGzLuYRw8KQBCaCfKwANYgHPpIO4GhJBcHREcDQ58NBmH8P4MwiREj6E4JIXgLAJAaCCNfW%2B98OC8AUCAIIP8b4n1IHAWAMBEAgDWAQVItxyCUDQHsOg8RIgeU4KoRI/hE7%2BEkM8YAyBqxSDuGYXgmB8CsTwOgPQ/BBAiDEOwKQMhBCKBUOoUhpBdBr2PIOVInAeCnwvlfX%2Bd9OBfFuPQpkqAqDPC4TwvhAihHPBEWYZ4EAPAsPoE2D%2Bh9eAkK0CsCASBmGpFYWQCgEBQnhJAMAKQKQaC0C8oQiAMRTExHCC0AAngY3gGTmDECyV8GI2hXwkK/sw9mBAvgMFoDkzRWAYheGANcWgtBCHcF4FgFghhgDiAafeMpeAlIdNvvWeSOxcnkEEHUUxtA8AxEHIUjwWBTHVTwBgzppAlLEBiBkTANpdi9PmUYX%2BKwqAGALmqPAmBjx4Wvl/ORwhRDiGUU8tRahTHaP0L0lAT9LD6AWYQyAKxUCpAaB0xO4wwI2lMJYawZhcE7KTFgYFEAVh2CGc4CArgph%2BDXqEcIQxKgjDXkULIAg8V6HJQ0eYwwEhr0xbXAQfRJieA6HoJlDRWUDCJQsUltgJhtHZfkRlQq6UkoZRi1%2BmwJBGI4JfUgODeB4Lsdw3h/DBHCJAW4iAuBCAkCtGYT%2BSx/FnJWIZJgWAEjotIIAyQRw7gAE4jjokkGAswkhAjQP8E6lBHA0GkAwZ/O4/guD%2BESE6xI4bgFcHPi6/wSrTF4IIUQ7%2BZzyFUOCTQyxDDInRO8ewtgnAWgsFbOiROTBXgGAilwJ1dwuCgPEZIkg0jZGyAUa86Q7ylCfM0boFIuimD6M6fKxVyqzEcAsXQ/SNjmzEDLRWqtbxekuPrY2jQ7jPFhO8Uao4ZhTXptIUEkJqAvHxEYVEs9O6RilvLYnFdRg61cCCIk5JlA0maPydkqZ37CnFNKQ4KZlSCY1LqaYxpzTWntKmd045Wxb74CCrXEZpjxnIFuFsL%2B4Qdhn00fMxZ2SVkIf8UmTZX8dl7KUIcnpRgTmgGPXwS5Chrm3PuVMp5nalHdtkB8jRt8B0/NOXCqwAKCNotBeC7IkLoV7xEwipF8QUXRXgBiuoWK/A4vfFSgl74JWLDJRkClOQRX4rSEZ2lfL6WcvU8yxoQqdPdA0zy/TArZhsryGZ9zvLyjWcPqsdYsr/N4fHcmzg87F2VurauutDbQHuP1axPdfij2BItZgK1IxbV4cDcG%2BtYD0TxvRJAyQnq%2BFrwnSm2waaAlkIodQ2hVjL0FrYRwjgpbHEsAUK2asrZYsXHGM2g1KL23yJedxlR8he38Z0CADeQ6R2GP9aFzReDp1WNDLYjr/Cus9bbP1wkMUPHXvCXuo4h7asnpQCd7xzWbsjB66kVIY8%2BtOrHgNggE8F18L4HQd9qT0mZMKb%2BoHRSSllOA2eqpYH6mIcwE0lpYgYNbLg3RkjpAkNDNQ5o9DmGpk4dmfhhZSysnEbWWRqZlH9k0eOWTDNFzOQsZuXc34DzeCcfGxIHjqjptfLm0J4w/ybDidU3fKTtZODOmhX8%2BFlhEUquRdIlTIKnN2ZcNp0zehCW%2BcldSiz2RHM0uyK5hlqvuUOc14y2z5u5hWd12K/ojnvMm7lQFt%2BruQsmNW%2BF7bzxdu9YOzsI7iXDW%2BIu%2Ba0glrrWUHlblkAZh61HCOOfGB4CsFJ/RBGpN3v8HVeIRH%2B159nXn2SL6yQTrIGuq4BvPDRwve4M4Ga498qxHZ4b7ny7KwdmZGcJIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/fold_right.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/fold_right.test.hpp)
