<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Confess`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-confess">To Index</a></p>

## Description

`Varybivore::Confess` accepts a callable predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns true and returns false if otherwise.

<pre><code>   Pred, Es...
-> Pred(Es::value...)</code></pre>

## Structure

```C++
template<auto, typename...>
concept Confess = REQUIREMENT;
```

## Examples

`Confess` turns a callable predicate into a concept so that it can be used for subsumption.

Since `(Pred_0(***))` and `(Pred_0(***)) && (Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (Pred_0(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (Pred_0(Args::value...)) && (Pred_1(Args::value...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgmgM45iqqcSHTF5Ex6cXVxM/gAIocTEkrElgRBvkQAHQIpYmADsFlOBHWDEOBGIXkwQKsyOBBPuD1JewOfzO5y41wOd0ez1e70%2BsNQVIutKBoPBkOhbIRcKRqPRmOxuPx/kJxKlpPJN0OADUmABPOn7BkPAiYFipAzaoFuNmHACSQOwpPGuIcStVctRpMOTsOs0cyEOTO1LK%2BP3ZADcxHiwaizUSSY8UTKrBHHhT9ocqF4sTdNdrdfrJW4CCrUoxWJhBQ9iMAFObSacAI5ePCnBSHCAnakaCBFksgEAB7wFxFIxkCZkfQ4xVCeBNJiDCtGYDHELFUMRKElhmNanV6pgG/xZnN5tiF4ul/wWx6V6u1%2BuNgEtg/tzt4wVLJZgswANnML4v/xp17bHcD3aFXsnn7L1B2HUdEwYCcUSnGcsRxPEl2JFc4yOAAVTBxnVW5yW2Q5sGIYgSEtZo3XOJgFCUVpqCTQ1lRVQ0uDLI8JyRKUOBWWhOCSXg/A4LRSFQTg3GsawXTWDZMGffweFIAhNA4lYAGsQCSF84QADhfKQkmRF9JAATn8PSzH8fROEkXgWAkDQgj4gShI4XgFBAIJ5P4jjSDgWAYEQEA1gIVIfnISg0F1Oh4kifNOFULSAFp9MOYBkHdKQ4TMXgzkIEg8HQPR%2BEEEQxHYKQZEERQVHUDzSF0LhSAAd2IJhUk4HhOO43iFMEzgAHkfiCghDlQKhDlil8EskJKUsONKzHrDxwvoT5zBkpZeHcrQVggJAwtSCKyAoCBdv2kBgCkMw%2BDobViBciAYi6mJwhaFVWt4R7mGIFUepibRMAcV7SDCthBB6hhaBe6qsBiLxgCNWhaBc7heCwFhDGAcRIZrP7HD9TCureP6fi2WTwm1LjqtoPAYiaz6PCwLqcTwaykdIXHiGHJRgR1NHKaMBSVioAwS0VPBMHqnrcz42SCuEURxFKmWKrULrav0NGUFEyx9CplzIBWVBUgaRG4vGdBuVMSxrDMBy2eIXK8b17pseyFwGHcTwOj0UJwiGSoRjqoosgEKY/ADjIg4YeZhgSOq7GdgQ%2BkmD38ljup48aCYBh9hZ/dsTOQ70WZWijv2Y5WBQJM2CR2o4HjSHs3hHNG%2BLEuS1LJHS%2BtcGy5bTK4Na5P5lYEEwJgsASCdSBUyR/DhIzkUkDRJDMSQX1stSDPMjhLNIaz/DMOF/BfZENP8DSkiSLhjIMjT666xznNcwePK23ztv8/rgsO46lqitgYpbpNZABgjAzQMnCLgcIBJZSIHbPKdUZZFXltIRWShlbVV0BdRqzVXo1zrg3bqHA%2BqBR%2BENEaY0JoehAcAMBECoHzVQIteI0kzADw2p5d%2BP94ghSOowvaS0UDUK4AZLgQQaC0Gurde61V3rPQBrIz631fr/RZkDRgBBQbgy6lDGGcMEYAxRjzLYAl8CnAcHgXGiNoGqEJtqAGpM6hdUptTZ6dNjHrTtszWSbMOaYC5qjIwvNQAvz4ELBQIsxYS0YADRBcsSooNkErKqAlMFqz5hbKwWtnG60ngbI2nATYEDNiCDJVsbbxDgQ7SecdzHOAgK4AudVvblGjnoQODRGlpHDg0EuixU49ATvnZOocna1IznMbOrTY5DLyCMouWcWml2rqsdYVd%2B5b3wffTgzdxqJWAWjWhkCrgQG7rA6S/d1pD1ICPMeIxJ4qVEUEcmO895JDhIZJIBkzBfNfBpK%2B%2Bk77VQfrYJ%2B7DX7wHfgFAaPCuHED/lsFoLBEosAUH6d0fphFwgzOMTK%2BBYG5XyrIJB8SyryDQcknQAQGpNRakjPBnUgW9U/oNYao1kWovRZi7Fg0IALX4cwla/g2H8y8jtPh%2B0YXioEWi1IqRzgYoMucbl5xVAAvEZIyg0iBIKIhrJHVSjsYAzUSDMGEMTGYGhrDMQ%2BiWaGMCe40gpjnaWPxjY5ARN7GCEcRTKmNMVRuIZp4gGPiMh%2BO5oE8IwTNqhKYMLUW4tJYxKJXEiQCTyrkpVlS6hGtLZZJ1vAfWhtsiI22KbHNmSLDW0brbe2OTy5pzGa7d2syvZu16bndp2ROmdtKJMpZ/T06JzaMMwuDaGhDvbTHPO/ROnzMncsiuqySr0sBQ5bZqrJoorRYcBVWKNyYR5ackg5zhUv2HqPcelAa4vICAff5pkzCPq4BpDQL5PmrsbpwR%2BbkrnT1nlfc%2By9/BJFfaZPSW9/AMrXU5Z%2Bm0a4ZQ/YQy5Z7WbxEyM4SQQA%3D)

By turning `(Pred_0(***))` and `(Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires Confess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Confess<Pred_0, Args...> && Confess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept Confess = Predicate(Elements::value...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8biYXiId2UxEw%2BFEYNIdwIAE8UoxWJgAHRE7CvRgEBTQ7AgtAMbYpAh3DwMKiYBQKO7QgAiiORqI%2BmAgJPBZIUIBAADcxF5CUSVtCrNcQX8Aeclcc7gAVVnkr6q34qk5AtX3JEogD6Gl1hyBNNmmFUKWIdzhCNN6AtHP83JMiSsiU5EBdqCJBLlAHYLMiCJsGJjiNL5SYw5zE4r9SbeWauFb9jaBHaHU6gzzzdmuRzfT6A0GQ%2BHI5ho8RYwR45hE8nU8D04c7gA1JhYnNAsEQ/nQ2Hw1CPSkg2bxhx9gcgpMKq53dd3WYfPDIO62sGF52Tu6S7yYDkRh5JlP%2BVfXzvGntULyx74gkcvMcw7G45hsENXMQwAUv4VLXMiACOXh4Mi7JMiybLjm6FoYoBwEhjO1z7vajp3DEqCeHcz4MBAdZRjGRFiEo7YpmmoLgp%2BULfjieL/kSaEgWBgGYFBMGsoyAgISBbjIUEdwcRhoEcmYABs5gyQJzKssJyFcKhQEKJJXHYYe%2BGEcRpEruRTZxgmt73nRyqatqQ6zk0jjIGaTBsvEBDUC%2B479li45cDOoGkXKt4cGstCcIkvB%2BBwWikKgnBuNY1ibhsWznuY/g8KQBCaMFawANYgIkMkEgAHDJUiJGGMmSAAnP4lVmP4%2BicJIvAsBIGhBJF0WxRwvCikEWVRcFpBwLAMCICAGwECk8LkJQaDPHQ8SRPinCqKVAC0VV3MAyC7lIBJmLwKKECQeDoHo/CCCIYjsFIMiCIoKjqENpC6GpADuxBMCknA8CFYURdlMWcAA8vCM0MqgVB3OtMlbZIO17XcB1mHcEAeIt9BOmlXArLwg1aGsEBIAtKRLWQFAQGTFMgMAUhmHwdBgsQooQDEwMxOEzRYn9vBc8wxBYqDMTaHUg0ZQtbwEKDDC0Lzr1YDEXjALCtC0KK3C8FgLCGMA4iK3x9TiqywP2nU8I7Bl4RgqFr20HgMTfULHhYMDLZ4G1WukCbxD4UonLgnrDtGNlaxUAYwG9ngmAfaDv58w9wiiOI91XfIShqMD736HrKAJZY%2BiO6KkBrKg9JZJrG2zOgXKmJY1hmN1vvEOdpul10PRZC4DDuJ47R6KECzlJUeiFJkAhTH4anj70Qwj6Mam1PUAj9JM/d5Ev3Tiw0czzyMCRL3MU96FuLT70sh9rAoyXbBIAMcOFpBdbwPWw5t227ftkiHejuCnTjBqeMCZhzWAgTATAsAJFIqQfKkh/AElqmGSQGhJBmEkDJDqhVqpNQ4C1UgbV/BmAJP4GSYZir%2BGKokRIXA6rVWKs/YGPU%2BogAGmHEa40SaTQhrNKmNNsYrTYGtD%2BiNkAGCMCjaqBIuAEmiidIgrcLpqXTjdVO0h05PSzq9XQjMvo/T5g/J%2BL8QYcHBtNeEdxobv3httMRetJHSNkejTG5NsbSSIfjTK7CuH8PiHNamqAsajDsUYLg1UuBBBoLQFmbMOavQFjzROCShYizFg4ROUsySy3lsDJWKs1Ya0TjrYOOxor4GRMbU2r1zbIEtonG23RgYOydjzV2pSCaty9hlX2/tMCB11kYEOoAhrh0jgoaOsd46METiolOd11GyE0S9aKOjc6h3rlYQuzSS4wPLr0KuNc64FwsE3V%2BLc247OvtvFefgICuBPmpIeZQD5j3SBPbIG9p6pDeXPYeLyt5d1XsfT5p9rm9DXvMZ5l9T7AtyF8s%2BkLFijzxusTYd8UV2yMUwzg1iEZ7nEcABxMjLSCnwAo9xwCvEjLARAqBlA8rtSCHbfBhDEgEhqokaqZguWyWKrQqqjDXrMNsKwqlRMOHwC4VNSG/jfHEEETsZoLBtosAUOKXc4owkEkhNqY6ZKzpKKTqo%2BZSclnZwCKQPRv0taGKBkKsGPCoYw1UCqtVGqtU6tmM4wJrj4juP8J4wmw0fE%2BoprK0N2MJTIBSCkM0mrqpmk9QQM0Lr1HM3iLEzm3MhZJOzcLUW4sMmBOltkhWZTMDK1VmIQp3timDPaaQcpO8TaazkaoC2YJ6mCEafbR2zssRtPdp0xOPT0h9KDoM8IwzxURyYFHGOccE7e1mbdCQCzHqZ2WToC1BL84Ny2cXeAZcK75k4LsGue7NknObvERR7cYHL16D3PucLB69wvsi75RQsgPK/e8j9i9O47yBQMX9j7d4DAA4fcYoGQVH0g386FKKb5orurawV3UcWpruKq9VJ4PX8i9aSgBFLA2gNIOAyBowYHMtagEYh/KGpmGY1wYqGgZKcow6/TgLC2HUtgSAeB0jKGJDQdUdjDVKq4P8HazDvUxU5VwUdLjJiQH8d9hkZwkggA)

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/confess.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/confess.test.hpp)
- [Example](../../../code/facilities/concepts/varybivore/confess/implementation.hpp)
