#pragma once

namespace tl {

struct null_t {
    using head = null_t;
    using tail = null_t;
};

template <class T, class U>
struct tl
{
    using head = T;
    using tail = U;
};

template <class TList>
using head_t = typename TList::head;

template <class TList>
using tail_t = typename TList::tail;


template <class ... Ts> struct make;

template <class T, class ... REST>
struct make<T, REST...> { using type = tl<T, typename make<REST...>::type>; };
template <>
struct make<> { using type = null_t; };

template <class ... Ts>
using make_t = typename make<Ts...>::type;


template <class TList, class T>
struct append;
template <>
struct append<null_t, null_t> { using type = null_t; };
template <class T>
struct append<null_t, T> { using type = make_t<T>; };
template <class Head, class T>
struct append<null_t, tl<Head, T>> { using type = tl<Head, T>; };
template <class Head, class Tail, class T>
struct append<tl<Head, Tail>, T>
{ using type = tl<Head, typename append<Tail, T>::type>; };

template <class TList, class T>
using append_t = typename append<TList, T>::type;


} // namespace tl
