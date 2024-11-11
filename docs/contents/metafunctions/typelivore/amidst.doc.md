<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Amidst`

## Description

`Typelivore::Amidst` accepts a list of elements and returns a function. When invoked by an index, the function returns the element at the index from the list.
<pre><code>...Element<sub><i>i</i></sub>... -> I -> Element<sub><i>i</i></sub></code></pre>

## Type Signature

```Haskell
Amidst :: typename... -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Amidst
{
    template<auto...>
    alias Page = RESULT;

    template<auto>
    alias UniPage = RESULT;
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
using SupposedResult = int***;

using Result = Amidst<int, int*, int**, int***>::Page<3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We want to count elements one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
There are two ways to achieve it.
First, we can use `void*` to declare unwanted parameters in the function signature to reach the desired element.

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

Second, we can use concepts from C++20 to constrain the type of unwanted parameters in the function signature to reach the desired element.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `Prefix<I> auto*...` to enumerate unwanted arguments.
    static constexpr auto idyl(Prefix<I> auto*..., auto* target, auto*...)
    { return target; }
};
```

`Prefix<I> auto*` constrains the placeholder type `auto`. Assuming the deduced type is `T`, then `Prefix<I> auto*` becomes `T*`, and `Prefix<T, I>` is evaluated to determine the legitimacy of the instantiation.

Note that `Prefix<I>` constrains `auto` instead of `auto*`.

```C++
template<typename Type, auto>
concept IsPointer = std::is_pointer_v<Type>;

consteval bool checker(IsPointer<0> auto)
{ return false; }

consteval bool checker(IsPointer<0> auto*)
{ return true; }

constexpr void* pointer = 0;
constexpr void** pointer_pointer = 0;

