<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Amidst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-amidst">To Index</a></p>

## Description

`Varybivore::Amidst` accepts a list of variables and returns a function. When invoked by an index, the function returns the variable at the index from the list.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> V<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amidst :: auto... -> template<auto...>
```

## Structure

```C++
template<auto...>
struct Amidst
{
    template<auto>
    alias Page
    {
        static constexpr auto value {RESULT};
    };
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
template<auto...Args>
using At = Amidst<0, 1, 2, 3>::Page<Args...>;

static_assert(At<3>::value == 3);
```

## Implementation

We want to count variables one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
There are two ways to achieve it.

- First, we can use `void*` to declare unwanted parameters in the function signature, eventually reaching the target variable.

```C++
template<auto>
using VoidPointer = void*;

template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `VoidPointer<I>...` to enumerate unwanted arguments.
    static constexpr auto idyl(VoidPointer<I>..., auto* target, auto*...)
    { return target; }
};
```

To make it work, we need to turn variables into pointers. We will create a helper template for this purpose.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Now, we can make pointers from variables by:

```C++
static_cast<Vay<Variables>*>(nullptr)
```

Finally, we will make a template that generates the `std::index_sequence` and translates the result.

```C++
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value 
        {
            std::remove_pointer_t
            <
                decltype
                (
                    Midst<std::make_index_sequence<I>>
                    ::idyl(static_cast<Vay<Variables>*>(nullptr)...)
                )
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQAcpK4AMngMmAByPgBGmMQgAMzSAA6oCoRODB7evv5BaRmOAmER0SxxCcm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfFJ0gpNLW15nWN9A%2BWVIwCUtqhexMjsHOaJ4cjeWADUJoluXo60hACex9gmGgCC27v7mEcnyGPoWFQ3d48PBEwLBSBkBxzcTDOqF%2BDy8GSMBwAaqg8OhlCjBPE3gARA4ANxR6AAVMcrA8/oDgaDMOCCJcUoxWDTErcHmNiF4HAcALKosZHADsVgF2NJfwpQJBTDBJwyAC9MAB9AgAOjVAEkYfd2ZyCDy%2BQRwZ8QCBwlhVIqlABHLyMDbg9VqlW/FnioV/A6eg4zRzIA5oBhjTCqFLEA6QogHVGXWgQZGo9HhQHEB03J2kcNQokHcbATAEDMR1BEp2LD1ekxCg7EfNrBg55p5w2JCyC0XkkVi8kAyXU8FFpFanVc7kCVBEBjXDutn14P0BoMhsMDvFiW2CiyIyuilttrv/e6UqUyiFQp2I5p4JgxegKIcEDlc%2B4sA1usn3L053vS5lueVKvVNVdB5P2HPVlGIcdUGUJg83LT1K3fT9QKaX1/QERdQ0zSNV28V54OQxCCOQr1jRAGsWFQPElTSJN4mVYiSLeNxGKYr0sD2OkGVYtiDggHjeK9Xl0DGI0CHQE0WCYABrJUzWDS1MBtO1fyA25gI/QTeJNaNY1nZBFVEUSTlHBgoMncEL2IK8b0wO8WRJFkIAYLxaFoFIH0WUsBKYssQK0m4TVw20eO3fdPzCltxX8z0jz7E4iyde5gBrIFGAIezWU0z04XCYADhgvMcQKyCiEK39ktSthBAUJ0XXfSKGoeAB6Ik2vajrmr%2BVq2oAFWwIRevarqWo6saiRGg8ngYPYvEOcEAw2DzMuiw9vxPRK1XuYhgBW2F4Xyw9iufV8Tg0DMuAzMwM0SQKQHK8Ftt2urXSi7ttVQudFSYBQlBaCBD3BW6WSCtd8MSHdcUSMs3vuDhlloTgAFZeD8DgtFIVBOBYyxrG9VZ1nwsxEh4UgCE0eHlmkkAkbMFUADYkYATjMMxaa4RJEiZyR6cuxGOEkXgWAkDRzrRjGsY4XgFBAc7yfR%2BHSDgWAYEQEBVgIFIznISg0GBOh4kiJlOFUAJ6YAWnpyQDmAZA/SkFUzF4TB8CIayJMu/hBBEMR2CkGRBEUFR1AV0hdEugB3YgmBSTgeAR5HUYpzHOAAeTOLW9VQKgDlNi2rZtu2Dgdsw%2BI8fX6DDbYuEWXh5a0ZYICQPWUgNsgKAgFu25AYApGumhaGTGWIBiZOYnCZpLjj3hx%2BYYhLlTmJtEwBxp9IPXqoIVOGFoKfQ6wGIvGACE3Jl7heCwKSjHEfe8BrBw8Gos%2BMeDFezk2Um6P5jGLhiaP548FgZOD48DC3PqQaixAYjpEwNiIEhhgAXCMBTZYVADC7URHgTAEdU4MjRqTL2whRDiH9oQoOahk7h30AglA1hrD6DwDEGWkBlioA8lkM%2B5tPjHGxKYXGlgzAS0ge7Oy8Blh2BXvUFwDB3CeHaHoUI4RBgVGGJdQomQBCTD8Go9IGiGBzCGAkS6EiH4CF6BMOReRjG1EkT0cY/QlHzFUbYexWi9AzBaAYlRRjxEEw2BIBOHAUakHFrwSWuczaW2trbe2khHZ8VwIQEgRxiY1zrig5YCBMBMCwAkCAVN/CJBVEzRIApJAaEkGYHmoskb0yZvoTggtSDCxJgzLg9MAhMwCO0pGkguDM0SPTEJydJbS1lmTFBStVZN3VhnbWHcu6VyNmwTgzQWB4gFObJg/oDAIi4EzFUXAVQv1diQVEehCE%2BxIdIMhSgKGh10NdKOMdp6BOCaElOHB06azOAcbO4ZiDrM2dsvYCDi4HKORoMuqAK5Ym2GYWuEyFaN2bjC1ulcdadzRd3NZGzzagqMPsrg50B5D0oKPUOs9J5rypfPRey9V7gI3ulbeu9k4HyPifWgZ9SaXwQTfDG%2BB76OCfsnV%2ByB35ry/snX%2B/9LiAM2BjEBYDSaQOgUoOBV9EF5UmWg2CChMHYNwYwNelziF%2BxubIchIcMaPOocgvhVhLAMKYWIzG7CMKcC4eJHhjrrCCLCcI1EoiWFdFsc4CArg3GXUUWUQxeh1H1GjaQRNWQvELGsd0MxrjLHaLDaYho9j03OI8a0XN7ii2OPjTXFYax/E1v5u8kZnAAVAq2TssF%2BzDnHISacquqTEX10pqQLJOThj5IaQLIWSQDkVIFMzAUApkhVKtpdD5ozbDjKHY3aZSANaZ0xYsw2xsOBrILiwBQeI/R4i7dSMYzs%2B3nM9rIK5FqA7yDuTanQSRSDPNjufN5SdQ6S2%2BZnP5Ocz3WwvVe/Et6fz8ggOXdFcLibQ3ScipWqLYXt11tiyuIAr0pBSIqG9TNFR3oIN9QFVs%2BB0DJSPMeE9540qYwvJeki17MsEKyvegrMCH2PmIbla8%2BXX0VRfO%2BtjRWh3FZK8B0rQ6ysngq4B1kVW8DVTAzV/KdUYb1RgrBOC8GmpfeaiQlrA6fsoT%2B3Zxg6HOt/swidbD6hn2asaP1AihHxBEU58RNiC3SNkbkPNsblEZpTbopN5adFFDTVW7x7iAv1HMWWkLSWs2FtmAliLpbk2luLT42thMAmTqbcBltkGDjQevXBwECHEluxSSTQdGSR3ZNyZQQJTThZmAOZzJGSMKnEo0JzAUHThkValpuuWbXqaSAFCqZIGhF0LbNvTDQSMuaTsSEBiWnB0MN0CU7Sb%2B3pvbuWJAjIzhJBAA%3D)

