#ifndef __tc_operation_h__
#define __tc_operation_h__

namespace tc {

/*!
*/
template < typename R >
class operation {
public:
	using raw_handler = R (*)(operation*);
	operation(raw_handler handler);
	operation(const operation& rhs);
	operation& operator=(const operation& rhs);
	operation& operator=(const raw_handler handler);
	~operation(void);

	R operator()(void);
private:
	raw_handler _raw_handler;
};


template<typename R>
inline operation<R>::operation(raw_handler handler)
	: _raw_handler(handler)
{
}

template<typename R>
inline operation<R>::operation(const operation & rhs)
	: _raw_handler(rhs._raw_handler)
{
}

template<typename R>
inline operation & operation<R>::operator=(const operation & rhs)
{
	_raw_handler = _rhs._raw_handler;
	return *this;
}

template<typename R>
inline operation & operation<R>::operator=(const raw_handler handler)
{
	_raw_handler = handler;
	return *this;
}

template<typename R>
inline operation<R>::~operation(void)
{
}

template<typename R>
inline R operation<R>::operator()(void)
{
	if (_raw_handler)
		return _raw_handler(this);
	return R();
}

}

#endif