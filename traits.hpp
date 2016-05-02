#pragma once

template <bool CONDITION, class THEN, class ELSE>
struct if_else { using type = ELSE; };
template <class THEN, class ELSE>
struct if_else<true, THEN, ELSE> { using type = THEN; };

template <bool CONDITION, class THEN, class ELSE>
using if_else_t = typename if_else<CONDITION, THEN, ELSE>::type;

