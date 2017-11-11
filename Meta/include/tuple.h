#ifndef _META_TUPLE_H_
#define _META_TUPLE_H_

namespace meta {

	template <typename... _Types> class tuple;

	template <> class tuple<> {
	public:
		tuple() = default;
	};

	template <typename _First, typename... _Rests>
	class tuple<_First, _Rests...> : public tuple<_Rests...> {
	public:
		typedef tuple<_First, _Rests...> type;
		typedef tuple<_Rests...>         parent_type;
		typedef _First                   value_type;

		explicit tuple(value_type value, _Rests... rests) : 
			parent_type(rests), m_val(value) { }

		const value_type& value() const { return m_val; }
		value_type& value() { return m_val; }

	public:
		value_type m_val;
	};

	template <size_t _Index, typename _Tuple> struct tuple_element;

	template <typename _First, typename... _Rests>
	struct tuple_element<0, tuple<_First, _Rests...>> {
		typedef tuple<_First, _Rests...>        tuple_type;
		typedef typename tuple_type::value_type value_type;
	};

	template <size_t _Index, typename _First, typename... _Rests>
	struct tuple_element<_Index, tuple<_First, _Rests...>> : 
		tuple_element<_Index - 1, tuple<_Rests...>> { };


	template <size_t _Index, typename... _Types>
	typename tuple_element<_Index, tuple<_Types...>>::value_type& 
		get(tuple<_Types...>& tuple) {
		return static_cast<
			typename tuple_element<_Index, meta::tuple<_Types...>>::tuple_type
		>(tuple).value();
	}

	template <size_t _Index, typename _Tuple>
	void tuple_fill(_Tuple& tuple) { }

	template <size_t _Index, typename _Tuple, typename _First, typename _Rests>
	void tuple_fill(_Tuple& tuple, _First first, _Rests... args) {
		get<_Index>(tuple) = first;
		tuple_fill<_Index + 1>(tuple, args...);
	}

	template <typename... _Types>
	tuple<_Types...> make_tuple(_Types... args) {
		tuple<_Types...> result;
		tuple_fill<0>(result, args...);
		return result;
	}
}

#endif