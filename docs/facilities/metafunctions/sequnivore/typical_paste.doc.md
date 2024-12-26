<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::TypicalPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#sequnivore-typical-paste">To Index</a></p>

## Description

`Sequnivore::TypicalPaste` accepts a list of packed sequences.
It concatenates them together and uses the first sequence to hold the result.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Vs<sub><i>n</i></sub>...&gt;
-> Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

`Sequnivore::TypicalPaste` can also handle `std::integer_sequence`. The function `static_cast` integers to fit into the first sequence.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Type<sub>1</sub>, Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Type<sub>n</sub>, Vs<sub><i>n</i></sub>...&gt;
-> Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

Here, we paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
/**** SupposedResult ****/
using SupposedResult = std::integer_sequence<int, 0, 1, 2, 3>;

/**** Result ****/
using Result = TypicalPaste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPaste` using recursion over the total number of packed sequences.

- **Base Case:** Handle several amounts directly;
- **Recursive Case:**
  1. Concatenate several packed sequences at the front directly and place the result into the first sequence;
  2. Invoke `TypicalPaste` with the newly packed first sequence and the unhandled sequences.

A simplified version will be as follows:

```C++
template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedSequence>
struct TypicalPaste<PackedSequence>
{
    using type = PackedSequence;
};

// Recursive Case:

template
<
    template<auto...> class SequenceA,
    template<auto...> class SequenceB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct TypicalPaste<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    using type = TypicalPaste
    <
        SequenceA<VariableAs..., VariableBs...>,
        Others...
    >::type;
};

