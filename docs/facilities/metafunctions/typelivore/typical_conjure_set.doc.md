<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalConjureSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-conjure-set">To Index</a></p>

## Description

`Typelivore::TypicalConjureSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

<pre><code>   Args...
-> Capsule&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
TypicalConjureSet
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalConjureSet
{
    using type = RESULT;
};
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = TypicalConjureSet<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will traverse the element list and only collect each element's first appearance. We do this by only collecting an element into a capsule if it has not already appeared. Then, we will concatenate all the capsules.

We will expand the constraint `Prefix<***>` alongside the arguments to skip the examined items.

```C++
template<typename, auto>
concept Prefix = true;
```

We check if the element we are inspecting has already appeared using the following static member function.

```C++
template<typename Inspecting>
static consteval auto idyl
(
    Prefix<I> auto...front_args,
    Inspecting,
    ...
)
-> std::conditional_t
<
    (...||std::is_same_v<Inspecting, decltype(front_args)>),
    Capsule<>,
    Capsule<typename Inspecting::type>
>;
```

In `std::conditional_t,` we check if `Inspecting` has appeared in `decltype(front_args)...`.
If so, an empty `Capsule` is returned.
Otherwise, `idyl` returns a `Capsule` containing `Inspecting`.

Here is the entire implementation.

Note that we wrap the elements inside `std::type_identity`. This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct TypicalConjureSet
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    {
        template<typename Inspecting>
        static consteval auto idyl
        (
            Prefix<I> auto...front_args,
            Inspecting,
            ...
        )
        -> std::conditional_t
        <
            (...||std::is_same_v<Inspecting, decltype(front_args)>),
            Capsule<>,
            Capsule<typename Inspecting::type>
        >;
    };

    template<typename>
    struct Hidden {};

    template<size_t...I>
    struct Hidden<std::index_sequence<I...>>
    {
        using type = Cotanivore::TypicalPaste
        <
            decltype
            (
                Detail<std::make_index_sequence<I>>
                ::idyl(std::type_identity<Elements>{}...)
            )...
        >::type;
    };

    using type = Hidden<std::make_index_sequence<sizeof...(Elements)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEElz%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWKkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/ntbm4mKkFF56AyDkyWWymBy4VyeaxMAA6e0iy4TJUObW6/X0VXk66UjwtBh4ABuJHYIAAKty8KJaMomBNMEaziDeR9UkwttrUP6gyGYQB2NXAq7M1nslWW7mMG3222O51eV0R1JRsSx%2BP5qx5%2B5e9W/Ha3CxxhM6pQgb0ls0WtxWqtsKnpgDWmHcsiYEQSdcVDclTZbMbjU9jyCXK8Ea8ixEdJgLINud9uXkyRgVldl8qPJ48Z/Xl8Chev3Z/t6Oz9gASpgyAbJkgbDkOY69pcE5lhicK3veSHmuW06VimNZorckJxp8X4tD%2BlykGhd4YVOM64Q6gTYARBgKMRq4/jYlEvtabA1tg9BsIITr8pxtHVvafEsowBAWAoFFXPeXGzna9oAPIEAgCQKCh6JXPWjaRtGbZTiR54JMCcISQJBBOnhDH8iZ7H4pZUkybZ2D8mpGnEAobkYje8n3o%2BETAIpb63LuhkHiqAV3vinEKQ5F7mW4zmCT59r8ql0npbWdnxfenmaXhMWytgIAgDOPbAl2VV%2Bd2CGagCTVJhSdwAJKlpJZ6NImQKNc1/xAiC1FYaJPHifxUlaQxIJ6TuBliF%2B2gbJgQiYAQfmFgpI2cjhNqOgpc0POta60B2AG1SVO1wpkABemAAPoEDWbUHfeR2PKRtD4kS5URFgqgPUoACOyrivibW%2BTNJXXltCnoaayEVtxCZtQwCjPA4wVvfDtxzI4yAEQI8aBmIApCrceDoMi30lQpED5bj1K0ngqgQ/hgpEDWVDELID2tMAsmM/DaMYxBjhGHJly47jxXSzLyzCwAtPhv0oAI%2BCNGIT3C3FdMyxAeF5m415uGreAKEDNoPYGEPo5jEvAPyWCQjO1C84I/PEILisMaswsJe6BpYWiUsy/DOp6sHu0o7cosO8F5WVdD8u42SQEwzVGdFqnCqI5hMdKTjeNbq6AASVNYAw51Z/%2BV351Od2Pc99qvSnh2l5KFfEowP0EOgf0MADQOYKDrxYZD9Hou396w8LQXPjOYV%2BoYOY0uVEWtlFuuofruMu7QlV7/DDPH%2BHn2nX3A8gCwTBLg9/2YIDINg1s7MzTP4e4391O0BAaszgflXRwXInKTUENNdEN4uw1kVmfe8yw5bhzREnSsVUFIXWzpxBeIUl6wnlN3KuV9yq33vo/Z%2Bo9X5YSbqgKgNYIBZQUL7aeZUKpoKwbXYCA1AQakpNgVQrA2QJm%2BLw7hjJvSYghFCBM%2BIxRbFSAQSBXC7iRw9MI8RxYG6jT2uNXKOknSdzdFHT0WDWoHFuEILwqQijLnAh6SUIirg4IsVYmx6A7EGklPgoxaj8QRAIPyfxexAmCAOOnOuPo7geMPr1EEzjoleLlOFBatAlorTWhtOE/iQkEGCZTUJeSgl7BQWw54l1InmLDB8BxGiDHmijPzFiCQCD/37uVBQ1s4z4gSfySx1iMi2I%2BJ4tEvsLAcFWLQTg/heB%2BA4FoUgqBOAm0sNYPG6xNgyLBDwUgBBNDjNWAuAIkhbQaAABxmDMAATkuckM5pyuB5jzNISZHBJC8BYBIDQGhSCzPmYsjgvAFAgG%2BbsuZ4zSBwFgDARAIB1gEFSAicglA0CsjoAkKINpOCqFOQANiVjiyQtxgDIEJlIW0ZheDLkICQKmeh%2BCCBEGIdgUgZCCEUCodQYLSC6C4KQAA7sQXUnAeATKmTMvZCzOAqQRAiyUtDbjYrxQSolJLbhkrMLcCAHhUX0GIDCLZyxeCgq0KsCASAUXNl1UiiAFq0WJGAFIMwfA6DMm8pQWIErYgRFaMiYVvAvXMGIMiFSsRtDiz9aQFFVkVIMFoL6rlWBYheGADqWgtAgXcF4FgW%2BRhxAJrwDSLGMEM3zKfhBBE2xtn%2BPqBKpEsRBVBo8FgCVio8AfMzaQGCxBYgDMeDm4ASIjB7NWFQAwgsABq7w%2BUqR5BG%2BlwhozMukPO9lagJU8v0IYYw1hrD6DwLEIFkBVioAUdkDNSsiT4NMCsywZg/lduIFTD48BVh2HFtkFwQ9ph%2BF5WEdcixRi8qKFkAQ369DAcaAsEY1QejvoEP0KYnhOh6DfVjeDkxBj/ugyhjDYHeVzDaFByogHX3rK2BIUVHBpk/Ilf8hVuL8WEuJaS45GqGGaxIPqwIXBDU7OHasDSTAsCJAgAckAkhAi2kuYEJ5GhJBmEkDir5/gcWXP0JwN5pAPncdtDirgOLTmXPuTi/wkhkjSZxTRrl/zAXAr42C010KzWwplYiigNrUA6vRZijgrQWCBjzErJgTEt1qsubaLgJzKUccfQPXl87GXiBZSupQa6uW6CdQKoVmbKPUd%2Bbwf50r4UIluPKxVjGQvPi4OFyLGhNXastQkLjZhePGvBc521Vr3OddGIRIw1WuDfJoIfTS7rPXeqDRGgNPqQ1hocBGqNUkY1xolYm5Nqb00RuzVuvN8z8CFscMWiVZbILMgjdWl58y60NuRE27Y8zW3tu2V2ntSg%2B07cTg5vgY6FCTswNO2dHaEuLokMu2Qq7OXzIy5uod16rCWD3Qel9CzT3E04Be/uV6d23vvQkWLz6j2wbQ34CArg8MhCHkRpYQGMggZyEh/INPijZCp4BonjQEPtAZz%2B9nfQMOs5gwRrneQedC4FxRtYGxyM8fU1R8V1nOD0aVYSvrIVqsRZOZq3A1K9WYh40a/jpBBPCcoJRzT2nwtybzP4S5jzAjycU2ZqzfzOC2ZBcOiFTmkBwtldanrxAMVsE4H55VLAFCBkJoGdXZYJjRZ17S%2BLshEtLtZfIVLkOdAgGCFl1Ifrcvy5dxwIrsrStUAVaH8Pkfo%2BYQmPVzzjXddgkCK1j3HX692r9%2B33VIAI/WJttVh6MeCAPVUAS51I23UQA9Vy6bk2O2z%2BDaG8NHbFuCGW/GvbmAk0prEJtjt23c33azQW99R2uUnYredwQNauXXZ9Xdltj6nu8Be72lkH2h1fdHUwCdU6Z2MDnSTxB2S3B3T3XSzxh23RvRsDrUPVExR0aAzR2F%2Bjh2sDvQKwfSfTgNfXqDgxJzJ25z0D/XKGwyZzp3JwgxZyw2I0F1wOJ053J1Qw5352oOp1sFw0IPwxYJIJoIlwUDI2ZXz2dwK0V1H0JTDwj1uCj3CyHy1xiy4313sxNQE0wCE1GHgJeXNxACuVtECECH8H8Dk0Gw0D0LzAM2EMlQBVsDsza2WDE0kH8CkweTzC%2BVOUkBuS4HOTMEsxeUCALxEKsNsMowpQsJsyUP2U7U0g/UkCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_conjure_set/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/conjure_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_conjure_set.test.hpp)
