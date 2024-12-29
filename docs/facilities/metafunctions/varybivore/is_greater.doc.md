<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsGreater`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-greater">To Index</a></p>

## Description

`Varybivore::IsGreater` accepts a target and a list of variables.
It returns true if the target is greater than all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &gt; V<sub>0</sub>) && (Target &gt; V<sub>1</sub>) && ... && (Target &gt; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsGreater
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsGreater
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsGreater_v
{RESULT};
```

## Examples

```C++
static_assert(IsGreater<5, 2, 3, 4>::value);
static_assert(! IsGreater<4, 2, 3, 4>::value);
```

## Implementation

We will implement `IsGreater` using only `<`, meaning <code>Target > Variable</code> is expressed as:

```C++
Variable < Target
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsGreater
{
    static constexpr bool value
    { (...&&(Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsGreater_v
{ (...&&(Variables < Target)) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgZlykAA6oCoRODB7evv5BaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3EwvERrgAVZrATAEUjXGFEAB02IAas08EwYvQFJDsICxsQvA47goAOLETCveKAkwBKwXa6c64zRzIa5oBhjTCqFLEa4xVCea4ANzEXkwgK511ZFmuEGxmPMADZtRA8cQCUTMAplVCEUiUYtFsqAgARSHsgF2h0si7A0FMyHQ2Goc3EZGo9E%2BjX6w3E0mAgVCkViiVS250hlM4gAfWlLLZao12t1ocJxNNbj9AatNvtEMdgO%2Bv0O/2r12wqlYj0w7xOVZrf1d5x5eGQKaYCiULQgCfpjOBxC9AFY0WY0RC0ZJSSAQLLvJhFi6Lr3%2B4PhwQIGAwDTx8mvdJrvProvrsuIdhV%2Bv5VuKxxlrRONPeH4OFpSKgnBuNY1jcqs6ytuYEI8KQBCaO%2BywANYgNOkiYhoAAcZhmAAnDhXDTphGFcAEATSJ%2BHCSLwLASBoGikL%2B/6ARwvAKCA9FwX%2B76kHAsAwIgICrAQKSwuQlBoA8dDxJErCbKoGFagAtFqkjXMAyB8lImJmLwmD4EQBroHo/CCCIYjsFIMiCIoKjqFxpC6MkADuxBMCknA8B%2BX4/vBAGcAA8rCIkENcqBUNc8lKSpakadcWlmGqHiSfQYpQVwiy8JxWjLBASASSkUlkBQED5YVIDAFI840LQk5sRAMS%2BTE4TNAAnh5vBNcwxAtf5MTaJgDjtaQEnPAQ/kMLQbX2VgMReMA0K0LQbHcLwWAsIYwDiNNeAMg4eDSsavnCgNsKbDB4TAhR/60HgMSud1HhYL5BAGjRK2kAdxASkotoghtN1GPByxUAYwAKDieCYE5/kpIwQ0mcIojiJZCM2WovmOfoG0oCBlj6LdbGQMsqApPUy2KWM6CQrapiWNYZhMZ9hmHUTXQDfULgMO4njtHooThIMFTDMkhSZAIkx%2BCL6RiwwcxDAkoy1OzPTjK0PN5Ir3QCL0LRy0LCu2KrEt6DMusC/MwvLAo4EbBIXkcN%2BDG%2BcxEUKcpqnqZpaEJRAuCECQypmNBGWwUDywIIyWAJBASH%2BBCmI4RCZEaJIZiSFqdHTlqOH6JwVGkDR0GYlqXBahhOHEVqqEEYnWpO/ZzGsexodcTl/G5YJQWicVpUpTJbCcM0LDSgEilMPyBhGHFOGYlw6G6fpJB4EZyQI2ZyPSKjSjo/Zujzi5bntfbjuMbwzGBcJsKheFkXuxPG3T7P6GJagyXxIHEJmCHWXcR3vfxGJEqr8CopRQJPCq%2BF6LVVqpQBq9lOqtSGgg7qvV%2BqDXeiNRgY0JpTX/DNOaC0lpDTWv9TYeCdrKwOstf8x1kCnSGhdWovkbp3Vao9MhmVXpDU%2Bt9TAv11pGABqAVufBQbg0htDWGv4YJryRhZTesg0Z2X/HvLGgNaZWDxiwwmMcAKkyyOTSm1MNH00ZvEZmOirZKz2s4CArhjbJH5mUeWehRb1AcakaW9Q9YLE1srbWRt1aSzZjYhoqsfHC0Nn0Dxpt%2BjmxcelFYaxbaJIoifZ2nBXZRVUsgcBj854aDVH7AyH90qZTDqQCOTAo6UHtvnQuM8U4BGnDhUiEJU7p0kMkU%2BfkWK2Gbj/Nu8AO5CWCoA/%2BxB%2B6bCHtFFgChpR8mlFwGeYJjQEAXv7QyxlZDr3kVZeQ29lE6BAIuA%2B7kVrHx8g3AKXcQphQirM%2BZizlmYlWWMF%2Bb9UpBwhN/IGPE8rAMKuMwFoCFkpBSGmZZKY3kEBTKoFSfA6AwPqo1Zq3UkFop6n1dmQ1MGCHGpNXy%2BD5piCIe9EhgiOGkHwLtRwVCjqqBOsCBhggmH2RYfdFq7DnpcPejw9IfC/qCPCMI7KoimBgwhlDGGcN3qyPMhIBR1lDkYxOWo4wuMbDaPgMTfRAhlpbEpjjOmlgGZnyZsvFmui7D%2BL8HYrmHinGC18Z4ooWQPFuKyBEg2NrQk6zVrkYJvr6j%2Bu9SbQJgbw2zHifrO2SSIJxrSVcpimT4WqTmQsmULyYVFMXl84O5TW7h0jsMXRFF6mJBnhCCE05CJdLotWgIZd64pr6WxDiFTkKSGnAnEiAQ6IYUkPhLgWEzB1wohCZNZ9OCFuyvbHSLbp19MGcsT6GRnCSCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_greater/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_greater.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_greater.test.hpp)
