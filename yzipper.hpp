#pragma once

#include "typelist.hpp"

namespace yz {

using ::tl::tl;
using ::tl::null_t;

template <class LList, class Cursor, class RList>
struct yzipper;

template <class LHead, class LTail, class Cursor, class RHead, class RTail>
struct yzipper<tl<LHead, LTail>, Cursor, tl<RHead, RTail>> {
    using get = Cursor;
    template <class T>
    using set = yzipper<tl<LHead, LTail>, T, tl<RHead, RTail>>;

    using move_left  = yzipper<LTail, LHead, tl<Cursor, tl<RHead, RTail>>>;
    using move_right = yzipper<tl<Cursor, tl<LHead, LTail>>, RHead, RTail>;
};

template <class Cursor>
struct yzipper<null_t, Cursor, null_t> {
    using get = Cursor;
    template <class T>
    using set = yzipper<null_t, T, null_t>;

    using move_left  = yzipper<null_t, null_t, tl<Cursor, null_t>>;
    using move_right = yzipper<tl<Cursor, null_t>, null_t, null_t>;
};

template <class Cursor, class RHead, class RTail>
struct yzipper<null_t, Cursor, tl<RHead, RTail>> {
    using get = Cursor;
    template <class T>
    using set = yzipper<null_t, T, tl<RHead, RTail>>;

    using move_left  = yzipper<null_t, null_t, tl<Cursor, tl<RHead, RTail>>>;
    using move_right = yzipper<tl<Cursor, null_t>, RHead, RTail>;

};

template <class LHead, class LTail, class Cursor>
struct yzipper<tl<LHead, LTail>, Cursor, null_t> {
    using get = Cursor;
    template <class T>
    using set = yzipper<tl<LHead, LTail>, T, null_t>;

    using move_left  = yzipper<LTail, LHead, tl<Cursor, null_t>>;
    using move_right = yzipper<tl<Cursor, tl<LHead, LTail>>, null_t, null_t>;
};

template <class YZipper>
using get_t = typename YZipper::get;

template <class YZipper, class T>
using set_t = typename YZipper::template set<T>;

template <class YZipper>
using move_left_t  = typename YZipper::move_left;

template <class YZipper>
using move_right_t = typename YZipper::move_right;

template <class T>
using make_t = yzipper<null_t, T, null_t>;

}
