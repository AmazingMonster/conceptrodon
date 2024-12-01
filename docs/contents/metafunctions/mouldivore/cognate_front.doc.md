<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateFront`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-1">To Index</a></p>

## Description

`Mouldivore::CognateFront` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function collects arguments of the amount from the front of its argument list and instantiates the operation with the collection.

<pre><code>   Operation
-> I
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> Operation&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateFront ::   template<typename...> class...
               -> auto...
               -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateFront
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three elements from `int, int*, int**, int**`.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = CognateFront<Operation>
::Page<3>
::Mold<int, int*, int**, int**>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateFront` using concept expansion.

```C++
template<typename, size_t>
concept Prefix = true;

template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to enumerate `Targets`.
        Prefix<I>...Targets,
        typename...
    >
    static consteval auto idyl() -> Operation<Targets...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `Targets` satisfies `Prefix<Targets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateFront
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsGqQADqgKhE4MHt6%2BehlZjgLhkTEs8Yn%2BXLaY9iUMQgRMxAR5Pn5BdQ05za0EZdFxCcmpCi1tHQW1EwNDFVUBXACUtqhexMjsHOaBEcjeWADUJoFuXo60hACeZ9gmGgCCewdHmKfnyBPoWFT3jxeZn2DEOXhOZzcBBuaUwAH0CMQmIQFADnoCAPQAKhxWOOymImBoqmOuKxGMBBEwLDSBipkOhsOYbFIxyyAC94QQ0U80KDMGkCPjCcTPgARY6IryYM5WdHPbG444AMRIHzJFOeVJpdJl50ZjFYeoezwmxC8DhVatOAHYrDaxbLAZTqbSmPTzhyuQA6X0ASR5ZotQtVhMhPxAIAiWFUcKUAEdpfzIX7fd6AYETS87YDjnnJa7dbn85Di/n89q3R6oTDDWw0/djocmAoFMcAPKwpGNUhl8vHDEY44AdQ%2BXiUpxSBKJeFUKfuDZSktQx0YPgS7o%2BJhSABVWsBMARUSl089%2B/np8T55m03viAej72z%2BfJbXmZgG8%2B8zzy3NHMgmwECZMAANzEY4mEuFc8HQG5aAgFZjgAWkbTsN0aSE7wfBQG0zJ10QdfCXgVMljg8YBmCpZViFkUlcU1J5KyLfVC03Bk3yNXDsCbAxWw7Lt3RyQMpUtcjKMwajZGdHMvwLHU2M9PBOQRY4nhYDZBB/fMg0tAlUCIZQmAPPsTBkp4Xzkqs9RrJlON9bB6DYQRUTw2Ty3HCJgGOABZTx0HFY4sEOA0%2B3LCBQpfUNrIjEAWCYABreFo0wWMEyTbZITUjTuTw1zzIs/NIyYzdjhguDITQ7sclZBzqUYI8uIQiK8xWIjy1Mx1AjlYj8rzYrq0gog0yeYBCTq5ytLzDyjHxIyt0CCU9IMubMtGzBxoa30M26jqiMxMkDsOhjFRxY4d0wCY2w1fbDtu8lnXRYE3nBea3D5bZBRcrMXXk6sDXfLjAR0oVKsEgQ9ueaavKELw0iKTB0AAJQurxaCFM4JVBjDzgiAhWVxrF8cEHFtoep4oeOZGFFR9GFrI1AKM3STNPOLGhLyyNDOM85Ah5SNfNodBIVxomCEJ0rifFgmsVJ%2BUnj/PBkDhFslDaCAYoUI1lZctwYbhzIEapmnWSNtH7larqODWWhOH8Xg/A4LRSFQTg3Gsaw2Q2LYt2BHhSAITQrbWeKAgADm9JJAkkMwbUkSR/FDwINH8ABOUP9E4SReBYCQNFSB2nZdjheAUEBUgDx2rdIOBYBgRAQA2Ag0kuchKDQGk6ASKIjU4VRQ6SJCkkkY5gGQACpG9MxeARwgSBgvR%2BEEEQxHYKQZEERQVHUSvSF0WoAHckTSTgeGt237cD53OHbS5m6FVAqGOPuB6Hkex%2BOCezGOCAPA7%2BhiFOL7FYvAK5aDWBAJA7c0idzIBQCAUCYEgGAFIMwfA6BUmIKXCAsRL6xAiK0G4J9eB4OYMQG47ZYjaEwA4IhpB25OQIO2BgtBCE7ywLELwwA3BiFoKXbgvAsBxSMOINheBCQODwCBC6l8UrUMuDsP2uN6iX2uLEJEZCPBYEvoiPAOd%2BGkCkcQWIBsxTUkMMAa4RhA5rCoAYYACgABqeBMD7zQg7P2i9hCiHEGvTxm81CXz3vocxKB3aWH0HgWIpdIBrFQIKHIfCkI/AxqYSw1gzCF0McQGC0iYk9GoY0FwDB3CeE6HoMIERhiVFGLUIo2QBDTD8LUzI9SGALBGIkWY9QCl9EmO0UpMx8kSIEP0No7TqmdNsH0xpeg5hjMqYsGpawFBe22BIM%2BHA7akALrwIuT9%2B6D2HqPcekhJ7f1wLPABexVggOsWsBAmAmBYESAhUgIdJCBG9CnQIscNDR0kCkZOSQU4Zw4FnUgOdAhcAjlwJIoc06wv8JILgqdAhJG2ZfIuJcy7%2B2sdXOuECG63xbnAhB/9u5sE4K0FgIEbRISYDxcxH8U7emhU7GeRBsnoAXrIZePjpB%2BKUAEneuhUGHyYMffhGytk7KvhwG%2BTdLjHAfhBYgNK6UMubDNLgLK2Xf1/tA/%2BgDAhmGAbiyu4DIGoD/gkVu8DrWGtGNS2lSEtXIJTlwVINA0YJCwTgneJCCG0MDWQihVCaH6PofVJhLDL7sM4dw2gvDaGCPMSIp2%2BBxGOCkXw9lqg5FUloUom2O9VHqJuJonYTsdF6L9oY4xShTFCIsZ5PFtijKOOca4pktDPF8tXgK2Q/jt5O1FcEqxqSrDhNUdE15cTGiJOSQtSd6TMkJC5bk15dgenOAgK4GZtQKnlA6YUFpjQD3pDPTkcZSwum9BGdMgZTShmNFGYMBZJ7ZiPvyM%2BuZ77j0TPWesTYazVigplZizgqr1X0sZdq3V3oNDnPwJy41NzzVgPuY855lANngshSyv5NpU42htFHMwALkUYp3li2wOLQFVxrvXRud87Vkq7j3Dg1LX4sAUCBACIEdXel1BMaeKG57ctqH27xA717yCFSOnQIBgjislafcDF8aPX2JffR%2B3Hh68f48cQTLKRNCh/g6mBxrAhmoY5alAln/5scc6MfjcM4QmbhGZ5Waqh5oJ9Zgyg/qnYhtYX7ULYaCm0KjYIGNrCM2YA4VwnhfC/apuEVWgRYiek5pkfm5A8ii2CGUaWyJ5bK3aOybW3g9aTFmOEa2i1fA7GdpcW43tvKZMSEHRvBTgTlPjuMGEmwM74CxPiUBTgGIIwrssBk3ZWScmzuWd04Zfg93FIvUeqpt7L3FByBeupjQb01Jfb0gYF7t1rbfSdyZf7Lt9Nu0BlZIHV7Ss04XKD%2BnjiGYE0JszyHLlods3c0gDynmjFeSW/DIAzAssCIEfw/g/meo0Ajm0cLqOfeLnR8uoP3nQrRf4G0ZgkfIuBZIDQqCS2BA%2B7szgtyLUbKnlj%2BnOO7NrEMVkZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_front.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_front.test.hpp)
