<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicRecur`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-recur">To Index</a></p>

## Description

`Mouldivore::ClassicRecur` accepts an operation.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function instantiates the operation with its arguments and uses the type result to call the operation repeatedly until the type result satisfies all the predicates.

<pre><code>   Oper
-> Preds...
-> Args...
-> (...&&Preds&lt;Oper&lt;Args...&gt;::type&gt;::value) ? Oper&lt;Args...&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Args...&gt;::type&gt;::type&gt;::value) ? Oper&lt;Oper&lt;Args...&gt;::type&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Oper&lt;Args...&gt;::type&gt;::type&gt;::type&gt;::value) ? Oper&lt;Oper&lt;Oper&lt;Args...&gt;::type&gt;::type&gt; : (
            &vellip;
   )))</code></pre>

## Type Signature

```Haskell
ClassicRecur
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicRecur
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will increment `0` and `-1` until they are greater than `9`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** AddOne ****/
template<typename Val>
struct AddOne
{
    using type = Vay<Val::value + 1>;
};

/**** IsGreaterThanNine ****/
template<typename Val>
struct IsGreaterThanNine
{
    static constexpr auto value
    {Val::value > 9};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ClassicRecur<AddOne>
::Road<IsGreaterThanNine>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Vay<10>;

/**** Results ****/
using Result_0 = Metafunction<Vay<0>>::type;
using Result_1 = Metafunction<Vay<-1>>::type;

/**** Tests ****/
static_assert(std::same_as<Result_0, SupposedResult>);
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will implement `ClassicRecur` using a helper regular function, which utilizes `constexpr if` statements to decide whether the recursion should continue.

```C++
// `Sacrifices` are the arguments that will initiate `Operation`.
template<typename...Sacrifices>
static consteval auto idyl()
{
    if constexpr 
    (
        // `LessonsLearned...` are the predicates.
        (...&&LessonsLearned<
            // `History` is the operation that will recur.
            typename History<
                Sacrifices...
            >::type
        >::value)
    )
    {
        return std::type_identity<History<
                Sacrifices...
        >>{};
    }
    
    else if constexpr 
    (
        (...&&LessonsLearned<
            typename History<
            typename History<
                Sacrifices...
            >::type
            >::type
        >::value)
    )
    {
        return std::type_identity<History<
            typename History<
                Sacrifices...
            >::type
        >>{};
    }

    else
    {
        return idyl<
            typename History<
            typename History<
                Sacrifices...
            >::type
            >::type
        >();
    }
}
```

Note that we wrap around each result inside a `std::type_identity`.
This is to avoid creating an object of an instantiation of the operation, as it might be impossible.

We return the final operation itself instead of its type result.
This is because the type result that we are testing might be an indicator to signal the end of the recursion, and the actual output could be a different member of the final operation.

Here is the entire implementation.

```C++
template<template<typename...> class History>
struct ClassicRecur
{
    template<template<typename...> class...LessonsLearned>
    struct ProtoRoad
    {
        // `Sacrifices` are the arguments that will initiate `Operation`.
        template<typename...Sacrifices>
        static consteval auto idyl()
        {
            if constexpr 
            (
                // `LessonsLearned...` are the predicates.
                (...&&LessonsLearned<
                    // `History` is the operation that will recur.
                    typename History<
                        Sacrifices...
                    >::type
                >::value)
            )
            {
                return std::type_identity<History<
                        Sacrifices...
                >>{};
            }
            
            else if constexpr 
            (
                (...&&LessonsLearned<
                    typename History<
                    typename History<
                        Sacrifices...
                    >::type
                    >::type
                >::value)
            )
            {
                return std::type_identity<History<
                    typename History<
                        Sacrifices...
                    >::type
                >>{};
            }

            else
            {
                return idyl<
                    typename History<
                    typename History<
                        Sacrifices...
                    >::type
                    >::type
                >();
            }
        }

        template<typename...Sacrifices>
        using Mold = decltype(idyl<Sacrifices...>())::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSXABspAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8YkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGZwshvFhbiYwW4CABPZ4AfQIxCYhAUcOwIJBfwBhIOQIJtwAkixUvQ2IImI0vocSUTmWc8VcCJhKQYOXCEZyqXTMLykc9mGwAHSSnG3KFMBSfAASeAmJEROJBE2IXgctzcBnleGQACVMMgNniAOxWK63W23DlcwXC/ncoXwkWMViYSXi6Wy%2BU%2BkIfBQCBRB1oRdDqm12zXagi3ZTEVBEI2oJhRmO2kxWkF2/O3HY7WFJDRCJjIYh4GhbbGl26tTD2hBN1rAHyMAifAgIOm3ADudFot3CWUFJY0AHlnhjGiZS76swWHQKee7kZ6JZLy5Xq4aPtHLgXYy1HMgZaGOQA3MQNrxEEfoRG0CDLPPH2G5pcfkdUC8MCZMFUVJiFhb8Pwgd8f2PIsJyDeVQ3DYhIx9ecNAbYgmx7JsQMwfBRA5BRFyPaDjwgVCzCScwkngkMAKQyNeSg0iP1gtClRVYg1XrZVmybVAZzpbJmz7QdaGHTCzWIYiWOgj0xSbDiiC4pjwNk48dyrGsPlQtT1JxEAQA9ZjZIMkAb28TA3z0/NrJI0ic2tez1MwggNgYW4JnQQyPRRPAsEEQg1XhJTVVU5z1I/TS91rXSIpY9UwVxXMLXuOEnNM1KTI/bLj3qJRf3/QDgNA3KC0gmyIIoqjKNoxDMAjPDwsi495K9W5QpU%2BEytktq2A65VlOCtwepa6LtKIqVKocpKfI3UaZuwObngWgszIsrwrNWuzMoylrXPczyCG8oyNz8gLHCRXlOuG1afz6xTBrC7rpvU8b90mmSWvzMzjNen6kvVFK0rBPaHKyq5VvyoVXscu67QO5DH2fZrvrtB6Bs427/o/DGbtRtGC3e2KpviyLfvmnHjwplaqdhJLX3S1aczSvSWbZMn7RdJ111FL0fWJg9Ab0rxMiMW4AFlPHQen7luLAoQ9CB/JR%2BFBc%2BnFX2WZa3TBz8Qac5iV1dZ1HTXBENwU1CkplfVPsuYBMM5TtsWF5zRfCYBbjTDNZcTZNU3TKN4Qdp2aS7a3cVBy0DY5gkWSZO5sFUVgqSbb58RZDPIch8FIWhJteTQBgtlSLtD0zu4ADUmERBliRBY2ebcJh71QclDzjHUa7VSGrSOoTz2L4qQLvB8NsLq0yXZ0H9aZnPriOW5LnQdBJwievWXZbnzYxmvaE79F42X1f15h4Ev3dsWvY9P2e95ffDIn2FLFuLhEsNrLo4X0kyQUABxTCgpiAABVewMEiOEdOjJG47zdBbPm/V96Hy1DqP%2BgCGoclAeAyBERLR6zmGeIqHISpj3bhPZijlH7mTEJtem2BbgAE4Z6f1jj/JeEtMAtCoF4Eu9Js6XCbrvS2/NJSXGIMAV2uIrge3Fpw7hvCHDCThHLPUcpMjGlNOaEOp88Fu0Mj7YObh0FAKwWAwwuC3TSMuIZKWtAjHiMkZHeewJfhLyEF4VIRQ8ImgUF4WgCYBGyK9h4rxGQfEfH8QmFRtx77wi4BoD%2Bccl6%2BKiZ8IJ19vaRICSidCMT5FMB4Xw7ID9a68kSYDWap0Vrf0uMErJficlcD9gUopSiBClOGgAWnfpUpa1TdbJLuCAj4XZN5AkIYaFE6j4gEAgF5QyCgvTTNdm4VJOSNCkFuKE7x6B1kEBxG%2BWpkzkArKUG0eZx1FnLLlLyfZKIuBbJ2eEvZ2SDlJSORYDgqxaCcH8LwPwHAtCkFQJwEalhrCeXWJsQu4IeCkAIJob5qwADWARJDig0JILgFowQaH8BoSiSQzAAA4SX6E4JIXgLAJAaE2YC4FoKOC8AUCATZiKgXfNIHAWAMBEAgHWAQVI95yCUDQJSOg8RIhek4KoElSQulJEkLcYAyBzxSHFGYXgeFCAkH8nofgggRBiHYFIGQghFAqHUJy0guhHn9gxKkTgPAfl/IBUikFnBJz3mFQmVAf45UKqVSqtVb8MVmFuBADwEr6ClThcsXgHKtCrAgEgcVqRJVkAoBAdNmaQDACkGYPgdAsGsogDED1MRwitERM63gVbmBcUnDEbQpoOXwvFeHdetBa02qwDELwwAW7iVZdwXgWAWCGGAOIPteBJKOCvB8D1QEtEcjreQQQ9QPW0DwDEDEXEPBYA9eiPANKx2kEXcQGI4THiTqMDuowSLVhUAMJIqu7x%2BzTkYOuw1whRDiDNb%2By1agPV2v0FOlA1hrD6F3ayyAqwBKNFHV0ryKjTAQssGYRll6qxYDg6%2BHobbsguAYO4TwnQ9ChCgYsUYjyihZAENMPwdGMgMYYAsEY1RCPtKaJMdo5H8iPLsERgQ/Q2gccqLR2wfGmN6DmOJ6jnGJCrBDBsLYymKUcH%2BaQBlvAmW3EDYq5Vqr1XhsjbgXVcawRcATQip9qwWwZlGARtFkgwTikYWCC0kgsVmEkKWfFSRGGaapaQGl1nxRJGSCSxhJLkj%2BGxf4TzKRdOeuZbYNldnOUpr5amgVPqRXZtzbG6VbBOCtBYFeC0XSmC2ynW/Rh4ouCYu1fgZS%2BrHm/uNQB6QQGlAgZtboItDqmBOrHa6rT7qbVMu9UK%2B8tx/UGflUZur4suCNea%2BhKNqAY3xBfmCMwtmk1cry8V%2BIoqc07YzbGlABgjDrYScWgJ8Qy0VptQ2mt66PtNpbW29dnbOzdt7cC/tg7h20FHfCidU6Z0g7nURxdo7gUrrNGu894QOS/JtTuvdNbD3bGBSes98LL3XqULemHnsn18FfQod9mBP2ih/bIbrpreuyGA9a4FQ3wOPvQ1YSwMGYj4YQ2XbIyHUNgnuPz6wWG9M4f8ku%2BD3HGgkbI3kZjwRSMSaWCx4o2RZN67YzrqTwmeNif4xruT9QRO8fmIpyTXH5OW4o0JvjJvqgqehepmzmntOpf04Z4Nso1sbcxeZtrJB9s2cTfZ0gjmsAJAI1j0L4XGtYotEli0uLJB%2BaVY8gPnAWWZeOzl%2BAeXBW%2Bou2d4gpXtgVeDSwBQV5zxXnW%2BKV0ExWuWY6%2Bav9JqJDs4tf1rnOgQBglICNsbLq/dTcZV6grfqA2N%2Bb639vneEzbd21ZsER3qenau5m6vh%2Bbst68SiNvjCUQb5RKoJVT3S2UDe8C77vb4Wv%2Bba2hw/2dtdoYD2j1UHIdMQCHddaHe9AncdeHJRRHZdVQVdbYeFDHLdbHXdfdREfHY9KsYnXgUnG9TkSnR9bLGnJgN9D9L9QFeFLrf9NnPvTnUDcfXnYwKDQXHHEXEFMXUMTgHYBZGXTDbDeIXDJXAjM3VXCAVwQ3LXdAD3PQejRoSQuQ7IGQoTG3c3GTATTXUQvod3B3XXaTAYSQ53ZQr3NTU1Cbf3D1QPFfFvW4S/DvQUCYCPSzaPPfbLBzBqRPSgCbVPEAMwRrMEMEQILFBJDQAIi0JIclQvdLVldlOPVzfwDzfwElSiRhSQRhXFLzLgCfLHMEOfPTIvLLZNCbLVHTSwgo0vVYS9TIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/classic_recur.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/classic_recur.test.hpp)