static_assert(! checker(pointer));
static_assert(checker(pointer_pointer));
```

[*Check out this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDMpK4AMngMmAByPgBGmMT%2BpAAOqAqETgwe3r7%2BQSlpjgJhEdEscQlmtpj2hQxCBEzEBFk%2BfoFVNRn1jQTFUbHxiQoNTS057cM9faXl/gCUtqhexMjsHOYB4cjeWADUJgFuXo60hACeB9gmGgCCG1s7mPuHBGdJmAD6BMRMhAqX1zutwImBYSQMIIOble72YbF2ABU3phSLsmMdUADbmgGKskgRdgBJBTKVDhEHEZ4AEV2w3QIBAeAUHxS5PiHwAblCke8AQErLdATjhpgOWJdjFUJ5dsgEJhkABreIQYmktnEKEaS5ojFzQEmADsFl2xEwBGWDF2VDESgOxsNVP12IEIrFtAlUvdsvlSuIKpJZME8U12vRRAAVHrBUaTWaLbtvl5MHb9gbHYLnQwRaokpSOWT0OHdqyg5SDjStfyhS6QTm8wXw0WSxSWYGKdTdpWBUCbpNHMgPkwFEomhAwGAZXLFcrm/E5nqq7c%2B3gB0ORwQIN7p37Z8RW%2Br53aOAtaJwAKy8PwcLSkVCcNzWay0pYrJ4bHikAiaY8LBUgM%2BSAAdBokhcAaAQaGeGhmAAbDBZgABwIfonCSLwLASBoGikFeN53hwvAKCA2Fftex6kHAsAwIgIBLAQSTHOQlBoGCdDxJErBrKoCEwQAtDBki7MAyDILsUiAWYvCYPgRDEHg9JcDIggiGI7BSEp8hKGo36kLoikAO4/EknA8Ce56Xjp%2BEAPLHAxBKoFQuzcXxAlCSJYlAWYuwQB4rH0GWgRcHMvCkVoCwQEgLFJGxZAUJuqB%2BYMwBSJUNC0BSREQDEOkxOEjRnCZvC5cwxBnFZMTaPKpEfixbCCFZDC0AVZGkFgMReMAbhiLQRHcLwWAsIYwDiC1%2BCmg4eAcpgvU3pgqjyscawfmyp4tacMQ/KVHhYDp3x4BhfWkFNxCSkoVKgkNpxGN%2BCxUAYwAKAAangmD6VZsKFRpKniOp/CCIoKjqC1en6ENKCPpY%2Bh4DERGQAsqD4hkvW8XS5amJY1hmHhx1yVgsMQAsdhVRkLgMO4nitHooThP0ZSDIp%2BTpAIYx%2BAzqRMww0wDAkilExNAjdKMFM5Lz1TEwLIy9DTMz07Ykss3okxNFzdM84TL6rBIZkcBeOGWZwTk8fxgnCaJ4leRAuCECQ%2ByBcFn43QscpMFgCQE6Qf6SAEgEAJwBAakggWYkgwVhZ4wT7KEcGhpAYQEXCATBXAwQhPsIcnAFcGefswXrLX4YRxEO2R4XURFtG2YxcVRTFHFsJwjQsByBq8UwMoGEYYk%2B4BCezTJJDyXof3CKIP3SMPAPacDiSGUwxl9druu4bw1mV/ZjmN83rft0NXc98B3m%2BdF/m2wEZj26F5HlzX/lMfFiUJJvLfbENXA%2B1w2FpRllDZS1xX5Z9f%2BpVyqVQcJ9WqjACANSajpNqHUuq0B6p9Aal01g3jGsTKaM0pLzWQItT6K0dLrU2mcbaaCQpyQOh%2BY6p1MDnUGkYK6oAS58Huk9F6b0PqHWHt9NS49ZCTyBjeXQlQO7GAhjYda%2BN4aIxdJwFGBB0BowkVjFeON5LTXgITMW/M/AQFcArRS1MSjcz0IzWohjkjs1qCrWYotOgSx6JYvmtRBZSxMarRW8thaszllMaWpigqLGWJrIJq0l76w4GiYgTcW5txfp3N%2B%2B8NDeStrJU%2BQUQqO1IM7V2lBtYxzjt3ECBps4GnApIYOAlFLL1vJwQuJEboUTLkgOidk7433YpxBuMTXIsAUByUSHIkkQmmgQKS/dcZD1kLwiQ/D/paSEToEAQRZ7z1MlHCJ%2BdOA2XoscXYDloksD6QMoZIymAgmGIfBKx94inwCBfJp18bkxQ6S8/yIBBlJCSJyN%2BHxRnDEHL08edBv5ZRynlUqgDIVlQqlVcBCU6pQMas1dBmB2qdW6r1D8KDGHkNangcajgsE6TmgtEEBCgyrRvMQ/KZDdqUM%2BjQ1IdCLqMPCMwsKrCmAPWeq9d6jBPo8NHnwjSgidK6CCGI8GGNIZSK0beWRWZOAAHo6QyqsJYVRt51F4wVS4km%2BiyaWOMbTOxViCgZEseYjItjZYGscULbIviHV1ElnanmfinWU15u6gJnigkKA1mpReFltlRMbicwZuxhndwBQSS2kyMmPJLk7TALtBju1WoU/w3cAgBDPFBUCWF80GhTnnPC9TbBF0vvOD2IBJBnl9meBCsEfaSB9uBf2XApWcACGGytBFi5hW1pJCtK8q21oWMdNIzhJBAA%3D)

Now, we make a class that generates the `std::index_sequence` and translates the result to a type.

```C++
template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (
            Midst<std::make_index_sequence<I>>
            ::idyl(static_cast<Elements*>(nullptr)...)
        );
    };

    template<auto...Agreements>
    using Page = std::remove_pointer_t
    <typename Detail<Agreements...>::type>;
};
```

Check out these tests, which use different `Midst` for `Amidst`:

- [`void*`](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBIArKQADqgKhE4MHt6%2BASlpGQKh4VEssfFcSXaYDplCBEzEBNk%2BfoHVtQL1jQTFkTFxibYNTS257SO9Yf1lg5UAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnofYJhoAgpvbu5gHR8gKBOhYVFc393cEmBYyQMAMObiYJ1QPzuXnSRj2ADVUHh0MpkYI4i8ACJ7ABuyPQACpDlY7r8AUCQZgwQRzslGKxqf5rnd3sQvA49gBZFHvA4Adis/KxJN%2B5MBwKYoKO6QAXpgAPoEAB0qoAktDbmyOQRubyCGD3ugQCAwlhVAqlABHLyMNZgtWq5U/ZliwW/PaevbvKV4ZB7NAMd6YVTJYh7CFEPYo860CBIlFosIA4gOq5O0gRyGEvYjYCYAiZyOoQlO%2BYer0mQV7YgFlYMXONfMG/wWAUisnC0Vk/4Sqk0ukMthO7D0NiCBSa7Wc24sfVu0m3L25vtSpluOWK3Ua113ZfT3VYgtMOgVz1VxfL5ewsLAXOD7F7LA7Wn0s9XiDvq9ennod6Gj4TRYJgAGtFTNENLUwG07XXHdrl3JdvyvE0YzjH1HGQBVRH/I5R0BRgCAUYlmQgBgvFoWhkgIYh5jLL8vXLVt3yrEVmJ7JDPQpSVpXBSEnVuYBawIidNWvOE72UJh80fI0TVrFhUFxRVUmTOIlRYo5XyHZ4jwaU8jkE4TxyIp0rhNbSXUXVjuz%2BW4AHpCSc5yXPs35HKcgAVbAhE85y3LuDyXNcsUyTMLYGB2Lx9jBQM1moydEN%2BG94SELxklSJR0AAJUwBQKN1Q4cWTZzbOSiS9ly/LaEK/wcVnecjmTTMSpawQnLaghSuZE0pPzMF/Cs0KtQaTCFSYBQlCaCA5JABRGXGxK3CqgrMzSjK0kwHK8oKq4mMXDhFloTgEl4PxuF4VBODcaxrG9ZZVmeTYeFIAhNEOxYQJABJJGVDRJC4fl/A0BINDMAA2cGzAADmh/ROEkXgWAkDQNFIc6tFIK6OF4BQQDRt6OC0RY4FgGBEBAZYCGSE5yEoNAgToOIIkZThVGh8GAFpwckPZgGQf0pGVMxeC2wgSBRPR%2BEEEQxHYKQZEERQVHUImdD0AB3YgmGSTgeCOk6zverHOAAeROGndVQKg9nZrmeb5gW9iFsw9ggDxGfocNnvmXhCeJ0gICQBnkiZsgKAgEOw5AYApDMPg6BTPGIGiY3ojCRpzj13h0%2BYYhzlN6JtBqQmXoZkzTYYWgs7V0gsGiLxgHBSi8YuuvAUMYBxFr/Ba1qZTW8xkMahOdYXrU47a7OaJtfzjwsGNmi8GRtvlOIaJNqPYCjDOIx3sWKgDGABQETwTANdN%2Blzpe6XhFEcQFdv5W1GN3QuH0TuUFuyx9DwaI8cgIsVA1FMit05kaIqphLDWDMJjJScRiAojyvARYHRHDOAgK4MYfh34hGmKUcoehMqFCyJ4VoRCCjoIYH0AhcxbCYHsFQ7oowyG5HfmguokwaEDAqMMHo2C9A%2BiaNw2YFRUEPTWBIA2HBTro2NtjW2HNua835oLX6rsIC4HFt7cKXBfavX3osBAmAmBYHiBAT6IBJD%2BGVAATn8PySQ/0zCSHBqjBI4NbHww4IjUgyN/BcGVODLg4Noa2OhiEn6lR7HgzkbXbGuN8YGLViTcmQdKYW1phHKOXsWZsE4I0FguJ%2BScyYAGAw8IuC2OVIEoe%2BAiCIONO/W%2BssH7SCfkoF%2BtddDxy1jrbO0jZEY0umbTJVsbaFOKaU8pndnbVNqW7D2ocvYHHCmYfR/tDqB2DqgT2cQ6aR12cswYkySk7E7lUrgaMaA1TiMnVOtdc6Z2zqQJ5%2BdC7FwcC88uhFK7V2NvXRuzdaCtxelgbeXd1iY17iXPAA9jbD2QKPF5E9jbT1nuceeUK/aIJXi9NeG8lBb07rvUAKS%2BBHxPmfC%2BV8XktPvvLdpshn6q0xj0j%2Be8oFWB/tPABFisYgIEGAiBdUuUwLgWvRpyDAH0MYZkFwDB3CsJwUERVIjCHv2IVQgRmrKGZHVXQjhXRJg6tlbC41PQDW8KEc0ZVgiuH4J4VIpYKxJF6O8UM%2BRnAIzECKSUsp5zKnzL%2Bm7LRDTVkBI2YY0gxjTGDH5ZPXx/jqn/X5AkWx/IgaSBcTzd%2BwyTY41sEkzZqT4DpKppbA5OTmasw4IUh2LAFC4n9LiKpyoqTvFFvUiWTTFZ3zlhIJlStOmsvVoEPpusLqDKNvE0Z1MTh7Gtj6lgDam0trbR23U7sjlhwjf4KN5L0nVvDvTHdXsQDNoygqVttiFSbvGr6nmCdbnEHuWnDO%2BcXlvILkXEu3zdkVyrjXaFmAG5NzECCl54KSXYrrngPujh4W10RcituqKp5/wxVixeuKXkEs3h3Het594UuklS8%2Bl9GB0tkK0xlfaWWvzyBU4w38bC8pQQKqhrd7JyTFZYWBl1JVIL5aghh5q/CYMVaavBJQnW6vSNqu18mSFWsEWJzoDBmG2pyCqo1mmHWydEfa/hSm%2BHCMdUZ91CgJHy2nXEuB3r6280bc2vEG61x8k0d2nRka/bRtjWYyg0ik0gDMNU/w/gEigwBqjCL/JQn2ZGYWvGBNo1fUkAkOxCRoYQ1sZIDNcWuCBEnv4GdDnC0lukSLRLBa/MpMWGvdIzhJBAA%3D%3D)
- [concepts](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxAGBAA6oCoRODB7evgGkyamOAqHhUSyx8f6BdpgO6UIETMQEmT5%2BlZj2BQx1DQRFkTFxCbb1jc3ZlSO9Yf2lgxUAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnofYJhoAgpvbu5gHR8gKBOhYVFc393cEmBYiQMAMObgI50SjFYmFIeyYJ1QPzuaAYa0SBD2ymImBoqheABE9gRiF5MIcrHdfgCgSDyUcIVDmGxkbd3qSHHsALJ4dDvA4AdisAoJFN%2B1MBwKYoKOqQAXpgAPoEAB0aoAkqz2V5OTy%2BQQwe90CAQGEsKpFUoAI5ktH0tzqtUqn7%2Ba5UoW/PZevbvaV4ZB7VHvTCqRLEeGIva8860CDY3F4VRgzWuiNEPZOuEIogAKmJDWAmAIWcROad8093pMQr2OIIKwY%2BeIhYN/gsgtF7tFbfF/0ldLBjOhbCd2HobEECi1JJ1mNuLF573FHru3uJ/el9vlSsxKbdtzX2s5BKLTDola91cpB7X3q8qSMxMhz0ORKwOyHF9vEC/t%2B9eqXWUPhNFgmAAayVM0Q0tTAbUYNZkxdfc/z/E1o1jX1HGQRVREAtwx0BRgCAUHMrggBgvFoWgMWIeZy1/b0Kx7VcqxFMUqRYr0aSlGU3GzVAnVuYAcUIydWTXe8wmALEmELQkfWAkAcRYVAADclWSMIAWIZUv0HZ9mWeE96nPI4hJEidiKdK4TU/V12PuNjmL%2BW4AHocw8zyvNc353I8gAVbAhH8zyfLuPyvO83t7jMLY0SeF43FRdFiNZX5JMfIQvESPJMHQAAlTAFEozFXyjQRPIc9KH2kwritoUr/CJedF1bNwtLhLSc06iruvKghKtdE1lFk%2B1/Bda9fkw/1FSYBQlEaCAjRNBQYVmqcjjqkq4SynKUjyraGquJjrw4RZaE4ABWXg/G4XhUE4NxrGsH1llWF9Yp4UgCE0M7FjAkBLskFUNEkLgBX8DRLo0MwADZYbMAAORH9E4SReBYCQNA0Uhbq0UgHo4XgFBAHGfo4LRFjgWAYEQEBlgIRITnISg0CBOg4giGFOFURHYYAWlhyQ9mAZAAykFUzF4PLCBIXk9H4QQRDEdgpBkQRFBUdQKZ0PQAHdiCYRJOB4c6rpu36Cc4AB5E4mcxVAqD2XmBaFkWxb2CWzD2CAPHZ%2Bhw02Lh5l4cnKdICAkDZxIObICgIGj2OQGAKQzD4OhtJJiBokt6Iwgac4Td4PPmGIc5reibRqnJr62cs62GFoQuddILBoi8YA%2BKokm7tbwFDGAcQW/wHEanUnv8ZDaoTnWL6tPaS2zmiQ2y48LBLZJPBMd79TiGifaT1AowziMX7FioAxgAUAA1PBMD162mSL9XhFEcQ1cV%2BQlDUS3dC4fQB4oGepYfQeBogk0gIsVAGJ0g935kaV8phLDWDMPjNScRiC8iKvARYVQajOAgK4MYfh/4hGmCUMoeg8hpAEMQqhKQaEMD6BQwY/88GdG6KMTwLQ9DsNqJMZhAx4hsMmHQkRPRBGzGEbgt6awJBmw4NdXGltCbOz5oLYWotxbA29hAXAstA6fRDt9M%2BiwECYCYFgeIEB/ogEkP4FUABOfwApJCgzMJIWG2NLqw0cajDg6NSCY38FwFUsMuCw0Ro4xGESgZcEus42GyiW6E2JqTExOsqa00jvTO2zN46JwDlzNgnAGgsFUgKfmTBAwGEfFwRxKpQmT3wEQTBxp/6f2Vu/aQn9NY/xbroNOBsjZFwUUovG90bZ5Idk7MpFSqk1IHp7BpTSfZ%2BxjgHA4sUzDGLDmdCOUdUD%2BziCzBORyNmDDmZUnYA96lcBxjQBqcQs45xbiXAuz93llwrlXBwz865EQbk3S2bcO5d1oD3L6WAj6D3WPjEe1c8Dj0tlPZAM9n7zwui3JeK9zhrzhaHTB28vq733koQ%2BA8T6gEyXwS%2BN874Pyfr3Tpb9VY9NkH07W%2BNBkANPkgqwICl4QJsQTGBAg4EIKavylBaDd5tOwZA2w7REUEKIdw7IpCGDoEkZQ/%2B1DOhiNyAwzoOrWFKo6Pwnohq%2BECE4VMYoQjeGiPVSQ4YEjyGOuDksFYcivVYvGSozg8JiDlMqdUm5dSVkgx9vo1pWyQm7NMaQcxljBgiqxYE4JDTQYCgSQKCGkgPFC3/hMq2RNbDpL2Vk%2BAOSGb21OYUzm3MOBlLdiwBQqkAyqXqSqOk7xpYtLlu0l%2BXS2Uv05b/HIwzjZ3TGRbFJUzGYnD2I7YNLA20dq7T2vtmJfbnNjvG/wiaaU5MbXHVm%2B6A4gE7TlRU3bHGKh3bNENQt05POIC83O%2Bcy6fO/eXSu1d/lHPro3Zu8LMDt07mICFz9oWUoJa3PAo9HDIpbqi9FvdMWLzAbi/FG8iXP1JQffux8pJn1pbJel99H6MGfiylWEh2Ua2/ly3WgRanGGATYIVODRWdB7q5Za0rLCoPunKrBwrcHKvwX4QhWrDVkIdVI%2Bh%2BR0iGv1ekU1wjzUqq6M6rIrqbV6fdUp3VbquEGadSZmYuqZE%2BtVnO5JaCg2tuFu2ztex729s3PyPRg7DEJtDkmlNVjKAKMzSAMwDSKiXWhmDbGFQBSRKc5M8tJMyZJoBpIS6TjLqIzho4yQjiIYuK4Oxzg/h53OfLVWhRUsUtlqC5kxYu9UjOEkEAA%3D%3D%3D)

Note that we only constrain the types in the second approach.
If we move the constraints to the template head, we don't need to define the function at all:

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<Prefix<I>...Nah, typename Target, typename...>
    static constexpr auto idyl() -> Target;

    template<typename...Elements>
    struct Detail
    { using type = decltype(idyl<Elements...>()); };

    template<typename...Elements>
    using Mold = Detail<Elements...>::type;
};
```