- Second, we can use concepts from C++20 to constrain the type of unwanted parameters in the function signature, eventually reaching the target variable.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `Prefix<I> auto...` to enumerate unwanted arguments.
    static constexpr auto idyl(Prefix<I> auto..., auto target, auto...)
    { return target; }
};
```

`Prefix<I> auto` constrains the placeholder type `auto`. Assuming the deduced type is `T`, then `Prefix<I> auto` becomes `T`, and `Prefix<T, I>` is evaluated to determine the legitimacy of the instantiation.

Now, we make a template that generates the `std::index_sequence` and translates the result.

```C++
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value
        {
            Midst<std::make_index_sequence<I>>
            ::idyl(Variables...)
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxAGBAA6oCoRODB7evnrJqY4CoeFRLLHxXAActpj2%2BQxCBEzEBJk%2BfoF2mA7p9Y0EhZExcQm2DU0t2Vwjvf3FpRLlAJS2qF7EyOwc5v5hyN5YANQm/m5ejrSEAJ5H2CYaAIJbO3uYh8fICgToWFTXtw/3BEwLESBkBRzcBAuiUYrEwpH2TFOqF%2B9zQDHWiQI%2B2UxEwNFUrwAIvsCMQvJgjlZ7n9AcDQRTjpDocw2Ci7h8yQ59gBZPDoD6HADsVkFhMpfxpQJBTDBx1SAC9MAB9AgAOnVAEk2RyvFzefyCOCPugQCAwlhVEqlABHcnohluDXq1W/fw3anCv77b37AD0vv2AHUXl4lIcAGwaHF4vCqcFat0IpHOkyRkmofaMHxxGUhhgAd0MgPQCOIwGzggULvuPv2HxleGQ%2BzRH0wqkSxCTRH2fIutAg0fx8euXdQzvhiO7o2AmAIE%2BT6oWXp9JmF%2B1xBFWDBJjRnhv8FiFYo9YoPEoBUvp4MnY/VADVGngmNF6AptaTdVi7iw%2BR8JZ6ax9WlpVlNwFWVLEE3dO5ax1LkcVQIhlCYGdl29VcqRg2sfXrRwmxbQF207G99gANzEck0OwjCqOwn19T/OVPlNFgmAAa2Vc02ytTBbUYdZhzdNk6Lo01e37B9iCfF9MCrRdaJXUVxUA9ClLPakVJJS9c2vBdVTuYBcSBRgCDfITNNDMJgGxFCXiOYkEKQ2zwQMoy2ErFMhPUh41Mwv5fQAKiC4KQt9fzgoAFWwIQIuCsL7kCkKkvi/4HjMbZ0WeV43DRDFTLZSU6R044b2dO4yzM6DLKMfY7ixezap/A1wQ0eFJn2Mx4X8a5TWQ1DjnK4A5JdLy/PuXDGyVJgFCUJoIDq8FurdU1yO8Oz/FPYl/CXbyOCWWhOAAVl4PwOC0UhUE4NxrGsOsVjWOz0p4UgCE0PaljYkBDrMVVw0OgBOMwzG%2Brh/H8f7JHDSYDo4SReBYCQNFa07zsujheAUEBWtes69tIOBYBgRAQBWAhElOchKDQYE6DiCJYU4VRynDABacNJH2YBkCbKRVTMXhMHwIgpJNSZ%2BEEEQxHYKQZEERQVHUXHSF0SZ82IJhEk4Hh9qOk63ouzgAHlTnJrFUCofYmdZ9nOe5/ZebMfYIA8Gn6E7LYuAWXgca0JYICQanElpsgKAgQPg5AYApE6mhaEBYhMYgaJ9eiMJGguLXeFT5hiAuQ3om0Tocee6n3IIQ2GFoDOlawaIvGANwxFoTHuF4LBWKMcQa7wXEulI2T9bbTpTg2Z6wkBGHzvOaJ1dzjwsH10k8AR1vSH74hohSTBCSBQxgHOIw3qWKgDCGu88EwfNDeZTPZeEURxBl8X5CUNR9ZV/Q95QG7LH0PBokxpAJYqBMTpBbizY09lTCWGsGYVG68RYDyAVUGo6QXAMHcJ4VoegQhhAGCUIYkxchpAEOMPwRCUgkIYDMQYZQUFF26KMZoWCJj0K6AIHoTQaEELofWMYLDyFTC4Xg2YhClgKHuusCQOsODHVICjXgaNLbMzZhzLmPNJB8ydrgQgJBDhPS9i9I%2BSwECYCYFgeIEAPogEkP4VU/1/CCkkBoSQZhIZI0OuGf6%2BhOBw1IAjfwXBfpcHDOUf65QQmHUkFwAG/hwzyP1mjDGWMjG4z9kTf2JMTYU1DuHN29M2CcEaCwUigoWZMGbAYGqXB/qqiCedQWuiRZ6GfpLR%2B0hn7yzfkrXQnU1Ya0zjIuRCiDYcGNmTU4%2BxzalhKWUipuw9721qfUp2Lsg5u30f4MwhifZ40yXkuIlMw6oFdkMYppSWYLKMDUrgrVY7x0TsnJW2d063xebnfOhcHC31LiZCuVd9a13ro3Wgzdb7tz3l3c6%2BBe6OH7i3Bpqhh6AlvuPao%2Btp6zwuPPDY50l4r2euvTeSgd4d33lZI%2BfBT4KHPpfa%2BjBb6tIftLDpsgumK3Or0z%2Bh9oFWF/tPQBViLqgIEOAyBG1eWwPgXERBgrxHVAYc4CArgyE4IwdwuYFC8jpFVVqqhGrCFsNqJw5hWRBEdHYXUJhBreFMN1UIvoIjaHSOWKsKRnsfGyL1krJR5y5mVMWTUupqoNDaKFnoj2OzjGkFMeYoYQqYZ%2BICbUlxgoAaCkFP4VxkNokJJ9ZwZJ2NKUE2JqTU2RyDnEAKRsYpNsWAKFIk2UiQb6QfAFuG5pYtZBtJZXfdl78AikH6ZrVuQzvWoyNtks2Fta0c3rY2siLbcwCmdic9ZcRNnbW9sWgOa7g4Vr3W7EAjbEiJCVM2/6SpW0ECmsQFg7M%2BB0AeZQJ5513nV2eu%2Bz5RcfknLLv86u0LMB1wbk3Fuz0IWd1xW3HuDD4WDyRcgEeqLBDoqVpi9OOLF5SQJbwIlW9SWQopWkqlKEaUXyvjfVeTKpYSFZXLV%2BHKdCDqqcYH%2BNgBXwGASKhgLdfTGm/jAywcDFEIL5EgoVFrajoMwWatV6AbU5EobUe1xDaiKcmFJxhvR7VaY4dap1PC9B8NNdgzTBmijOo9RIt10sx15onRwGZdaG1NqXYCFdOjhabM9tutJJizEWMoDIpNIAzC1LBodQ6LjbkaDBoKUJDnFEFtsCk3ZCxrGSEFKqLNGgM1ZeZpGQ64NPX%2BHHcl9GqTfYyP5kl0ZfnqtrziKkZwkggA%3D%3D)

