<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Amid`

## Description

`Varybivore::Amid` accepts a list of variables and returns a function. When invoked by an index, the function returns the variable at the index from the list.

<pre><code>...Variable<sub><i>i</i></sub>... -> I -> Variable<sub><i>i</i></sub></code></pre>

## Type Signature

```Haskell
Amid :: auto... -> auto... -> auto
```

## Structure

```C++
template<auto...>
struct Amid
{
    template<auto>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<auto>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
static_assert(Amid<0, 1, 2, 3>::Page<3>::value == 3);
```

## Implementation

We will label each variable by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding variable from the roster.

First, we need to create a label class.

```C++
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};
```

Note that `Label::idyl` maps its parameter type `Key` to its return type `Treasure`. We will pack each variable into a `Monotony` so that we can use it as a return type:

```C++
template<auto Variable>
struct Monotony
{
    static constexpr auto value {Variable};
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> Monotony&lt;Variable<sub>I</sub>&gt;</code></pre>

Now, we will assemble an overload set and instruct compilers to pull the variable out when provided with an index. Here's the entire implementation:

```C++
template<auto...Variables>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Monotony<Variables>, std::integral_constant<I>>...
    {
        // We bring every `idyl` from its base class to the current scope.
        using Label<Monotony<Variables>, std::integral_constant<I>>::idyl...;
    };

    template<size_t I>
    struct ProtoPage
    {
        // We ask the compiler to find an `idyl` that
        // declares a parameter of type `std::integral_constant<size_t, I>`.
        // If found, the value result of the return type
        // of such `idyl` is the variable of index I in the list.
        static constexpr auto value 
        {
            decltype
            (
                Detail<std::make_index_sequence<sizeof...(Variables)>>
                ::idyl(std::integral_constant<size_t, I>{})
            )::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIABwArKSuADJ4DJgAcj4ARpjEIGb%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BflwatfXZTS0EZdFxCUkpCs2t7fldtpODEcOVo8kAlLaoXsTI7BzmAMwRyN5YANQm%2B25ejrSEAJ4X2CYaAIIHRyeY55fIE%2BhYVEezzerwImBYqQMYIubgId1SjFYXwAKsRMEwFFtMKRTnCEcw2KcANKYB77J6vCbELwOU6hJjxWjAkwAdgs51epy5pwmTEcyFOaAYE0wqlSxFOTGuqFOeHQd1oEBJd1WpwAtI9Tqj0Zi0RcrK9WQARfXM0HgyF8zAwqVEU4ANRaeAZ9CBlII1NpAFkBKgiAwHoa2cDuTzmvzBQIRWKJbaZQA3MReL6siyO4jO2Kulkm/YGt4502G80QqHWy5xgB01fTmfoCjdLypNIIpxeLDlzODnO5YNLVpheMRbEboebtKNmGadHOwcLebNL1Dfct0MumQAXpgAPoEauVgCSo%2B549bk%2BnTPXBHQIBAESwqm3SgAjsmGDsYQf90DySHuQB6f9TgAdS%2BZA0StSUGFOVB4wSWhUCYdAeSnGCqHOAA2DQ5QVEwsNxBBiE2YAEFlBgEASQhDB2Ss/y5EBTlSLwszwAV6UZGEfQYP0BDJNxaxdTAG3JHE/lvCIwWAYgxG3IVeUEGFNx3AgcSPX9yW/HsuVTOjQ1OQCQK%2BWIMyMU5MDg4g7kw7D5SZfCqCIlhZQIBRTliDEwIMBRXLtAgKMFLY0UEHk0ARWitL0rxMlM9i6k431/T4gSsyEx5ROvcTBEwKSZLk5oFPXPAt13VSf2wcTbO/BcIuNIsQSXXsLTLRSiuU041IpBquVPU5lCIohlCYYBrRq7sur0gzQMlBQAGsCLA1AIToBJcRlGgGGQwxrJwuyNAIvldNDAysGOFohMlRiWiRMEJVQdCh2ssS7yynLaFkqN8oIFripU9qgSw8LxqOoCD3Q/gvA2nE/K%2BRNvC%2BNFMVoVs7vm040QILZoKHQ6AKAlHMWQUi8Js3D8LwHz/MTDNBLQsiH3asjUduCZAb0k9w1YyNhTBGNJWlU5YeTDkge5HSIrZrkTqR%2BERpFtmIBxiXuXPJg6EUjKQBYJgZp3e9RSfTBX0YD9Cq3O79wgZL61WMrFaV04KoVCAnok7LpLevLDC%2B03lNK385yNG3xYl1Zb0F2Wldq6rxqj/NdJXZqK2lfcXikzBwUYFzjy5KKImAXqhpTfYjV6/rUEG4aYVTtEM8EBQqqeaPY8Xf8ACp247zv/2BNv2%2BRbAhGRDvu9eXvO67xd3nfT5vjcIUdlSLPf2LJsOeQbcMSUVoIHbTtLm6U4uBxMwcX2R5bwr8s3DP8kw6TIvcxL/Ybejjh1loThAl4PwOC0UhUE4G4aw1geSbG2CmMw%2BweCkAIJoN%2B6wZogECJISsGhJBcBZPsDQgQNBmAwhhZIKQP4cEkLwFgEgNDdB/n/ABHBeAKBAN0WBv836kDgLAGAiAQCbAIExFSFAIBoCWvQYgUQkScFUP4DCaoMKSFOMAZAAopCVjMLwTA%2BAiAZhvEffgggRBiHYFIGQghFAqHUCw0gugj4AHdpKpE4Dwd%2Bn9v5wP/pwAA8tcPhtNJHSNkfIxRh8UFmFOBADwwiVoHC4KsXgzCtDrAgEgIRqRlpkAEck1JIBgBSBPjQJGCQGEQFiK42IEQWh3AcbwUpzBLLuNiNoTADhKmkCEWwQQ7iGC0AqRYrAsQvDADcGIWgDDuC8CwFrIw4gel4DRA4PAcERl/1FI064uxoGu2IX/W4xlykeCwK4j0eByGjNIBZWIGRMCTgmcAW4Rg4HrCoAYYACh7R4EwNY9x%2BJmm6OEKIcQRifmmLUK4qx%2BhDDGGAZYfQeBYgMMgOsVAi9sgjLVH8C4RpTCWGsGYGhFktFCXgOsOwjSGguA2tMToIQNpDAqFUPQRQsgCApfSjIjKGA0pGIkI%2BxK5kCH6FMTwHQ9A8oaPyhY5ROXCvmMy7l8wOXLC5USsBOwJBOI4F/Ug1DeC0NOL4mRciFFKOCaE3AhASDnEgdE2J9z1gUSQqMCACCQCSH2JWAAnPsFkkg0FmEkFhbBGE3X6E4KQ0g5CoGVgwlwDC/g3X%2BGjcgrggQPUYU1a42h9DGEwPuWwzhiTuFeOuOQSgGSRFiLYJwFoLB4wsjVEwQUBhTJcDdZWLgqC1EaJIHKPQPz9H/OkICpQwKLG6BPrYpg9jRlqo1VqtxHBPG8OuLTKtNa60NvBYfFtba9phMWikkRFr9hmBidmlhCSkl7tScWwRl6REgBXbW06Rhm2zDyTdQpxSLHVPKc079tT6kkuaa0zOHSumuN6f0wZtBhnNPGeCqZf98CzMcAs1xyzkCrOaRs1x2zpKWT2bsP%2BhzjnQLORcq58G845seUNF5byPlfJOb2v5hiB2yCBeYv%2Bo6wV3MxVYKF2y4WOv/kiqMnBUXXnRXx7FuKEj4qE0SuoJLshkvcIKmYVL0DyrpUfBlDQZVpFZQ0bToxuVKd5Y0aV6nKUir6HKxYtLTNzAGAZ3krQTOKo2FsFV0Tg3qpcRYnVD611Pvzs21tqCTWdolFEk9cT4GkDtVgRIwniGhvDS2tBLJk0skwZIX1sij6zozbYLN8WEl5qQDwvh17S0JHLbsKt/iWAKHjAKeM4WywTA7WarRPbZB9tY8Y%2BQQ7OM6BAPsUg47J2OL8zO9NHjC3I3Qk1uRLW2sC061aCYoTwn7siZA5%2B1qz1sIvREtJJbb2jDa6kVI24Otuu3F1ggG9iAsFkXwOg77KCfr/n%2B7p0D/t1IaU0k5wH2mdO6YhzAfSBlDJGdAuDkzCNjJmcp1DFj0OYZOdhixuHdkYBRzAjMJHeBkaUBRyZVGTs0eea895nzGDfIGyxiQbGTGjZBRNnjEKsUCZhQpkTDQRn/jEtJywOLtV4rlAS%2BFPRlPOAgK4AzYQHOSt00Z7IBm9PZA88K8zoqrN5BswbuzAw9eypc9ZqV5u1cKtVV58BDviHzcC5wSUb3mutfa1tsEO2ICms0Yeq1p74m2vRMlygar0tJBbfsfYgQcHoMofHlkMa01u7oaVphNrSCIMkIEd1gR/B4LdZIN1mDPVcEm8Q/YAWaGcGO2HvzqiM8N6z%2BV9YFlMjOEkEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/amid.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/amid.test.hpp)
