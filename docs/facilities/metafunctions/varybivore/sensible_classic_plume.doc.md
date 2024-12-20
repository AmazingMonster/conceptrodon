<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensibleClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-classic-plume">To Index</a></p>

## Description

`Varybivore::SensibleClassicPlume` accepts a list of variables.
Its first layer accepts an operation and returns a function.
When invoked by sequences, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects the type result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Variable
-> Operation
-> ...Sequence<sub><i>i</i></sub>...
-> Operation&lt;...Sequence<sub><i>i</i></sub>&lt;Variable&gt;::type...&gt;</code></pre>
<pre><code>   ...Variable<sub><i>i</i></sub>...
-> Operation
-> Sequence
-> Operation&lt;...Sequence&lt;Variable<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>
<pre><code>   ...Variable<sub><i>i</i></sub>...
-> Operation
-> ...Sequence<sub><i>i</i></sub>...
-> Operation<...Sequence<sub><i>i</i></sub>&lt;Variable<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>

## Type Signature

```Haskell
SensibleClassicPlume ::   auto... 
                       -> template<typename...> class...
                       -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct SensibleClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensibleClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensibleClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::SensibleClassicPlume`:

- We will pack `0` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<auto I>
struct ZeroStar
{ using type = std::integral_constant<int, I>; };

template<auto I>
struct OneStar
{ using type = std::integral_constant<int, I>*; };

template<auto I>
struct TwoStars
{ using type = std::integral_constant<int, I>**; };

template<typename...>
struct Operation;

using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

using Result = SensibleClassicPlume<0>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

using Result_1 = SensibleClassicPlume<0, 1, 2>
::Road<Operation>
::Rail<OneStar>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

using Result_2 = SensibleClassicPlume<0, 1, 2>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::SensibleClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // Multiple Variables
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <typename Cosmetics<Variables>::type...>;
        };

        // Multiple Variables
        // One Sequence
        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <typename Cosmetic<Variables>::type...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<auto Variable>