- Note that we only need to constrain the parameter types during concept expansion.
If we move the constraints to the template head, we don't need to define the function at all:

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<Prefix<I>...Nah, typename Target, typename...>
    static constexpr auto idyl() -> Target;
};
```

`Prefix<I>...Nah` tells compilers that this function template is only allowed when `Nah` satisfies `Prefix<Nah, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

We will use `Vay` defined above and write an `Amidst` compatible with this version of `Midst`:

```C++
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value
        {
            decltype
            (
                Midst<std::make_index_sequence<I>>
                ::template idyl<Vay<Variables>...>()
            )::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAHKSuADJ4DJgAcj4ARpjEIACcpAAOqAqETgwe3r4BwemZjgLhkTEs8YkpdpgO2UIETMQEuT5%2BQbaY9iUMjc0EZdFxCcm2TS1t%2BZ0KE4MRw5WjSQCUtqhexMjsHOb%2BEcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnyLPoWFT3jxezwImBYqQMILObgIN1SjFYmFIxyYl1QAOeaAY21SBGOymImBoqk%2BABFjgRiF5MGcrM9ASCwRDqecUURjgA1dFPWaUhzHACyAlQRAYdzpAHYLMdZkxHMhjpjZphVKliMjUccAG5iKmnSWc8Ukml6o3%2BWlAp4M8Gy5nQ2HwthcnlePn8vDoWZ6qyGmmA%2Bmg62Q86ZABemAA%2BgQAHQxgCSTopLtxbo9BChPxAIAiWFU4aUAEcqVjbbGY1GAf4HhLzcda%2BSA0yofjCXhVFD45Wy1EmAgkTC4cw2McACrNYCYAh9%2B2DzBlrl16VNOUKgRKlVq1moY7um60CArY4AWnuI7HE99EtN5v9jJtUM3ZfZzTwTFi9AUCd5uKeLHdsz9kqAguVqNsGeBhpGxwdlWTwLs6fL4sKqDKEw45AXWJiAc8C5wUueDyoqILruqbLat41LYThtaYTWVE4Vghz9hRsF0QuEDoaxVEpv%2BwYEOgmYsEwADWEbZsqeaYIWjDbO2FYwZxdGZiBNrbugu5QoKDBIaKUJPsQL5vpgH6djG9z7hxnErJmZFUhZC6YVeFkOReFrAQ2d4sqiZZPMABKgowBDGfJdZeJkRh4qhHxnGSiFEChaHnD5flsIIChzpWLnOWafrPAA9AAVIVRXFblgIFYVw7YEIw5FaVeXFQ1%2BV1RarxYu8nxuJi2KBVyN6BraD4xk8xDAEFgKhREwDHJapLTb%2BqZQhoSJcEiZhIv49yZvFtrDaN6UPNldLPDKcrhkwChKC0ECWlCG2VtZOpRf4ppkv4KwuRway0JwACsvB%2BBwWikKgnBuNY1jShsWxRWY/g8KQBCaJ9axCSAP2SFGGiSFw4r%2BBoP0aGYABsRNmIEwTfRwki8CwEgaEtANAyDHC8AoIBLYjgOfaQcCwDAiAgBsBCpJc5CUGgYJ0Ak3ZsJwqiBETh5E5IxzAMg8pSFGZi8Jg%2BBEPp/ErfwggiGI7BSDIgiKCo6hc6QugrQA7sQTCpJwPBfb9/1I8DnAAPKXCLuKoFQxzy4ryuq%2Brxya2YxwQB4kv0GqexcCsvCc1oawQEgEupFLZAUBAecFyAwBSGtNC0CCxBsxAsQ%2B7EETNDc7u8E3zDEDcfuxNodSc/DEspQQfsMLQrd21gsReMAbhiLQbPcLwWCCUY4iT3gBL1JqRk%2B8qdSXDs8MRCClNA9csQu13HhYD7FJ4LTS%2BkDvxCxBkmAkqChjANcRhI2sVADCjXZHgTAjs/YDjbpbYQohxAW2NvIJQagfYO30N/FA4NLD6DwLENmkA1ioBxNkReh4fjRVMJYawZgmYvwNrvfBXQejZBcAwdwnh2h6DCAsCoVQ9BFCyAIKYfgVr8N6EMHhowVq1HqAIfokx2H5Ckd0fuDQ5jiJGIkKRcwhF6BlC0dRSxNFrAUFDbYEhPYcD%2BqQRmvBmZhwVkrFWasNYYzjhAXAhASCnFhmnDO/81gIEwEwLAiR9ykFRpIfwUYkj%2BHFJILGZhJBE3pj9ImKRKbU1ILTOGUYiZcCJoEJIgR8noy4D9GJRNrE%2B2ZqzdmCN/4835jnQWgdRZFxLsnGWOxmgsE1OKQ8TAFQGHClwJIUYuCYx1nrEg7o9AINNnA6QCDrbILtroNaztXZtwsVYmxvsOAB2FpcY4IdkTEF6f0wZhxv4xzGRMjQ8dE752Tt4/wZh071K5tnXOqAk4JDFsXX5zzRg9L6Yea5RhRlcCWlXGudcG52w7i3KBSKu49z7g4KBQ8Aqj3Hj7KeM8560AXlAle3915A3wFvRwO9F5A33sgQ%2BUCT7dB9hfK%2BNwb47CBvfR%2B8MX5vyUJ/VeP9JoNMAahBQICwEQMYFA%2BZsDzZLNkCs22QN1loL/hQqwWCL54LCYQ3oJCyHPW1VQmhCQ6H6uMcomRfgICuB0StLh5QNF8IyAInICjhFpA9WI7hbqlFMNkdo71ujbW9DkfMV1hjdGhryD6vR0bFi8LTusTYZi02U12dUzgZyLkDKGTc0Z4zMbxw8frV5vjPlZwCUEkJlALGZOyWMrG4pynilxpIRJysVp7JqbYOpmdua8wFkLIOAKOnSwRJwHpkcWAKE1PKTUJamSzCmZ4g2czZALKVdA1VKCAikE2W7JeOzvZ22ZocoOJzQ5zpVgupdWpV02k9AnIFBdXlvT8V8nmPy/mF3Fh%2B5OIAl2pFSOGFdSRwxroIGdc5ys%2BB0DhZQBFQNUUT3hhh9F/csW/OHriielLMDT1nvPRe8MyVr25cvTeKjaV71UAfEEzLBCsrtuyluXK776T5bwAV79hXkrFb%2BiVwDQHgMgU/BVZsJDKqtkgtVOgj3DOMJgmwer4AEKIauTguUMxmssNQ2xtD3T0LCdI3oLC2EJs4awgxqbfXFGyE6pznqHOSMYSokNAxXOWdUQMDzmjxi%2BbDVowLAbY1ppMRm8256qmXrzfe44j7l0vpBG%2BitXjU4fOHSsOtwTRhhIyTTEAZgxn%2BH8D9Am2N6aVfFAUhLTNOC1I5v48JIBJA/WiT9QIxMkiSCSLjWJXB/D6E4P4C9zWWY1uRuNjg2smu2Ja7N/Lz8EiZGcJIIAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/amidst.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/amidst.test.hpp)
