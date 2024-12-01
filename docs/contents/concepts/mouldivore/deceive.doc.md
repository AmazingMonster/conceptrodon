<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Deceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations">To Index</a></p>

## Description

`Mouldivore::Deceive` accepts a class template predicate and a list of elements.
It returns true if the predicate invoked by the elements returns false and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> not Predicate&lt;Elements...&gt;::value</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept Deceive = REQUIREMENT;
```

## Examples

`Deceive` turns a class template predicate into a concept so that it can be used for subsumption.

The following code will fail since `not Pred_0<*>::value` and `(not Pred_0<*>::value) && (not Pred_1<*>::value)` are both atomic:

```C++
template<typename...>
struct Pred_0
{
    static constexpr bool value {false};
};

template<typename...>
struct Pred_1
{
    static constexpr bool value {false};
};

template<typename...Args>
requires (not Pred_0<Args...>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0<Args...>::value && not Pred_1<Args...>::value)
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAnKSuADJ4DJgAcj4ARpjEEhqkAA6oCoRODB7evgHBaRmOAuGRMSzxiVzJdpgOWUIETMQEOT5%2BQbaY9sUMjc0EpdFxCUm2TS1teZ0KE4MRwxWj1QCUtqhexMjsHASYLCkGeyb%2BbgQAnimMrJgAdPcn2CYaAIKzxF4OANTKxJjoAH0NM8XiYAOxWV5faFfWZMRzIL5oBizTCqFLEL6xVCeL4ANzEXkwX3BFioYiU4IAIidIaCwTT/HSQXsDkdMCczpdrmx7rdHiD3p8CD8/oCuCDSSCYbCmgikQJUejMdjcQTvMTSeTaJSGbTJXqmZLXqzDvCOacLldmLz7i9iMAFALXn8AI5ePB/BRfCAMVAi37/IGc%2B2OvmPEAgdVElYg5FKjFYnG0L5ULwMCCxiF/AibBipikWqx614s/Zm46W7k2u52h1O/xPF2Yd2ezDe33%2B0VB4GnUMKcONyPRzArElmABs5gnPr9AbFAIlffrg%2Bww8Jo7jir2yqTuLTGazFhzea%2BBA%2BRepxrecrwyABTAUSha1HTnIiBEemdjTI4a1onAAKy8H4HBaKQqCcG41jWLCGxbJqZj%2BDwpAEJof5rAA1iAgETrcAAcE5SIBYITpIgT%2BKRSH6Jwki8CwSTJKB4GQRwvAKCAyRoWBf6kHAsAwIgIAbAQKReAQ5CUGgBx0AkUQ3JwqiEQAtGRXzAMgiJSLcZi8P8hAkHg6B6PwggiGI7BSDIgiKCo6g8aQuhcKQADuxBMCknA8P%2BQEgehEGcAA8uJYkiqgVBfEpE6qZI6maV82lmD6HgyfQmLmMhKy8NxWhrBASDSSkslkBQECFcVIDAFIZh8HQezEBxECxP5sQRM05xebwrXMMQ5yBbE2h1NxKHSWwgiBQwtAdQ5WCxF4wBuGIOqdaQWAsIYwDiDNbb1Hi7b%2BWidTiTsKEft0/m0HgsTub1HhYP5554Ax3C8HtxDYkoVL7Btl1GOhaxUAYjoAGp4JgLmBdaK2mcIojiFZMO2Wo/lOfoG0oDBlj6FdHGQGsqApL0HEcMpszoCcVKmJY1hmCxb3EEZ%2B1410PRZC4DDuJ47R6GECzlJUeiFJkAhTH4zlC70Qz88sLNDQ0cyi3otT1AI/QtFLIxVOMAyK85cLq3zmsSGsCjwdsxs0RwwGkMxvCsZFKlqRpWmSDpPq4AZ6VIVwWWof9awIJgTBYIkmakNhkj%2BLcFFgpIGiSGYkgThoGi4cEAEcHRpAMchtxERO%2BGBPhXAToBkhcIBFETjb/msexnF%2BzxeWCflwkheJkllagqVyQpHDNCweJgspTBIgYRgJYEtxcLc4H6UQDPGc5MPmfD0iI0oyMOboNVuR5nU%2BVbfkOaxwWieJXzhV8A9DyPY8bZP0%2Bz8l3dFWl47%2BGYvs5bxrflWlnd/6jBvsPZA48qqBGqLVWg9VGrNQct1dqK1EG9X6oNBwK1RqMAIBNKa/lZrzUWrQZaL1VrfSMFtcC%2BA/i7X2g5Q6yBjorTOhncCl1rrtTujscCj1nooTeh9TAX11oUIiKAJufAgYKFBuDSGjBoayFXpZdesgkb2XAjvNGf0qZWCxuw3GYcCZE04KTAg5N/CU0xhYWmdt6aMwMSbboctnAQFcLrEIHMNZLC1hLLI7jfElENt4pWTiVZ9AVlzPIetQm9DVvMMoRs9YRNyGLbWBsEnBJ9usTY5sskZ2trbAKHBr7EEHsPUeYCH5cCnjPDQ7t8ALw/j7bK/tSCB2DqMMOGcs45ynvHMElcwRgn8AnJO5ca4n04PXLi/0%2BItyQCJUKgDX7FXkmwTgA81IsAUHiREeJqm3HZLMPSDTDJL2srDCyEgVE2U3uonQARXLuU8i9Q%2BBTa5BXbmFCKmzYrbN2fiA5RyRQQBSm/BIH9/Df1mX/FZADSpAMSLslIKQAT7MCACYFD5SlkWgbAyg8DwIoOmihYlaChqYO7mNHBk1ppUMwHNBaS1iYoTWj9bhvBqFyz2sTOeqgjp7GYYIc6Dl2E3XOFwh6DM%2BGvQSII4RP0xGzMBkwEGYMIZQ1ISvOGyiLlqJRo88BGNqZ6JxvAfGhMsjEwAPRk2Nbo6xdMEiLyZmHZWvR2acxSTzTxQSBbi3SMLbIkTUkBIYF4/1sswlxPce6%2BWAwI0y31q0ENSs5iJqqCbM2lk3nHxYpwEpLAtk7L2UC80sx6meyadCpuAcg4h0oIfHpIAzBT38P4QCgF47VA0O20i%2BEJn5rYrYBuP8VhYRAJHae/h8JlyQl2icSFSKW38Hmu2UzG65UPrpQd67h1jrWG9DIzhJBAA)

