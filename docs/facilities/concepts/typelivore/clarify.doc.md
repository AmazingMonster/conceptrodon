<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Clarify`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-2">To Index</a></p>

## Description

`Typelivore::Clarify` accepts a callable type predicate and a list of variables.
It returns true if the predicate invoked by the variables returns true and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> Predicate{}(Variables...)</code></pre>

## Structure

```C++
template<typename, auto...>
concept Clarify = REQUIREMENT;
```

## Examples

`Clarify` turns a callable type predicate into a concept so that it can be used for subsumption.

The following code will fail since `(Pred_0{}(*))` and `(Pred_0{}(*)) && (Pred_1{}(*))` are both atomic:

```C++
using Pred_0 = decltype([](auto...){return true;});

using Pred_1 = decltype([](auto...){return true;});

template<auto...Args>
requires (Pred_0{}(Args...))
constexpr bool fun(){return false;}

template<auto...Args>
requires (Pred_0{}(Args...)) && (Pred_1{}(Args...))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSAMykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHF4ZRgDUysSY6AD6GgcmiQAiB1jItAQAnimYECYBVgE3EExeRAAdMCViYAOwWE4ETYMA4EYheTDXKxgm6gxJWDQAQRM2L24WARxO5y4V1u9zqT1e70%2B31%2B/yBIPBkMw0OIsPhiOR4LR3OxuKxBEwLBSBiF1zcDNQwMBWOIwAU12wApOAEcvHgTgoDhBjqcLsyeRA5QqZStQdi0AxZphVCliAcYqhPAcqF4GBBQRCoTDXWIlNzUQKBUKRWKkYlJQDpcCTYrEsrsWqNVqdXrzhpDajjfKFGaVlczAA2cxFtPEs5cLO/OP5gVWm12h1Ol1uj1ellsjkIiMom7B7GzJiOZBnJgKJQtajuiVVhOe9EWDhrWicAK8PwcLSkVCcNzWawHBQbLaYQuJHikAiaZdrADWIACRcBAA4i1IAmCi5IAJyJL9mMkq4cJIvAsBIGgaKQm7bruHC8AoIBQdeW7LqQcCwDAiAgBsBApAC5CUGgIp0PEkSsDsqhvgAtN%2BBzAMgyAHFIgJmLwpyECQeDoHo/CCCIYjsFIMiCIoKjqKhpC6FwpAAO7EEwKScDwK5rhuN47pwADyAL4QQByoFQBxUUWtGSPRjHMZIrE6h4JH0A65gXisvAoVoawQEgxEpKRZAUBA3m%2BSAwBSGYfB0EKxCIRAMQaTE4TNM8ym8PFzDEM8WkxNodQoZexFsIIWkMLQSWSVgMReMAkq0LQiHcLwWAsIYwDiGVmo5XgABumB1dutp1ACOyXuEQrAdutB4DECnpR4WAafCeDgfVpDdcQTpKDcwrNRNRg3msVAGAqABqeCYLJWlvJul58cIojiMJN1iWoGnSfozUoAelj6JNiGQGsqApL0dXUbM6DXDcpiWNYZiwatxDcT18BrLU9TOBArhTH4MmhAs5SVHohSZAImME%2BkRMMEMePLF0PQNHMJMySjvT9C0lMjFU4wDAznOs7j7MSMjJ7bAL%2BhqdBGlwcZNF0QxTEsWYOq4JxjmAVwLlXntawIJgTBYAknqkA%2BkiJICf5gpIGiSGYkhFpBT4/qLIFgSAF6Au%2BRYvj%2BL5cEWASSFwAR/kW4uSXBCFIRrqEeVhnk4bpBH%2BYFDnkWwnDNCwnVgtRTAHI8zXMT%2BgJcICfX4EQ8M8TJN0Cfd0iPUoz2SboYXyYpyWqRw64h7B2nx/phkHOnmfZ7nBiHFwhfF5cEB2T5DnnmY6tuWhsdJ/EhEBag9mjEPWd50YE9cFBNBPPE0WxZJqWJclpBX%2BlmXZQ4N/5YwBBFSVGnlZV1W1TfjXbTsbc%2BATj1G6r1diqgBpChviNboGkJpTUSrNQBrl4ZLUvKtdamBNpNSMDtUAUc%2BCHQUCdM6F1GA32rndISddZBPQktuZub1dqQysF9BBv0DYAyBpwEGBAwa3FYdDWG8QK6Iz%2BjTDqaMMaeHaHoHGZR%2BYyUJr0bmKishsyWBzJmdMuayLyIzboUi%2BhzE0fjRm9N9FYx5vMRRWiRbHk2MLNWjsu4wV4JLXeI996EgnkXEuisy4kHPGrVymtSDa11qMA2wFQKkHAokQulswSBzBGCRIVsbb%2B27h4zg4dkJ7XQjHJAuE9IbzXsQFOOx050RYAoTqTFOp%2BPDLMdiQSK68VkDXGhIl5ANwYToF2ckFJKXqh3NxEte54QBAZIyNTzJ1IaQcJphcWn6RnlvOe8RzyJCXoU1emzfLlMOQ5EADSUgpDOCss4ayxzEBYN%2BcKp8oqUAvtuO%2BpVLwfIfjlZ%2BW8Cpv2KqVIBmAKpVTEL/Za/88EoNIMAjqYCNL9WQINGBgg4GSQQdNZ4yD5poJvpg9I2Ctp4IJIUg6TBjqnXOpdShXTqESFoaJfpL0hlj2MJ9GwHCkY7kBlkOqAB6UGH0oaWBhh4uGCNOHIyMajPw6MGDuCsfIxVZjqbqOJsq5RZNehqu0bK5mljcjWJ0QIFmtjFjmJsdzIcvM7HmMFk4oS4z1Kh04IPe5tT6mNOacOHq6ylblxCXsqOWsdZ60oB3OJ4EzCF0SIkAIARLZHw0PGr8L4cmaXgrYCOy9zSGxAMbIuiQXx%2B0AkmosgEvyO0SK6nu2a80dzYpmsOkd3JrFWhkZwkggA%3D%3D%3D)