template
<
    template<typename, auto...> class SequenceA,
    template<typename, auto...> class SequenceB,
    typename TA,
    typename TB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct TypicalPaste<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    using type = TypicalPaste
    <
        SequenceA<TA, static_cast<TA>(VariableAs)..., static_cast<TA>(VariableBs)...>,
        Others...
    >::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADswQAOqAqETgwe3r4BaRlZAuGRMSzxiSm2mPaOAkIETMQEuT5%2BQTV12Y3NBKXRcQnJwQpNLW35nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiyp9GyCTPUM1wenF1fHv8df5zO5wImAeBhBJkCbgIAE9UoxWJgAHQoyHYIFjYheBzXAAqcLwoloyiYY0w1xMSSsSQAIpCrBcgVsttcLKTyW52SAgUCQWDXphIdC4Qi2NcScgANaYdBCTAARy8jA2aIxBCxOPxqUJYhJZKFEulsoVSoYKsC6MZVKB11t1y8mSM11h8IpgRp4qYUplcsVysFgQZgNp9J53xZACVMMg1pkAG4crlh4Ggx4CnlQm12vlpiFQpheIgopFo67IAwKBTXX2mjbnUhZ2058EBzmF1DF0vl0lVmv%2BmyN64FosogBqzTwTFi9HOClIFIudqH7eL4%2BIk%2BnmAsc8HLtFyJRAHkCAgEgoM5bZ%2BrsQQ8QSiXq824%2B2bMICoWuNzOFJ2LfOXxsVgfhOU70Nuv7YPOx6nsQP6ohaPLWoudoOhEwDOiKboelqOrEqSELIbaQqDkuAFvkKn6gW%2BcFIvOlGbuB8GQSRdrQWenaEW62AgCAe6hladKBsmzbpoymacSJT57swbDzsOHZMWWFa9ia/r1ruqYtkK0mInJK6Kd2lbVqpr4DhJIoyeSuLqeZ8KWXiZnnEu8mriBm6zvOg4uWOblgTutn7sWbGwReaoareOEPvhrZke%2BbjWXRvnURB/4mYBQq4jY1z0X5KXXMFNGqlaQZLqhTp7lhd7alF%2BqccRnGkWl5FQgl1wzI4yAAPqiGMGXvtgEA5dRizFvO7WEt1%2BF9Wig1JduI1MQ2DWsSe7GonVFo8XxQkCfxgLfH8vwAj8OzXNgqisI85KfEyh3/Mm5iBBE5ZeFgbpuGgr6pAQ54IYyZhPWa3hvUKhZ0IQMJFftlwHNWXipOkSjoFGCheLQt43RcZXoUI8OIzKKNo7ekIemM6A8REILAAknVKH6r5CpT84aPOXDzmY86BKqO3Qyd1yE%2BjHwnEC2P85gqOCyTVW4Y%2BgpiW4g5kxTgiYNTxC001jOCMzaKeZxSsgBEWCqBr9Pmm4bPXGYuuKwQ5OGwwxum7WrZc39/VbSKe23TcuLixjwsXONXU9gkBAQAbCiIp1pJCgLBD/njGQE%2BLRNoos9IcMstCcP4vB%2BBwWikKgnAK5Y1htas6zko9PCkAQmhZ8skoBJISIaAAHGYZgAJw91w/idx3XBJEk0g5xwki8CwEgaCzBdFyXHC8AoIAsw3hdZ6QcCwDAiAgKsBCpIW5CUGgDx0AkUSIpwqgdwAbAAtPfkjXMAyDINcUhImYvAyoQJA8DkzZvwQQIgxDsCkDIQQigVDqE3qQXQbMADuxAmCpE4DwbOud86N2LpwQ8hZj63lQFQa4d8n4vzfh/L%2BbczDXAgB4C%2B9BiAUgBlwRYvAN5aGWBAJA59tQsNPhAARl9EjACkBzGg6MzyUFiHg2IERmgwkwbwRRzBiAwkPLEbQ0YN513Ps8Agh4GC0BUQgrAsQvDAE5LQWgq9uC8CwCwQwwBxAWLwMQPReAEwOKLpgVQ0ZCybDrpTWoeDaB4FiGgzRHgsB4PVHgGejjSAJmILEZONJQSuMiUYRuywqAGGAAoUceBMDIMPHZVR0DhBEkgdIUB8glBqDwUg/QriUDWGsPoKJq9IDLFQN9bIDjH5kxJqYculgzCLzSeuLAfSIDLDsN45wEBXCTD8GzMIERBgVGGGzRGxQcieHaHoQ5bw5hDESGzZZDgejjFaCc/INzagrIYL0Foly9nXNsA8jZegZifJ2fMfZSyq4bAkNgjgedSAL14EvchD9n6v3fp/b%2B9CIC4AAaw2unD675OWKeJgWBEiLNIC3SQgQkQ90CGPDQkgzCSHvnPfw98e76E4FPUgM9AhcCRPfLg98O492HvffwkgB40vvrCvBS8V5r3xZvXhe8%2BEHyISfCgIjUDMKvjfDgzQWBxiSI/JgSlXFfx7kiPl/j8BEDmXoRp4DxBQMabAlpCDdAc1Qeg1RUKYVwvwRwQhR9CzXFIYiyhr9uxOi4Ja61DCmGCISGwwIZg8XcK3qq0RQjNXZuGNGiR/cWbSJBLBORCilGaOqeo5R2jdEOGqYYxgxjTHmKLpY6xtj7HVOcTkzY7bPHeN8XggJQSQTVLCRPIukTonKLif2rh65kl1zSRkpQWSXFGFyaAJVfAiklLKRUqpKTHV1IkA02Qbr4FF09e0vJEyrCWB6bEBZAyhkCBGWM90D7rDTPhbMoB4t4BLNeXc1Z6ynmbJCI7L5CwDlFDeP8%2BDmQLnAquQC0DbwPmPLyFB25WGHmwf2b8voSGSNArKOhjhKw1gQuoxPf1srOARuRWamNcb24MKxXalNHCuEEtIESkllAoVcp5Za%2BlSR/A91HoEBlTKJUyoQXK2wCqM3KvgKqw%2BxDhF5uINfNgnADVUJYAoOMn84yxqRC2MYf9bWAOATUp19SalXtaSAYI3qMGOL9bg5TBD1UkLIaoEzZmLNWZs7eRh2qk04oBoEdN%2BTt78Ji2I3TqWWEgHMwjTqlme6dUi51ELDS6CltXhAeRCCa1VpSdVrROi9GNu1UYkxZi8EdpsWIbtKTe1boXaQfAXi7nDoQaOmM46UmToiVEmJMJ50JKXdU1dmTslbrQklwpTBimlPKZUxg1TT0QPPa55p16dAebvcYLpT6Z2vuLu%2BhgDithKx/VMmZCQ5lAf6V0N5LhHZke2ZR75ZyEPZDI%2Bc7IRGfn4fuaRyDGHugNEI2h4HNy/nw7R7MFHcGwW0cgb5pTi9mPFeuKZ8z1w8vWYFGMLj9m4u8sS0qwlmBiXDDJRPMTIBe5IkCIEfwg8JVz150kIVhP4WcHlevATFL/DUpHkkOeHdJD9y4F3Mw0qJ6BD80T5eiqeFQt/mLwN/GmepLPNkEAkggA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/sequnivore/paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/sequnivore/typical_paste.test.hpp)