By turning `(not Pred_0<*>::value)` and `(not Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept Deceive = not Predicate<Elements...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDMpK4AMngMmAByPgBGmMT%2BpAAOqAqETgwe3r7%2BQSlpjgJhEdEscQlmtpj2hQxCBEzEBFk%2BfoFVNRn1jQTFUbHxiQoNTS057cM9faXl/gCUtqhexMjsHASYLEkGGyYBbhtbO5h7BwCeSYysmAB0d3vYANTIBgoKj8rEmPiiG6SPBAuVzYdxu2HobEECgeJg0AEE0AxVkkCI8ACKYVZ4ABumEeezRjwYqFRn2%2BeF%2BJ324M2jAIClBDxAIGxYi8VKs8NhcIA9AAqAWCoXCnnc/mCx4AFUww3eQtF8PFwuVAoVcO5h22TF2%2B0Bl2YIPuAWw3OGxC8Dg%2BX3QAH0NNyTAB2Tlwx5ux6TRzIZ4CYaYVRJYiPGKoTyPVnePFOixUMRKJ1ovYuhNJh3wzXHU564G3I0m%2BFmi2k602rgO53c90ehpen0MP0BoMhsMR9n452x2jxx2JgLJnuprnpzZanXnfXXUFw4jAaHG7lfACOXjwX3eGKxuNOZNtGn%2B09njPn8MRDcDwdDtEeVC8DAgc2jXwIywY17jHJTQ7hGe1VPHOanGc53zadMGXVcZXRTFMBxP8dztfcgKPJ5zAANjQqDNzgksuEQw8825U8NkbC8wxvO8H2dJ8XwBc0PwHL9PQpG0mDeeICGoW9TnCAgHnvB8%2B25DgFloTgAFZeD8DgtFIVBODcaxrA9JYVijQIeFIAhNGEhYAGsQDEyQbg0SQuEdAINDEjQzFQ1CzAADns/ROEkXgWAkDQ9ykmS5I4XgFBAPctOk4TSDgWAYEQEAlgIJIvAIchKDQLY6HiSJrk4VR7NQgBaVDJEeYBkG9KQbjMXhySIYg8HQPR%2BEEEQxHYKQZEERQVHUELSF0XCAHdiCYJJOB4ETxMk7TZM4AB5eK4tRVAqEeLLcvywriseUqzEeCAPBS%2Bgg3MAIuDmXhgq0BYICQZKklSsgKAga7bpAYApEqGhaA2YgAogGIJpicJGjOYbeH%2B5hiDOKaYm0TFgo05LIQIKaGFoIGuqwGIvGANwxC7YHSCwFhDGAcQ0YghxYICrr/UxeK1g0njqgm2g8BiAbwY8LAJoIar3O4XhcWIEMlAxQmjGZoxtIWKgDFnAA1PBMF6qb9Tx%2BrhFEcQWrV9q1Amnr9CJlBFMsfQWYCyAFlQFEMkpnLhnQAlTEsawzB8gXqqwc37w6GGMhcBh3E8Vo9FCcJ%2BjKQZcPydIBDGPwo9SGOGGmAYElwuxfYEbpRiDnJ0%2BqTO6hGXow5mSPbGLuO9EmJoU4jtOFgUFTVgkUaOAk0hvN4XyluyvKCqKkqjK2iBcEIEh8XUk7NMlhYEEwJgsASb39MkAIbgATgCR1JBMsxJFQzyxNQjfnI4VzSHco6blQrhUPsjf7LvwyuDErfUM7ibfP8wKZ5Ci7IqXWirNeKiUHqoD2mlDKHBGgsGxI6HKTBngGCMBtDeNwuDGQqvgKqNU6qyEapraQ2slC6y6roSo/VBrAzbh3Luk0OAzVivFR4C1HiwPgYg5BRM0EYOMttXaN19qTwCGYaeZ1QpAMevtMB0jBgcIQS8ImXAN5cD3O9T631fpdVBoDPGujwaQ2hg4PG8M6RIxRhNdGmNsa0FxnzfGmwiYkxkvgL45NcSUxktTZAtM8YM1El1ZmrNAYczWDJbmeBeYaQFkLTAItnHhFAP/PgMsFDy0VsrRgqsCEa2asQ2QOtOoyQoQbCWTsrAm2CV7S21tfScDtgQB2AQ0QVJdm7eIHsZTwEbgXcmzgICuCrrhUOJRU56GjrUYZyRE61DrrMfOnQs6V1zvHH2/Si5TFLuM9OKzshrJriXMZ9dW6LGWC3Y6Z86Ff04Ow4gcCEFIKUaglRfCNDbTHlVERx1Tqz1IPPRegxvaBIvlfdBJlHRv0dOZSQ%2B98q4Xod/Wwv8JEAPgEAmKc1ZEQKEVAtgnBYGrRYAobE3psSvOOMMbB48Pb4IankiQBS2qkOKToEAQQqFDT5rQ8aXVfJMLmqwxahKCrEtJeGClv5hgCJxbdERARxGSzCldWVMj7pyISKSpISQbTko3jaSlBAWL3PynwOgmjKDaJkgY1GGkbVGJhqYiBCMLGo1cZgDGWMcaUw0gTZx4TeBuN9p4iaPi/EOICUzFmbMzhhK5jzPGsTUjxKcWLJJSrpZMDlgrJWKsHFq0Ifk1q8gWV63ZWU4wxsbDVJ6bJOp9ZOA8ntkbZ2lhXbd3djVbpFt1m1H9oHfZIcA7zPLpMjI0yx1FG2ScxZhds7NFWdXPptR50jrThXHo0zDlrtOU3c5zUeWfz5bckVjwxVkslRsaVo8cET0Oj8v%2B5054LyXpQNuoL/DoICAEMSVlTKeW/Y6e%2BR6fKcB/kFP5q8xKbzEvZGyG9JAb3MtvLgQRAkBF5aBvyj6dJn3KiB7uYGcNzAWALNIzhJBAA)

## Links

- [source code](../../../../conceptrodon/mouldivore/concepts/deceive.hpp)
- [unit test](../../../../tests/unit/concepts/mouldivore/deceive.test.hpp)