By turning `(Pred_0{}(*))` and `(Pred_1{}(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires Clarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Clarify<Pred_0, Args...> && Clarify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept Clarify = Predicate{}(Variables...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQCspK4AMngMmAByPgBGmMQgZqQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJSXaYDplCBEzEBNk%2BfoG2mPZFDPWNBCVRsfGJtg1NLbntCmP94YPlw2YAlLaoXsTI7BwEmCzJBjsmAMxuBACeyYysmADUysSY%2BKI7pDdMXkQAdN8Aao14TBi9AUx2wJg0AEE0AxNskCDc3AZiHgqGcbscACJ3B5PJiHADsVnxGIgf2RgOB30%2BS2OVkh4IhAHoAFSstnsjmMhkstk3AAqmGmChu7K5kJ5HMlrLFEIZXnSRmxjwA%2Bhp0UcsVhkLRzpcICYAlYAiT3l9vjTCQ8COsGDcCMQvJhaSZiTSjnTZZD5eFgEr0MquOrNTUdRdMPrDQaTR9UFSLRYrTa7Q6ne6XRi3R6GTs9gdU25TbHvhDiMAQUcwZCHgBHLx4B7CxH/VHHNz3FUaV4lstU0EM6HTTCqZLEG4xVCeG5ULwMCDxxPEW1UMRKZ3EhnZ3b7PH5wtU7vlyslzC1%2BuChFIlFnVvt/2dm4H3sV9FmABs5lfF%2Bb15Ot4DXdLBQnyPAcdmHUdx0nadZ3nTBrUXZNHTXDEN0haY8TwZBlSYBQlCaagZ1bLhQTnTMOBWWhOACXg/A4LRSFQTg3GsawbgUNYNlucwjh4UgCE0ciVgAaxAAJJE%2BDRJC4fEjg0AINDfV8zAADmU/ROEkXgWAkDRO1o%2BjGI4XgFBATt%2BLo8jSDgWAYEQEA1gIZIPnISg0D2Oh4kia5OFUZTXwAWlfSQbmAZBkBuKRPjMXhHkIEg8HQPR%2BEEEQxHYKQZEERQVHUCzSF0LhSAAd2IJhkk4HgKKomiBIYzgAHkPic%2BFUCoG5fICoKQrCiLxLMG4IA8dz6FHbiuCWXhzK0FYICQNzkg8sgKAgebFpAYApCSGgdXiEyIBiWqYnCRozgq3gjuYYgznqmJtBqczeLcthBHqhhaFOvKsBiLxgALWhaBM7heCwFhDGAcRPrPWoADdBVqocag%2BLZePCHZKLy2g8BiUqro8LBavtPBtKB0hYeIcclAxXYwcxowBJWKgDDLH48EwIr6suWjeOS4RRHEDKeeytRaoK/QwZQFjLH0LGTMgFZUDhTJAf86Z0ExUxLGsMwDLJ5EsFlucOi6TIXAYdxPFaPRQjmMoKj0AoMgECY/EKh3ugGW3hkK6pagEXpxgt3Jvc6e66hmD2hgSb2ZmdvR0KaCOFijlZ2PWTYJCqjhqNIfTeEM9q/MC4LQvCyL%2BogXA4tGsweImvj6ZWBBMCYLAEkNkTJCOT4AE4jnxSRJLMSRX10gJX279SOE00htJ4z5Xy4V9lO75TF7ErgAl718c9qwzjNM%2BuLJm2zZvsprnOW1aRq8thOEaFhofxfymBubUwYi7vPi4CSYvwIg9aSrIVK/NpCCyUMLPKugkglTKmdTO2dc51Q4I1RyHwbitTeMQB%2BT8X5v0VFwT%2B381SDVQMNeIL4jjLEmvTKyc1SELRGi5Fa9C1r30fv5PBG1u5cE7NtHYxA9oHTyhdE6Z1SAiKujdO6DgxFPUYAQV671apfR%2Bn9AGYiQY0y2PRfADwYZwzygjZASMxGo06LVTG2MTp420ZNZExNeJkwppgKmoMjC01AEfPgTMFAszZhzRgYiebAPSqA2QQtcr0SgWLOmGsrBS0sQbeWisBDK1VurSWFhtZ511glOGcsjah2cBAVwsdCrW1KJHe2aRHZZEDi7FINT3Y2yqcHY2fsY71LjiHX2PRw4tKTnHTpOQGnx1mJUwZ41Vhp3SvAmqeV85sJwa/Aw%2BDCESQGpXf%2BFDxrUKPo3ZurdKCZ2nrPT%2Bkl8Sb3xDJSQQ8gqFUQXvWwB8pqWWsnZByzUmFX08t5Dg98uosAUNDcK0MCGfDzNMX%2BVcEqAJSnzUJmV5DgMiToEARxiqlXKkDOZO8FkNXPi1NqALgpApBTcMFn9IXwhIWQ6uRwjh11eTNOhdLvksJGiAEFyRkjKkpcqal2EsFBT4HQfhgjDrHSumIiR11br3VkaQ56Ci3ofR0Zgb6v0xDqJJpo9xtjSC6NDrDQG9EjEmJJmY9G9FLE4zODYgm9ixFOLSC46m7ifQ0MZkwZmrN2acyCUAhFEgwlZRRSLdFMTjCZOljEJJDEUkMEBoyVWEtNaWGyQxXJ%2Bt4Apx6d0U25sRlWzNonO2rsmmZDKY0womQy1e0Kb0/2zQultKKX0vo9ao6jD6NWsZXaM7TM4oO9GCDd6cEwSwQFwLQXgupZsv%2BJAdlMobqQJuLdhiG3RqcxIn8GUBHklJXSDL8RLzxQZTg%2B8zKro7gEHuARlJvm7pIbuMk%2B5cAxejI48yL1GUPtNTO0Vz150vf%2BwSpNdom0kEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/concepts/clarify.hpp)
- [unit test](../../../../tests/unit/concepts/typelivore/clarify.test.hpp)
