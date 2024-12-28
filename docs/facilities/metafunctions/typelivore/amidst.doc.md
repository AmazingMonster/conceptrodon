<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Amidst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-amidst">To Index</a></p>

## Description

`Typelivore::Amidst` accepts a list of elements and returns a function. When invoked by an index, the function returns the element at the index from the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> E<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amidst
 :: typename...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Amidst
{
    template<auto>
    alias Page = RESULT;
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

- First, we can use `void*` to declare unwanted parameters in the function signature, eventually reaching the target element.

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

- Second, we can use concepts from C++20 to constrain the type of unwanted parameters in the function signature, eventually reaching the target variable.

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
/**** IsPointer ****/
template<typename Type, auto>
concept IsPointer = std::is_pointer_v<Type>;

/**** checker ****/
consteval bool checker(IsPointer<0> auto)
{ return false; }

/**** checker ****/
consteval bool checker(IsPointer<0> auto*)
{ return true; }

/**** Pointer to void ****/
constexpr void* pointer = 0;

/**** Pointer to void* */
constexpr void** pointer_pointer = 0;

/**** Tests ****/
static_assert(! checker(pointer));
static_assert(checker(pointer_pointer));
```

[*Check out this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBm0gAOqAqETgwe3r56icmOAkEh4SxRMXG2mPa5DEIETMQE6T5%2BXGUVqdW1BPlhkdGx0go1dQ2ZzQMdXYXFfQCUtqhexMjsHOYAzMHI3lgA1CarbgQAnvGYAPoExEyECnvYJhoAgvcPAPQAVB9v2wCSCsqowQI0W2nzeL2eQJY8QMQL2B2OjFYmG2ABUEaRtkwvERbs80AwlvECD8/gDBMC9gARbYDdAgEB4BSnRKA6KnABucLRJ1xqysj2e70%2B22QCEwyAA1sDQeDHviBph2WJthFUJ4RWLJdEIL9/qziHCNLdMdjUNNniYAOwWbbETAEBYMbZUMRKPY2q2Ui2PIUfDXiqXEEGfWUPeVApW0FVqqOigPa3VkoEG/ZG1bYE1EN7mgXW232x3bC5eTDu3aWr0Cn2g7Z68lBojbdkA9DBj6h8OYVTxIPNvDoL4s%2Bu7VbUtP8p7V4V15NF1BNltfMF4gQK7u9xeDpNsoezqnbcfe141lGYAYKNvLx5jRzIU5MBRKOoQMBgf1a4gQXfRabmvnPG88DvB8nwICA4w/L9t2IZloN/d1ng4WZaE4ABWXg/A4LRSFQTg3GsawaXmRZkTWHhSAITQkNmCUQFQyQADoNAADjMMwAE52K4VCWOYrhLUtaQUI4SReBYCQNA0UhMOw3COF4BQQCkyisKQ0g4FgGBEBAeYCHibFyEoNAoToaJQiRThVGYgA2ABaazJG2YBkGQbYpAYsxeEwfAiGIfs9H4QQRDEdgpBkQRFBUdRVNIXRmgAd0ueJOB4ZC0IwqicM4AB5bF9OJVAqG2Ky7IcpyXLcxizG2CAPBM%2BggzI6ZeBUrRZggJBjPiUyyAocDUHq3pgCkMw%2BDoZNFIgCJMoiYJakOFLeFm5hiEObKIm0cUVPI4y2EEbKGFoBaYqwCIvGANwxFoRTuF4LAWEMYBxBOvA7QcPB2TPTKu3FbFlnI1lhOw2g8AiS5Vo8LBMouPBxNu0hPuIVUlEpTAHqMEGjCo2YqAMYAFAANTwTB4uyk5MPIwLhFEcQwqpyK1EyuL9EelACMsfRQcUyBZlQIlUhu2zaSpUxLGsMxZMRvysG5iBZjsLbUhcBh3E8Rp/BViYehiZpshSARhiaUg9cqLWil6UZykVgR2iGNWRhaa2qkGTpgm6c2ddsF3Db0MY6jNqYuHl4ilgkNKOHQ6TMrk4qbPsxznNc9zqogXBCBIXYzFWIOWux2YxSYLAYjl0haMkVYGPY1ZBI0SQ4msyTUOs9j9E4UTSHE7OGOsrhrOY9i%2BOs%2BjuKr6yo5iuSFKUijsfUrSOp0vKDL6rqevMthOFqFh2UtWymBFAwjDc9iGK4JivJ8kh/OaKngtp6R6aURmYt0UbEqYZLbvDyOZN4OTcr0tibYhVY6lUcpsR6x9T5MRqnVbqDVM6rDMM1Geql2qdQGvA6Ihl%2BqDRiBAowXAuJSRoLQCalBpoxWWvNRapBqGrXWptBwtDdqMAIAdI6mVTrnUurQa6tD7qPWethfAb1HCfRuthH6yA/q0MBplEGYN5qQ2WNhGGcNyKI2RpgVG6MnrBFAGgvgeNCbE1JuTWht8aahQfrIBm0VsKvxZljUWVgOaKNlrzfmq5OBCwIOgEW7MLASz/lLfsX0eaO3es4CArgfbNECG7SYFtjZJH1mke2RsTapADikhW0TnYdHiVEyottXYFG1r7b2mSqnjCSZUoOcwFih0acJH%2B0dOCgPjgfSBRDoEaBqmnXyiCc6oLavnTAhdegl2Eu3TuJ9a6WlQuxASqw66SAcs0X%2BWV5K2Gnq1NSGltK6Xyjg1eDV17LC3mVFgCh2SuXZH0mEZ4CAX3TtLAKsg742PCvIJ%2BDidAgFWKQd%2Bn9UqtwjhlCeOUl4FSKqoG5dyHlPKYECAYsDME9UQasFBBz0EoExQ1M5hLej3PiPEDkRDTjPIGKcBFD9xrREmpQ7C9DjrkTZYwraLCBp7XYYdY6IjMBnQuldG65FBEY1UXdV6isJHfVUL9IEcjyRA14Io8GhwVHQz8ho3gWikg6LRkIgxs9cZMHxkTEmZNGCWK%2BdYiQtiIr/KZkC5xxggmcwiJ4nC3iGA3ReLSNmYtLAhJwmEmW8B5ZWwKcrVWGQjaJIqR7LIaTKjFOyXkepKbLatBttUhNvsY2lJdrkz2ft6g1NGKW7Ngdg7NNCt/KFslOn0u2Lc%2B5TYUVouJKnS%2BjUs6jLxRMqZxdw5zNiCfVYqxUI8UkFwSS07LR93Hi23ZillJ51LiASQqFK78UtJJZikguJcFYmYMewlVjNr/pwXOaDw6eVXbe3Zw6EZMqVpIIAA%3D)$Done$

Now, we make a template that generates the `std::index_sequence` and translates the result.

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

- [`void*`](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbAAcpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3F5HLRCABPSHYf7mYEMUFecGQtzIYboLBUJEoj67C4BJhRWivHa/AiYFhJAx07EEeF3ZhsC4AFWImCYCmWmFIF1Z7NYmAuAGlMIjAcjTsNiF4HGSKVUUQB2CwQ04XPUXSaOZAXNAMYaYVRJYgXJgw1AXPDoeG0CDS%2BFzC4AWiR3N5/MFkKspxMGqugeJZ2%2BUZ%2B/0%2BmwuAEkGfQ2IImDVqdtfnHo99frHSQA1VCO5QlwTRTOHf505PpzDY21EImnLxpIwXYul8t062Qq4XABuJfQm3DwZJlwAso7hlXafTGfWWWzGOKWydFcqCBcZ%2Bg5yGrKHx39TrWl8yoWkAF6YAD6BAAdM%2BExutyq98NsXiQCBglhVDvJQAEcvAeBsoQTZ9HyJOVNSDE59QudZ1guAB1CU2wlExYg0Lt0DLYJe2xV85WgnCNBFe1GB8aJ6wuLwGAAd0MOl0BtYhgFowQFBg3V9UNPBjVNc1LWtJt7UdZ0IHwwiK2IEikWg4UJPjEZgEwAgVLtTZoLmf4kMPC5eQIZYGBFBoNIIQMIWPYNj0BBCC0uE4WFnHc3hrRcmQgtxRTXNhoOwFNGAIBQ3wIJUVVc9z4IM/Vzx8788FvB9Ew3JD3x3G56joeK9UPfKkIY9tgBFVcIUBAcsFBfyiqQiB6uKvVP2sq8CHQX8WCYABre9/wtIDMFA8DFLguD%2BOapDfykl1BOQO9RC/KFgvpUKFDHOUIAYLxaFoJJIrmPSmr1fTHKKkMw3OidEIS7zlyhCToJOYBeTWniMv1NtgjK5QmA0yqBx/EBeRYVBB3vFIiOiB8LqhfyOQlHKmDyqEXre1MwvIuVfzq8anIcpzJ1zGlnO2C5sFUVhGQlTziZJ6sbtREEwWwqFTVWA7wom09I0uIQvCSPJMHQAAlZ5do80nW1Ki4BaF1IRfFgVaB3fsHUEHYTzJ%2BNlcl%2Bd/m%2Bjs9dVwGLhi/c2rcIjhSIzZbc1%2B2NYILWcZAP6NOxQFYKJvnya5Z4pazf55rvfklEaCBgYUcUw%2B5twTa0uXBeFsWJdVpEzoQjgFloTgAFZeD8DgtFIVBODcaxrANJYVmwoEeFIAhNBzhYepAfPJEfDR4jMMwAE5%2B64fOe/iLgNQ1aQ844SReBYCQNA0Uhi9L8uOF4BQQCX5uS5z0g4FgGBEBAJYCCSGFyEoNAGToaJQnFThVHiWJPViSQLmAZBjSkR8zF4EXCAkEdHofgggRBiHYFIGQghFAqHULvUgug2hMWIEwJInAeC5wLkXFuZdOAAHkYTnx3KgKgFwn4vzfh/L%2BFwf5mAuBADwN96B9gbnMXgO8tALAgEga%2BSRb5kAoBAPhAiQDACkGYPgdBeybwgBEXBERggNHhBg3gijmDEHhPgiI2hMAOFUaQa%2BmN8EMFoCohBWAIheGAG4MQtBN7cF4FgbqRhxAWLwLyBweAIYONLhaPRMI1iN2htPUucIIioM0R4LAuDIp4Hno40gENiAREVjcFxwA4RGBbgsKgBhgAKELE8Ji%2BD2QGNAcIUQ4goEVNgWoXBSD9CGGMFXSw%2Bg8ARE3pABYqADoZAcZ6PE/ZTCWGsGYVeyTiCOmePABYdg9E1BcAwdwngWj%2BGWdMfoMQ2h5HSAIMYrRkipD2QwTZpQBgTCqAszoIwmirPGO0a5AguiNDObMCYtyDl6EmK84IfRznbLmbXVYEgsEcELsvXBa9yHP1fu/T%2B38u70IgLgQBrDARcHYU3HJCwEB8iwDECAbcQCSEBI%2BfugJJ4aEkGYSQuEND51iP3fQnBZ6kHnhix8sQuAJH7mPWIndh4UtiJChBa8N5b2xbvbhR8eEnyIRfIRIiWH3zYJwBoLBBwak9EwE0BgOxcH7o%2BLg3d/74CIFMzqbQKngOqdIWpSh6kIN0JIlBaDVFgohSvXga9CFnxhBcUhMLKHv1BM02hRqTWUUYagZhlZURmCxZwvecrlXREvsI2N/CWEoH1eIoeS8aCq2iLI%2BRCD1HKIMRWzR2jdH6MSUY0KJizG4MsdY2xe0HGN2cc0txpd8CeMcD43B/jkCBIMSE3B4TInwmiWsUucSEmN2SakpQ6Te0/RyXwfJhTimlMYOU2QtrIH2tkHU%2BBpcXVNOySMqwbTwldKJWXPpAgBlDKqresZEzoiWpmd0x5XjnAQFcF8togQ/kzAuUc/IGRQPQZOW8qD8zAO1E%2Bfcw5yGagvJ6BBrZ3y0PZAw7cxDgLFjLBBZill4KcFis4MGuFerw2GuNd3BhqKLUQjYRwnFpA8VMAJZQMFbKOVGupRqfO/cJ6AhpXSyQbRvV4PXrYSVyaZXwDlafYhGa03EFVWsDVVCWAKEHMaQczGfLDDNWi4B1qj1VJPdA%2BQjqL06BAICUgbr0GOM9TR1eBCFUkLIaoQzxnTPmfrHOGNcb0WAiTVu1NWaBHacSzmkzQs7xmf7neCzBA7zBftdIktlAy2l2reYxuZXa0LIMY2wQzbzH9swFYmxdiu1OPpL2%2BdTiPHXOHQg0d47EmToQdO5Rc7YlTKXbwFdaSOuuM3dK7d/1d2YBKWUxJNr7MSFPTA5zDS3PXpaaM%2B9HTH09JfWaTg6wfyfssOMn1kzplnYA4s4Dyy4PgeKHhnZxyahwd2TUEj3yrkoew3BzDNypi4YBfh7o4PiPQ/eUC8jkCfOir8xwchIWTNDnC3SSL7GSCcYxXF6VuL8UDCfdPYTIAB6PkBICfOI85OLwZxqCoCnxXKe3jx9ukh87kvHhqRe8RJBDy4L3MwIrp6Al8z6zg3GydUb/uj%2BXSnVMLGSWkZwkggA)$Done$
- [concepts](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbFykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn4JdpgO6bX1BIVhkdFxrXUNTdlD3b3FpYMAlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKYia6MyHiYCmfbB8enex87r0eHP2YAzMFkN4sGcTP83F5HLRCABPcHYX7mQEMYFeUHgtzIBQEdBYKgIpFvT4kr6/d7rM4ASRYiXobEETGqzy23wppM%2B33J2zOymImBoqhZm2%2BBEwtIMYsxBFhN2YbFIZyYUNQhOOaFR1wIvP5grB/wuZwIxC8mHBVmO3POAFk8OgccL9r8xRKmWaITK5ax3YjjjiTQ4zrb7dqTAB2Kxhi7molHF10t2Y1IAL0wAH0CAA6bNUtVHf1eQPBnFJ3EgEDBLCqNNKACOps1mKp2czhP%2Bvp%2BEd%2BZx7Z1WqzOAHVMGcvEowbENHyBXhVE2EUqVesWyZJ0bUGdGD5om7RwwAO6GMXoJXEYDbwQKVvHXtnHFMvDIM4anGYVSJYiLohnO2w2gQadBXndsv1QZds0VZUiEpYZgEwAhIKXFsZm7XtwwsM5%2BQIRYGCNeo4IIc0wSjJESP%2BC0fmJc4jhYO0HReZ1xQTKUPVlRhvRbbB6UYAgFDzAtAxoujCMtLsb17eNJXdNwU3TbVc3bVCewE7UrjqOglOIijb1vMdgmAI02P1Q0sGBT0zXEnSzggTSrJ7YtCIhHF0HLFgmAAa3TSs3xrTB6zuaSFMRRTLLsnty1/f970cZA01EEsIS48UeIUdYEQgBgvFoWhEmNGZkNs3sUPIzTw2jErLVCyTEwhKDUBbI5gH5ZLLzzXTUiMXkmDg4y7zLEB%2BRYVAADd02SYIxWIDNStYr02EueCmA0iFGuahleJXdty3MtsKLKmNKpODkySozYzmwVRWDpEcGNO46nUO5EgRBEdMQ1ZZcr4kLKKO84hC8RJckwdAACVHiy7VbqOPTOv%2BwGUmBsGFAh3qJq2A6fopM4kZRqGYYMnHaFDA0ziEkNMQmxU0apwRNhpgh0a2kBlG66T/l22MsYAFUeSHWV%2BaLHzTJgFCUBoIGc8sFG9YWvrcQmELOOGgdB8GiYRYqKI4OZaE4ABWXg/A4LRSFQTg3Gsaw7wWJZXoBHhSAITRtbmdyQD1yRMw0AAOMwzAATn9rg9Z972uDDMNpF1jhJF4FgJA0DRSCNk2zY4XgFBAJOneN7XSDgWAYEQEAFgIRIoXISg0FpOholCb1OFUb3YgAWliSQzmAZAnykTMzF4YHCBIO09H4QQRDEdgpBkQRFBUdRc9IXQEn3YgmESTgeB1/XDed03OAAeShcvtVQKgzib1v2877uzl7sxrI8Gv6E/ZEuBmXgc60OYICQavElrmQCgEB/6AJAMAKQZg%2BB0EmpnCAEQ94RGCPUWEm9eBIOYMQWEB8IjaHaDnB21d1oHwYLQVBi8sARC8MANwYhaCZ24LwLAbkjDiAoXgfkHRRoMJNm%2BdoUIVgOwmpUPeMIIhrywR4LAe9jR4Hjow0go1iARARlcFhwAYRGGdnMKgBhgAKAAGoPH3AfOUaCZ7CFEOIaeY95BKDUHvZe%2BhDDGEtpYfQeAIiZ0gHMVAuV0gMJbs5cEFxTCWGsGYVOSjiB2kePAOYbQOjOAgK4UYLRSCBGCH0EoAwEi5DSAINJOQUgFIYJMfoMRWiVHwZ0YYjRPDND0Ik6oXQGjlJyZU2wdSinjDaVkqYuSEk22WBIbeHADbJz3mnC%2Bzc24dy7j3T2D8IC4CHq/e2H9HbaLmAgTATAsAxAgK7EAkh/iZn9v8SOGhJBmEkJODQetYj%2B30JwWOpB47/C4JmeIsRvb%2BzDrED2wcLmxEmYvNOGcs5bNzj/Iuv8S7HwrsA0BL965sE4PUFgw0wwtyYM%2BAwnUuD%2B0zF83h%2BAiAxJcgkWxE9rHSFsXPBxi9dBQNXuvNBYyJkp14GnI%2BZcoRnDPjMq%2BHdgQuLvsS0lj9UDP2iGCAEZhNlfzzvClF0RK4gJlQAl%2BKACUQKDknGgRNohwIQYvDBKDzEWqwTgvBDhzFEJ4iQshe9KHUNodlBhDtmEuLYSbfAnDHDcL3nw5AAjzHCOjibMREjYRSJWCbWR8iHZKJUUoNRvr9LaL4HowxxjTGMHMTSqxU96WyEZQvE2LLnFaLCVYdxYjvFHNNv4gQgTgkGjrREqJ0RKVxJ8RUKo6QXAMHcA0sYGTR3tOmHkkp1QelJDnekaduTB01IEK0%2BpWR0nNNqRMfpFSmndPHTuupK7KlDMWCM9%2BLzxm73BZwYVcz8XiqJSSr21lVkUvlZ8pV2zSC7P2QMZt0c3kfOJdcsMet/YR3%2BDcu5kgEjcv3unWwULlWwvgPC0uJ8NVquIGilYmLr4sAUMNJ8w031SRxAPclw8qUWNpaWixFbHEgH%2BKQNlG9GGcvvanQ%2BiLT7n1UCRsjFGqNugdBAJ%2B2q5XIn%2BH%2BmF%2Bc/5asAXh1TOryOAzTJR/2aZqMEDTCJ%2BlMCTWUDNSba15CHZWdtfgh1MriGkPIf6zAVCaF0K9Uw8UvqE1MI4TU4Ni9Q3hoUZG0RnjY3xpkTE5NvBU2qJ86wrNSndHdTzZgExZiFHFsnhIMts97GVp0OxmtrjwkNs8U23xraGAMNWJLLtlhIk8uibE6ra6kl%2BBSaOhdmSiiHtnXkdIC78nVHPU06pXXN0Lt3Rus9B6OlHu6LNhbA2ls3oUMMqevGwX8Y4BfUT5Gzi6czAZz9dH1m/s/v%2BwDBzKBjLAyAAOmZ/j/D1iHRDic3thl%2BXtnlnBIXZ3/W7SQetznhzDInb2kgg5cF9mYUF0d/h8YB6hjDYz%2B7/ZQzdmFcwlGpGcJIIAA%3D%3D)$Done$

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

We will write an `Amidst` compatible with this version of `Midst`:

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
            ::template idyl<Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArACcpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3F5HLRCABPSHYf7mYEMUFecGQtzIYboLBUJEoj7fUk/f6fTYXACSLCS9DYgiYNVeO1%2BlLJ31%2BFN2F2UxEwNFUrO2vwImDpBnF2II8LuzDYpAuTBhqCJpzQ6NuBD5AqFEMBVwuBGIXkwkKspx5lwAsnh0MMRYd/uLJczzVDZfLWB7kadhqaHBc7Q6dSYAOxWcNXC3Ek6u%2Bnu7FpABemAA%2BgQAHQ56nqk4BrxBkPDZMEdAgEDBLCqdNKACOZq12OpOazRMBfr%2Bkf%2BFz7xolielUP5grwqhbSLboSYCCVXsYPouABUGsBMAR53LF2w2/n%2BxdJo5kBdNcNMKoksRlaqLvb4bQIHMLgBaJErtcb2NW6Pfv4ky4ThYe1HTeF1BylD03AXBVMDbbAGUYAgFHzQsgyAkCCBRHtTgPBNIOTPA00zGl937NCdRueo6F7fsI0tE4DwPLw0iMY1twNI0sFBBdaKYi4ID4/j%2BxLLCoTxSsWCYABrDNqwvOtMEbB4oLzTsyOE/tK3w9073QB9sQQiUkIUPdOyfISDzmP8DwjGNAQYoSdOHNwVSINsTmAAVjMEFD1Nw/sWOCYA%2BSYddOOuDcmBoqFPO8xlkLM7BtO3P87LSgDOTZa1tgubBVFYelMCddksrAq0rSBEEwWK7FNVWJJkPzHKqSELwkjyTB0AAJWeLxaB1cqTiCti2o61Iut6hR%2BrDQ070EHYMrOXkppmkr/hGkLVoGiKMNDbFgk3eaCE2JVDu2M6Fu2JFK2UMKoMBDtHMyqll2eQbsv9epj3TJgFCURoIAkkAFB9X6/LcbajrGzqer6gakWshz/g4BZaE4WJeD8DgtFIVBODcaxrEPJYVlqoEeFIAhNFRhZpLiSQsw0AAOMwzHieIuFiFnma4cNw2kdGOEkXgWAkDQNFIbHcfxjheAUEBJepnHUdIOBYBgRAQCWAgkhhchKDQOk6GiGc2E4VRmYANhfK3JAuYBkBPKQszMXgusIEh7T0fhBBEMR2CkGRBEUFR1BV0hdDaAB3YgmCSTgeDRjGsZpvHOAAeRhPWdVQKgLktm27Ydp2LhdswBI8Y36GvVEuDmXhla0BYICQI2khNsgKAgdvO5AYApDMPg6HFYgFYgCI04iYIGnhRPeGn5hiHhDOIm0TAHHn0gjYSjOGFoOeI6wCIvGAVzaFoBXuF4LApKMcQj7wAUHDwAA3Z404vDeYTWSnDqqNOcIIhx2Xh4LAacTR4DFtfUg79iARAmjcO%2BwA4RGBpgsKgBhgAKAAGpPGjhneUW9fbCFEOIIOJDQ5qDTlHfQhhjBE0sPoPAEQFaQAWKgRqGQr4vjxJCK4phLDWDMDLOBxB7Qf3Ye0DeNQXAMHcJ4Fo/h5HTH6DENoeR0gCDGK0ZIqQtEMFUaUAYEwqgyM6CMJoijxjSJfgILojQjGzAmJYnRehJiOOCH0Yx6iFgKFJqsCQycOCYylmnWWBdra23to7Z2jMK4QFwJ7WuFMG5U3QQsBAmAmBYBiE%2BUg9NJCAizPEQEAsNCSDMJIK2EtYhW0SELEWpAxaAi4FmK2XArbM3iLzK2sRJBc1KVbMJEdZby0VuklWLdNat21tnfW3de41zNmsBoLBX7hhfEwU8Bg2JcHiFmNpuMPZEHERWNoJD/bkOkJQpQ1CI66CHrHeO89gmhOlrwWWWddYwguHnSJRd7agnoWXA5RzK6oGrtECEQIzBpKbqrWZSzogGx7pCjuNcUC7IHpzSWNABrRHHpPCOi9Z5b1JcvVe69N4wJ3khPeB807H1PufS%2BW9b70IfrjfAz9HDvyvsc1Q39xRb3/kLXGQCQHwjAWsXGkDoGUzgQgpQSDOXBXQXwLBuD8GEMYMQ2QVzA43NkFQ8OuNHl0LQYIqwTCgFsPyZwmoPC%2BGGmtcI0R0QzmSPyXYcxzgICuDcW0QIXiZgmL0fkDIQaI0GKceG31djaiuOsbohNNQHE9FDWo9xybsipssXG3xixliBPrvoFOIyZacABdEnZIL9mHKZgJJJpyYWtPhRk0gWSckDHyY00WIBAQHIqeGBI/NASVOqQMytnzODjKVhq9WWsdY51Rci4gKzOBrOLiwBQr8TyvwbZBYY7t8CnO9hcg1ZCjXB3kHcs1OhB2kGeQna%2BbzU6jMzvM3O%2BdVA7r3Qeo97pHQQCrhi6FqJAQdqmWrNu6LO5rvg5i/dHV0yHviOmY9BB0x/puSPQllBiW4wpYfSmJGqUyK3nSwQDLD7cswCfM%2BYg2UwI5ffWVN8n7mP5Z/IVyAf6isEAAiOkrZ4yogeIhVvAlWIIlGqtBMHMFhW1ZgAhRCYGXOvRIY1Id700KfdilAjCbB2vgBwrhAgr7rAkm6ywIjPliIkfavxZjE1yIUXm5R6BC25H0TUaNmiag%2BdMR0exualEhb9UmqYWafE5u6NGjxmbijZrLf4ktgd30zvThwAu/790XHQ1mLDzaz0kDbfXRunbu25MoMEppYt2ZZkBICWI3MBkSxa%2BGLp2Wxm2AmQiuYdMQCSFiCUvm4YJbM0kJzLgrMzDDKFoCD9Va5aTObsEt2vW53rdprAwlGQRtAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/amidst/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/amidst.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/amidst.test.hpp)
