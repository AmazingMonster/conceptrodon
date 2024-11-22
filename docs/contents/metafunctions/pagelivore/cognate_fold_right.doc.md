<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFoldRight`

## Description

`Pagelivore::CognateFoldRight` accepts an operation. Its first layer accepts an initiator and returns a function.
When invoked, the function right-folds its argument list using the operation and the initiator.

<pre><code>   Operation
-> Initiator
-> E<sub>0</sub>, E<sub>1</sub>..., E<sub>n</sub>
-> Operation&lt;E<sub>0</sub>, ...
   Operation&lt;E<sub>n-1</sub>,
   Operation&lt;E<sub>n</sub>,
       Initiator
   &gt;::value
   &gt;::value
   ...&gt;::value</code></pre>

## Type Signature

```Haskell
CognateFoldRight ::   template<auto...> class...
                   -> auto...
                   -> auto...
                   -> auto
```

## Structure

```C++
template<template<auto...> class>
struct CognateFoldRight
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
= CognateFoldRight<Subtract>
::Page<Args...>;

static_assert(Metafunction<3>::Page<1, 3, 4>::value == -1);
```

## Implementation

We will implement `CognateFoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct CognateFoldRight
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
                        CognateFoldRight
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwapK4AMngMmAByPgBGmMQgABxmpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuO3sHmMduTF5EAHQPx9gA1MgGCgrPAPKp8UwNTxMGgAguNiF4HM8PMBmDsAGKedAAJTwwAQBCBwJMAHYrCDngTnmd9v9LicbkRngBJBhZf4kQH4wlgiEEZ7KYioIjKJjAS5Mgk4vHAwmi54syFCd4ITFiwlC2VysXEi5XCmoB53ABqLTwTBi9E%2BjJFStFErZHK5qB5fOeCuxABFjsLFaaCQB6d3PCxMJRQ33sTGut2e54I2joZ4CTZ3YOmlWktW3VDPHXEPUGsnYONK83sznc3lktxpjP0Y1u%2BW4nOV2aOZCvATjTCqVLEZ7q54ANzEXn5JsroqF31%2BxH%2B2Supf19FI1NpjnpxCeIBAPe8mDtjudNbFOKdRxdApDXvDkYIAHc8DGd6KE4dycmw3hiONZ52hJg0Ax0BXB3nLYWfJXHCz6vs8H5fj%2BRzZkepoKrBf7NPWjYMM2rbtp2a59naCGVsON6Dj8fwAicIEvgQpAEZWRFjiRbgQQI6CUbhg5yjSdJEEuLGscuq69v2rFwdBK5YQJgmCluB5UZu%2B6HgOx7PEin7rJkXYbtcSggEG3GEqGADq6Y7FGtxEggG7vGyF4pvwEYKLOCCGOg9CmRuNDkUS54pqkLSsJgOwvsx8mmqGjnPMQykvhuXiZEYLlhZg4xEimqAxM04RxeEHEkLGOkEnexadmRYHvp%2BjFvsmmpfAQZkvr%2BtYEOCkIAdaRbAaBFHgaV36zlVNUKJqdVuvBQWIeODZfmhbYdo%2BonSUO1a5W6NHjgIbXkYF4lystdEMd1c2DtCsKYKeKJohii2sSu%2BX5laNrFuxC6cYNm1iiuUq%2BjKF2DlduwkkZzV3VcvXxP1jzQftlYifxEO7sJfHrjDQ5w7NX0SbJ0l7tuLGY1J2MsflSb3A8wLAOFuyMAQCjPYS0XhMA7JFnaRwOuB0o/ecpI3YBxYk2TbCCKDsbg7j8k48KcFHgTD5E3cvOYOTAuDbTsV3UzLMA61JxywrlMDcLLqSXJ7oAFSm2b5sW%2B6mIm2bzwACoJZTzzm1bII2xbHum67WIglL1yPsC5WUlY4MgnmQheKlY4OEGC3yXWV4oZNGEzdDR7DiKAC03oyVjWKG9pwJ%2B%2BqmrAsQwBU6HwLK/TACyflMFQXgMA42Q4VizNQqgMKkidqLolcEdR0wMdVyugNa%2BXguAiLmIJ8gAD6vpKK0ED180Tct3RRy8RPbhcLORyzpIvGiWrxws5nXBLM6HArLQnAAKy8H4HBaKQqCcG41jWOKawbBucwRweCkAIJoO%2BKwADWIBH6SDuBoSQXBsRHA0I/DQZh/D%2BDMIkRI%2BhOCSF4CwCQGggiv3fp/DgvAFAgCCGAt%2Bd9SBwFgDARAIA1gEFSLccglA0B7DoPESIvlOCqESP4TO/hJDPGAMgBsUg7hmF4JgfAnE8DoD0PwQQIgxDsCkDIQQigVDqHoaQXQB9zxjlSJwHg98n4v3AR/TgXxbicLZKgKgzwRFiIkVImRzw5FmGeBADwfD6DtiAdfXgdCtArAgEgXhqR%2BFkAoBAeJiSQDACkCkGgtB/LUIgDEexMRwgtAAJ5WN4EU5gxASlfBiNoT8dCQG8P5gQL4DBaBlOMVgGIXhgDXFoLQah3BeBYBYIYYA4gunPgaXgNSQz34tmUjscp5BBB1HsbQPAMQxzVI8FgexDU8BEOGaQNSxAYgZEwA6XY4zNlGHASsKgBgK5ajwJgc8RFX4gI0cIUQ4hdE/IMWoexpj9DjJQD/Sw%2BgtnUMgCsVAqQGhDMzuMKCDpTCWGsGYchZz0xYFhRAFYdgZnOAgK4KYfgD6hHCEMSoIwD5FCyAIClehGUNHmMMBIB9iWtwEH0SYngOh6B5Q0flAwaULHpbYCYbRBX5G5TKjldKuVEv/psCQNiODP1IGQ3gFCPGiPEZI6Rsi4EBIgLgQgJA7RmGAUsSJDyVhmSYFgBIhLSDQMkEcO4ABOI42JJAILMJIQIqD/A%2BrwRwAhpAiHALuP4Lg/hEg%2BsSIm2BXBH5%2Bv8Dq%2BxFCqE0NAQ8xhLDYlsOcVw5JqTQmCLYJwFoLAuzYkzkwV4BhYpcB9XcLg8DFHKJIKo9RsgtH/OkICpQwLjG6BSOYpgljhmau1bqhxHAnEcJMm4jsxAG1NpbW8cZfjO3do0IE4JCTQk2qOGYe1hb6ExLiagEJ8RuEpIfWekY9bG2Zz3UYDtXAgjZNyZQApxjKmlJWaB6ptT6kOBWc0imbSOn2O6b0/pgyVmjNuVsd%2B%2BBwqtzmfYxZyBbhbBAeEHYD9jGbO2aUvZWHInpmOSAs5FylDXLGUYO5oBb18GeQoV57zPkrJ%2BcOnRo7ZBAqMe/KdYL7kYqsFCqjBL4WIuyMi1FF85NYpxfEPFCV4BErqCSvwZLvwsqpd%2BJViwGUZCZTkOVlK0g2fZRKzlwrDO8saDKsz3QjNiss1K2YAq8gOcC%2BK8ornr6rHWOqyLFHF25s4Ju7dzbW37o7V2%2BBgTLWcQvREm90SnWYBdSMd1FHo2xs7Qg7EmbsTIMkMGiRB8l15tsAWqJDCmGsPYS459VaBFCI4PW7xLAFBdgbF2dLFxxi9qtXiwdmi/mib0fIcdkmdAgCPjOud1jI3xeMRQ1dLiozuKG5IkbY3uyTdJIlIJr7EkXqONe9rd6UB3dCb1t7IwxupFSAvCbPqF5TYIEvLdEi%2BB0EA/kwpxTqngZhzUupDTYMPpaQhzp2HMA9L6WINDJyMMcbo6QHDMz8PGMI8RlZZH1mUa2TskptGDkMZWcxy5bHbl0yLU83kfG3kfN%2BF83gwnFsSDE/o1bIKNsyeMJCmwin9MfxU02Tg7pUUQsxZYbFercWqL03CnzHmXCmfs3oal4XlWsqc9kbzbLsj%2Ba5fr0VXnjfcvc47uYLnzcKv6N50LduNVRYAf7uLdj9uJdO88c742rs7Bu9l614SnuOtIM611lBNXlZAGYTtRwjiPzQYgkhOfsRJpzaHyhrXaFJ89Y/X1j9kjhskD65B/quBHwo0cEP5DOAOtvZqhRpeu/l%2BeysM5mRnCSCAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_fold_right_last.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_fold_right_last.test.hpp)
