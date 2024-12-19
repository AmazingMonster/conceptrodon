<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::AllConfess`

<p style='text-align: right;'><a href="../../../index.md#concepts-mouldivore-conceptualization">To Index</a></p>

## Description

`Mouldivore::AllConfess` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `true` for every element and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...&&Predicate&lt;Elements&gt;::value)</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&Pred_0<*>::value)` and `(...&&Pred_0<*>::value) && (...&&Pred_1<*>::value)` are both atomic:

```C++
template<typename...>
struct Pred_0
{
    static constexpr bool value {true};
};

template<typename...>
struct Pred_1
{
    static constexpr bool value {true};
};

template<typename...Args>
requires (...&&Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&Pred_0<Args>::value) && (...&&Pred_1<Args>::value)
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BXKQADqgKhE4MHt6%2BeqnpjgJhEdEscQlJdpgOmUIETMQE2T5%2BgbaY9oUMdQ0ExVGx8Ym29Y3NuZWjfeEDZUNcAJS2qF7EyOwcBJgsyQZbJgDMbgQAnsmMrJgAdDeH2CYaAIIKBMReDgDUysSY6AD6GgejxMASsTw%2BEI%2BLyYjmQHzQDBemFUyWIHxiqE8HwAbmIvJgPiCLK98SCACKHMHAgIUg5UoFbHZ7TCHY5nC5sG5XO5Al5vT7fX5/LhAolAyFQ%2Bqw%2BECJEotEYrG47wEokklk0ymizV00VPRm7GEso6nc7MTk3R7EYAKHlPH4ARy8eB%2BCg%2BEC55gAbN7Bf9AUcrTa7iAQMr8QsgQi5aj0ZjaB8qF4GBBI6CfgRVgxE2IlFrNU8GdtDfsTezzddLdbbQd7vbME6XZg3R7bmYfe2/QDWUGa9hQ%2BHMAtCe3ve7PaPOz9/iLA9WQ2G8UOo7KtvK41ikym0xYM1mPur8xTC09obC/kwFEpGtRk6zwgQ7qnI3SOEtaJwAKy8PwcLSkVBODcaxrChFY1lVMwDh4UgCE0N8lgAaxAT8vSuAAOL0pE/AIvUkABOA5cKg/ROEkXgWAkDQNFIX9/0AjheAUEAaLgv831IOBYBgRAQBWAhki8AhyEoNAdjoeJIkuThVEwgBaPCPmAZA4SkK4zF4X5CBIPB0D0fhBBEMR2CkGRBEUFR1HY0hdCSAB3YgmGSTgeHfL8f3ggDOAAeSEwSCA%2BVAqA%2BWSvQUyQlJUj41LMd0PHE%2Bg0XMaCFl4NitCWCAkDE5IJLICgIByvKQGAKQzD4OgtmIZiIBiTyYnCBoThc3gGuYYgTm8mJtGqNiYLEthBG8hhaGa6ysBiLxgDcMRaGY7heCwFhDGAcRxqbGpsWbTzkWqISNhgh8Ok82g8BiRyOo8LBPNePBKIW0gtuIDElDJbYVtOox4KWKgDBtAA1PBMDs7yzRaszhFEcRTIM%2BQlDUTzbP0FaUBAyx9DO5jICWVBki6ea5JedBDjJUxLGsMx6Ke4hdO27H2k6TIXAYdxPBaPRQhmUpyjyNIMgEcY/CSfJ%2BYYfpufmBnetqKZBb0KoagEHpGnFwYKhGXo5cmXpVbmColgUcD1gkNyOG/WjPIYkL5MU5TVMkdT3VwbSkqgxY0u%2BpYEEwJgsASVNSGQyQDiuQiAkkDRJDMSQvWo1D8NIjhyNISjoKuLCvXQ/D0K4L1P0kLhP0Ir0LeshimJY2Dvs4nisr4vyhJEwrUASyTpI4BoWGxAI5KYeEDCMaL8KuLgrn/LSiBpvSklhozoekWGLIR6zdHKhynJa03zbo3gGN8gShMC4LO%2B73v%2B5WoeR7HuKW9yxKRwOMxUqr9jMuy2%2B8qborEpAE%2Be%2BQAepV8JcBojQWgVUap1Wsm1Jq4MYEdS6j1Bw4MBqMAIMNUankJpTRmrQOa4MlofQ2P%2BfAPxNrbWsrtZA%2B1wZHQ/NZU650mpXWIWlGm90YJPRepgN6y0jCfVAK/Pgf0FCA2BqDRg4NZ5QxMgvWQS8rL/lXsjL6ZMrDo0YVjAOuN8acEJgQYmBxSZowsJTXe1NaZaINh0aWzgICuC1sEFmusebCz5l0RxIsuguMlgrLoysmhswmFLRW3Qpg%2BPVtCMYQShYaxVlzNWJtlirGNosRO29LacA%2BH/M%2BACL5cGHqPDQTt8CTwfu7F%2BGUvY%2Bz9pQU2ydU7D0jgEIuAQAgHCjjHAupd6KcArqxauXFeL8X8l/D%2BiUpJsE4J3RSLAFDYjhNiApVxmQvE0qUnS08IZz1kRDBRiMQAHFIOvZyC0t4eTLj5BuAUgrZOICwWZ8zFnLNWQFCA8U77xAfgcZ%2B6UOJ12/vEMZrcEgLOSMkP4Sz8J/FeRee5eEKrgPiJA%2BqjUOpwLRZ1bqvUUEt0GugkaY0SGYEmtNWa80YKEP4aw0gpDpZbXmuPVQe0ti0MEMdBhZ0LonBYTddh4MuFpB4e9fh4RBEZWEUwAGQMQZgwetI4yEg5HmXhoonQhyVHGBMRjGIViAJ40yPNAA9ETVG5NLBmIAhYrAeq/FM3sSzRxnMSiJLcQUTInj3GZAifLGxoSAmOLtUrcJCS9by1ljE8NOtQ2uINkbEy5yem7yyTMiKcyFk4heUaF4JSXblN%2BZ7Ug3tfZDADvQhp/hh4HAOJ%2BT8kcQEaGrbhdCSavKMVsJXP5CwkIgGDiPA46F85QTrV6KCuFE4HAub09tXbTYaVbeXSpCFHrIqZpIIAA%3D)

By turning `(...&&Pred_0<*>::value)` and `(...&&Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AllConfess = (...&&Predicate<Elements>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQgZqQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJSXaYDplCBEzEBNk%2BfoG2mPZFDPWNBCVRsfGJtg1NLbntCmP94YPlw2YAlLaoXsTI7BwEmCzJBjsmAMxuO3sHmMenAJ7JjKyYAHTPx9gA1MgGCgpvysSY%2BFEO1IbwIt3ubGej2w9DYggUrxMGgAgmgGJtkgQ3sjaLQPAwqJhvm9jgARN4QKHmALUv4AvBAy4nGG7RgEBFHbAgEAANzEXkwS2OVhRSORAHoAFTSmWyuXisVSmVvAAqRPZb1lCpRSrleul2uRYrO%2ByYhxOYLuzEhL05YumxC8Dl%2B/3QAH0NGKTAB2EXIt4Bt7TM0Mj4CaaYVTJYhvGKoTxvPneTAk30ER2Xb2k4VerM50Uok0XK6WiFPW3Ye3pp1Yunuri5v2BoMNRzIMMMCNRmNxhNJgWpizVzPZo5%2Bn2j8eF3am803K0PKHI4jADmVlH/ACOXjw/x%2BOLxAkJ3yudY9IOXq6pdpRaK70dj8dobyoXgYECFvv%2BBHWDBfYiUHM8wLZEizNJl5zLJcVzXMUtx3PdsVxfFjw5Nwzw0C8YOvd5qWpJDDwJIk0LPLgsKvCsxTvHZu0fBNX3fT8LG/X9QQzIDsxA4M2zdJhvniAhqDfK5wgIV4PyFMcxQ4FZaE4ABWXg/A4LRSFQTg3GsawgzWDYU3MI4eFIAhNBklYAGsQHkyRHg0SQuG9I4NHkjQzACAIzAADk8/ROEkXgWAkDRMOU1T1I4XgFBATCTJUmTSDgWAYEQEA1gIZIvAIchKDQPY6HiSIHk4VRPICABaAJJDeYBkHbKRHjMXh6SIYg8HQPR%2BEEEQxHYKQZEERQVHUOLSF0MiAHdiCYZJOB4WSFKU0y1M4AB5TKMqxVAqDeErysq6rareeqzApDw8voGMDK4JZeFirQVggJBcuSfKyAoCBntekBgCkJIaFoHZiCiiAYiWmJwkaa5Zt4cHmGIa4VpibQaliozcrhAgVoYWgoZGrAYi8YA3DEWgou4XgsBYQxgHEPHdxRvAeSJJbIxqTKtiM0TOiW2g8BiKb4Y8LAlvTPBAvJ0gmeIOMlFJXZqd5oxTJWKgDFXAA1PBMHGlarWh/rhFEcQ%2Bs6%2BQlDUJaxv0amUC0yx9D5qLIBWVBMUyMmyumdAyVMSxrDMMKpdarAnY/DoukyFwGHcTxWj0UI5jKCo9AKDIBAmPwyNT7oBiT4YyOqWoBF6cZY9yAvOgZ4uZlzoYEgLmYM70YMmlrhZ65WBRdM2CR5o4RTSFC3hwp20qKqqmq6psk6IFwQgSBJMxDJu4zlZWBBMCYLAEjDyzJCOR4AE4jm9SQ7LMQJgvkgJD98jh/NIQLDMeAIuACTzD88t/rK4eTj6CIey0Iq2GiqvOKD1kqPVSutTK2UPqoHOgVIqHBGgsB5N6MqTAPgGCMEdQ%2BjwuC2SavgFqbUOqyG6sbaQptBoWxGroJIk1prQz7gPQB4U1rpUym8LabxUHoMwdg6meCCG2VOggl6F1F5HGWLdZWCUnoSNenAz6F0QD8IwZ8amXBD5cEwv9QGwNQYjVhpDfWpj4aI2Rg4fW6M2RYxxktfGhNia4jJkZSmCstiqXwP8WoTMyaqVZsgdm%2BsuZyRGrzfmkMhbeNuq1cWRkpYy0wHLKmRhFagHAXwNWChNba11owfWptKG9WobIWhw1VIMOtkrX2Vh7ZRNDi7N24ZOCewIN7I4pJ6n%2B0DvEYOzNnbhyrn4CArgm5kQTqUOuKc0hpyyGXTOKR5k50TrMiuEdq59EmSMouPQa7rPbs3RuSyTl9Dbsna6qx1g92uREthS0R4aMEVo3BOjREaApHPFq0jrpyPAevTe29KB9wfk/fBdlvR/29I5SQF9KpkXYZwSKoC7rxUSilNKG0VFKIuoVNgnBUH7RYAoHk7YeQfIuNMYh89g7kK6kbMpBtKmWxAEcUgTCZrk1YYtEaHCYGbW2sSqqpLyWJipeBaY4jEGXSXkcFe6KHqKNlbi2VvJkDJGSG6Slh83TUoILxYgLBKp8DoIYygxjVIWNxkZG1ViUa2IQRjBxuMfGYAJkTEm7iKbywyXE0gviGYBJZqoNmOwwmCG5pEvmAtrixJFgk/WyS0ipL9TTcIWT7o5KYBrLWOs9YSxKUyiQ5SBrmyqTodltTjB2xsE0%2BALTuhk3FF7W2ftLAB2HkHNqQyw6F26FHGOORlnTPmFclZhRMi7OzpkS5%2Bc9ndBLs0M5mzRnLvnfXUYOzV3btbkcq5ndu69V5YPJ5nA%2BHGpJWSilkqdjStniQheV1FVr1IBvLewww4RPBYkfBRwjjyRcvZYKAHvTvzPfylFICYpvr3vJI%2B8lPJuUPpIQ%2BjkT5cA5REo4fKwrQaVX3RqkH8PAMI5LeI6RnCSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/concepts/all_confess.hpp)
- [unit test](../../../../tests/unit/concepts/mouldivore/all_confess.test.hpp)
