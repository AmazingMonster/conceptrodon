<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::LaboriousPress`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-laborious-press">To Index</a></p>

## Description

`Omennivore::LaboriousPress` accepts an operation and flattens its inner structure. It returns an uncurried version of the operation. Check out **Examples** for a detailed description.

`Omennivore::LaboriousPress` functions the same way as `Omennivore::Press`.
The only difference is that `Omennivore::LaboriousPress` has more base cases.
This function is provided to compare against `Omennivore::Press`.

## Type Signature

```Haskell
LaboriousPress
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename>
struct LaboriousPress
{
    template<typename...>
    alias Mold = RESULT;
}
```

## Examples

We will press the following operation:

```C++
struct Operation
{
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage 
        {
            struct Slash
            {
                template<auto...>
                struct ProtoPage {};
            };

            template<auto...Agreements>
            using Page = Slash::template ProtoPage<Agreements...>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

Note that the type signature of `Operation::Mold` is as follows:

```Haskell
Mold :: typename... -> auto... -> template<auto...>
```

After composing with the instantiation map of type signature:

```Haskell
Instantiation :: template<auto...> -> auto... -> typename
```

We rewrite `Mold` as follows:

```Haskell
(Operation::Mold) :: typename... -> auto... -> auto... -> typename
```

This interpretation indicates that if we pass `int` to `Operation::Mold,` we obtain a metafunction:

```Haskell
(Operation::Mold<int>::Page) :: auto... -> auto... -> typename
```

Then, if we pass `0` to `Page`, we will obtain another metafunction:

```Haskell
(Operation::Mold<int>::Page<0>::Page) :: auto... -> typename
```

Finally, we pass `1` and obtain a `typename`:

```Haskell
(Operation::Mold<int>::Page<0>::Page<1>) :: typename
```

By 'uncurrying,' we mean we would like to pass all arguments together via a tuple-like structure.
The type signature of the resulting metafunction will be like this:

```Haskell
Metafunction :: (typename..., auto..., auto...) -> typename
```

Since in C++, parameter packs are not transportable notation-wise, we place them inside suitable vessels, which will yield `typename...`. Since `typename...` corresponds to template member `Mold`, we will invoke `LaboriousPress<Operation>::Mold` with the results.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Operation
::Mold<int>::Page<0>::Page<1>;

/**** Result ****/
using Result = LaboriousPress<Operation>
::Mold<Capsule<int>, Shuttle<0>, Shuttle<1>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `LaboriousPress` relies heavily on recursion.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
template<typename Operation>
struct LaboriousPress
{
    template<typename...>
    struct Detail {};

// Base case:

    template
    <
        template<typename...> class Container,
// There is only one parameter pack left.
        typename...Contents
    >
    struct Detail<Container<Contents...>>
    {
// We invoke the corresponding template member of the operation
// with the extracted pack.
        using type = Operation::template Mold<Contents...>; 
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents
    >
    struct Detail<Sequence<Contents...>>
    { using type = Operation::template Page<Contents...>; };

// Recursive case:

    template
    <
        template<typename...> class Container,
// We separate the first parameter pack from the others.
        typename...Contents,
        typename...Others
    >
    struct Detail<Container<Contents...>, Others...>
    {
        using type = LaboriousPress
        <
// We invoke the corresponding template member of the operation
// with the extracted pack.
// Then, we pass the result back to LaboriousPress for further invocations.
            typename Operation::template Mold<Contents...>
        >
// Unused packs are recycled for further invocations.
        ::template Detail<Others...>::type;
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents,
        typename...Others
    >
    struct Detail<Sequence<Contents...>, Others...>
    {
        using type = LaboriousPress<typename Operation::template Page<Contents...>>
        ::template Detail<Others...>::type;
    };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmZmpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLKn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcBAAnqlGKxMLcAPII4jvbJQ7DAibELwOW6hJixEhOLwKZTETAKBTAkwAdisV1urNuoPB70wUJh8MRbAAdELscC2bc8QSCLcACKYFp0W6MqwM6VQ5lAn47W4WJhKW6iJQgekstkc55c0VsnmWsWss0Q7nQuEI5iC4WBbD6gy024eN4RBKkYE7LUAFQQCWReAUtwEtFhscit1SrSRoOIyaYyAA1rd6FQCAKbbbnfzMEKBX7QYI6SbWSK6%2BKCPjCbL5bQeVWmAHiJ3ZIwCAoKyKPcWlcGtQB1KMMABuqGzyIIEf1JGpCnSDHwRnZYPNoNubEqCVjVHZK9Q6MxAgntwA7oQEOfkZhVM2s6D0Jmc0XG2KKREwDsnyiqBNKqJXo0IAgPaXK3AAsp46B9oIA5Du6OKBBYiqNoyqpYcalxirBkK4dCxbEXuDo8kwXhEMOHperqMZCJgACOXiMFsQZ/mytH0UKVZoWOo6NhKrZyt2HbQqxHFcY6bhCTWDGYTiuFMrcAE7qWoHgWiCTXn4MFUXByhMMAClKYOKlqoqKpqoRIa3AASpgyAbJks7Iga7CEZRnKkURVrkbxdomZCTp8q65YYUxPpdj2PHXFOyJKCmGIHsuyI0MQEyZhibDpt%2BuZUMQqAsM%2BsZZblv5BbawEukiFZWQoSX1XaUVNUKKLVbWdWgWp/XiVKbZSSh8qRL20ItSppCor1Nnqeq7WaZk2kgVC4HEqSxDkpS659St1qarc063BE86LpVaDEOum7bkBJHIkeVSnpVl4GY0t4PsulWvu%2BDiYF%2BKY/re4aMHNd7IimPpZbc65eLQUqxFmuZEESJJkus%2B00jG/AZlQGzVedc6oKIjRDhR7WltFEGfdk0FPQhSHjWhi39WKDbJbccgMBSQPFTGrTItSyCwsg9BfvjtyE20EYZhdZOGZToW3Iz4XIqNdA8j18voUWHqM3yDnqfh6rFk9IluFTYUBQp/GoCpcUsexnEMNxNu3A7zX9jWbXU51boCrrCSHcFg1isNMqSdrMmu/JrPKRhc0hzVGFjkyntaY9G1gRjO17VSuM8jTSJ0xlDPGXbtxmRZifWenokc2y6vV1r0luKn%2BvYkbCIm/1eH95zjaW5FjVB5cwDUmCwlN/%2Ba1AYhtBfpt0ftjyk/T68DcG9gveOub9kEVcwb/H8gK/HstzYKorDPMiXyn2fJyAvSZiBBEEteFgoFuGg7uYFSIOLmT8Djl0Mp8M4uJmySnAV9E%2BmcR4axLoHGKu9ixRypKgIgS9kJLU9qPNw3t06q0wWVIgtdkSe3HKrSOMDCRCG9AgT2nNEHNxWrbfc9s6KOxIewjhZDsGoEoXZZUZsWFWiPubWhppkHQmIQKTemAZ41i5hwtk2ca7mSoXnRhuokBVy4TXchwjtEbynso7e3dRzH34YPWxBC5FEJ4RWJRKjgFz3apokRq8sEULMdCNxVibK2NYeIk%2BSC7YoPHmgoJs8I4aIXszZeuljFCNweYrebNG6H3CRqa4RxfRMFSAoRGD8oFXEIaXIOXMo5EJKWU/uoCr5CAQHRAg9BIEHEBIQhRtT6FSlae0%2BgTSfiFKEF4VIRQgauVKUjLpexASaImVMjIMyaSIylKvfSFcbxXGghk6EEQCA9xAJQnkGhTnnOhFwEc0iCl3FmZshZSyklPPmavbaWMKRF1pDrSCWIm4HJZtNYpcyFLHOxHNIZBAOkKUuR6aFbTYUjJuSOTC9zL63FDDSKUj8rhzEcMgAA%2BsxBIBAIATHQNBBQSJSV0mhO8gg0LJnTPQEy7Eyw1QcFWLQTg/heB%2BA4FoUgqBODW0sNYcU6xNhUPfjwUgBBNA8tWNmAIkgBQaAABzJAAJy6q4P4bVWquAMgZNIPlHBJC8BYBIDQGhSBCpFWKjgvAFAgAdUq4VPLSBwFgDARAIB1gEFSHRcglA0BPDoAkKISJOCqC1QANgALSJskLcYAyBkC3CkAKMwvAgaEDJNSrgMhBAiDEOwKQZb5BKDUMq0guhS13gxKkTgPBeX8sFQ2l1KI6KhqlKgM8CaU1pozVmnNGqzC3AgB4KN9AMzmECFwZYvAvVaFWBAJAkbUjRrIBQCAO690gGAFIFINAkah0oLEBtsQIitFhO23gd7mDEFhCiWI2g3JeoVZG7eKIGDxgbVgWIXhgBENoLQd13BeBYBYIYYA4hvWkHwKLRwXloMitfG5Oi2wFXHPqA22geBYgYjfR4LADbmx4FtTB0gXliCkiULKeDRhiNGGVasKgBhgAKAAGp4EwHefSQqFX8HLaIcQ1bxO1pUOoZDTb9AIZQNYaw%2BgSPusgKsS8FNODJqpZtUwkrLBmGdQx3aWBNMQFWHYb9DMICuGmH4UtYQAyLFGKWooWQBBOb0F5xoCwRjVB6HZgQ/QpieE6HoWzDg%2BiTEGG5oL0X4u%2BdLXMNogXjzVBszKrYEhO0cAFY6ntnBbgjtTemzN2bc3TogLgIti75WrsVZx1YEYmBYESNZ0garJCBAFLqwI5qNCSDMJIRN9r/CJt1foTg1rSC2uXQKRNXBE1at1SaxN/hJCGsG4m4ryGXVuo9S171m6A1bqDf2sNB6j0LtjWwTgrQWCzgZMmpgTEdxcF1QKLgmqC34CIBZvQMmK1SekDJxQcmG26BSC24pT6CtFadbwXt13B3DqTRVz7QFvu/c1TOudu6F2KnfmYZr66fWXbu4GW75ViejAlgh77XAHUXvTO6iAN7kMvofU%2B0gvO30fq/Q4fnf6BwAaA8hkDYGINQf53BhDSGRWobsxhht2H3Kgn5wRy1IriOkYfRR7YIrqO0YVQxpjmAWNK8ApxvgPH%2BOCeEy6fnoPJNVoh7IKH9aFMgBSAYDjRmrCWHU7EKz2mgHZGg/pggyEwLB%2BsKZ1H5m8CWfgDZ%2BooW/AOa3KlkIW5MtLE8xkbzORIv5BL8UbIRePMhdi2FlLFfnP18aOFhL5Qktpab3kFv6WO/DCy/ltYGw8srtm4V7th3SvlbHUzr7P2/saBnfVoHpPl0U9a6QdrnXKAFfm4tn7I2GT%2BF1WawIo3xs7YO86zgx3PX279YG4NA7w2Hvp3uh72xntjpYAoWc2as4eODoEwAODWaeIOsgYOnuNaPu8mIqugwQ8ObaMGSOU%2Bt%2BHAfaIadEb0qgv%2B/%2BgBwBXIeUs6H%2BJOS6gQm%2BZ2vq26ZBtOEadBiQABUyxKQBuqxKIBBAxKeBEOdAHO16t696b6/Ogu76n636Yu5U/6gGj60umAoG4GYg8udGiubGJusGeAaGeA6uyGmuuGOuqEeuvABuZGsIxuVGu05uvAluayNubGdu1B3G5kTuQmImbuUBHuEgXuggcBMOIAwQgexgqmoeBuEeoqUeAg0GOwVKKmxmFgyeoqqe6eWmre9mjmzeegrmneQ%2BVeZe%2Be/mNeiWORqRjeAw%2BeMWbe8WtewW/e5RVRRRxeOWo%2BVaaBN%2BqOM%2B%2BBABtwbBAonBK%2BgOJA6%2BK6a6W%2BO%2Bow3WlqB%2B/uP2gQgQ/gRqO29qsxDIa2bRoqd%2BtgJ2lOywqqIAkg/gA2pqDI9qWqkgBqXAOqZg%2B2lqgQ6B7Rrqp2G6BW%2BaaxR2jxKq9GocDMkgQAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/laborious_press/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/laborious_press.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/laborious_press.test.hpp)
