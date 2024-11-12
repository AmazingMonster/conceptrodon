<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Amidst`

## Description

`Varybivore::Amidst` accepts a list of variables and returns a function. When invoked by an index, the function returns the variable at the index from the list.

<pre><code>   ...Variable<sub><i>i</i></sub>... -> I -> Variable<sub><i>i</i></sub></code></pre>

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
    alias Page = RESULT;

    template<auto>
    alias UniPage = RESULT;
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
template<auto V>
struct Typify 
{ static constexpr auto value {V}; };
```

Now, we can make pointers from variables by:

```C++
static_cast<Typify<Variables>*>(nullptr)
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
                    ::idyl(static_cast<Typify<Variables>*>(nullptr)...)
                )
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSZqQADqgKhE4MHt6%2BeqnpjgKh4VEssfFmXLaY9oUMQgRMxATZPn6BdpgOmQ1NBMWRMXEJSQqNza25VWN9A6XlIJUAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHp8hj6FhUt/dPjwImBYyQMQJObiY51Qf0eXnSRkOADVUHh0MpUYI4u8ACKHABuqPQACoTlZHv8gSCwZgIQQrslGKxaf47o8xsQvA5DgBZNFjY4AdisgpxZP%2BlOBoKY4NO6QAXpgAPoEAB06oAkrCHhyuQRefyCBCviAQGEsKolUoAI5eRibCEa9Wqv6siXC/6HL2HGaOZCHNAMMaYVTJYiHKFEQ5oq60CAotEYsJA4iO27O0gR6HEw7jYCYAiZyOoYnOpae70mYWHYgF9YMXNNfNG/wWIViimi8UUwFSmkQ4vI7W67kAFQZeCoV2Onbbvrw/sDwdD4cH%2BLEdqFFiRVbFrfb3YBDyp0tlkOhzqRTTwTGi9AUw4InO5DxYhvd5Ie3tzfZlLLcCrKvqWpuo834jvqyjEKgRDKEw%2BYVl6Vaft%2B4GNH6AYCMuYZZlG67eG8iGochRGod6JogLWLCoPiyqpMmcQqqRZHvG4zEsd6WD7PSjLsRxhwQHx/Heny6BjMaBDoKaLBMAA1sq5ohlamC2va/4gXcoFfsJ/GmjGcbzsgSqiOJpzjskk43KcV7EDed6YA%2BrKkqyEAMF4tC0MkT5LGWQkseWYE6bcpr4XafG7oe34Ra2EqBV6J79qcxbOg8wC1sCjAEI5bLaV68JhMAhxwfmuJFdBsHwf%2BqXpWwggKM6rqftFTWPAA9MSHWdV1rX/O1HWjtgQijp1PVtV143EqNR7PAw%2BxeEcEKBpsXnZbFx6/meyXqg8xDAKtcIIoVx6la%2B76nBomZVIcSSHP4wUgMVVW7fV6qNWthlKkwChKM0EDHhCd2siFG6Ef4e54v45YxY8HArLQnAAKy8H4HBaKQqCcGxljWD6awbIRZj%2BDwpAEJosMrLJIAI2YqoAGwIwAnGYZjU1w/j%2BAzki01U8McJIvAsBIGgXSjaMYxwvAKCAF2k6jsOkHAsAwIgIBrAQyTnOQlBoCCdBxBEzKcKoAActMALS05IhzAMg/pSKqZi8Jg%2BBELZUlVPwggiGI7BSDIgiKCo6hy6QuhVAA7sQTDJJwPBw4jyNk%2BjnAAPLnBr%2BqoFQhwm%2BblvW7bhz22YAkeLr9DhjsXBLLwstaCsEBIDrFkV1rEDN3r8TAFISQ0LQKZSxA0RJ9EYRNFcse8KPzDEFcKfRNoXSy8TOu1QQKcMLQE8h1g0ReMAkIeVL3C8FgMlGOIO94LW3S0cfaMhl05xbMTDG82jlzRFHs8eFgSdPngQWJ9SC0WINENImAcTAkMMAS4RgyYrCoAYPaSI8CYHDinRkKNiae2EKIcQftcGBzUEnMO%2BgYEoGsNYfQeBohS0gCsVAXlMjHzNl8E4OJTDY0sGYMWoC3YOXgCsTo3RnAQFcJMPwVQQhhEGGUYYVR8gZAEJIvIaRlEMDmEMeI0wahLx6OMFong2h6BEXUXozQtHyJ0bYQxqjpiGKsQsauqx1ibAkPHDgSNSCi14OLHOpsLZWxtnbSQDsBK4EICQY4hNq61wQSsBAmAmBYHiBACmCR/CqgZv4QUkgNCJC5sLBGtMGb6E4PzUggsiZ0y4LTY2DNjZ1IRpILgjN/C0x8UncWktpYkwQQrZWjdVbp01hQduqBy760NhwJoLB8SCjNkwAMBhERcAZqqLgqoH4uxIGiPQuDvYEOkEQpQJCQ66CSJHaOk9PHeN8cnDgad1bnEOFnCMxB5mLOWfsGBRcNlbI0KXSZLdsQ7DMDXfpcsG5NxBZ3NuHcK4gDmQss2vyjDrK4BdPuA9KDDxDtPcek9SCEtnvPReDhiWr0yhvLeSdd770PrQY%2BxMz4wMvmjfAN9HB3yTo/ZAz9iVvyTp/b%2BVxf5bDRgAoBxNQHgKUFA8%2BsCCoDKQfBBQqD0GYMYMSw5%2BDfYnNkMQ4OaNLnkPgVwqwlgaF0KEejZhWFOBsMkhwy11heF%2BP4WiQRDDqi1EyC4Bg7hjFTCCEGpxCiUjqLqPYqNBRMgRpsWYgxfRY3JoEBY/osj5iRpmBMENUjbGzGzdojxrj8Zlt5vc7pnAPlfKWSsv56zNnbIibsyusTIV13JqQJJKThjpPKXzAWAQNkFMFIzQUgp/CFMtlUB5PTbB9O7Q3IZSA1YZwRXCiuBs2CcDmfnFgCh8T%2BnxM2mkYwnbtv2R7WQRyDX%2B3kGck1OgAikGuTHE%2BdzE4h3Fs8jObzs4Hqtkek9BJz1/gFBAMuoKO3sy7QM4ZiK4hbqmfEE9yRkhKjPQzJUF6CCfU%2BZbPgdBcVDxHmPWexLSVzwXkvKlky160u3pyzAe8D5iGZcStlF9JWn2vvo3lId%2BWCuAcKkOorx4Sv/rZGVvA5UQMVeylV0K%2BDII1WgjBWDdV3v1RIQ1Adn2kLfas4wVDrWf3oYOphdRj6tRNG6nhfC4gCKs8IvRoi/DiKDbGmRJRS2KOjZkWNSi6iJtMR58xdiC0Rf9RmxxJbrGmOizkQteas3%2BaSy4hQeN3EuKrT%2BsWtbgOHFA6eiDQIoORNdjEomCHoWJOSakygnjKmCzMBs9mCMEYFKxRodmgp6ldN/ZwXpMsEmkEppIQUqoZ0aCndN02tMNAIw5kO/whW/GjahfXTxjthtFYljtntoD0jOEkEAA%3D%3D)

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

Now, we make a class that generates the `std::index_sequence` and translates the result.

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

Note that we only need to constrain the parameter types during concept expansion.
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

We will use `Typify` defined above and write an `Amidst` compatible with this version of `Midst`:

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
                ::template idyl<Typify<Variables>...>()
            )::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxAEAnKQADqgKhE4MHt6%2BeqnpjgKh4VEssfFmXLaY9oUMQgRMxATZPn6BdpgOmQ1NBMWRMXGJto3NrblVCmP9YYNlw5UAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHp8jT6FhUt/dPjwImBYyQMQJObgIV2SjFYmFIhyY51Qf0eaAYm2SBEOymImBoqneABFDgRiF5MCcrI9/kCQWDKackURDgA1VEPabkhyHAAq0LwVCuxxpAHYLIdpkxHMhDujpphVMliIjkYcAG5iCnHcXs0VEqk6g3%2BakAh500HSxmQ6GwtgcrleHkAWTw6GmOqs%2Bqp/1pwMt4NO6QAXpgAPoEAB00YAkg6yU7sa73QQIV8QCAwlhVGGlABHCkY60x6ORv7%2BO5i02HGuk/0MiG4/F4VQQuMV0sRJgIBFQmHMNh8prATAEXu2geYUsc2uSxoyuUCBVKlXM1CHN1XWgQJaHAC0tyHxBHqZNvu9Z5pgPrVoha9LrKaeCY0XoCnj3OxDxYbum5%2BrtYWg2QZ4KGEaHO2lYPLOjo8riqBEMoTAjv8s4mOKqGzrWUoLvKQIrqqLKat4lKPFhtboQB5Gzlg%2Bx9qR0HUbOECYUx5HJn%2BQYEOgGYsEwADW4ZZoquaYAWjCbG25ZQWx1EZkBVobugW4QvyySCjcpyPsQz6vpg74dtGtw7qxbFLBmxEUqZaEXlRRo%2BlejE1gpgZuPe0YPMAeLAowBAGTJtZeOkRg4shbwnCS8GIWFEKed5bCCAo04Vg5Ty2b6jwAPQAFS5Xl%2BWZf8OW5by2BCLyeWFVl%2BU1dlVVms8GKvO8bjopifkcn69K3kyyKlg8x7%2Bf8QVhMAhzmsS40/imEIaAiVSHGYCL%2BLcGZIShpwDcASVGSll5mjheDIGGTAKEozQQOaEIrRWFlauF/jGiS/hLKlHArLQnAAKy8H4HBaKQqCcG41jWJKawbOFZj%2BDwpAEJo70rPxIBfZIkYaJIXCiv4GhfRoZgAGwE2YAAcJP6Jwki8CwEgaHNf0A0DHC8AoIBzfD/3vaQcCwDAiAgGsBDJOc5CUGgIJ0HEXZsJwqgkwTe4E5IhzAMgspSJGZi8Jg%2BBEDpPFVPwggiGI7BSDIgiKCo6ic6QuhVAA7sQTDJJwPAfd9v0I4DnAAPLnML2KoFQhxywrSsq2rhwa2YhwQB4Ev0CqOxcEsvAc1oKwQEg4vqUnosQLnkvxMAUhLTQtBAsQrMQNE3vRGETRXG7vAN8wxBXL70TaF0HOw%2BLCUEL7DC0M3ttYNEXjAG5tC0Kz3C8FgfFGOI494Hi3Tqvp3uKl05xbLDYRAp9tuXNEzsdx4WDe2SeA0wvpBb8Q0RpJgRLAoYwCXEYCMrFQBjbVZHgTADtfb9hbhbYQohxDmyNvIJQahvb230J/FAoNLD6DwNEVmkAVioCxJkeee4vgRVMJYawZhGZP31tvXB1RaiZBcAwdwng2h6BCHMUo5Q8hpAyAICYfgqj5D4QwAYXDhhTBqL3HoMwBF6E6N0AQvRmhiKGPEKYsjWGTFGH0VRCx1ErAUBDTYEgPYcB%2BqQBmvAmah3lorZWqt1Zo1jhAXAhASDHGhqndOv8VgIEwEwLA8QdykGRpIfwkYEj%2BFFJIDGZhJAEzpl9AmSQT5U1IDTGGkYCZcAJiTBIJNcmoy4F9KJBNLHeyZizNmcNf7cz5tnAWAcRYUELqgROUs4ScCaCwdUoo9xMDlAYEKXAEiRi4OjbWusSBuj0HAk2MDpBwKtog22uglpOxdi3MxFirE%2Bw4P7IW5xDjB0RMQXp/TBn7E/tHMZEyNBxwTnnOInj/BmDTrUzmWcc7tOeWQVpRck4gB6X0vc1yjCjK4HNCuVca511tm3JuEDEUdy7j3BwECB6%2BWHqPb2E8p4zznhApen9V4A3wBvRwW954A13sgfeECj41G9mfC%2BVwr5bABrfe%2BsMn4vyUO/ZeX9Rp1P/shBQQCQFgMYBA%2BZ0CzZLNkCsm2AN1koJ/mQqwGCz44JCfguoRCSGPU1RQqhcQaG6sMVIxRfgICuDkVUDhJQ1E8IKJkB1KReF1D0dwyRDClGaJyII%2Bh0iA26M4S6jRfQPVShURG/RpjVjrBManCm5iva2xsSCy5QybmjPGejOObi9avO8Z8zOfiAlBMoGY9JmSxkY1FKU0U2NJDxKVlUPZVTbA1IzlzHm/NBaBwLoCzpMsOA9IjiwBQ6pZTqnzQyaYUz3H6zmbIBZCrIHKqQQEUgmzXYLx2RmxmftmlBxDpO5W07Z0agXVaD08dfnF1eS9HxXzuY/I6f8sWT6gWzuSMkMM86EhhkXQQE65ylZ8DoLCyg8KAYorHrDRDaLe6YvaYPHFY9yWYEntPMQRKH4kpXpyxe69pHUp3qoPeQJGWCGZafLBbKOU3x0jy3gfLX6CtJSK99YrAHANAeAh%2BcrTYSEVZbBBKqdC7uGcYdBNgdXwDwQQpcnBMrphNZYSh1jqFuloSEhRdQmEsKDew5hPqJGerdfwrRwbhHevjb6kNNrlEtDs/I61dQ3OWfUTo8YHmo1xudQm1NRjk1myPRUzNnAzksCnTOudd6gQPuLR4lOHy%2B1LErYE4YIS0nUxAGYMZ/h/BfTxpjOmpXRR5Oiye5mPb2a%2BNCSASQX1IlfRJoTBIkgEjY2iVwQIJ9/DHusZwN9Fa01azq2NhrWWVhP3SM4SQQA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/amidst.hpp)
- [unit test](../../../../tests/unit/varybivore/amidst.test.hpp)
