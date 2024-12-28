<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateInject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-inject">To Index</a></p>

## Description

`Mouldivore::CognateInject` accepts an operation.
Its first layer accepts an index, which indicates a location in a list.
Its second layer accepts a list of new elements and returns a function.
When invoked, the function injects new elements into the location of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Es..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateInject
 :: template<typename...> class...
 -> auto...
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateInject
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold
        { 
            template<typename...>
            alias Mold = RESULT;
        };
    };
}；
```

## Examples

We will inject `double, double*` into index `1` of `int, int*, int**, int**`. Then, we will instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, double, double*, int*, int**>;

/**** Result ****/
using Result = CognateInject<Operation>
::Page<1>
::Mold<double, double*>
::Mold<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateInject` using concept expansion.

```C++
/**** Prefix ****/
template<typename, size_t>
concept Prefix = true;

/**** Enrich ****/
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        template
        <
            template<typename...> class Operation,
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl() ->
        // `NewElements...` are injected in the return type.
        Operation<FrontTargets..., NewElements..., BackTargets...>;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<typename...NewElements>
            struct ProtoMold
            {
                template<typename...Elements>
                using Mold = decltype
                (
                    // Note that we use a parameter pack in the template head
                    // even though the function only allows one operation.
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoMold<NewElements...>
                    ::template idyl<Operation, Elements...>()
                );
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcwQAOqAqETgwe3r4BaRlZAuGRMSzxiSm2mPaOAkIETMQEuT5%2BQTV12Y3NBKXRcQnJwQpNLW35nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpiprozIeJgK1wenF1fHv4df5zOgLMgQiyG8WGuJkCbi8jlohAAntDsEDzKCGOCvJDoW5kGN0FgqCi0RcCJgWKkDOTcQREY9mGxSNdMgAvTAAfQIJIuaExDwI12UxEwNFUUMCt2uBGIXkw0KsFyBPz%2Bqr2AJV1wAkpT6GxBEx6gwPvsNWrzSdSZcDtdsAxiHhkAgTeqgeTdYb5TC6QzWF7URcxrKHLb7Y7nSYAOxWSO3BVW91Uz24tmcggAOkzWp55yDXhDdodTpTBHQIBAESwqg5SgAjnL%2BbitZn0yTAgHAdGgdce9KKUmad76Yw/S2opgAO7YPWMAgKHO9lky/OC4WoIgAWU86G7vajFihF0Xi8T1PlR%2BPPdxu8vJ/7Z9pw8ZmBbKOu4KYCneAHlHsRDdkpA3rePZbFs1wAOqYNcXhKFCABsGjCqKeCqE2KKvoh0qoNcjA%2BAknoIRoABixCyAAKs0wCYHOJiIa2F4gT2yFiuh7YtqRFFUTRChAYxTE%2BiObAthYTDIAA1pRxDUbR/GLgut4zI4yDvgIYyYAAbmI1xMHCOF4OgiK0BAizXAAtApl5gUR45TjOggKJhGg6SK1wRNomAOJg6BucaBAINBIoEGsfnDgx5wgb%2BBFGrinGCFJMmOZmzK2dOFKzkl6bMqJEkJTxr7tvG/FRnGgSKoC/GnsmQ6%2BsJmapfZtGFfxsERMA1xbrQPnQlKa6btuuINelDkFaiZVorGRUVdaNweMAzDklqDAeSGnxuve1VuFVg5bU%2Bo6Zm%2BH5ftcUX/jFzW5suIZzQtmBLSt3JKl2lUbTtqZctqDBVpZS7BquZFEMoTDUcB%2B7AYueYhkIBgKAg4N7s9EVMT221erttUvvVk5pfqTUdsjPaQ/966oJ1O5ybeYMU8jqOPhjLY4xlP0EzBmRGB124SlKWDgoJ8PIxA/Ms9c1lROu0H%2BYa1wTtBsHQUw1ypM0frksQitieJvnSgFfYeuS1wBUw5NI8Lx7WZpjDa6swDOv50FUF4mJGtcAi0IiOm0LQqATu8AjQagf4AQI4Wm5ehbhiWZYgCwTDiZylaYNWdYNhsTZfYnbb46Hi7lqjQoA6TA0wkNuOZczoe5690EGUZuKnUHDDMozI0He2JlCyBixTSzJXd5Tk3jUq1O6wOaOCc%2BLbnMAIrDXjQutezZNc9c0OfkgIB531hddbiU8z6Xo191eA/lcBtMwrpRCT9PmCz/OF2Lgv7VA9Ry9by/aN77fB%2Bt2Np8n1aFUFozQ3GwKoVgVJoJrW%2BBaaB010RgghNBXEfINipDnkPGaewTqB2dnA8%2B6MhKY1bBdImODorZCmsqG0QgvCpHSEodAAAlN4XhaCCjgU/FedCGHeRYQoNhgoerkLOpQmEEQCDMnQKsWI9ApEyPoDsZkEilG%2BQIHsNsp8YE3H4YIl0loLhcN0ew5eN1PT3U8tyGE9dzodnLB/XEXAczljJriaRXhZGYHkR4xRziQCuPEYIZRghVEqJ2JowBNpyJvA4aaIESlHQck/EoFoEACTlgUH6JJ983DGMkdw%2BhGQ%2BGsPYSiLuZUODLFoJwfwvA/AcC0KQVAnA3DWGsCyVY6xkEgh4KQAgmhKnLHEgESQ6YNAAA4zBmCSEkLg/gJnjK4JGSM0hqkcEkLwFgEgNAaFIPUxpzSOC8AUCAXZ/SGmVNIHAWAMBEAgFWAQVIcJyCUDQJSOgCQoh%2Bk4KocZ8EzLwUkNcYAyAVJSHTGYXg3lCAkAMnofgggRBiHYFIGQghFAqHUBc0guguCkAnP%2BVInAeBVJqXUgZTTODfjhE8wUqAqDXF%2Bf8wFwLQXXHBWYa4EAPDvPoGrdEXBFi8HOVoZYEAkBvNSB8sgFAICSulSAYAUgzB8DoKrE5EBYgUtiBEZoiJiW8B1cwYgiJvyxAega0gbzcbfgYG7ClWBYheGAG4MQtATncF4FgGORhxDYvwCKBweANJvApYnTycJNi9IkbUClCJYj/hNR4LAFKZR4C2Z60gIbiCxCKfcH1wAERGAGcsKgBhgAKAAGqvAnFFepvSEXCFEOIVFjaMVqApbi/QhhjBtMsPoPAsQTmQGWAHI0HqzIEh6qYSw1gzAHOzQ6LAw6TJdEsdkFwX1Jh%2BDxWECIgwKjDDxQw4oORPDtD0Ceo0cwhiJDxXYddDRxitHPfke9tRH0MF6C0G9h6722GfduvQMwf37vmEe5YChOkbAkKSjgtS9kUsOYyv5AKgUgrBaMzlEBcAwv5T0oVfSS3LENlgRIq7hmSECOmFIKyNCSDMJIRCGh/DwSSPoTgGzSBbMCFwdM8EuDwXGUkRZ8F/CSDmSkeCiHsWHOOacojFyxW3PFfcmlzzZXyr5V8tgnBmgsA0pGMyCsPzsy4EkdMfHGnQqIEu%2BFsgkUtukG2pQHbsW6BVQSpgRLPVwYQ/s3ghzqWPLhC7BlTK0PvgMGZizVmuU8qlXyqEIIzCEZFZc1TWmEgvLlagXlwxTNKtmbsmg7CEgaq1dio1erLXVZNWai1mbrWzltfa/1mAnUurdR63p3qe1%2BsaQG9dIaPXWdUBG8klqY1rMafGxNiJk2bEaWmjNvTs25qUPm/rbUS18HLVWmtdbLWNscyi5zsh21YsaR57txaZ1WH7fGldo70HZAnVOyU9250LoSEu0NI611BucBAVwQHd1fV/QsY9RQjRg9IFe7IkOj2A6NN%2Bl9eQd0o56M%2BpH/6QPo4vfenHYHb2wZWGsGDgqOPwfJbJzgKHmVAsK%2By2LYyuW4ds8l3jaXiOkFI8MVdayuM8Ys/RyM/gkjLMCAxpjEmZMHM4PJs5u3rl3IebSnLWXiA6c2PpllLAFAaRUhpcz6YzxjChfgWzcK8UnebWdtF8hXNXZ0CAYIXmfMkup/5pDVL1N0vC/rw3xvTfm8FNyvLiWEhc8CDzpTVyJWR%2BlZrpPfKQBG/oRyE3SQORh45KoQFqqyvEAq9q3VJravl9NeayxlrmuCFa/q9rnXXWex616ik/WlterwIGxwI2w3jeQJGqbghY3Yrm3qxbqaHSrd4OtvNnffU7fj2W4GB3JxHczXb5FEhzvoud52t3t3e2zse4O57TTXtqU4FsdJX3LDzsC4ugy/3V0PqB34EHW7X2Y73WUUnaHTIWHX/S9GHRHEnP9YDD9T/NHOHD/VHYnAAqAonPoeApAg9KHSDaDFFPzWnBXDgRlIPI3a4bPM3T0MYdnK3EgLnQVYVXnfncjODYXEAaZdMQIQIfweZCTHZDgyMITeXQLRXWwBTdLRYIZEASQfwGjJZSMHZcZSQWZLgSZMwaTNZQIfAoQo5RTUVODSFQQylbQsQ5YbNTIZwSQIAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_inject/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/cognate_inject.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_inject.test.hpp)
