#ifndef _META_TINY_H_
#define _META_TINY_H_

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/vector/aux_/at.hpp>

namespace mpl = boost::mpl;

namespace meta {

	struct na { };

	template <
		typename _T0 = na, 
		typename _T1 = na, 
		typename _T2 = na
	> 
	struct tiny {
		typedef tiny<_T0, _T1, _T2> type;
		typedef _T0                 t0;
		typedef _T1                 t1;
		typedef _T2                 t2;
	};

	template <typename _Tiny, typename _Pos>
	struct tiny_iterator {
		typedef mpl::random_access_iterator_tag category;
	};

	template <typename _Tiny, size_t _N>
	struct tiny_at { };

	template <typename _Tiny>
	struct tiny_at<_Tiny, 0> {
		typedef typename _Tiny::t0 type;
	};

	template <typename _Tiny>
	struct tiny_at<_Tiny, 1> {
		typedef typename _Tiny::t1 type;
	};

	template <typename _Tiny>
	struct tiny_at<_Tiny, 2> {
		typedef typename _Tiny::t2 type;
	};
}

namespace boost {
	namespace mpl {
	
		template <typename _Tiny, typename _Pos>
		struct next<meta::tiny_iterator<_Tiny, _Pos>> {
			typedef meta::tiny_iterator<
				_Tiny,
				typename next<_Pos>::type
			> type;
		};

		template <typename _Tiny, typename _Pos>
		struct prior<meta::tiny_iterator<_Tiny, _Pos>> {
			typedef meta::tiny_iterator<
				_Tiny, 
				typename prior<_Pos>::type
			> type;
		};

		template <
			typename _T0,
			typename _T1,
			typename _T2,
			typename _Pos
		>
		struct at<meta::tiny<_T0, _T1, _T2>, _Pos> : 
			meta::tiny_at<meta::tiny<_T0, _T1, _T2>, _Pos::value> { };
	}
}


#endif