`Prefix<I>...Nah` tells compilers that this function template is only allowed when `Nah` satisfies `Prefix<Nah, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

We will write an `Amidst` compatible with this version of `Midst`, which is also the one this library uses:

```C++
template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (Typella::Midst<std::make_index_sequence<I>>::template idyl<Elements...>());
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;

    template<size_t I>
    using UniPage = decltype
    (Typella::Midst<std::make_index_sequence<I>>::template idyl<Elements...>());
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGykrgAyeAyYAHI%2BAEaYxCAAzACcpAAOqAqETgwe3r4BaRlZAqHhUSyx8cm2mPaOAkIETMQEuT5%2BgXaYDtmNzQSlkTFxiSkKTS1t%2BZ0TA2FDFSPJAJS2qF7EyOwc5glhyN5YANQmCW5ejrSEAJ6n2CYaAIK7%2B4eYJ2fI4%2BhYVHcPzyeBEwLFSBmBpzcBGuqUYrEwpCOTAuqH%2BTzQDC2qQIR2UxEwNFUHwAIkcCMQvJhTlYngDgaDwVSztDYcw2GjHuMKQ4jgBZPDocYnADsVmFxOpALpILBTAhZ0yAC9MAB9AgAOk1AEkOVyvDz%2BYKCJDviAQGEsKoVUoAI6UzFMtxazXq/4Je600UAo4%2BskyxmQvEEvCqSE690uxEsuFsI4AFWawEwBCjMJjmBdHN9R3GcrwyCOGPGmFUqWISJRRwF11oEGWRwAtHd44nk5LaU9s/TZfKoWm2RnNdh6GxBAos769TzicmmHRvb6TKKjl5MkYyWmSUcsAdoxBq7RIcOQYwCApM%2B668tqSKJQkaYDHl3/XLHdGBy7j6OzxOfauwsAfKeOgW4zk085nF%2Bp7npqdxmtG7bPOKiHSgyr6Qu%2B8KfiO0G6uS%2Bo4o8LACuMUpep2vrdgGCp4MqapHOGHpPpO%2BHTrO84UT6S4Ptm2b/uu0ZbjutAIZxvEQIapEKgQ6BmiwTAANaqhaJbWpgdqMFsYZutg8EvsCVboDWR44WOF7YFeiHZkud4PguPpUehZzIkQLqPMA%2BInmOv4rmugHKEwSagexh5nO5nnfjBrruvBaYoWJjm9kqqo4ox9m%2BQBRxyAweABUFpyksJonMT6Ekkca0mySA8lKSqKlWra9paWcaUxSAiXvAeJleWe5mWfeZG2VKTwAPQAFQTZNU0jQC40TXG2BCHGk0zaNU3rWNq2Pi8mJvB8bgYliP7usNjz8YBQheKk6RKOgABKmAKF4IlbmEBCTfFZ1%2BUcD1PS9BVHER5WQm9iJvWNYOCBNkPvRNcEgHljoJG6dlPLmjjICqTAKEoLQQKaIAKPCWPjmcv3PSmRyXddGSYPdj0U3c14DU8HCrLQnAAKy8H43C8KgnBuNY1g5usmzvLsPCkAQmhs6sCkgJzkjqhokhcMKCQaJzGhmP4/hmAAHAb%2BicJIvAsBIGgaKQvNaKQAscLwCggNbMscFoqxwLAMCICA6wEKkFzkJQaCgnQcQRPCnCqAb/gNv4khHMAyAFlI6pmLwdOECQAp6PwggiGI7BSDIgiKCo6juzoegAO7EEwqScDw7Nczzsv25wADyFyBziqBUEcMdxwnScp0cadmEcEAeGH9DlpLyy8G7HukBASCh6k4dkBQEAb1vIDAFIZh8HQwLEM7EDRO30RhM01xN7wN/MMQ1yd9E2jdG7Uuh9%2BncMLQ98q6kCwNELwwA3BiFoM7PmwCQSGGAOIIB%2BB8Q9AAG6PXbiWboFxthSzerUduVxoj1xfh4LA7dyR4AtjA9BxBoi0xnPJIwVwjCy1WFQAwwAFAADU8CYBrp3VkD9S7CFEOIEu%2Bd5BKDUO3XQXB9DwJQMLSw%2Bg8DRGdpAVYqBsTZGgQ2b4BVTCWGsGYO2qBaHEAFBgzRNQ6jZBcAwdwnh2h6BCPMcolQ9A3WKDkZx%2BR5HePqAwQYHiRjyK6D0Boswph%2BHCbUT%2BvRZghOGPEcJ0S/GxNsEk9xKSJCrAUGLLYeSTYcG5jbduDtB6x3jonZOqdlaTwgLgbO88zAJC4IvaWbDVgIEwEwLA8Q6ykAVpIBI6okgJGFJIVWZhJD%2BCtpzfwKQOYcDNqQC27T1T%2BC4P4A2SQDY7KVlwTmEzAi235pwJ2LsulV09j7Nefse5Bx3nvOekc2CcGaCwVBwoGxMELAYdcXAkjqi4CrTO%2BAiCWNkvIyRhdxHSEkeXGRQDdDHzrg3B%2BLdSltyAQ7buAcLhHH7kiYg3zfn/IOPA8eIKwUaCnjPTec8ThtLMJ05ebNV7r1QLPOIwdd48qZSML5PyGxUqMMCrg1saAiTiBfK%2BQCn532EUql%2Bb8P4OGET/U8f8AHtxAWAiBtAoHCKwEwhB2w7bIISeg6BdssHIBwcI/BKy7ZEJIdcMhlql6WOoVLWh9ClCMPgSw0Aty%2BCcJ4XwgRQiYFwrEcXRFshkWVztmihRrCjFWBUUQjRQztFBL0QYhIxIs0mLMRYqxeb8nxMiX4CArgYmuMcckxYqTCiZCCU2gJRQgmts8XEuxUT%2BjdtsQk4dLR%2B1hKySOjJehcyTpyW24pBSNhFI6SUsp5yO4cFJeSv5ALqXAtBSrKezSoUsvaey7ppBen9JGEMlZayNkgtVsKE5woNaSFmQneR26HZXNdmw1e9ykD%2B17vy15Eco4cC%2BSPFgChUEFlQcexk4wIUtNzrC2Q8LE0iJTbIxIpAMWNz5tirdFSu5PL7gPODicENIaOChkFaGcTT0FVvS9CRr3hoeVB7eIcONzxAEh66KpmMqlY1jMlCcT6yvPpQBVdtVWAKlip9Vn8tU8t/v/QBVrMCgPAZA6BUszUhu9cAvAKDHC2swaobBwJnWCAIUA91d8vUUN9cIgNDC4HMIAsBjhgUo38MEYwYR8ai4SCTWXaRqbq4JAzcYZRNhc3wC0TogQ0CRqmjLZYUx/NK1YGrWOutDinF5EyW4souSe2duyKOwJ2Qp3toiUEvokw52DvHQwDrcwavLrSbOyr87skDYHfkwpxdyO4rMZwPd8HEPIdQ6%2BIUTTIUkEvR0peN670DMoNi59IAzAgoSAkTm2s1ZWzO8KXZ5S8WXNsNcjlyx5YgEkJzcZnMDa6ySJIJIGtJlcESyshIs2LmOxuR7bFGd7tzchy91YtDMjOEkEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/amidst.hpp)
- [unit test](../../../../tests/unit/typelivore/amidst.test.hpp)
