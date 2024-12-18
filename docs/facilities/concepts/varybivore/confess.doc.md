<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Confess`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-3">To Index</a></p>

## Description

`Varybivore::Confess` accepts a callable predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns true and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> Predicate(Elements::value...)</code></pre>

## Structure

```C++
template<auto, typename...>
concept Confess = REQUIREMENT;
```

## Examples

`Confess` turns a callable predicate into a concept so that it can be used for subsumption.

The following code will fail since `(Pred_0(*))` and `(Pred_0(*)) && (Pred_1(*))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return true;};

constexpr auto Pred_1 = [](auto...){return true;};

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (Pred_0(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (Pred_0(Args::value...)) && (Pred_1(Args::value...))
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxoDHOYqqnEANRMXkSnysSY6AD6Gqcm/gAiz4FWga8QF0QAdIDViYAOwWW4ELYMU4EYheTAvKwg16IkwaACCaPR%2B0OxzOf1Q11uDy4zzeHy%2BPwJgP%2BwLBEKhMLhCP8SJRrKxWIImBYqQM3JebgJpwAki9sFi5nCHKcALICVBEBgAT05YKxp01pzmTEcyFOOO5ePOl0JADcxPDnmCxcjURjQeyrA6MdzefyWW4CMrUoxWJgaejiMAFOKsbcAI5ePC3BSnCA3O6PCBBkMgEAW7wBoHAjGGo4nU6xVCeU5ULwMCB08GYSHEaFUMRKVF2l3ot183We72%2B5hsQPB0P%2BCUYyPR2PxxMPDQpwfpzPwmmrVbPMwANnMa8nxPuXFnaYzluztNz2IEuMLxdL5cr1YZ9aZ8JbKLbOr19yYCiUrWoFcF8oYRUBFVfw3C4MNhyrYFWQ4dZaE4QJeD8DgtFIVBODcaxrG1TZtkwVd/B4UgCE0WD1gAaxAQI13%2BAAONcpECEE10kJJ/GYsx/H0ThJF4FgJA0DRSGQ1D0I4XgFBAISSJQ2DSDgWAYEQEBNgIVJLnISg0F5OgEiif1OFUeiAFoWNOYBkH1KR/jMXg7kIEg8HQPR%2BEEEQxHYKQZEERQVHUWTSF0LhSAAd2IJhUk4Hg4IQpDSLQzgAHlLnUghTlQKhTiMtdTMkczLNOayzHjDwdPoM5zEI1ZeBkrR1ggJBtNSXSyAoCAmpakBgCkMw%2BDobliEkiBYni2IIhaZUot4MbmGIZVEtibR6hkojtLYQREoYWhJoCrBYi8YAhVoWhJO4XgsBYQxgHEXaY2WvAzUwU7UKOepLl2IiIm5eCAtoPBYnCuaPCweLYTwfiztIR7iGLJRXh5K6/qMUj1ioAwQwANTwTAQsS3spu84RRHELzXPkJQ1HioL9CulAsMsfR/skyB1lQVI%2BlO4y5nQF5XlMSxrDMUToeIJynvgdY6gaZwIFcaY/GCsJFgqKo9CKLIBHltWMg1hhhhVlZul6Rp5i14Kpb6AZWn10ZqgmQYzft63ldtiRJdwnY3e4jhEOE%2BKxKykyzIsqzJBs%2BNcAcirOK4ariJR9YEEwJgsESKtSEoyR/H%2BNiQUkDRJDMSQ10E6iUh%2B3jSH4wj/gYtdaKSWiuDXQJJC4QI2LXP2ArEiSpPj2T6qUhqVJSjS2o68r9LYTgWhYM0QWMpgDQMIxCqSf4uH%2BF78CIUXnOCsn3JJ6Qyd8ymAt0XqwoiqaYp9uKe6Sse0oy85iHnxfl%2BQVfgHXzft4lVQGVBIBEzBx1qnJEek8EiaXasA5q5UQBzwXsZH%2BV0ahcCEjQWgA0hojQCjNCaBMiFzQWktBwBM1qMAIJtba8U9oHSOidAmF1Ea7FQvgW4DRHrPTsqoN63ICZfR6PFP6AMJrAw4TVUWEMiLQ1hpgeGl0jBI1AIPPg6MFBYxxnjRgBMj7E08qfWQ59/KoSvjTZG/MrAM3EczdObMOacC5gQHmbwbGC2Fgkfe4sWZG3ujLOWngOh6CVuUV2wV1Z9EdtE7INtlh2wtibB2IT8jmx6IE/o8wEmq3NqbNJCsnYLAiYkr2CgPaeXvr7ESvAA4oK/ivK6/8t5PAgJHPeBFY41QTqQJOKcxjpwrnxAIG8C4gg7iCEE/hC7Fzbt3USnA%2B7SRRvJYeSBVKpTgTA4g09dhzzMiwBQZp9RmhqP8D0cw7K70cgfQmx9jGEzMVTAIoVwqRTOtUx%2BiyODJTUpcdKmUDl5SOSc04ZyN6XLShAUqiDQGVX8BA1Z0CEEtW2aipBJzUipHuBC%2B4UKPwfxYn1XBCR8GjXGnNEhlL5qLWWlQ4B61aFbR2pwzA%2B1DpiBYZDNhqjpGkC4fdXh8VXrIHesIwQojfr/UBsqKRoNZEEwURkJRCNVERHUXVTRTBMbY1xvjSGhiPISBMT5Cm5idCvN/nTAWdimYSzQuzbIp0AD03MbW2IsELOpIsxYOMlpk6WfhZYMHcIUsJobcmGziZrcNUSdZ9CjUkwNlsCl5CKckgQVsSlLDycUx2OpnalLye7LYntY7exqf7Tg78WCHOOac85UKI43OjlVHpg9E7J1TpQe%2Bld%2BJmA3v4IIgQC5YI0MO5itEFl1KWbYfukDlwZxAFnTe/haKt04qOtcnFmLe38N82d4kB51XvrZGdCVj2LvWNDTIzhJBAA)

By turning `(Pred_0(*))` and `(Pred_1(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires Confess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Confess<Pred_0, Args...> && Confess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept Confess = Predicate(Elements::value...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEIGYAbKQADqgKhE4MHt6%2BehlZjgLhkTEs8YlcABy2mPYlDEIETMQEeT5%2BQfWNOS1tBGXRcQlJqQqt7Z0FXLZTQxEjlWO1AJS2qF7EyOwcBJgsaQYHJv5uTF5EANTKxJj4ogek1wQAnmmMrJgAdH/Y9DYggUZ2wJg0AEE0AxdmkCNcPAwqJgFAprmcACK3e6PJgHCAAw6MAgKEAgABuYi8vz%2BazOVkh4IhAHoAFTsjmcrnMplsjnXAAqKJJ105PMhfK5UvZ4ohTOhk0wqjSxGulxudweAH0NOj/FiTIErIEMRB1ag/j86QB2Cz3AjbBivYjU%2Bkma0Yt2MyEKg7K1Xm7Harh6g1Gw2m82Wm12zAO4hOgguzBuj1euWQg5HE4p86BgCSoKZkxdDmuAFkBKgiAw3kz3QyIddm9dJni8Mhrr6lSq1VdUNdKd5MOjbYW0/5G%2B7PZP65nDsc8bm3O9Psw2JaIcRgCD/GDIfcAI5ePD3NGI5Gos5uTXoHUvLc7y1Fn0CRX%2B66xVCea5ULwMCAY3tR1fzEJRU09b0ISzRdTnOVcvg3P5H13fct0wY9TxRBEBEvXcbxxe9rhQ5893RFJzGSHCkRRfDby1OZiO3BRSLQ7sPy/H8/wAoC4xApNXVnNMoLbRxkC1JhUQSAhqH/a9KwYasBDrc4uCLPdALpScOA2WhOECXg/A4LRSFQTg3GsaxWy2HYR3MfweFIAhNB0jYAGsQECSQfg0SQuGtfwNECDQUmSMwajqPSOEkXgWAkDQNFIIyTLMjheFJRLnOMnTSDgWAYEQEAtgINIrnISg0COOgEiib5OFUGpkgAWmSSRrmAZBOykH4zF4B5CBIPB0D0fhBBEMR2CkGRBEUFR1Gy0hdDmAB3YgmDSTgeF0/TDJc0zOAAeSuUr4VQKhrga5rWvazrrm6sxrggDwqvoVV7K4NZeCyrQNggJBKrSaqyAoCAAaBkBgCkMw%2BDoA5iFJCBYj22IIjaN5Nt4FHmGIN4DtibRMAcDHSEqoECAOhhaHRhasFiLxgAuWhaFJbheCwFhDGAcQaawhw8HJFE9qVQmrj2RyIgOKKTNoPBYjWnGPCwPakzwOLWdIAXiC/JQMUOTmZaMFyNioAwdwANTwTBloOtdidG4RRHEKb7dmtQ9qW/ROZQSzLH0WXSUgDZUDhHIWaayZ0ExUxLGsMwUs14ghsFwPekJpoXAYdxPC6PQwiWCoqkKTJsgEGY/DmIoS4YYYC9WVO%2BYEAZpmz2Z66aJvFnKUZqnmQYy70Nt2hr7uJA2BQbN2Uf9B2pK9tSi7GpatqOq67yHoJfAiDeswHM%2BpyjY2BBMCYLBEkA0gPMkfwfgATn8a1JF8sxJGSBLAmSG/p%2Bi2KAi4H5ki4MkGoN8aiAK8lwQId9UjJV4KldKIBMpG1ygVP6RVjplRBmDV6tU2CcDaCwck1ompMC7AYIwd0b4/D/iZfqW8hojVkONJ20gXZKDdgtXQ0NVrrQxttDgBlZ4LVSkdEqVxrhnTVMQAhRCSHIDIcAChVCfKPWeoDV65F/BmD3t9HKqCsEJHKqDVAL0xj4MIU1ORnMuA3y4IlGgtA4YIyRgtLGaNiauJxnjAmRN1ak2JBTKme1ab00ZszYm7N9Z7BMvge4fMBYsxoaoEWBxiYSwaHtGWcs0aKyiV9ROatHKa21pgXWHMjAG1ANlY2psFAWytjbRgdtGGO0miw2Qrt5omU4Z7Q20crC%2B0yQHc%2BwcmhhwjlHH2Fg46wITknIZY8GhpxyBnLO%2BRy4hEzsPFYPdK5NH7hXYuTQtmFzmHYJZjcFj7Lbv0BYxy66Dw6C3dZDy7nVDHhPSafCBEwP2hwSR0jiGkM5oo6hj1cADW3rvL6B9SBHxPmMc%2BUUYqkDiv4ShvlrSQOtAFSQz9WpzB%2BXA2wCD95VOQfAVBxUTqGP0cQHBex8HXRYAocknZyTWJ%2BDmSYfVN6DWGnMe2TDWnTXkGwzpOgAikG4RtVmXzdpCMOug0651GVtWZaywcHKuXwiesYtRCQNH%2BG0UgvReqgY0rNa9CkyA0hpC1Oym%2BWptUSSka1GGDiEhOORqjHG7ifW43xmnYmfjBABOptEzAdMGZiDCerCJ5TcmkBiUs%2BJQsknIFFqkwQ6SFqZPlm8HJyt8nEyKZkEpetykREqT9PgNS6nW1turQVLSJBtJmmK92kr5HexjgM/28Ag4hzfJwZkEce39KmfHBIicsDzOuc4CArgrl5y7tsouxQchXN2TkV5A9FkN2aJcp5e6%2BgXMGLu05R61kD1ufnEeH1NjbEng%2BqK3y56cH%2BUyllbKtVLkmGC3lkKPrQqqYfY%2Bp9KB8ORXFMwlD/BBGCn5BK8HrRAMESlTg8DEGgYviASQgRb6BBqCkG%2Bkgb4BXvlwfwX9/Dyow2lUlP0%2BG9XQ7AzDjHXIa09csyQQA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/confess.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/confess.test.hpp)
