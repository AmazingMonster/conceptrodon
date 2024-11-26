<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::IndependentRightInterview`

## Description

`Mouldivore::IndependentRightInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.
When invoked, the function first binds the elements to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> RightSides...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Exist (...&& Predicates&lt;Arg<sub>I</sub>, RightSides...&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
IndependentRightInterview ::   template<typename...> class...
                            -> typename...
                            -> typename...
                            -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct IndependentRightInterview
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;

        template<typename...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = IndependentRightInterview<std::is_same>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);
```

## Implementation

We will implement `IndependentRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class...Predicates>
struct IndependentRightInterview
{
    template<typename...RightSides>
    struct ProtoMold
    {
        struct Slash
        {
            template<typename...>
            struct ProtoMold
            { static constexpr auto value {-1}; };

            template<typename First>
            struct ProtoMold<First>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<First, RightSides...>::value))
                        { return 0; }

                        else
                        { return -1; }
                    }()
                };
            };

            template<typename First, typename Second, typename...Others>
            struct ProtoMold<First, Second, Others...>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<First, RightSides...>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<Second, RightSides...>::value))
                        { return 1; }

                        else if constexpr
                        (
                            ProtoMold<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoMold<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQgABxBAA6oCoRODB7evgGp6ZkCYRHRLHEJybaY9o4CQgRMxAQ5Pn6B1bVZDU0EJVGx8UlBCo3NrXkdo739ZRXDAJS2qF7EyOwc5gDM4cjeWADUJltuBACeKZgA%2BgTETIQKx9gmGgCC27v7mEcnyKPoWCoTxe7zeBEwLBSBnBx1OEKhTBhJ3Ol2YbAAdJingc9kwFApMejlMRMPhRODHltnm9RsQvA4DgBJBhYVFYQQAJTwwAQBGZ4OIADc8JgAO4gkwAdisbwOcoO4Mh0MwsJRjFYmEJXJ5wjwWEp1Ne8oOtPpBAOxNQRAAsp50CDjVKZUbjfLTQyhAYFAgHa65U7fX7jYqEUjThd1RisVTA0G5e7zZabXbY3GnSbGo5kDiBKNMKoUsQDkwvEQDoKxF5vk6ALRcKUAEWOFiOkqbW2dqaDIeVqojaO%2BADE8MRRsDZXG3bczRbiFbULbaPaTsPRwRxy7J62W/6J1vjdMszmGHmC0WS2WK95q3v9/7pV27/6AKxWZ8NiALA417H/EAgFgmAAa2uDJgAidAblhDIAC9rnXGNbyfeUAyQ5DXTwKhj1PQsjjQ9D5SgQlzH8EjiVJPByUwSk3FXUZSAObVeSEPVqOIql/yvKsFgWR8CO3A4SQIVYGAODRm1bJs3j4giaiUGT0PTISRO/esO0khSt0bT9NNdRtm10/SOwlfDXR7REVWRfsNQOOiCAYtUBwOIRMDQFkHOsqN0QAeQIBB4gNXSE1nedF2XWiR3o5zXIEdAGN8/zR3Yw073TXdNyfQ9KOw8Ez2LUtUHLSsbwy1KH1M1LXxMd9P2/X8CHQf9AJAq4wIgqCTlg%2BCN34lDytK3qDkwnL81w3S7yIrEzFI6byLJCyaLshimN1fVks44qePG/clMwYTiFE8T1P06SKvQuTvmGtycKLbat0m9ESLIkl5opWEXLcuLGO5ZjWIJaNsA268trO5Ddv20S1JbE7QQG3qLqGrDrtyws7snCA0bvJMFxTE4EoC5LMf3IGqwOMAwGOBtVKJv1eNBp90xpydlIOg4zCOSwQuTJdYXxpKAaZuMScs6H6bKqTYcG10LsFvqWxZ0S6wkmGpe0um4cnIznXFgzTK1kyNfMsNHI1QlXmAEkIUYAhAtMrwMiMA4wp%2BKnPTxJAQCN75sbC2FzctthBH%2Bx6Y2M299dOjKvb7VFTcxV5iGAW2Mvt8JgCdu0Xa5nGeZOBOk8JsP3jbXXYYAegAKir6ua9rsuQUr6uDgAFWom2Dhr%2Bu3kb2ve6rrvYY%2BBg9i8Q5YTc9YUhtjcQWjqzY68/Pk9Tx3rT2pgqC8Ye6lEymmRZTA2Wtlb%2BXiYUxWghr/zwBRWo1Dd/19vPE%2BD4Ei5BLLkCuPElGaEEIDXo0Te28siwnCAQKuTxH64zcOAhi4CK7wMEFXJBECK5QJAFxasWx2xUzMLxIun9v74niOuN4AD17AIcKAk4gpUB6gwU/WBghUGIKGsgthCD0EcUwcVF2e86wEIsBwJYtBODPl4H4DgWhSCoE4G4aw1gTQrDWNWMwWweCkAIJoERSwgIgGfJIdEGhJBcElFsDQz4NDTX8GYRIiR9CcEkLwFgEgNAaFIFImRciOC8AUCADx2jpEiNIHAWAMBEAgBWAQFIpZyCUDQJCOg8RIgak4KoZINZ/CSAOMAZA2YpDojMLwCiRBiB6j0PwQQIgxDsCkDIQQigVDqGCaQXQXBSCijuCkTgPBRHiMkTo2RnBvKllieaVAWEMn%2BCyTkvJBSjHswgB4JJ9BbrqK4AsXgQStBLAgEgRJKRklkAoBAQ5xyQDACkGYPgdABT%2BIgDEIZMRwhNDOL03gLzmDEDON5GI2hXJBM0YkwOBBvIMFoO81pWAYheGAG4MQtB/HcF4FgQCRhxDQpHICvAgpqJDPzK5UsGxNHgJqEM2geAYh3B%2BR4LAQzbh4FcSi0geLiAxHSJgBsEJDDAEpUYHRSwqAGCTgANRFKKbyqIPkNOEKIcQ9SqnyCUGoIZ7T9C8pQIoyw%2BgqX%2BMgEsVAU8sjIprP8SmphLDWDMN4tl5T9TwCWHYHFzgICuAmH4DpoRwgDHKEMDpaQMg7w9XoQNRQGCzEGAkDpzrqH1DGC0TwbQ9Cxp3j0Zoka/XRtsAmkNMaE2ZvmJs5Yqx1gSH6RwCRnihk%2BIONM2ZuT8kHEKUs3AhASAcw0VsrRgqlj%2BSYFgBIn5SD6MkFsdEABOLYkpJAmLMJIfw7jnz%2BAnY4jgzjSCuI0eifwXB/CJAnYkPdhiuDPinUELxvAfF%2BICT24JeyIn7KiWMuJpzzlrNSWwTgTQWCCklDWJgOIDCOy4BO9EXBjElPwGUipHSlU1IVdIJVTTVWtN0DcrpTAekoorVWy9wyOCjJiaWA4kzizEF/f%2BwDuIQNgYgxoA4yzUCrPiJ2/B2zBWhIOcxo5az4lnJ4xcn9f6aw0auROrgHiaC0HuZQJ5rSvlvJlYpn5fyAUOBlSC624LIVDJhXChFtAkUyrRbyzFMj8AkmoXi5FMjCXIGJTKslYjWmUupW8ulGwZGMuZZotlHKlDcvRXytOnHhVMDFRKqVjAZXwflXUpDsgUMtJkehjVArLVWB1W5/Vw6jU71NeanBmXrW2viPa/FBrOgur8G6lkebggskLf60gYbg1JryAGwoO9mvZtTd0XNHXPXVbjQwdNfQfVzBa9McYQ2U0Fsm1G8tJbVHLZc3hmtnByOUYA0B3lza6PGMY22spnbNkcfvX2zAA6hjDpcxurdYGTGSjPZKcxkh53ZI6fh69thb07JCWEyJ0Txn8ffSktJHAf3ZIOCwBQgpsyClA%2BiZUowoPtvtZU2QCGEuyuS2qkAWxOndI%2BbhwZrSfFEfGaRrC0Oclw4R%2BWZHqPzRMZY%2BsrYWxu0A72dx9nYPBNrMwcgFIKQrhI4nVcFn38KPZNuTJgKcnnmvJ%2BcplXvz/mAs08x0FOmoUWcwLC%2BFiLkWaNMxirzqLsXWfxa0%2BzjmWXOYpVSmlZxPMMvKb53g/nOVBbM6F%2B9fARUKHFWKaLUjNFxdqRIRLjSVUpZ0IT9LxhtU2By462RxrcycDLn%2BErlgbVXrtX9DP/XXXurm16pri2s2hu61kBrbWsi9ZTTUGr42Gtl7Gwt0oS3829E7z331RanUqLLcW9b5PvFbbp7D%2BHiPmcLVZydjt2xzt3t2Vdm7Q6K0PZAGYMDnPnxWNMe4znkp93Vop5wG9gTe0jpAJIZ8k7nyJGmhOyQE7zHTq4ETlzWwp8r0b8N9dE11ikr9p9fEQCeJWUAoshH8gA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/independent_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/independent_right_interview.test.hpp)
