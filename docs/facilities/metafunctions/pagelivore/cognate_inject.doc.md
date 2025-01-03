<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateInject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-inject">To Index</a></p>

## Description

`Pagelivore::CognateInject` accepts an operation.
Its first layer accepts an index, which indicates a location in a list.
Its second layer accepts a list of new variables and returns a function.
When invoked, the function injects new variables into the location of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Vs..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateInject
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateInject
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        { 
            template<auto...>
            alias Page = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `10, 11` into index one of `0, 1, 2`. Then, we will instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 10, 11, 1, 2>;

/**** Result ****/
using Result = CognateInject<Operation>
::Page<1>
::Page<10, 11>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateInject` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

`Enrich` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<auto...NewVariables>
    struct ProtoPage
    { 
        template
        <
            template<auto...> class Operation,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to count the arguments from the front.
            Prefix<I> auto...front_args,
            // Collect the rest.
            BackArgs...
        )
        -> Operation
        <
            decltype(front_args)::value...,
            NewVariables...,
            BackArgs::value...
        >;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                template<auto...Variables>
                using Page = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Operation>(Vay<Variables>{}...)
                );
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhr%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrcAGpMZFfQ5AgiYFipAxM/FMBGoamtPBMWL0MlXCbELwOHmoq4mADsFluc0cyFuaAYE0wqlSxFunKItwAbmIvJgYbKacQ%2BQLMDL7rC5dbbeTrpTlMRMDRVPSDozmaymOy4QRkc9mGxSNquULLiqtqkCLcXW68B7YfdbgRRVbAlYpRSAXnviC/ntbgBJFn0NiCP3ZT1nQv5ht1nNOu7YBjm5AIWve8t%2BzNuQPB1iZ9HC9NiuNtjtdmVWaU2rOOpm9/1uTIAL0wAH0CAA6fclyMiie3Kd4Tv4okgEARLCqLdKACORux/ZL%2B93ZMCo%2BBspBtwAtMfTZfsdVQD8okwAB3M0LXoBRI0A%2BVx3FF1UCIZQmGAK0riQ2cYVwpDAOXX12UIoiYThf8KKIkiQI5LkPzRZUDAUT4AHlnmIasBFIaiaOIoNGGHD8LCYZAAGtLmIYAEPIojEJohVz2VAQ1QNWhw11PB0GRWh%2BKIiADIEnYdlPDVDHQGEADYNATd18UPb8TFstNuTQLxBDTBBjVaYAfEYAhPioYhUBYbzjRC2RP3kgT7KTRzmLAj8osELc/IUPjYpo0zblyBoItuV0Jhiy4BKQsTJOk2SmOygDlmMwCAFpmM4hIeIYRqAPxLqiKwSFB0wahQrSjLlmvDSjQ/LKyvKgDIJg3l%2BXg6beoq8SpJkhQJsNTBatmiiv2zA6TQXY6DLovsGKICDoNg5aPkUgCvEyIx4yw40U3jUKMI%2B/EFvuy0FCY5zFylecHWbIs8tQYBmCZEsGG0TBxQLK5LtXDHQMY/dmMhJg2NuNruMaI8ULjDw4b7RHkYcDE/3krHLzwTcd1LBg7ye5DRVQn7UEw7CDNnXrj3FIRWIQXrhbq2jgKuuFkv3AGlqBrmBNFuM0N%2BwWZbwhmTrmgCmYVnHd0B%2BC1cNl6ImAd7sMo1N%2BtoQa1poozdcNs8LzhK8QBYJgJO3W91QfTBn1eN8OfVL8f0N8rryx770P5v64WV80HuB3HnI9uaE7lplbh0vT8WJjq0QgGlUThc3Hucv95w/Brc6IhqwYNmj7XbgSu/OmXjbcRXd0uYBXWZQKEJzjvnte22Bc%2BwJU3FgmkBAROtZTwW4RHsfKyCkH0W7wDe8dJCB6HnfMHHwRJ9jwDrbe%2BeHaT7X%2B0v6/9%2Bzw/zoh9v60bBk/8DjmVYKyY0aMWwAKbMCKUYIIRQgXgSAQMYgqRiAcWMujRuwgnPqbMmPM4yYOyJDGBkDixCC8KkIomB0AACUPheGdtgq4D9bYUKoRkGh9CFCMLjF9IhAh8QaDDDUERXARFhjMEdR00NuG8OYZcVhtw5FMK%2BpTeGmAaYowIKXLi5cp7XnnviLgkZDGpzcKI24XATEGJAEYuEwirGSOkVDSkAAVD4cYIHKWQOlNiCQCAQF9goYcfj8QqIIGGdh1C6EMOdmiNuFgOCrFoJwfwvA/AcC0KQVAnA3DWGsPKdYmxPpgh4KQAgmhkmrAkgESQu4NAAA4zBmAAJytK4P4JpjSuDSmlNIVJHBJC8BYEkYRmTsm5I4LwbawjKlZOSaQOAsAYCIBAOsAgqQETkEoGgFkdAEhRGHJwVQjTrJNWspIW4wBkBKikLuMwvAaGEBIDpPQ/BBAiDEOwKQMhBCKBUOoBZpBdDiKgtxVInAeApLSRkqpOTODsQRFsuMqAqC3FOecy51zblWPqWYW4EAPD7PoFqTEXBli8HmVoVYEAkB7NSAcsgFAIAMqZSAYAUgzB8DoEyYg20ICxHhbECIrRkRQt4CK5gxBkTsViLTeZ5S9l73YgwWg4rgVYFiF4YAg9aC0G2twXgWB/ZGHEJqvAroHB4D1B8eF6oUYIm2OUiITJBnZKRLEbiMqPBYHhemPAoyjWkFtcQWInDHimuAEiIwVTVhUAMLJKk7woJtUyeUj5whRDiF%2BZmgFah4Wgv0IYYwBTLD6DwLEbakBVioFjNkQ1TUiQplMJYawZhJmhvNFgatEBVh2G0dkFwHNph%2BHEWECIwxKijHEUULIAhR16DnY0BYIxqg9EHQIfoUxPCdD0AO61W7JiDEnYsGdthj2LvEXMNoq7p3VH7cUrYEgYUcHSaQCZvApkYrORcq5Ny7n4sJbgF5ZKymUoqXG1YPkmBYESH20gtTJCBF3K0wI/SNCSDMJIWyyRrKtP0JwYZpBRmBC4LuayXBrKNNaT06y/hJCdLQ9ZD98KpkzJAHMuNSzVl0vWci7ZLK2WkqOWwTgrQWB6mlE1JgLES1WNabucj2TnlEG7e82QXyc3SDzUoAtwLdDcvBUwSFRrX3vs/QijgSLNkIluGin9WKrn4zelwRTynCXEsZaSmEYIzAQepYsvjwmEg7NZWFbzowXOco6cImgzsEgCqFcCqVYqJWkFSzKuVCr0vKsCqq9V8KtU6r1Qa9LJqS3muyfgK1jhbWGpU6oR1TJ0uuvqPCz13rkS%2Bu2NkgNQbymhvDUoSNlWbbcYTVhBQyboJpvS5mrTPydOyHzUC7Jhni2xtbVYctnre21vrWpTgTaCDoBbWWiwHav1dp0namtG7D1%2BAgK4K9IQOZ3qWLOjI86ci7vyF94o2QPvnoPY0bd7Q/tjoe2D49wP103oh3kKHCO4cvrWBsZ9FLCNvrhcC79mK/1ydc%2B5hpwH8Bqd82RgLUHSAwbg5QV9xHSOKcw9KfwrS%2BmBCwzhxjrG8ecA41xhZtLeNIA2SisLIXiCie2BJ7FLAFB6iVHqNzu4QITCeeT156ANOfOzUtv58g9NrZ0CAYIxnTPQuxxZtjiKBOovRaoeXivleq/V3GIlEWmWU8CNT4XSz6Ve9JZLoPowldUK3Cr1pW53dbidzp3liXKDJeyZljV5S0/Ze0blsKKq1Uauq5gbVuqxBleDRVs1vXjWWsHfV%2B1TXkBOta4IdrwLOtip6/680A3eBDYjcyMbsb/eTaTSmubwaFv64kMt/5xvC1m826Wttu3K37ZyYd1UnAdhXm2%2B2ztCRu13YQ6Dodz2R2Q70BO8oa6l3fcaK95dQPT03%2BvfUTdTRL0X9f70I98xn/3v3U/yR0AL/2vwAKxwUCfR%2BXM1x0mU4AxWdyV31Ddz7AmDJ1A0pwpSpRpzp1GAQ0GSZxADaV3ECECH8C6UYw0A0FIOlGoz5zgOmVsE40g2FxqRAEkH8FQ16WlCoMaUkA6S4GaTMBY0GUCFgK/QFxYJpVfUeXoIkMYMC2WFWFDUyGcEkCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_inject/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/cognate_inject.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_inject.test.hpp)
