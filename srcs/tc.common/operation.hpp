#ifndef __tc_operation_h__
#define __tc_operation_h__

namespace tc {

/*!
*/
class operation {
public:
	using raw_handler = void (*)(operation*);
	operation(raw_handler handler);
	operation(const operation& rhs);
	operation& operator=(const operation& rhs);
	operation& operator=(const raw_handler handler);
	~operation(void);

	void operator()(void);
private:
	raw_handler _raw_handler;
};

}

#endif