struct SensibleClassicPlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // One Variable
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        using Rail = Operation
        <typename Cosmetics<Variable>::type...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMzSrgAyeAyYAHI%2BAEaYxCAAHACspAAOqAqETgwe3r4B0umZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsm/m5MXkQAdJcAai14TNH0CkfYANQmGgCC48ReDi9CjEyD0wbgMCkyyGUeUw7w%2BJgA7FZPi8US8dnsDjDjuj9kxDtiAJ6pRisTCXc7PF7IMEKF4AeWJxDx2WesNRL2%2BvwIL2UxFQRAASqgmOg2aiEUiPuz2QB6GUvACyXlojn2mBeN2Id2BT2R0pRcsVytV9H%2BmAAjl5GJtdVL9Wjdrj8W4cZijiczqhyZTqUxweSPAo2I5kE9/NgxfrOX8ACKYZp0SPSiVJ%2B0vLyZIxoonqo4x%2BmM5kCVP290EHPMNgvQPBvCh92a7WPZ4gEDl4ne8NHSVphEx7uwksG%2BVKlV4NUa273Zt6/WGunhM2W60w2fS114rEux1u46nC6XH006sZWumLtr9nR7lxhO0d01%2BN11mX8WIofSjNhYDZ4lvfz5gycRFgwH7smWFakieQZPuebiNtOmBhtgrbtmSh5dv4PalvC/ZYYOr4ohuzrEVu%2B5ehhry%2Bv6lyPiGyEfl%2BWYCkwdD/vmt6sfexx0XWCidihbY5gOa59iJcJrqRZY7puEHEpW6EUuGVI0uSHzAMQmC7IwBAMWuTE/kKIrsTyfKCsKorHOpmnaYI/GUeJYn4Z8BEfFJe6epOWqIS%2BXwED8fwAgwQL0KCfoQlCPhbghwK%2BSmkkySRiVbmhCkCSp4UFsBDS%2BVe/lcqZ/KoEZoqie%2BhEvPOi4xfQH6GqOJrqgCy4MDaH7uduGKyR5B5KVRqm0aesF6Xa%2BoGS8LFsXmWVMjlFVySSVa8fWxw1VigloQJ4ngbhjkJV1SUHSlkFsOl1H2ec1laWwdm5ai40lSZvJFSV7pXbZulbc5cK7d9sIygAVEDwMgzK/3AwAKtgQgQ8DYOfIDINI/DElwmY/hhNSXhYP%2BbhoK1mCpLpcWfB15EvAAkr514vAAWnEqB9MQg6IummY/mhJnjOgrZhDsGliAA%2BvjsyCO6fOkJTrJYW8v2SrCZOeVTF5%2BQF3ILpgTMsxYbPfr%2BuYARyBA8yAfOYALtDCwIosEOLgiS8r2AA92st4fLpPJe65OO7CNMQwA7ozEy2hKutZpz03c7zgjm0ylsi80YvHBLUvhkDLtOe7bme4S8mkltnw00Bs0sn9CPyhDSHchornjUIXipEUmDoAKSHGiZxcgYOxxJlHpsxxbVvBYntvJ/bLw1%2BGpC98b0f83HQ823bBCS5PTvT2ufdm4PCeGKPbgp2v6cuZhWcPW3KomUFIUgjSdaRWw7pr7Cravccnc5Srr9ce69N8kzksNYAJeAHIOLQGJlz8syZAgtwpxAIBAPuChSSwLDG4VuChjSS3ro3DIzcMHGmeEsPaHxDSV3GC8Lgtd2b/Abk3FuF8CCCy4B3Qsc04Q903rPfu88ha7yTgfceR8N6jSNibbeC9%2BH7xTlQtOIi8riIHpI62I9l6SzMM8Z2J8IyQPPpglUzCr6AjwMCMK4J77QifpLLg6jfKvwsu6D%2BpcIyfG/omd%2B4Qtan1crMEMqClCtEQdw5BbBUHugIQYmxtDcFKAYfophsjsDEMgWQquLwNEuU%2BHXOheC4nGkFmYVh2UWQnzcDPRRvD44qL3moiezx5Goi3kovh1SBEyM0Q0lETTKmL1UWPFe6TNFaI4Tos%2BNCIlMMKdNa%2BJjQp30hJY44GhrG2K/iAN%2BbgnHFjWZNbibg/5gLIPSTxExJagKZhArOvi6z%2BPgUEk2ITMBhOOBMgp2CcmxNeRo8MySLAcBWLQTgSReB%2BA4FoUgqBOBlMsNYDkawNi5nRjwUgBBND/JWAAaxAEkSQ5wNCSC4PCfwGgkgaDMAANnJWYBICR9CcEkLwFgEgNDLNBeCyFHBeAKBAMs1FYL/mkDgLAGAiAQBrAIKkM45BKBoD2HQOIERSScFUAkclABaclkgXjAGQMgShuKzC8GboQEgeAeY2P4IIEQYh2BSBkIIRQKh1D8tILoGx/smSpE4DwAFQKQVoohZwOkZxJXclQFQF4Kr1Wau1bq/V5xCkQA8HK%2BgxA3hIqWLwPlWgVgQCQLK1I8qyAUAgAWotIBgBSDMHwOgOxiDcogNEAN0QwgtAJN63gLbmDEAJHSaI2hMAOA7aQWVN0CALloO2l1WBoheGACcWgtBuXcF4FgFghhgDiGnXgTSDg8AADckIBswKoQdZwtjIrNoCl1tATFMh7R4LAAb/J4CZSu0gh7iDRDwXGddRhb1GDRSsKgBhgAKCuHgTA/sgKguRZa4QohxB2vg46tQAa3X6A3Sgaw1h9AmO5ZAFYqAibZGXWq7meZTAwssGYdln6tRYAIxAFYdhB0NBcAwdwngOh6BCGEIYlQRg2KKFkAQUw/DCYyKJhg8xhjxBsaxvdAgmZtG4/kBTdQ2O9AmAMfjCwhO2B0%2BJvQsxWiycE/Jlj8LNgSF9RwYFpA2W8A5ZG1VGqtU6r1VIBNLwIC4BNWm8w/guCZpRUBlYCBMAihGMx0gWLJD%2BHOAATn8PCSQ%2BKzCSHJSypI5Kkt0o4Ay0gTLgvnHJVwclCQksJAqzirgSQUvkscwGjlXKeVhf5bmkVeaxUhqlSWstqbFVsE4C0Fg%2B74RqqYBlLMXAkvnC4Hio1%2BAiAMb0PB61SHpAoaUGhl1uhq0eqYF6lddmHNOcDRwYNEqzgvHDS8MbE2pszZ/HNhbeLfPJsLam9N/gzChezQKnrg24jStLagFNIxHuTd9EYObXBlk0BVHEBtTaXVdrbcOjHPa%2B0DqHe%2B0dOkJ1TvBTOudC6l3DrXRurdpOd1acPcu8FJ6z07GHVegNt7oj3oJI%2BrY4KX1vuRZ%2B79Shf00%2B/EBvgoHwOQeg/JYdG3EO2u27IVDzrwUHcw4BqjVhLB4eiExojJHracHI8bSjOGaN0biAxo9hHuhaecBAVwxmbF8fKHJvQImGhu7SFJho5nFgaZ6MpozamJOO6U40HTQeDOmdU3kSPCe4%2BWdWOsGzIWCvnZa5wB7xBxuTem7D1783FsaF8/51bv2QtZvC6QSL0X4ixevUVkr838Xwga/CIlkhMuapsRd1rth2uA66/AHr4rQ1g5B8QYbWwxsxpYAofder91vcxOMZbAWzXrdkJtlX9r5C7Y1zoAIpAjsnZ9dn/1LqOXXdDXdiNi%2BtXL9Xy8df83N/ciTRD77cRft/AAcpdgc/8i0Z8wDU0QBV9G5BZP9BZv9YEC9NUa1kd61KA0dwVscp1kVsDcc2Nh1CdBBicA0yd50xBKd31qd/1%2BdV16c91Gdj1T1kBz12cY5r1wUucec%2Bdn0tQhdeARcf1dgJdANOtpcmAwMIMoMYNFd99lcJBVcHUT90Nz8DAdcrcbAucjcIUTdgpOAZQo5ddrBaNnN6MzV7dYtFN2MXdOM/cPcBNg9/dihsg/cfdshU8TNNNo8VM/crDtM5g9MvcFNw8k8TNY9AiLNbN08EUojr0c87888X8Xg3818N9NwKE/MVsSAa9gDOsIsossBm87M28QAzB5t/B/AkhSUCUWUKj4RKtmsEjOUR9eV694skhkskgEgKUktJAksiVUsuB/ACt/Bb92VOA688iCtDVGjxjmix8VhP1MhnBJAgA)

## Links

- [source code](../../../../conceptrodon/varybivore/sensible_classic_plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/sensible_classic_plume.test.hpp)
