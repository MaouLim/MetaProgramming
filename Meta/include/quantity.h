#ifndef _META_QUANTITY_H_
#define _META_QUANTITY_H_

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/placeholders.hpp>

/*
 * Created by Maou Lim on 2017/10/21.
 */

namespace mpl = boost::mpl;

namespace meta {

	typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
	typedef mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
	typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
	typedef mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> current;
	typedef mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
	typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
	typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> amount_of_substance;

	typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;
	typedef mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;
	typedef mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum;
	typedef mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;

	template <typename _Val, typename _Dim>
	class quantity {
	public:
		typedef _Val                 value_type;
		typedef _Dim                 dim_type;
		typedef quantity<_Val, _Dim> self_type;

		typedef _Val&                reference;
		typedef const _Val&          const_reference;
		typedef _Val*                pointer;
		typedef const _Val*          const_pointer;

		quantity(const self_type& other) = default;
		self_type& operator=(const self_type& other) = default;

		explicit quantity(const_reference val) : m_val(val) { }

		template <typename _OtherDim>
		explicit quantity(const quantity<_Val, _OtherDim>& other) : 
			m_val(other.value()) {
			static_assert(mpl::equal<_Dim, _OtherDim>::type::value);
		}

		template <typename _OtherDim>
		self_type& operator=(const )

		const_reference value() const { return m_val; }
		reference value() { return m_val; }

	private:
		_Val m_val;
	};

	template <typename _Val, typename _Dim>
	quantity<_Val, _Dim>
		operator+(const quantity<_Val, _Dim>& first,
		          const quantity<_Val, _Dim>& second) {
		return quantity<_Val, _Dim>(first.value() + second.value());
	};

	template <typename _Val, typename _Dim>
	quantity<_Val, _Dim>
		operator-(const quantity<_Val, _Dim>& first,
	              const quantity<_Val, _Dim>& second) {
		return quantity<_Val, _Dim>(first.value() - second.value());
	};

	template <typename _Val, typename _Dim1, typename _Dim2>
	quantity<
		_Val,
		typename mpl::transform<
			_Dim1,
			_Dim2,
			mpl::plus<
				mpl::placeholders::_1,
				mpl::placeholders::_2
			>
		>::type
	> operator*(const quantity<_Val, _Dim1>& first,
	            const quantity<_Val, _Dim2>& second) {
		typedef typename
			mpl::transform<
				_Dim1,
				_Dim2,
				mpl::plus<
					mpl::placeholders::_1,
				    mpl::placeholders::_2
				>
			>::type new_dim_type;
		return quantity<_Val, new_dim_type>(first.value() * second.value());
	}

	template <typename _Val, typename _Dim1, typename _Dim2>
	quantity<
		_Val,
		typename mpl::transform<
			_Dim1,
			_Dim2,
			mpl::minus<
				mpl::placeholders::_1,
				mpl::placeholders::_2
			>
		>::type
	> operator/(const quantity<_Val, _Dim1>& first,
	            const quantity<_Val, _Dim2>& second) {
		typedef typename
			mpl::transform<
				_Dim1,
				_Dim2,
				mpl::minus<
					mpl::placeholders::_1,
				    mpl::placeholders::_2
				>
			>::type new_dim_type;
		return quantity<_Val, new_dim_type>(first.value() / second.value());
	}


}

#endif