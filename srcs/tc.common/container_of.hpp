#ifndef __tc_container_of_h__
#define __tc_container_of_h__

#define tc_offset_of(type,member)((ptrdiff_t)&((type*)0)->member)
#define tc_container_of(ptr, type, member)  ((type *)((uint8_t*)(ptr) - tc_offset_of(type,member)))
//#define tc_container_of( ptr , type , member )({\
//	const typeof(((type*)0)->member ) * __mptr = (ptr);\
//	(type*)((char*)__mptr-tc_offset_of(type,member));})

namespace tc {
	/*!
	 * @brief boost/intrusive/detail/parent_from_member.hpp
	 */
	template < class Parent , class Member >
	std::ptrdiff_t offset_of( const Member Parent::*ptr_to_member ){
		const Parent * const parent = nullptr;
		const char *const member = static_cast<const char*>(
				static_cast<const void*>(&(parent->*ptr_to_member)));
		std::ptrdiff_t val(member - static_cast<const char*>(
					static_cast<const void*>(parent)));
		return val;
	}


	template<class Parent, class Member>
	inline Parent* container_of(Member *member, const Member Parent::* ptr_to_member)
	{
		return static_cast<Parent*>(
				static_cast<void*>(
					static_cast<char*>(
						static_cast<void*>(member)) - offset_of(ptr_to_member)
					)
				);
	}

	template<class Parent, class Member>
	inline const Parent *container_of(const Member *member, const Member Parent::* ptr_to_member)
	{
		return static_cast<const Parent*>(
			 static_cast<const void*>(
			  static_cast<const char*>(static_cast<const void*>(member)) - offset_of(ptr_to_member)
			 )
			);
	}

}

#endif
